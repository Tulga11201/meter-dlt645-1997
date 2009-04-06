#define TASKPRG_CFG_C
#include "TaskProc.h"
#include "Includes.h"
#include "pub.h"


/**********************************************************************************
�������ܣ�����ڹ����⹷
��ڣ�    
���ڣ�    
**********************************************************************************/
void Clr_Ext_Inter_Dog(void)
{    
  Clear_CPU_Dog();    //��CPU�ڲ����Ź�
  Clear_Ext_Dog();    //��CPU�ⲿ���Ź�
}
/**********************************************************************************
�������ܣ�������п��Ź�
��ڣ�    
���ڣ�    
**********************************************************************************/
void Clear_All_Dog(void)
{    
  Clear_Task_Dog();   //�������Ź�
  Clear_CPU_Dog();    //��CPU�ڲ����Ź�
  Clear_Ext_Dog();    //��CPU�ⲿ���Ź�
}
/**********************************************************************************
�������ܣ���������������
��ڣ�    
���ڣ�    
**********************************************************************************/
void Creat_AllSub_Tasks(void)
{ 
#ifdef TASK_ENERGE_HUCK_EN  
  OS_Create_Task(&AppEnergeTask_HUCK,&AppEnergTaskStk_huck[TASK_ENERGE_SIZE_HUCK-1],sizeof(AppEnergTaskStk_huck),"AppEnergeTask_HUCK");
#endif  
  
#ifdef TASK_LCD_LUCK_EN  
  OS_Create_Task(&AppLCDTask_LUCK,&AppLCDTaskStk_LUCK[TASK_LCD_SIZE_LUCK-1],sizeof(AppLCDTaskStk_LUCK),"AppLCDTask_LUCK");
#endif
  
#ifdef TASK_MEASU_PUCK_EN
  OS_Create_Task(&AppMeasuTask_PUCK,&AppMeasuTaskStk_PUCK[TASK_MEASU_SIZE_PUCK-1],sizeof(AppMeasuTaskStk_PUCK),"AppMeasuTask_PUCK");
#endif
  
  
#ifdef TASK_CHANNEL_PUCK_EN
  OS_Create_Task(&AppChannelTask_PUCK,&AppChannelTaskStk_PUCK[TASK_CHANNEL_SIZE_PUCK-1],sizeof(AppChannelTaskStk_PUCK),"AppChannelTask_PUCK");
 #endif
  
  
#ifdef TASK_EVENT_PUCK_EN 
  OS_Create_Task(&AppEventTask_PUCK,&AppEventTaskStk_PUCK[TASK_EVENT_STK_SIZE_PUCK-1],sizeof(AppEventTaskStk_PUCK),"AppEventTask_PUCK");
#endif
  
  
#ifdef TASK_FREEZ_HUCK_EN  
  OS_Create_Task(&AppFreezeTask_HUCK,&AppFreezTaskStk_HUCK[TASK_FREEZ_SIZE_HUCK-1],sizeof(AppFreezTaskStk_HUCK),"AppFreezeTask_HUCK");
#endif
  
  
#ifdef TEST_MODE  
  OS_Create_Task(&AppTestTask_HUCK,&AppTestTaskStk_HUCK[TASK_TEST_SIZE_HUCK-1],sizeof(AppTestTaskStk_HUCK),"AppTestTask_HUCK");
#endif
  
  DEBUG_PRINT(HUCK,DEBUG_0,"All Tasks Created Succeed!");
}

void Main_Init_Print()
{
  Assert_Info.Flag=0;//��ֹ�������뱨��
  INIT_STRUCT_VAR(Assert_Info);
  
  Init_DebugChanel_PUCK(1);     //��ʼ�����Դ��ڣ����ж�����״̬
  OS_Debug_Print("\r\n---------------SYSTEM START----------------");      //�ϵ��ǿ�ƴ�ӡ��λ��Ϣ
  OS_Debug_Print("\r\n---------------SYSTEM START----------------");      //�ϵ��ǿ�ƴ�ӡ��λ��Ϣ
  OS_Debug_Print("\r\n---------------SYSTEM START----------------");      //�ϵ��ǿ�ƴ�ӡ��λ��Ϣ
  OS_Debug_Print("\r\n----------Version:%s----------",COMM_PROTO_VERSION);      //�ϵ��ǿ�ƴ�ӡ��λ��Ϣ  
  Print_Reset_Source(); 

  OS_Assert_Ctrl(0xFF);//ǰ8������ȫ���򿪶���    
  ASSERT(A_WARNING,0);//��ʾ��λǰ�ĺ������ù켣

  Close_DebugChanel_PUCK(1);   //�رյ��Դ��ڣ����ж�����״̬
}
/**********************************************************************************
�������ܣ�������
��ڣ�    
���ڣ�    
**********************************************************************************/
void  Main_Task_PUB(void *p_arg)
{
  PROTO_DI DI;
  
  PD_DATA_PROC();//�����������    
  Clr_Screen_PUCK();  //�ϵ��ǿ����LCD��ʾ

  Main_Init_Print();  
  
  Energy_Task_Ram_Init();
  Init_Measure_Ram();  //��ʼ�����sram
  
  Test_HardWare_PUCK();  //�����ص�sram��ʼ���󣬲��ܵ��ã����ź�����ʼ��
  
  Init_Low_Power_Proc();
  //PD_INT_EN_Flag= 1;
  
  Check_Boot_On_Flag();//�ڹ���״̬�£�����Ƿ��ǵ�һ���ϵ�
  Read_Energy_Data_Para_For_Show();//�˴���ȡ�����Ա���Һ����ʾ

  Init_Measu_PUCK();  //��ʼ����������Һ��������ʾ�����¼��ж�  
  LCD_Init_PUCK();   //LCD��ʾ��ʼ���������ٶ���Ҫ
    
  Monitor_Init();
  Energy_Demand_Task_Init();   //���ڿ�����
  
  Extend_Init();
  Power_On_Event_Proc();//�ϵ���ǰһ�ε���ǰ���¼�����
  
#ifdef TEST_MODE
  Test_Unit();
#endif
  
  MAIN_INIT_END; //��ʼ����ɣ�
  Creat_AllSub_Tasks();
 
  for(;;)
  {
    Low_Power_Proc();
    Main_Chk_Data_Avail();
    Task_Monitor_Proc();
    Clear_Task_Dog();   //�������Ź�
    Clear_CPU_Dog();    //��CPU�ڲ����Ź�
    Get_Para_Modify(&DI);  //��ȡ������ÿ��������Ҫ�Ӳ����޸Ķ����ж�ȡ����
    Power_Down_Check();
    OS_TimeDly_Ms(100);   //100ms˯��
   }
}
/**********************************************************************************
�������ܣ���������
��ڣ�    
���ڣ�    
**********************************************************************************/
#ifdef TASK_MEASU_PUCK_EN
void  AppMeasuTask_PUCK (void *p_arg)
{
       
    (void)p_arg;
     //Measu_Main_Puck(1);
for(;;)	
  {  
      Measu_Main_Puck(0);
      Clear_Task_Dog();   //�������Ź�
      OS_TimeDly_Ms(100);//100Ms˯��
  }
}
#endif


/**********************************************************************************
�������ܣ�ͨ��ά������
��ڣ�    
���ڣ�    
**********************************************************************************/
#ifdef TASK_EVENT_PUCK_EN
void  AppEventTask_PUCK(void *p_arg)
{

    (void)p_arg;
    Event_main_PUCK(1);
    
for(;;)	
  { 
      Event_main_PUCK(0);      
      Clear_Task_Dog();   //�������Ź�
      OS_TimeDly_Ms(100);//100ms˯��
  }
}
#endif
/**********************************************************************************
�������ܣ���������
��ڣ�    
���ڣ�    
**********************************************************************************/
#ifdef TASK_FREEZ_HUCK_EN
void  AppFreezeTask_HUCK (void *p_arg)
{
       
    (void)p_arg;
for(;;)	
  {  
      Clear_Task_Dog();   //�������Ź�
      OS_TimeDly_Sec(1);//1s˯��
  }
}
#endif

/**********************************************************************************
�������ܣ����ܴ�������:��ʱ/����,��������
��ڣ�    
���ڣ�    
**********************************************************************************/
#ifdef TASK_ENERGE_HUCK_EN
void  AppEnergeTask_HUCK (void *p_arg)
{
       
    (void)p_arg;
    Energy_Demand_Task(1);
for(;;)	
  {  
      Energy_Demand_Task(0);
      Clear_Task_Dog();   //�������Ź�
      OS_TimeDly_Ms(100);//100ms˯��
  }
}
#endif

/**********************************************************************************
�������ܣ����ܴ�������:��ʱ/����,��������
��ڣ�    
���ڣ�    
**********************************************************************************/
#ifdef TASK_LCD_LUCK_EN
void  AppLCDTask_LUCK (void *p_arg)
{
       
    (void)p_arg;
    Init_Event_DIS_PUCK();  //��ʼ���¼�����Һ����ʾ
    Channel_Main_PUCK(1);
    //LCD_main_LUCK(1);   
for(;;)	
  {
      Channel_Main_PUCK(0);
      LCD_main_LUCK(0);
      Clear_Ext_Dog();    //����������CPU�ⲿ���Ź�
      Clear_Task_Dog();   //�������Ź�
      
#ifdef CHANNEL_FAST_EN
      OS_Waitfor_Ms(REC_FRAME_CONDITION,10);
      CLR_REC_FRAME;
#else
      OS_TimeDly_Ms(10);
#endif
  }
}
#endif

#ifdef TEST_MODE
void  AppTestTask_HUCK (void *p_arg)
{
       
    (void)p_arg;
    
    Test_Proc(1);

  for(;;)	
  {        
      Test_Proc(0);
      Clear_Task_Dog();
      //OS_TimeDly_Min(5);//UPDATETIMEms˯��
  }
}
#endif