#define MONITOR_C
#include "Includes.h"

void Monitor_Init()
{
  mem_set((void *)&Task_Monitor,0,sizeof(Task_Monitor),(void *)&Task_Monitor,sizeof(Task_Monitor));
  SET_STRUCT_SUM(Task_Monitor);
}

//������,�ǵ���OS_Tick_Task������ҲҪ�幷
void Clear_Task_Dog()
{
  INT8U Re,Cur_Task_ID;
  INT8U Cur_Task_Num;

#if OS_USE_CS==1 
  Re=CHECK_STRUCT_VAR(Task_Info);
  ASSERT(A_WARNING,1==Re);
#endif
  
  Cur_Task_ID=Get_Cur_Task_ID();
  if(ASSERT(A_WARNING,Cur_Task_ID<OS_TASK_NUM))
    return;
  
  Cur_Task_Num=Get_Cur_Task_Num();
  if(Cur_Task_Num>1)
  {
    Re=CHECK_STRUCT_SUM(Task_Monitor);
    if(ASSERT(A_WARNING,1==Re))
      return;
    
    Task_Monitor.Counts[Cur_Task_ID]=0;
    SET_STRUCT_SUM(Task_Monitor);
  }
}

//�����ش���
void Task_Monitor_Proc()
{
  static INT32U Sec_Bak=0xFFFFFFFF;
  INT8U i,Re;
  static INT8U Counts=0;
  
  //ÿ���ӲŽ���һ�����������
  if(Sec_Bak!=Sec_Timer_Pub)
  {
    Counts++;
    if(Counts>=60)//ÿ���Ӵ�ӡһ�ζ�ջ��ʹ�����
    {
      Counts=0;
      Print_Task_Stk_Left();
    }
    
    Sec_Bak=Sec_Timer_Pub;
    
#if OS_USE_CS==1     
    Re=CHECK_STRUCT_VAR(Task_Info);
    ASSERT(A_WARNING,1==Re);
#endif
    
    for(i=0;i<OS_TASK_NUM && i<Task_Info.Cur_Task_Num;i++)
    {
      //����û��˯�߶��� ����ļ������������Ϊ��ʱ
       if(Task_Monitor.Counts[i]>TASK_DOG_SEC)
       {
         //ĳ�����Ѿ�˯����,�ҵ�ǰ�����ڵ�Դ����״̬��,���ô������������
         if(Check_Task_Sleep(i)==1 && Check_Sys_Status()!=SYS_NORMAL)
         {
           Task_Monitor.Counts[i]=0;
         }
         else
         {
           DEBUG_PRINT(HUCK,DEBUG_0,"Task %d,Name:%s dog overflowed",i,Tcb[i].Name);
           Soft_Reset();
         }
       }
       Task_Monitor.Counts[i]++;
    }
    SET_STRUCT_SUM(Task_Monitor);
  }
}
#undef MONITOR_C
