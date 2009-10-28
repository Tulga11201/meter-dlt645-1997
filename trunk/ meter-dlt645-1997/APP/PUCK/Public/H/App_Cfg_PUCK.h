
#ifndef APP_CFG_PUCK
#define APP_CFG_PUCK


#define TH_MODE     0   //˫����
#define TF_MODE     1   //������

#define PARSE_331    0
#define PARSE_341    1

#define PULSE_TYPE1  0
#define PULSE_TYPE2  1

#define VOLT_3100    0
#define VOLT_3220    1
#define VOLT_3577    2
#define VOLT_3380    3

#define CURR_1x5_6   0
#define CURR_1_2     1
#define CURR_5_10    2
#define CURR_10_40   3
#define CURR_0x3_1x2 4
#define CURR_5_6     5
#define CURR_15_60   6
#define CURR_20_80   7
#define CURR_5_20   8
#define CURR_30_100   9



#define SHOW_ENERG_BIT     3   //��ʾ�ĵ���С��λ
#define MEASURE_ERROR_STATICS_EN //�������򿪼�������ͳ�ƣ�ͬʱ������Ӧ�� Sram��Դ��Flash��Դ
#define OS_DEBG_EN       //OS���ܴ� ��

#define PRINT_PUCK_MEA_EN  1        //1:ʹ��PUCK�ļ���������Ϣ��0:��ֹ
#define PRINT_PUCK_LCD_EN  1        //1:ʹ��LUCK��LCD������Ϣ��0:��ֹ
#define PRINT_PUCK_CHANNEL_EN  1    //1:ʹ��ͨ��������Ϣ��0:��ֹ
#define PRINT_PUCK_EVENT_EN  1    //1:ʹ��ͨ��������Ϣ��0:��ֹ
#define PRINT_PUCK_MEM_EN  1    //1:ʹ��ͨ��������Ϣ��0:��ֹ

#define MEASURE_VAR_BAK_EN       //������ʹ�ܵ��ܱ����ı���
//#define MEASU_ANGLE_RD           //�������Ƕ���7022�������رգ����Լ����,����رոú꣬�Ƕ��Լ���
#define DRV_TEST_EN             //����:ʹ���������Թ���
//#define CONFLICT_TAB_CHKEN     //����������ñ��Ƿ��ͻ
#define C_MODE_EN               //��򿪣�ʹ��Cģʽ����


//�������ú�
#define CHANNEL_FAST_EN               //��򿪣�ͨ��ͨ��������Ӧ





#define GD_VERSION


#ifdef  GD_VERSION                      
  #define LOSS_VOLT_ONLY           //�ж����ݣ�ʧѹֻ�ж���ѹ��������޹�
  #define LOSS_CURR_ONLY           //�ж����ݣ�ʧ��ֻ�ж������������ƽ�����޹�
#else                              //ͨ�ð汾
  #define MULTI_LOSS_VOLT_EN       //�����ж�����򿪣�ʧѹ�����ж�����رգ������ж�
  #define MULTI_LOSS_CURR_EN       //�����ж�����򿪣�ʧ�������ж�����رգ������ж�
#endif

//�����������ú�
#define DEFAULT_PULSE_SPEC  PULSE_TYPE2
#define DEFAULT_VOLT_SPEC   VOLT_3220
#define DEFAULT_CURR_SPEC   CURR_1x5_6
#define DEFAULT_TFH_SPEC    TH_MODE
#if DEFAULT_VOLT_SPEC==VOLT_3220 || DEFAULT_VOLT_SPEC==VOLT_3577
  #define DEFAULT_PARSE_SPEC  PARSE_341
#else
  #define DEFAULT_PARSE_SPEC  PARSE_331
#endif
#define DEFAULT_AC_PULSE        5000
#define DEFAULT_REAC_PULSE      5000

//Ӳ���汾����
#define HARD_TYPE_20081005        1   //��һ��������
#define HARD_TYPE_20090224        2   //�ڶ�����������̩/����
#define HARD_TYPE_20090601_NC     3   //������������NC
#define HARD_TYPE_20090620_SD     4   //���İ�������ɽ����

#define METER_HARD_TYPE   HARD_TYPE_20090601_NC   //-------PUCK


//��ť����
#if METER_HARD_TYPE<=HARD_TYPE_20090224
  #define LEFT_KEY_EN               //��򿪣�ʹ����ť
  #define RIGHT_KEY_EN              //��򿪣�ʹ���Ұ�ť
  #define DIS_PARA_JUMP_EN          //��򿪣�ʹ�ܲ����޸�����
  #define NEAR_IRDA_EN             //��򿪣�ʹ����������
  #undef MAN_CLR_DEMAND_EN             //��򿪣��ֶ�������ʹ��
#else
  #if METER_HARD_TYPE == HARD_TYPE_20090601_NC
    #define  LEFT_KEY_EN               //��򿪣�ʹ����ť
    #define RIGHT_KEY_EN               //��򿪣�ʹ���Ұ�ť
    #define DIS_PARA_JUMP_EN          //��򿪣�ʹ�ܲ����޸�����
    #define NEAR_IRDA_EN             //��򿪣�ʹ����������
    #define MAN_CLR_DEMAND_EN             //��򿪣��ֶ�������ʹ��
  #endif
  #if METER_HARD_TYPE == HARD_TYPE_20090620_SD
    #undef  LEFT_KEY_EN               //��򿪣�ʹ����ť
    #undef RIGHT_KEY_EN               //��򿪣�ʹ���Ұ�ť
    #undef NEAR_IRDA_EN             //��򿪣�ʹ����������
    #define MAN_CLR_DEMAND_EN             //��򿪣��ֶ�������ʹ��
  #endif
#endif


//LCD����
#define LCD_NORMAL           0         //ͨ��Һ��
#define LCD_JS_ZXW           1         //����Һ��---������
#define LCD_JS_JX            2         //����Һ��---����
#define LCD_SD_ZXW           3         //ɽ��Һ��---������

#define LCD_PROPERTY  LCD_JS_ZXW



//�����������ú�
#define PARSE_METER_3   0               //ͨ������๦��
#define IC_METER        1               //IC��Ԥ���ѱ�
#define NETMETER_METER  2               //���������
#define METER_PROPERTY NETMETER_METER



//��������
#if METER_PROPERTY>=NETMETER_METER
  #define UART1_EN                         //����1ʹ��
#else
  #undef UART1_EN                          //����1��ֹ
#endif



#endif