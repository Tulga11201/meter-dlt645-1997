#ifndef INTER_ABS_H
#define INTER_ABS_H



#ifndef INTER_ABS_PUCK
#define INTER_ABS_PUCK_EXT  extern
#else
#define INTER_ABS_PUCK_EXT 
#endif

//���뼶���Ӻ�����
#define MS_HOOK_NUM     5

#define UP_KEY_VALUE    0x01
#define DOWN_KEY_VALUE  0x02
#define LEFT_KEY_VALUE  0x04
#define RIGHT_KEY_VALUE 0x08
#define AB_KEY_VALUE    0x10
#define A_KEY_VALUE     0x20
#define B_KEY_VALUE     0x40

#define MIN_KEY_VALUE   UP_KEY_VALUE
#define MAX_KEY_VALUE   B_KEY_VALUE

#define IRDA_WKUP_MS_TIME  160   //��λ������
#define IRDA_WKUP_NUM     5    //������� 

typedef struct
{ 
  INT8U Head;
  INT16U Ac_Pulse_Num;               //�й��������
  INT16U Rea_Pulse_Num;               //�޹�����
  INT8U Tail;
}PULSE_NUM_STRUC;



INTER_ABS_PUCK_EXT volatile PULSE_NUM_STRUC  Pulse_Num_Temp;
INTER_ABS_PUCK_EXT volatile INT32U Fast_Timer_Reg;

typedef struct
{
  INT8U  UpKey:1;        //�ж�������λ
  INT8U  DownKey:1;      //�ж�������λ
  INT8U  LeftKey:1;      //�ж�������λ���е�Cģʽ��ť,�����ť
  INT8U  RightKey:1;     //�ж�������λ���е�Cģʽ��ť,�Ҽ���ť
  INT8U  AB_Key:1;       //�¼�������λ��A/Bģʽ�л���ť
  INT8U  A_Key:1;        //�л���Aģʽ
  INT8U  B_Key:1;        //�л���Bģʽ
  INT8U  PrgKey:1;       //��̰�ť���ж���λ
}KeyBit;

typedef union
{
   KeyBit Bit;
  INT8U Byte;
}KeyUnion;

typedef struct
{
  INT8U Head;
  KeyUnion Key;
  INT8U Tail;
}KeyProperty;


INTER_ABS_PUCK_EXT volatile KeyProperty  Key_Value_Pub;

#define ALL_LOSS_NUM 10   //��¼ȫʧѹ������

#pragma pack(1)
typedef struct
{
  INT8U start:1;  //ȫʧѹ����
  INT8U Occur:1;  //ȫʧѹ�źţ�ȫʧѹ�ж���1��RTC�ڲ���0
  INT8U First:1;
  INT8U Exist:1; //��ʾ��ǰȫʧѹ�ж��Ƿ����
  INT8U Reserved:4;
  INT8U Index;  //���������¼����к�
  INT32U BatRunTime;      //�󱸵�ع���ʱ�䣺��λ��  
  INT32U Nums;    //ÿ�ε����ڼ�ȫʧѹ�������ܴ�����
  INT32U Mins;    //ÿ�ε����ڼ�ȫʧѹ��������ʱ�䣻
  INT8U cS;
}ALL_LOSS_STATUS;

typedef struct
{
  INT8U  StartTime[5];    //��ʼʱ�䣬ȫ0��ʾ����ʼ,��--->�ߣ��֡�ʱ���ա��¡���
  INT8U  EndTime[5];      //����ʱ�䣬ȫ0��ʾ�޽�����ͬ��
  INT8U cS;
}RECORD_TIME;

typedef struct
{
  ALL_LOSS_STATUS   Status;
  RECORD_TIME       RecordTime[ALL_LOSS_NUM];  //����ȫʧѹ�����ͽ�����¼
}ALL_LOSS_STRUC;
NO_INIT INTER_ABS_PUCK_EXT volatile ALL_LOSS_STRUC All_Loss_Var;


#define SET_VAR_CS_PUCK(Var) {Var.cS=GetBufSum_Pub((INT8U *)(&Var),sizeof(Var)-1);}
#define CHK_VAR_CS_PUCK(Var) ((Var.cS==GetBufSum_Pub((INT8U *)(&Var),sizeof(Var)-1))?1:0)
#define CLEAR_VAR_PUCK(Var)  {mem_set((void *)(&Var),0,sizeof(Var),(void *)(&Var),sizeof(Var));\
                              SET_VAR_CS_PUCK(Var);}

#define IRDA_WAKE_UP_MS    80   //�ж�����֡�ĳ�ʱʱ�䣺ms
#define IRDA_WAKE_UP_NUM   7   //�ж�����֡��������Ŀ������


typedef struct
{
  INT8U Head;
  INT8U Start:1;     //���յ�һ��bit0��־
  INT8U WakeUp:1;    //�Ƿ���������
  INT8U PulseNum:6;  //��ǰ���յ����������
  INT8U Tail;
}IRDA_WAKE_UP;
INTER_ABS_PUCK_EXT volatile IRDA_WAKE_UP Irda_Wake_Ctrl;
#pragma pack()

#define IRDA_READ_METER_EN Mode_Word.Mode[1].Bit.Bit1

void Inter_CF1(void);
void Inter_CF2(void);
//left key
void Inter_Left_Key(void);
//Down Key
void Inter_Down_Key(void);

//Right key
void Inter_Right_Key(void);//UP Key
void Inter_Up_Key(void);

//ALL_LOSE  7
void Inter_ALL_LOSS(void);


//POWER_DOWN  4
void POWER_DOWN(void);


void laser_up(void);

void Irda_Wake_Up(void);


//1HZ
void INT_1HZ(void);

void count_1ms(void);

void CPU_RTC_Interrupt(void);

void Inter_Prg_Key(void);
void Fast_Timer(void);
void IR_Decode_Proc(void);
void Init_Interr_Sram(void);
#endif