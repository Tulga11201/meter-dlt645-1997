#define PUB_DEBUG_C
#include "includes.h"
#include "OS_Port.h"

extern void OS_vsPrintf(CONST OS_INT8S *format, va_list ap);
//����
//x����������ʱ����1������ʱ����0
//�������Է��㺯�������������ж�:
//
// if(ASSERT(A_WARNING,x))
//   return 0;
//

//������Ϣ���
/*****************************************
����ԭ�ͣ�
INT8U DEBUG_BUF_PRINT(INT8U Src[],INT16U SrcLen,INT8U Flag)
�������ܣ�
��ӡ������Ϣ�����Խ�Src�������еı�����print����
��ڲ�����
Src,Դ���ݻ�����
SrcLen,Դ���ݳ���
Flag,0��ʾ��ʮ�����Ʒ�ʽ��ӡ,1��ʾ��ʮ���Ʒ�ʽ��ӡ
Num,ûNum�����ִ�һ�����з�
���ڲ�������ӡ��Ϣ����
******************************************/
INT8U DEBUG_BUF_PRINT(INT8U Src[],INT16U SrcLen,INT8U Flag,INT8U Num)
{
#ifdef PRINT_TYPE
  INT16U i;

  if(Check_Debug_En()==0)//���ǹ���״̬����ӡ
    return 0;
  
  if(PRINT_TYPE==PRINT_NULL)
    return 0;

  i=0;
  if(Flag==PRINT_HEX) //hex��ӡ
  {
    for(i=0;i<SrcLen;i++)
    {
      if(Num!=0 && i%Num==0)
        OS_Debug_Print("\r\n");
      
      OS_Debug_Print("%2x ",Src[i]);
    }
  }
  else//%d
  {
    for(i=0;i<SrcLen;i++)
    {
      if(Num!=0 && i%Num==0)
        OS_Debug_Print("\r\n");
      
      OS_Debug_Print("%3d ",Src[i]);
    }
  }
  return 1;
#endif

}

/*****************************************
����ԭ�ͣ�
INT16U DEBUG_PRINT(char *format,...)
�������ܣ�
��ӡ������Ϣ�����Խ�������Ϣ��ӡ�����ڻ�IAR��i/o������
��ڲ����������б�
���ڲ�������ӡ��Ϣ����
******************************************/
INT16U Debug_Print(char *format,...)
{

#ifdef PRINT_TYPE
  va_list ap;

  if(Check_Debug_En()==0)//���ǹ���״̬����ӡ
    return 0;
  
  if(Task_Info.Cur_Task_Num==0)
    OS_Debug_Print("\r\nMAIN:");
  else
    OS_Debug_Print("\r\n%s:",Tcb[Task_Info.Cur_Task_ID].Name);
/*    
  if(ID==HUCK)
    ;//Debug_Out_Public_Puck("HUCK:",5);
  else if(ID==PUCK)
    ;//Debug_Out_Public_Puck("PUCK:",5);
  else if(ID==SUCK)
    ;//Debug_Out_Public_Puck("SUCK:",5);
  else if(ID==LUCK)
    ;//Debug_Out_Public_Puck("LUCK:",5);
  else if(ID==ASSERT_ID)
    Debug_Out_Public_Puck("ASSERT:",7);
  else if(ID==TEST)
    Debug_Out_Public_Puck("TEST:",5);
*/  
  if(PRINT_TYPE==PRINT_NULL)
    return 0;
  else
  {
    va_start(ap,format);
    OS_vsPrintf(format,ap);
    va_end(ap);
    return 1;
  }
#else
  return 0;
#endif
}

#undef PUB_DEBUG_C

