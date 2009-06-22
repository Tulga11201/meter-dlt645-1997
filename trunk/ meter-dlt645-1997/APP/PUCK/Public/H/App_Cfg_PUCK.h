
#ifndef APP_CFG_PUCK
#define APP_CFG_PUCK




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





#if METER_PLACE == METER_GD   //HUCK ver
  #define GD_VERSION
#endif

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
#define HARD_TYPE_20081005     1   //��һ��������
#define HARD_TYPE_20090224     2   //�ڶ������������հ棬�м�����߰���汾�ϳ�������

#define METER_HARD_TYPE   HARD_TYPE_20090224   //-------PUCK


//����������ú�
#define PARSE_METER_3   0               //ͨ������๦��
#define IC_METER        1               //IC��Ԥ���ѱ�
#define NETMETER_METER  2               //��������
#define MWRWE_HARD_TYPE NETMETER_METER

//LCD����
#define LCD_NORMAL           0         //ͨ��Һ��
#define LCD_JS_ZXW           1          //����Һ��---������
#define LCD_JS_JX            2           //����Һ��---����

#define LCD_PROPERTY  LCD_JS_ZXW


//��������
#if MWRWE_HARD_TYPE>=NETMETER_METER
  #define UART1_EN                         //����1ʹ��
#else
  #undef UART1_EN                          //����1��ֹ
#endif



#endif
