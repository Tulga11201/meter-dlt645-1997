#define OS_SEM_C
#include "OS_Core.h"

void OS_Sem_Clr()
{
  OS_ASSERT(OS_SEM_NUM<=32);
  OS_memset((void *)&OS_Sem,0,sizeof(OS_Sem),(void *)&OS_Sem,sizeof(OS_Sem));
#if OS_USE_CS==1
  OS_SET_STRUCT_SUM(OS_Sem);
#endif  
}

//�����ź���,�ź�����ID��Ӧ�ó����Լ��̶�
//ValΪ�ź����ĳ�ʼֵ��1��ʾ��Դ��ռ�ã�0��ʾ��Դ���ͷ�
//�����ɹ�����1��ʧ�ܷ���0
OS_INT8U OS_Sem_Init(OS_INT8U ID,OS_INT8U Val)
{
#if OS_USE_CS==1
  OS_INT8U Re;
  
  Re=OS_CHECK_STRUCT_SUM(OS_Sem);
  OS_ASSERT(1==Re);
#endif
  
  if(ID>OS_SEM_NUM-1)
    return 0;
  
  OS_Sem.Sem_Num++;
  if(Val==0)
    OS_CLR_BIT(OS_Sem.Sem,ID);
  else
    OS_SET_BIT(OS_Sem.Sem,ID);
  
#if OS_USE_CS==1
  OS_SET_STRUCT_SUM(OS_Sem);//����У���
#endif
  
  return 1; 
}

//Post�ź���,�ɹ�����1��ʧ�ܷ���0
OS_INT8U OS_Sem_Post(OS_INT8U ID)
{
#if OS_USE_CS==1
  OS_INT8U Re;
  
  Re=OS_CHECK_STRUCT_SUM(OS_Sem);
  OS_ASSERT(1==Re);
#endif
  
  if(ID>=OS_SEM_NUM)
  {
    OS_ASSERT(0);
    return 0;
  }
  
  OS_CLR_BIT(OS_Sem.Sem,ID);
  //���Ǹ���������Դ������Ϊ�Ǵ�����ͷ��ź���
  //��ϵͳ�е��ź����������ڻ�����ʣ�����ź�����������ͷ���ÿ�������ж��ǳɶԳ��ֵ�
  if(OS_GET_BIT(OS_Sem.Task_Hold_Flag[Task_Info.Cur_Task_ID],ID)==0)
  {
    OS_ASSERT(0);  
    return 0;
  }
  
  OS_CLR_BIT(OS_Sem.Task_Hold_Flag[Task_Info.Cur_Task_ID],ID);//�������ռ���ź�����־  
#if OS_USE_CS==1
  OS_SET_STRUCT_SUM(OS_Sem);
#endif
  //OS_TimeDly_Ms(10);
  
  return 1;
}
#if OS_SEM_LOCK_CHK==1
//��ѯ��ǰ����������ź����Ƿ�����,��������������1�����򷵻�0
OS_INT8U OS_Check_Task_Sem_Lock(OS_INT8U Task_ID)
{
  OS_INT32U Wait_Flag;
  OS_INT8U i;
  
  Wait_Flag=OS_Sem.Task_Wait_Flag[Task_ID];  
  while(1)
  {
    for(i=0;i<Task_Info.Cur_Task_Num;i++)
    {
      if((OS_Sem.Task_Hold_Flag[i] & Wait_Flag)!=0)//��ǰ�ȴ����ź�����������i��ռ�е��ź���
      {
         Wait_Flag=OS_Sem.Task_Wait_Flag[i];//�滻�ȴ��ź���
         //������ȴ����ź�������Task_IDռ�е��ź������γ���һ��������Ȧ
         if((Wait_Flag & OS_Sem.Task_Hold_Flag[Task_ID])!=0)
           return 1;
         else if(Wait_Flag==0)//û�еȴ��ź����ˣ���Ȼ���γ�Ȧ
           return 0;
         else  //���´ӵ�0���������
           break;
      }
    }
    //û��һ������ռ�е��ź�������Wait_Flag˵���޷��γ�һ��Ȧ����������
    if(i==Task_Info.Cur_Task_Num)
      return 0;
  }
}
#endif

//�����ź���,�ɹ�����1��ʧ�ܷ���0���߲����� 
OS_INT8U OS_Sem_Pend(OS_INT8U ID)
{
#if OS_USE_CS==1
  OS_INT8U Re;
  
  Re=OS_CHECK_STRUCT_SUM(OS_Sem);
  OS_ASSERT(1==Re);
#endif
  
  if(ID>=OS_SEM_NUM)
  {
    OS_ASSERT(0);
    OS_Debug_Print("OS:Task %d pend sem %d ID error\r\n",Task_Info.Cur_Task_ID,ID);
    return 0;
  }
  
#if OS_SEM_LOCK_CHK==1
  OS_SET_BIT(OS_Sem.Task_Wait_Flag[Task_Info.Cur_Task_ID],ID);//��������ȴ��ź�����־
  OS_SET_STRUCT_SUM(OS_Sem);
  //�ڵȴ������ź���������£�ÿ��OS_SEM_CHK_LOCK_TIME S���һ���Ƿ���������״̬
  while(1)
  {
    OS_Waitfor_Sec(OS_GET_BIT(OS_Sem.Sem,ID)==0,OS_SEM_CHK_LOCK_TIME);
    //�ȴ�1S����Ȼ���벻���ź���������Ҫ��ѯ�Ƿ�����������
    if(OS_GET_BIT(OS_Sem.Sem,ID)!=0)
    {
      if(OS_Check_Task_Sem_Lock(Task_Info.Cur_Task_ID))//��ǰ����������ź�����������
      {
        OS_ASSERT(0);
        OS_Debug_Print("OS:Task %d pend sem %d locked!\r\n",Task_Info.Cur_Task_ID,ID);
        return 0;
      }
    }
    else//�Ѿ����뵽
    {
      OS_CLR_BIT(OS_Sem.Task_Wait_Flag[Task_Info.Cur_Task_ID],ID);//�������ȴ��ź�����־
      OS_SET_BIT(OS_Sem.Task_Hold_Flag[Task_Info.Cur_Task_ID],ID);//��������ռ���ź�����־
      break;
    }
  }
#else
  OS_Waitfor(OS_GET_BIT(OS_Sem.Sem,ID)==0);
#endif
  
  OS_SET_BIT(OS_Sem.Sem,ID);
   
#if OS_USE_CS==1
  OS_SET_STRUCT_SUM(OS_Sem);
#endif   
   return 1;  
}


#undef OS_SEM_C

