#ifndef EVENTPUB_VAR
#define EVENTPUB_VAR


#ifndef EVENTPUB_C
#define EVENTPUB_C_EXT  extern
#else
#define EVENTPUB_C_EXT 
#endif



//�������¼�����ID,�������壬��Э���޹�,ע�⣺��֤�����¼�һ���������ģ����޸�ʱ��ע�⣡
#define ID_EVENT_NO_VALID    0  	                      //��Ч�¼�--------0
#define ID_EVENT_A_LOSS_VOLT 1  	                      //A��ʧѹ--------1
#define ID_EVENT_B_LOSS_VOLT (ID_EVENT_A_LOSS_VOLT+1)  	      //B��ʧѹ--------2
#define ID_EVENT_C_LOSS_VOLT (ID_EVENT_B_LOSS_VOLT+1)	      //C��ʧѹ--------3

#define ID_EVENT_A_LOSS_CURR (ID_EVENT_C_LOSS_VOLT+1)         //A��ʧ��--------4
#define ID_EVENT_B_LOSS_CURR (ID_EVENT_A_LOSS_CURR+1)  	      //B��ʧ��--------5
#define ID_EVENT_C_LOSS_CURR (ID_EVENT_B_LOSS_CURR+1)	      //C��ʧ��--------6

#define ID_EVENT_CUR_NEG_SEQ  (ID_EVENT_C_LOSS_CURR+1)        //����������--------7
#define ID_EVENT_VOLT_NEG_SEQ (ID_EVENT_CUR_NEG_SEQ+1)        //��ѹ������--------8

#define ID_EVENT_A_VOLT_MAX    (ID_EVENT_VOLT_NEG_SEQ+1)      //A���ѹ������--------9
#define ID_EVENT_B_VOLT_MAX    (ID_EVENT_A_VOLT_MAX+1)        //B���ѹ������--------10
#define ID_EVENT_C_VOLT_MAX    (ID_EVENT_B_VOLT_MAX+1)	      //C���ѹ������--------11
#define ID_EVENT_A_VOLT_MIN    (ID_EVENT_C_VOLT_MAX+1)        //A���ѹ������--------12
#define ID_EVENT_B_VOLT_MIN    (ID_EVENT_A_VOLT_MIN+1)        //B���ѹ������--------13
#define ID_EVENT_C_VOLT_MIN    (ID_EVENT_B_VOLT_MIN+1)	      //C���ѹ������--------14

#define ID_EVENT_DEMAND_ALARM  (ID_EVENT_C_VOLT_MIN+1)         //����������--------15
#define ID_EVENT_DEMAND_SWITCH (ID_EVENT_DEMAND_ALARM+1)        //��������բ--------16
#define ID_EVENT_NC            (ID_EVENT_DEMAND_SWITCH+1)      //�տտ�--------17
#define ID_EVENT_RESET           (ID_EVENT_NC+1)          //��λ--------18
#define ID_EVENT_CLR_DEMAND_COM  (ID_EVENT_RESET+1)             //ͨ��������--------19
#define ID_EVENT_CLR_DEMAND_MAN  (ID_EVENT_CLR_DEMAND_COM+1)    //�ֶ�������--------20
#define ID_EVENT_CLR_PROCESS     (ID_EVENT_CLR_DEMAND_MAN+1)      //�����--------21
#define ID_EVENT_CLR_VOLT_PASS   (ID_EVENT_CLR_PROCESS+1)      //���ѹ�ϸ���--------22
#define ID_EVENT_SET_ENERG       (ID_EVENT_CLR_VOLT_PASS+1)    //���ó�ʼ����--------23
#define ID_EVENT_UP_COVER_OPEN   (ID_EVENT_SET_ENERG+1)        //�����--------24
#define ID_EVENT_LEAD_COVER_OPEN (ID_EVENT_UP_COVER_OPEN+1)    //��Ǧ����--------25
#define ID_EVENT_RTC_BAT_LOW     (ID_EVENT_LEAD_COVER_OPEN+1) //ʱ�ӵ��Ƿѹ--------26
#define ID_EVENT_LOWPWR_BAT_LOW  (ID_EVENT_RTC_BAT_LOW+1)     //�͹��ĵ��Ƿѹ--------27
#define ID_EVENT_ADJUST_TIME     (ID_EVENT_LOWPWR_BAT_LOW+1)   //Уʱ--------28
#define ID_EVENT_RTCERR_RUN      (ID_EVENT_ADJUST_TIME+1)      //����ʱ����--------29
#define ID_EVENT_RTCERR_PWRON    (ID_EVENT_RTCERR_RUN+1)      //�ϵ�ʱ����--------30
#define ID_EVENT_EPPROM_FAULT    (ID_EVENT_RTCERR_PWRON+1)    //EEPROM��--------31
#define ID_EVENT_ADJUST_MEASU    (ID_EVENT_EPPROM_FAULT+1)    //У��--------32
#define ID_EVENT_MODI_ENERG      (ID_EVENT_ADJUST_MEASU+1)    //��������--------33

#define ID_EVENT_A_VOLT_OVERLOAD (ID_EVENT_MODI_ENERG+1)      //A���ѹ��ѹ--------34
#define ID_EVENT_B_VOLT_OVERLOAD (ID_EVENT_A_VOLT_OVERLOAD+1)   //B���ѹ��ѹ--------35
#define ID_EVENT_C_VOLT_OVERLOAD (ID_EVENT_B_VOLT_OVERLOAD+1)   //C���ѹ��ѹ--------36
#define ID_EVENT_ENERG_FREEZ     (ID_EVENT_C_VOLT_OVERLOAD+1)   //��������--------37
#define ID_EVENT_POWER_ALARM     (ID_EVENT_ENERG_FREEZ+1)    //�����ʱ���--------38
#define ID_EVENT_POWER_SWITCH  (ID_EVENT_POWER_ALARM+1)       //��������բ--------39


#define ID_EVENT_A_LOSS_PARSE  (ID_EVENT_POWER_SWITCH+1)    //A�����--------40
#define ID_EVENT_B_LOSS_PARSE  (ID_EVENT_A_LOSS_PARSE+1)         //B�����--------41
#define ID_EVENT_C_LOSS_PARSE  (ID_EVENT_B_LOSS_PARSE+1)         //C�����--------42

#define ID_EVENT_A_NEG_CURR  (ID_EVENT_C_LOSS_PARSE+1)        //A���������--------43
#define ID_EVENT_B_NEG_CURR  (ID_EVENT_A_NEG_CURR+1)          //B���������--------44
#define ID_EVENT_C_NEG_CURR  (ID_EVENT_B_NEG_CURR+1)          //C���������--------45

#define ID_EVENT_KEY_SWITCH     (ID_EVENT_C_NEG_CURR+1)     //���߶̽�--------46
#define ID_EVENT_ERR_DI       (ID_EVENT_KEY_SWITCH+1)       //���ݱ�ʶ��--------47
#define ID_EVENT_ERR_PASSWD   (ID_EVENT_ERR_DI+1)         //�����--------48
#define ID_EVENT_YEAR_FLOW    (ID_EVENT_ERR_PASSWD+1)     //��ʱ������--------49
#define ID_EVENT_DATE_FLOW    (ID_EVENT_YEAR_FLOW+1)      //��ʱ������--------50
#define ID_EVENT_TRRI_FLOW    (ID_EVENT_DATE_FLOW+1)      //��������--------51
#define ID_EVENT_PRGKEY_ON    (ID_EVENT_TRRI_FLOW+1)      //��̼���--------52
#define ID_EVENT_FAC_ON       (ID_EVENT_PRGKEY_ON+1)       //����ģʽ--------53
#define ID_EVENT_METER_LOCK   (ID_EVENT_FAC_ON+1)       //�Ե����(������Ҫ����)ʱ����������������������ڵ���5�κ�--------54

#define ID_EVENT_AB_FUNC_KEY     (ID_EVENT_METER_LOCK+1)    //AB�л����ܼ�ʶ��--------55
#define ID_EVENT_POWER_OFF  (ID_EVENT_AB_FUNC_KEY+1)        //�����¼�--------56----PUCK 
#define ID_DEMAND_ARRIVE      (ID_EVENT_POWER_OFF+1)          //�������ڵ�--------57
#define ID_OVER_LOAD        (ID_DEMAND_ARRIVE+1)            //���ɿ��Ʊ���--------58
#define ID_NOT_CHARGE        (ID_OVER_LOAD+1)              //Ƿ�ѱ���--------59
#define ID_PARSE_SWITCH      (ID_NOT_CHARGE+1)             //ʱ���л�--------60
#define ID_MEASURE_ERROR     (ID_PARSE_SWITCH+1)           //��������--------61
#define ID_METER_ADDR_EN     (ID_MEASURE_ERROR+1)          //���ñ��ַ��ť-------62
#define ID_EVENT_ALL_LOSS_VOLT (ID_METER_ADDR_EN+1)        //���ñ��ַ��ť-------63

#define ID_EVENT_AB_LOSS_VOLT (ID_EVENT_ALL_LOSS_VOLT+1)   //ABʧѹ------------------64
#define ID_EVENT_AC_LOSS_VOLT (ID_EVENT_AB_LOSS_VOLT+1)    //ACʧѹ------------------65
#define ID_EVENT_BC_LOSS_VOLT (ID_EVENT_AC_LOSS_VOLT+1)   //BCʧѹ------------------66
#define ID_EVENT_ABC_LOSS_VOLT (ID_EVENT_BC_LOSS_VOLT+1)   //ABCʧѹ------------------67

#define ID_EVENT_PROG          (ID_EVENT_ABC_LOSS_VOLT+1)  //����¼������ò���-----------68
#define ID_EVENT_CLR_ALL_DATA  (ID_EVENT_PROG+1)           //��������-----------69
#define ID_EVENT_UP_COVER_CLOSE  (ID_EVENT_CLR_ALL_DATA+1)     //�ش��--------70(HUCK����) 
#define ID_EVENT_LEAD_COVER_CLOSE (ID_EVENT_UP_COVER_CLOSE+1)   //��Ǧ����------------71(HUCK����)  


#define ID_EVENT_AB_LOSS_CURR (ID_EVENT_LEAD_COVER_CLOSE+1)   //ABʧ��------------------72
#define ID_EVENT_AC_LOSS_CURR (ID_EVENT_AB_LOSS_CURR+1)    //ACʧ��------------------73
#define ID_EVENT_BC_LOSS_CURR (ID_EVENT_AC_LOSS_CURR+1)   //BCʧ��------------------74

#define ID_EVENT_ALL_LOSS_CURR (ID_EVENT_BC_LOSS_CURR+1)   //ȫʧ��-------------75

#define ID_EVENT_DOWN_COVER_OPEN   (ID_EVENT_ALL_LOSS_CURR+1)        //���˸�--------76
#define ID_EVENT_DOWN_COVER_CLOSE   (ID_EVENT_DOWN_COVER_OPEN+1)    //�ض˸�--------77

#define ID_EVENT_DOOR_OPEN          (ID_EVENT_DOWN_COVER_CLOSE+1)        //������װ����--------78
#define ID_EVENT_DOOR_CLOSE           (ID_EVENT_DOOR_OPEN+1)                  //�ؼ���װ����--------79
#define ID_SLIP_ARRIVE            (ID_EVENT_DOOR_CLOSE+1)          //���--------80
#define ID_ALARM_OUT              (ID_SLIP_ARRIVE+1)             //�Ƿ��б����¼������������������LCD_LED�����������ű���--------81
#define ID_CLR_DEMAND_KEY         (ID_ALARM_OUT+1)             //�ֶ���������ť--------81
#define ID_EVENT_EXT_PROG         (ID_CLR_DEMAND_KEY+1)             //����¼������ò���--------82(ͬ ID_EVENT_PROG,ӦHUCKGD��������)
/*
#define ID_EVENT_LOSS_VOL         (ID_EVENT_EXT_PROG+1)        //ʧѹ�仯��--------83(ӦHUCKGD�������ӣ�˲̬����HUCKά��)
#define ID_EVENT_LOSS_CUR         (ID_EVENT_LOSS_VOL+1)        //ʧ���仯��--------84(ӦHUCKGD�������ӣ�˲̬����HUCKά��)
#define ID_EVENT_NEG_CUR         (ID_EVENT_LOSS_CUR+1)        //���ʷ���仯��--------85(ӦHUCKGD�������ӣ�˲̬����HUCKά��)
*/
#define ID_EVENT_OSC_ERR         (ID_EVENT_EXT_PROG+1)        //��Ƭ��ʱ��ϵͳ����--------86


#define MIN_ID_EVENT          ID_EVENT_A_LOSS_VOLT
#define MAX_ID_EVENT          ID_EVENT_OSC_ERR

#define MAX_EVENT_NUM          (MAX_ID_EVENT+1)



typedef struct
{
  INT8U Instant_Event[MAX_EVENT_NUM/8+1];
  INT8U CS[CS_BYTES];
}EVENT_INSTANT_STATUS;
NO_INIT EVENTPUB_C_EXT  EVENT_INSTANT_STATUS Meter_Instant_Status;

typedef struct
{
  U_Byte_Bit  Meter_Stat1;        //C020/C040----B1
  U_Byte_Bit  Meter_Stat2;        //C026/C041----B2     
  U_Byte_Bit  Meter_Stat3;        //C027/C042----B3   
  U_Byte_Bit  Meter_Stat4;        //C028/C043----B4 
  U_Byte_Bit  Grid_Stat;          //C021/C044----B5
  U_Byte_Bit  Meter_Stat6;        //C045---------B6
  U_Byte_Bit  Volt_LossMiss;      //����ʧѹ/���࣬DI:DI_LOW_VOL
  U_Byte_Bit  NegCurr_Qudrant;    //�������������/��������ޣ�DI_CURRENT_QUADRANT
  U_Byte_Bit  Key_Event;          //�����̼���/���߶̽�/������λ/���������DI:DI_METER_PERIPHERY
  U_Byte_Bit  Comm_Status;        //����ͨ��״̬�֣�DI:DI_MODULE_STATUS
  
  //��չ�����ݵĹ��ʷ���״̬��
  U_Byte_Bit  Ext_Ac_Power_Dir;        //�й������־�ֽڣ�1�ֽڣ�0-3λΪ�ܡ�a��b��cԪ������4�ֽ�Ϊ0��
  U_Byte_Bit  Ext_Reac_Power_Dir;        //�޹������־�ֽڣ�1�ֽڣ�0-3λΪ�ܡ�a��b��cԪ������4�ֽ�Ϊ0��
  
  U_Byte_Bit  GD_Meter_Stat;        //�㶫�����״̬��
  U_Byte_Bit  GD_PwrDir_Stat;       //�㶫���й����ʷ���״̬��
  U_Byte_Bit  GD_LossVolt_Stat;        //�㶫��ʧѹ״̬��
  U_Byte_Bit  GD_LossCurr_Stat;        //�㶫��ʧ��״̬��
  U_Byte_Bit  GD_Hard_Stat;        //�㶫��Ӳ��״̬��
  //U_Byte_Bit  GD_Prog_Stat;        //�㶫�����״̬��(HUCK)
  
  INT8U CS[CS_BYTES];
}POWER_STATS;


EVENTPUB_C_EXT POWER_STATS Meter_Run_Status;


typedef struct
{
  U_Byte_Bit  Low_Byte;        //C129��8λ
  U_Byte_Bit  High_Byte;        //C129��8λ
  INT8U CS[CS_BYTES];
}SELF_TSET;
EVENTPUB_C_EXT SELF_TSET Meter_Self_Test;


typedef struct{
  INT8U  Occur:1;         //�¼�������־�����������
  
  INT8U  Status:1;        //�¼�������״̬λ���ⲿ���ʣ����ʺ󣬸�λ����������Ƿ�Ӧ���¼��ķ�����0-------���¼�������1-------�¼�������  
  INT8U  Status1:1;       //�¼�������־���ݣ��ⲿ����1�����ʺ󣬸�λ���
  INT8U  Status2:1;       //�¼�������־���ݣ��ⲿ����2�����ʺ󣬸�λ���
  INT8U  Status3:1;       //�¼�������־���ݣ��ⲿ����3�����ʺ󣬸�λ���
  INT8U  Status4:1;       //�¼�������־���ݣ��ⲿ����4�����ʺ󣬸�λ���  
  INT8U  Reserved:2;      //Ԥ��
  INT8U  Mins;           //�ּ�����
  INT8U  StartCount;      //�¼�����������
  INT8U  EndCount;        //�¼�����������  
  INT8U  CS[CS_BYTES];
}EventProcStatus;         //�¼�����״̬


EVENTPUB_C_EXT EventProcStatus EventProcStatusVar[MAX_EVENT_NUM]; 



#define POWER_OFF        0x37   //����
#define POWER_ON         0xF6   //�ϵ�
#define ABNORMAL_RESET   0xE8   //�쳣��λ



typedef struct{
  INT8U  Power;
  INT8U  CS[CS_BYTES];
}POWER_STATUS;         //�ϵ紦��״̬

NO_INIT EVENTPUB_C_EXT POWER_STATUS Power_Status;

void Get_Meter_Status(void);
void Event_Main_PUCK(INT8U Flag);


INT8U Read_Event_Ststus(INT8U PersonID,INT8U EventId);
void Set_Event_Instant(INT8U Id);
void Clr_Event_Instant(INT8U Id);

INT8U Check_Prog_Status(void);
void Save_Event_Data(void);
INT8U Check_AB_Switch(void);
INT8U Check_C_Switch(void);
INT8U Check_MeterAddr_Status(void);
INT8U Read_Event_Status(INT8U Id);
void Init_Event_Sram(INT8U);

//void Emerg_Event_Proc(void);
void Event_Proc_Sec(void);
INT8U Check_Event_End(INT8U Id);
void Save_All_Loss_Data(void);
void Init_All_Loss_Sram(void);
void Count_All_Loss_Proc(void);
INT8U RTC_Read_Fxt(volatile INT8U Time[]);
void Clr_All_Loss_Data(void);
void Init_Event_DIS_PUCK(void);
void PwrOff_Proc_PUCK(void);
void Check_Loss_All_Curr(void);
void Sound_LED_LCD_Port_Alarm(void);
INT8U Check_Man_ClrDemd_En(void);
void Get_Meter_Run_Status(void);
void Set_Event_Occur_Status(INT8U i);
void Set_Event_End_Status(INT8U i);
void Clr_Event_Real_Status(INT8U i);
void Clr_All_Event_Sram(void);
void Init_All_Event_Sram(void);
#endif
