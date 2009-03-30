#ifndef OS_CORE_H
#define OS_CORE_H

#include "OS_Cfg.h"
#include "OS_Port.h"
#include "OS_Sem.h"
#include "OS_Ext.h"
#include "OS_Pub.h"

#if OS_USE_LIB
#include "setjmp.h"
#endif

#undef OS_EXT
#ifndef OS_CORE_C
#define OS_EXT extern
#else
#define OS_EXT
#endif

//#define OS_VERSION 106 //2008.03.29
//#define OS_VERSION 107 //2008.04.08
//#define OS_VERSION 108 //2008.04.19
//#define OS_VERSION 109 //2008.05.06
//#define OS_VERSION 110 //2008.06.12
//#define OS_VERSION 111 //2008.06.29
//#define OS_VERSION 112 //2008.07.25
//#define OS_VERSION 113 //2008.09.28
#define OS_VERSION 114 //2008.10.08

//�����ջ�����
#define CHK_BYTE (OS_INT8U)0x5A

#if OS_USE_LIB
#define OS_Task_Env jmp_buf
#define OS_Save_Env(x) setjmp(x)
#define OS_Restore_Env(x) longjmp(x,1) 
#endif

//��������λ������
#define OS_SET_BIT(x,y) (x)|=0x01<<(y)
#define OS_CLR_BIT(x,y) (x)&=~(0x01<<(y))
#define OS_GET_BIT(x,y) (((x)>>(y))&0x01)

//4����������ʱ��,�������
#define OS_TimeDly_Ms(x) OS_TimeDly(0,0,0,x)
#define OS_TimeDly_Sec(x) OS_TimeDly(0,0,x,0)
#define OS_TimeDly_Min(x) OS_TimeDly(0,x,0,0)
#define OS_TimeDly_Hou(x) OS_TimeDly(x,0,0,0)

extern void Power_Down_Check();
extern void Task_Switch_Hook();
//�����ȴ�,ע��Condition�е�ȫ�ֱ���������Volatile����
#define OS_Waitfor(Condition)\
do{ OS_Save_Env(Tcb[Task_Info.Cur_Task_ID].Env);\
    Power_Down_Check();\
    if(!(Condition))\
    { OS_Task_Switch();\
      OS_Restore_Env(Tcb[Task_Info.Cur_Task_ID].Env);\
    }\
  }while(0)

//����ʱ�������ȴ�,ע��Condition�е�ȫ�ֱ���������Volatile����
#define OS_Waitfor_HMSM(Condition,Hour,Min,Sec,m_Sec)\
  do{Tcb[Task_Info.Cur_Task_ID].Time_Dly=Hour*3600L*1000L+Min*60L*1000L+Sec*1000L+m_Sec;\
     OS_Waitfor((Condition||Tcb[Task_Info.Cur_Task_ID].Time_Dly==0));\
   }while(0)

//�ĸ������Ĵ���ʱ�������ȴ�,�������,ע��Condition�е�ȫ�ֱ���������Volatile����
#define OS_Waitfor_Hou(Condition,Hou) OS_Waitfor_HMSM(Condition,Hou,0,0,0) 
#define OS_Waitfor_Min(Condition,Min) OS_Waitfor_HMSM(Condition,0,Min,0,0)
#define OS_Waitfor_Sec(Condition,Sec) OS_Waitfor_HMSM(Condition,0,0,Sec,0)
#define OS_Waitfor_Ms(Condition,Ms) OS_Waitfor_HMSM(Condition,0,0,0,Ms)


//����������ƿ���Ϣ
typedef struct{
  OS_INT16U Head;
  
  OS_Task_Env Env;          //��ǰ���񻷾�
  void (*pEntry)();         //�������
  OS_STK *pStk;             //��ջ��ʼָ��
  OS_INT16U Stk_Size;       //��ջ��С

#if OS_USE_TASK_NAME       //ʹ����������
  OS_INT8S Name[OS_TASK_NAME_SIZE];//��������,�ౣ��һ���ֽ���0
#endif

#if OS_USE_CS==1//ʹ��У���,���ڱ���TCB��Ϣ
  OS_INT8U CS[OS_CS_BYTES];
#endif
  
  OS_INT32U Time_Dly;       //��ʱʱ�䣬��λms
  
  OS_INT16U Tail;
}OS_TCB;

typedef struct{
  OS_INT8U Head;
  
  OS_INT16U Cur_Task_ID;  //��ǰ����ID��
  OS_INT16U Cur_Task_Num; //��ǰ�������� 
  
#if OS_USE_CS==1//ʹ��У���,���ڱ���Task_Info��Ϣ
  OS_INT8U CS[OS_CS_BYTES];
#endif
  
  OS_INT8U Tail;
  
}OS_Task_Info;

#ifdef OS_CORE_C //ֻ�ṩ��OS_Core.c�ļ�
OS_EXT OS_SP volatile Old_SP;//���ڴ�������ʱ�����ϵ������ջָ��,SAVE_TASK_SP()����ǰSP���浽Old_SP��
OS_EXT OS_SP volatile New_SP;//���ڴ�������ʱ�ָ��ϵ������ջָ��,RESTORE_TASK_SP()����ǰNew_SP���浽SP��
#if OS_USE_TICK_ISR
OS_EXT OS_INT8U volatile Tick_ISR_Flag;//�жϱ�־���ñ�־��1��ʾһ��ʱ�����ڹ�ȥ
#endif
#endif

OS_EXT OS_TCB Tcb[OS_TASK_NUM];//���������Ϣ��
OS_EXT OS_Task_Info volatile Task_Info;//��ǰ������Ϣ

#if OS_RST_CHK_STK==1
OS_EXT OS_INT16U Task_Stk_Left[OS_TASK_NUM];//���ڴ洢�쳣��λǰ�Ķ�ջʣ����
#endif

OS_EXT void OS_Init();
OS_EXT void Change_Cur_Task_ID();
OS_EXT void OS_Check_TaskDly();
OS_EXT void OS_Task_Switch();
OS_EXT OS_INT8U OS_Create_Task(void(*Entry)(),OS_STK *pStk,OS_INT16U Stk_Size,OS_INT8U Name[]);
OS_EXT void OS_TimeDly(OS_INT32U Hour,OS_INT32U Min,OS_INT32U Sec,OS_INT32U m_Sec);
OS_EXT void OS_Start();

#if OS_USE_TICK_ISR
OS_EXT void OS_Tick_ISR();//����ʱ���жϷ���
#endif

#endif
