
#ifndef PORT_ABS_H
#define PORT_ABS_H



#ifndef PORT_ABS_PUCK
#define PORT_ABS_PUCK_EXT  extern
#else
#define PORT_ABS_PUCK_EXT 
#endif


//���һ���������ã������塢ʱ�Ρ�����������
//1:�������º꣬��Const_Port_Status[]�е�MultiFlagΪ0����1���岻һ����
//2������ Const_Port_Status[]�е� MultiFlagΪ0����1
//3:����������������3��һ���ӹ��ã�������ʹ�����ã�MultiFlag��0(Ϊ1��Port_Out_Pub�����У����� END��)��SEC_MULTI_PORT��1��
#if METER_HARD_TYPE == HARD_TYPE_20090620_SD
  #define SEC_MULTI_PORT 1        //0�������岻�Ǹ��϶��ӣ�1���������Ǹ��϶���(���ã�
  #define MULTI_3_PORT   2        //0�����Ǹ��϶��ӣ�1���Ǹ��϶��ӣ����������岻���ã�2�Ǹ��϶��ӣ����������干�ã�
#else
  #define SEC_MULTI_PORT 0        //�����岻�Ǹ��϶���
  #define MULTI_3_PORT   1        //0�����Ǹ��϶��ӣ�1���Ǹ��϶��ӣ����������岻���ã�2�Ǹ��϶��ӣ����������干�ã�
#endif


//LED����ָʾ��
#define LED_ALARM_CLR        ALARM_0   
#define LED_ALARM_SET        ALARM_1

//���ȱ���
#define BEEP_ALARM_CLR       ALARM_BEEP_0   
#define BEEP_ALARM_SET       ALARM_BEEP_1

//�����ű���
#define EXT_ALARM_CLR        ALARM_PORT_0   
#define EXT_ALARM_SET        ALARM_PORT_1


//��������
#define EXT_DEMAND_CLR        B_dma_0   
#define EXT_DEMAND_SET        B_dma_1


//ʱ���л�
#define EXT_PARSE_CLR        B_time_priod_0   
#define EXT_PARSE_SET        B_time_priod_1

//��բ
#define EXT_SWITCH_CLR        RELAY_PORT_0   
#define EXT_SWITCH_SET        RELAY_PORT_1

//�����״̬��0��ʾ����
#define GUMB_STATUS          B_REED_TEST_STATUS

//�ⲿRTC���״̬��0��ʾǷѹ
#define RTC_BAT_LOW      B_BATLOWRTC_TEST_STATUS

//�͹��ĵ��״̬��0��ʾǷѹ
#define LOWCOST_BAT_LOW      B_BATLOW_TEST_STATUS

#define IRDA_SEND_EN              IRA_1             //���ⷢ��ʹ��
#define IRDA_SEND_DIS             IRA_0             //���ⷢ�ͽ�ֹ

#define IRDA_FAR_REC_EN            B_ird_chose_0     //Զ����տ���
#define IRDA_NEAR_REC_EN           B_ird_chose_1     //����������տ���

#define BAK_POWER_FOR_IRDA         B_ird_pow_1       //Զ�����Դ�ɵ͹��ĵ�ع���;
#define MAIN_POWER_FOR_IRDA        B_ird_pow_0       //Զ�����Դ������Դ����;


#define BAK_POWER_FOR_LCD          LCD_POW_1         //LCD��Դ�ɵ͹��ĵ�ع���;
#define MAIN_POWER_FOR_LCD         LCD_POW_0         //LCD��Դ������Դ����;


#define BAK_POWER_FOR_MEM        EEPOWER_1         //�ڿ���Դ�ɵ͹��ĵ�ع���;
#define MAIN_POWER_FOR_MEM       EEPOWER_0         //�ڿ���Դ������Դ����;


#define OPEN_MEASU_PWR           B_7022_POWER_1    //����оƬ��Դ����
#define CLOSE_MEASU_PWR          B_7022_POWER_0    //����оƬ��Դ�ر�

#define B_PRG_KEY_STATUS        OPEN_PROG_KEY    //��̿���
#define DOWN_COVER_STATUS       OPEN1_STATUS  //���˸�(��˸�)Ǧ��
#define UP_COVER_STATUS         OPEN2_STATUS  //�����(�϶˸�)


//���������޹��������ָʾ

//�й��������
#define A_DIR_1   B_4IN1_1_1
#define A_DIR_0   B_4IN1_1_0
//�޹��������
#define R_DIR_1   B_4IN1_2_1
#define R_DIR_0   B_4IN1_2_0

//�й����
#define A_OUT_1   B_4IN1_3_1
#define A_OUT_0   B_4IN1_3_0

//�޹����
#define R_OUT_1   B_4IN1_4_1
#define R_OUT_0   B_4IN1_4_0


//�й����� LED �����
#define MEASU_A_DIR_0        B_POWERDIR1_0   
#define MEASU_A_DIR_1        B_POWERDIR1_1

//�޹����� LED �������
#define MEASU_R_DIR_0        B_POWERDIR2_0   //�޹�����ָʾ
#define MEASU_R_DIR_1        B_POWERDIR2_1


/**********************************************************************************
�������ܣ�����ⲿ���Ź�
��ڣ�    
���ڣ�    
**********************************************************************************/

 


//ι���ź�
#define Clear_Ext_Dog()       {B_WTD_1;  B_WTD_0; B_WTD_0; B_WTD_1;}    //һ��B_WTD_0��Լ 240ns


#define BEEP_MODE_50        50
#define BEEP_MODE_100       100
#define BEEP_MODE_150       150
#define BEEP_MODE_200       200
#define BEEP_MODE_300       300
#define BEEP_MODE_400       400
#define BEEP_MODE_500       500

//����PORT�豸ID
#define EXT_ID_NONE         0  //��Ч����
#define EXT_ID_POWER_ALARM        (EXT_ID_NONE+1)          //������Ϣ�������糬���ʱ������-------------1
#define EXT_ID_FEE_ALARM          (EXT_ID_POWER_ALARM+1)    //Ƿ�ѱ������------------------------------2
#define EXT_ID_TOGGLE             (EXT_ID_FEE_ALARM+1)      //��բ���----------------------------------3
#define EXT_ID_ACPOWER            (EXT_ID_TOGGLE+1)        //�й�����-----------------------------------4
#define EXT_ID_REACPOWER          (EXT_ID_ACPOWER+1)       //�޹�����-----------------------------------5
#define EXT_ID_AP_DIR             (EXT_ID_REACPOWER+1)     //�й����巽��-------------------------------6
#define EXT_ID_RP_DIR             (EXT_ID_AP_DIR+1)        //�޹����巽��-------------------------------7
#define EXT_ID_SEC_EN             (EXT_ID_RP_DIR+1)        //������ʹ��---------------------------------8
#define EXT_ID_DEMAND             (EXT_ID_SEC_EN+1)        //�������ڵ����-----------------------------9
#define EXT_ID_SLIPE              (EXT_ID_DEMAND+1)        //�����������-------------------------------10
#define EXT_ID_PARSE              (EXT_ID_SLIPE+1)        //ʱ���л����--------------------------------11
#define GERNAL_ID_ACPOWER         (EXT_ID_PARSE+1)         //���й�����---------------------------------12
#define GERNAL_ID_REACPOWER       (GERNAL_ID_ACPOWER+1)    //���޹�����---------------------------------13
#define INTER_ID_ALARM_DIS        (GERNAL_ID_REACPOWER+1)  //����ָʾ��---------------------------------14
#define INTER_ID_ALARM_BEEP       (INTER_ID_ALARM_DIS+1)  //��������------------------------------------15
  

//����PORT�豸ID��Ŀ
#define MIN_PORT_DI      (EXT_ID_NONE+1)
#define MAX_PORT_DI      (INTER_ID_ALARM_BEEP)

#define MAX_PORT_NUM      (MAX_PORT_DI+1)

//���ģʽ
#define LEVEL_MODE        0x00   //��ƽ���ģʽ
#define PULSE_MODE        0x01   //�������ģʽ


#define PORT_END   0
#define PORT_START 1

typedef struct
{ 
  INT8U InitFlag;           //���ӳ�ʼ�����
  INT8U Status;             //״̬��0��ʾ�޶�����1��ʾ������2��ʾ���У�3��ʾ������
  INT16U CurCount;          //��ǰ1ms������0��ʾִ�ж������������65536ms��ĳһ�ֻ��е�������
  INT16U CurCountBak;       //ĳһ�ֻ��е������ȱ���
  INT16U LoopCount;         //�ֻ�����ÿһ���ֻس�һ������
  INT8U CS[CS_BYTES];
}PORT_HANDER;
PORT_ABS_PUCK_EXT volatile PORT_HANDER Ext_Port_Hander[MAX_PORT_NUM];


#define MODE_ERR     0     //δ֪ģʽ
#define MODE_RUN     1     //�ֳ�����ģʽ�������������Ϣ����Ȩ��
#define MODE_DEBUG   2     //����ģʽ�������������Ϣ����Ȩ��
#define MODE_FAC     4     //����ģʽ�������������Ϣ���߱����Ȩ��
#define MODE_TEST    8     //�Լ�ģʽ�������������Ϣ����Ȩ��


void Beep_For_Measu_Alarm_PUCK(void);
void Beep_For_OSC_Alarm_PUCK(void);
void Beep_For_Test_Alarm_PUCK(void);
void ExtPort_xMs_Hook(void);
void Init_All_Port(INT32U Mode);
void Port_Out_Pub(INT8U Id,INT16U Para);
INT8U Get_Meter_Hard_Mode(void);

INT8U Get_Sec_Out_En(void);
INT8U Get_Parse_Out_En(void);
INT8U Get_Demand_Out_En(void);
INT8U Get_Slipe_Out_En(void);
INT8U Get_FeeAlarm_Out_En(void);
INT8U Get_GridAlarm_Out_En(void);

#endif