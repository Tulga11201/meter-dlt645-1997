#define OS_EXT_C
#include "OS_Core.h"
#include "Pub_Debug.h"

//���ĳ�����ջʹ���������ջʹ�������򷵻�0�����򷵻�1
//��Ҫ�ǲ�ѯ��ջ��ͷβ�ֽ�,ͷβ�ֽ���ȷ,������Ϊ��ջ����û�б��ƻ�����Խ��
OS_INT8U Check_Task_Stk(OS_INT8U Task_ID)
{
  OS_ASSERT(Task_ID<Task_Info.Cur_Task_Num);
  
#if OS_STK_GROWTH==1//��ջ�Ӹߵ�ַ��͵�ַ�ݼ� 
  if(CHK_BYTE==*(OS_INT8U *)(Tcb[Task_ID].pStk) &&\
     CHK_BYTE==*(OS_INT8U *)(Tcb[Task_ID].pStk-Tcb[Task_ID].Stk_Size/sizeof(OS_STK)+1))
    return 1;
#else  //��ջ�ӵ͵�ַ��ߵ�ַ����
  if(CHK_BYTE==*(OS_INT8U *)(Tcb[Task_ID].pStk) &&
     CHK_BYTE==*(OS_INT8U *)(Tcb[Task_ID].pStk+Stk_Size-1))
    return 1;
#endif
  OS_ASSERT(0);
  return 0;
}

//������������ջ��ʹ�����
OS_INT8U Check_All_Task_Stk()
{
  OS_INT8U i;
#if OS_USE_CS==1
  OS_INT8U Re;
  
  Re=OS_CHECK_STRUCT_VAR(Task_Info);
  OS_ASSERT(1==Re);
#endif
  
  for(i=0;i<Task_Info.Cur_Task_Num;i++)
  {
    if(Check_Task_Stk(i)==0 || Calc_Stk_Left(i)<MIN_STK_SIZE)
    {
      OS_ASSERT(0);//�����ջ�д�,��ʾ����
      return 0;
    }
  }
  return 1;
}

//���ĳ������Ķ�ջ��ʣ����ٿռ�
OS_INT16U Calc_Stk_Left(OS_INT8U Task_ID)
{
  OS_INT16U i;
  OS_INT8U *p;
  
  OS_ASSERT(Task_ID<Task_Info.Cur_Task_Num);
  
#if OS_STK_GROWTH==1//��ջ�Ӹߵ�ַ��͵�ַ�ݼ� 
  p=(OS_INT8U *)(Tcb[Task_ID].pStk-Tcb[Task_ID].Stk_Size/sizeof(OS_STK)+1);
#else  //��ջ�ӵ͵�ַ��ߵ�ַ����
  p=(OS_INT8U *)(Tcb[Task_ID].pStk);
#endif  
  
  i=0;
  while(1)
  {
    if(CHK_BYTE!=*(p+i))
      return i;
    i++;
  } 
}

//��ȡ��ǰ�����ID��
OS_INT8U Get_Cur_Task_ID()
{
  OS_INT8U Re;
  
  Re=OS_CHECK_STRUCT_VAR(Task_Info);
  if(1!=Re)
    OS_ASSERT(0);
  
  return Task_Info.Cur_Task_ID;
}

//��ȡ��ǰ��������
OS_INT8U Get_Cur_Task_Num()
{
  OS_INT8U Re;
  
  Re=OS_CHECK_STRUCT_VAR(Task_Info);
  if(1!=Re)
    OS_ASSERT(0);

  return Task_Info.Cur_Task_Num;
}


//��ӡ��λǰ�������ջʹ�����,�����������Ѿ������ú���ܵ��øú���
void Print_Task_Stk_Left_Bef_Rst()
{
#if OS_RST_CHK_STK==1
  OS_INT8U i;
  
#if OS_USE_CS==1
  OS_INT8U Re;
  
  Re=OS_CHECK_STRUCT_VAR(Task_Info);
  OS_ASSERT(1==Re);
#endif
  
  for(i=0;i<Task_Info.Cur_Task_Num;i++)
    DEBUG_PRINT(HUCK,DEBUG_0,"Task %d Stack Left bef Rst:%d\r\n",i,Task_Stk_Left[i]);  
#endif
}

//��ӡ���������ջ��Ϣ
void Print_Task_Stk_Left()
{
  OS_INT8U i;
  DEBUG_PRINT(HUCK,DEBUG_0,"------Task Stack Left Stat----");
  for(i=0;i<Task_Info.Cur_Task_Num;i++)
    DEBUG_PRINT(HUCK,DEBUG_0,"Task %s Stack Left:%d",Tcb[i].Name,Calc_Stk_Left(i));
}

//���������������Ƿ���ȷ��ע�⣺�ú����в��ܵ��ò���ϵͳ�ṩ�ĵ���
void OS_Task_Context_Chk()
{
  OS_INT8U Re,Next_Task_ID;

  Next_Task_ID=(Task_Info.Cur_Task_ID+1)%Task_Info.Cur_Task_Num;  
  Re=OS_CHECK_STRUCT_VAR(Tcb[Next_Task_ID]);
  if(0==Re)
    OS_ASSERT(0);
  
  Re=Check_Task_Stk(Next_Task_ID);
  if(0==Re)
    OS_ASSERT(0);
  /*
#if OS_USE_CS==1
  OS_INT8U Re,Next_Task_ID;

  OS_SET_STRUCT_SUM(Tcb[Task_Info.Cur_Task_ID]);
  Next_Task_ID=(Task_Info.Cur_Task_ID+1)%Task_Info.Cur_Task_Num;  
  Re=OS_CHECK_STRUCT_SUM(Tcb[Next_Task_ID]);
  OS_ASSERT(1==Re);

  Re=Check_Task_Stk(Next_Task_ID);
  OS_ASSERT(1==Re);
#endif
  */
}

//ʱ��Tick���Ӻ���
void OS_Tick_Hook()
{
  static OS_INT16U i=0;
  
  i+=OS_MS_PER_TICK;
  if(i>=1000)
  {
    i=0;
    Sec_Timer_Pub++;
  }
}
#undef OS_EXT_C

