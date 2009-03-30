#ifndef POWER_CTRL_H
#define POWER_CTRL_H

#undef EXT
#ifdef POWER_CTRL_C
#define EXT
#else
#define EXT extern
#endif
/*
//����PORT�豸ID
#define EXT_ID_ALARM        0  //�������
#define EXT_ID_TOGGLE       1  //��բ���
#define EXT_ID_ACPOWER      2  //�й�����
#define EXT_ID_REACPOWER    3  //�޹�����
#define EXT_ID_AP_DIR       4  //�й����巽��
#define EXT_ID_RP_DIR       5  //�޹����巽��
#define EXT_ID_SEC_EN       6  //������ʹ��
#define EXT_ID_DEMAND       7  //�����������
#define EXT_ID_PARSE        8  //ʱ���л����
#define GERNAL_ID_ACPOWER    9 //���й�����
#define GERNAL_ID_REACPOWER  10  //���޹�����
#define INTER_ID_ALARM_DIS   11  //����ָʾ��
#define INTER_ID_ALARM_BEEP  12  //��������
*/
#define OUTPUT_TIME_CHANGE_FLAG 0x01//���ʱ���л��źű�־
#define OUTPUT_DEMAND_FLAG 0x02//����������ڻ��߻����ź�

#define OUTPUT_SEC_PULSE 0//��������� 
#define OUTPUT_TIME_CHANGE_PULSE 1//ʱ���л�����
#define OUTPUT_DEMAND_PERIOD_PULSE 2//������������
#define OUTPUT_DEMAND_SLIDE_PULSE 3//������������
#define OUTPUT_POWER_WARN 4//���ɿ��Ʊ���
#define OUTPUT_METER_GRID_WARN 5//�����Լ����״̬����
#define OUTPUT_OWN_MONEY_WARN 6//Ƿ�ѱ���
#define OUPPUT_OWN_MONEY_TRIP 7//Ƿ����բ

//�����й���������
typedef struct
{
  INT32U AcDemand_Up_Limit;//�й���������
  INT8U User_Level;//�û�����
  INT8U CS[CS_BYTES];
}S_Power_Ctrl_Para;

//������������־
typedef struct
{
  INT32U Pulse_Flag;
  INT8U CS[CS_BYTES];  
}S_Output_Pulse;

EXT volatile S_Power_Ctrl_Para Power_Ctrl_Para;
EXT volatile S_Output_Pulse Output_Pulse;//���������־

EXT void Read_Power_Ctrl_Para_From_Rom();
EXT void Check_Power_Ctrl_Para_Avail();
EXT void Power_Ctrl_Proc();
#endif
