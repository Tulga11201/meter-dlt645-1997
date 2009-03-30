#ifndef EVENTINSTANT_VAR
#define EVENTINSTANT_VAR


#ifndef EVENTINSTANT_C
#define EVENTINSTANT_C_EXT  extern
#else
#define EVENTINSTANT_C_EXT 
#endif



#define      DI_LOSS_VOLT 0xCA10          //ʧѹ�ж���ֵ
#define      DI_LOSS_CURR 0xCA11          //ʧ���ж���ֵ

#define      ALL_LOSS_CURR_VALUE          0.02   //ȫʧ����ֵ��0.02*In

//ȫʧ����ֵ�����ʧ��������ֵС
typedef struct{
  FP32S  LossVolt_Per;        //ʧѹ��ѹ��ֵ,%-----CA10,ȡֵ���100:0.0~1.0��Ĭ�ϣ�0.78
  FP32S LossVolt_I;           //ʧѹ�����ж�ֵ:A��Ĭ�ϣ�0.1
  
  FP32S  LossCurr_Per;       //ʧ����ѹ��ֵ,%-----CA11,ȡֵ���100:0.0~1.0��Ĭ�ϣ�0.3
  FP32S LossCurr_I;          //ʧ�������ж�ֵ:A��Ĭ�ϣ�0.1
  INT8U CS[CS_BYTES];
}EventInsPara;         //�¼�����״̬



EVENTINSTANT_C_EXT EventInsPara EventInsParaVar;


#define KEY_INIT_STATUS  0x35
typedef struct{
  INT8U Prg;            //���
  INT8U CS[CS_BYTES];
}KeyStatus;         //�¼�����״̬

EVENTINSTANT_C_EXT KeyStatus  KeyInitStatus;


#define MAX_CHANGE_SEC    8     //��λ�ж�ʱ��
typedef struct
{ 
  INT8U Head;
  INT8U OldStatus;           //��״̬
  INT8U NewStatus;           //��״̬
  INT8U Counts;             //������
  INT8U Tail;
}EVENT_CHANGE;
EVENTINSTANT_C_EXT volatile EVENT_CHANGE Loss_Volt_Change;
EVENTINSTANT_C_EXT volatile EVENT_CHANGE Loss_Curr_Change;
EVENTINSTANT_C_EXT volatile EVENT_CHANGE Curr_Neg_Change;

INT8U Get_Event_Instant(INT8U Id);
void Check_Volt_Curr_Seq(void);
void  Check_Overload_Volt(void);
void  Check_Loss_Curr(void);
void  Check_Loss_Parse(void);
void Check_Loss_Volt(void);
void Check_RTCBat_Low(void);
void Check_LPWBat_Low(void);
void Check_Prg_Key(void);
void Check_Fac_Status(void);
void Check_Key_Switch(void);
void Init_Event_Instant_Para(void);
void Check_Neg_Curr(void);
void Check_UpCover(void);
void Check_DownCover(void);
void Check_AB_Func_Key(void);
void Check_MeterAddr_Key(void);
void Set_Cal_Event(void);
void Event_Para_Modi(void);
void Check_ClrDemand_Key(void);
void Get_Loss_Volt_Change(void);
void Get_Loss_Curr_Change(void);
void Get_Curr_Neg_Change(void);
void Monitor_Meter_System_Osc(void);
void Get_Meter_PowerOn(void);
#endif