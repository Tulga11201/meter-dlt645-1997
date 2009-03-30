#define EVENT_DATA_C
#include <includes.h>

//��鵱ǰ�¼��Ƿ��ڷ���
INT8U Check_Event_Occuring(INT8U Event_ID)
{
  if(Read_Event_Status(Event_ID)==1)
    return 1;
  else
    return 0;
}

void Event_Data_Proc(INT8U Event_ID,INT8U Occur_Or_End)
{
  INT8U Total_Event_ID;
  
  DEBUG_PRINT(HUCK,DEBUG_0,"\r\n++++++++++Event Data Proc,ID:%d,Occur_Or_End:%d++++++++++",Event_ID,Occur_Or_End);
  OS_Sem_Pend(PUB_BUF0_SEM_ID);//����PUB_BUF0������ĺ�����Ҫ�õ�����ź���
  
  Event_Cumu_Data_Proc(Event_ID,Occur_Or_End,EVENT_REAL);
  
  Total_Event_ID = Get_Total_Event_ID(Event_ID);//���¼���Ӧ���ܼ���ҲҪ����
  if(Total_Event_ID != NULL_EVENT_ID)
  {
    DEBUG_PRINT(HUCK, DEBUG_0, "Total Event Proc");
    Event_Cumu_Data_Proc(Total_Event_ID,Occur_Or_End,EVENT_REAL);
  }
  Event_MultiTimes_Proc(Event_ID,Occur_Or_End,EVENT_REAL);
  
  OS_Sem_Post(PUB_BUF0_SEM_ID);//�ͷ�PUB_BUF0 
  DEBUG_PRINT(HUCK,DEBUG_0,"++++++++++Event Data Proc:End++++++++++\r\n");
}


//����¼�
void Clear_Event_Data()
{
  if(Check_Clear_Data_Authority()==0)
    return;
  
  if(CLEAR_EVENT_FLAG!=Check_Clear_Data_Flag() &&
     CLEAR_ALL_FLAG!=Check_Clear_Data_Flag())
    return;
  DEBUG_PRINT(HUCK,DEBUG_0,"Clear_Event_Data!!!");
  //Set_Def_Event_Data();
  Set_Def_Event_Cumu0_Data();
  Clear_Event_MultiTimes_Data();
  Clr_All_Event_Sram(); //����ڴ��е��¼����ݣ����¿�ʼ�ж��¼�
}

//����Ĭ�ϵ��¼�����������
void Set_Def_Event_Data()
{
  Set_Def_Event_Cumu0_Data();
  Set_Def_Event_MultiTimes_Data();
}


#undef EVENT_DATA_C


