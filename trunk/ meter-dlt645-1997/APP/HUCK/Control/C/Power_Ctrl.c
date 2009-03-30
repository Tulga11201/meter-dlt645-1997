#define POWER_CTRL_C
#include "Includes.h"

//��ȡ���ɿ��Ʋ�������ROM�ж�ȡ
void Read_Power_Ctrl_Para_From_Rom()
{
  INT8U Err;
  INT8U Temp[4];
  INT16U Len;

  Len=Read_Storage_Data(0xCA16,Temp,Temp,sizeof(Temp),&Err);//��������
  ASSERT(A_WARNING,3==Len && NO_ERR==Err);
  
  Power_Ctrl_Para.AcDemand_Up_Limit=Bcd2Hex(Temp,3);
  SET_STRUCT_SUM(Power_Ctrl_Para);
  
  Len=Read_Storage_Data(0xC214,Temp,Temp,sizeof(Temp),&Err);//�û����� 
  ASSERT(A_WARNING,1==Len && NO_ERR==Err); 
  
  Power_Ctrl_Para.User_Level=Temp[0];
  SET_STRUCT_SUM(Power_Ctrl_Para);
}

//�����Ϣ���������
//��Ϣ��������Ų���
//�����塢������Ƿ�ѱ�����Ƿ����բ���ж����Ķ������
//ʱ���л��������������������һ������
/*
INT8U Check_Output_Mode(INT8U Output_Flag)
{
  INT8U Mode;
  INT8U Re;
  
  Re=1;
  Re&=CHECK_STRUCT_SUM(Output_Mode);//����ź����������
  Re&=CHECK_STRUCT_SUM(Mode_Word);//���״̬��
  if(ASSERT(A_WARNING,1==Re))
    Check_Data_Avail();
  
  Mode=Output_Mode.Mode;
  switch(Output_Flag)
  {
  case EXT_ID_SEC_EN://�ж����Ķ��ӣ�������������
    return 1;
  case EXT_ID_PARSE://ʱ���л�����
    if(OUTPUT_TIME_CHANGE_FLAG==Mode)
      return 1;
    else 
      return 0;
  case EXT_ID_DEMAND://������������
    if(OUTPUT_DEMAND_FLAG==Mode)
    {
      if(0==Mode_Word.Mode[2].Bit.Bit4)
        return 1;
      else
        return 0;
    }
    else 
      return 0;
  case OUTPUT_DEMAND_SLIDE_PULSE://����ʱ������
    if(OUTPUT_DEMAND_FLAG==Mode)
    {
      if(1==Mode_Word.Mode[2].Bit.Bit4)
        return 1;
      else
        return 0;
    }
    else 
      return 0;    
  case OUTPUT_POWER_WARN://���ɿ��Ʊ�������,���ر����͵���Լ�����״̬����������һ������
    if(1==Mode_Word.Mode[1].Bit.Bit4)//ʹ�ø��ع���
    {
      return 1; 
    }
    else
      return 0;
  case OUTPUT_METER_GRID_WARN://����Լ�����״̬����
    if(0==Mode_Word.Mode[1].Bit.Bit4)//���ع��ܹر�
    {
      //if(1==Mode_Word.Mode[3].Bit.Bit0)//���������,��Ϊ�ж����ı������ӣ����Ըô�����
      {
        return 1; 
      }
      //else
        //return 0;
    }
    else
      return 0;
  //case OUTPUT_OWN_MONEY_WARN://�ж����Ķ��ӣ������������
    return 1;
  //case OUPPUT_OWN_MONEY_TRIP://�ж����Ķ��ӣ������������
    return 1;
  }
  return 0;
}
*/
/*
//����������ĺ��빳�Ӻ���
void Meter_Info_Output_Timer_Hook()
{
  static INT8U Counts;
  
  
  
}
//�����Ϣ���
void Meter_Info_Output(INT8U Flag)
{
  switch(Flag)
  {
    case OUTPUT_SEC_PULSE:
      break;
    case OUTPUT_TIME_CHANGE_PULSE://ʱ���л�
      break;   
  } 
}
*/

void Check_Power_Ctrl_Para_Avail()
{
  INT8U Re;
  
  Re=CHECK_STRUCT_SUM(Mode_Word);
  if(ASSERT(A_WARNING,0!=Re))
  {
    Read_Power_Ctrl_Para_From_Rom();
  }
}

//���ɿ��ƴ���
void Power_Ctrl_Proc()
{
  INT8U Re;
  Re=CHECK_STRUCT_SUM(Mode_Word);
  if(ASSERT(A_WARNING,0!=Re))
    Check_Data_Avail();
  
  if(1==Mode_Word.Mode[1].Bit.Bit4)//ģʽ��2��bit4��ʾ�Ƿ��и��ع���
  {
    //��ǰ�����й�������!
    if(Demand_Accu.Cur_Pos_Active>Power_Ctrl_Para.AcDemand_Up_Limit)
    {
      if(2==Power_Ctrl_Para.User_Level)//1���û�����������բ��2���û�ֻ��������բ��3���û��ȱ�������բ
      {
        Set_Event_Instant(ID_EVENT_DEMAND_ALARM);//����
        Port_Out_Pub(EXT_ID_POWER_ALARM,PORT_START);
      }
      else if(3==Power_Ctrl_Para.User_Level)//�û�����2����3����
      {
        Set_Event_Instant(ID_EVENT_DEMAND_ALARM);//����
        Set_Event_Instant(ID_EVENT_DEMAND_SWITCH);//��բ
        Port_Out_Pub(EXT_ID_POWER_ALARM,PORT_START);
        Port_Out_Pub(EXT_ID_TOGGLE,PORT_START);
      }
    }
    else//�������ָ�
    {
      if(2==Power_Ctrl_Para.User_Level)//1���û�����������բ��2���û�ֻ��������բ��3���û��ȱ�������բ
      {
        Clr_Event_Instant(ID_EVENT_DEMAND_ALARM);//����
        Port_Out_Pub(EXT_ID_POWER_ALARM,PORT_END);        
      }
      else if(3==Power_Ctrl_Para.User_Level)//�û�����2����3����
      {
        Clr_Event_Instant(ID_EVENT_DEMAND_ALARM);//����
        Clr_Event_Instant(ID_EVENT_DEMAND_SWITCH);//��բ
        Port_Out_Pub(EXT_ID_POWER_ALARM,PORT_END);        
        Port_Out_Pub(EXT_ID_TOGGLE,PORT_END);        
      }
    }
  }
}