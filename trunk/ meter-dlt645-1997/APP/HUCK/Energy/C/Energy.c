#define ENERGY_C
#include "Includes.h"

volatile MEASU_ENERG Cumu_Energy;
extern void Event_Energy_Cumu(MEASU_ENERG *pEnergy);

//�����ڴ��Ƿ�����磬��������POWER_ON���򷵻�RESET
//��鵱ǰ���ϵ绹�Ǹ�λ,ʵ���ϸú������ж��ڴ��е������ڸ�λ���Ƿ��б仯�����Ƿ����˵���֮��
//�ϵ緵��POWER_ON,��λ����RESET
//�ú������Power_On_Flag.Flag[]�ǲ���ÿ������0x55
INT8U Check_Rst_Flag()
{
  INT8U i,Re;

  static S_Int8U Flag={CHK_BYTE,0x55,CHK_BYTE};//0x55��ʾ��һ�ν���ú���,0xAA��ʾ���ǵ�һ�ν���,����ֵ��ʾ����,��¼�Ƿ����ϵ���һ�ν���ú���
  static S_Int8U Power_Flag={CHK_BYTE,SOFT_RST,CHK_BYTE};//��λ���ϵ��־
  
  Re=CHECK_STRUCT_VAR(Flag);
  ASSERT(A_WARNING,1==Re);
  
  if(0x55==Flag.Var)//��һ�ν���ú���
  {
    Flag.Var=0xAA;//��0xAA���Ժ��ٵ��øú����Ͳ����ٽ����������
    Power_Flag.Var=SOFT_RST;//Ĭ���Ǹ�λ
    for(i=0;i<S_NUM(Power_On_Flag.Flag);i++)
    {
      if(Power_On_Flag.Flag[i]!=0x55)//��һ������0x55˵�����ϵ�
      {
        Power_Flag.Var=POWER_ON_RST;
        break;
      }
    }
    //Power_Flag==RESET����Power_On_Flag��У�����ȷ,��Ϊ����λ
    if(Power_Flag.Var==SOFT_RST && CHECK_STRUCT_SUM(Power_On_Flag))
      Power_Flag.Var=SOFT_RST;
    else
      Power_Flag.Var=POWER_ON_RST;
    
    //Power_On_Flag.Flag���ó�0x55���´θ�λ���ϵ�ɲ鿴�ñ�־
    mem_set((void *)Power_On_Flag.Flag,0x55,sizeof(Power_On_Flag.Flag),(void *)Power_On_Flag.Flag,sizeof(Power_On_Flag.Flag));
    SET_STRUCT_SUM(Power_On_Flag);
    
    return Power_Flag.Var; 
  }
  else if(0xAA==Flag.Var)
  {
    Re=CHECK_STRUCT_VAR(Power_Flag);
    ASSERT(A_WARNING,1==Re);
    
    if(Power_Flag.Var==SOFT_RST || Power_Flag.Var==POWER_ON_RST)
      return Power_Flag.Var;
    else
    {
      ASSERT(A_WARNING,0);
      return POWER_ON_RST;
    }
  }
  else
  {
    ASSERT(A_WARNING,0);
    return POWER_ON_RST;
  }
}

//��ȡBCDʱ��
//Dst[0]��
//Dst[1]ʱ
//Dst[2]��
//Dst[3]��
//Dst[4]��
void Get_BCD_Time(S_BCD_Time *pSrc,INT8U Dst[],INT8U Dst_Start[],INT8U DstLen)
{
  ASSERT(A_WARNING,Dst>=Dst_Start && Dst+5<=Dst_Start+DstLen);
  
  Dst[T_MIN]=pSrc->Min;
  Dst[T_HOUR]=pSrc->Hour;
  Dst[T_DATE]=pSrc->Date;
  Dst[T_MONTH]=pSrc->Month;
  Dst[T_YEAR]=pSrc->Year;  
}

//�����������ĺϷ���
void Check_Energy_Para_Avil()
{
  INT8U Re;
  
  Re=1;
  Re&=CHECK_STRUCT_SUM(Mode_Word);
  Re&=CHECK_STRUCT_SUM(Rate_Status);
  Re&=CHECK_STRUCT_SUM(Rate_Scheme_Switch_Time);
  Re&=CHECK_STRUCT_SUM(Multi_Rate_Para);
  Re&=CHECK_STRUCT_SUM(Year_Table);
  Re&=CHECK_STRUCT_SUM(Date_Table);
  Re&=CHECK_STRUCT_SUM(Data_Freeze_Time);
  Re&=CHECK_STRUCT_SUM(Cur_Rate_Info);

  if(ASSERT(A_WARNING,1==Re))
    Read_Energy_Para_From_Rom();//���¶�ȡ��������!!
}

//�����в�ѯ��Ҫ���ݵ�У��Ͳ���ʱ�����ô˺���
void Check_Data_Avail()
{
  if(Get_Cur_Task_ID()!=0)//���������²��������ݼ��!
  {  
    Chk_Data_Flag.Chk_Flag=1;//֪ͨ���������һ�����ݼ�����
  
    OS_Waitfor_Sec(Chk_Data_Flag.Chk_Flag==0,5);
    if(Chk_Data_Flag.Chk_Flag==1)
    {
      ASSERT(A_WARNING,0);
      OS_Waitfor(Chk_Data_Flag.Chk_Flag==0);
    }
  }
}
//��������������������
void Main_Chk_Data_Avail()
{
  if(Chk_Data_Flag.Chk_Flag==1)
  {
    Check_Energy_Demand_Task_Data_Avail();
    Chk_Data_Flag.Chk_Flag=0; 
  }
}

//����������ݵĿ�����
void Check_Energy_Demand_Task_Data_Avail()
{
  INT8U Re;
  static S_Int8U Flag={CHK_BYTE,0,CHK_BYTE};
  
  Re=CHECK_STRUCT_VAR(Flag);
  ASSERT(A_WARNING,1==Re);
  
  if(Flag.Var==1)//��ֹ����ĺ��������ڵ���Check_Data_Avail(),�Ӷ�����Ƕ��
    return;
  
  Flag.Var=1;
  //����ĺ�����ò�Ҫ�ٱ�������е��ã���ֹ����Ƕ�׵���
  ASSERT(A_WARNING,PD_INT_EN_Flag==1);
  ASSERT(A_WARNING,CHECK_STRUCT_VAR(Assert_Info));
  
  Check_Energy_Data_Avail();//��鵱ǰ�������������Ƿ�Ϸ�
  //OS_TimeDly_Ms(20);
  Check_Energy_Para_Avil();//��������ز����Ƿ�Ϸ�
  //OS_TimeDly_Ms(20);
  Check_Demand_Data_Avail();//������������Ƿ�Ϸ�
  OS_TimeDly_Ms(20);
  Check_Demand_Para_Avail();//������������Ƿ�Ϸ�
  //OS_TimeDly_Ms(20);
  Check_Clock_Data_Avail();//���ʱ�������Ƿ���Ч
  //OS_TimeDly_Ms(20);
  Check_LoadData_Index_Avail();//��鸺������������Ϣ�Ƿ�Ϸ�
  OS_TimeDly_Ms(20);
  Check_LoadData_Para_Avail();//��鸺�����߲����Ƿ�Ϸ�
  //OS_TimeDly_Ms(20);
  Check_Power_Ctrl_Para_Avail();//��鸺�ɿ�����ز����Ƿ���ȷ
  //OS_TimeDly_Ms(20);
  Check_Sys_Status_Avail();//��鵱ǰϵͳ״̬�Ƿ�Ϸ�
  OS_TimeDly_Ms(20);
  Check_Pub_Var_Avail();//���ȫ��buf���߱������Ƿ�Ϸ�
  //OS_TimeDly_Ms(20);
  Check_Event_Cumu_Avail();//����¼��ۼ������Ƿ���ȷ
  //OS_TimeDly_Ms(20);
  Check_Data_Trans_Data_Avail();//���Э�鴫����������Ƿ���ȷ
  OS_TimeDly_Ms(20);
  Check_Low_Power_Data_Avail();//���͹�����ر����Ƿ���ȷ
  //OS_TimeDly_Ms(20);
  Check_VolStat_Para_Avail();//����ѹͳ�Ʋ����ĺϷ���
  //OS_TimeDly_Ms(20);
  Check_VolStat_Data_Avail();//����ѹͳ�����ݵĺϷ���
  Flag.Var=0;
  return;
}

//��ROM�ռ��ж�ȡģʽ��
void Read_Mode_Word()
{
  INT8U i,Err;
  INT16U Len;
  PROTO_DI DI=0xC047;
  
  //��ȡģʽ��1-8
  for(i=0;i<8;i++)
  {
    //�����ȡģʽ��ʧ���������Ĭ�ϵ�ģʽ��
    Len=Read_Storage_Data(DI+i,(INT8U *)&Mode_Word.Mode[i],(INT8U *)&Mode_Word.Mode[i],1,&Err);
    ASSERT(A_WARNING,1==Len && NO_ERR==Err);
  }
  //ģʽ��9��δ��
/*  
  //��ȡģʽ��9
  Len=Read_Storage_Data(0xCA1A,(INT8U *)&Mode_Word.Mode[8],(INT8U *)&Mode_Word.Mode[8],1,&Err);
  ASSERT(A_WARNING,1==Len && NO_ERR==Err);  
*/
  SET_STRUCT_SUM(Mode_Word);

  //��ȡ�ź����������
  //Len=Read_Storage_Data(0xCA12,(INT8U *)&Output_Mode.Mode,(INT8U *)&Output_Mode.Mode,1,&Err);
  //ASSERT(A_WARNING,1==Len && NO_ERR==Err); 
  
  //Output_Mode.Mode=(Output_Mode.Mode & 0x03);//4��1�ź����ģʽ��ֻ�������λ������
  //SET_STRUCT_SUM(Output_Mode);
}

//��ȡ��ǰ���ʷ���,
//����RATE_SCHEME0��ʾʹ�������ʷ���,����RATE_SCHEME1��ʾ��ǰʹ�ø����ʷ���
INT8U Get_Using_Rate_Scheme()
{
  INT8U Re;
  
  Re=CHECK_STRUCT_SUM(Rate_Status);
  //������״̬��У���   
  if(ASSERT(A_WARNING,0!=Re))
    Check_Data_Avail();
  //���ʷ�����Ĭ��Ϊ����0
  if(ASSERT(A_WARNING,RATE_SCHEME0==Rate_Status.Status[0].Byte ||\
    RATE_SCHEME1==Rate_Status.Status[0].Byte))
    return RATE_SCHEME0;
  else
    return Rate_Status.Status[0].Byte;
}

//���õ�ǰ���ʷ���
//����ǰ���ʷ�����Ϣ���õ���ǰ����״̬����
void Set_Using_Rate_Scheme(INT8U Rate_Scheme)
{
  INT8U Re;
  
  Re=CHECK_STRUCT_SUM(Rate_Status);
  if(ASSERT(A_WARNING,0!=Re))
    Check_Data_Avail();
  
  if(ASSERT(A_WARNING,RATE_SCHEME0==Rate_Scheme ||\
     RATE_SCHEME1==Rate_Scheme))
    Rate_Status.Status[0].Byte=RATE_SCHEME0;
  else
    Rate_Status.Status[0].Byte=Rate_Scheme;
  
  SET_STRUCT_SUM(Rate_Status);//����У���  
}

//�ӵ�ǰ����״̬���ж�ȡ��ǰ�ķ��ʣ������ǰ���ʲ���Ĭ�Ϸ�Χ���򷵻ط���1
//��Ҫ�����÷���״̬��
INT8U Get_Using_Rate()
{
  INT8U Re;
  
  Re=CHECK_STRUCT_SUM(Rate_Status);
  if(ASSERT(A_WARNING,0!=Re))
    Check_Data_Avail();
  
  if(ASSERT(A_WARNING,Rate_Status.Status[1].Byte<=MAX_RATES &&\
    Rate_Status.Status[1].Byte>=1))
  {
    Rate_Status.Status[1].Byte=1;//�����ǰ���ʴ�Ĭ��ʹ�÷���1
    SET_STRUCT_SUM(Rate_Status);
    return 1;
  }
  else
    return Rate_Status.Status[1].Byte;  
}

//���õ�ǰ����ΪRate,��Ҫ�����÷���״̬��
void Set_Using_Rate(INT8U Rate)
{
  INT8U Re;
  
  Re=CHECK_STRUCT_SUM(Rate_Status);
  ASSERT(A_WARNING,0!=Re);
  if(ASSERT(A_WARNING,Rate>=1 && Rate<=MAX_RATES))
    Rate_Status.Status[1].Byte=1;
  else
    Rate_Status.Status[1].Byte=Rate;
  
  SET_STRUCT_SUM(Rate_Status);//����У���  
}

//���㵱ǰӦ��ʹ�õķ��ʷ���,���Flag==CALC_ROM�����´�ROM�ж�ȡ�������㵫ǰ�ķ��ʷ���
//ͬʱ������ʷ����������л��������ڲ������л���صĴ���
// ��ǰӦ�ò��������ʷ����򷵻�RATE_SCHEME0,���򷵻�RATE_SCHEME1
//�ú�������Ҫ�������ж��Ƿ���������л�
//���ʷ����л��Ļ�����Rate_Scheme_Changed_Proc������ش���
INT8U Calc_Cur_Rate_Scheme(INT8U Flag)
{
  INT8U Re,Scheme,Err;
  INT16U Len;
  
  //��ȡ�����׷����л�ʱ��
  if(CALC_ROM==Flag)//��ʾ��ROM�����¶�ȡ������ݣ����м���
  {
    //��ȡģʽ��
    Read_Mode_Word();
    //��ȡ���������л�ʱ��
    Len=Read_Storage_Data(0xCA13,(INT8U *)Rate_Scheme_Switch_Time.Time,(INT8U *)Rate_Scheme_Switch_Time.Time,sizeof(Rate_Scheme_Switch_Time.Time),&Err);
    if(ASSERT(A_WARNING,5==Len))
    {
      DEBUG_PRINT(HUCK,DEBUG_0,"Read Rate_Scheme_Switch_Time Error"); 
      //���0xFF����ʹ�õڶ��׷��ʷ���
      mem_set((INT8U *)Rate_Scheme_Switch_Time.Time,0xFF,sizeof(Rate_Scheme_Switch_Time.Time),\
            (INT8U *)Rate_Scheme_Switch_Time.Time,sizeof(Rate_Scheme_Switch_Time.Time));
    }
    if(Check_BCD_Data((INT8U *)Rate_Scheme_Switch_Time.Time,5)==1)//ȷʵ��BCDʱ������,���������ȫFF(Ĭ�ϲ���)
      Bcd2Hex_Buf((INT8U *)Rate_Scheme_Switch_Time.Time,sizeof(Rate_Scheme_Switch_Time.Time),(INT8U *)Rate_Scheme_Switch_Time.Time,(INT8U *)Rate_Scheme_Switch_Time.Time,sizeof(Rate_Scheme_Switch_Time.Time));
    else
      mem_set((INT8U *)Rate_Scheme_Switch_Time.Time,0xFF,sizeof(Rate_Scheme_Switch_Time.Time),\
            (INT8U *)Rate_Scheme_Switch_Time.Time,sizeof(Rate_Scheme_Switch_Time.Time));
      
    SET_STRUCT_SUM(Rate_Scheme_Switch_Time); 
  }

  //����ڴ�����ر�������ȷ��
  Re=1;
  Re&=Check_HEX_Time((S_HEX_Time *)&Cur_Time0);//���Cur_Time0ʱ��
  Re&=CHECK_STRUCT_SUM(Mode_Word);//���ģʽ���Ƿ���������л�
  Re&=CHECK_STRUCT_SUM(Rate_Scheme_Switch_Time);//�������л�ʱ��
  Re&=CHECK_STRUCT_SUM(Cur_Rate_Info);//��鵱ǰ������Ϣ
  if(ASSERT(A_WARNING,0!=Re))
    Check_Data_Avail();
  
  if(Mode_Word.Mode[2].Bit.Bit5==1)//�Ƿ������л����ʷ���?
  {
    if(_Check_HEX_Time((INT8U *)&Rate_Scheme_Switch_Time.Time))
    {
      Re=_Cmp_Time((S_HEX_Time *)&Cur_Time0,(S_HEX_Time *)&Rate_Scheme_Switch_Time);//��ǰʱ���Ƿ��ڷ����л�ʱ��֮��?
      if(Re!=TIME_BEF)//��ǰʱ���ڷ��ʷ����л�ʱ��֮��
        Scheme=RATE_SCHEME1;//��ǰӦ���ø����ʷ���
      else
        Scheme=RATE_SCHEME0;
    }
    else
      Scheme=RATE_SCHEME0;
  }
  else//�����������£�Ĭ��ʹ���׷��ʷ���0
    Scheme=RATE_SCHEME0;
  
  //�͵�ǰʹ�õķ��ʷ�����һ�£�Ӧ���л����ʷ���
  //ʹ��ROM�в���������ʷ���ʱ��ǿ����Ϊ������һ�η����л�,�������
  if(Cur_Rate_Info.Scheme!=Scheme || CALC_ROM==Flag)
  {
    Cur_Rate_Info.Scheme=Scheme;
    SET_STRUCT_SUM(Cur_Rate_Info); 
    Rate_Scheme_Changed_Proc();//���ʷ����л�����
  }
  return Scheme;
}
/*
typedef struct
{
  INT8U Year_Period; //��ʱ����
  INT8U Date_Table;  //��ʱ�α���
  INT8U Date_Period; //��ʱ����
  INT8U Rates;    //������
  INT8U Holidays; //�ڼ�����
  INT8U WeekRest_DataTable;//������ʹ�õ�ʱ�α��
  INT8U WeekRest_Status;  //������״̬��
  
  INT8U CS[CS_BYTES];
}S_Multi_Rate_Para;//�����ʲ���
*/

//��鸴���ʲ���
void Check_Multi_Rate_Para()
{
  if(ASSERT(A_WARNING,Multi_Rate_Para.Year_Period<=MAX_YEAR_PERIODS))
  {
    Multi_Rate_Para.Year_Period=MAX_YEAR_PERIODS; 
    SET_STRUCT_SUM(Multi_Rate_Para);
  }
  if(ASSERT(A_WARNING,Multi_Rate_Para.Date_Table<=MAX_DATE_TABLES))
  {
    Multi_Rate_Para.Date_Table=MAX_DATE_TABLES; 
    SET_STRUCT_SUM(Multi_Rate_Para);    
  }
  if(ASSERT(A_WARNING,Multi_Rate_Para.Date_Period<=MAX_DATE_PERIODS))
  {
    Multi_Rate_Para.Date_Table=MAX_DATE_PERIODS; 
    SET_STRUCT_SUM(Multi_Rate_Para);    
  }
  if(ASSERT(A_WARNING,Multi_Rate_Para.Holidays<=MAX_YEAR_HOLIDAYS))
  {
    Multi_Rate_Para.Holidays=MAX_YEAR_HOLIDAYS; 
    SET_STRUCT_SUM(Multi_Rate_Para);      
  }
}


//��ȡ�������ز���
//Rate_Scheme��ʾ���ʷ�����,ΪRATE_SCHEME0����RATE_SCHEME1
void Read_Multi_Rate_Para(INT8U Rate_Scheme)
{
  INT16U i,Len;
  INT8U Err;
  
  if(ASSERT(A_WARNING,RATE_SCHEME0==Rate_Scheme ||\
                      RATE_SCHEME1==Rate_Scheme))
    Rate_Scheme=RATE_SCHEME0;
  
  if(RATE_SCHEME0==Rate_Scheme)//ʹ�õ�һ�׷��ʷ���
    i=0;
  else
    i=0x0800;//�ڶ��׷���������CB1F��ʼ,�ǵ�һ�׷��ʲ�����ʶ��+0x0800
  
  //��һ�׷��ʷ�������
  Len=S_OFF(S_Multi_Rate_Para,CS);
  if(Get_DLT645_Data(0xC31F+i,(void *)&Multi_Rate_Para,(void *)&Multi_Rate_Para,Len,&Err)!=Len ||\
    Err!=NO_ERR)
  {
     DEBUG_PRINT(HUCK,DEBUG_0,"Read 0xC31F Len Error"); 
  }
  
  Len=S_OFF(S_Multi_Rate_Para,WeekRest_Status);//������״̬��ǰ������ҪBCD->HEX
  Bcd2Hex_Buf((void *)&Multi_Rate_Para,Len,(void *)&Multi_Rate_Para,(void *)&Multi_Rate_Para,Len);
  SET_STRUCT_SUM(Multi_Rate_Para);
  Check_Multi_Rate_Para();//��鸴���ʲ����ĺϷ���
  
  //��ʱ����
  if(Read_Storage_Data(0xC32F+i,(void *)Year_Table.MDN,(void *)Year_Table.MDN,MAX_YEAR_PERIODS*3,&Err)!=MAX_YEAR_PERIODS*3 ||\
    Err!=NO_ERR)
    DEBUG_PRINT(HUCK,DEBUG_0,"Read 0xC32F Len Error"); 

  Len=S_OFF(S_Year_Table,CS);
  Bcd2Hex_Buf((void *)&Year_Table,Len,(void *)&Year_Table,(void *)&Year_Table,Len);
  SET_STRUCT_SUM(Year_Table); 
}

//���ڼ�������ʱ���ʱ�������,��ʱ��ʱ���,���ؽ��Ϊ����
//���ڼ�����ʱ�����������ʱ���,Time0-Time1���ú�����������ʱ������Ѱ�ҵ�ǰʱ���ʱ��
//���Time0��ʡ��Time1֮ǰ����ô�����Time0+12*31-Time1
//Time0[0]��ʾ��,Time0[1]��ʾ��,Time1��ʾ������Time0��ͬ
INT16U Year_Period_Dec(INT8U Time0[],INT8U Time1[])
{
  INT16U Days[2];

  ASSERT(A_WARNING, Time0[0]<32 && Time0[0]>0 && Time0[1]<13 && Time0[1]>0);//�ж����������ĸ�ʽ
  ASSERT(A_WARNING, Time1[0]<32 && Time0[0]>0 && Time1[1]<13 && Time1[1]>0);//�ж����������ĸ�ʽ
  
  Days[0]=(INT16U)(Time0[1])*31+(INT16U)(Time0[0]);
  Days[1]=(INT16U)(Time1[1])*31+(INT16U)(Time1[0]);
  
  if(Days[0]<Days[1])
    return Days[0]+12*31-Days[1];
  else
    return Days[0]-Days[1];
}

//��ʱ��ʱ���,����Ϊ������
//���ڼ�����ʱ�α��������ʱ���,Time0-Time1,���Time0��Time1֮ǰ����ô�����
//Time0+24*60-Time1
//Time0[0]��ʾ�֣�Time0[1]��ʾʱ��Time1��ʾ������Time0��ͬ
INT16U Date_Period_Dec(INT8U Time0[],INT8U Time1[])
{
  INT16U Mins[2];
  
  //��ʱ���ݱ���Ϸ�
  ASSERT(A_WARNING,Time0[0]<60 && Time0[1]<24);//�ж����������ĸ�ʽ
  ASSERT(A_WARNING,Time1[0]<60 && Time1[1]<24);//�ж����������ĸ�ʽ
  
  Mins[0]=(INT16U)(Time0[1])*60+(INT16U)(Time0[0]);
  Mins[1]=(INT16U)(Time1[1])*60+(INT16U)(Time1[0]);
  
  if(Mins[0]<Mins[1])
    return Mins[0]+24*60-Mins[1];
  else
    return Mins[0]-Mins[1];  
}

//��鵱ǰ�Ƿ��ǽڼ���
//�ú�����Ҫ���ڴ��ж����ڼ��ձ����бȽ�,һ��ÿ�յ��øú���һ��
//����0��ʾ���ǽڼ��գ�����>0��ʾ�ǽڼ��գ�ͬʱ����ֵ�����ǵڶ��ٸ��ڼ��գ�*pDate_Table_Index������ʱ�α��
INT8U Check_Today_Holiday(INT8U *pDate_Table_Index)
{
  INT8U Num,i,j,Counts,Err,Re;
  PROTO_DI DI;

  Re=1;
  Re&=CHECK_STRUCT_SUM(Cur_Rate_Info);
  Re&=CHECK_STRUCT_SUM(Multi_Rate_Para);
  if(ASSERT(A_WARNING,0!=Re))
    Check_Data_Avail();

  if(Multi_Rate_Para.Holidays>MAX_YEAR_HOLIDAYS)
  {
    Multi_Rate_Para.Holidays=MAX_YEAR_HOLIDAYS;
    SET_STRUCT_SUM(Multi_Rate_Para);
  }

  //ÿ���ڼ��ղ���DI��Ӧ15���ڼ��գ�������Ҫ��ȡ���ٸ��ڼ���DI����
  if(0==Multi_Rate_Para.Holidays%15)
    Num=Multi_Rate_Para.Holidays/15;
  else
    Num=Multi_Rate_Para.Holidays/15+1;

  OS_Sem_Pend(PUB_BUF0_SEM_ID);//���溯���ڲ����õ�Pub_Buf0,���ʹ���ź�������
  Counts=0;//�Ѿ��������Ľڼ��ո���
  Re=0;//���ؽ��
  for(i=0;i<Num;i++)
  {
    if(RATE_SCHEME1==Cur_Rate_Info.Scheme)
      DI=0xCC1F+(i<<4);
    else
      DI=0xC41F+(i<<4);
    
    if(Get_DLT645_Data(DI,(void *)Pub_Buf0,(void *)Pub_Buf0,15*3,&Err)!=15*3 || Err!=NO_ERR)
    {
      DEBUG_PRINT(HUCK,DEBUG_0,"Read 0x%x Len Error",DI);
      Counts+=15;
      if(Counts>=Multi_Rate_Para.Holidays || Counts>=MAX_YEAR_HOLIDAYS)
        break;//��ʱRe==0
    }
    else
    {
      Bcd2Hex_Buf((void *)&Pub_Buf0,15*3,(void *)&Pub_Buf0,(void *)&Pub_Buf0,sizeof(Pub_Buf0));
      for(j=0;j<15;j++)//һ��F����15���ڼ���
      {
        if(Cur_Time0.Time[T_MONTH]==Pub_Buf0[j*3+2] &&\
           Cur_Time0.Time[T_DATE]==Pub_Buf0[j*3+1])
        {
          *pDate_Table_Index=Pub_Buf0[j*3];//�ڼ��ղ��õ���ʱ�α��
          Re=1;//ȷʵ�Ǹ��ڼ���
          break;
        }
        Counts++;
        if(Counts>=Multi_Rate_Para.Holidays || Counts>=MAX_YEAR_HOLIDAYS)
          break;//��ʱRe==0
      }
      //�ǽڼ��գ������ⲿѭ��
      if(1==Re)
        break;
    }
  }
  OS_Sem_Post(PUB_BUF0_SEM_ID);//�ͷ�Pub_Buf0
  if(0==Re)
    return Re;
  else
    return Counts+1;//�ڶ��ٸ��ڼ���?+1��֤�ý��>0
}

//���㵱ǰӦ��ʹ�õ���ʱ�α��,���Flag==CALC_ROM��ǿ���ж�һ�ε�ǰ����ʱ�α��
//�����ʱ�α�ű仯�ˣ�����ǰ��ʱ�α����Date_Table��
INT8U Cal_Cur_Date_Table(INT8U Flag)
{
  INT8U i,Re;//Data_IndexΪʹ�õ���ʱ�α������
  INT8U Date_Table_Flag;//1��ʾ�ҵ���ʱ�α��
  INT16U Min=0xFFFF;//��Сֵ,����һ������ֵ
  INT16U Dec;//��
  
  static S_HEX_Time Last_Chk_Time={{0,0,0,0,0},0,{0^((INT8U)CHK_CS_BYTES)}};
  static S_Int8U Date_Table_Index={CHK_BYTE,1,CHK_BYTE};
  
  //�ڵ�ǰ�ڼ����в����Ƿ��ǽڼ���?
  //ʱ�䷢���˱仯������Flag��־ΪCALC_ROM��ʾǿ���ж�һ��
  //ÿ��ֻ�����������һ��,����CALC_ROM==Flagʱ���������
  Re=CHECK_STRUCT_SUM(Last_Chk_Time);
  if(Last_Chk_Time.Time[T_DATE]!=Cur_Time0.Time[T_DATE] ||\
     Last_Chk_Time.Time[T_MONTH]!=Cur_Time0.Time[T_MONTH] ||\
     Last_Chk_Time.Time[T_YEAR]!=Cur_Time0.Time[T_YEAR]||\
     CALC_ROM==Flag)//���ջ���CALC_ROM����������жϵ����Ƿ�ڼ���,ÿ��ֻ��һ�Σ�����CALC_ROM��������ж�
  {
    Re=1;
    Re&=CHECK_STRUCT_SUM(Cur_Time0);//��ǰʱ��
    Re&=CHECK_STRUCT_SUM(Multi_Rate_Para);//��ǰ�����ʲ���
    Re&=CHECK_STRUCT_SUM(Year_Table);//��ʱ����
    Re&=CHECK_STRUCT_SUM(Cur_Rate_Info);//��ǰ������Ϣ
    
    if(ASSERT(A_WARNING,0!=Re))
      Check_Data_Avail();
  
    Date_Table_Flag=0;

    //���ǵ���ʱ�䣬������жϱ�֤ÿ��ֻ����ú���һ��
    mem_cpy(&Last_Chk_Time,(void *)&Cur_Time0,sizeof(Cur_Time0),&Last_Chk_Time,sizeof(Last_Chk_Time));

    //���жϵ�ǰ�Ƿ��ǽڼ���
    Re=Check_Today_Holiday(&Date_Table_Index.Var);//����>0��ʶ��ʾ�ǽڼ���
    if(Re>0)//
    {
      Date_Table_Flag=1;//==1��ʾ�ҵ���ʱ�α���������
      Cur_Rate_Info.Date_Flag=HOLIDAY;
      Cur_Rate_Info.Holiday_Index=Re;    
    }

    //���ǹ������գ��Ƿ���������?
    if(0==Date_Table_Flag)
    {
      if(GET_BIT(Multi_Rate_Para.WeekRest_Status,Cur_Time0.Week)==0)//Ϊ0��ʾ������������
      {
        Date_Table_Index.Var=Multi_Rate_Para.WeekRest_DataTable;//��������ʱ�α��
        Date_Table_Flag=1;//==1��ʾ�ҵ���ʱ�α���������      
        Cur_Rate_Info.Date_Flag=WEEK_REST_DAY;    
      }
    }
    
    //���ǹ������գ�Ҳ���������գ�����ʱ�����в���
    if(0==Date_Table_Flag)
    {
      Cur_Rate_Info.Date_Flag=NORMAL_DAY;//����һ��ƽ�������ӣ��Ȳ��ǽڼ��գ�Ҳ����������
      for(i=0;i<Multi_Rate_Para.Year_Period && i<MAX_YEAR_PERIODS;i++)
      {                                    //�ա���
        Dec=Year_Period_Dec((INT8U *)&Cur_Time0.Time[T_DATE],(INT8U *)&Year_Table.MDN[i][1]);//���㵱ǰʱ�����ʱ������ĳ��ʱ���ʱ���
        if(Dec<Min)//Ѱ��ʱ�����С��һ����Ϊ�ǵ�ǰ��ʱ��
        {
          Date_Table_Index.Var=Year_Table.MDN[i][0];//��ʱ�α�����
          Date_Table_Flag=1;
          Cur_Rate_Info.Year_Period=i+1;//��ʱ����
          Min=Dec;
        }
      }
    }
  
    //û�еõ����ʵ���ʱ�α�ţ������1ʱ�α�
    if(ASSERT(A_WARNING,1==Date_Table_Flag &&\
                        Date_Table_Index.Var>0 &&\
                        Date_Table_Index.Var<=Multi_Rate_Para.Date_Table &&\
                        Date_Table_Index.Var<=MAX_DATE_TABLES))
      Date_Table_Index.Var=1;
    //�ж�ʱ�α���Ƿ����仯,�仯�������¶�ȡʱ�α����,����ǿ����Ϊ��ʱ�η����˱仯�Ļ�Ҳ���¶�ȡ
    if(Cur_Rate_Info.Date_Table!=Date_Table_Index.Var || CALC_ROM==Flag)//��ǰʱ�α�ŷ����仯��
    {
      DEBUG_PRINT(HUCK,DEBUG_0,"Date Table Changed,%d-->%d",Cur_Rate_Info.Date_Table,Date_Table_Index.Var);
      Cur_Rate_Info.Date_Table=Date_Table_Index.Var;//��ʱ�α�������
      SET_STRUCT_SUM(Cur_Rate_Info);    
      Get_Cur_Date_Table(Cur_Rate_Info.Scheme,Date_Table_Index.Var);//��ȡ��ǰʱ�α������Date_Table�� 
    }
  }
  return Cur_Rate_Info.Date_Table;//Date_Table_Index;
}

//��ȡRate_Scheme�׷��ʷ�����Date_Table_Index��ʱ�α�Date_Table�ṹ�������
void Get_Cur_Date_Table(INT8U Rate_Scheme,INT8U Date_Table_Index)
{
  INT8U Re;
  INT8U Err;
  INT16U Len;

  Re=CHECK_STRUCT_SUM(Date_Table);
  if(ASSERT(A_WARNING,1==Re))
    Check_Data_Avail();

  ASSERT(A_WARNING,(RATE_SCHEME0==Rate_Scheme || RATE_SCHEME1==Rate_Scheme));
  if(ASSERT(A_WARNING,Date_Table_Index>0 && Date_Table_Index<=MAX_DATE_TABLES))
    Date_Table_Index=1;

  Len=0;
  if(Rate_Scheme==RATE_SCHEME0)
    Len=Read_Storage_Data(0xC33F+((Date_Table_Index-1)<<4),(INT8U *)Date_Table.HMN,(INT8U *)Date_Table.HMN,sizeof(Date_Table.HMN),&Err);
  else
    Len=Read_Storage_Data(0xCB3F+((Date_Table_Index-1)<<4),(INT8U *)Date_Table.HMN,(INT8U *)Date_Table.HMN,sizeof(Date_Table.HMN),&Err);
  //��ʱ�α�����ת��Ϊhex��
  Bcd2Hex_Buf((void *)&Date_Table,S_OFF(S_Date_Table,CS),(void *)&Date_Table,(void *)&Date_Table,S_OFF(S_Date_Table,CS));
  ASSERT(A_WARNING,MAX_DATE_PERIODS*3==Len && NO_ERR==Err);
  
  SET_STRUCT_SUM(Date_Table);
}


//���㵱ǰӦ��ʹ�õķ��ʱ��
//��Ҫ�Ǵӵ�ǰ��ʱ�α����ҵ���ǰ���ʺ�
INT8U Calc_Cur_Rate(INT8U Flag)
{
  INT8U Rate,Re;//Data_IndexΪʹ�õ���ʱ�α������
  INT16U Min=0xFFFF,i;
  INT16U Dec;
  INT8U Period;//��ʱ�κ�
  
  Re=1;
  Re&=CHECK_STRUCT_SUM(Cur_Time0);
  Re&=CHECK_STRUCT_SUM(Cur_Rate_Info);
  Re&=CHECK_STRUCT_SUM(Multi_Rate_Para);
  
  if(ASSERT(A_WARNING,0!=Re))
    Check_Data_Avail();//������ݵ���Ч��

  Period=Cur_Rate_Info.Date_Period;
  //�����ʱ�α�ŷ����仯�������¶�ȡ��Date_Table������
  //�׷��ʷ��������仯��ʱ�򣬻�ǿ���л�Date_Table
  //ƽʱ������ʵ�ʱ��ֻ��ÿ�����һ��Date_Table
  Cal_Cur_Date_Table(CALC_RAM);
  //�˴�û����Flag������CALC_RAM����Ϊ��Flag==CACL_ROMʱ��֮ǰ�϶�������Calc_Cur_Rate_Scheme(CACL_ROM)���������Ѿ�����ʱ�α�����˴���

  //����ʱ�α����ҵ�ǰ����
  Rate=0;
  Min=0xFFFF;//��һ������ֵ
  for(i=0;i<Multi_Rate_Para.Date_Period && i<MAX_DATE_PERIODS;i++)
  {                                
    Dec=Date_Period_Dec((INT8U *)&Cur_Time0.Time[T_MIN],(INT8U *)&Date_Table.HMN[i][1]);
    if(Dec<Min)
    {
      Rate=Date_Table.HMN[i][0];//����
      Cur_Rate_Info.Date_Period=i+1;//��ʱ�κ�
      Min=Dec;
    }
  }
  
  if(ASSERT(A_WARNING,Rate<=MAX_RATES && Rate<=Multi_Rate_Para.Rates && Rate>0))//���ʺŴ�Ĭ��ʹ�÷���1
    Rate=1;
  
  if(Cur_Rate_Info.Rate!=Rate || CALC_ROM==Flag)//��Ҫ�л�������
  {
    Cur_Rate_Info.Rate=Rate;
    SET_STRUCT_SUM(Cur_Rate_Info);//���溯����CHECK_STRUCT_SUMŶ
    Rate_Changed_Proc();//�����л���ش���
  }
  
  if(Period!=Cur_Rate_Info.Date_Period)
  {
    Set_Event_Instant(ID_PARSE_SWITCH);//ʱ���л�
    Port_Out_Pub(EXT_ID_PARSE,85);
    DEBUG_PRINT(HUCK,DEBUG_0,"Date Period Switch!!!");
  }
  SET_STRUCT_SUM(Cur_Rate_Info);  
  return Rate;//���ط��ʺ�
}
/*
typedef struct
{
  INT32U Chang_Plus_AcEnerg[4];            //A/B/C/SUM��Ԫ�������й�����:��λ:0.01wh
  INT32U Chang_Nega_AcEnerg[4];            //A/B/C/SUM��Ԫ�������й�����:��λ:0.01wh
  
  //INT32U Chang_Plus_ReacEnerg[4];          //A/B/C/SUM��Ԫ�������޹�����(�޹����1):��λ:0.01warh  
  //INT32U Chang_Nega_ReacEnerg[4];          //A/B/C/SUM��Ԫ�������޹�����(�޹����2):��λ:0.01warh
  
  INT32U Chang_Quad_ReacEnerg[4][4];       //A/B/C/SUM��Ԫ���������޹�����,Chang_Quad_ReacEnerg[1][2]��ʾB��3�����޹�
  
  INT32U Add_AmpaHour[3];                 //AH�ۼ�:0.0001As,�ۼ���
  INT32U Add_CopperLoss[4];		  //A,B,C,sumͭ��,��λΪ0.0000001kA2s,�ۼ���
  INT32U Add_IronLoss[4];		  //A,B,C,sum����,��λΪ0.0000001KV2s���ۼ���
  INT32U Add_GenaralErr[4];		  //A,B,C,sum�ϳ����,��λ:0.01*tgFA*s,�ۼ���
  INT8U CS[CS_BYTES];
}MEASU_ENERG; 
*/
//����ۻ����������Ƿ���ȷ
INT8U Check_Cumulative_Energy_Data(MEASU_ENERG *pEnergy)
{
  INT8U Re,i,j;
  
  Re=Check_STRUCT_Sum(pEnergy,sizeof(MEASU_ENERG),pEnergy->CS,sizeof(pEnergy->CS));
  if(ASSERT(A_WARNING,1==Re))
    return 0;
  
  for(i=0;i<4;i++)
  {
    if(pEnergy->Chang_Plus_AcEnerg[i]>=(INT32U)MAX_ACTIVE_INC*ENERGY_RATIO ||\
      pEnergy->Chang_Nega_AcEnerg[i]>=(INT32U)MAX_ACTIVE_INC*ENERGY_RATIO)
    {
      ASSERT(A_WARNING,0);
      return 0;
    }
    else
    {
      for(j=0;j<4;j++)
      {
        if(pEnergy->Chang_Quad_ReacEnerg[i][j]>=(INT32U)MAX_REACTIVE_INC*ENERGY_RATIO) 
        {
          ASSERT(A_WARNING,0);
          return 0;
        }        
      }
    }
  }

  return 1;
}

//�����������Ƿ�����
INT8U Check_Energy_Data_Inc()
{
  INT8U i;
  INT32U Temp;
  
  //�����й�����
  if(Cur_Energy.Pos_Active[0]>=Cur_Energy_Bak.Pos_Active[0])
  {
    Temp=Cur_Energy.Pos_Active[0]-Cur_Energy_Bak.Pos_Active[0];
    if(Temp>MAX_ACTIVE_INC)//��������
    {
      DEBUG_PRINT(HUCK,DEBUG_0,"Pos Energy Data Inc too much:%ld",Temp);
      ASSERT(A_WARNING,0);
      return 0;
    }
  }
  else//��������
  {
    ASSERT(A_WARNING,0);
    DEBUG_PRINT(HUCK,DEBUG_0,"Pos Energy Data Dec!");
    return 0;
  }
  
  //�����й�����
  if(Cur_Energy.Neg_Active[0]>=Cur_Energy_Bak.Neg_Active[0])
  {
    Temp=Cur_Energy.Neg_Active[0]-Cur_Energy_Bak.Neg_Active[0];
    if(Temp>MAX_ACTIVE_INC)//��������
    {
      DEBUG_PRINT(HUCK,DEBUG_0,"Neg Energy Data Inc too much:%ld",Temp);
      ASSERT(A_WARNING,0);
      return 0;
    }
  }
  else//��������
  {
    ASSERT(A_WARNING,0);
    DEBUG_PRINT(HUCK,DEBUG_0,"Neg Energy Data Dec!");
    return 0;
  }
  
  //�������޹�
  for(i=0;i<4;i++)
  {
    if(Cur_Energy.Quad_Reactive[i][0]>=Cur_Energy_Bak.Quad_Reactive[i][0])
    {
      Temp=Cur_Energy.Quad_Reactive[i][0]-Cur_Energy_Bak.Quad_Reactive[i][0];
      if(Temp>MAX_REACTIVE_INC)//��������
      {
        DEBUG_PRINT(HUCK,DEBUG_0,"Quad %d Reactive Energy Data Inc too much:%ld",i,Temp);
        ASSERT(A_WARNING,0);
        return 0;
      }
    }
    else//��������
    {
      ASSERT(A_WARNING,0);
      DEBUG_PRINT(HUCK,DEBUG_0,"Quad %d Reactive Energy Data Dec!",i);
      return 0;
    }
  }
  
  //����������й�
  for(i=0;i<3;i++)
  {
    //�����й�
    if(Cur_Energy.Phase_Pos_Active[i]>=Cur_Energy_Bak.Phase_Pos_Active[i])
    {
      Temp=Cur_Energy.Phase_Pos_Active[i]-Cur_Energy_Bak.Phase_Pos_Active[i];
      if(Temp>MAX_ACTIVE_INC)//��������
      {
        DEBUG_PRINT(HUCK,DEBUG_0,"Phase %c Pos_Active Energy Data Inc too much:%d",'A'+i,Temp);
        ASSERT(A_WARNING,0);
        return 0;
      }
    }
    else//��������
    {
      ASSERT(A_WARNING,0);
      DEBUG_PRINT(HUCK,DEBUG_0,"Phase %c Pos_Active Energy Data Dec!",'A'+i);
      return 0;
    }
    
    //�����й�
    if(Cur_Energy.Phase_Neg_Active[i]>=Cur_Energy_Bak.Phase_Neg_Active[i])
    {
      Temp=Cur_Energy.Phase_Neg_Active[i]-Cur_Energy_Bak.Phase_Neg_Active[i];
      if(Temp>MAX_REACTIVE_INC)//��������
      {
        DEBUG_PRINT(HUCK,DEBUG_0,"Phase %c Neg_Active Energy Data Inc too much:%ld",'A'+i,Temp);
        ASSERT(A_WARNING,0);
        return 0;
      }
    }
    else//��������
    {
      ASSERT(A_WARNING,0);
      DEBUG_PRINT(HUCK,DEBUG_0,"Phase %c Neg_Active Energy Data Dec!",'A'+i);
      return 0;
    }
  }
  return 1;
}

//��ǰ�����ۼ�
void Cur_Energy_Cumu(MEASU_ENERG *pEnergy)
{
  INT8U Rate;
  INT8U i,j;
  
  Rate=Cur_Rate_Info.Rate;//Get_Using_Rate();//��ǰʹ�÷���
  //��֤��ǰ����������ȷ��,���������������������Ĭ��ʹ�÷���1
  if(ASSERT(A_WARNING,Rate>0 && Rate<=Multi_Rate_Para.Rates && Rate<=MAX_RATES))
     Rate=1;
  //�����ۼ�  
  Cur_Energy.Pos_Active[0]+=(pEnergy->Chang_Plus_AcEnerg[3]/ENERGY_RATIO);
  Cur_Energy.Pos_Active[Rate]+=(pEnergy->Chang_Plus_AcEnerg[3]/ENERGY_RATIO);
  //�����ۼ�
  Cur_Energy.Neg_Active[0]+=(pEnergy->Chang_Nega_AcEnerg[3]/ENERGY_RATIO);
  Cur_Energy.Neg_Active[Rate]+=(pEnergy->Chang_Nega_AcEnerg[3]/ENERGY_RATIO);
  //�����ۼ�
  //Cur_Energy.Pos_Reactive[0]+=(pEnergy->Chang_Plus_ReacEnerg[3]/ENERGY_RATIO);
  //Cur_Energy.Pos_Reactive[Rate]+=(pEnergy->Chang_Plus_ReacEnerg[3]/ENERGY_RATIO);
  //�����ۼ�
  //Cur_Energy.Neg_Reactive[0]+=(pEnergy->Chang_Nega_ReacEnerg[3]/ENERGY_RATIO);
  //Cur_Energy.Neg_Reactive[Rate]+=(pEnergy->Chang_Nega_ReacEnerg[3]/ENERGY_RATIO);
  
  //�������޹��ۼ�
  for(i=0;i<4;i++)
  {
    Cur_Energy.Quad_Reactive[i][0]+=pEnergy->Chang_Quad_ReacEnerg[3][i]/ENERGY_RATIO;      
    Cur_Energy.Quad_Reactive[i][Rate]+=pEnergy->Chang_Quad_ReacEnerg[3][i]/ENERGY_RATIO;
  }
  
  //�������޹�
  for(i=0;i<3;i++)
  {
    Cur_Energy.Phase_Pos_Active[i]+=(pEnergy->Chang_Plus_AcEnerg[i]/ENERGY_RATIO);
    Cur_Energy.Phase_Neg_Active[i]+=(pEnergy->Chang_Nega_AcEnerg[i]/ENERGY_RATIO);

    for(j=0;j<4;j++)//���������޷ֱ����
      Cur_Energy.Phase_Quad_Reactive[i][j]+=pEnergy->Chang_Quad_ReacEnerg[i][j]/ENERGY_RATIO;
  }
  
  //���ల��ʱ
  for(i=0;i<3;i++)
    Cur_Energy.Phase_AH[i+1]+=(pEnergy->Add_AmpaHour[i]/AH_RATIO);
  
   Cur_Energy.Phase_AH[0]+=(pEnergy->Add_AmpaHour[3]/AH_RATIO);
   
  //���Լ�����ͭ��  
  Cur_Energy.CopperLoss[0]+=(pEnergy->Add_CopperLoss[3]/COPPERLOSS_RATIO);
  Cur_Energy.CopperLoss[1]+=(pEnergy->Add_CopperLoss[0]/COPPERLOSS_RATIO);
  Cur_Energy.CopperLoss[2]+=(pEnergy->Add_CopperLoss[1]/COPPERLOSS_RATIO);
  Cur_Energy.CopperLoss[3]+=(pEnergy->Add_CopperLoss[2]/COPPERLOSS_RATIO);
  //���Լ���������  
  Cur_Energy.IronLoss[0]+=(pEnergy->Add_IronLoss[3]/IRONLOSS_RATIO);
  Cur_Energy.IronLoss[1]+=(pEnergy->Add_IronLoss[0]/IRONLOSS_RATIO);
  Cur_Energy.IronLoss[2]+=(pEnergy->Add_IronLoss[1]/IRONLOSS_RATIO);
  Cur_Energy.IronLoss[3]+=(pEnergy->Add_IronLoss[2]/IRONLOSS_RATIO);
  //���Լ�����ϳ����
  Cur_Energy.TransErr[0]+=(pEnergy->Add_GenaralErr[3]/TRANSERR_RATIO);
  Cur_Energy.TransErr[1]+=(pEnergy->Add_GenaralErr[0]/TRANSERR_RATIO);
  Cur_Energy.TransErr[2]+=(pEnergy->Add_GenaralErr[1]/TRANSERR_RATIO);
  Cur_Energy.TransErr[3]+=(pEnergy->Add_GenaralErr[2]/TRANSERR_RATIO);
  //����Cur_Energy.Time��ʱ��
  //mem_cpy((S_HEX_Time *)&Cur_Energy.Time,(S_HEX_Time *)&Cur_Time0,sizeof(Cur_Time0),(S_HEX_Time *)&Cur_Energy.Time,sizeof(Cur_Energy.Time));
  SET_STRUCT_SUM(Cur_Energy);   
  
}
//�ۼӵ���
void Cumulative_Energy()
{
  static S_Int32U Sec_Bak={CHK_BYTE,0,CHK_BYTE};
  MEASU_ENERG *pEnergy;
  INT8U Re;
  
  Re=CHECK_STRUCT_VAR(Sec_Bak);
  ASSERT(A_WARNING,1==Re);
  
  //��֤ÿ��Ž���һ�θú���
  if(Sec_Bak.Var==Sec_Timer_Pub)
    return;
  else
    Sec_Bak.Var=Sec_Timer_Pub;    
  
  Re=1;
  Re&=Check_Energy_Data((S_Energy *)&Cur_Energy);
  Re&=CHECK_STRUCT_SUM(Cur_Rate_Info);
  if(ASSERT(A_WARNING,1==Re))
    Check_Data_Avail();
  
  //OS_Sem_Pend(PUB_BUF_SEM_ID);//����Pub_Buf���ź���

  Get_Measu_AcculateData_PUCK(HUCK,(void *)&Cumu_Energy,(void *)&Cumu_Energy,sizeof(Cumu_Energy),sizeof(Cumu_Energy));
  pEnergy=(MEASU_ENERG *)&Cumu_Energy;
  Re=Check_Cumulative_Energy_Data(pEnergy);
  ASSERT(A_WARNING,1==Re);
  if(1==Re)//pEnergyָ������ݺϷ�
  { 
    DIS_PD_INT;//�ص����ж�
    Cur_Energy_Cumu(pEnergy); //��ǰ�����ۼ�   
    //Event_Energy_Cumu(pEnergy);//������ص������ݵ��ۼ�
    Energy_Cumu_Counts.Var++; //�����ۼӴ�������
    EN_PD_INT;//�������ж�
  }
  //OS_Sem_Post(PUB_BUF_SEM_ID);//����Pub_Buf���ź���
  
  Check_Energy_Data_Inc();//�����������Ƿ�Ϸ�
  

  
#if USE_ENERGY_RAM_BAK//�����ݱ��ݵ�Cur_Energy_Bak������
  mem_cpy((void *)&Cur_Energy_Bak,(void *)&Cur_Energy,sizeof(Cur_Energy_Bak),(void *)&Cur_Energy_Bak,sizeof(Cur_Energy_Bak));
#endif
}

//��鸴���ʵ������ݷַ��ʵ������Ƿ�����ܵ���
INT8U Check_Multi_Rate_Data(INT32U Data[])
{
  INT16U i;
  INT32U Sum;
  
  Sum=0;
  for(i=1;i<=MAX_RATES;i++)
    Sum+=Data[i];
  if(Sum==Data[0])
    return 1;
  else
    return 0;
}

//�����������Ƿ�Ϸ���ȷ
//����1��ʾ������ȷ,0��ʾ�����д�
INT8U Check_Energy_Data(S_Energy *pEnergy)
{
  INT8U Re=1;

  Re&=(pEnergy->Head==CHK_BYTE && pEnergy->Tail==CHK_BYTE)?1:0;  
  Re&=Check_STRUCT_Sum(pEnergy,sizeof(S_Energy),pEnergy->CS,sizeof(pEnergy->CS));
  Re&=(pEnergy->Data_Ready_Flag==DATA_READY)?1:0;
  if(ASSERT(A_WARNING,0!=Re))
    return 0;
  
  Re&=Check_Multi_Rate_Data((INT32U *)(pEnergy->Pos_Active));
  ASSERT(A_WARNING,0!=Re);
  Re&=Check_Multi_Rate_Data((INT32U *)(pEnergy->Neg_Active));
  ASSERT(A_WARNING,0!=Re);
  Re&=Check_Multi_Rate_Data((INT32U *)(pEnergy->Neg_Active));
  ASSERT(A_WARNING,0!=Re);
  Re&=Check_Multi_Rate_Data((INT32U *)(pEnergy->Quad_Reactive[0]));
  ASSERT(A_WARNING,0!=Re);
  Re&=Check_Multi_Rate_Data((INT32U *)(pEnergy->Quad_Reactive[1]));
  ASSERT(A_WARNING,0!=Re);
  Re&=Check_Multi_Rate_Data((INT32U *)(pEnergy->Quad_Reactive[2]));
  ASSERT(A_WARNING,0!=Re);
  Re&=Check_Multi_Rate_Data((INT32U *)(pEnergy->Quad_Reactive[3]));
  ASSERT(A_WARNING,0!=Re);
  Re&=Check_STRUCT_Sum(pEnergy,sizeof(S_Energy),pEnergy->CS,sizeof(pEnergy->CS));  
  ASSERT(A_WARNING,0!=Re);
  return Re;
}

//���ȫ�ֹ���buf�Ƿ�Ϸ�
void Check_Pub_Var_Avail()
{
  INT8U Re;
  Re=CHECK_STRUCT_VAR(_Pub_Buf);
  ASSERT(A_WARNING,1==Re);
  Re=CHECK_STRUCT_VAR(_Pub_Buf0);
  ASSERT(A_WARNING,1==Re);
  Re=CHECK_STRUCT_VAR(Pub_Timer);
  ASSERT(A_WARNING,1==Re);
  Re=CHECK_STRUCT_VAR(Assert_Info);
  ASSERT(A_WARNING,1==Re);
}

//��鵱ǰ��������������,�������ݴ���
void Check_Energy_Data_Avail()//��鵱ǰ�������������ݵ���ȷ��,��=��
{
  INT8U Re;
  static S_Flag Energy_Err_Flag={0,{0}};
 
  //Energy_Err_Flag������¼���������Ƿ��������󣨷ַ��ʺͣ�=�ܣ�,����Ѿ���������û�о���ɹ�
  //��ñ�־��1����ʶ�����ɹ�,�Ӷ��´ν���ú������ٽ��о�����,��ֹ�ظ����ϵľ��������
  
  //��鵱ǰ����,ͬʱ���ַ����Ƿ�����ܣ��Լ�У���
  //���ַ����Ƿ������ʱ������ڴ������ݲ��ԣ����ȡROM�����ݣ�������������ݻ�����
  //��Ĭ�ϸôεĴ���,�Ժ��ٽ��м�飬��ʱEnergy_Err_Flag==1
  Re=Check_Energy_Data((S_Energy *)&Cur_Energy);
  if(0==Re)
  {
    ASSERT(A_WARNING,0);
#if USE_ENERGY_RAM_BAK//�ú�Ϊ1��ʾ������Cur_Energy_Bak������ΪCur_Energy���ڴ汸��
    DEBUG_PRINT(HUCK,DEBUG_0,"Cur_Energy Data Error,Copy from Cur_Energy_Bak Data");
    Re=Check_Energy_Data((S_Energy *)&Cur_Energy_Bak);//ʹ���ڴ汸�ݵ���
    if(1==Re)//Cur_Energy_Bak�е�������ȷ
    {
      DEBUG_PRINT(HUCK,DEBUG_0,"Copy Cur_Energy_Bak Data to Cur_Energy");//��Cur_Energy_Bak�е����ݸ��Ƶ�Cur_Energy��
      mem_cpy((void *)&Cur_Energy,(void *)&Cur_Energy_Bak,sizeof(Cur_Energy),(void *)&Cur_Energy,sizeof(Cur_Energy));
    }
    else//Cur_Energy_Bak�����ݲ���ȷ�������ֱ�Ӵ�rom�ж�ȡ����
    {
      DEBUG_PRINT(HUCK,DEBUG_0,"Cur_Energy_Bak Data Error,Read_Energy_Data_From_Rom");
      Read_Energy_Data_From_Rom(); 
      Re=Check_Energy_Data((S_Energy *)&Cur_Energy);//ROM�е�����Ҳ���ԵĻ�����ȫû�а취�ˣ�Ĭ���������,��Energy_Err_Flag=1
      if(0==Re)
        Energy_Err_Flag.Flag=1;//��ʾ����û�гɹ�
      SET_STRUCT_SUM(Energy_Err_Flag);//ͬʱҲ�ɾ��������CHECK_STRUCT_SUM(Energy_Err_Flag)!=1
    }
#else
    ASSERT(A_WARNING,0);
    DEBUG_PRINT(HUCK,DEBUG_0,"Cur_Energy Data Error,Read_Energy_Data_From_Rom");
    Read_Energy_Data_From_Rom(); 
    Re=Check_Energy_Data((S_Energy *)&Cur_Energy);//ROM�е�����Ҳ���ԵĻ�����ȫû�а취�ˣ�Ĭ���������,��Energy_Err_Flag=1
    if(0==Re)
      Energy_Err_Flag.Flag=1;//��ʾ����û�гɹ�
    SET_STRUCT_SUM(Energy_Err_Flag);//ͬʱҲ�ɾ��������CHECK_STRUCT_SUM(Energy_Err_Flag)!=1
#endif
  }
}

//���浱ǰ�������������ݣ������̶�ʱ���øú������������
void Save_Cur_Energy_Data()
{
  INT8U Re;
  Re=Check_Energy_Data((S_Energy *)&Cur_Energy);
  if(ASSERT(A_WARNING,1==Re))
    Check_Data_Avail();
 
  Re=Check_Energy_Data((S_Energy *)&Cur_Energy);
  if(1==Re)
  {
    Re=Write_Storage_Data(CUR_ENERGY,(void *)(&Cur_Energy),ENERGY_SAVE_SIZE);
    ASSERT(A_WARNING,NO_ERR==Re);
    OS_TimeDly_Ms(100);
  }
  else
    ASSERT(A_WARNING,0);
}

//����ʱ���øú����������������
void Save_Cur_Energy_PD_Data()
{
  INT8U Re;
  Re=Check_Energy_Data((S_Energy *)&Cur_Energy);
  if(0==Re)//�ж�Cur_Energy�е������Ƿ���ȷ������ȷ�����Cur_Energy_Bak�е����ݣ�����������ݶ�����ȷ���򲻴�
  {
    ASSERT(A_WARNING,0);
#if USE_ENERGY_RAM_BAK==1
    Re=Check_Energy_Data((S_Energy *)&Cur_Energy_Bak);
    if(1==Re)
      mem_cpy((S_Energy *)&Cur_Energy,(S_Energy *)&Cur_Energy_Bak,sizeof(Cur_Energy_Bak),(S_Energy *)&Cur_Energy,sizeof(Cur_Energy));
    else
    {
      ASSERT(A_WARNING,0);
      return;
    }
#else
    return;
#endif
  }
  Re=Write_Storage_Data(CUR_ENERGY_PD,(void *)(&Cur_Energy),ENERGY_SAVE_SIZE);
  if(NO_ERR!=Re)
    ASSERT(A_WARNING,0);
}

//���浱ǰ�������������ݣ������̶�ʱ���øú������������
void Save_Cur_Energy_Bak0_Data()
{
  INT8U Re;
  
  Re=Check_Energy_Data((S_Energy *)&Cur_Energy);
  if(1==Re)
  {
    Re=Write_Storage_Data(CUR_ENERGY_BAK0,(void *)(&Cur_Energy),ENERGY_SAVE_SIZE);
    ASSERT(A_WARNING,NO_ERR==Re);  
    OS_TimeDly_Ms(100);
  }
  else
    ASSERT(A_WARNING,0);
}

//���浱ǰ�������������ݣ������̶�ʱ���øú������������
void Save_Cur_Energy_Bak1_Data()
{
  INT8U Re;

  Re=Check_Energy_Data((S_Energy *)&Cur_Energy);
  if(1==Re)
  {  
    Re=Write_Storage_Data(CUR_ENERGY_BAK1,(void *)(&Cur_Energy),ENERGY_SAVE_SIZE);
    ASSERT(A_WARNING,NO_ERR==Re);  
    OS_TimeDly_Ms(100);
  }
  else
    ASSERT(A_WARNING,0);
}

//���浱ǰ�������������ݣ������̶�ʱ���øú������������
void Save_Cur_Energy_Bak2_Data()
{
  INT8U Re;
  Re=Check_Energy_Data((S_Energy *)&Cur_Energy);
  if(1==Re)
  {
    Re=Write_Storage_Data(CUR_ENERGY_BAK2,(void *)(&Cur_Energy),ENERGY_SAVE_SIZE);
    ASSERT(A_WARNING,NO_ERR==Re);  
    OS_TimeDly_Ms(100);
  }
  else
    ASSERT(A_WARNING,0);
}

//����Ĭ�ϵĵ�������
void Set_Def_Energy_Data()
{
  INT8U i,Re;
  S_HEX_Time TempTime;
  
  DISP_CLR_DATA_INFO;
  DEBUG_PRINT(HUCK,DEBUG_0,"Set Def Energy Data");
  mem_set((void *)&Cur_Energy,0,sizeof(Cur_Energy),(void *)&Cur_Energy,sizeof(Cur_Energy));
  SET_STRUCT_SUM(Cur_Energy);
  
#if USE_ENERGY_RAM_BAK==1
  mem_set((void *)&Cur_Energy_Bak,0,sizeof(Cur_Energy),(void *)&Cur_Energy_Bak,sizeof(Cur_Energy_Bak));
  SET_STRUCT_SUM(Cur_Energy_Bak);
#endif
  
  INIT_STRUCT_VAR(Cur_Energy);
  SET_DATA_READY_FLAG(Cur_Energy);
  SET_STRUCT_SUM(Cur_Energy);
  
  Save_Cur_Energy_PD_Data();
  Save_Cur_Energy_Data();
  Save_Cur_Energy_Bak0_Data();  
  //Save_Cur_Energy_Bak1_Data();  
  //Save_Cur_Energy_Bak2_Data();
  
  Re=CHECK_STRUCT_SUM(Cur_Time0);//��鵱ǰʱ��
  if(ASSERT(A_WARNING,0!=Re))
    Check_Data_Avail();

  //<=Cur_Time0�����һ������ʱ���
  Get_Last_Freeze_Time((S_HEX_Time *)&Cur_Time0,&TempTime);
  //��ǰi���µ����ݶ��������ܶ��������ʧ�ܵģ����ж���
  //mem_cpy(&TempTime1,&TempTime,sizeof(S_HEX_Time),&TempTime1,sizeof(TempTime1));//����TempTime��TempTime1
  for(i=0;i<HIS_ENERGY_DATA_MONTHS;i++)
  {
    SET_STRUCT_TIME(Cur_Energy,TempTime);//���õ�������ʱ��ΪTempTime
    DEBUG_PRINT(HUCK,DEBUG_0,"Set Energy Data Time: ");
    Debug_Print_HEX_Time((INT8U *)Cur_Energy.Time.Time);
    Write_HIS_Data(HIS_ENERGY_DATA,&TempTime,(void *)&Cur_Energy,ENERGY_SAVE_SIZE);
    
    Time_Dec(&TempTime,1,UNIT_MON,&TempTime);//ʱ����ǰ��1����
    OS_TimeDly_Ms(20);//��ʱ����������
  }
  SET_STRUCT_TIME(Cur_Energy,Cur_Time0);//�ָ�����ʱ�� 
  
  Extend_Set_Def_Energy_Data();
}

//ÿ��һ��ʱ���Զ����浱ǰ����������������ʱ�������
void Auto_Save_Cur_Data()
{
  DECLARE_BUF_TYPE(INT8U,6,S_Bak_Hour);
  static S_Bak_Hour Bak_Hour={CHK_BYTE,{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},CHK_BYTE};
  static S_Int8U Min_Bak={CHK_BYTE,0xFF,CHK_BYTE};
  INT8U Re;
  
  Re=1;
  Re&=CHECK_STRUCT_VAR(Min_Bak);
  Re&=CHECK_STRUCT_VAR(Bak_Hour);
  ASSERT(A_WARNING,1==Re);
  
  Re=CHECK_STRUCT_SUM(Cur_Time0);
  ASSERT(A_WARNING,0!=Re);
  
  if(Min_Bak.Var!=Cur_Time0.Time[T_MIN])//ÿ�����ж�һ��
  {
    Min_Bak.Var=Cur_Time0.Time[T_MIN];
    
    if(Min_Bak.Var==0)//����Ϊ0������²�����!��Ϊ���ʱ�̿������¶���ʱ�̣���ʱ��Ӧ�ô����������������
      return;
 
    Re=CHECK_STRUCT_VAR(Bak_Hour);
    ASSERT(A_WARNING,1==Re);
  
    SET_STRUCT_TIME(Cur_Energy,Cur_Time0);
    SET_STRUCT_TIME(Cur_Demand.Demand[0],Cur_Time0);
    SET_STRUCT_TIME(Cur_Demand.Demand[1],Cur_Time0);
    SET_STRUCT_SUM(Cur_Demand);
    SET_STRUCT_TIME(Cur_VolStat,Cur_Time0);
    
    //ÿ��Сʱ�����������,�����ݴ����������
    if(Cur_Time0.Time[T_MIN]==17 || Cur_Time0.Time[T_MIN]==47)
    {
      DEBUG_PRINT(HUCK,DEBUG_0,"Every 30 Mins Save_Cur_Energy_PD_Data,Save_Cur_Demand_PD_Data,Save_Bak_PD_Time");
      Save_Cur_Energy_PD_Data();
      Save_Cur_Demand_PD_Data();
      Save_Bak_PD_Time();
    }
    
    //ÿСʱ43�ֱ�������,�����ݴ����EEROM��
    if(Cur_Time0.Time[T_MIN]==43 && Cur_Time0.Time[T_HOUR]!=Bak_Hour.Buf[0])
    {
      DEBUG_PRINT(HUCK,DEBUG_0,"Every Hour Save_Cur_Energy_Data,Save_Cur_Demand_Data,Save_PD_Time,Save_LoadData_PD_Data");
      Bak_Hour.Buf[0]=Cur_Time0.Time[T_HOUR];
      Save_Cur_Energy_Data();
      Save_Cur_Demand_Data();
      Save_PD_Time();
      Save_LoadData_PD_Data();      
    }
    
    //ÿ6Сʱ����һ�ε����������ݵ����ݵ�DI��,�����ݴ����EEROM��
    if(Cur_Time0.Time[T_HOUR]%6==5 && Cur_Time0.Time[T_HOUR]!=Bak_Hour.Buf[1])
    {
      DEBUG_PRINT(HUCK,DEBUG_0,"Every 6 Hours Save_Cur_Energy_Bak0_Data && Save_Cur_Demand_Bak_Data");
      Bak_Hour.Buf[1]=Cur_Time0.Time[T_HOUR];
      Save_Cur_Energy_Bak0_Data();
      Save_Cur_Demand_Bak_Data();   
    }
    
    //ÿ12Сʱ����һ�ε����������ݵ����ݵ�DI��,�����ݴ����EEROM��
    if(Cur_Time0.Time[T_HOUR]%12==1 && Cur_Time0.Time[T_HOUR]!=Bak_Hour.Buf[2])
    {
      DEBUG_PRINT(HUCK,DEBUG_0,"Every 6 Hours Save_Cur_Energy_Bak1_Data,Save_LoadData_Index_Bak");
      Bak_Hour.Buf[2]=Cur_Time0.Time[T_HOUR];
      Save_Cur_Energy_Bak1_Data();      
      Save_LoadData_Index_Bak();
    }

    //ÿ12Сʱ����һ�ε����������ݵ����ݵ�DI��,��Ϊ��������DataFlash��,���12Сʱ��һ��
    if(Cur_Time0.Time[T_HOUR]%12==2 && Cur_Time0.Time[T_HOUR]!=Bak_Hour.Buf[3])
    {
      DEBUG_PRINT(HUCK,DEBUG_0,"Every 12 hours Save_Cur_Energy_Bak2_Data");
      Bak_Hour.Buf[3]=Cur_Time0.Time[T_HOUR];
      Save_Cur_Energy_Bak2_Data(); 
    }
    
    //ÿ12Сʱ�����ѹͳ�Ƶ�������,�����ݴ����������
    if(Cur_Time0.Time[T_HOUR]%12==3 && Cur_Time0.Time[T_HOUR]!=Bak_Hour.Buf[4])
    {
      DEBUG_PRINT(HUCK,DEBUG_0,"Every hour Save_Cur_VolStat_PD_Data");
      Bak_Hour.Buf[4]=Cur_Time0.Time[T_HOUR];    
      Save_Cur_VolStat_PD_Data();
    }
    
    //ÿ12Сʱ�����ѹͳ������,�Լ�����������������,�����ݴ����EEROM��
    if(Cur_Time0.Time[T_HOUR]%12==4 && Cur_Time0.Time[T_HOUR]!=Bak_Hour.Buf[5])
    {
      DEBUG_PRINT(HUCK,DEBUG_0,"Every 12 hour Save_Cur_VolStat_Data,Save_LoadData_Index");
      Bak_Hour.Buf[5]=Cur_Time0.Time[T_HOUR];    
      Save_Cur_VolStat_Data();
      Save_LoadData_Index(); 
    }
  }
}

//���ʷ����л�����,��Ҫ�����¶�ȡ���ֲ���
//New_Scheme,��ʾ�л����÷��ʷ���
//New_Scheme==RATE_SCHEME0����New_Scheme==RATE_SCHEME1
//�ú�������Ҫ�����Ǹ����׷��ʷ�����ز���
void Rate_Scheme_Changed_Proc()
{
  INT8U Re;
  
  Re=CHECK_STRUCT_SUM(Cur_Rate_Info);
  if(ASSERT(A_WARNING,1==Re))
    Check_Data_Avail();
  
  if(ASSERT(A_WARNING,Cur_Rate_Info.Scheme==RATE_SCHEME0 || Cur_Rate_Info.Scheme==RATE_SCHEME1))
  {
    Cur_Rate_Info.Scheme=RATE_SCHEME0;//Ĭ��ʹ�������ʷ���
    SET_STRUCT_SUM(Cur_Rate_Info);
  }
  DEBUG_PRINT(HUCK,DEBUG_0,"Rate_Scheme Changed! Use %dth Scheme",Cur_Rate_Info.Scheme);
  
  Set_Using_Rate_Scheme(Cur_Rate_Info.Scheme);//�������õ�ǰ���ʷ���������״̬��
  Read_Multi_Rate_Para(Cur_Rate_Info.Scheme);//�Ӵ洢���ж�ȡ��ǰ���ʷ�����صĲ��� 
  
  Cal_Cur_Date_Table(CALC_ROM);//���¼���ʱ�α��,�������¶�ȡ��ʱ�α������Date_Table��  
}

//�����л�����
void Rate_Changed_Proc()
{
  INT8U Re;
 
  Re=CHECK_STRUCT_SUM(Cur_Rate_Info);
  if(ASSERT(A_WARNING,1==Re))
    Check_Data_Avail();
  
  DEBUG_PRINT(HUCK,DEBUG_0,"Rate Changed! Use %dth Rate",Cur_Rate_Info.Rate);
  Set_Using_Rate(Cur_Rate_Info.Rate);//���÷���״̬��
}

//���㵱ǰ���ʷ����ͷ��ʣ��Լ��Ƿ��������л���������������л�
//�����´�rom�ж�ȡ��ز�����
void Check_Cur_Rate()
{
  S_Int8U  static Min={CHK_BYTE,0,CHK_BYTE};
  INT8U Re;  
 
  Re = 1;
  Re &= CHECK_STRUCT_VAR(Min);
  Re &= CHECK_STRUCT_VAR(Time_Modify_Flag);
  ASSERT(A_WARNING, 1==Re);
  
  if(Min.Var!=Cur_Time0.Time[T_MIN] || Time_Modify_Flag.Var==1)//ÿ��һ���ӽ���һ�����������
  {
    Time_Modify_Flag.Var = 0;
    Min.Var=Cur_Time0.Time[T_MIN];
    //��鵱ǰ������Ϣ
    Re=CHECK_STRUCT_SUM(Cur_Rate_Info);
    if(ASSERT(A_WARNING,0!=Re))
      Check_Data_Avail();
  
    //Cur_Rate_Info�еķ�����ϢӦ�ú�Rate_Status�еķ�����ϢӦ��һ��
    ASSERT(A_WARNING,Cur_Rate_Info.Rate==Rate_Status.Status[1].Byte);
    ASSERT(A_WARNING,Cur_Rate_Info.Scheme==Rate_Status.Status[0].Byte);
  
    //���㵱ǰӦ��ʹ�õķ��ʷ���,�жϵ�ǰ�׷��ʷ�������������������л�������¸����ʲ���Multi_Rate_Para,�Լ����µ�ǰ��ʱ�α�     
    Calc_Cur_Rate_Scheme(CALC_RAM);//���㵱ǰ���ʷ���
    Calc_Cur_Rate(CALC_RAM);//���㵱ǰӦ��ʹ�õķ���
  }
}

//����ǰ�������ݰ�pTimeʱ��洢����
void _Freeze_Energy_Data(S_HEX_Time *pTime)
{
  //SET_STRUCT_TIME(Cur_Energy,*pTime);//���ṹ���е�ʱ����Ϊ���ݴ洢ʱ��
  Write_HIS_Data(HIS_ENERGY_DATA,pTime,(void *)&Cur_Energy,ENERGY_SAVE_SIZE);
  //SET_STRUCT_TIME(Cur_Energy,Cur_Time0);//�ṹ����ʱ��ָ�Ϊ��ǰʱ��
  OS_TimeDly_Ms(100);//�ó�CPU 

}

//ÿ�³����ն��ᴦ��
void Month_Data_Freeze()
{
  INT8U Re;
  static S_Int8U Min_Bak={CHK_BYTE,0xFF,CHK_BYTE};
  S_HEX_Time TempTime;
  
  //��֤ÿ����ֻ����һ��
  Re=CHECK_STRUCT_VAR(Min_Bak);
  ASSERT(A_WARNING,1==Re);
  
  if(Min_Bak.Var==Cur_Time0.Time[T_MIN])
    return;
  else
    Min_Bak.Var=Cur_Time0.Time[T_MIN];
  
  Re=1;
  Re&=Check_HEX_Time((S_HEX_Time *)&Cur_Time0);
  Re&=CHECK_STRUCT_SUM(Data_Freeze_Time);
  if(ASSERT(A_WARNING,1==Re))
    Check_Data_Avail();
  
  //ʱ�����ݲ���BCD��
  //Re=C((INT8U *)(Data_Freeze_Time.DDHH),2);
  //Re=CHECK_STRUCT_SUM(Data_Freeze_Time);
  //if(ASSERT(A_WARNING,1==Re))
    //Check_Data_Avail();
  
  //����Զ�����ʱ�����ô���
  if(ASSERT(A_WARNING,Data_Freeze_Time.DDHH[0]<=23))
  {
    Data_Freeze_Time.DDHH[0]=0;
    SET_STRUCT_SUM(Data_Freeze_Time);
  }
  if(ASSERT(A_WARNING,Data_Freeze_Time.DDHH[1]>=1 &&\
                      Data_Freeze_Time.DDHH[1]<=31))
  {
    Data_Freeze_Time.DDHH[1]=1;
    SET_STRUCT_SUM(Data_Freeze_Time);
  }
  
  //�ж϶�����ʱ���Ƿ���
  if(Cur_Time0.Time[T_MIN] == 0 &&\
     Cur_Time0.Time[T_HOUR]==Data_Freeze_Time.DDHH[0] &&\
     Cur_Time0.Time[T_DATE]==Data_Freeze_Time.DDHH[1])
  {
    DEBUG_PRINT(HUCK,DEBUG_0,"----------Month Data Freeze Start!----------");
    //��ȡ���¶���ʱ���
    Get_NowMonth_Freeze_Time((S_HEX_Time *)&Cur_Time0,&TempTime);//��ֱֹ��ʹ��Cur_Time0�����ķ������

    //����Ҫ��������ݵ�ʱ������Ϊ����ʱ���
    SET_STRUCT_TIME(Cur_Energy,TempTime);
    SET_STRUCT_TIME(Cur_Demand.Demand[0],TempTime);
    SET_STRUCT_TIME(Cur_Demand.Demand[1],TempTime);
    SET_STRUCT_SUM(Cur_Demand);
    SET_STRUCT_TIME(Cur_VolStat,TempTime);
    
    Freeze_Energy_Data(&TempTime);//�����������
    Freeze_Demand_Data(&TempTime);//������������
    Freeze_VolStat_Data(&TempTime);//�����ѹͳ������

  }
}

//��ʼ����������
void Read_Energy_Data_From_Rom()
{
  INT8U Err=NO_ERR;
  S_Energy *p;
  
  //�ȶ�ȡ����洢������
  //�ٶ���ͨ����
  //��������������
  OS_Sem_Pend(PUB_BUF0_SEM_ID); 
  p=(S_Energy *)Pub_Buf0;
  
  if(Read_Storage_Data(CUR_ENERGY_PD,p,p,sizeof(Pub_Buf0),&Err)!=ENERGY_SAVE_SIZE ||\
    Check_Energy_Data((S_Energy *)p)!=1)
  {
    //��Ҫ��֤�洢��У�����ȷ�����ݱ�����ȷ����Ϊ��ȡ�ɹ�
    DEBUG_PRINT(HUCK,DEBUG_0,"Read CUR_ENERGY_PD data error");
    OS_TimeDly_Ms(500);
    if(Read_Storage_Data(CUR_ENERGY,p,p,sizeof(Pub_Buf0),&Err)!=ENERGY_SAVE_SIZE ||\
       Check_Energy_Data((S_Energy *)p)!=1)
    {
      DEBUG_PRINT(HUCK,DEBUG_0,"Read CUR_ENERGY data error");
      OS_TimeDly_Ms(500);
      if(Read_Storage_Data(CUR_ENERGY_BAK0,p,p,sizeof(Pub_Buf0),&Err)!=ENERGY_SAVE_SIZE ||\
         Check_Energy_Data((S_Energy *)p)!=1)
      {
        DEBUG_PRINT(HUCK,DEBUG_0,"Read CUR_ENERGY_BAK0 data error");
        OS_TimeDly_Ms(500);
        if(Read_Storage_Data(CUR_ENERGY_BAK1,p,p,sizeof(Pub_Buf0),&Err)!=ENERGY_SAVE_SIZE ||\
           Check_Energy_Data((S_Energy *)p)!=1)
        {
          DEBUG_PRINT(HUCK,DEBUG_0,"Read CUR_ENERGY_BAK1 data error");
          if(Read_Storage_Data(CUR_ENERGY_BAK2,p,p,sizeof(Pub_Buf0),&Err)!=ENERGY_SAVE_SIZE ||\
             Check_Energy_Data((S_Energy *)p)!=1)
          {
            DEBUG_PRINT(HUCK,DEBUG_0,"Read CUR_ENERGY_BAK2 data error");
            mem_set(p,0,sizeof(Cur_Energy),p,sizeof(Pub_Buf0));
            Write_Storage_Data(CUR_ENERGY_BAK2,p,ENERGY_SAVE_SIZE);
          }
          Write_Storage_Data(CUR_ENERGY_BAK1,p,ENERGY_SAVE_SIZE);
        }
        Write_Storage_Data(CUR_ENERGY_BAK0,p,ENERGY_SAVE_SIZE);
      }  
      Write_Storage_Data(CUR_ENERGY,p,ENERGY_SAVE_SIZE);
    }
    Write_Storage_Data(CUR_ENERGY_PD,p,ENERGY_SAVE_SIZE);
  }
 
  DIS_PD_INT;
  mem_cpy((void *)&Cur_Energy,p,sizeof(Cur_Energy),(void *)&Cur_Energy,sizeof(Cur_Energy));
  INIT_STRUCT_VAR(Cur_Energy);  
  SET_DATA_READY_FLAG(Cur_Energy);
  SET_STRUCT_SUM(Cur_Energy);
  
#if USE_ENERGY_RAM_BAK
  mem_cpy((void *)&Cur_Energy_Bak,(void *)&Cur_Energy,sizeof(Cur_Energy_Bak),(void *)&Cur_Energy_Bak,sizeof(Cur_Energy_Bak)); 
#endif
  
  EN_PD_INT;
  
  OS_Sem_Post(PUB_BUF0_SEM_ID);   
}
//�ú�����Ҫ��ΪҺ����ʾ��һ��׼������������
//��������̻������¶���Щ����
void Read_Energy_Data_Para_For_Show()
{
  INT8U Rst_Flag;  
  INT8U Err;
  
  //��ȡ����ʱ�洢�ĵ�������,û�ж�ȡ�ɹ����ȡ���ݴ洢������ 
  Rst_Flag=Check_Rst_Flag();
  if(Rst_Flag==POWER_ON_RST || Check_Energy_Data((S_Energy *)&Cur_Energy)==0)//��Դ�ϵ����У��ʹ��������¶������ȡROM�е�����
  {
    DEBUG_PRINT(HUCK,DEBUG_0,"PowerOn Read Energy Data");
    Read_Energy_Data_From_Rom();
  }

  Read_Mode_Word();//��ȡģʽ�֣����ڼ��������й���ģʽ��
  //������ʾС��λ��
  if(Read_Storage_Data(0xC115,(void *)(&Disp_Digs.Energy_Digs),(void *)(&Disp_Digs.Energy_Digs),1,&Err)!=1 || Err!=NO_ERR)
    DEBUG_PRINT(HUCK,DEBUG_0,"Read 0xC125 Para Err");    
  Disp_Digs.Energy_Digs=Bcd2Hex_Byte(Disp_Digs.Energy_Digs);
  SET_STRUCT_SUM(Disp_Digs);
}

//��ʼ����������������
void PowerOn_Read_Data_From_Rom()
{
  INT8U Rst_Flag;
  //��ȡ����ʱ�洢�ĵ�������,û�ж�ȡ�ɹ����ȡ���ݴ洢������ 
  Rst_Flag=Check_Rst_Flag();
  //��ʾ��һ����ǰ�Ѿ���ȡ���ܵ���
  if(Rst_Flag==POWER_ON_RST || Check_Energy_Data((S_Energy *)&Cur_Energy)==0)//��Դ�ϵ����У��ʹ��������¶������ȡROM�е�����
  {
    DEBUG_PRINT(HUCK,DEBUG_0,"PowerOn Read Energy Data");
    Read_Energy_Data_From_Rom();
  }
  
  //��ȡ����ʱ�洢���������ݣ�û�ж�ȡ�ɹ����ȡ���ݴ洢������ 
  if(Rst_Flag==POWER_ON_RST || Check_Demand_Data((S_Demand *)&Cur_Demand)==0)//��Դ�ϵ����У��ʹ��������¶������ȡROM�е�����
  {
    DEBUG_PRINT(HUCK,DEBUG_0,"PowerOn Read Demand Data");
    Read_Demand_Data_From_Rom();
  }
  
  //��ȡ����ʱ�洢������ʱ�����ݣ�û�ж�ȡ�ɹ����ȡ���ݴ洢������
  if(Rst_Flag==POWER_ON_RST || Check_VolStat_Data((S_VolStat *)&Cur_VolStat)==0 ||\
                           Check_VolStat_Data((S_VolStat *)&Total_VolStat)==0)//��Դ�ϵ����У��ʹ��������¶������ȡROM�е����� 
  {
    DEBUG_PRINT(HUCK,DEBUG_0,"PowerOn Read VolStat Data");
    Read_VolStat_Data_From_Rom();
  } 
  
  //��ȡ�������ߴ洢��Ϣ
  if(Rst_Flag==POWER_ON_RST || CHECK_STRUCT_SUM(LoadData_Index)==0)//��Դ�ϵ����У��ʹ��������¶������ȡROM�е����� 
  {
    DEBUG_PRINT(HUCK,DEBUG_0,"PowerOn Read LoadData Index");
    Read_LoadData_Index_Data_From_Rom();
  }
  
  //if(Rst_Flag==POWER_ON_RST || CHECK_STRUCT_SUM(Event_Cumu)==0)//��Դ�ϵ����У��ʹ��������¶������ȡROM�е����� 
  {
    //DEBUG_PRINT(HUCK,DEBUG_0,"PowerOn Read Event_Cumu Data");
    //Read_Event_Cumu_Data_From_Rom();
  }
  
}

//�ϵ�������ݵĶ��ᣬǰ��HIS_ENERGY_DATA_MONTHS����
void PowerOn_Energy_Data_Freeze()
{
  Freeze_Energy_Data((S_HEX_Time *)&Cur_Time0);
}

void Freeze_Energy_Data(S_HEX_Time *pTime)
{
  INT8U i,Err,Re;
  INT16U Len;
  S_HEX_Time TempTime;
  
  Re=Check_HEX_Time(pTime);//��鵱ǰʱ��
  if(ASSERT(A_WARNING,0!=Re))
    Check_Data_Avail();
  
  DEBUG_PRINT(HUCK,DEBUG_0,"----------Freeze Energy Data %d-%d-%d %d:%d----------",\
                           pTime->Time[T_YEAR],pTime->Time[T_MONTH],pTime->Time[T_DATE],pTime->Time[T_HOUR],pTime->Time[T_MIN]);
  
  DEBUG_PRINT(HUCK,DEBUG_0,"Energy Data Freeze, Data Time: ");
  Debug_Print_HEX_Time((INT8U *)Cur_Energy.Time.Time);  
  //<=Cur_Time0�����һ������ʱ���
  Get_Last_Freeze_Time(pTime,&TempTime);
  //��ǰi���µ����ݶ��������ܶ��������ʧ�ܵģ����ж���
  //mem_cpy(&TempTime1,&TempTime,sizeof(S_HEX_Time),&TempTime1,sizeof(TempTime1));//����TempTime��TempTime1
  for(i=0;i<HIS_ENERGY_DATA_MONTHS;i++)
  {
    //����������,֪����ȡ��һ����ȷ��������Ϊ����Ҫ����������    
    OS_Sem_Pend(PUB_BUF_SEM_ID);//����Pub_Buf���ź���
    Len=Read_HIS_Data(HIS_ENERGY_DATA,&TempTime,(void *)Pub_Buf,(void *)Pub_Buf,sizeof(Pub_Buf),&Err);
    OS_Sem_Post(PUB_BUF_SEM_ID);//�ͷ�Pub_Buf���ź���
    
    if(ENERGY_SAVE_SIZE!=Len)
    {
      SET_STRUCT_TIME(Cur_Energy,TempTime);//���õ�������ʱ��ΪTempTime
      DEBUG_PRINT(HUCK,DEBUG_0,"Freeze Energy Data,Time:");
      Debug_Print_HEX_Time(TempTime.Time);
      _Freeze_Energy_Data(&TempTime);     
    }
    else
      break;
    
    Time_Dec(&TempTime,1,UNIT_MON,&TempTime);//ʱ����ǰ��1����
    OS_TimeDly_Ms(20);//��ʱ����������
  }
  SET_STRUCT_TIME(Cur_Energy,Cur_Time0);//�ָ�����ʱ��
  DEBUG_PRINT(HUCK,DEBUG_0,"----------Freeze Energy Data End----------");   
}

//�ϵ粹����(����)����
void PowerOn_MonthData_Freeze()
{
  PowerOn_Energy_Data_Freeze();//��������
  PowerOn_Demand_Data_Freeze();//��������
  PowerOn_VolStat_Data_Freeze();//��ѹͳ������
}

//���籣��������������ݵ�
//�˺�����Ϊ�ǵ���洢�����û����ʱ����
void PowerDown_Save_Energy_Data()
{
  //�������ʱ�洢�ĵ�������,û�ж�ȡ�ɹ����ȡ���ݴ洢������ 
  Write_Storage_Data(CUR_ENERGY_PD,(void *)(&Cur_Energy),ENERGY_SAVE_SIZE);

}

//�������
void PowerDown_Save_Data()
{
  PowerDown_Save_Energy_Data();//�����������
  PowerDown_Save_Demand_Data();//������������
  PowerDown_Save_VolStat_Data(); //�����ѹͳ������
}

#pragma optimize=none
//����ǰ������Ϣ�ȴ�ӡ����
void Debug_Print_Cur_Energy_Info()
{ 
  static S_Int8U Min={CHK_BYTE,0,CHK_BYTE};
  static S_Int8U Counts={CHK_BYTE,0,CHK_BYTE};
  INT8U i,Re;
  
  if(Check_Debug_En()==0)//�ǹ���״̬����ӡ
    return;
  
  if(Cur_Time0.Time[T_MIN]==Min.Var)//ÿ����ִ��һ�θú���
    return;

  Re=CHECK_STRUCT_VAR(Min);
  ASSERT(A_WARNING,1==Re);
  Re=CHECK_STRUCT_VAR(Counts);
  ASSERT(A_WARNING,1==Re);
  
  Min.Var=Cur_Time0.Time[T_MIN];
  
  Clr_Ext_Inter_Dog();
  DEBUG_PRINT(HUCK,DEBUG_0,"----------Cur_Rate_Info-----------");
  DEBUG_PRINT(HUCK,DEBUG_0,"Cur_Time:%d-%d-%d %d:%d,Week:%d",Cur_Time0.Time[T_YEAR],Cur_Time0.Time[T_MONTH],\
              Cur_Time0.Time[T_DATE],Cur_Time0.Time[T_HOUR],Cur_Time0.Time[T_MIN],Cur_Time0.Week);
  DEBUG_PRINT(HUCK,DEBUG_1,"Cur Rate Scheme:%d",Cur_Rate_Info.Scheme);
  DEBUG_PRINT(HUCK,DEBUG_1,"Cur Rate:%d",Cur_Rate_Info.Rate);
  
  if(Cur_Rate_Info.Date_Flag==HOLIDAY)
    DEBUG_PRINT(HUCK,DEBUG_1,"Today is Holiday,Holiday_Index=%d",Cur_Rate_Info.Holiday_Index);
  else if(Cur_Rate_Info.Date_Flag==WEEK_REST_DAY)
    DEBUG_PRINT(HUCK,DEBUG_1,"Today is Week_Rest_Day");
  else if(Cur_Rate_Info.Date_Flag==NORMAL_DAY)
    DEBUG_PRINT(HUCK,DEBUG_1,"Today is Normal_Day,Year_Peirod=%d",Cur_Rate_Info.Year_Period);
  else
    DEBUG_PRINT(HUCK,DEBUG_1,"Today Date_Flag Err");
  
  //��ǰ��ʱ�α�ź͵�ǰ��ʱ��
  DEBUG_PRINT(HUCK,DEBUG_1,"Cur Date_Table:%d Date_Period:%d",\
    Cur_Rate_Info.Date_Table,Cur_Rate_Info.Date_Period);
  //��ǰ�����й���
  DEBUG_PRINT(HUCK,DEBUG_1,"Cur_Pos_Active:%ld",Cur_Energy.Pos_Active[0]);
 
  Counts.Var++;
  if(Counts.Var>=5)//ÿ��5���Ӵ�ӡһ�ε�ǰ����ֵ
  {
    Counts.Var=0;
    
    Clr_Ext_Inter_Dog();
      DEBUG_PRINT(HUCK,DEBUG_1,"|-----------------------------Total_Energy-------------------------|"); 
      DEBUG_PRINT(HUCK,DEBUG_1,"| Rate Pos_Activ Neg_Activ Quad0_Rea Quad1_Rea Quad2_Rea Quad3_Rea |");
    for(i=0;i<=Multi_Rate_Para.Rates;i++)
    {
      DEBUG_PRINT(HUCK,DEBUG_1,"|   %2d %9ld %9ld %9ld %9ld %9ld %9ld |",\
        i,Cur_Energy.Pos_Active[i],Cur_Energy.Neg_Active[i],\
        Cur_Energy.Quad_Reactive[0][i],Cur_Energy.Quad_Reactive[1][i],Cur_Energy.Quad_Reactive[2][i],Cur_Energy.Quad_Reactive[3][i]);
    }
  
    //��ӡ�������
      DEBUG_PRINT(HUCK,DEBUG_1,"|------------------------------------------------------------------|"); 
      
    OS_TimeDly_Ms(50);
   
    Clr_Ext_Inter_Dog();    
      DEBUG_PRINT(HUCK,DEBUG_1,"|-----------------------------Phase_Energy-------------------------|"); 
      DEBUG_PRINT(HUCK,DEBUG_1,"| Phas Pos_Activ Neg_Activ Quad0_Rea Quad1_Rea Quad2_Rea Quad3_Rea |");

    for(i=0;i<3;i++)
    {
      DEBUG_PRINT(HUCK,DEBUG_1,"|    %c %9ld %9ld %9ld %9ld %9ld %9ld |",\
        (INT8S)('A'+i),Cur_Energy.Phase_Pos_Active[i],Cur_Energy.Phase_Neg_Active[i],\
        Cur_Energy.Phase_Quad_Reactive[i][0],Cur_Energy.Phase_Quad_Reactive[i][1],\
        Cur_Energy.Phase_Quad_Reactive[i][2],Cur_Energy.Phase_Quad_Reactive[i][3]);
         
    }
      DEBUG_PRINT(HUCK,DEBUG_1,"|------------------------------------------------------------------|"); 

   }

}

//��ʼ��������������ز���
void Read_Energy_Para_From_Rom()
{
  INT8U Err;
  INT16U Len;
  
  //��ȡ�Զ�������
  Len=Read_Storage_Data(0xC117,(INT8U *)&Data_Freeze_Time,(INT8U *)&Data_Freeze_Time,sizeof(Data_Freeze_Time.DDHH),&Err);
  if(ASSERT(A_WARNING,2==Len && NO_ERR==Err))
    DEBUG_PRINT(HUCK,DEBUG_0,"Read Data_Freeze_Time Error"); 
  
  if(!(Check_BCD_Data((INT8U *)Data_Freeze_Time.DDHH,2) &&
       Data_Freeze_Time.DDHH[0]<0x24 && Data_Freeze_Time.DDHH[1]>0 && Data_Freeze_Time.DDHH[1]<0x32))
  {
    Read_Def_Para(0xC117,(void *)Data_Freeze_Time.DDHH,2,(void *)Data_Freeze_Time.DDHH,sizeof(Data_Freeze_Time.DDHH));
    //mem_cpy((void *)Data_Freeze_Time.DDHH,Def_C117,2,(void *)Data_Freeze_Time.DDHH,sizeof(Data_Freeze_Time.DDHH));
  }
  Bcd2Hex_Buf((INT8U *)&Data_Freeze_Time,S_OFF(S_Data_Freeze_Time,CS),(INT8U *)&Data_Freeze_Time,(INT8U *)&Data_Freeze_Time,S_OFF(S_Data_Freeze_Time,CS));

  SET_STRUCT_SUM(Data_Freeze_Time);  

  //���²��ֶ�ȡ�׷�����ز���,��ȡ��Multi_Rate_Para,Year_Table��Holiday_Table
  Calc_Cur_Rate_Scheme(CALC_ROM);//���㵱ǰ�׷��ʷ���,CALC_ROM��־��ʾ��ROM�ж�ȡ���������ж�
  OS_TimeDly_Ms(100);
  Calc_Cur_Rate(CALC_ROM);//���㵱ǰӦ��ʹ�õķ���
}

void Clear_All_Data()
{
  Set_Def_Energy_Data();
  Set_Def_Demand_Data();  
}

//���������
void Clear_Energy_Data()
{
  if(Check_Clear_Data_Authority()==0)
    return;

  if(CLEAR_ENERGY_FLAG!=Check_Clear_Data_Flag() &&
     CLEAR_ALL_FLAG!=Check_Clear_Data_Flag())
    return;
  
  DEBUG_PRINT(HUCK,DEBUG_0,"Clear_Energy_Data!!!");   
  Set_Def_Energy_Data();
}

//���ĳ�����Ƿ��ǵ���������ز���
INT8U Check_If_Energy_Task_Para(PROTO_DI DI)
{
  if(DI==0xC010 || DI==0xC011)//���ڻ�ʱ�����������Time_Modify_Flag
    return 0;
  else if(DI>=0xC030 && DI<=0xC034)//�й����峣��,�޹����峣�� ��� �û����豸��
    return 0;
  else if(0xC211==DI || 0xC215==DI || 0xC216==DI)//����բ��ʱ
    return 0;
  //else if((DI & 0xFF00)==0xC400 && DI!=0xC41E)//��һ�׹����ڼ���(�������������ն�Ӧ��ʱ�α�0xC41E)
    //return 0;
  //else if((DI & 0xFF00)==0xCC00 && DI!=0xCC1E)//�ڶ��׹����ڼ���(�������������ն�Ӧ��ʱ�α�0xCC1E)
    //return 0;
  else if(ADJ_METER_PUL_VOL_CUR_SPEC<=DI && DI<=ADJ_METER_C_CUR)
    return 0;
  else if((0xC113<=DI && DI<=0xC116) || (0xC123<=DI && DI<=0xC126) || 0xC128==DI)//ѭ��ʱ�����ʾ��Ŀ��
    return 0;
  else if(0xC030==DI || 0xC031==DI)//���峣��
    return 0;
  else if((DI & 0xFF00)==0xC600)//A��B����ʾ��
    return 0;
  
  return 1;
}


//�������Ƿ����޸�
void Check_Energy_Para_Modified()
{
  PROTO_DI DI;
  INT8U Re;
  static S_Int32U Sec_Bak0={CHK_BYTE,0xFF,CHK_BYTE};
  static S_Int32U Sec_Bak={CHK_BYTE,0xFF,CHK_BYTE};
  static S_Int8U Count={CHK_BYTE,0,CHK_BYTE};
  static S_Int8U Init_Para_Flag={CHK_BYTE,0,CHK_BYTE};

  if(Sec_Bak0.Var==Sec_Timer_Pub)//ÿ��Ž�����һ��
    return;

  Sec_Bak0.Var=Sec_Timer_Pub;
  Re=1;
  Re&=CHECK_STRUCT_VAR(Sec_Bak);
  Re&=CHECK_STRUCT_VAR(Count);
  Re&=CHECK_STRUCT_VAR(Init_Para_Flag);
  ASSERT(A_WARNING,1==Re);
  
  OS_TimeDly_Ms(20);
//�����ù��Ĳ����������  
  while(Get_Para_Modify(&DI)==1)
  {
    if(Check_If_Energy_Task_Para(DI))//����ǵ�ǰ������صĲ�������Ҫ���³�ʼ������
    {
      Init_Para_Flag.Var=1;//��Ҫ���³�ʼ������ 
      Sec_Bak.Var=Sec_Timer_Pub;//���ʱ��    
      Count.Var=0;//���¿�ʼ����,10S�����޲������������³�ʼ��������ز���
    }
  }
  
  //�Ƿ���Ҫ���³�ʼ��?
  if(1==Init_Para_Flag.Var && Sec_Bak.Var!=Sec_Timer_Pub)
  {
    Sec_Bak.Var=Sec_Timer_Pub;
    Count.Var++;//�����
  }
  
  //�޸ĵ�ǰ������ز�����10S�����³�ʼ������
  if(Count.Var>=1 && 1==Init_Para_Flag.Var)
  {
    //�����˵�����ز���
    Init_Para_Flag.Var=0;
    Count.Var=0;
    Refresh_Para_From_Rom();//���½�
  }
  
}

//��ʼ��������������صĲ���
void Init_Energy_Demand_Ram_Para()
{
  //��ʼ���ź���

  //��ʼ������״̬��
  Rate_Status.Status[0].Byte=0x01;//�׷��ʷ���0
  Rate_Status.Status[1].Byte=0x01;//��ǰ����Ϊ����1
  SET_STRUCT_SUM(Rate_Status);//����״̬��
  //��ʼ��������Ϣ
  mem_set((void *)&Cur_Rate_Info,0,sizeof(Cur_Rate_Info),(void *)&Cur_Rate_Info,sizeof(Cur_Rate_Info));
  SET_STRUCT_SUM(Cur_Rate_Info);//������Ϣ
  //��ʼ����ʱ�α�
  mem_set((void *)&Date_Table,0,sizeof(Date_Table),(void *)&Date_Table,sizeof(Date_Table));
  SET_STRUCT_SUM(Date_Table);//��ʱ�α�
  
  //��ʼ�������޸ı�־
  //Clear_Flag.Flag=CLEAR_END_FLAG;//�����־,����������ȵı�־
  //SET_STRUCT_SUM(Clear_Flag);
  
  //����ȫ�ֻ�������ͷβ�����ֽ�
  INIT_STRUCT_VAR(_Pub_Buf);
  INIT_STRUCT_VAR(_Pub_Buf0);
  INIT_STRUCT_VAR(Pub_Timer);
  Energy_Cumu_Counts.Var=0; //�����ۼӴ���,�����Գ�����
  INIT_STRUCT_VAR(Energy_Cumu_Counts);
  
  Chk_Data_Flag.Chk_Flag=0;
  SET_STRUCT_SUM(Chk_Data_Flag);
}

void Init_Sem()
{
  //��ʼ���ź���
  OS_Sem_Clr();
  OS_Sem_Init(PUB_BUF_SEM_ID,0);//��ʼ��Pub_Buf�����ź���
  OS_Sem_Init(PUB_RW_ROM_ID,0);//��ʼ����дROM���ź���  
}
//��ʼ���ڴ����ز���
/*
void Init_Ram_Para_()
{
  Init_Sem();//��ʼ���ź���
  Init_Clock_Ram_Para();//��ʼ��ʼ���ڴ�
  Init_Energy_Demand_Ram_Para();//��ʼ��������������ڴ�
  Init_VolStat_Ram_Para();
  Init_Data_Trans_Ram_Para();//���ݴ�����ر�����ʼ��
}
*/

//��ʼ��������ز���
void Read_Para_From_Rom()
{
  Read_Energy_Para_From_Rom();//��ʼ�������ۼ���ز���
  Read_Demand_Para_From_Rom();//��ʼ��������ز���
  Read_Data_Trans_Para_From_Rom();//����ת����Ҫ����ز�����ʼ�� 
  Read_VolStat_Para_From_Rom();//��ѹͳ����ز���
  Read_LoadData_Para_From_Rom();//����������ز���
  Read_Power_Ctrl_Para_From_Rom();//��ȡ���ɿ��Ʋ���
  Read_Freeze_Data_Para_From_Rom();
}

void Refresh_Para_From_Rom()
{
  Read_Energy_Para_From_Rom();//��ʼ�������ۼ���ز���
  OS_TimeDly_Ms(100);
  Read_Demand_Para_From_Rom();//��ʼ��������ز���
  OS_TimeDly_Ms(100);
  Read_Data_Trans_Para_From_Rom();//����ת����Ҫ����ز�����ʼ��
  OS_TimeDly_Ms(100);
  Read_VolStat_Para_From_Rom();//��ѹͳ����ز���
  OS_TimeDly_Ms(100);
  Read_LoadData_Para_From_Rom();//����������ز���
  OS_TimeDly_Ms(100);
  Read_Power_Ctrl_Para_From_Rom();//��ȡ���ɿ��Ʋ���
  OS_TimeDly_Ms(100);
  Read_Freeze_Data_Para_From_Rom();  
  
}

//����������ʱ����
void PSW_Lock_Proc()
{
  INT8U Re;
  static S_Int8U Min_Bak={CHK_BYTE,0xFF,CHK_BYTE};
  
  if(Min_Bak.Var!=Cur_Time0.Time[T_MIN])
  {
    Min_Bak.Var=Cur_Time0.Time[T_MIN];
    
    Re=CHECK_STRUCT_SUM(PSW_Err_Info);
    if(1!=Re || PSW_Err_Info.Err_Times>99 ||\
      PSW_Err_Info.Lock_Mins>1440 || PSW_Err_Info.Clr_Err_Times_Mins>1440)
      Clear_PSW_Err_Info();

    if(Check_Meter_Factory_Status())//�ڹ���״̬���������
    {
      Clear_PSW_Err_Info();
      Clr_Event_Instant(ID_EVENT_METER_LOCK);
    }
    
    if(PSW_Err_Info.Lock_Mins>0)//����ʱ��ݼ�
    {
      Set_Event_Instant(ID_EVENT_METER_LOCK);  //�������¼�����
      PSW_Err_Info.Lock_Mins--;
      if(PSW_Err_Info.Lock_Mins==0)
      {
        PSW_Err_Info.Err_Times=0;//����������0
        Clr_Event_Instant(ID_EVENT_METER_LOCK);
      }
    }
    
    if(PSW_Err_Info.Clr_Err_Times_Mins>0)//1440���Ӻ��������Զ���0
    {
      PSW_Err_Info.Clr_Err_Times_Mins--;
      if(PSW_Err_Info.Clr_Err_Times_Mins==0)
        PSW_Err_Info.Err_Times=0;
    }
    
    if(PSW_Err_Info.Set_En_Mins>0)//�������ù���ʱ��
    {
      PSW_Err_Info.Set_En_Mins--;
    }
    
    SET_STRUCT_SUM(PSW_Err_Info);
  }
} 
//����Ƿ�����������Ҫ
//������ǰ��Ҫ����Set_Clear_Data_Flag������������
void Check_Clear_Data()
{
  INT32U Flag;
  
  Check_Man_Clr_Demand();//�ֶ����������
  
  Flag=Check_Clear_Data_Flag();//CHECK_STRUCT_SUM(Clear_Flag);
  //�����
  if(CLEAR_ALL_FLAG==Flag)
  {
    Clear_Energy_Data();
    Clear_All_Demand_Data();
    //Clear_VolStat_Data();
    //Clear_Event_Data();
    Clear_Data_End();//���������
    OS_TimeDly_Ms(100);//�ó�CPU��ͨ������    
  }
  else if(CLEAR_ENERGY_FLAG==Flag)
  {
    Clear_Energy_Data();
    Clear_Data_End();//���������
    OS_TimeDly_Ms(100);//�ó�CPU��ͨ������
    //DEBUG_PRINT(HUCK,DEBUG_0,"Clear_Energy_Data");
  }
  //������
  else if(CLEAR_DEMAND_FLAG==Flag)
  {
    Clear_Cur_Demand_Data();
    Clear_Data_End();//���������
    OS_TimeDly_Ms(100);//�ó�CPU��ͨ������ 
  }
  //���ѹͳ��
  else if(CLEAR_VOLSTAT_FLAG==Flag)
  {
    Clear_VolStat_Data();
    Clear_Data_End();//���������
    OS_TimeDly_Ms(100);//�ó�CPU��ͨ������
    //DEBUG_PRINT(HUCK,DEBUG_0,"Clear_VolStat_Data");     
  }
  else if(CLEAR_EVENT_FLAG==Flag)
  {
    Clear_Event_Data(); 
    Clear_Data_End();//���������
    OS_TimeDly_Ms(100);//�ó�CPU��ͨ������
  }
}

void Energy_Task_Ram_Init()
{
  Init_Sem();//��ʼ���ź���
  Init_Clock_Ram_Para();//��ʼ��ʼ���ڴ�
  Init_Energy_Demand_Ram_Para();//��ʼ��������������ڴ�
  Init_VolStat_Ram_Para();//��ѹͳ�Ʊ�����ʼ��
  Init_Data_Trans_Ram_Para();//���ݴ�����ر�����ʼ��  
  Init_Low_Power_Ram();
}

extern INT8U Check_Imp_Data_Storage();
//����������������ĳ�ʼ��,�ó�ʼ��ֻ���������е��ã��ڸ������񴴽�ǰ����
void Energy_Demand_Task_Init()
{
  if(Check_Sys_Status()==SYS_NORMAL)//ϵͳ��Դ����������²Ž������ݶ������������
  {
   //Check_Imp_Data_Storage();
    //Check_Sys_Storage();//�洢���Լ�
    //Check_Boot_On_Flag();//�ж��Ƿ��ǵ�һ���ϵ磬��������Ĭ�ϲ���
    //Init_Clock();//��ʼ��ʱ��
    Read_Para_From_Rom();//��ȡ�洢��ROM�еĲ���,�˺���ǰ��Ҫ�ȶ�ȡ��ʱ��!
    Clock_Update();//���»�ȡʱ��,��Ϊǰ��Ķ��������õ��ܶ�ʱ��
  }
  else
  {
    //�ڻ��ѵ������û�ж�ȡ�������������������������Ҫ��ȡ
    Read_Mode_Word();//ģʽ��
    Read_Data_Trans_Para_From_Rom();//����ת����ز���
  }
}

void Task_Switch_Hook()
{
  static INT32U Ms10_Timer=0;
  static INT32U Max=0;
  static INT32U Temp=1000;

  if(Ms10_Timer_Pub>Ms10_Timer && Ms10_Timer_Pub-Ms10_Timer>Max)
    Max=Ms10_Timer_Pub-Ms10_Timer;
  
  if(Max>Temp)
    Max=Max;
  Ms10_Timer=Ms10_Timer_Pub;
}

//��ӡ����������Ϣ
void Print_Energy_Demand_Info()
{
  Debug_Print_Cur_Energy_Info(); 
  Debug_Print_Cur_Demand_Info();
}
/*
void Test_Cur_Demand_Rate_Data()
{
  INT8U i;

  for(i=0;i<4;i++)
  {
    Cur_Demand.Rate=i+1;
    Save_Cur_Demand_Data();    
  }

  for(i=0;i<4;i++)
  {
    Cur_Demand.Rate=i+1;
    Read_Demand_Rate_Data(i+1,(void *)&Cur_Demand.Demand[0],(void *)&Cur_Demand.Demand[0],sizeof(Cur_Demand.Demand[0]));    
  }  
}
*/
//������������
//��ʵ���˼�������������Ȼ����˵�ѹͳ�ơ��������ߡ�ʱ�Ӵ���ȹ���
void Energy_Demand_Task(INT8U Flag)
{
  if(Flag!=0)
  {
    PowerOn_Read_Data_From_Rom();//�������ݶ�ȡ��ʼ��
    if(Check_Sys_Status()==SYS_NORMAL)//ϵͳ��Դ����������²Ž������ݶ������������
    {
      PowerOn_MonthData_Freeze();//���������ݽ��㣬ǰHIS_ENERGY_ENERGY_DATA_MONTHS���µ�����  
      PowerOn_Demand_Proc(); //�ϵ�����������
        
      OS_Waitfor_Sec(1==Measu_Status_Mode_ToPub_PUCK.DataRecFlg,5);//�ȴ���������׼���ã�
      if(1!=Measu_Status_Mode_ToPub_PUCK.DataRecFlg)
      {
        ASSERT(A_WARNING,0);
        OS_Waitfor(1==Measu_Status_Mode_ToPub_PUCK.DataRecFlg);
      }
    }

////////////////////////
/*
    INT8U a=0;  
    while(a<=50)
    {
      Event_Data_Proc(a,EVENT_OCCUR);
      Clear_Task_Dog();
      OS_TimeDly_Ms(100);
      Event_Data_Proc(a,EVENT_END);
      DEBUG_PRINT(HUCK,DEBUG_0,"a=%d",a);
      a++;      
    }
*/
/////////////////////////    
    return;
  }
  else
  {
    if(Check_Sys_Status()!=SYS_NORMAL)//�����ڻ��ѵ�����£������κ����� 
    {
      while(1)
      Task_Sleep();
    }
    else
    {
      //Clear_Task_Dog();//��������
  
      Clock_Proc();//ʱ�Ӵ�����ʱˢ��ʱ��
      Check_Energy_Para_Modified();//�������Ƿ����޸�
  
      PSW_Lock_Proc();//����������ʱ
      Check_Energy_Demand_Task_Data_Avail();//��鱾�����������ݵĺϷ���
      
      //Check_Cur_RateӦ�÷���Month_Data_Freeze��Auto_Save_Cur_Data�����ĺ��棬��֤�Ŀ��ʱ���ú�����ִ��
      Check_Cur_Rate();//��鵱ǰ����
      
      Month_Data_Freeze();//ÿ���Զ��������
      Auto_Save_Cur_Data();//�����Զ����浱ǰ����
      
      Cumulative_Energy();//ÿ���ۼӵ���
  
      Demand_Proc();//�������ݴ���

      VolStat_Proc();//��ѹͳ�ƴ���
      LoadData_Proc();//�������ߴ���
      Period_Freeze_Data_Proc();//���ڶ�������
      Check_Clear_Data();//����Ƿ����������������

      Power_Ctrl_Proc();//���ɿ��ƴ���
      
      Event_Cumu_Mins_Proc();//�¼����ۼ�
      Extend_Main_Proc();
      //Debug_Print_Cur_Energy_Info();//����ǰ������Ϣ��������Կ�
      Print_Energy_Demand_Info();
    }
  }
 
}

//��鵱���Ƿ��ǵ����λ�ģ����������е������ݱ���
/*
void Last_Power_Down_Proc()
{
  //INT32U Status;

  if(Check_Sys_Status()==SYS_NORMAL_TO_SLEEP)
  {
    PowerDown_Save_Data();//�������
    //���汨������,PUCK�ṩ����
  }
}
*/
/*
INT8U Temp[1000];
void Energy_Demand_Task()
{
  INT16U Len,DI;
  INT8U Err;
  
  DI=0x7000;
  Multi_Rate_Para.Rates=8;
  INT8U i;
  for(i=0;i<=8;i++)
  {
    Cur_Energy.Pos_Active[i]=i*111;
    Cur_Energy.Neg_Active[i]=i*1111; 
    Cur_Energy.Quad_Reactive[0][i]=i*1111;
    Cur_Energy.Quad_Reactive[1][i]=i*2222;
    Cur_Energy.Quad_Reactive[2][i]=i*3333;
    Cur_Energy.Quad_Reactive[3][i]=i*4444;
  }
  
  for(i=0;i<3;i++)
  {
    Cur_Energy.Phase_Pos_Active[i]=i*111;
    Cur_Energy.Phase_Neg_Active[i]=i*222;
    Cur_Energy.Phase_Pos_Reactive[i]=i*333; 
    Cur_Energy.Phase_Neg_Reactive[i]=i*444;
  }
  Len=sizeof(Cur_Energy.Time);
  printf("Len=%d",Len);
  while(1)
  {
    
    Len=Get_DLT645_Data(DI,Temp,Temp,sizeof(Temp),&Err);
    if(Len>0)
    {
      DEBUG_PRINT(HUCK,DEBUG_0,"Get 0x%x Data Len=%d",Len);
      DEBUG_BUF_PRINT(Temp,Len,PRINT_HEX,8);
    }
  }
}
*/

#undef ENERGY_C
