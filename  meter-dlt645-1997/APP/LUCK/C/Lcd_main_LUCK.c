
#define LCD_MAIN_C
#include "Pub_Puck.h"


/********************************************************************************
PUCK:
�������ܣ�����ȡ�����޸�DI������������־
��ڣ�
���أ�
********************************************************************************/
void Set_Para_Modi_DI(INT16U Di)
{  
  INT8U i;
  for(i=0;i<MAX_MODI_NUM;i++)
  {
    if(CHECK_STRUCT_SUM(Para_Dis_Var)==0)
       ASSERT(A_WARNING,0);     
    if(Para_Dis_Var.Para_Modi[i]==0)
    {
      Para_Dis_Var.Para_Modi[i]=Di;
      Para_Dis_Var.Flag=1;
      SET_STRUCT_SUM(Para_Dis_Var);
      return ;
    }     
  }
 
}
/********************************************************************************
PUCK:
�������ܣ���ȡ�����޸�DI
��ڣ�
���أ�
********************************************************************************/
INT16U Get_Para_Modi_DI(void)
{
  INT8U i;
  INT16U  temp=0;
  
  if(Para_Dis_Var.Flag==0)
    return 0;
    
  for(i=0;i<MAX_MODI_NUM;i++)
  {
    if(Para_Dis_Var.Para_Modi[i]!=0)
    {
      if(CHECK_STRUCT_SUM(Para_Dis_Var)==0)
        ASSERT(A_WARNING,0);
      temp=Para_Dis_Var.Para_Modi[i];
      Para_Dis_Var.Para_Modi[i]=0;
      SET_STRUCT_SUM(Para_Dis_Var);      
      break;
    }  
  }  
  return temp;
}
/********************************************************************************
PUCK:
�������ܣ���ȡ�����޸�DI
��ڣ�
���أ�
********************************************************************************/
INT8U Get_Para_Modi_Flag(void)
{
  if(Para_Dis_Var.Flag)
  {
    if(CHECK_STRUCT_SUM(Para_Dis_Var)==0)
      ASSERT(A_WARNING,0);
    Para_Dis_Var.Flag=0;
    SET_STRUCT_SUM(Para_Dis_Var);
    return 1;
  }
    return 0; 
}

/********************************************************************************
PUCK:
�������ܣ�
��ڣ�
���أ�
********************************************************************************/

void Clr_LCDSleep_Timer(void)
{
  Sleep_Sec_Timer.Var=Sec_Timer_Pub;
}
/********************************************************************************
PUCK:
�������ܣ�
��ڣ�
���أ�
********************************************************************************/

void LCD_Task_Monitor(void)
{
  if(Get_Sys_Status()==SYS_SLEEP)//������˯�ߵ�����£������κ����� 
  {
    Task_Sleep();
  }
   
  if(Get_Sys_Status()==SYS_RESUME)
  {
    if(Sec_Timer_Pub-Sleep_Sec_Timer.Var>=LCD_SLEEP_SEC)
    {
      DEBUG_PRINT(PUCK,PRINT_PUCK_LCD_EN,"Lcd Task Enter To Sleep!"); 
      Task_Sleep();
      Clr_LCDSleep_Timer();
    }
  }
  
}

/********************************************************************************
PUCK:
�������ܣ�
��ڣ�
���أ�
********************************************************************************/
void LCD_Init_PUCK(void)  //LCD��ʾ��ʼ���������ٶ���Ҫ
{
  Init_Event_DIS_PUCK();  //��ʼ���¼�����Һ����ʾ
   //һ�����룬˵�������ѻ�������ģʽ,�����ϵ���߰�ť���⻽��,Һ���ĳ�ʼ���Ѿ���Init_ExtDevice_PUCK()���
  if((Get_Sys_Status()==SYS_NORMAL) || (Check_Resume_Source(IRAD_RESUME|KEY_RESUME)))
  {
    Initial();
    Clr_LCDSleep_Timer();
  }
}
/********************************************************************************
PUCK:
�������ܣ�
��ڣ�
���أ�
********************************************************************************/

void LCD_main_LUCK (INT8U Flag)  //10ms����һ��
{
  if(Flag)   //һ�����룬˵�������ѻ�������ģʽ
  {
    if(Get_Sys_Status()==SYS_NORMAL)  //�����ϵ�
      MainHTLCD_Puck_Pub(1);
    else if(Check_Resume_Source(IRAD_RESUME|KEY_RESUME))  //���ѣ��Ǻ�����߰�ť����
      MainHTLCD_Puck_Pub(0);
    else
      Task_Sleep();
    Initial();
    Clr_LCDSleep_Timer();
    return ;
  }
  
  LCD_Task_Monitor();   //����ģʽ���
  Dis_Jump_Para();      //������ʾ
  Key_Fast_LCD_Proc();  //��ť�ȿ��ٴ���
  Loop_Dis_LCD_Proc();  //ѭ�Դ���
  Init_LCD_Loop();
}
