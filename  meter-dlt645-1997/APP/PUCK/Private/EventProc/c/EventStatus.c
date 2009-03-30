#define EVENTSTATUS_C
#include "Pub_PUCK.h"
#include "EventStatus.h"

/***********************************************************************
�������ܣ���ʼ���¼�״̬�Ȳ���
��ڣ�1------------ǿ������¼�˲̬�֣����¼��������״̬��sram��0-------����CSֵ�����
���ڣ���
***********************************************************************/
void Init_Event_Sram(INT8U Flag)
{
  INT8U i;
  
  if((CHECK_STRUCT_SUM(Meter_Run_Status)==0) || Flag)
     mem_set((void *)(&Meter_Run_Status),0,sizeof(Meter_Run_Status),\
                 (void *)(&Meter_Run_Status),sizeof(Meter_Run_Status));    
  SET_STRUCT_SUM(Meter_Run_Status);

  if((CHECK_STRUCT_SUM(Meter_Self_Test)==0) || Flag)
     mem_set((void *)(&Meter_Self_Test),0,sizeof(Meter_Self_Test),\
                 (void *)(&Meter_Self_Test),sizeof(Meter_Self_Test));    
  SET_STRUCT_SUM(Meter_Self_Test);
  
  for(i=0;i<MAX_EVENT_NUM;i++)
  {
    if((CHECK_STRUCT_SUM(EventProcStatusVar[i])==0) || Flag)
      Clr_Event_Real_Status(i);      
  }
  
  if((CHECK_STRUCT_SUM(Meter_Run_Status)==0) || Flag)
   
    mem_set((void *)(&Meter_Instant_Status),0,sizeof(Meter_Instant_Status),\
                 (void *)(&Meter_Instant_Status),sizeof(Meter_Instant_Status));
  SET_STRUCT_SUM(Meter_Instant_Status); 

  //��ʼ���¼���λsram
  mem_set((void *)(&Loss_Volt_Change),0,sizeof(Loss_Volt_Change),\
               (void *)(&Loss_Volt_Change),sizeof(Loss_Volt_Change));   
  INIT_STRUCT_VAR(Loss_Volt_Change);
  mem_set((void *)(&Loss_Curr_Change),0,sizeof(Loss_Curr_Change),\
               (void *)(&Loss_Curr_Change),sizeof(Loss_Curr_Change));   
  INIT_STRUCT_VAR(Loss_Curr_Change);
  
  mem_set((void *)(&Curr_Neg_Change),0,sizeof(Curr_Neg_Change),\
               (void *)(&Curr_Neg_Change),sizeof(Curr_Neg_Change));   
  INIT_STRUCT_VAR(Curr_Neg_Change);
  
  //�ظ������¼�״̬��Ϊ���������׼������Ϊǰ��������ˣ�
  if(!Flag)
  {
    if(POWER_OFF==Power_Status.Power)   //�����¼�������,������Ϊ����,Ϊ���������׼��
    {
      EventProcStatusVar[ID_EVENT_POWER_OFF].Occur=1;
      EventProcStatusVar[ID_EVENT_POWER_OFF].Status=1;
      EventProcStatusVar[ID_EVENT_POWER_OFF].StartCount=0;
      EventProcStatusVar[ID_EVENT_POWER_OFF].EndCount=0;
     SET_STRUCT_SUM(EventProcStatusVar[ID_EVENT_POWER_OFF]); 
    } 
  }
}

/***********************************************************************
�������ܣ���������¼�״̬
��ڣ�
���ڣ���
***********************************************************************/
void Clr_All_Event_Sram(void)
{  
  Init_Event_Sram(1);  
}
/***********************************************************************
�������ܣ���ʼ�������¼�״̬
��ڣ�
���ڣ���
***********************************************************************/
void Init_All_Event_Sram(void)
{  
  Init_Event_Sram(0);  
}
/***********************************************************************
�������ܣ���ȫʧѹ�������㣬����������fx1�����ڵ�������е��ã�Ϊ��ʼ��ȫʧѹ��׼��
��ڣ���
���ڣ���
***********************************************************************/
void Clr_All_Loss_Data(void)
{
  INT8U i;
  mem_set((void *)(&All_Loss_Var),0,sizeof(All_Loss_Var),\
                   (void *)(&All_Loss_Var),sizeof(All_Loss_Var));
  All_Loss_Var.Status.First=1;
  SET_VAR_CS_PUCK(All_Loss_Var.Status); 
  for(i=0;i<ALL_LOSS_NUM;i++)
    SET_VAR_CS_PUCK(All_Loss_Var.RecordTime[i]);
}

/***********************************************************************
�������ܣ�����CS��������������ȫʧѹsram������������fx1���񣬳���λ��
��ڣ���
���ڣ���
***********************************************************************/
void Init_All_Loss_Sram(void)
{
  INT8U Flag,i;
  
  Flag=CHK_VAR_CS_PUCK(All_Loss_Var.Status);
  for(i=0;i<ALL_LOSS_NUM;i++)
    Flag&=CHK_VAR_CS_PUCK(All_Loss_Var.RecordTime[i]);
  
  if(!Flag)
  {
    ASSERT(A_WARNING,0);  
    mem_set((void *)(&All_Loss_Var),0,sizeof(All_Loss_Var),(void *)(&All_Loss_Var),sizeof(All_Loss_Var));
    All_Loss_Var.Status.First=1;
    SET_VAR_CS_PUCK(All_Loss_Var.Status); 
    for(i=0;i<ALL_LOSS_NUM;i++)
    SET_VAR_CS_PUCK(All_Loss_Var.RecordTime[i]); 
  }
}

/***********************************************************************
�������ܣ��洢ȫʧѹ���ݣ�����������fx1�����¼������Ѿ�����������������Դ����
��ڣ���
���ڣ���
***********************************************************************/
void Save_All_Loss_Data(void)
{
  INT8U i,temp,num;
  INT32U temp32;
  
  temp=CHK_VAR_CS_PUCK(All_Loss_Var.Status);
  if(0==temp)
  ASSERT(A_WARNING,0);  
  
  if(All_Loss_Var.Status.BatRunTime)  //ʱ���ۼ�
  {
    temp=Read_Storage_Data_PUCK(0xb214,(INT8U *)(&temp32),4);
    ASSERT(A_WARNING,1==temp);  
    temp32+=All_Loss_Var.Status.BatRunTime;
    temp=Write_Storage_Data(0xb214,(INT8U *)(&temp32),4);
    ASSERT(A_WARNING,NO_ERR==temp); 
    All_Loss_Var.Status.BatRunTime=0; //���
    SET_VAR_CS_PUCK(All_Loss_Var.Status); 
  }  
  
  if((All_Loss_Var.Status.Nums==0)||(All_Loss_Var.Status.Mins==0))   //û���¼�����
  {
    Clr_All_Loss_Data();   //�������0
    return ;
  }
   
  if(All_Loss_Var.Status.start && All_Loss_Var.Status.Index<ALL_LOSS_NUM)  //�з���û�н���,�Ҳ�Խ��
  {
    if((CHeck_Same_Byte((INT8U*)All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime,0x00,sizeof(All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime))))
    {
      All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime[0]=Cur_Time1.Min;
      All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime[1]=Cur_Time1.Hour;
      All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime[2]=Cur_Time1.Date;
      All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime[3]=Cur_Time1.Month;
      All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime[4]=Cur_Time1.Year;  //ȡϵͳʱ��
      SET_VAR_CS_PUCK(All_Loss_Var.RecordTime[All_Loss_Var.Status.Index]);
    }
  }
  num=(All_Loss_Var.Status.Nums<=ALL_LOSS_NUM)?All_Loss_Var.Status.Nums:ALL_LOSS_NUM;
  if(All_Loss_Var.Status.Index<ALL_LOSS_NUM)   //index��֤��Խ��
  {
     for(i=0;i<num;i++)  
     {
       if(num<=ALL_LOSS_NUM)  //û�з�ת����˳������д
         temp=i;   
       else                   //��ת������-->������д  
        temp=((All_Loss_Var.Status.Index+1)%ALL_LOSS_NUM+i)%ALL_LOSS_NUM;       
      All_Loss_Vol_Data_Proc((INT8U *)All_Loss_Var.RecordTime[temp].StartTime,(INT8U *)All_Loss_Var.RecordTime[temp].EndTime);
     }
  }
  
  All_Loss_Vol_Counts_Time_Proc(All_Loss_Var.Status.Nums,All_Loss_Var.Status.Mins); 
  Clr_All_Loss_Data();   //�������0  
}
/***********************************************************************
�������ܣ�����ȫʧѹ���ݣ�����������fxt����RTC���塣��RTC�ж��е��ã�
��ڣ���
���ڣ���
***********************************************************************/
void Count_All_Loss_Proc(void)
{ 
  All_Loss_Var.Status.BatRunTime++;  //�ж�һ�Σ��ǵ�ع���1����----PUCK

  if(All_Loss_Var.Status.Occur)
  {
    All_Loss_Var.Status.Occur=0;
    All_Loss_Var.Status.Exist=1;
  }
  else
    All_Loss_Var.Status.Exist=0;
  
  if(All_Loss_Var.Status.Exist==0 && All_Loss_Var.Status.start==0) //��ʧѹ�������������ٶ��˳�
  {
    SET_VAR_CS_PUCK(All_Loss_Var.Status); 
    return  ;
  }
  
  if(All_Loss_Var.Status.Exist && All_Loss_Var.Status.start==0)  //ȫʧѹ����
  {
    All_Loss_Var.Status.start=1;
    if(All_Loss_Var.Status.First)
    {
      All_Loss_Var.Status.First=0;
      All_Loss_Var.Status.Index=0;
    }
    else
      All_Loss_Var.Status.Index=(All_Loss_Var.Status.Index+1)%ALL_LOSS_NUM;
    
    /*
    if(All_Loss_Var.Status.Index>ALL_LOSS_NUM)  //��ֹԽ��
      All_Loss_Var.Status.Index=0;
    */
    All_Loss_Var.Status.Nums++;
    All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].StartTime[0]=MIN;      //CPU_RTC_Time.RTC.Min;
    All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].StartTime[1]=HOUR;      //CPU_RTC_Time.RTC.Hour;
    All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].StartTime[2]=DAY;      //CPU_RTC_Time.RTC.Date;
    All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].StartTime[3]=MONTH;      //CPU_RTC_Time.RTC.Month;
    All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].StartTime[4]=YEAR;      //CPU_RTC_Time.RTC.Year;
    
    memset((INT8U*)All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime,0x00,\
          sizeof(All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime));     //��д������mem_set
    
    SET_VAR_CS_PUCK(All_Loss_Var.Status); 
    SET_VAR_CS_PUCK(All_Loss_Var.RecordTime[All_Loss_Var.Status.Index]); 
    return ;
  }
  
  if(All_Loss_Var.Status.Exist && All_Loss_Var.Status.start)    //ȫʧѹ����
  {
    All_Loss_Var.Status.Mins++;
    SET_VAR_CS_PUCK(All_Loss_Var.Status);
    return ;
  }
  
  if(All_Loss_Var.Status.Exist==0 && All_Loss_Var.Status.start) //ȫʧѹ����
  {
    All_Loss_Var.Status.Mins++;
    All_Loss_Var.Status.start=0;
    All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime[0]=MIN;      //CPU_RTC_Time.RTC.Min;
    All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime[1]=HOUR;     // CPU_RTC_Time.RTC.Hour;
    All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime[2]=DAY;      //CPU_RTC_Time.RTC.Date;
    All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime[3]=MONTH;    //  CPU_RTC_Time.RTC.Month;
    All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime[4]=YEAR;     // CPU_RTC_Time.RTC.Year;
    SET_VAR_CS_PUCK(All_Loss_Var.Status); 
    SET_VAR_CS_PUCK(All_Loss_Var.RecordTime[All_Loss_Var.Status.Index]); 
    return ;    
  }
  
  SET_VAR_CS_PUCK(All_Loss_Var.Status); 
  SET_VAR_CS_PUCK(All_Loss_Var.RecordTime[All_Loss_Var.Status.Index]);
}
/***********************************************************************
�������ܣ����ݷ������¼�Id��״̬��������Ӧ��״̬
��ڣ���
���ڣ���
***********************************************************************/
void Set_Event_Instant_Status(INT8U Id,INT8U Status)
{
  INT8U Byte,Bit;
  if(Id>=MAX_EVENT_NUM)
    return ;
  
  Byte=Id/8;
  Bit=Id%8;
  DIS_PD_INT;  //�ص����ж�
  if(Status)
    SET_BIT(Meter_Instant_Status.Instant_Event[Byte],Bit);
  else
    CLR_BIT(Meter_Instant_Status.Instant_Event[Byte],Bit);    
  SET_STRUCT_SUM(Meter_Instant_Status);
  EN_PD_INT; //�������ж�
}

/***********************************************************************
�������ܣ����ݷ������¼���������Ӧ��˲̬״̬��
��ڣ���
���ڣ���
***********************************************************************/
void Set_Event_Instant(INT8U Id)
{
  if(EventPropertyVar[Id].DoubleFlag==0)  //���ɶ��¼����������ԭ����ʵ״̬
    Clr_Event_Real_Status(Id);
  Set_Event_Instant_Status(Id,1);
}
/***********************************************************************
�������ܣ�����λ�����ֽڵ�λ�������Ӧ��λ��Ϣ���ֽ���Ϣ
��ڣ���
���ڣ���
***********************************************************************/
void Clr_Event_Instant(INT8U Id)
{
  Set_Event_Instant_Status(Id,0); 
}

/***********************************************************************
�������ܣ����¼�ģ��Ϊ�������״̬,Ϊ������׼��
��ڣ���
���ڣ���
***********************************************************************/
void Set_Event_Occur_Status(INT8U i)
{
  if(i>MAX_ID_EVENT)
    return ;
  
  mem_set((void *)(EventProcStatusVar+i),1,sizeof(EventProcStatusVar+i),\
                 (void *)(EventProcStatusVar+i),sizeof(EventProcStatusVar+i));
  
  EventProcStatusVar[i].EndCount=EventPropertyVar[i].EndCount+1;
  SET_STRUCT_SUM(EventProcStatusVar[i]);    
}
/***********************************************************************
�������ܣ����¼�ģ��Ϊ�������״̬,Ϊ������׼��
��ڣ���
���ڣ���
***********************************************************************/
void Set_Event_End_Status(INT8U i)
{
  if(i>MAX_ID_EVENT)
    return ;
  
  mem_set((void *)(EventProcStatusVar+i),0,sizeof(EventProcStatusVar+i),\
                 (void *)(EventProcStatusVar+i),sizeof(EventProcStatusVar+i));
  
  EventProcStatusVar[i].StartCount=EventPropertyVar[i].StartCount+1;
  SET_STRUCT_SUM(EventProcStatusVar[i]);    
}
/***********************************************************************
�������ܣ�����¼�����������״̬
��ڣ���
���ڣ���
***********************************************************************/
void Clr_Event_Real_Status(INT8U Id)
{
  if(Id>MAX_ID_EVENT)
    return ;
  
  mem_set((void *)(EventProcStatusVar+Id),0,sizeof(EventProcStatusVar+Id),\
                 (void *)(EventProcStatusVar+Id),sizeof(EventProcStatusVar+Id));
  SET_STRUCT_SUM(EventProcStatusVar[Id]);

}
/***********************************************************************
�������ܣ�����λ�����ֽڵ�λ����ȡ��Ӧ��λ��Ϣ���ֽ���Ϣ
��ڣ���
���ڣ���
***********************************************************************/
INT8U Get_Event_Instant(INT8U Id)
{  
  INT8U Byte,Bit,temp;
  
  if(Id>=MAX_EVENT_NUM)
    return 0;
  
  Byte=Id/8;
  Bit=Id%8;
  
  temp=CHECK_STRUCT_SUM(Meter_Instant_Status); 
  if(0==temp)
  ASSERT(A_WARNING,0);  

  temp=GET_BIT(Meter_Instant_Status.Instant_Event[Byte],Bit);  
  return temp;    
}


/********************************************************************************
����ԭ�ͣ�void Event_Judge_StartAndEnd(INT8U Id,INT8U CountMode,INT8U SaveMode)
�������ܣ�����¼�(�ɶ�)����
CountMode:0----------��ʾ�趨�����ж�Ϊ0������-------------�����¼����ʱ���ж�
SaveMode:0----------��ʾ���洢������-------------��ʾ�洢
*********************************************************************************/
void Event_Judge_StartAndEnd(INT8U Id,INT8U CountMode,INT8U SaveMode)
{
  INT16U ConStartcounts,ConEndcounts;
  INT16U RamStartcounts,RamEndcounts;
  
  if(Id<MIN_ID_EVENT || Id>MAX_ID_EVENT) //����һ��
    return ;
  
  if(CHECK_STRUCT_SUM(EventProcStatusVar[Id])==0)  //У��Ͳ��ԣ���ֹ�¼��Ҵ��Ҹ㣬���֮
  {
    ASSERT(A_WARNING,0);
    Clr_Event_Real_Status(Id);
    return ;
  }
  if(Check_Sys_Status()==SYS_NORMAL) //����ģʽ�£������ж�ʱ�䣬�ɱ�����
  {
    ConStartcounts=(EventPropertyVar[Id].StartUnit==0)?\
                EventPropertyVar[Id].StartCount:((INT16U)EventPropertyVar[Id].StartCount*60);
    ConEndcounts=(EventPropertyVar[Id].EndUnit==0)?\
                EventPropertyVar[Id].EndCount:((INT16U)EventPropertyVar[Id].EndCount*60); 
  }
  else                               //������ģʽ�£������ͽ���ֻ�ж�һ��
  {
    ConStartcounts=1;
    ConEndcounts=1; 
  }
  
  if(0==CountMode)
  {
    ConStartcounts=1;
    ConEndcounts=1; 
  }
  
  if(EventProcStatusVar[Id].Occur==0)   //δ�������¼�
  {
    if(Get_Event_Instant(Id))  //��ǰ˲ʱ״ָ̬ʾ���¼��ķ���
      EventProcStatusVar[Id].StartCount++;
    else                                 //���������������������
      EventProcStatusVar[Id].StartCount=0;
    
    if(EventProcStatusVar[Id].StartCount>=60)  //���Ӽ���
    {
      EventProcStatusVar[Id].Mins++;
      EventProcStatusVar[Id].StartCount=0;
    }
      
    RamStartcounts=EventProcStatusVar[Id].Mins*60+(INT16U)EventProcStatusVar[Id].StartCount;
    if(RamStartcounts>=ConStartcounts)  //�¼���������
    {       
      if(EventPropertyVar[Id].DisEvent)
        DEBUG_PRINT(PUCK,PRINT_PUCK_EVENT_EN,"Event_Occur----->%s(%d)(%x-%x-%x %x:%x:%x)",EventPropertyVar[Id].EventName,Id,\
                        Cur_Time1.Year,Cur_Time1.Month,Cur_Time1.Date,Cur_Time1.Hour,Cur_Time1.Min,Cur_Time1.Sec);  
     
      if((EventPropertyVar[Id].StartSave)&&(0!=SaveMode))
      {
        //�ֽ�ϵͳ״̬����λ��ΪEvent_Data_Proc()����
        EventProcStatusVar[Id].Status=1;
        Get_Meter_Run_Status();
        //��ϵͳ״̬����0����ΪEvent_Data_Proc()ĳЩ�ж�������
        EventProcStatusVar[Id].Status=0;
        
        Event_Data_Proc(Id,EVENT_OCCUR);  //�����¼������洢����  
        DEBUG_PRINT(PUCK,PRINT_PUCK_EVENT_EN,"Write Event_Occur----->%s(%d)",EventPropertyVar[Id].EventName,Id);
      }
      EventProcStatusVar[Id].Occur=1; EventProcStatusVar[Id].Status=1;  
      EventProcStatusVar[Id].Status1=1; EventProcStatusVar[Id].Status2=1; 
      EventProcStatusVar[Id].Status3=1; EventProcStatusVar[Id].Status4=1; 
      EventProcStatusVar[Id].StartCount=0;EventProcStatusVar[Id].EndCount=0;  
      EventProcStatusVar[Id].Mins=0;

      if(EventPropertyVar[Id].DoubleFlag==0)  //���ڲ��ɶԵ��¼��������������˲̬��
      {
          Clr_Event_Instant(Id); //�����Ӧ˲ʱ״̬�֣����ڶԽ���ʱ����¼���Ӧ
          //DEBUG_PRINT(PUCK,PRINT_PUCK_EVENT_EN,"Emergece Event End,Clear Instant---------->%s",EventPropertyVar[Id].EventName);
      }
      if(EventPropertyVar[Id].DoubleFlag &&ConEndcounts==0)  //�ɶԵ��¼�����Ҫ�����������˲̬��
         Clr_Event_Instant(Id);
    }
  }
  else                         //�Ѿ������˸��¼�,�����������ʼ����
  {
    if(EventPropertyVar[Id].DoubleFlag==1)  //�ɶ��¼�
    {
      if(EventProcStatusVar[Id].Status==1)  //�ɶ��¼�������,�н����¼�
      {
        if(Get_Event_Instant(Id)==0)  //�ڽ�������ʱ
          EventProcStatusVar[Id].EndCount++;
        else                          
        {
          if(EventPropertyVar[Id].ForbitEnd==0)       //����Ҫǿ�н���
            EventProcStatusVar[Id].EndCount=0;         //���������������������
          else                                    //��Ҫǿ�н���,������ʱ,����������
          {
            Clr_Event_Instant(Id); //ǿ�������Ӧ˲ʱ״̬��
            EventProcStatusVar[Id].EndCount++;
            if(EventPropertyVar[Id].EndIndex<MAX_END_TIME_NUM)
              ConEndcounts=Const_End_Time[EventPropertyVar[Id].EndIndex]; 
            else
              ASSERT(A_WARNING,0);
          }
        }          
      }
    }
    else                                //���ǳɶ��¼������������������������������
    {
      Clr_Event_Instant(Id); //ǿ�������Ӧ˲ʱ״̬��-------PUCK!!!!!!!!!
      EventProcStatusVar[Id].EndCount++;
    }
    
    if(EventProcStatusVar[Id].EndCount>=60)  //���Ӽ���
    {
      EventProcStatusVar[Id].Mins++;
      EventProcStatusVar[Id].EndCount=0;
    }
    RamEndcounts=EventProcStatusVar[Id].Mins*60+(INT16U)EventProcStatusVar[Id].EndCount; 
    if(RamEndcounts>=ConEndcounts)  //�¼�����/�ָ�
    {
      if(EventPropertyVar[Id].DisEvent)
        DEBUG_PRINT(PUCK,PRINT_PUCK_EVENT_EN,"Event_End----->%s(%d)(%x-%x-%x %x:%x:%x)",EventPropertyVar[Id].EventName,Id,\
                        Cur_Time1.Year,Cur_Time1.Month,Cur_Time1.Date,Cur_Time1.Hour,Cur_Time1.Min,Cur_Time1.Sec); 
       if((EventPropertyVar[Id].EndSave)&&(0!=SaveMode))
       {
         //�ֽ�ϵͳ״̬����0��ΪEvent_Data_Proc()����
        EventProcStatusVar[Id].Status=0;
        Get_Meter_Run_Status();
        //��ϵͳ״̬�ֻ�ԭ����ΪEvent_Data_Proc()ĳЩ�ж�������
        EventProcStatusVar[Id].Status=1;
        
         Event_Data_Proc(Id,EVENT_END);  //�����¼������洢����
         DEBUG_PRINT(PUCK,PRINT_PUCK_EVENT_EN,"Write Event_End----->%s(%d)",EventPropertyVar[Id].EventName,Id);
       }
       EventProcStatusVar[Id].Occur=0;    EventProcStatusVar[Id].Status=0;
       EventProcStatusVar[Id].Status1=0;  EventProcStatusVar[Id].Status2=0;
       EventProcStatusVar[Id].Status3=0;   EventProcStatusVar[Id].Status4=0;
       EventProcStatusVar[Id].StartCount=0;EventProcStatusVar[Id].EndCount=0; 
       EventProcStatusVar[Id].Mins=0;       
      
       if(Id==ID_EVENT_PRGKEY_ON)
        Key_Value_Pub.Key.Bit.PrgKey=0;
    }
  }
    SET_STRUCT_SUM(EventProcStatusVar[Id]);  
}
/********************************************************************************
����ԭ�ͣ�void Get_Meter_Instant_Status(void)
�������ܣ���ȡ���˲̬��,ͨ������ָ�������Ӧ����ʵ��
*********************************************************************************/
void Get_Meter_Instant_Status(void)
{
  INT8U i;
  
  for(i=MIN_ID_EVENT;i<=MAX_ID_EVENT;i++)
  {
    if(EventPropertyVar[i].GetInstStatus)
      EventPropertyVar[i].GetInstStatus();
  }
}
/********************************************************************************
����ԭ�ͣ�void Event_Judge_Save_Alarm(INT8U Flag)
�������ܣ������¼�����/�����ж���,ͬʱ���ⱨ��
*********************************************************************************/
void Event_Judge_Save_Alarm(INT8U CountMode,INT8U SaveMode)
{
  INT8U i;
  
  for(i=MIN_ID_EVENT;i<=MAX_ID_EVENT;i++)
  {
    if(REC_FRAME_CONDITION)
    {
        OS_TimeDly_Ms(10);  
    }
    Event_Judge_StartAndEnd(i,CountMode,SaveMode);
  }
}
/********************************************************************************
����ԭ�ͣ�void Read_Event_Status_Perone(INT8U PersonID,INT8U EventId)
�������ܣ������ڲ����˼���Ƿ���,�������
��ڣ�    PersonID--------����ID
          EventId---------�¼�ID
���ڣ�0---------�޴��¼�������1---------���¼�������
*********************************************************************************/
INT8U Read_Event_Status_Perone(INT8U PersonID,INT8U EventId)
{
  INT8U temp;  
 
  if(EventId>MAX_EVENT_NUM)
    return 0;
  
  temp=0;   
  switch(PersonID)
  {
  case HUCK:
    temp=EventProcStatusVar[EventId].Status1;
    EventProcStatusVar[EventId].Status1=0;
    break;
    
   case SUCK:
    temp=EventProcStatusVar[EventId].Status2;
    EventProcStatusVar[EventId].Status2=0;
    break;
      
   case PUCK:
    temp=EventProcStatusVar[EventId].Status3;
    EventProcStatusVar[EventId].Status3=0;
    break;
      
    
    case LUCK:
    temp=EventProcStatusVar[EventId].Status4;
    EventProcStatusVar[EventId].Status4=0;
    break;
  }
  SET_STRUCT_SUM(EventProcStatusVar[EventId]);  
  return  temp;
}
/********************************************************************************
����ԭ�ͣ�void Read_Event_Status(INT8U EventId)
�������ܣ��ⲿ(��485�ӿ�)����¼��Ƿ���
          ע�⣺���¼��ǳɶԷ��������������״̬һֱ���ڣ������ǳɶԷ��������¼�����һ����ʱ���Զ����
��ڣ�    EventId---------�¼�ID
���ڣ�0---------�޴��¼�������1---------���¼�������
*********************************************************************************/
INT8U Read_Event_Status(INT8U Id)
{
  if(Id>MAX_EVENT_NUM)
    return 0;

  return  (EventProcStatusVar[Id].Status);
}
/********************************************************************************
����ԭ�ͣ�void Check_Event_End(INT8U EventId)
�������ܣ��жϽ����¼��Ƿ�����������¼��Ƿ����������ͽ�������Ҫ����Read_Event_Status()����
��ڣ�    EventId---------�¼�ID
���ڣ�1---------���¼��Ѿ�������0---------���¼�������
*********************************************************************************/
INT8U Check_Event_End(INT8U Id)
{
  if(Id>MAX_EVENT_NUM)
    return 0;
  
  if(EventPropertyVar[Id].DoubleFlag==1)    //�ж��Ƿ��ǽ����¼�    
    ASSERT(A_WARNING,0);  
  if(Get_Event_Instant(Id)==0)
    return 1;
  
  return  0;
}
/***********************************************************************
�������ܣ���ȡ�������״̬��,����Э���ʽ��֡
��ڣ���
���ڣ���
***********************************************************************/
void Get_Meter_Run_Status(void)
{

  if(CHECK_STRUCT_SUM(Measu_Status_Mode_ToPub_PUCK)==0)
  ASSERT(A_WARNING,0);  
  
  //mem_set(&Meter_Run_Status,0xff,sizeof(Meter_Run_Status),&Meter_Run_Status,sizeof(Meter_Run_Status));  
  
  //�������״̬��1
  Meter_Run_Status.Meter_Stat1.Bit.Bit0=0;                                        //����ʽ��0--�Զ���1----�ֶ�������
  Meter_Run_Status.Meter_Stat1.Bit.Bit1=0;                                        //����������㷽ʽ��0--���1----���䣻??????????
  Meter_Run_Status.Meter_Stat1.Bit.Bit2=Read_Event_Status(ID_EVENT_LOWPWR_BAT_LOW);    //�͹��ĵ�ص�ѹ��0--������1----Ƿѹ��
  Meter_Run_Status.Meter_Stat1.Bit.Bit3=0;                                        //������0
  Meter_Run_Status.Meter_Stat1.Bit.Bit4=Measu_Status_Mode_ToPub_PUCK.SUM_APwrDir; //���й�����0--����1----����
  Meter_Run_Status.Meter_Stat1.Bit.Bit5=Measu_Status_Mode_ToPub_PUCK.SUM_RPwrDir; //���޹�����0--����1----����
  Meter_Run_Status.Meter_Stat1.Bit.Bit6=0;                                        //������0
  Meter_Run_Status.Meter_Stat1.Bit.Bit7=0;                                        //������0
  
  
  //�������״̬��2
  Meter_Run_Status.Meter_Stat2.Bit.Bit0=Measu_Status_Mode_ToPub_PUCK.A_APwrDir;   //�й�����0--����1----����
  Meter_Run_Status.Meter_Stat2.Bit.Bit1=Measu_Status_Mode_ToPub_PUCK.B_APwrDir;   //�й�����0--����1----����
  Meter_Run_Status.Meter_Stat2.Bit.Bit2=Measu_Status_Mode_ToPub_PUCK.C_APwrDir;   //�й�����0--����1----����
  Meter_Run_Status.Meter_Stat2.Bit.Bit3=0;                                        //������0
  Meter_Run_Status.Meter_Stat2.Bit.Bit4=Measu_Status_Mode_ToPub_PUCK.A_RPwrDir;   //�޹�����0--����1----����
  Meter_Run_Status.Meter_Stat2.Bit.Bit5=Measu_Status_Mode_ToPub_PUCK.B_RPwrDir;   //�޹�����0--����1----����
  Meter_Run_Status.Meter_Stat2.Bit.Bit6=Measu_Status_Mode_ToPub_PUCK.C_RPwrDir;   //�޹�����0--����1----����
  Meter_Run_Status.Meter_Stat2.Bit.Bit7=0;                                        //������0
  
  
  //�������״̬��3
  Meter_Run_Status.Meter_Stat3.Bit.Bit0=Read_Event_Status(ID_EVENT_CUR_NEG_SEQ);    //����������0--������1----������
  Meter_Run_Status.Meter_Stat3.Bit.Bit1=Read_Event_Status(ID_EVENT_VOLT_NEG_SEQ);    //��ѹ������0--������1----������
  Meter_Run_Status.Meter_Stat3.Bit.Bit2=0;                                        //������0
  Meter_Run_Status.Meter_Stat3.Bit.Bit3=0;                                        //������0
  Meter_Run_Status.Meter_Stat3.Bit.Bit4=Read_Event_Status(ID_EVENT_A_LOSS_CURR)|\
                                        Read_Event_Status(ID_EVENT_AB_LOSS_CURR)|\
                                        Read_Event_Status(ID_EVENT_AC_LOSS_CURR)|\
                                        Read_Event_Status(ID_EVENT_ALL_LOSS_CURR);  //A��ʧ����0--��ʧ����1----ʧ��;
  
  Meter_Run_Status.Meter_Stat3.Bit.Bit5=Read_Event_Status(ID_EVENT_B_LOSS_CURR)|\
                                        Read_Event_Status(ID_EVENT_AB_LOSS_CURR)|\
                                        Read_Event_Status(ID_EVENT_BC_LOSS_CURR)|\
                                        Read_Event_Status(ID_EVENT_ALL_LOSS_CURR);  //B��ʧ����0--��ʧ����1----ʧ��;
  
  Meter_Run_Status.Meter_Stat3.Bit.Bit6=Read_Event_Status(ID_EVENT_C_LOSS_CURR)|\
                                        Read_Event_Status(ID_EVENT_AC_LOSS_CURR)|\
                                        Read_Event_Status(ID_EVENT_BC_LOSS_CURR)|\
                                        Read_Event_Status(ID_EVENT_ALL_LOSS_CURR);  //C��ʧ����0--��ʧ����1----ʧ��;
  Meter_Run_Status.Meter_Stat3.Bit.Bit7=0;                                        //������0

  //�������״̬��4
  Meter_Run_Status.Meter_Stat4.Bit.Bit0=Read_Event_Status(ID_EVENT_POWER_ALARM);   //�����ʱ�����0--û������1----������
  Meter_Run_Status.Meter_Stat4.Bit.Bit1=Read_Event_Status(ID_EVENT_POWER_SWITCH);   //��������բ��0--û������1----������
  Meter_Run_Status.Meter_Stat4.Bit.Bit2=Read_Event_Status(ID_EVENT_RTC_BAT_LOW);    //�ڲ����Ƿѹ��0--������1----Ƿѹ��
  Meter_Run_Status.Meter_Stat4.Bit.Bit3=0;                                        //������0
  Meter_Run_Status.Meter_Stat4.Bit.Bit4=0;                                        //Ƿ�ѱ�����0--û������1----������??????????
  Meter_Run_Status.Meter_Stat4.Bit.Bit5=0;                                        //Ƿ����բ��0--û������1----������??????????
  Meter_Run_Status.Meter_Stat4.Bit.Bit6=Read_Event_Status(ID_EVENT_LOWPWR_BAT_LOW); //�ⲿ���Ƿѹ��0--������1----Ƿѹ��
  Meter_Run_Status.Meter_Stat4.Bit.Bit7=0;                                        //������0
  
  
  //��������״̬��
  Meter_Run_Status.Grid_Stat.Bit.Bit0=Read_Event_Status(ID_EVENT_A_LOSS_PARSE); //A��ϵ磺0--û������1----�������ö������
  Meter_Run_Status.Grid_Stat.Bit.Bit1=Read_Event_Status(ID_EVENT_B_LOSS_PARSE); //B��ϵ磺0--û������1----�������ö������
  Meter_Run_Status.Grid_Stat.Bit.Bit2=Read_Event_Status(ID_EVENT_C_LOSS_PARSE); //C��ϵ磺0--û������1----�������ö������
  Meter_Run_Status.Grid_Stat.Bit.Bit3=0;                                        //������0
  Meter_Run_Status.Grid_Stat.Bit.Bit4=Read_Event_Status(ID_EVENT_A_VOLT_OVERLOAD);//A���ѹ��0--û������1----������
  Meter_Run_Status.Grid_Stat.Bit.Bit5=Read_Event_Status(ID_EVENT_B_VOLT_OVERLOAD); //B���ѹ��0--û������1----������
  Meter_Run_Status.Grid_Stat.Bit.Bit6=Read_Event_Status(ID_EVENT_C_VOLT_OVERLOAD); //C���ѹ��0--û������1----������
  Meter_Run_Status.Grid_Stat.Bit.Bit7=0;                                        //������0
  
  
  //������Ϣ��ERR
  Meter_Run_Status.Meter_Stat6.Bit.Bit0=0;//Read_Event_Status(ID_EVENT_ERR_DATA);  //�Ƿ�����
  Meter_Run_Status.Meter_Stat6.Bit.Bit1=Read_Event_Status(ID_EVENT_ERR_DI); //���ݱ�ʶ��
  Meter_Run_Status.Meter_Stat6.Bit.Bit2=Read_Event_Status(ID_EVENT_ERR_PASSWD);  //�����
  Meter_Run_Status.Meter_Stat6.Bit.Bit3=0;                                        //������0
  Meter_Run_Status.Meter_Stat6.Bit.Bit4=Read_Event_Status(ID_EVENT_YEAR_FLOW); //��ʱ������
  Meter_Run_Status.Meter_Stat6.Bit.Bit5=Read_Event_Status(ID_EVENT_DATE_FLOW); //��ʱ������
  Meter_Run_Status.Meter_Stat6.Bit.Bit6=Read_Event_Status(ID_EVENT_TRRI_FLOW); //��������
  Meter_Run_Status.Meter_Stat6.Bit.Bit7=0;                                        //������0
  
  //ʧѹ/����״̬��
  Meter_Run_Status.Volt_LossMiss.Bit.Bit0=Read_Event_Status(ID_EVENT_A_LOSS_PARSE); //A����ࣺ0--û������1----������
  Meter_Run_Status.Volt_LossMiss.Bit.Bit1=Read_Event_Status(ID_EVENT_B_LOSS_PARSE); //B����ࣺ0--û������1----������
  Meter_Run_Status.Volt_LossMiss.Bit.Bit2=Read_Event_Status(ID_EVENT_C_LOSS_PARSE); //C����ࣺ0--û������1----������
  Meter_Run_Status.Volt_LossMiss.Bit.Bit3=0;                                    //������0
  Meter_Run_Status.Volt_LossMiss.Bit.Bit4=Read_Event_Status(ID_EVENT_A_LOSS_VOLT)|\
                                          Read_Event_Status(ID_EVENT_AB_LOSS_VOLT)|\
                                          Read_Event_Status(ID_EVENT_AC_LOSS_VOLT)|\
                                          Read_Event_Status(ID_EVENT_ABC_LOSS_VOLT);//A��ʧѹ��0--û������1----������
  Meter_Run_Status.Volt_LossMiss.Bit.Bit5=Read_Event_Status(ID_EVENT_B_LOSS_VOLT)|\
                                          Read_Event_Status(ID_EVENT_AB_LOSS_VOLT)|\
                                          Read_Event_Status(ID_EVENT_BC_LOSS_VOLT)|\
                                          Read_Event_Status(ID_EVENT_ABC_LOSS_VOLT);//B��ʧѹ��0--û������1----������
  Meter_Run_Status.Volt_LossMiss.Bit.Bit6=Read_Event_Status(ID_EVENT_C_LOSS_VOLT)|\
                                          Read_Event_Status(ID_EVENT_AC_LOSS_VOLT)|\
                                          Read_Event_Status(ID_EVENT_BC_LOSS_VOLT)|\
                                          Read_Event_Status(ID_EVENT_ABC_LOSS_VOLT);//C��ʧѹ��0--û������1----������
  Meter_Run_Status.Volt_LossMiss.Bit.Bit7=0;                                    //������0
  
  //����������/����
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit0=0;  //���������1��
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit1=0;  //���������2:
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit2=0;  //���������3��
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit3=0;  //���������4��
  
  if(Judge_I_Start())  //������������������
  {
    switch(Measu_InstantData_ToPub_PUCK.Quadrant.Sum)
    {
    case QUADRANT1:
        Meter_Run_Status.NegCurr_Qudrant.Bit.Bit0=1;
      break;
    case QUADRANT2:
        Meter_Run_Status.NegCurr_Qudrant.Bit.Bit1=1;
      break;
    case QUADRANT3:
        Meter_Run_Status.NegCurr_Qudrant.Bit.Bit2=1;
      break;
    case QUADRANT4:
        Meter_Run_Status.NegCurr_Qudrant.Bit.Bit3=1;
      break;
    }
  }
  else
    Meter_Run_Status.NegCurr_Qudrant.Byte&=0xf0;
    
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit4=Read_Event_Status(ID_EVENT_A_NEG_CURR);    //A����������ԣ�0--������1----��;
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit5=Read_Event_Status(ID_EVENT_B_NEG_CURR);    //B����������ԣ�0--������1----����
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit6=Read_Event_Status(ID_EVENT_C_NEG_CURR);    //C����������ԣ�0--������1----����
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit7=0;                                          //������0
  
  //�̼���/���߶̽�/������λ/�������
  Meter_Run_Status.Key_Event.Bit.Bit0=Read_Event_Status(ID_EVENT_PRGKEY_ON);   //��̼���
  Meter_Run_Status.Key_Event.Bit.Bit1=Read_Event_Status(ID_EVENT_FAC_ON);      //����ģʽ
  Meter_Run_Status.Key_Event.Bit.Bit2=Read_Event_Status(ID_EVENT_CLR_DEMAND_MAN)|Read_Event_Status(ID_EVENT_CLR_DEMAND_COM) |Read_Event_Status(ID_EVENT_CLR_ALL_DATA); //������λ
  Meter_Run_Status.Key_Event.Bit.Bit3=Read_Event_Status(ID_EVENT_METER_LOCK);   //�������
  Meter_Run_Status.Key_Event.Bit.Bit4=Read_Event_Status(ID_ALARM_OUT);   //���Ƿ���ڱ���ָʾ
  Meter_Run_Status.Key_Event.Bit.Bit5=Read_Event_Status(ID_EVENT_KEY_SWITCH);    //���߶̽�ģʽ
  Meter_Run_Status.Key_Event.Bit.Bit6=Read_Event_Status(ID_EVENT_ADJUST_MEASU);          //У��״̬����ϵͳ����δ����
  Meter_Run_Status.Key_Event.Bit.Bit7=0;                                       //������0
  
  //ͨ��״̬��
  Meter_Run_Status.Comm_Status.Bit.Bit0=0;                                       //���ߣ�??????????
  Meter_Run_Status.Comm_Status.Bit.Bit1=0;                                       //��ǿ0��??????????
  Meter_Run_Status.Comm_Status.Bit.Bit2=0;                                       //��ǿ1��??????????
  Meter_Run_Status.Comm_Status.Bit.Bit3=0;                                       //��ǿ2��??????????
  Meter_Run_Status.Comm_Status.Bit.Bit4=0;                                       //������0
  Meter_Run_Status.Comm_Status.Bit.Bit5=0;                                       //������0
  Meter_Run_Status.Comm_Status.Bit.Bit6=0;                                       //������0
  Meter_Run_Status.Comm_Status.Bit.Bit7=0;                                       //������0 
  
  
      
  //��չ�����ݵ�״̬��
  Meter_Run_Status.Ext_Ac_Power_Dir.Byte=0;
  Meter_Run_Status.Ext_Ac_Power_Dir.Bit.Bit0=Measu_Status_Mode_ToPub_PUCK.SUM_APwrDir;   //�й������־�ֽڣ�1�ֽڣ�0-3λΪ�ܡ�a��b��cԪ������4�ֽ�Ϊ0��
  Meter_Run_Status.Ext_Ac_Power_Dir.Bit.Bit1=Measu_Status_Mode_ToPub_PUCK.A_APwrDir;   //�й�����0--����1----����
  Meter_Run_Status.Ext_Ac_Power_Dir.Bit.Bit2=Measu_Status_Mode_ToPub_PUCK.B_APwrDir;   //�й�����0--����1----����
  Meter_Run_Status.Ext_Ac_Power_Dir.Bit.Bit3=Measu_Status_Mode_ToPub_PUCK.C_APwrDir;   //�й�����0--����1----����
  
  Meter_Run_Status.Ext_Reac_Power_Dir.Byte=0;
  Meter_Run_Status.Ext_Reac_Power_Dir.Bit.Bit0=Measu_Status_Mode_ToPub_PUCK.SUM_RPwrDir;   //�й������־�ֽڣ�1�ֽڣ�0-3λΪ�ܡ�a��b��cԪ������4�ֽ�Ϊ0��
  Meter_Run_Status.Ext_Reac_Power_Dir.Bit.Bit1=Measu_Status_Mode_ToPub_PUCK.A_RPwrDir;   //�޹�����0--����1----����
  Meter_Run_Status.Ext_Reac_Power_Dir.Bit.Bit2=Measu_Status_Mode_ToPub_PUCK.B_RPwrDir;   //�޹�����0--����1----����
  Meter_Run_Status.Ext_Reac_Power_Dir.Bit.Bit3=Measu_Status_Mode_ToPub_PUCK.C_RPwrDir;   //�޹�����0--����1----����
  
 
  //�㶫�����״̬��
  Meter_Run_Status.GD_Meter_Stat.Byte=0;                              
  Meter_Run_Status.GD_Meter_Stat.Bit.Bit0=0;        //������բ                          
  Meter_Run_Status.GD_Meter_Stat.Bit.Bit1=0;        //ʵ����բ
  Meter_Run_Status.GD_Meter_Stat.Bit.Bit3=0;        //ʱ�ӳ���
  Meter_Run_Status.GD_Meter_Stat.Bit.Bit4=1;        //���ʱ����У
  Meter_Run_Status.GD_Meter_Stat.Bit.Bit5=Read_Event_Status(ID_EVENT_DEMAND_ALARM);        //���󸺺�״̬(ͬ������)
  Meter_Run_Status.GD_Meter_Stat.Bit.Bit6=Read_Event_Status(ID_EVENT_LOWPWR_BAT_LOW)|Read_Event_Status(ID_EVENT_RTC_BAT_LOW); //���Ƿѹ

  
  //�㶫���й����ʷ���״̬��
  Meter_Run_Status.GD_PwrDir_Stat.Byte=0;                              
  Meter_Run_Status.GD_PwrDir_Stat.Bit.Bit0=Measu_Status_Mode_ToPub_PUCK.A_APwrDir;        //A�๦�ʷ���                          
  Meter_Run_Status.GD_PwrDir_Stat.Bit.Bit1=Measu_Status_Mode_ToPub_PUCK.B_APwrDir;        //B�๦�ʷ���  
  Meter_Run_Status.GD_PwrDir_Stat.Bit.Bit2=Measu_Status_Mode_ToPub_PUCK.C_APwrDir;        //C�๦�ʷ���  
  Meter_Run_Status.GD_PwrDir_Stat.Bit.Bit4=Measu_Status_Mode_ToPub_PUCK.SUM_APwrDir;        //���๦�ʷ���  

  //�㶫��ʧѹ״̬��
  Meter_Run_Status.GD_LossVolt_Stat.Byte=0;                              
  Meter_Run_Status.GD_LossVolt_Stat.Bit.Bit0=Read_Event_Status(ID_EVENT_A_LOSS_VOLT);        //A��ʧѹ                         
  Meter_Run_Status.GD_LossVolt_Stat.Bit.Bit1=Read_Event_Status(ID_EVENT_B_LOSS_VOLT);        //B��ʧѹ    
  Meter_Run_Status.GD_LossVolt_Stat.Bit.Bit2=Read_Event_Status(ID_EVENT_C_LOSS_VOLT);        //C��ʧѹ    
  
  //�㶫��ʧ��״̬��
  Meter_Run_Status.GD_LossCurr_Stat.Byte=0;                              
  Meter_Run_Status.GD_LossCurr_Stat.Bit.Bit0=Read_Event_Status(ID_EVENT_A_LOSS_CURR);        //A��ʧ��                          
  Meter_Run_Status.GD_LossCurr_Stat.Bit.Bit1=Read_Event_Status(ID_EVENT_B_LOSS_CURR);        //B��ʧ��          
  Meter_Run_Status.GD_LossCurr_Stat.Bit.Bit2=Read_Event_Status(ID_EVENT_C_LOSS_CURR);        //C��ʧ��          

  //�㶫��Ӳ��״̬��
  Meter_Run_Status.GD_Hard_Stat.Byte=0;                              
  Meter_Run_Status.GD_Hard_Stat.Bit.Bit0=1;           //�к��⹦��                       
  Meter_Run_Status.GD_Hard_Stat.Bit.Bit1=0;           //����բ����        
  Meter_Run_Status.GD_Hard_Stat.Bit.Bit2=1;           //��485���� 
  
  //�㶫�����״̬��
  /*
  Meter_Run_Status.GD_Prog_Stat.Byte=0;                              
  Meter_Run_Status.GD_Prog_Stat.Bit.Bit0=0;           //ʱ�η��ʸ���                     
  Meter_Run_Status.GD_Prog_Stat.Bit.Bit1=0;           //�����ո���       
  Meter_Run_Status.GD_Prog_Stat.Bit.Bit2=0;           //��Ÿ���
  Meter_Run_Status.GD_Prog_Stat.Bit.Bit3=0;           //�������
  Meter_Run_Status.GD_Prog_Stat.Bit.Bit2=0;           //�㲥Уʱ
  Meter_Run_Status.GD_Prog_Stat.Bit.Bit3=0;           //��ͨУʱ
  Meter_Run_Status.GD_Prog_Stat.Bit.Bit3=0;           //�׶�����
  Meter_Run_Status.GD_Prog_Stat.Bit.Bit3=0;           //��ʾ���ø���
  */
  SET_STRUCT_SUM(Meter_Run_Status);
}


/***********************************************************************
�������ܣ���ȡ����Լ�״̬��,����Э���ʽ��֡
��ڣ���
���ڣ���
***********************************************************************/
void Get_Meter_Self_Test(void)
{
  
  Meter_Self_Test.Low_Byte.Byte=0;
  Meter_Self_Test.Low_Byte.Bit.Bit0=Read_Event_Status(ID_EVENT_RTCERR_RUN)|Read_Event_Status(ID_EVENT_RTCERR_PWRON);  //ʱ����
  Meter_Self_Test.Low_Byte.Bit.Bit4=Read_Event_Status(ID_EVENT_DEMAND_ALARM);    //������/����
  Meter_Self_Test.Low_Byte.Bit.Bit6=Read_Event_Status(ID_EVENT_A_LOSS_PARSE)| \
                                    Read_Event_Status(ID_EVENT_B_LOSS_PARSE)| \
                                    Read_Event_Status(ID_EVENT_C_LOSS_PARSE);      //����


  
  Meter_Self_Test.High_Byte.Bit.Bit0=Meter_Run_Status.Meter_Stat3.Bit.Bit4|\
                                     Meter_Run_Status.Meter_Stat3.Bit.Bit5|\
                                     Meter_Run_Status.Meter_Stat3.Bit.Bit6;          //ʧ��(��ȫʧ��)
  Meter_Self_Test.High_Byte.Bit.Bit1=Meter_Run_Status.Grid_Stat.Bit.Bit4|\
                                     Meter_Run_Status.Grid_Stat.Bit.Bit5|\
                                     Meter_Run_Status.Grid_Stat.Bit.Bit6;           //��ѹ
  Meter_Self_Test.High_Byte.Bit.Bit2=Meter_Run_Status.Volt_LossMiss.Bit.Bit4|\
                                     Meter_Run_Status.Volt_LossMiss.Bit.Bit5|\
                                     Meter_Run_Status.Volt_LossMiss.Bit.Bit6;       //ʧѹ
  
  Meter_Self_Test.High_Byte.Bit.Bit3=Meter_Run_Status.Meter_Stat3.Bit.Bit1;        //������
  Meter_Self_Test.High_Byte.Bit.Bit4=Read_Event_Status(ID_EVENT_LOWPWR_BAT_LOW);        //�͹��ĵ��Ƿѹ
  Meter_Self_Test.High_Byte.Bit.Bit5=Read_Event_Status(ID_EVENT_RTC_BAT_LOW);        //ʱ�ӵ��Ƿѹ
  Meter_Self_Test.High_Byte.Bit.Bit6=0;        //�ڿ����ݴ�
  Meter_Self_Test.High_Byte.Bit.Bit7=0;        //�ڿ�����
  
  SET_STRUCT_SUM(Meter_Self_Test);  
  
}
/********************************************************************************
����ԭ�ͣ�void Check_Prog_Status(void)
�������ܣ�����Ƿ��ڱ��״̬
��ڣ� 
���ڣ�0---------���Ǳ��״̬��1---------�Ǳ��״̬��
*********************************************************************************/
INT8U Check_Prog_Status(void)
{
  return (Read_Event_Status(ID_EVENT_PRGKEY_ON));  
  
}
/********************************************************************************
����ԭ�ͣ�void Check_MeterAddr_Status(void)
�������ܣ�������ñ��ַ��ť�Ƿ���
��ڣ� 
���ڣ�0---------���ַ��ťû�а��£�1---------���ַ��ť�����ˣ�
*********************************************************************************/
INT8U Check_MeterAddr_Status(void)
{
  return (Read_Event_Status(ID_METER_ADDR_EN));  
  
}
/********************************************************************************
����ԭ�ͣ�INT8U Check_Man_ClrDemd_En(void)
�������ܣ�������ñ��ַ��ť�Ƿ���
��ڣ� 
���ڣ�0---------�������ֶ���������1---------�����ֶ�������
*********************************************************************************/
INT8U Check_Man_ClrDemd_En(void)
{
  return (Read_Event_Status(ID_CLR_DEMAND_KEY));  
}
/********************************************************************************
����ԭ�ͣ�void ClrDemand_Request(void)
�������ܣ��ֶ����������󣬷��ʺ��������
��ڣ� 
���ڣ�1------������������0-------������������
*********************************************************************************/
INT8U ClrDemand_Request(void)
{
  return (Read_Event_Status_Perone(PUCK,ID_EVENT_PROG));  
  
}
/********************************************************************************
����ԭ�ͣ�void Check_AB_Switch(void)
�������ܣ�
��ڣ� 
���ڣ�0---------����AB��ʾģʽ�л�״̬��1---------��AB��ʾģʽ�л�״̬��
*********************************************************************************/
INT8U Check_AB_Switch(void)
{
  static INT8U KeyStatus=0;
  
  if(Get_Sys_Status()==SYS_NORMAL)
    return (Read_Event_Status_Perone(PUCK,ID_EVENT_AB_FUNC_KEY)); 
  if(Get_Sys_Status()==SYS_RESUME)  //10ms��ѯһ��
  {
    if((Inter_Up_Key_STATUS==1)&&(Inter_Down_Key_STATUS==1))  //û�а�ť����
      KeyStatus=0;
    else    //��һ����ť������
      KeyStatus++;
  }
  if(KeyStatus>=80)
  {
    KeyStatus=0;
    return 1;
  }
  return 0;
}
/********************************************************************************
����ԭ�ͣ�void Check_Event_StruCS(void)
�������ܣ�������¼���ص����нṹ���У���
��ڣ� 
���ڣ�
*********************************************************************************/
void Check_Event_StruCS(void)
{
  INT8U i,Flag;
  for(i=0;i<MAX_EVENT_NUM;i++)
  {
    Flag=CHECK_STRUCT_SUM(EventProcStatusVar[i]);
    ASSERT(A_WARNING,1==Flag);  
  }
  
  Flag=CHECK_STRUCT_SUM(Meter_Instant_Status);
  if(Flag==0)  //Sram��������¼�˲̬��
  {
    ASSERT(A_WARNING,0);
    mem_set((void *)(&Meter_Instant_Status),0,sizeof(Meter_Instant_Status),\
                   (void *)(&Meter_Instant_Status),sizeof(Meter_Instant_Status));
    SET_STRUCT_SUM(Meter_Instant_Status);  
  }
  
  Flag=CHECK_STRUCT_SUM(EventInsParaVar);
  if(Flag==0)
  {
    ASSERT(A_WARNING,0);
    Init_Event_Instant_Para(); 
  }
  
  Flag=CHECK_STRUCT_SUM(Meter_Run_Status);
  if(Flag==0)  //Sram��������¼�˲̬��
  {
    ASSERT(A_WARNING,0);
    mem_set((void *)(&Meter_Run_Status),0,sizeof(Meter_Run_Status),\
                   (void *)(&Meter_Run_Status),sizeof(Meter_Run_Status));
    SET_STRUCT_SUM(Meter_Run_Status);  
  }
  
  Flag=CHECK_STRUCT_SUM(Meter_Self_Test);
  if(Flag==0)  //Sram��������¼�˲̬��
  {
    ASSERT(A_WARNING,0);
    mem_set((void *)(&Meter_Self_Test),0,sizeof(Meter_Self_Test),\
                   (void *)(&Meter_Self_Test),sizeof(Meter_Self_Test));
    SET_STRUCT_SUM(Meter_Self_Test);  
  }

  if(CHECK_STRUCT_SUM(Power_Status)==0)
    ASSERT(A_WARNING,0);
  
  if(CHECK_STRUCT_VAR(Loss_Volt_Change)==0)
    ASSERT(A_WARNING,0);
  
  if(CHECK_STRUCT_VAR(Loss_Curr_Change)==0)
    ASSERT(A_WARNING,0);
  
  if(CHECK_STRUCT_VAR(Curr_Neg_Change)==0)
    ASSERT(A_WARNING,0);

}
/********************************************************************************
����ԭ�ͣ�void Test_Interr_IO_Status(void)
�������ܣ���ѯ�ж����ŵ�IO��״̬
��ڣ� 
���ڣ�
*********************************************************************************/
void Test_Interr_IO_Status(void)
{    
    if(Inter_Up_Key_STATUS==0)
      DEBUG_PRINT(PUCK,PRINT_PUCK_EVENT_EN,"Check Up_Key_Pin IO==0");  
    if(Inter_Down_Key_STATUS==0)
      DEBUG_PRINT(PUCK,PRINT_PUCK_EVENT_EN,"Check Down_Key_Pin IO==0"); 
    if(Inter_Left_Key_STATUS==0)
      DEBUG_PRINT(PUCK,PRINT_PUCK_EVENT_EN,"Check Left_Key_Pin IO==0"); 
    if(Inter_Right_Key_STATUS==0)
      DEBUG_PRINT(PUCK,PRINT_PUCK_EVENT_EN,"Check Right_Key_Pin IO==0"); 
    if(POWER_OFF_STATUS==0)
      DEBUG_PRINT(PUCK,PRINT_PUCK_EVENT_EN,"Check PowerOff_Pin IO==0"); 
    //if(ALL_V_LOSS_STATUS==0)
    //  DEBUG_PRINT(PUCK,PRINT_PUCK_EVENT_EN,"Check LossVolt_Pin IO==0"); 
    
}
/********************************************************************************
����ԭ�ͣ�void ReNew_PwrOff_Status(void)
�������ܣ����õ��������˲ʱ״̬��
*********************************************************************************/
void ReNew_PwrOff_Status(void)
{   
  INT8U i;
  if(CHECK_STRUCT_SUM(Meter_Instant_Status)==0)  //����ǰ�¼���״̬��У��ʹ����������
  {
    ASSERT(A_WARNING,0);
     mem_set((void *)(&Meter_Instant_Status),0,sizeof(Meter_Instant_Status),\
                   (void *)(&Meter_Instant_Status),sizeof(Meter_Instant_Status));
    SET_STRUCT_SUM(Meter_Instant_Status); 
    return ;
  }
  else
  {
    for(i=MIN_ID_EVENT;i<=MAX_ID_EVENT;i++)   //���ݵ���ʱ���¼���������ʵ״̬������ʼ��˲̬�֣�������洢
    {
      if(Read_Event_Status(i))
        Set_Event_Instant(i);
      else
        Clr_Event_Instant(i);
    }    
  }
  
 /*
  for(i=0;i<MAX_EVENT_NUM;i++)
  {
    if(Get_Event_Instant(i)&&EventPropertyVar[i].EndSave)    //��ǰ���¼�����,�һָ�ʱ��Ҫ�洢
    {
       DEBUG_PRINT(PUCK,PRINT_PUCK_EVENT_EN,"Event_End(Power Off)----->%s(%d)(%x-%x-%x %x:%x:%x)",EventPropertyVar[i].EventName,i,\
                        Cur_Time1.Year,Cur_Time1.Month,Cur_Time1.Date,Cur_Time1.Hour,Cur_Time1.Min,Cur_Time1.Sec); 
       if(EventPropertyVar[i].EndSave)
       {
         Event_Data_Proc(i,EVENT_END);  //�����¼������洢����
         DEBUG_PRINT(PUCK,PRINT_PUCK_EVENT_EN,"Write Event_End----->%s(%d)",EventPropertyVar[i].EventName,i);
       }
    }
  } 
  */
}
/********************************************************************************
����ԭ�ͣ�void Set_Power_Or_Reset_Ststus(void)
�������ܣ���λǰ������������λ��־
*********************************************************************************/
void Set_PwrOrRst_Status(void)
{  
  Set_Event_Instant(ID_EVENT_POWER_OFF);  //�����¼�����
  Power_Status.Power=POWER_OFF;          //�����¼���־
  SET_STRUCT_SUM(Power_Status);    
}
/********************************************************************************
����ԭ�ͣ�void Save_Event_Data(void)
�������ܣ��ϵ�󣬶Ե�����¼����ݴ洢
*********************************************************************************/
void Save_Event_Data(void)
{ 
  INT8U Flag,i;
  
  Flag=CHECK_STRUCT_SUM(Power_Status);  
  if(Flag)    //�ϴθ�λǰ��״̬,sram״̬��ȷ
  {
    if(Get_Sys_Status()==SYS_NORMAL) 
    {
      if(POWER_OFF!=Power_Status.Power)     //ǰ��û�в��������Ϣ
      {
        Power_Status.Power=ABNORMAL_RESET;      //��Ϊ��λ״̬��Ϊ�ϵ��¼��ж���׼����������Ϊ�ϵ��¼����洢
      }
    } 
  }
  else
    Power_Status.Power=POWER_ON;       //�ϵ��¼���λ��Ϊ�ж���׼��
  SET_STRUCT_SUM(Power_Status);    
      
  
  for(i=MIN_ID_EVENT;i<=MAX_ID_EVENT;i++)  //�����ϴε����˲̬�֣�ǿ�������¼��ķ���
  {
    if(Get_Event_Instant(i))   //��״̬ʵ���Ǵ� �ڿ� ȡ����״̬������ sram״̬
    {
      if(ID_EVENT_POWER_OFF!=i)        //�ϵ�󣬶�ǰ���¼�,ģ�ⷢ���˵�״̬,�ȴ�����
        Set_Event_Occur_Status(i);
      else                             //�ϵ�󣬶�ǰ�ε����¼���ģ����������˵�״̬���ȴ�����
      {
         if(ABNORMAL_RESET!=Power_Status.Power)     //Sram �ж���Ϊ��λ���ڿ��ж�Ϊ���磬��ȷʵ�����ˣ�
         {
           Set_Event_End_Status(i);     
           Power_Status.Power=POWER_OFF;    //���ڿ��ĵ���Ϊ׼
         }
      }
    }
    else
        Clr_Event_Real_Status(i);
  }  

  Event_Judge_Save_Alarm(0,1);    //����ǿ�����õ�˲̬�֣�ģ��һ�ν���    
  Clr_All_Event_Sram();     //������������
  
}
/********************************************************************************
����ԭ�ͣ�void Afer_PwrOff_Proc(void)
�������ܣ�������¼�����
*********************************************************************************/
void PwrOff_Proc_PUCK(void)
{ 
  Clr_All_Loss_Data();         //����ȫʧѹSram����
  Set_Soft_RTC_PUCK(ID_CPU_RTC);        //��ʼ����ʱ��
  ReNew_PwrOff_Status();       //�����˲ʱ״̬��
  Set_PwrOrRst_Status();
}
/********************************************************************************
����ԭ�ͣ�void Event_Main_PUCK(INT8U Flag)
�������ܣ�״̬�ּ��¼�������
*********************************************************************************/
void Event_Main_PUCK(INT8U Flag)
{
  Check_Event_StruCS();  
  Get_Meter_Instant_Status();  //��ȡ���˲̬��
  Event_Judge_Save_Alarm(1,1);    //ͨ��˲̬�֣���ȡ��������¼���ʵ״̬,�洢�¼���Ϣ,ͬʱ���ⱨ��
   //Test_Interr_IO_Status();
}
/********************************************************************************
����ԭ�ͣ�void Event_Proc_Sec(void)
�������ܣ�ÿ����¼��Ĵ������ж�����
*********************************************************************************/
void Event_Proc_Sec(void)
{
  static volatile S_Int32U Sec_Timer_Bak={CHK_BYTE,0xFFFFFFFF,CHK_BYTE};
    
  if(Sec_Timer_Bak.Var!=Sec_Timer_Pub)
  {
    Event_Para_Modi();
    Event_Main_PUCK(0);
    Get_Meter_Run_Status(); 
    Get_Meter_Self_Test();
    Sec_Timer_Bak.Var=Sec_Timer_Pub;
  }
}
/********************************************************************************
����ԭ�ͣ�void Emerg_Event_Proc(void)
�������ܣ���ͻ���¼��ķݶ��
���ڣ�0---------�޴��¼�������1---------���¼�������
*********************************************************************************/
void Emerg_Event_Proc(void)
{
  INT8U i;
  for(i=MIN_ID_EVENT;i<=MAX_ID_EVENT;i++)
  {
    if((EventPropertyVar[i].DoubleFlag==0)&&(Get_Event_Instant(i)))  //���ɶ��¼�������˲̬������
    {
      if(REC_FRAME_CONDITION)
      {
        OS_TimeDly_Ms(10);  
      }
      
      Event_Judge_StartAndEnd(i,1,1);
      
      /*
      Get_Meter_Instant_Status();     
      Event_Judge_Save_Alarm(1,1);    //ͨ��˲̬�֣���ȡ��������¼���ʵ״̬,�洢�¼���Ϣ,ͬʱ���ⱨ��
      */
      return ;
    }    
  }
}

/********************************************************************************
����ԭ�ͣ�void Init_Event_DIS_PUCK(void)
�������ܣ���ʼ���¼�
���ڣ�
*********************************************************************************/
void Init_Event_DIS_PUCK(void)
{  
  if((FP32S)Measu_InstantData_ToPub_PUCK.Volt.A/UNIT_V<60.0)
      Meter_Run_Status.Volt_LossMiss.Bit.Bit0=1;  //A����ࣺ0--û������1----������
  else
      Meter_Run_Status.Volt_LossMiss.Bit.Bit0=0; 
  
  if(Get_SysParse_Mode()==PARSE_341)
  {  
    if((FP32S)Measu_InstantData_ToPub_PUCK.Volt.B/UNIT_V<60.0)
      Meter_Run_Status.Volt_LossMiss.Bit.Bit1=1;  //B����ࣺ0--û������1----������
    else
      Meter_Run_Status.Volt_LossMiss.Bit.Bit1=0;
  }
  
  if((FP32S)Measu_InstantData_ToPub_PUCK.Volt.C/UNIT_V<60.0)
      Meter_Run_Status.Volt_LossMiss.Bit.Bit2=1;  //C����ࣺ0--û������1----������
  else
     Meter_Run_Status.Volt_LossMiss.Bit.Bit2=0;
  
  if((FP32S)Measu_InstantData_ToPub_PUCK.Volt.A/(FP32S)UNIT_V>Get_Un()*(FP32S)1.25)
  {
    Meter_Run_Status.Grid_Stat.Bit.Bit4=1;        //A��ѹ��ѹ
  }
  if((FP32S)Measu_InstantData_ToPub_PUCK.Volt.A/(FP32S)UNIT_V<Get_Un()*(FP32S)1.20)  //���ߵ���,����ϵ�������
    Meter_Run_Status.Grid_Stat.Bit.Bit4=0;        //A��ѹ��ѹ���

  if((FP32S)Measu_InstantData_ToPub_PUCK.Volt.B/(FP32S)UNIT_V>Get_Un()*(FP32S)1.25)
  {
    Meter_Run_Status.Grid_Stat.Bit.Bit5=1;  //B��ѹ��ѹ
  }
  if((FP32S)Measu_InstantData_ToPub_PUCK.Volt.B/(FP32S)UNIT_V<Get_Un()*(FP32S)1.20)  //���ߵ���,����ϵ�������
    Meter_Run_Status.Grid_Stat.Bit.Bit5=0;  //B��ѹ��ѹ���

  if((FP32S)Measu_InstantData_ToPub_PUCK.Volt.C/(FP32S)UNIT_V>Get_Un()*(FP32S)1.25)
  {
    Meter_Run_Status.Grid_Stat.Bit.Bit6=1;  //B��ѹ��ѹ
    Event_Vol_Cur.Over_Vol[2]=Measu_InstantData_ToPub_PUCK.Volt.C;
  }
  if(Measu_InstantData_ToPub_PUCK.Volt.C/(FP32S)UNIT_V<Get_Un()*(FP32S)1.20)  //���ߵ���,����ϵ�������
    Meter_Run_Status.Grid_Stat.Bit.Bit6=0;  //B��ѹ��ѹ���
  
  
  
  if((FP32S)Measu_InstantData_ToPub_PUCK.Curr.A/UNIT_A<(Get_In()/50))  //����С��2%In
    Meter_Run_Status.Meter_Stat3.Bit.Bit4=1;     //A��ʧ����0--û������1----������
  else
    Meter_Run_Status.Meter_Stat3.Bit.Bit4=0;
  
  if(Get_SysParse_Mode()==PARSE_341)
  {
    if((FP32S)Measu_InstantData_ToPub_PUCK.Curr.B/UNIT_A<(Get_In()/50))  //����С��2%In
      Meter_Run_Status.Meter_Stat3.Bit.Bit5=1;     //B��ʧ����0--û������1----������
    else
      Meter_Run_Status.Meter_Stat3.Bit.Bit5=0;
  }
  
  if((FP32S)Measu_InstantData_ToPub_PUCK.Curr.C/UNIT_A<(Get_In()/50))  //����С��2%In
    Meter_Run_Status.Meter_Stat3.Bit.Bit6=1;     //C��ʧ����0--û������1----������
  else
    Meter_Run_Status.Meter_Stat3.Bit.Bit6=0;  
  
    //����������/����
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit0=0;  //���������1��
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit1=0;  //���������2:
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit2=0;  //���������3��
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit3=0;  //���������4��
  
  if(Judge_I_Start())  //������������������
  {
    switch(Measu_InstantData_ToPub_PUCK.Quadrant.Sum)
    {
    case QUADRANT1:
        Meter_Run_Status.NegCurr_Qudrant.Bit.Bit0=1;
      break;
    case QUADRANT2:
        Meter_Run_Status.NegCurr_Qudrant.Bit.Bit1=1;
      break;
    case QUADRANT3:
        Meter_Run_Status.NegCurr_Qudrant.Bit.Bit2=1;
      break;
    case QUADRANT4:
        Meter_Run_Status.NegCurr_Qudrant.Bit.Bit3=1;
      break;
    }
  }
  else
    Meter_Run_Status.NegCurr_Qudrant.Byte&=0xf0;
  
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit4=Measu_Status_Mode_ToPub_PUCK.A_APwrDir; 
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit5=Measu_Status_Mode_ToPub_PUCK.B_APwrDir; 
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit6=Measu_Status_Mode_ToPub_PUCK.C_APwrDir; 
    
        
  SET_STRUCT_SUM(Meter_Run_Status);  
}
/********************************************************************************

*********************************************************************************/
void Event_main_PUCK(INT8U Flag)
{
  if(Get_Sys_Status()!=SYS_NORMAL)  //ֻ��������Դ��������£��������ִ��
  {
    while(1)
     Task_Sleep();    
  }
  
  if(Get_Sys_Status()!=SYS_NORMAL) //ֻ��������ģʽ�£������¼��Ĵ���
    return ;
  
  if(Flag)
  { 
    Init_All_Event_Sram();
    Set_Cal_Event();  //�ϵ�󣬸���flash״̬����ʼ��У��״̬����ϵͳ����δ�趨�¼�״̬���Ժ�����¼�����    
    Init_Event_Instant_Para();
    Save_All_Loss_Data();
    OS_TimeDly_Sec(1);
    return ;
  }
  Emerg_Event_Proc();     //��ͻ���¼���ÿ10ms����������Channel_Data_Proc_PUCKStatus��ͬ��
  Event_Proc_Sec();       //�������¼���ÿ�봦��
 }  