#ifndef ENERGY_H
#define ENERGY_H

#undef EXT
#ifdef ENERGY_C
#define EXT
#else
#define EXT extern
#endif

#define POWER_ON_RST 0x5A
#define SOFT_RST 0xA5

//����Cmp_Time��������ֵ
#define TIME_EQU 0
#define TIME_AFT 1
#define TIME_BEF 2

//�������ʷ���,Check_Rate_Scheme()�����ķ���
#define RATE_SCHEME0 1
#define RATE_SCHEME1  2

#define CALC_RAM 0//������ʻ��߷��ʷ���ʱ����RAM�еĲ���
#define CALC_ROM 1//������ʻ��߷��ʷ���ʱ����ROM�еĲ���

//�ձ�־���壬�����������ա������պ�һ����
#define HOLIDAY 0
#define WEEK_REST_DAY 1
#define NORMAL_DAY 2

//�ۼ����ı���ֵ,��Լ�е����ݶ���λ2λС����Cur_Energy�е����ݶ���3λС��
#define ENERGY_RATIO ((INT32U)100)//����
#define COPPERLOSS_RATIO ((INT32U)3600*100000)//ͭ��
#define IRONLOSS_RATIO   ((INT32U)3600*1000000)//����
#define TRANSERR_RATIO   ((INT32U)3600)//�������ϳ����
#define AH_RATIO         ((INT32U)3600*100)//��ʱ:1000----0.1AH;100-----0.01AH

#define MAX_ACTIVE_INC 50
#define MAX_REACTIVE_INC 50

//�ϵ��־
typedef struct
{
  INT8U Flag[10];
  INT8U CS[CS_BYTES];
}S_Power_On_Flag;

//������Ϣ״̬��
typedef struct
{
  INT8U ErrFlag;
  INT8U CS[CS_BYTES];
}S_Err_Info;

//�����ṹ��
typedef struct 
{
  INT8U Head;
  //INT8U Time[5];//����ʱ���,��ʱ���ڶ���ʱ����Ϊ����ʱ��
  S_HEX_Time Time;//����ʱ���,��ʱ���ڶ���ʱ����Ϊ����ʱ��
  
  INT8U Temp;//���ã���������ṹ�����
  
  INT32U  Pos_Active[MAX_RATES+1];//���Լ��ַ��������й�,��λС��,��λKWh����ͬ
  INT32U  Neg_Active[MAX_RATES+1];//���Լ��ַ��ʷ����й�
  
  INT32U  Quad_Reactive[4][MAX_RATES+1];//�����޷ַ����޹�
  
  INT32U  Phase_Pos_Active[3];//���������й�
  INT32U  Phase_Neg_Active[3];//���෴���й�
 
  INT32U Phase_Quad_Reactive[3][4];//A��B��C���ܵ��������޹�,��Phase_Quad_Reactive[1][2]��ʾB��3�����޹�
  
  INT32U  Phase_AH[4];//������AH

  INT32U  CopperLoss[4];//��ABCͭ��
  INT32U  IronLoss[4];  //��ABC����
  INT32U  TransErr[4];  //��ABC���������
  
  //INT32U  Phase_Reactive[3][4];//������������޹�
  INT32U Data_Ready_Flag;
  
  INT8U   CS[CS_BYTES];//����Ĳ���Ҫ���浽Flash��
  
  INT8U Tail;
  //���²����Ǹ�������������ã�����Ҫ���浽Flash��EERom��
  //INT32U Pos_Reactive[MAX_RATES+1];//���Լ��ַ��������޹�
  //INT32U Neg_Reactive[MAX_RATES+1];

}S_Energy;




/*
//�����������ʱ��
//0-4�ֽڷֱ��Ƿ֡�ʱ���ա��¡���
typedef struct
{
  INT8U Time[5];
  
  INT8U   Pos_Active[MAX_RATES+1][5];//�����й������������ʱ��
  INT8U   Neg_Active[MAX_RATES+1][5];//�����й������������ʱ��
  
  INT8U   Quad_Reactive[4][MAX_RATES+1][5];//�������޹������������ʱ��
  
  INT32U  Pos_Reactive[MAX_RATES+1][5];//�����޹�(����޹�1)�����������ʱ��
  INT32U  Neg_Reactive[MAX_RATES+1][5];//�����޹�(����޹�2)�����������ʱ��
  
  INT8U   CS[CS_BYTES];//У���
}S_Demand_Time;
*/

DATA_PACKED_BEGIN
//������״̬��
typedef struct
{
  INT8U Status;
  INT8U CS[CS_BYTES];
}S_WeekRest_Status;
//��������ز���
typedef struct
{
  INT8U Year_Period; //��ʱ����
  INT8U Date_Table;  //��ʱ�α���
  INT8U Date_Period; //��ʱ����
  INT8U Rates;    //������
  INT8U Holidays; //�ڼ�����
  INT8U WeekRest_DataTable;//������ʹ�õ�ʱ�α��
  INT8U WeekRest_Status;  //������״̬��
  
  INT8U CS[CS_BYTES];
}S_Multi_Rate_Para;//�����ʲ���
//��ʱ����
typedef struct
{       /*"��ʱ���ṹ��"*/
  INT8U MDN[MAX_YEAR_PERIODS][3];
  INT8U CS[CS_BYTES];
}S_Year_Table;
//��ʱ�α�
typedef struct
{       /*"��ʱ�α�ṹ��"*/
  INT8U HMN[MAX_DATE_PERIODS][3];
  
  //INT8U Rate_Scheme;//��ǰ�׷��ʷ���
  //INT8U Index;//��ǰʱ�α�������
  INT8U CS[CS_BYTES];
}S_Date_Table;

typedef struct
{
  INT8U Index;
  INT8U CS[CS_BYTES]; 
}S_Cur_Date_Table;
//-------------300 byte-----------------------
//�ڼ��սṹ��
typedef struct
{       /*"�ڼ��սṹ��"*/
  //INT8U WeekRest_DataTable;//�ڼ��ղ��õ���ʱ�α�� 
  INT8U MDN[MAX_YEAR_HOLIDAYS][3];
  INT8U CS[CS_BYTES];
}S_Holiday_Table;

//����������ز���
typedef struct
{
  INT8U Mode;//��������ģʽ��
  
  INT8U Start_Time[4];//��¼����ʼʱ��
  INT8U Rec_Period[6][2];//6�����ݵļ�¼����
  INT8U CS[CS_BYTES];
  
}S_Load_Data_Para;
//�޹�ģʽ��
typedef struct
{
  INT8U Mode[2];
  INT8U CS[CS_BYTES];
  
}S_Reactive_Com_Mode;

//��ǰģʽ��
typedef struct
{
  U_Byte_Bit Mode[9];
  INT8U CS[CS_BYTES];  
}S_Mode_Word;

//��ǰ����״̬��
typedef struct
{
  U_Byte_Bit Status[2];
  INT8U CS[CS_BYTES];
}S_Rate_Status;

//�Զ������ղ���,DDHH[0]��ʾСʱ,DDHH[1]��ʾ��
typedef struct
{
  INT8U DDHH[2];
  INT8U CS[CS_BYTES];
}S_Data_Freeze_Time;

typedef struct
{
  INT8U Mode;//�ź����������
  INT8U CS[CS_BYTES];  
}S_Output_Mode;

//��ǰ���������Ϣ����Ҫ���ڴ�ӡ���
typedef struct
{
  INT8U Scheme;//��ǰʹ�õ��׷��ʷ���
  INT8U Date_Flag;//HOLIDAY,WeekRest,NORMAL_DAY
  
  INT8U Holiday_Index; //�ڶ��ٸ�����
  INT8U Year_Period;  //��ʱ����
  
  INT8U Date_Table;//��ʱ�α��
  INT8U Date_Period; //��ʱ�κ�
  INT8U Rate; //��ǰ����
  
  INT8U CS[CS_BYTES];
}S_Cur_Rate_Info;


DATA_PACKED_END

typedef struct
{
  INT8U Flag;
  INT8U CS[CS_BYTES];
}S_Flag;

typedef struct
{
  INT8U Head;
 
  INT8U Err_Flag;//�����־
  INT8U Tail;
}S_Sys_Run_Flag;

typedef struct
{
  INT32U Chk_Flag;
  INT8U CS[CS_BYTES];
}S_Chk_Data_Flag;

#define PUB_BUF_LEN ((sizeof(S_Energy)+50))//MAX_SIZE(sizeof(S_Energy),sizeof(S_Demand),sizeof(S_Demand_Time))
/*
typedef struct
{
  INT8U Head;
  INT8U Buf[PUB_BUF_LEN];
  INT8U Tail;
}S_Pub_Buf;
*/
DECLARE_BUF_TYPE (INT8U,PUB_BUF_LEN,S_Pub_Buf);
//EXT volatile INT16U Pub_Buf[PUB_BUF_LEN];//��ROM�ж�ȡ����ʱʹ�ø�buf
EXT S_Pub_Buf _Pub_Buf;
#define Pub_Buf _Pub_Buf.Buf

EXT volatile INT8U Rst_Flag;

EXT volatile S_Err_Info Err_Info;    //������Ϣ״̬��

EXT volatile S_Chk_Data_Flag Chk_Data_Flag;
EXT NO_INIT volatile S_Power_On_Flag Power_On_Flag;   //�ϵ��λ��־

EXT volatile S_Mode_Word Mode_Word;           //��ǰ�޹�ģʽ��
EXT volatile S_Rate_Status Rate_Status;       //��ǰ����״̬��
EXT volatile S_HEX_Time Rate_Scheme_Switch_Time;   //���������л�ʱ��

EXT NO_INIT volatile S_Multi_Rate_Para Multi_Rate_Para;//��ǰ���ʷ�������
EXT volatile S_Year_Table Year_Table;          //��ǰ��ʱ����
EXT volatile S_Date_Table Date_Table;          //��ǰ��ʱ�α�

EXT volatile S_Data_Freeze_Time Data_Freeze_Time;//�Զ������ղ���

EXT volatile S_Cur_Date_Table Cur_Date_Table;//��ǰ��ʱ�α�������

EXT NO_INIT volatile S_Energy Cur_Energy;     //��ǰ�������ݽṹ��

#if USE_ENERGY_RAM_BAK
EXT NO_INIT volatile S_Energy Cur_Energy_Bak;     //��ǰ�������ݽṹ��
#endif


EXT volatile S_Output_Mode Output_Mode;
EXT volatile S_Cur_Rate_Info Cur_Rate_Info;//��ǰ���������Ϣ,��Ҫ�ǹ�������
EXT volatile S_Sys_Run_Flag Sys_Run_Flag;
EXT volatile S_Int32U Energy_Cumu_Counts;

EXT INT8U Check_Rst_Flag();
EXT void Main_Chk_Data_Avail();
EXT void Check_Pub_Var_Avail();
EXT void Check_Cur_Energy_Data();
EXT INT8U Get_Using_Rate();
EXT void Read_Mode_Word();

EXT void Read_Energy_Para_From_Rom();
EXT void Read_Energy_Data_From_Rom();

EXT void Calc_Pos_Neg_Reactive(S_Energy *pEnergy);
EXT void Get_Cur_Date_Table(INT8U Rate_Scheme,INT8U Date_Table_Index);

EXT void Rate_Scheme_Changed_Proc();
EXT void Rate_Changed_Proc();

EXT INT8U Check_Energy_Data(S_Energy *pEnergy);
EXT void Check_Energy_Data_Avail();
EXT void Check_Data_Avail();
EXT void Check_Energy_Demand_Task_Data_Avail();
EXT void Freeze_Energy_Data(S_HEX_Time *pTime);

EXT void Save_Cur_Energy_Data();
EXT void Save_Cur_Energy_Bak0_Data();
EXT void Save_Cur_Energy_PD_Data();
EXT void Clear_Energy_Data();
EXT void Set_Def_Energy_Data();

EXT void Read_Energy_Data_Para_For_Show();
EXT void Energy_Task_Ram_Init();
EXT void Read_Para_From_Rom();
EXT void Refresh_Para_From_Rom();
EXT void Energy_Demand_Task_Init();
EXT void Energy_Demand_Task(INT8U Flag);
EXT void Last_Power_Down_Proc();
#endif
