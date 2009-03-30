#define ALARM_C
#include "Pub_PUCK.h"
#include "Alarm.h"
/***********************************************************************
�������ܣ�����λ�����ֽڵ�λ����ȡ��Ӧ��λ��Ϣ���ֽ���Ϣ
��ڣ���
���ڣ���
***********************************************************************/
void Sound_LED_LCD_Port_Alarm(void)
{
  INT8U  i,j,flag,num;
   
   for(i=0,flag=0;i<ALARM_EVENT_NUM;i++)
   {
     if(GET_BIT(*(Alarm_Event_Property[i].EventEn),Alarm_Event_Property[i].EventBit))   //�Ƿ������¼��������
     {
       if(Read_Event_Status(Alarm_Event_Property[i].EventID))  //ȷ�ϸ��¼�����
       {
         for(j=0,num=0;j<ALARM_MODE_NUM;j++)  //����������LED�����������ű���
         {
           if(GET_BIT(*(Alarm_Mode_Property[j].AlarmEn),Alarm_Mode_Property[j].AlarmBit))  //���ַ�ʽ����
           {
             Port_Out_Pub(Alarm_Mode_Property[j].PortID,Alarm_Mode_Property[j].AlarmWidth);
             Set_Event_Instant(ID_ALARM_OUT);
             num++;
             flag=1;
           }
           if(num>=ALARM_MODE_NUM)
             return ;
         }       
       }     
     }  
   }
   if(0==flag)
   Clr_Event_Instant(ID_ALARM_OUT);
}
