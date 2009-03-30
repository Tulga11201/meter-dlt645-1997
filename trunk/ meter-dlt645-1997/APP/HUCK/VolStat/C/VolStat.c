#define VOLSTAT_C
#include "Includes.h"

void Read_VolStat_Para_From_Rom()
{
  INT8U Err;
  INT8U Temp[12];

  if(Read_Storage_Data(0xC213,(void *)Temp,(void *)Temp,sizeof(Temp),&Err)!=12 || Err!=NO_ERR)
    DEBUG_PRINT(HUCK,DEBUG_0,"Read 0xC213 Para Err");    
  //��Լ��ѹ����Ϊ2λС����puck�ṩ��ѹ����Ϊ4λС�����������ҪX100
  VolStat_Para.Qual_Upper_Limit=Bcd2Hex(Temp,3)*VOL_RATIO;
  VolStat_Para.Qual_Lower_Limit=Bcd2Hex(Temp+3,3)*VOL_RATIO;
  VolStat_Para.Exam_Upper_Limit=Bcd2Hex(Temp+6,3)*VOL_RATIO;
  VolStat_Para.Exam_Lower_Limit=Bcd2Hex(Temp+9,3)*VOL_RATIO;
  
  SET_STRUCT_SUM(VolStat_Para); 
}

//��ѹͳ�ƴ������
void VolStat_Proc()
{
  INT8U i,Re;
  static S_Int8U Min_Bak={CHK_BYTE,0xFF,CHK_BYTE};
  static S_Int32U Sec_Bak={CHK_BYTE,0xFFFFFFFF,CHK_BYTE};
  
  MEASU_INSTANT *p;//��ѹ��4λС��,VolStat_Para�еĵ�ѹ����Ҳ�Ѿ�ת��Ϊ��4λС��

  Re=1;
  Re&=CHECK_STRUCT_VAR(Min_Bak);
  Re&=CHECK_STRUCT_VAR(Sec_Bak);
  
  if(Min_Bak.Var==0xFF)//��һ�ν���ú�������Ҫ��1���Ӻ������Ӽ���
    Min_Bak.Var=Cur_Time0.Time[T_MIN];
  
  //ÿ�����и�����
  if(Min_Bak.Var!=Cur_Time0.Time[T_MIN])
  {
    DIS_PD_INT;//�ص����ж�
    Min_Bak.Var=Cur_Time0.Time[T_MIN];
    for(i=0;i<3;i++)//����ֱ𿼺�
    {
      if(i==1 && Get_SysParse_Mode()!=PARSE_341)//331����²���B����п���
      {
        //��B��ͳ�������0
        Cur_VolStat.Total_Time[i]=0;
        Cur_VolStat.Upper_Time[i]=0;
        Cur_VolStat.Lower_Time[i]=0;
        Cur_VolStat.Qual[i]=0;
          
        Total_VolStat.Total_Time[i]=0;
        Total_VolStat.Upper_Time[i]=0;
        Total_VolStat.Lower_Time[i]=0; 
        Total_VolStat.Qual[i]=0;
        continue;
      }
      //�÷����ڵ�ѹ�������ڿ��˷�Χ�ڲŽ���ͳ��
      if(VolStat_Count.Exam_Upper[i]==0 && VolStat_Count.Exam_Lower[i]==0)
      {  
        //�÷�����û�з���һ�ε�ѹ����������Ҳû�з���һ�ε�ѹ����������
        //��������Ϊ��ѹ�ڿ��˷�Χ��
        Cur_VolStat.Total_Time[i]++;//�����ʱ��
        Total_VolStat.Total_Time[i]++;//�ܼ��ʱ��
        
        if(0!=VolStat_Count.Qual_Upper[i] ||\
           0!=VolStat_Count.Qual_Lower[i])//��ѹ���ϸ�
        {
          if(VolStat_Count.Qual_Upper[i]>VolStat_Count.Qual_Lower[i])//��ѹ����
          {
            Cur_VolStat.Upper_Time[i]++;
            Total_VolStat.Upper_Time[i]++;
          }
          else
          {
            Cur_VolStat.Lower_Time[i]++;
            Total_VolStat.Lower_Time[i]++;
          }
        }
      }
      //������൱�µ�ѹ�ϸ���
      if(Cur_VolStat.Total_Time[i]!=0 &&\
         Cur_VolStat.Total_Time[i] > Cur_VolStat.Upper_Time[i] + Cur_VolStat.Lower_Time[i])
        Cur_VolStat.Qual[i]=(Cur_VolStat.Total_Time[i]-Cur_VolStat.Upper_Time[i]-Cur_VolStat.Lower_Time[i])*10000/Cur_VolStat.Total_Time[i];
      else
         Cur_VolStat.Qual[i]=0;
      //�����ܵ�ѹ�ϸ���
      if(Total_VolStat.Total_Time[i]!=0 &&\
         Total_VolStat.Total_Time[i] > Total_VolStat.Upper_Time[i] + Total_VolStat.Lower_Time[i])
        Total_VolStat.Qual[i]=(Total_VolStat.Total_Time[i]-Total_VolStat.Upper_Time[i]-Total_VolStat.Lower_Time[i])*10000/Total_VolStat.Total_Time[i];
      else
        Total_VolStat.Qual[i]=0;      
    }
    

    SET_STRUCT_SUM(Cur_VolStat);
    SET_STRUCT_SUM(Total_VolStat);
    //ÿ���ӹ�ȥ���÷����ڵ�ͳ��������0
    mem_set((void *)&VolStat_Count,0,sizeof(VolStat_Count),(void *)&VolStat_Count,sizeof(VolStat_Count));
    EN_PD_INT;//�������ж�
  }
  
  //ÿ��Ƚ�һ�µ�ǰ��ѹֵ
  if(Sec_Bak.Var!=Sec_Timer_Pub)
  {
    Sec_Bak.Var=Sec_Timer_Pub;

    p=(MEASU_INSTANT *)&Measu_InstantData_ToPub_PUCK;//˲ʱ������
  /////////��ѹ�ϸ�ͳ��///////////
    //A��
   if(p->Volt.A<VolStat_Para.Exam_Upper_Limit &&\
      p->Volt.A>VolStat_Para.Exam_Lower_Limit)
    {
      if(p->Volt.A>VolStat_Para.Qual_Upper_Limit)//A�೬����
      {
        VolStat_Count.Qual_Upper[0]++;
        Event_Vol_Cur.Qual_Up_Vol[0]=p->Volt.A;
        SET_STRUCT_SUM(Event_Vol_Cur);
        Set_Event_Instant(ID_EVENT_A_VOLT_MAX);//֪ͨ�¼�����
        Clr_Event_Instant(ID_EVENT_A_VOLT_MIN);
      }
      else if(p->Volt.A<VolStat_Para.Qual_Lower_Limit)//A�೬����
      {
        VolStat_Count.Qual_Lower[0]++;
        Event_Vol_Cur.Qual_Low_Vol[0]=p->Volt.A;
        SET_STRUCT_SUM(Event_Vol_Cur);
        Set_Event_Instant(ID_EVENT_A_VOLT_MIN);//֪ͨ�¼�����  
        Clr_Event_Instant(ID_EVENT_A_VOLT_MAX);
      }
      else
      {
        Clr_Event_Instant(ID_EVENT_A_VOLT_MAX);//֪ͨ�¼�����
        Clr_Event_Instant(ID_EVENT_A_VOLT_MIN);      
      }
    }
   else
   {
        Clr_Event_Instant(ID_EVENT_A_VOLT_MAX);//֪ͨ�¼�����
        Clr_Event_Instant(ID_EVENT_A_VOLT_MIN);     
   }
    
    if(Get_SysParse_Mode()==PARSE_341)//341��Ŷ�B�����ͳ��
    {
       if(p->Volt.B<VolStat_Para.Exam_Upper_Limit &&\
          p->Volt.B>VolStat_Para.Exam_Lower_Limit)
      {      
        //B��
        if(p->Volt.B>VolStat_Para.Qual_Upper_Limit)//B�೬����
        {
          VolStat_Count.Qual_Upper[1]++;
          Event_Vol_Cur.Qual_Up_Vol[1]=p->Volt.B;
          SET_STRUCT_SUM(Event_Vol_Cur);
          Set_Event_Instant(ID_EVENT_B_VOLT_MAX);//֪ͨ�¼�����
          Clr_Event_Instant(ID_EVENT_B_VOLT_MIN);//֪ͨ�¼�����
        }
        else if(p->Volt.B<VolStat_Para.Qual_Lower_Limit)//B�೬����
        {
          VolStat_Count.Qual_Lower[1]++;
          Event_Vol_Cur.Qual_Low_Vol[1]=p->Volt.B;
          SET_STRUCT_SUM(Event_Vol_Cur);
          Set_Event_Instant(ID_EVENT_B_VOLT_MIN);//֪ͨ�¼�����
          Clr_Event_Instant(ID_EVENT_B_VOLT_MAX);//֪ͨ�¼�����
        }
        else
        {
          Clr_Event_Instant(ID_EVENT_B_VOLT_MIN);//֪ͨ�¼�����
          Clr_Event_Instant(ID_EVENT_B_VOLT_MAX);//֪ͨ�¼�����      
        }
      }
      else
      {
          Clr_Event_Instant(ID_EVENT_B_VOLT_MIN);//֪ͨ�¼�����
          Clr_Event_Instant(ID_EVENT_B_VOLT_MAX);//֪ͨ�¼�����        
      }
    }
    //C��
    if(p->Volt.B<VolStat_Para.Exam_Upper_Limit &&\
        p->Volt.B>VolStat_Para.Exam_Lower_Limit)
    {   
      if(p->Volt.C>VolStat_Para.Qual_Upper_Limit)//C�೬����
      {
        VolStat_Count.Qual_Upper[2]++;
        Event_Vol_Cur.Qual_Up_Vol[2]=p->Volt.C;
        SET_STRUCT_SUM(Event_Vol_Cur);
        Set_Event_Instant(ID_EVENT_C_VOLT_MAX);//֪ͨ�¼�����
        Clr_Event_Instant(ID_EVENT_C_VOLT_MIN);//֪ͨ�¼�����      
      }
      else if(p->Volt.C<VolStat_Para.Qual_Lower_Limit)//C�೬����
      {
        VolStat_Count.Qual_Lower[2]++;
        Event_Vol_Cur.Qual_Low_Vol[2]=p->Volt.C;
        SET_STRUCT_SUM(Event_Vol_Cur);
        Set_Event_Instant(ID_EVENT_C_VOLT_MIN);//֪ͨ�¼�����
        Clr_Event_Instant(ID_EVENT_C_VOLT_MAX);//֪ͨ�¼�����
      }
      else
      {
        Clr_Event_Instant(ID_EVENT_C_VOLT_MIN);//֪ͨ�¼�����
        Clr_Event_Instant(ID_EVENT_C_VOLT_MAX);//֪ͨ�¼�����     
      }
    }
    else
    {
        Clr_Event_Instant(ID_EVENT_C_VOLT_MIN);//֪ͨ�¼�����
        Clr_Event_Instant(ID_EVENT_C_VOLT_MAX);//֪ͨ�¼�����      
    }
    
  /////////��ѹ����ͳ��///////////////
    if(p->Volt.A>VolStat_Para.Exam_Upper_Limit)
      VolStat_Count.Exam_Upper[0]++;
    else if(p->Volt.A<VolStat_Para.Exam_Lower_Limit)
      VolStat_Count.Exam_Lower[0]++;
    
    if(p->Volt.B>VolStat_Para.Exam_Upper_Limit)
      VolStat_Count.Exam_Upper[1]++;
    else if(p->Volt.B<VolStat_Para.Exam_Lower_Limit)
      VolStat_Count.Exam_Lower[1]++;
    
    if(p->Volt.C>VolStat_Para.Exam_Upper_Limit)
      VolStat_Count.Exam_Upper[2]++;
    else if(p->Volt.C<VolStat_Para.Exam_Lower_Limit)
      VolStat_Count.Exam_Lower[2]++;  
   } 
}

//�뵱�µ�ѹͳ������
void Set_Def_Cur_VolStat_Data()
{
  //if(Check_Meter_Factory_Status()==0)//��ǰ���ǹ���״̬���Ƴ�
    //return;
  //����ʼ����д��洢����  
  DEBUG_PRINT(HUCK,DEBUG_0,"Set Def VolStat Data");
  mem_set((void *)&Cur_VolStat,0,sizeof(Cur_VolStat),(void *)&Cur_VolStat,sizeof(Cur_VolStat));
 
  INIT_STRUCT_VAR(Cur_VolStat);
  SET_DATA_READY_FLAG(Cur_VolStat);   
  SET_STRUCT_SUM(Cur_VolStat);
  
  mem_set((void *)&Total_VolStat,0,sizeof(Total_VolStat),(void *)&Total_VolStat,sizeof(Total_VolStat));
  
  INIT_STRUCT_VAR(Total_VolStat);
  SET_DATA_READY_FLAG(Total_VolStat); 
  SET_STRUCT_SUM(Total_VolStat); 
  
  if(Check_Meter_Factory_Status()==0)//��ǰ���ǹ���״̬���Ƴ�
    return;  
  Save_Cur_VolStat_Data();
  Save_Cur_VolStat_PD_Data();  
  
}

//����Ĭ�ϵĵ�ѹͳ������
void Set_Def_VolStat_Data()
{
  INT8U i;
  Set_Def_Cur_VolStat_Data();
  
  for(i=0;i<HIS_VOLSTAT_DATA_MONTHS;i++)
  {
    Write_Storage_Data(HIS_VOLSTAT+i,(void *)&Cur_VolStat,sizeof(Cur_VolStat)); 
  }
}

//���浱ǰ��ѹͳ������
void Save_Cur_VolStat_Data()
{  
  if(CHECK_STRUCT_SUM(Cur_VolStat))
    Write_Storage_Data(CUR_VOLSTAT,(void *)(&Cur_VolStat),sizeof(Cur_VolStat));
  else
    ASSERT(A_WARNING,0);
  
  OS_TimeDly_Ms(100);
  if(CHECK_STRUCT_SUM(Total_VolStat))
    Write_Storage_Data(TOTAL_VOLSTAT,(void *)(&Total_VolStat),sizeof(Total_VolStat));
  else
    ASSERT(A_WARNING,0);
  
  OS_TimeDly_Ms(100);    
}

//���浱ǰ��ѹͳ������
void Save_Cur_VolStat_PD_Data()
{ 
  if(Check_VolStat_Data((S_VolStat *)&Cur_VolStat))
    Write_Storage_Data(CUR_VOLSTAT_PD,(void *)(&Cur_VolStat),sizeof(Cur_VolStat));
  else
    ASSERT(A_WARNING,0);
  
  if(Check_VolStat_Data((S_VolStat *)&Total_VolStat))
    Write_Storage_Data(TOTAL_VOLSTAT_PD,(void *)(&Total_VolStat),sizeof(Total_VolStat));
  else
    ASSERT(A_WARNING,0);
}

//���浱ǰ��ѹͳ������
//�˺�����Ϊ�ǵ���洢�����û����ʱ����
void PowerDown_Save_VolStat_Data()
{  
  Write_Storage_Data(CUR_VOLSTAT_PD,(void *)(&Cur_VolStat),sizeof(Cur_VolStat));
  Write_Storage_Data(TOTAL_VOLSTAT_PD,(void *)(&Total_VolStat),sizeof(Total_VolStat));
}

//����ѹͳ�������Ƿ���ȷ
INT8U Check_VolStat_Data(S_VolStat *pVolStat)
{
  INT8U Re;
  
  Re=1;
  Re&=(pVolStat->Head==CHK_BYTE && pVolStat->Tail==CHK_BYTE)?1:0;  
  Re&=Check_STRUCT_Sum(pVolStat,sizeof(S_VolStat),pVolStat->CS,sizeof(pVolStat->CS));
  Re&=(pVolStat->Data_Ready_Flag==DATA_READY)?1:0;
  if(ASSERT(A_WARNING,0!=Re))
    return 0;  
  return Re;
}

//��ROM�ж�ȡ��ѹͳ������
void Read_VolStat_Data_From_Rom()
{
  INT8U Err;
  S_VolStat *p;
  
  //�ȶ�ȡ����洢������
  //�ٶ���ͨ����
  //����ǰ��ѹ�������
  OS_Sem_Pend(PUB_BUF0_SEM_ID); 
  p=(S_VolStat *)Pub_Buf0;
  
  if(Read_Storage_Data(CUR_VOLSTAT_PD,p,p,sizeof(Pub_Buf0),&Err)\
    !=sizeof(Cur_VolStat) || Check_VolStat_Data(p)!=1)
  {
    DEBUG_PRINT(HUCK,DEBUG_0,"Read CUR_VOLSTAT_PD data error");
    OS_TimeDly_Ms(500);
    if(Read_Storage_Data(CUR_VOLSTAT,p,p,sizeof(Pub_Buf0),&Err)\
      !=sizeof(Cur_VolStat) || Check_VolStat_Data(p)!=1)//�ò�����Ĭ�ϲ�����,ʵ���ϲ���������������
    {
        DEBUG_PRINT(HUCK,DEBUG_0,"Read CUR_VOLSTAT data error");
        //������еı��������ݶ�û����������Ϊ�ǵ�һ���ϵ磬������0
        mem_cpy(p,(void *)Def_VolStat,sizeof(Cur_VolStat),p,sizeof(Pub_Buf0));
    }
  }
  DIS_PD_INT;
  mem_cpy((void *)&Cur_VolStat,p,sizeof(Cur_VolStat),(void *)&Cur_VolStat,sizeof(Cur_VolStat));
  INIT_STRUCT_VAR(Cur_VolStat);
  SET_DATA_READY_FLAG(Cur_VolStat);
  SET_STRUCT_SUM(Cur_VolStat);
  EN_PD_INT;
  //���ܵ�ѹ�������
  if(Read_Storage_Data(TOTAL_VOLSTAT_PD,p,p,sizeof(Total_VolStat),&Err)\
    !=sizeof(Total_VolStat) || Check_VolStat_Data(p)!=1)
  {
    DEBUG_PRINT(HUCK,DEBUG_0,"Read TOTAL_VOLSTAT_PD data error");
    OS_TimeDly_Ms(500);
    if(Read_Storage_Data(TOTAL_VOLSTAT,p,p,sizeof(Total_VolStat),&Err)\
      !=sizeof(Total_VolStat) || Check_VolStat_Data(p)!=1)//�ò�����Ĭ�ϲ�����,ʵ���ϲ���������������
    {
        DEBUG_PRINT(HUCK,DEBUG_0,"Read TOTAL_VOLSTAT data error");
        //������еı��������ݶ�û����������Ϊ�ǵ�һ���ϵ磬������0
        mem_cpy(p,(void *)Def_VolStat,sizeof(Total_VolStat),p,sizeof(Pub_Buf0));
        //SET_STRUCT_SUM(Total_VolStat);         
    }
  } 
  DIS_PD_INT;
  mem_cpy((void *)&Total_VolStat,p,sizeof(Total_VolStat),(void *)&Total_VolStat,sizeof(Total_VolStat));
  INIT_STRUCT_VAR(Total_VolStat);
  SET_DATA_READY_FLAG(Total_VolStat);
  SET_STRUCT_SUM(Total_VolStat);
  EN_PD_INT;  
  
  OS_Sem_Post(PUB_BUF0_SEM_ID);
}

//����ǰ��ѹͳ�����ݶ��ᣬpTime���붳��ʱ�̣�һ����ǵ�ǰʱ��
void Freeze_VolStat_Data(S_HEX_Time *pTime)
{
  INT8U Re;
  S_HEX_Time TempTime;
  INT8U Err;
  
  DEBUG_PRINT(HUCK,DEBUG_0,"----------Freeze VolStat Data %d-%d-%d %d:%d----------",\
                           pTime->Time[T_YEAR],pTime->Time[T_MONTH],pTime->Time[T_DATE],pTime->Time[T_HOUR],pTime->Time[T_MIN]);
  
  DEBUG_PRINT(HUCK,DEBUG_0,"VolStat Data Freeze, Data Time: ");
  Debug_Print_HEX_Time(Cur_VolStat.Time.Time);
      
  if((Cur_VolStat.Time.Time[T_YEAR]==0 && Cur_VolStat.Time.Time[T_MONTH]==0) ||\
     Check_HEX_Time((S_HEX_Time *)&(Cur_VolStat.Time))==0)
  {
    DEBUG_PRINT(HUCK,DEBUG_0,"----------Freeze VolStat Data End----------");
    return;
  }
  //<=pTime�����һ������ʱ���
  Get_Last_Freeze_Time(pTime,&TempTime);//pTime��ǰ�����һ������ʱ���,����pTime����
  //����TempTime�������һ�εĶ���ʱ���
  Re=Cmp_Time(&(Cur_VolStat.Time),&TempTime);//�Ƚ����ݶ���ʱ��������һ�ζ���ʱ���
  if(TIME_AFT==Re)//����ʱ��������һ�ν���ʱ���֮����һ����ǰ���ݣ�����Ҫ���浽��ʷ������
  {
    DEBUG_PRINT(HUCK,DEBUG_0,"VolStat Time > FreezeTime");
    Debug_Print_HEX_Time(Cur_VolStat.Time.Time);
    Debug_Print_HEX_Time(TempTime.Time);    
    DEBUG_PRINT(HUCK,DEBUG_0,"----------Freeze VolStat Data End----------");
    return;
  }
  //��һ����ʷ����
  //>=p->Time�����һ������ʱ���
  Get_Next_Freeze_Time(&(Cur_VolStat.Time),&TempTime);//��ʷ���ݵĶ���ʱ��� 
  OS_Sem_Pend(PUB_BUF0_SEM_ID);//����Pub_Buf0�ź���
  //����û�ж�����������ж���
  if(Read_HIS_Data(HIS_VOLSTAT_DATA,&TempTime,(void *)Pub_Buf0,(void *)Pub_Buf0,sizeof(Pub_Buf0),&Err) EQ sizeof(S_VolStat))
  {
    DEBUG_PRINT(HUCK,DEBUG_0,"VolStat Time Data Freezed!");
    Debug_Print_HEX_Time(TempTime.Time); 
  }
  else
  {
    //mem_cpy((void *)&Cur_VolStat.Time,&TempTime,sizeof(TempTime),(void *)&Cur_VolStat,sizeof(Cur_VolStat));
    SET_STRUCT_TIME(Cur_VolStat,TempTime);
    Write_HIS_Data(HIS_VOLSTAT_DATA,(S_HEX_Time *)&(Cur_VolStat.Time),(void *)&Cur_VolStat,sizeof(Cur_VolStat));
  }
  
  OS_Sem_Post(PUB_BUF0_SEM_ID);//�ͷ�Pub_Buf0�ź���  
  //��Ϊ����ʷ���ݣ�������Ҫ���ñ�Ϊ��������
  //�嵱�µ�ѹͳ������
  mem_set((void *)&Cur_VolStat,0,sizeof(Cur_VolStat),(void *)&Cur_VolStat,sizeof(Cur_VolStat));//������ȫ����0���뵱ǰ�洢�����´ζ���ȫ0���ݣ���ʾ��δ����������

  INIT_STRUCT_VAR(Cur_VolStat);
  SET_DATA_READY_FLAG(Cur_VolStat);   
  SET_STRUCT_SUM(Cur_VolStat);
  
  //���´洢������  
  Save_Cur_VolStat_PD_Data();
  Save_Cur_VolStat_Data();
  DEBUG_PRINT(HUCK,DEBUG_0,"----------Freeze VolStat Data End----------");
}

//�ϵ粹����ѹͳ������
void PowerOn_VolStat_Data_Freeze()
{
  Freeze_VolStat_Data((S_HEX_Time *)&Cur_Time0);
}

//����ѹͳ����ز����ĺϷ���
void Check_VolStat_Para_Avail()
{
  INT8U Re;
  
  Re=CHECK_STRUCT_SUM(VolStat_Para);  
  if(0==Re)
  {
    ASSERT(A_WARNING,0); 
    Read_VolStat_Para_From_Rom();
  }
}

//����ѹͳ��������ݵĺϷ���
void Check_VolStat_Data_Avail()
{
  INT8U Re;
  
  Re=1;
  Re&=CHECK_STRUCT_SUM(Cur_VolStat);
  Re&=CHECK_STRUCT_SUM(Total_VolStat);
  if(0==Re)
  {
    ASSERT(A_WARNING,0);
    Read_VolStat_Data_From_Rom();
  }
  
}

//���ѹͳ������
void Clear_VolStat_Data()
{ 
  if(Check_Clear_Data_Authority()==0)
    return;
  
  if(CLEAR_VOLSTAT_FLAG!=Check_Clear_Data_Flag() &&
     CLEAR_ALL_FLAG!=Check_Clear_Data_Flag())
    return;
  DEBUG_PRINT(HUCK,DEBUG_0,"Clear_VolStat_Data!!!");  
  Set_Def_VolStat_Data();
  /*
  INT8U i;
  S_HEX_Time Time;
  INT8U Re;
  
  DEBUG_PRINT(HUCK,DEBUG_0,"Clear_VolStat_Data!!!");
  //�����,����Ƿ��ڱ��״̬���Լ��û�Ȩ���Ƿ�
  if(Check_Meter_Prog_Status()==0 ||\
     CHECK_STRUCT_SUM(User_Authority_Flag)==0 ||\
    User_Authority_Flag.Flag!=AUTHORITY_FLAG)
    return;
  
  if(CLEAR_VOLSTAT_FLAG!=Check_Clear_Data_Flag())
    return;
  
  //���ڴ��б���
  mem_set((void *)&Cur_VolStat,0,sizeof(Cur_VolStat),(void *)&Cur_VolStat,sizeof(Cur_VolStat));
  SET_STRUCT_SUM(Cur_VolStat);
  mem_set((void *)&Total_VolStat,0,sizeof(Total_VolStat),(void *)&Total_VolStat,sizeof(Total_VolStat));
  SET_STRUCT_SUM(Total_VolStat);

  
  //�����,����Ƿ��ڱ��״̬���Լ��û�Ȩ���Ƿ�
  if(Check_Meter_Prog_Status()==0 ||\
     CHECK_STRUCT_SUM(User_Authority_Flag)==0 ||\
    User_Authority_Flag.Flag!=AUTHORITY_FLAG)
    return;
  
  //��������־�Ƿ�Ϸ�
  if(CLEAR_VOLSTAT_FLAG!=Check_Clear_Data_Flag())
    return;
  //�浱������
  Write_Storage_Data(CUR_VOLSTAT_PD,(void *)(&Cur_VolStat),sizeof(Cur_VolStat));
  Write_Storage_Data(CUR_VOLSTAT,(void *)(&Cur_VolStat),sizeof(Cur_VolStat));
  //��������
  Write_Storage_Data(TOTAL_VOLSTAT_PD,(void *)(&Total_VolStat),sizeof(Total_VolStat));
  Write_Storage_Data(TOTAL_VOLSTAT,(void *)(&Total_VolStat),sizeof(Total_VolStat));
  
  Re=CHECK_STRUCT_SUM(Cur_Time0);
  if(ASSERT(A_WARNING,1==Re))
    Check_Data_Avail();
  
  //��ǰ0-HIS_VOLSTAT_DATA_MONTHS���µ�ͳ������ȫ����0
  mem_cpy((void *)&Time,(void *)&Cur_Time0,sizeof(Time),(void *)&Time,sizeof(Time));//��ȡ��ǰʱ��
  Re=CHECK_STRUCT_SUM(Data_Freeze_Time);
  if(ASSERT(A_WARNING,0!=Re))
    Check_Data_Avail();
  
  Time.Time[T_HOUR]=Data_Freeze_Time.DDHH[0];
  Time.Time[T_DATE]=Data_Freeze_Time.DDHH[1];
  SET_STRUCT_SUM(Time);
  //��ǰ0-HIS_VOLSTAT_DATA_MONTHS���µ�ͳ������ȫ����0
  if(CLEAR_VOLSTAT_FLAG!=Check_Clear_Data_Flag())
    return;
  
  Re=1;
  Re&=CHECK_STRUCT_SUM(User_Authority_Flag);
  Re&=CHECK_STRUCT_SUM(Clear_Flag);
  for(i=0;i<=HIS_VOLSTAT_DATA_MONTHS;i++)
  {
    DEBUG_PRINT(HUCK,DEBUG_0,"Clear Freeze VolStat Data,Time:%d-%d-%d %d:%d",Time.Time[T_YEAR],Time.Time[T_MONTH],Time.Time[T_DATE],Time.Time[T_HOUR],Time.Time[T_MIN]);
    //�ϸ��жϣ���ֹ�������ܵ�����
    if(Check_Meter_Prog_Status()==0 || 1!=Re ||\
       AUTHORITY_FLAG!=User_Authority_Flag.Flag ||\
       CLEAR_DEMAND_FLAG!=Clear_Flag.Flag)
      return;
    Freeze_VolStat_Data(&Time);
    Time_Dec((S_HEX_Time *)&Time,1,UNIT_MON,(S_HEX_Time *)&Time);
  } 
  */
}

//��ʼ����ѹͳ�Ʋ���
void Init_VolStat_Ram_Para()
{
  mem_set((void *)&VolStat_Count,0,sizeof(VolStat_Count),(void *)&VolStat_Count,sizeof(VolStat_Count));
  SET_STRUCT_SUM(VolStat_Count);
  
}
#undef VOLSTAT_C

