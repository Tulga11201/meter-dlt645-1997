#define DEMAND_C
#include "Includes.h"

#define DEMAND_PERIOD_OUTPUT 0
#define SLIDE_PERIOD_OUTPUT 1
//��������ǰ��������ڻ��ǰ������������?
#define DEMAND_OUTPUT_MODE (Mode_Word.Mode[2].Bit.Bit4==1?DEMAND_PERIOD_OUTPUT:SLIDE_PERIOD_OUTPUT)
/*
�����͵�ѹͳ�Ƶ������ݶ�����������
1 ������ɺ󣬽���ǰ���ݴ洢��������ȫ��дΪ0����ʾ��ǰ������������Ϊ�գ���δд�뵱�£��µ�һ�£�������
2 ����ʱ��㣬���Զ�������������ܵ�������(ʵ����Ӧ�ò����ܳ�����)
3 ����ڶ�������ϸ�λ�ˣ���ô�����󣬶�ȡ��ǰ������ȫΪ0�����Ჹ����������������˲������̣����ڿ��Զ���ǰ����ʷ���ݣ����Ի��ǲ��Ჹ��
4 ����ڶ���ǰһ�̸�λ�ˣ���������Ȼ�ᰴ����ʷ���ݽ��ж��ᡣ
5 ����ڶ���Ĺ����и�λ��,���ݲ����γ�У���,��ǰ����Ҳû������Ϊ0�������ϵ���ǻᲹ��
*/

//��ʼ��������ز���
void Read_Demand_Para_From_Rom()
{
  INT8U Err;
  INT16U Len;
  //��ȡ��������
  Len=Read_Storage_Data(0xC111,(INT8U *)&Demand_Para.Period,(INT8U *)&Demand_Para.Period,1,&Err);
  ASSERT(A_WARNING,1==Len && NO_ERR==Err);
  Demand_Para.Period=Bcd2Hex_Byte(Demand_Para.Period);
  //��ȡ��������ʱ��
  Len=Read_Storage_Data(0xC112,(INT8U *)&Demand_Para.Slide_Time,(INT8U *)&Demand_Para.Slide_Time,1,&Err);
  ASSERT(A_WARNING,1==Len && NO_ERR==Err);
  Demand_Para.Slide_Time=Bcd2Hex_Byte(Demand_Para.Slide_Time);
  
  SET_STRUCT_SUM(Demand_Para);  
}

//������������Ƿ�Ϸ�
void Check_Demand_Para_Avail()
{
  INT8U Re;
  Re=CHECK_STRUCT_SUM(Demand_Para);//��������
  if(ASSERT(A_WARNING,1==Re))
  {
     Read_Demand_Para_From_Rom();    
  }
}

//���ĳһ��������Ԫ����
void Clr_Demand_Unit(INT8U Index)
{
  //���ù����ۼӵ�Ԫ��0
  Demand_Accu.Pos_Active[Index]=0;
  Demand_Accu.Neg_Active[Index]=0;
  Demand_Accu.Pos_Reactive[Index]=0;
  Demand_Accu.Neg_Reactive[Index]=0;     
  Demand_Accu.Counts[Index]=0;
  Demand_Accu.Mins[Index]=0;
  SET_STRUCT_SUM(Demand_Accu);
}

//�ж��������ںͻ���ʱ��������������
//�������㻬��ʱ��=1,2,3,5,10,��������/����ʱ��<MAX_PERIOD_SLIDE_RATIO(15)
void Check_Demand_Para()
{
  if(ASSERT(A_WARNING,
            (Demand_Para.Period%Demand_Para.Slide_Time==0 &&\
             Demand_Para.Period/Demand_Para.Slide_Time>=1 &&\
             Demand_Para.Period/Demand_Para.Slide_Time<=MAX_PERIOD_SLIDE_RATIO)))
  {
    //���������������Ĭ��Ϊ1���ӻ���ʱ���15������������
    //ASSERT(A_WARNING,0);
    DEBUG_PRINT(HUCK,DEBUG_0,"Demand_Para error");
    Demand_Para.Slide_Time=1;
    Demand_Para.Period=MAX_PERIOD_SLIDE_RATIO; 
    SET_STRUCT_SUM(Demand_Para);
  }  
  
}

//�����ۼӼ���,ÿ�����һ�θú���
//�ú�����ÿ�������ۼӵ�Ԫ�����ۼӣ������ݵ�ǰʱ������Ƿ����һ������
void Demand_Calc()
{
  INT32U Counts;
  INT16U Mins;
  INT8U i,j,Re;
  static S_Int8U Min_Bak={CHK_BYTE,0xFF,CHK_BYTE};

  Re=CHECK_STRUCT_SUM(Demand_Para);
  if(ASSERT(A_WARNING,0!=Re))
    Check_Data_Avail();
  
  Re=CHECK_STRUCT_SUM(Demand_Accu);
  if(ASSERT(A_WARNING,0!=Re))//����Ѿ�ͳ�ƹ������������Ƿ���ȷ
  {
    mem_set((void *)&Demand_Accu,0,sizeof(Demand_Accu),(void *)&Demand_Accu,sizeof(Demand_Accu));
    SET_STRUCT_SUM(Demand_Accu);
  }

  if(ASSERT(A_WARNING,Demand_Para.Slide_Time!=0))//��֤Demand_Accu.Slide_Time!=0
  {
    Demand_Para.Slide_Time=1;
    SET_STRUCT_SUM(Demand_Para);
  }
  
  Check_Demand_Para();

  Re=1;
  Re &= CHECK_STRUCT_SUM(Measu_Status_Mode_ToPub_PUCK);
  Re &= CHECK_STRUCT_SUM(Measu_InstantData_ToPub_PUCK);
  ASSERT(A_WARNING,1==Re);
  if(1==Re)
  {
    //��ÿ����������(�����ۼӵ�Ԫ)�����ۼ�
    for(i=0;i<MAX_PERIOD_SLIDE_RATIO;i++)
    {
      //�ۼӹ���,ԭ������6λС����ʵ��ʹ��4ΪС�������Ҫ����POWER_DATA_RATIO
      if(Mode_Word.Mode[0].Bit.Bit6==1)//�����,����ǵ������������ȫ����������
      {
        Demand_Accu.Pos_Active[i]+=(Measu_InstantData_ToPub_PUCK.AcPower.Sum/POWER_DATA_RATIO);
      }
      else//˫���,�������ʶ�����
      {
        if(Measu_Status_Mode_ToPub_PUCK.SUM_APwrDir==POWER_DIRECT_N)//�����й�����
          Demand_Accu.Pos_Active[i]+=(Measu_InstantData_ToPub_PUCK.AcPower.Sum/POWER_DATA_RATIO);
        else   //�����й�����
          Demand_Accu.Neg_Active[i]+=(Measu_InstantData_ToPub_PUCK.AcPower.Sum/POWER_DATA_RATIO);
      }
      //1,2�����޹����������޹�
      if(QUADRANT1==Measu_InstantData_ToPub_PUCK.Quadrant.Sum ||\
         QUADRANT2==Measu_InstantData_ToPub_PUCK.Quadrant.Sum)//�����޹�����
        Demand_Accu.Pos_Reactive[i]+=(Measu_InstantData_ToPub_PUCK.ReacPower.Sum/POWER_DATA_RATIO);
      //3,4�����޹����練���޹�
      else if(QUADRANT3==Measu_InstantData_ToPub_PUCK.Quadrant.Sum ||\
              QUADRANT4==Measu_InstantData_ToPub_PUCK.Quadrant.Sum)//�����޹�����
        Demand_Accu.Neg_Reactive[i]+=(Measu_InstantData_ToPub_PUCK.ReacPower.Sum/POWER_DATA_RATIO);
      else if(NO_QUADRANT!=Measu_InstantData_ToPub_PUCK.Quadrant.Sum)
        ASSERT(A_WARNING,0);
      
      Demand_Accu.Counts[i]++;
      SET_STRUCT_SUM(Demand_Accu);
    }
  }
  
  //ÿ���������Ƿ��˳�����ʱ��
  Re=CHECK_STRUCT_VAR(Min_Bak);
  ASSERT(A_WARNING,1==Re);
  if(Min_Bak.Var!=Cur_Time0.Time[T_MIN])
  {
    Min_Bak.Var=Cur_Time0.Time[T_MIN];  
    Mins=(INT16U)Cur_Time0.Time[T_HOUR]*60+(INT16U)Cur_Time0.Time[T_MIN];
    
    if(Demand_Para.Period!=0 && (Mins%Demand_Para.Period)==0)//�������ڵ�
    {
      Set_Event_Instant(ID_DEMAND_ARRIVE);//��������
      //if(DEMAND_OUTPUT_MODE EQ DEMAND_PERIOD_OUTPUT)
      {
        Port_Out_Pub(EXT_ID_DEMAND,85);
        DEBUG_PRINT(HUCK,DEBUG_0,"Demand Period Arrived!!!"); 
      }
    }
    
    //ÿ��һ������ʱ���һ������,������ǻ������ڣ������һ������ʵ�Ԫ����֤���Ἴ��
    Counts=0;
    i=0;
    
    if(0==Demand_Para.Slide_Time)
    {
      ASSERT(A_WARNING,0);
      Demand_Para.Slide_Time=1;
      SET_STRUCT_SUM(Demand_Para);
    }
    
    for(j=0;j<MAX_PERIOD_SLIDE_RATIO && j<(Demand_Para.Period/Demand_Para.Slide_Time);j++)
    {
      Demand_Accu.Mins[j]++;//���Ӽ���
      if(Counts<Demand_Accu.Counts[j])//�ҵ���ǰ�������������Ǹ���Ԫ��������
      {
        i=j;
        Counts=Demand_Accu.Counts[j];
      }
    }
    SET_STRUCT_SUM(Demand_Accu);
    
    if(Demand_Para.Slide_Time!=0 && (Mins%Demand_Para.Slide_Time)==0)//�������ڵ�,������ʱ�䵽
    {
      Set_Event_Instant(ID_SLIP_ARRIVE);//��������
      //if(DEMAND_OUTPUT_MODE EQ SLIDE_PERIOD_OUTPUT)
      {      
        Port_Out_Pub(EXT_ID_SLIPE,85);
        DEBUG_PRINT(HUCK,DEBUG_0,"Demand Slide Period Arrived!!!"); 
      }
      //����ƽ��ֵ��Ҳ��������
      //if(Counts>=(INT32U)Demand_Para.Period*(60-10))//��ֹ�ڲ����������ƫ��ʼ�ȥ10S
      if(Demand_Accu.Mins[i]>=((INT32U)Demand_Para.Period))
      {
        Demand_Accu.Cur_Pos_Active=Demand_Accu.Pos_Active[i]/Counts;
        Demand_Accu.Cur_Neg_Active=Demand_Accu.Neg_Active[i]/Counts; 
        Demand_Accu.Cur_Pos_Reactive=Demand_Accu.Pos_Reactive[i]/Counts;
        Demand_Accu.Cur_Neg_Reactive=Demand_Accu.Neg_Reactive[i]/Counts;
        
        Mins=Demand_Accu.Mins[i];
        
        //���ù����ۼӵ�Ԫ��0        
        Clr_Demand_Unit(i);
        
        //��ӡ������ص�����Ϣ
        DEBUG_PRINT(HUCK,DEBUG_0,"------Demand Update-----");
        DEBUG_PRINT(HUCK,DEBUG_0,"The %dth Unit make demand,Mins=%d,Counts=%d",\
                                  i,Mins,Counts);
        DEBUG_PRINT(HUCK,DEBUG_0,"Demand:Pos_Act=%d",Demand_Accu.Cur_Pos_Active);
        DEBUG_PRINT(HUCK,DEBUG_0,"Demand:Neg_Act=%d",Demand_Accu.Cur_Neg_Active);
        DEBUG_PRINT(HUCK,DEBUG_0,"Demand:Pos_React=%d",Demand_Accu.Cur_Pos_Reactive);
        DEBUG_PRINT(HUCK,DEBUG_0,"Demand:Neg_React=%d",Demand_Accu.Cur_Neg_Reactive);
      }
      else
        Clr_Demand_Unit(i);//��ʱӦ���Ǹ��ϵ�׶�
    }
    else//���������ʵ�Ԫ����ֹ������������һ����������
    {
        Clr_Demand_Unit(i);
    }
  }
}

//����������0����,�ڸ�λʱ���øú���
//����ʱ��Ҫ�������ۼ��м䵥Ԫ���ݶ�Ϊ����
void Demand_Accu_Clear()
{
  //INT8U i;
  //Mins=(INT16U)Cur_Time0.Time[T_HOUR]*60+(INT16U)Cur_Time0.Time[T_MIN];
  //i=(Mins/Demand_Para.Slide_Time)%(Demand_Para.Period/Demand_Para.Slide_Time);//�ڼ����м䵥Ԫ������

  mem_set((void *)&Demand_Accu,0,sizeof(Demand_Accu),(void *)&Demand_Accu,sizeof(Demand_Accu));
  
  //for(i=0;i<MAX_PERIOD_SLIDE_RATIO;i++)
    //Demand_Accu.Init_Flag[i]=1;//��ʼ����־��1����������ʱ����ʹ�øñ�־
  //���¸��ݵ�ǰʱ�����ÿ�������ۼӵ�ԪӦ���߹���ʱ��
  //Mins=(INT16U)Cur_Time0.Time[T_HOUR]*60+(INT16U)Cur_Time0.Time[T_MIN];
  //i=(Mins/Demand_Para.Slide_Time)%(Demand_Para.Period/Demand_Para.Slide_Time);//�ڼ����м䵥Ԫ������
 
  SET_STRUCT_SUM(Demand_Accu);

}

//������0����ڲ���pTime��ʾ�����ʱ���,һ���ǵ�ǰʱ��
//��������Ҫ���ݸ�ʱ�������´��������ݶ����ʱ��
void Demand_Clear(S_HEX_Time *pTime)
{
  //Demand_Accu_Clear();//���ۼ�,���µ������һ��Ҫ���ۼ�?
  mem_set((void *)&Cur_Demand,0,sizeof(Cur_Demand),(void *)&Cur_Demand,sizeof(Cur_Demand));//������
  SET_STRUCT_SUM(Cur_Demand.Demand[0]);
  SET_STRUCT_SUM(Cur_Demand.Demand[1]);
  SET_STRUCT_SUM(Cur_Demand);

}

//�����ϵ�ʱ�Ĵ�����Ҫ�ǵ����˯��ʱ������һ����������ʱ�Ĵ���
//�����ϵ�ʱ���øú��������Խ�Sleep_Secsֵ����һ�����ֵ
//����
void PowerOn_Demand_Proc()
{
  /*
  if(Check_Rst_Flag()==SOFT_RST)//����������λ��������м��ۼӵ�Ԫ
    Demand_Accu_Init(0);
  else
  {
    //�˴���Ҫ���˯��ʱ��������,����ΪDemand_Accu_Init����ڲ���
    Demand_Accu_Init(0xFFFFFFFF);//�ϵ�������ۼӵ�Ԫ

  }
  */
  Demand_Accu_Clear();
}

//�����ۼӵ�Ԫ��ʼ��
//Sleep_Secs��ʾ������һ�������ۼ��Ѿ��߹��˶೤ʱ��
/*
void Demand_Accu_Init(INT32U Sleep_Secs)
{
  INT32U Period;
  INT8U Re,i;
     
  Re=CHECK_STRUCT_SUM(Demand_Para);
  if(ASSERT(A_WARNING,Re>0))
    Check_Data_Avail();
  
  Period=(INT32U)(Demand_Para.Period)*60;//������������
  
  if(Sleep_Secs>=Period)//����ʱ�䳬��һ���������ڣ���Ҫ������������0
  {
    Demand_Accu_Clear();
  }
  else
  {   
    Re=CHECK_STRUCT_SUM(Mode_Word);
    //ģʽ��У����Ƿ���ȷ
    if(ASSERT(A_WARNING,0!=Re))
      Check_Data_Avail();

    //���������������Ļ����������ۼӵ�Ԫ
    if(Mode_Word.Mode[2].Bit.Bit3==0)//��������������
    {
      Demand_Accu_Clear();//���м��ۼ�
    }
    else
    {
      Re=CHECK_STRUCT_SUM(Demand_Accu);
      if(ASSERT(A_WARNING,0!=Re))
         Demand_Accu_Clear();
      else
      {
        Re=CHECK_STRUCT_SUM(Demand_Para);
        if(ASSERT(A_WARNING,1==Re))
          Check_Data_Avail();
          
        for(i=0;i<MAX_PERIOD_SLIDE_RATIO;i++)//�˴��д��ģ���Ҫ�ǿ���������³����Ƿ�����
        {
          Demand_Accu.Counts[i]+=Sleep_Secs;
          
          //�Ƚ�ÿ���м䵥Ԫ�ļ���������ü���������һ���������ڵ�ʱ�䣬����Ϊ
          //��ͣ���ڼ䣬���м䵥Ԫ�������һ��
          //+2��Ϊ�˷�ֹ���ֵ�����ϵ�������һ����Ԫ�ĳ�����������,�ϵ�ʱ�俿��������ʱ��
          //0-------------------------15
          //                  |pd    |po
          //������������׳����жϴ���,�������2����,ȷ���ڵ����ڼ����һ������
          if(Demand_Accu.Counts[i]>=((INT32U)Demand_Para.Period+2)*60)//�����ڼ�϶�����һ������
          {
            Demand_Accu.Counts[i]=Demand_Accu.Counts[i]-(INT32U)Demand_Para.Period*60;
            Demand_Accu.Pos_Active[i]=0;//���м䵥Ԫ
            Demand_Accu.Neg_Active[i]=0;
            Demand_Accu.Pos_Reactive[i]=0;
            Demand_Accu.Neg_Reactive[i]=0;
            //Demand_Accu.Init_Flag[i]=1;//��ʼ����־
          }
        }
        SET_STRUCT_SUM(Demand_Accu);
      }
    }
  }
}
*/

//�������ڵ��ۼ�
void Demand_Counts_Init()
{
  INT8U i;
  
  for(i=0;i<MAX_PERIOD_SLIDE_RATIO;i++)
  {
    Demand_Accu.Counts[i]=(INT16U)Demand_Para.Slide_Time*60*i;//ÿ�������ۼ��м䵥Ԫ�ĸ����ۼ� 
  } 
}

//��鵱ǰ�����Ƿ����������
void Demand_Check_Max()
{
  INT8U i,Re,Cur_Rate,Max_Flag;
  INT8U TempTime[5];

  Re=1;
  Re&=CHECK_STRUCT_SUM(Cur_Time0);//��鵱ǰ�����ۼӵ�Ԫ
  Re&=CHECK_STRUCT_SUM(Demand_Accu);//��鵱ǰ�����ۼӵ�Ԫ
  Re&=CHECK_STRUCT_SUM(Cur_Demand);//��鵱ǰ����
  Re&=CHECK_STRUCT_SUM(Cur_Rate_Info);//��ǰ���������Ϣ 
  Re&=CHECK_STRUCT_SUM(Multi_Rate_Para);//��鸴������ز���
  
  if(ASSERT(A_WARNING,0!=Re))
    Check_Data_Avail();

  Max_Flag=0;//�ñ�־Ϊ1��ʾ������һ���������
  
  //�����й�������������䷢��ʱ��
  DIS_PD_INT;//������������ʱ�ص����ж�
  for(i=0;i<2;i++)
  {
    if(i==0)
      Cur_Rate=0;//�����ܵ����ֵ
    else
    {
      Cur_Rate=Cur_Rate_Info.Rate;//Get_Using_Rate();//���㵱ǰ���ʵ����ֵ
      //���Cur_Rate����ȷ��
      if(ASSERT(A_WARNING,Cur_Rate>0 && Cur_Rate<=Multi_Rate_Para.Rates && Cur_Rate<=MAX_RATES))
        Cur_Rate=1;
    }
    //�õ���ǰBCDʱ��
    Hex2Bcd_Buf((void *)Cur_Time0.Time,sizeof(Cur_Time0.Time),TempTime,TempTime,sizeof(TempTime));
    //��ǰ�����ȸ��������������
    //�����й����������䷢��ʱ��
    if(Demand_Accu.Cur_Pos_Active>Cur_Demand.Demand[i].Pos_Active)
    {
      Cur_Demand.Demand[i].Pos_Active=Demand_Accu.Cur_Pos_Active;
      mem_cpy((void *)Cur_Demand.Demand[i].Pos_Active_Time,\
              TempTime,\
              5,\
              (void *)Cur_Demand.Demand[i].Pos_Active_Time,\
              sizeof(Cur_Demand.Demand[i].Pos_Active_Time));
      SET_STRUCT_SUM(Cur_Demand);
      Max_Flag=1;
    }
    //�����й�������������䷢��ʱ��  
    if(Demand_Accu.Cur_Neg_Active>Cur_Demand.Demand[i].Neg_Active)
    {
      Cur_Demand.Demand[i].Neg_Active=Demand_Accu.Cur_Neg_Active;
      mem_cpy((void *)Cur_Demand.Demand[i].Neg_Active_Time,\
              TempTime,\
              5,\
              (void *)Cur_Demand.Demand[i].Neg_Active_Time,\
              sizeof(Cur_Demand.Demand[i].Neg_Active_Time));
      SET_STRUCT_SUM(Cur_Demand);
      Max_Flag=1;
    }
  //�����޹�������������䷢��ʱ��  
    if(Demand_Accu.Cur_Pos_Reactive>Cur_Demand.Demand[i].Pos_Reactive)
    {
      Cur_Demand.Demand[i].Pos_Reactive=Demand_Accu.Cur_Pos_Reactive;
      mem_cpy((void *)Cur_Demand.Demand[i].Pos_Reactive_Time,\
              TempTime,\
              5,\
              (void *)Cur_Demand.Demand[i].Pos_Reactive_Time,\
              sizeof(Cur_Demand.Demand[i].Pos_Reactive_Time));
      SET_STRUCT_SUM(Cur_Demand);
      Max_Flag=1;
    } 
  //�����޹�������������䷢��ʱ�� 
    if(Demand_Accu.Cur_Neg_Reactive>Cur_Demand.Demand[i].Neg_Reactive)
    {
      Cur_Demand.Demand[i].Neg_Reactive=Demand_Accu.Cur_Neg_Reactive;
      mem_cpy((void *)Cur_Demand.Demand[i].Neg_Reactive_Time,\
              TempTime,\
              5,\
              (void *)Cur_Demand.Demand[i].Neg_Reactive_Time,\
              sizeof(Cur_Demand.Demand[i].Neg_Reactive_Time));
      SET_STRUCT_SUM(Cur_Demand);
      Max_Flag=1;
    }
  }
  EN_PD_INT;//�������ж�
  
  //������һ�������������
  if(Max_Flag==1)
  {
    DEBUG_PRINT(HUCK,DEBUG_0,"Demand max data generated");
    //Save_Cur_Demand_PD_Data(); 
  }
}
//��������,����ÿ���ۼ�������Ԫ���Լ��뵱ǰ��������Ƚϣ��������ֵ 
void Demand_Proc()
{
  INT8U Re;
  static S_Int32U Sec_Timer={CHK_BYTE,0x00,CHK_BYTE};
  
  Re=CHECK_STRUCT_VAR(Sec_Timer);
  ASSERT(A_WARNING,1==Re);
  
  if(Sec_Timer_Pub==Sec_Timer.Var)//ʱ�仹û���߹�1S���ú���ֻ����1S����һ�����������
    return;  
  Sec_Timer.Var=Sec_Timer_Pub;//�����������
  
  Demand_Calc();//ÿ��������ۼ��Լ�ÿ���ӵĵ�ǰ��������,�Լ�ÿ���������ڵ�������� 
  Demand_Check_Rate_Change();//��鵱ǰ�����Ƿ������޸ģ�����޸�����Ҫ���¶�ȡ��ǰ���ʵ���������
  Demand_Check_Max();//��鵱ǰ�����Ƿ����������
}

//���浱ǰ��������
void Save_Cur_Demand_Data()
{
  INT8U Re;
  INT32U Off;

  Re=Check_Demand_Data((S_Demand *)&Cur_Demand);
  if(1==Re)
  {
    Re=Write_Storage_Data_Fix_Len(CUR_DEMAND,0,(void *)&Cur_Demand.Demand[0],ONE_DEMAND_SAVE_SIZE);
    ASSERT(A_WARNING,NO_ERR==Re);
    //�ٱ��浱ǰ��������
    Off=DEMAND_RATE_OFF(Cur_Demand.Rate);
    Write_Storage_Data_Fix_Len(CUR_DEMAND,Off,(void *)&Cur_Demand.Demand[1],ONE_DEMAND_SAVE_SIZE);
    ASSERT(A_WARNING,NO_ERR==Re);
  }
  else
    ASSERT(A_WARNING,0);
}

//���浱ǰ������������
void Save_Cur_Demand_Bak_Data()
{
  INT8U Re;
  INT32U Off;

  Re=Check_Demand_Data((S_Demand *)&Cur_Demand);
  if(1==Re)
  {
    Re=Write_Storage_Data_Fix_Len(CUR_DEMAND_BAK,0,(void *)&Cur_Demand.Demand[0],ONE_DEMAND_SAVE_SIZE);
    ASSERT(A_WARNING,NO_ERR==Re);
    //�ٱ��浱ǰ��������
    Off=DEMAND_RATE_OFF(Cur_Demand.Rate);
    Write_Storage_Data_Fix_Len(CUR_DEMAND_BAK,Off,(void *)&Cur_Demand.Demand[1],ONE_DEMAND_SAVE_SIZE);
    ASSERT(A_WARNING,NO_ERR==Re);
  }
  else
    ASSERT(A_WARNING,0);
}

//���浱ǰ������������
void Save_Cur_Demand_PD_Data()
{
  INT8U Re;

  Re=Check_Demand_Data((S_Demand *)&Cur_Demand);
  if(1==Re)//����������ݵ�У��ͣ�У��ʹ��������´�ROM�ж�ȡ
  {
    //mem_cpy((void *)Cur_Demand.Time,(void *)Cur_Time0.Time,sizeof(Cur_Time0.Time),(void *)Cur_Demand.Time,sizeof(Cur_Demand.Time));
    Re=Write_Storage_Data(CUR_DEMAND_PD,(void *)&Cur_Demand,sizeof(S_Demand));
    ASSERT(A_WARNING,NO_ERR==Re);
  }
  else
    ASSERT(A_WARNING,0);
}

//����Ĭ�ϵ���������
void Set_Def_Cur_Demand_Data()
{
  INT8U i,Re;
  INT32U Off;
  //����ʼ����д��洢����  
  DEBUG_PRINT(HUCK,DEBUG_0,"Set Def Demand Data");
  mem_set((void *)&Cur_Demand,0,sizeof(Cur_Demand),(void *)&Cur_Demand,sizeof(Cur_Demand));
  SET_STRUCT_SUM(Cur_Demand.Demand[0]);
  SET_STRUCT_SUM(Cur_Demand.Demand[1]);
  
  INIT_STRUCT_VAR(Cur_Demand);
  SET_DATA_READY_FLAG(Cur_Demand);
  
  SET_STRUCT_SUM(Cur_Demand); 
  
  //���������ʵ�����������0
  for(i=0;i<=MAX_RATES;i++)
  {
    Cur_Demand.Rate=i;
    SET_STRUCT_SUM(Cur_Demand);
    
    Off=DEMAND_RATE_OFF(Cur_Demand.Rate);
    Re=Write_Storage_Data_Fix_Len(CUR_DEMAND,Off,(void *)&Cur_Demand.Demand[0],ONE_DEMAND_SAVE_SIZE);
    ASSERT(A_WARNING,NO_ERR==Re);
    
    Off=DEMAND_RATE_OFF(Cur_Demand.Rate);
    Re=Write_Storage_Data_Fix_Len(CUR_DEMAND_BAK,Off,(void *)&Cur_Demand.Demand[0],ONE_DEMAND_SAVE_SIZE);
    ASSERT(A_WARNING,NO_ERR==Re);    
  }

  mem_set((void *)&Cur_Demand,0,sizeof(Cur_Demand),(void *)&Cur_Demand,sizeof(Cur_Demand)); 
  Cur_Demand.Rate=0;
  SET_STRUCT_SUM(Cur_Demand.Demand[0]);
  SET_STRUCT_SUM(Cur_Demand.Demand[1]);

  INIT_STRUCT_VAR(Cur_Demand);
  SET_DATA_READY_FLAG(Cur_Demand);

  SET_STRUCT_SUM(Cur_Demand);
  
  mem_set((void *)&Demand_Accu,0,sizeof(Demand_Accu),(void *)&Demand_Accu,sizeof(Demand_Accu));//���м��ۼӵ�Ԫ
  SET_STRUCT_SUM(Demand_Accu);
  
  Save_Cur_Demand_PD_Data();  
}

//����Ĭ�ϵ���������
void Set_Def_Demand_Data()
{
  INT8U i,j;
  INT32U Off;

  //���õ�ǰ��������
  Set_Def_Cur_Demand_Data();

  //������ʷ��������
  for(i=0;i<HIS_DEMAND_DATA_MONTHS;i++)
  {
    for(j=0;j<MAX_RATES+1;j++)
    {
      Off=DEMAND_RATE_OFF(j);
      Write_Storage_Data_Fix_Len(HIS_DEMAND+i,Off,(void *)&Cur_Demand.Demand[0],ONE_DEMAND_SAVE_SIZE);    
    }
  }
}

//��ȡ���ڵ�ǰ�����洢���е��ܻ�ַ�����������
//Rate:��Ҫ��ȡ�������ķ���,0��ʾ��
//pDst:Ŀ�껺����
//pDst_Start��DstLenһ���޶�pDst�ͷ��س��ȵķ�Χ
//����ֵ:��ȡ���ݳ���,��ȡʧ�ܷ���0���ɹ�����ONE_DEMAND_SAVE_SIZE
INT16U Read_Demand_Rate_Data(INT8U Rate,void *pDst,void *pDst_Start,INT16U DstLen)
{
  INT8U Err;
  INT32U Off;

  Off=DEMAND_RATE_OFF(Rate);
  //�ȶ�ȡ��ǰ�洢��
  if(Read_Storage_Data_Fix_Len(CUR_DEMAND,Off,ONE_DEMAND_SAVE_SIZE,pDst,pDst_Start,\
                               DstLen,&Err)!=ONE_DEMAND_SAVE_SIZE)
  {
    DEBUG_PRINT(HUCK,DEBUG_0,"Read CUR_DEMAND CurRate data error");
    //�ٶ�ȡ���ݴ洢��
    OS_TimeDly_Ms(500);
    if(Read_Storage_Data_Fix_Len(CUR_DEMAND_BAK,Off,ONE_DEMAND_SAVE_SIZE,pDst,pDst_Start,\
                                 DstLen,&Err)!=ONE_DEMAND_SAVE_SIZE)
    {
        //�ò�����Ĭ�ϲ�����,ʵ���ϲ���������������
        DEBUG_PRINT(HUCK,DEBUG_0,"Read CUR_DEMAND_BAK Rate %d data Error",Rate);
        //������еı��������ݶ�û����������Ϊ�ǵ�һ���ϵ磬������0
        return 0;
    }
  }
  return ONE_DEMAND_SAVE_SIZE;
}

//������������Ƿ�Ϸ�
INT8U Check_Demand_Data(S_Demand *pDemand)
{
  INT8U i,Re;
  INT8U Temp[5]={0,0,0,0,0};

  Re=1;
  Re&=(pDemand->Head==CHK_BYTE && pDemand->Tail==CHK_BYTE)?1:0;  
  Re&=Check_STRUCT_Sum(pDemand,sizeof(S_Demand),pDemand->CS,sizeof(pDemand->CS));
  Re&=(pDemand->Data_Ready_Flag==DATA_READY)?1:0;  
  if(ASSERT(A_WARNING,0!=Re))
    return 0;
  
  if(!(pDemand->Rate<=Multi_Rate_Para.Rates && pDemand->Rate<=MAX_RATES))
  {
    ASSERT(A_WARNING,0);
    return 0;
  }
  
  for(i=0;i<2;i++)
  {
    if(!(memcmp(pDemand->Demand[i].Pos_Active_Time,Temp,5)==0 || _Check_BCD_Time(pDemand->Demand[i].Pos_Active_Time)==1) ||
       !(memcmp(pDemand->Demand[i].Neg_Active_Time,Temp,5)==0 || _Check_BCD_Time(pDemand->Demand[i].Neg_Active_Time)==1) ||
       !(memcmp(pDemand->Demand[i].Pos_Reactive_Time,Temp,5)==0 || _Check_BCD_Time(pDemand->Demand[i].Pos_Reactive_Time)==1) ||
       !(memcmp(pDemand->Demand[i].Neg_Reactive_Time,Temp,5)==0 || _Check_BCD_Time(pDemand->Demand[i].Neg_Reactive_Time)==1))
    { 
      ASSERT(A_WARNING,0);
      return 0;
    }  
  }
  return 1; 
}

//��ROM�ж�����ǰ��������
void Read_Demand_Data_From_Rom()
{
  INT8U Err,Re,Rate,i;
  S_Demand *p;
  
  //�ȶ�ȡ����洢������
  //�ٶ���ͨ����
  //��������������
  Re=CHECK_STRUCT_SUM(Cur_Rate_Info);
  if(ASSERT(A_WARNING,0!=Re))
    Check_Data_Avail();
  
  OS_Sem_Pend(PUB_BUF0_SEM_ID); 
  p=(S_Demand *)Pub_Buf0;
  if(Read_Storage_Data(CUR_DEMAND_PD,p,p,sizeof(Pub_Buf0),&Err)!=sizeof(Cur_Demand) ||\
     Check_Demand_Data((S_Demand *)p)==0)
  {
    DEBUG_PRINT(HUCK,DEBUG_0,"Read CUR_DEMAND_PD data error");
    OS_TimeDly_Ms(500);
    //��ȡ�ܺ͵�ǰ��������
    for(i=0;i<2;i++)
    {
      if(i==0)
        Rate=0;//��������ʱƫ��Ϊ0
      else
        Rate=Cur_Rate_Info.Rate;//����ʱ���ݷ��ʼ���ƫ��

      p->Rate=Cur_Rate_Info.Rate;
      //�ӵ�ǰ��������ȡ��ǰ���ܷ��ʵ���������
      if(Read_Demand_Rate_Data(Rate,(void *)&p->Demand[i],(void *)&p->Demand[i],sizeof(S_One_Demand))!=ONE_DEMAND_SAVE_SIZE)
      {
        DEBUG_PRINT(HUCK,DEBUG_0,"Read CUR_DEMAND Rate %d data error",Rate);
        mem_set((void *)&p->Demand[i],0,sizeof(p->Demand[i]),(void *)&p->Demand[i],sizeof(p->Demand[i]));
      }
    }
  }

  
  if(Check_Demand_Data((S_Demand *)p)==0)
  {
    ASSERT(A_WARNING,0);
    mem_set(p,0,sizeof(Cur_Demand),p,sizeof(Pub_Buf0));
  }
  
  DIS_PD_INT;//����Cur_Demand����ǰ�ص����ж�
  mem_cpy((void *)&Cur_Demand,p,sizeof(Cur_Demand),(void *)&Cur_Demand,sizeof(Cur_Demand));
  INIT_STRUCT_VAR(Cur_Demand);
  SET_DATA_READY_FLAG(Cur_Demand);
  SET_STRUCT_SUM(Cur_Demand);
  EN_PD_INT;
  
  OS_Sem_Post(PUB_BUF0_SEM_ID);  
  //SET_STRUCT_SUM(Cur_Demand); 
  //���µ�ǰ�洢���ͱ��ݴ洢����������������Ҫ�õ��������������Ҫ��֤�������������ݸ���
  Save_Cur_Demand_Data();
  Save_Cur_Demand_Bak_Data();
}

/*
//������ʷ����ʱ�������Ӧ�ô洢��DIλ��
//Flag==
INT8U Calc_HIS_Data_Time_Index(INT8U Flag,S_HEX_Time *pTime)
{
  INT8U Index;
  //����ʱ�����ݲ����ڵ�ǰʱ��֮ǰHIS_ENERGY_DATA_MONTHS
  if((INT16U)(Cur_Time0.Time[T_YEAR])*12+Cur_Time0.Time[T_MONTH]>\
     (INT16U)(pTime->Time[T_YEAR])*12+pTime->Time[T_MONTH]+HIS_ENERGY_DATA_MONTHS)
  {
    return NULL_1BYTES;
  }
  //��ʱ���ڵ��¶���ʱ��֮��
  if(pTime->Time[T_DATE]>=Data_Freeze_Time.DDHH[1] ||\
     (pTime->Time[T_DATE]==Data_Freeze_Time.DDHH[1] && pTime->Time[T_HOUR]>=Data_Freeze_Time.DDHH[0]))
  {
    Index=((INT16U)(pTime->Time[T_DATE])*12+pTime->Time[T_MONTH]) %HIS_ENERGY_DATA_MONTH;
  }
  else
  {
    Index=((INT16U)(pTime->Time[T_DATE])*12+pTime->Time[T_MONTH])%HIS_ENERGY_DATA_MONTH;
  }
  return Index;

}
*/

//��ȡpSrcʱ�������һ������ʱ��,����pSrc������ָ���ʱ���
//��>=pSrcָ��ʱ������һ������ʱ���
void Get_Next_Freeze_Time(S_HEX_Time *pSrc,S_HEX_Time *pDst)
{
  S_HEX_Time TempTime;

  Get_NowMonth_Freeze_Time(pSrc,&TempTime);//��ȡ���¶���ʱ��
  if(Cmp_Time(pSrc,&TempTime)==TIME_AFT)
  {
    Time_Inc(&TempTime,1,UNIT_MON,pDst);
  }
  else
    mem_cpy(pDst,&TempTime,sizeof(TempTime),pDst,sizeof(S_HEX_Time));
}

//��ȡpSrcʱ�����ʱ���֮ǰ�����һ������ʱ���,����pSrc������ָ���ʱ���
//��<=pSrcָ��ʱ������һ������ʱ���ʱ���
void Get_Last_Freeze_Time(S_HEX_Time *pSrc,S_HEX_Time *pDst)
{
  S_HEX_Time TempTime;

  Get_NowMonth_Freeze_Time(pSrc,&TempTime);//��ȡ���¶���ʱ��
  if(Cmp_Time(pSrc,&TempTime)==TIME_BEF)
  {
    Time_Dec(&TempTime,1,UNIT_MON,pDst);
  }
  else
    mem_cpy(pDst,&TempTime,sizeof(TempTime),pDst,sizeof(S_HEX_Time));
}

//��ȡpSrc��ָ���ʱ��ĵ��µĶ���ʱ���,����ָ��Ȼ��
void Get_NowMonth_Freeze_Time(S_HEX_Time *pSrc,S_HEX_Time *pDst)
{
  INT8U Re;

  Re=1;
  Re=Check_STRUCT_Sum(pSrc,sizeof(S_HEX_Time),pSrc->CS,sizeof(pSrc->CS));
  ASSERT(A_WARNING,1==Re);
  mem_cpy(pDst->Time,pSrc->Time,sizeof(pSrc->Time),pDst->Time,sizeof(pDst->Time));
  pDst->Time[T_HOUR]=Data_Freeze_Time.DDHH[0];
  pDst->Time[T_DATE]=Data_Freeze_Time.DDHH[1];
  pDst->Time[T_MIN]=0;
  Set_STRUCT_Sum(pDst,sizeof(S_HEX_Time),pDst->CS,sizeof(pDst->CS));
}

//����ĳ���������ݵ�ʱ����
void Set_One_Demand_Time(S_One_Demand *pSrc,S_HEX_Time *pTime)
{
  mem_cpy(&(pSrc->Time),pTime,sizeof(S_HEX_Time),&(pSrc->Time),sizeof(pSrc->Time));
  Set_STRUCT_Sum(pSrc,sizeof(S_One_Demand),pSrc->CS,sizeof(pSrc->CS));
}

//����������Ҫ�Ǵ�CUR_DEMAND�洢������CUR_DEMAND_BAK�洢����������,Ȼ����������ݶ���
//���ϵ粹�����߿�Խ����ʱ���Ե��øú���������ע�⣺
//pTime��ʾ����ʱ��ʱ��,һ��Ϊ��ǰʱ��
//�������������Ͼ�ͣ���ˣ���ô���ϵ�����ڶ���ʱ�̣����������Ļ��������Ѿ��ж��������ˣ��㲻���ٶ���
void Freeze_Demand_Data(S_HEX_Time *pTime)//S_HEX_Time *pTime)
{
  INT8U i,Re,Err;
  S_One_Demand *p;
  S_HEX_Time TempTime;//,TempTime1;
  INT32U Off;

  DEBUG_PRINT(HUCK,DEBUG_0,"----------Freeze Demand Data %d-%d-%d %d:%d----------",\
                           pTime->Time[T_YEAR],pTime->Time[T_MONTH],pTime->Time[T_DATE],pTime->Time[T_HOUR],pTime->Time[T_MIN]);
  
  Re=CHECK_STRUCT_SUM(Cur_Demand);
  if(ASSERT(A_WARNING,1==Re))
    Check_Data_Avail();
  
  OS_Sem_Pend(PUB_BUF0_SEM_ID);//����Pub_Buf�ź���
  //�ֱ��ȡÿ���ݷ��ʵ����ݣ�������ת�浽��Ӧ����ʷ������
  for(i=0;i<=Multi_Rate_Para.Rates && i<=MAX_RATES;i++)
  {
    //pָ��÷��ʵ���������
    //��ǰ������Cur_Demand�е��������
    if(i==0 || i==Cur_Demand.Rate)
    {
      if(i==0)
       p=(S_One_Demand *)&Cur_Demand.Demand[0];
      else if(i==Cur_Demand.Rate)
       p=(S_One_Demand *)&Cur_Demand.Demand[1];
      
      Re=1;
    }
    else if(Read_Demand_Rate_Data(i,(INT8U *)Pub_Buf0,(INT8U *)Pub_Buf0,sizeof(Pub_Buf0))==ONE_DEMAND_SAVE_SIZE)
    {
      p=(S_One_Demand *)Pub_Buf0; 
      Re=1;
    }
    else
      Re=0;
    
    if(1==Re)//�õ�����ȷ��ԭʼ���ݲŽ��ж���
    {
      DEBUG_PRINT(HUCK,DEBUG_0,"Demand Data Rate %u Freeze, Data Time: ",i);
      Debug_Print_HEX_Time((p->Time).Time);
      //���ҵ�pTime֮ǰ���ϴν����ʱ���(����pTime����)
      if(((p->Time).Time[T_YEAR]==0 && (p->Time).Time[T_MONTH]==0) ||\
          Check_HEX_Time(&(p->Time))!=1)//���뱣֤ʱ���ʽ��ȷ�Ž��в���,��Ϊ����Ҳ������ȫ0������,����Ĭ�ϲ���������0��
      {
        DEBUG_PRINT(HUCK,DEBUG_0,"Demand Rate %u Time EQ Zero or format error",i);
        continue;
      }
      //<=pTime�����һ������ʱ���,pTime���ܾ��Ƕ���ʱ���
      Get_Last_Freeze_Time(pTime,&TempTime);//pTime��ǰ�����һ������ʱ���,����pTime����
      
      //����TempTime�������һ�εĶ���ʱ���,p->Time���������ݵ�ʱ���
      Re=Cmp_Time(&(p->Time),&TempTime);//�Ƚ���������ʱ��������һ�ζ���ʱ���
      if(TIME_AFT==Re)//����ʱ��������һ�ν���ʱ���֮����һ����ǰ���ݣ�����Ҫ���浽��ʷ������,ʱ�����Ҳ�п�����Ҫ���棬��Ϊ��������ʱ����������ǽ���ʱ���
      {
        DEBUG_PRINT(HUCK,DEBUG_0,"Demand Rate %u Time > FreezeTime",i);
        Debug_Print_HEX_Time((p->Time).Time);
        Debug_Print_HEX_Time(TempTime.Time);
        continue;
      }
        //>=p->Time�����һ������ʱ���,���ܾ���p->Time,��Ϊp->Time���ܾ��ǵ�ǰʱ��,ͬʱ��ǰʱ����Ƕ���ʱ���
      Get_Next_Freeze_Time(&(p->Time),&TempTime);//��ʷ���ݵĶ���ʱ���,����������Ҫ�ҵ���ʱ��֮���һ������ʱ���
      //����µ�������ʵ������Ƿ񶳽��?û�ж�����Ŷ���
      if(Read_Demand_HIS_Data(i,&TempTime,(INT8U *)Pub_Buf0+sizeof(S_Demand),(INT8U *)Pub_Buf0,sizeof(Pub_Buf0),&Err) EQ ONE_DEMAND_SAVE_SIZE)
      {
        DEBUG_PRINT(HUCK,DEBUG_0,"Demand Rate %u Time Data Freezed!",i);
        Debug_Print_HEX_Time(TempTime.Time);        
        //continue;
      } 
      else
      {
        mem_cpy(p->Time.Time,&TempTime,sizeof(TempTime),p,sizeof(S_One_Demand));
        Set_STRUCT_Sum(p,sizeof(S_One_Demand),p->CS,sizeof(p->CS));
        Write_Demand_HIS_Data(i,&TempTime,p,ONE_DEMAND_SAVE_SIZE);
      }
      //��Ϊ����ʷ���ݣ�������Ҫ���ñ�Ϊ��������
      //��Ҫ���ñ��µ�������ֵ�Լ���������ʱ��
      mem_set(p,0,sizeof(S_One_Demand),p,sizeof(S_One_Demand));//������ȫ����0���뵱ǰ�洢�����´ζ���ȫ0���ݣ���ʾ��δ����������
      Set_STRUCT_Sum(p,sizeof(S_One_Demand),p->CS,sizeof(p->CS));
      //ȷ����ǰ������ʱ��㲻���Ƕ���ʱ���
      //ȷ������Ϊ0

      //����д�뵱ǰ�����洢������������
      Off=DEMAND_RATE_OFF(i);
      Write_Storage_Data_Fix_Len(CUR_DEMAND,Off,p,ONE_DEMAND_SAVE_SIZE);
      Write_Storage_Data_Fix_Len(CUR_DEMAND_BAK,Off,p,ONE_DEMAND_SAVE_SIZE);
      
      Demand_Accu_Clear();
      //���޸ĺ��Cur_Demand���ݱ��浽����������
      if(i==0 || i==Cur_Demand.Rate)
      {
        SET_STRUCT_SUM(Cur_Demand);
        Save_Cur_Demand_PD_Data();
      }
    }
  }
  OS_Sem_Post(PUB_BUF0_SEM_ID);//�ͷ�Pub_Buf�ź���
  DEBUG_PRINT(HUCK,DEBUG_0,"----------Freeze Demand Data End----------");
}

//������鵱ǰ�����Ƿ����˱仯������仯�ˣ��������ǰ���ʵ��������ֵ
void Demand_Check_Rate_Change()
{
  INT8U Re;

  Re=1;
  Re=CHECK_STRUCT_SUM(Cur_Rate_Info);
  Re=CHECK_STRUCT_SUM(Cur_Demand);
  if(ASSERT(A_WARNING,1==Re))
    Check_Data_Avail();

  if(Cur_Rate_Info.Rate!=Cur_Demand.Rate)//�����Ѿ������仯��
  {
    DEBUG_PRINT(HUCK,DEBUG_0,"Rate_Changed!Save Old Rate Demand && Read New Rate Demand");
    Save_Cur_Demand_Data();//�Ƚ�Cur_Demand���ݱ�������
    Save_Cur_Demand_Bak_Data();

    //���¸��ݵ�ǰ���ʶ�ȡ��������
    Cur_Demand.Rate=Cur_Rate_Info.Rate;
    //�����÷ַ�������
    if(Read_Demand_Rate_Data(Cur_Demand.Rate,(void *)&Cur_Demand.Demand[1],(void *)&Cur_Demand.Demand[1],sizeof(S_One_Demand))!=ONE_DEMAND_SAVE_SIZE)
    {
      mem_set((void *)&Cur_Demand.Demand[1],0,sizeof(Cur_Demand.Demand[1]),(void *)&Cur_Demand.Demand[1],sizeof(Cur_Demand.Demand[1]));
      SET_STRUCT_SUM(Cur_Demand.Demand[1]);
    }
    SET_STRUCT_SUM(Cur_Demand);
    
    Save_Cur_Demand_PD_Data();//���µ���洢������������
  }
}

//��鵱ǰ�������ݵ���Ч��
void Check_Demand_Data_Avail()
{
  INT8U Re;

  Re=Check_Demand_Data((S_Demand *)&Cur_Demand);
  if(ASSERT(A_WARNING,1==Re))//����������ݵ�У��ͣ�У��ʹ��������´�ROM�ж�ȡ
  {
    Read_Demand_Data_From_Rom();
  }
  
  Re=CHECK_STRUCT_SUM(Demand_Accu);
  if(ASSERT(WARNING,1==Re))
  {
     mem_set((void *)&Demand_Accu,0,sizeof(Demand_Accu),(void *)&Demand_Accu,sizeof(Demand_Accu));
     SET_STRUCT_SUM(Demand_Accu);
  }
}

//������������䷢��ʱ��,������ֻ�嵱������
void Clear_Cur_Demand_Data()
{
  if(Check_Clear_Data_Authority()==0)
    return;

  if(CLEAR_DEMAND_FLAG!=Check_Clear_Data_Flag())
    return;
  DEBUG_PRINT(HUCK,DEBUG_0,"Clear_Cur_Demand_Data!!!");  
  Set_Def_Cur_Demand_Data();
  Clear_Demand_Record();//��������¼
  /*
  INT8U i,Re;
  INT32U Off;
  //S_HEX_Time TempTime;
  
  DEBUG_PRINT(HUCK,DEBUG_0,"Clear_Demand_Data!!!");
  //������

  //�����״̬���û�Ȩ��״̬
  if(Check_Meter_Prog_Status()==0 ||\
     CHECK_STRUCT_SUM(User_Authority_Flag)==0 ||\
     User_Authority_Flag.Flag!=AUTHORITY_FLAG)
    return;
  
  //��������־
  if(CLEAR_DEMAND_FLAG!=Check_Clear_Data_Flag())
    return;

  //������������0��������������ʱ��Ϊ�´ζ���ʱ��
  mem_set((void *)&Cur_Demand,0,sizeof(Cur_Demand),(void *)&Cur_Demand,sizeof(Cur_Demand));

  Re=CHECK_STRUCT_SUM(Cur_Rate_Info);//����Ҫ�õ���ǰ����
  if(ASSERT(A_WARNING,1==Re))
    Check_Data_Avail();

  Cur_Demand.Rate=Cur_Rate_Info.Rate;//���õ�ǰ��������
  SET_STRUCT_SUM(Cur_Demand);
  
  //�����״̬���û�Ȩ��״̬
  if(Check_Meter_Prog_Status()==0 ||\
     CHECK_STRUCT_SUM(User_Authority_Flag)==0 ||\
     User_Authority_Flag.Flag!=AUTHORITY_FLAG)
    return;
  
  //��������־
  if(CLEAR_DEMAND_FLAG!=Check_Clear_Data_Flag())
    return;
  //�ȱ������洢������
  Write_Storage_Data(CUR_DEMAND_PD,(void *)(&Cur_Demand),sizeof(Cur_Demand));
  //�ٱ����������ͱ�������������,�������ͱ�����������ʽ��һ��,��Ҫ��ÿ�����ʶ����洢
  for(i=0;i<MAX_RATES;i++)
  {
    Off=DEMAND_RATE_OFF(i);
    Write_Storage_Data_Fix_Len(CUR_DEMAND,Off,(void *)(&Cur_Demand.Demand[0]),ONE_DEMAND_SAVE_SIZE);
    Write_Storage_Data_Fix_Len(CUR_DEMAND_BAK,Off,(void *)(&Cur_Demand.Demand[0]),ONE_DEMAND_SAVE_SIZE);
    OS_TimeDly_Ms(20);
  }
  */
}

//�嵱ǰ������¼����
void Clear_Demand_Record()
{
  INT8U Re;
  
  Re=CHECK_STRUCT_SUM(Clr_Demand_Record);
  if(0==Re)
  {
    ASSERT(A_WARNING,0);
    mem_set((void *)(&Clr_Demand_Record),0,sizeof(Clr_Demand_Record),(void *)(&Clr_Demand_Record),sizeof(Clr_Demand_Record));
    SET_STRUCT_SUM(Clr_Demand_Record);
  }
  
  Clr_Demand_Record.Time[0]=Cur_Time1.Min;
  Clr_Demand_Record.Time[1]=Cur_Time1.Hour;
  Clr_Demand_Record.Time[2]=Cur_Time1.Date;
  Clr_Demand_Record.Time[3]=Cur_Time1.Month;
  Clr_Demand_Record.Counts++;
  SET_STRUCT_SUM(Clr_Demand_Record);
  Write_Storage_Data(CLR_DEMAND_RECORD,(void *)&Clr_Demand_Record,sizeof(Clr_Demand_Record));
}

//�ֶ��������ļ��ִ��
void Check_Man_Clr_Demand()
{
  static S_Int8U Mins = {CHK_BYTE,0x00,CHK_BYTE};
  static S_Int8U Min_Bak = {CHK_BYTE,0x00,CHK_BYTE};
  INT8U Re;
  
  Re = CHECK_STRUCT_VAR(Mins);
  ASSERT(A_WARNING,1==Re);
 
  if(Mins.Var == 0)
  {
    if(Check_Man_ClrDemd_En())//�ֶ�������
    {
      Mins.Var ++; 
      Set_Event_Instant(ID_EVENT_CLR_DEMAND_MAN);//�ֶ��������¼�
      Wait_Event_Data_Proc_End(ID_EVENT_CLR_DEMAND_MAN);//�ȴ��¼��������
      
      DEBUG_PRINT(HUCK,DEBUG_0,"Man_Clear_Cur_Demand_Data!!!");  
      Set_Def_Cur_Demand_Data();
      Clear_Demand_Record();//��������¼      
    }
  }
  else
  {
    if(Min_Bak.Var == Cur_Time0.Time[T_MIN])//ÿ���ӽ���һ��
       return;
       
    Min_Bak.Var = Cur_Time0.Time[T_MIN];
       
    Mins.Var ++;
    if(Mins.Var > Demand_Para.Period)
      Mins.Var = 0;
  }
}

//�����е���������,�������º�ǰHIS_ENERGY_DATA_MONTHS����
void Clear_All_Demand_Data()
{
  if(Check_Clear_Data_Authority()==0)
    return;
  
  DEBUG_PRINT(HUCK,DEBUG_0,"Clear_All_Demand_Data!!!"); 
  if(CLEAR_DEMAND_FLAG!=Check_Clear_Data_Flag() &&
     CLEAR_ALL_FLAG!=Check_Clear_Data_Flag())
    return;
  Set_Def_Demand_Data();
  /*
  INT8U i,j;
  INT8U Re;
  INT32U Off;
  
  //��ǰ0-HIS_ENERGY_DATA_MONTHS�µ�����ȫ����0
  //�����״̬���û�Ȩ��״̬
  if(Check_Meter_Prog_Status()==0 ||\
     CHECK_STRUCT_SUM(User_Authority_Flag)==0 ||\
     User_Authority_Flag.Flag!=AUTHORITY_FLAG)
    return;
  
  //��������־

  
  Re=1;
  Re&=CHECK_STRUCT_SUM(User_Authority_Flag);
  Re&=CHECK_STRUCT_SUM(Clear_Flag);
  if(ASSERT(A_WARNING,1==Re))
    Check_Data_Avail();

  mem_set((void *)&Cur_Demand,0,sizeof(Cur_Demand),(void *)&Cur_Demand,sizeof(Cur_Demand));
  //��ǰ0-HIS_ENERGY_DATA_MONTHS�µ�����
  for(i=0;i<=HIS_DEMAND_DATA_MONTHS;i++)
  {
    //DEBUG_PRINT(HUCK,DEBUG_0,"Clear Freeze Demand Data,Time:%d-%d-%d %d:%d",Time.Time[T_YEAR],Time.Time[T_MONTH],Time.Time[T_DATE],Time.Time[T_HOUR],Time.Time[T_MIN]);
    //�ϸ��жϣ���ֹ�������ܵ�����
    if(Check_Meter_Prog_Status()==0 || 1!=Re ||\
       AUTHORITY_FLAG!=User_Authority_Flag.Flag ||\
       CLEAR_DEMAND_FLAG!=Clear_Flag.Flag)
      return;

      for(j=0;j<MAX_RATES;j++)
      {
        Off=DEMAND_RATE_OFF(i);//ֱ��д��ʷ���ݴ洢������
        Write_Storage_Data_Fix_Len(HIS_DEMAND+i,Off,(void *)&Cur_Demand.Demand[0],ONE_DEMAND_SAVE_SIZE);
      }
  }
  Clear_Demand_Data();//���嵱������
  */
}

//�ϵ粹����������
void PowerOn_Demand_Data_Freeze()
{
  Freeze_Demand_Data((S_HEX_Time *)&Cur_Time0);
}

//����洢��������
void PowerDown_Save_Demand_Data()
{
  Save_Cur_Demand_PD_Data();
}

//��ӡʱ��
void Debug_Print_Time(INT8U Time[])
{
  INT8U i;
  
  if(Check_Debug_En()==0)//�ǵ���״̬����ӡ
    return;
  
  OS_Debug_Print("  ");
  for(i=0;i<5;i++)
  {
    if(Time[4-i]<10)
      OS_Debug_Print("0");
    
    OS_Debug_Print("%x",Time[4-i]);
    if(i==0 || i==1)
      OS_Debug_Print("-");
    else if(i==2)
      OS_Debug_Print(" ");
    else if(i==3)
      OS_Debug_Print(":");
  }
  //OS_Debug_Print(" "); 
}

//��ӡʱ��
void Debug_Print_HEX_Time(INT8U Time[])
{
  INT8U i;
  
  if(Check_Debug_En()==0)//�ǵ���״̬����ӡ
    return;
  
  OS_Debug_Print("  ");
  for(i=0;i<5;i++)
  {
    if(Time[4-i]<10)
      OS_Debug_Print("0");
    
    OS_Debug_Print("%d",Time[4-i]);
    if(i==0 || i==1)
      OS_Debug_Print("-");
    else if(i==2)
      OS_Debug_Print(" ");
    else if(i==3)
      OS_Debug_Print(":");
  }
  //OS_Debug_Print(" "); 
}

//�����ǰ������Ϣ
void Debug_Print_Cur_Demand_Info()
{
  static S_Int8U Min={CHK_BYTE,0,CHK_BYTE};
  static S_Int8U Counts={CHK_BYTE,0,CHK_BYTE};
  INT8U i,Rate,Re;

  if(Check_Debug_En()==0)//�ǹ���״̬����ӡ
    return;
  
  if(Cur_Time0.Time[T_MIN]==Min.Var)//ÿ����ִ��һ�θú���
    return;
  
  Re=CHECK_STRUCT_VAR(Min);
  ASSERT(A_WARNING,1==Re);
  Re=CHECK_STRUCT_VAR(Counts);
  ASSERT(A_WARNING,1==Re);
  
  Min.Var=Cur_Time0.Time[T_MIN];
  Counts.Var++;
  if(Counts.Var>=5)//ÿ��5���Ӵ�ӡһ�ε�ǰ����ֵ
  {
    Counts.Var=0;
    
    Clr_Ext_Inter_Dog();
      DEBUG_PRINT(HUCK,DEBUG_1,"|-----------------------------Max_Demand-------------------------------|"); 
      DEBUG_PRINT(HUCK,DEBUG_1,"| Rate Pos_Act Neg_Act Pos_Rea Neg_Rea Quad0_R Quad1_R Quad2_R Quad3_R |");
    for(i=0;i<2;i++)
    {
      if(i==0)
        Rate=0;
      else
        Rate=Cur_Demand.Rate;
      
      DEBUG_PRINT(HUCK,DEBUG_1,"|   %2d %7ld %7ld %7ld %7ld %7ld %7ld %7ld %7ld |",\
        Rate,Cur_Demand.Demand[i].Pos_Active,Cur_Demand.Demand[i].Neg_Active,Cur_Demand.Demand[i].Pos_Reactive,Cur_Demand.Demand[i].Neg_Reactive,\
        Cur_Demand.Demand[i].Quad_Reactive[0],Cur_Demand.Demand[i].Quad_Reactive[1],Cur_Demand.Demand[i].Quad_Reactive[2],Cur_Demand.Demand[i].Quad_Reactive[3]);
    }
      DEBUG_PRINT(HUCK,DEBUG_1,"|----------------------------------------------------------------------|");
    
    OS_TimeDly_Ms(50);
    Clr_Ext_Inter_Dog();
      DEBUG_PRINT(HUCK,DEBUG_1,"|----------------------------Demand_Time-------------------------------|"); 
      DEBUG_PRINT(HUCK,DEBUG_1,"| Rate      Pos_Active      Neg_Active      Pos_Reacti      Neg_Reacti |");
    
    for(i=0;i<2;i++)
    {
      if(i==0)
        Rate=0;
      else
        Rate=Cur_Demand.Rate;
      
      DEBUG_PRINT(HUCK,DEBUG_1,"|   %2d",Rate);
      Debug_Print_Time((INT8U *)Cur_Demand.Demand[i].Pos_Active_Time);
      Debug_Print_Time((INT8U *)Cur_Demand.Demand[i].Neg_Active_Time);
      Debug_Print_Time((INT8U *)Cur_Demand.Demand[i].Pos_Reactive_Time);
      Debug_Print_Time((INT8U *)Cur_Demand.Demand[i].Neg_Reactive_Time);
      OS_Debug_Print(" |"); 
    }
    DEBUG_PRINT(HUCK,DEBUG_1,"|----------------------------------------------------------------------|");
    
    //��ʱû���������޹�
    /*
    Clr_Ext_Inter_Dog();
    //DEBUG_PRINT(HUCK,DEBUG_1,"|-------------------------------Demand_Time_0--------------------------|"); 
    DEBUG_PRINT(HUCK,DEBUG_1,"| Rate     Quad0_Reati     Quad1_Reati     Quad2_Reati     Quad3_Reati |");
    
    for(i=0;i<2;i++)
    {
      if(i==0)
        Rate=0;
      else
        Rate=Cur_Demand.Rate;
      
      DEBUG_PRINT(HUCK,DEBUG_1,"|   %2d",Rate);
      Debug_Print_Time((INT8U *)Cur_Demand.Demand[i].Quad_Reactive_Time[0]);
      Debug_Print_Time((INT8U *)Cur_Demand.Demand[i].Quad_Reactive_Time[1]);
      Debug_Print_Time((INT8U *)Cur_Demand.Demand[i].Quad_Reactive_Time[2]);
      Debug_Print_Time((INT8U *)Cur_Demand.Demand[i].Quad_Reactive_Time[3]);
      OS_Debug_Print(" |"); 
    }
      DEBUG_PRINT(HUCK,DEBUG_1,"|----------------------------------------------------------------------|");
    */
  } 
}

#undef DEMAND_C
