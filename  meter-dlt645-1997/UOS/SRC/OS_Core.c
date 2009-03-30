#define OS_CORE_C
#include "OS_Core.h"

#pragma optimize=none
//����������
OS_INT8U OS_Create_Task(void(*Entry)(),OS_STK *pStk,OS_INT16U Stk_Size,OS_INT8U Name[])
{
  static OS_INT8U i=0;//ʹ�þ�̬�ֲ���������ֹ�����ı仯ʱ�ֲ������ı仯
  static OS_INT8U Task_ID;

  if(Task_Info.Cur_Task_Num>=OS_TASK_NUM)
  {
    OS_ASSERT(0);
    return 0;  
  }
  
  i=0;
  Task_ID=Task_Info.Cur_Task_Num;
  
  Task_Info.Cur_Task_Num++; 
#if OS_USE_CS==1
    OS_SET_STRUCT_SUM(Task_Info);
#endif
  
  OS_INIT_STRUCT_VAR(Tcb[Task_ID]);
  
  Tcb[Task_ID].pEntry=Entry;  
  Tcb[Task_ID].pStk=pStk;
  Tcb[Task_ID].Stk_Size=Stk_Size;
  Tcb[Task_ID].Time_Dly=0;
  
#if OS_RST_CHK_STK==1
  Task_Stk_Left[Task_ID]=Calc_Stk_Left(Task_ID);
#endif
  
  //����ջ���ݳ�ʼ���������ַ�����ͳ�ƶ�ջ����
  //ͬʱ������ջ��ͷβ�����ֽڣ������ж϶�ջ�Ƿ�������߱�����
#if OS_STK_GROWTH==1//��ջ�Ӹߵ�ַ��͵�ַ�ݼ�
  OS_memset(pStk-Stk_Size/sizeof(OS_STK)+1,CHK_BYTE,Stk_Size,pStk-Stk_Size/sizeof(OS_STK)+1,Stk_Size);
  pStk--;
#else  //��ջ�ӵ͵�ַ��ߵ�ַ����
  OS_memset((INT8U *)pStk,CHK_BYTE,Stk_Size,(INT8U *)pStk,Stk_Size);
  pStk++;
#endif
  
  SAVE_TASK_SP();//��SP���浽Old_SP
  New_SP=(OS_SP)pStk;
  RESTORE_TASK_SP();//��New_SP�ָ���SP��

  if(OS_Save_Env(Tcb[Task_ID].Env)==0)//���浱ǰ��������
  { 
    New_SP=Old_SP;
    RESTORE_TASK_SP();//�ָ��ϵ�SP

#if OS_USE_TASK_NAME //���ʹ������ 
    while(i<OS_TASK_NAME_SIZE-1 && Name[i]!=0)
    {
      Tcb[Task_ID].Name[i]=Name[i];  
      i++;
    }
    Tcb[Task_ID].Name[i]=0;
#else
    Name[i]=Name[i];//��ֹ���뾯��
#endif
    
#if OS_USE_CS==1
    OS_SET_STRUCT_SUM(Tcb[Task_ID]);
#endif 

  }
  else//else�ڳ�����������������
  {
    Tcb[Task_Info.Cur_Task_ID].pEntry();//Entry���л��������ջ����ܶ�ʧ����˲���pEntry  
  }
  return 1;
}

//�޸ĵ�ǰ����ID���Ա���ȵ���һ������
void Change_Cur_Task_ID()
{
  /*
#if OS_USE_CS==1
  OS_INT8U Re;
  
  Re=OS_CHECK_STRUCT_SUM(Task_Info);
  OS_ASSERT(1==Re);
#endif 
*/
  OS_INT8U Re;
  
  Re=OS_CHECK_STRUCT_VAR(Task_Info);
  if(0==Re)
    OS_ASSERT(0);
  
  Task_Info.Cur_Task_ID++;
  if(Task_Info.Cur_Task_ID>=Task_Info.Cur_Task_Num) 
    Task_Info.Cur_Task_ID=0;
/*  
#if OS_USE_CS==1
  OS_SET_STRUCT_SUM(Task_Info);
#endif
*/  
}

//����������ʱʱ��
void OS_Check_TaskDly()
{
  OS_INT16U i;
  OS_INT8U Flag=0;
  
#if OS_USE_TICK_ISR //ʹ��OS_Tick_ISR��Tick_ISR_Flag��1
  if(1==Tick_ISR_Flag)//���ж��иñ�־��1��ʾһ��ʱ�����ڵ�
  {
    Tick_ISR_Flag=0;
    Flag=1;
  }
#else
  if(OS_Check_Tick())//��ѯ��ʱ����ȷ��ʱ�����ú������ݾ���CPU��ʵ��
  {
    OS_Tick_Hook();//ʱ��Hook����
    Flag=1;
  }
#endif
  
  if(1==Flag)//һ��ʱ������
  {
    for(i=0;i<Task_Info.Cur_Task_Num;i++)//�޸�ÿ���������ʱʱ��
    {
      if(0!=Tcb[i].Time_Dly)//����ʱ��0�ĺ�������������ʱ
      {
        /*
    #if OS_USE_CS==1
        Flag=OS_CHECK_STRUCT_SUM(Tcb[i]);//�ȼ��У���
        OS_ASSERT(1==Flag);
    #endif
        */
        
        //��ÿ���������ʱ���м���
        if(Tcb[i].Time_Dly>OS_MS_PER_TICK)
          Tcb[i].Time_Dly-=OS_MS_PER_TICK;
        else
          Tcb[i].Time_Dly=0;
     /*   
    #if OS_USE_CS==1
        OS_SET_STRUCT_SUM(Tcb[i]);//����У���
    #endif
     */
      }
    }
  }
}

void OS_Task_Switch()
{
  OS_Task_Context_Chk();
  OS_Check_TaskDly();
  Task_Switch_Hook();
  Change_Cur_Task_ID();
  OS_Restore_Env(Tcb[Task_Info.Cur_Task_ID].Env);   
}

#if OS_USE_TICK_ISR //ʹ���ж���ΪTick��׼
void OS_Tick_ISR() //����ms��ʱ��,ÿ�����жϵ���
{
  Tick_ISR_Flag=1;
  OS_Tick_Hook();
}
#endif

//��ʱ����
void OS_TimeDly(OS_INT32U Hour,OS_INT32U Min,OS_INT32U Sec,OS_INT32U m_Sec)
{
  Tcb[Task_Info.Cur_Task_ID].Time_Dly=Hour*3600L*1000L+Min*60L*1000L+Sec*1000L+m_Sec;
  if(Tcb[Task_Info.Cur_Task_ID].Time_Dly<=OS_MS_PER_TICK)//��������ʱС��һ��Tick��ʱ��
    Tcb[Task_Info.Cur_Task_ID].Time_Dly+=OS_MS_PER_TICK;
  OS_Waitfor((Tcb[Task_Info.Cur_Task_ID].Time_Dly==0));
}

//����ϵͳ��������
void OS_Start()
{
#if OS_USE_IDLE_TASK==1
  OS_Create_Task(&OS_Idle_Task,&Idle_Task_STK[OS_IDLE_TASK_STK_SIZE-1],100,"OS_Idle_Task");
#endif
  OS_Restore_Env(Tcb[0].Env);//�л�����һ�������ִ�л���   
}

//����ϵͳ��ʼ������
void OS_Init()
{
#if OS_USE_TICK_ISR==1
  Tick_ISR_Flag=0;
#endif
  
  Task_Info.Cur_Task_ID=0;
  Task_Info.Cur_Task_Num=0;
  OS_INIT_STRUCT_VAR(Task_Info);

#if OS_USE_CS==1
  OS_SET_STRUCT_SUM(Task_Info);
#endif
}
#undef OS_CORE_C
