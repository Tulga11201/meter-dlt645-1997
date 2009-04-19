#define DEF_PARA_C
#include "Includes.h"

#if METER_PLACE == 0
CONST INT8U Def_PSW_0[3]={0x00,0x00,0x00};
CONST INT8U Def_PSW_1[3]={0x00,0x00,0x00};
CONST INT8U Def_PSW_2[3]={0x00,0x00,0x00};


CONST INT8U Zero[100]={0};
//Ĭ��У�����
CONST INT8U Def_ADJ_METER_PUL_VOL_CUR_SPEC[]={0x00,0x01,0x01};
CONST INT8U Def_ADJ_METER_PARA_STATUS[]={0x00};
/*
CONST INT8U Def_ADJ_METER_A_POW[36]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
                                     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
                                     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
CONST INT8U Def_MeterAddr0[]={0x00,0x00,0x00,0x00,0x00,0x00};
CONST INT8U Def_MeterAddr1[]={0x00,0x00,0x00,0x00,0x00,0x00};
*/
CONST INT8U Def_ADJ_METER_A_POW[]= 
{
BYTE_0(0x000C491E),BYTE_1(0x000C491E),BYTE_2(0x000C491E),
BYTE_0(0x000D08FA),BYTE_1(0x000D08FA),BYTE_2(0x000D08FA),
BYTE_0(0x000C3D32),BYTE_1(0x000C3D32),BYTE_2(0x000C3D32),
          
BYTE_0(0x00000000),BYTE_1(0x00000000),BYTE_2(0x00000000),
BYTE_0(0x00000000),BYTE_1(0x00000000),BYTE_2(0x00000000),
BYTE_0(0x00000000),BYTE_1(0x00000000),BYTE_2(0x00000000),
          
BYTE_0(0x000020CD),BYTE_1(0x000020CD),BYTE_2(0x000020CD),
BYTE_0(0x0001665E),BYTE_1(0x0001665E),BYTE_2(0x0001665E),
BYTE_0(0x00011A6E),BYTE_1(0x00011A6E),BYTE_2(0x00011A6E),
          
BYTE_0(0x00450100),BYTE_1(0x00450100),BYTE_2(0x00450100),
BYTE_0(0x00442897),BYTE_1(0x00442897),BYTE_2(0x00442897),
BYTE_0(0x00439E74),BYTE_1(0x00439E74),BYTE_2(0x00439E74),
  
};
#define Def_MeterAddr0      Zero
#define Def_MeterAddr1      Zero
#define Def_LoadData_Index  Zero
//CONST S_LoadData_Index Def_LoadData_Index=
//{0x00,0x00,0x00,{0x00,0x00,0x01,0x01,0x00,0x00,{0x00}},{0x00}};

//CONST S_Demand Def_Demand={0};
//CONST S_VolStat Def_VolStat={0};
#define Def_VolStat Zero

CONST INT8U Def_C047[]={0x00};//ģʽ��1
CONST INT8U Def_C048[]={0x02};//ģʽ��2
CONST INT8U Def_C049[]={0x00};//ģʽ��3
CONST INT8U Def_C04A[]={0x02};//ģʽ��4
CONST INT8U Def_C04B[]={0x06};//ģʽ��5
CONST INT8U Def_C04C[]={0x03};//ģʽ��6
CONST INT8U Def_C04D[]={0x0C};//ģʽ��7
CONST INT8U Def_C04E[]={0x3F};//ģʽ��8
CONST INT8U Def_CA1A[]={0x03};//ģʽ��9-4��1ģʽ��

/*
//�����ʲ���--test
CONST INT8U Def_C31F[]=
{
  (MAX_YEAR_PERIODS%10)+((MAX_YEAR_PERIODS/10)<<4),//��ʱ����(Byte%10)+((Byte/10)<<4)
  (MAX_DATE_TABLES%10)+((MAX_DATE_TABLES/10)<<4),//��ʱ�α���
  (MAX_DATE_PERIODS%10)+((MAX_DATE_PERIODS/10)<<4),//��ʱ����
  (MAX_RATES%10)+((MAX_RATES/10)<<4),//������
  0x00,//����������
  0x01,//�����ղ��õ�ʱ�α��
  0x3E//������״̬��
};
*/

//�����ʲ���
CONST INT8U Def_C31F[]=
{
  0x01,//��ʱ����
  0x02,//��ʱ�α���
  0x08,//��ʱ����
  0x04,//������
  0x00,//����������
  0x01,//�����ղ��õ�ʱ�α��
  0x7F//������״̬��
};

//��ʱ����,����
//ʱ�α��,�գ���
CONST INT8U Def_C32F[]=
{
  1,1,1,
  1,1,2,
  1,1,3,
  1,1,4,
  1,1,5,
  1,1,6,  
  1,1,7,
  1,1,8,
  1,1,9,
  1,1,0x10,
  1,1,0x11,
  1,1,0x12    
};

//��ʱ�α�,����
//���ʣ��֣�ʱ
CONST INT8U Def_C33F[]=
{
  0x03,0x00,0x06,
  0x01,0x00,0x08,
  0x02,0x00,0x11,
  0x03,0x00,0x13,
  0x02,0x00,0x15,
  0x01,0x00,0x18,
  0x02,0x00,0x21,
  0x04,0x00,0x22,
  0x03,0x00,0x06,//�Ӵ˿�ʼͬDef_C331
  0x01,0x00,0x08,
  0x02,0x00,0x11,
  0x03,0x00,0x13,
  0x02,0x00,0x15,
  0x01,0x00,0x18
};

//Ĭ�ϵ���·�豸��ַ
/*
CONST INT8U Def_Device_Addr[]=
{
  0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00  
};
*/
#define Def_Device_Addr Zero

//Ĭ��ͨ�Ų�����
CONST INT8U Def_Comm_Baud[]=
{
  0x01,
  0x01,
  0x01
};

#define Def_Energy_Freeze_Time Zero
#define Def_Reactive_Freeze_Time Zero

//�й����峣��
CONST INT8U Def_C030[]=
{
  0x00,0x50,0x00
};

//�޹����峣��
CONST INT8U Def_C031[]=
{
  0x00,0x50,0x00
};

//��š��û��š��豸��
/*
CONST INT8U Def_C032_4[]=
{
  0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00
};
*/
#define Def_C032_4 Zero
//
CONST INT8U Def_C111_6[]=
{
  0x15,//��������
  0x01,//����ʱ��
  0x06,//ѭ��ʱ��
  0x13,//A��ѭ����Ŀ��
  0x03,//��ʾ����С��λ��
  0x03//��ʾ����С��λ��
};

//�Զ���������
CONST INT8U Def_C117[]=
{
  0x00,0x01 
};

//���ɴ�����
CONST INT8U Def_C118[]=
{
 0x01 
};

/*
//�й���ʼ����
CONST INT8U Def_C119[]=
{
 0x00,0x00,0x00,0x00 
};

//�޹���ʼ����
CONST INT8U Def_C11A[]=
{
 0x00,0x00,0x00,0x00
};
*/
#define Def_C119 Zero
#define Def_C11A Zero

//�Զ���������
CONST INT8U Def_C127[]=
{
  0x00,
  0x01
};

//B����ʾ��Ŀ��
CONST INT8U Def_C128[]=
{
  0x20,0x00 
};

//���������80ms
CONST INT8U Def_C211[]=
{
  0x80,0x00
};

//��ѹ���˲���
CONST INT8U Def_C213[]=
{
  0x00,0x40,0x02,//�ϸ����� 240V
  0x00,0x00,0x02,//�ϸ����� 200V
  0x00,0x62,0x02,//��ѹ�������� 262V
  0x00,0x78,0x01//��ѹ�������� 178V
};

//�û�����
CONST INT8U Def_C214[]=
{
  0x00 
};

//��բ����բ��ʱ
CONST INT8U Def_C215_6[]=
{
 0x00,
 0x00 
};

//�ڼ���
/*
CONST INT8U Def_C41F[45]=
{
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0
};
*/
#define Def_C41F Zero

//�������߼�¼��ʼʱ�� 1��1��0ʱ0��
CONST INT8U Def_C510[]=
{
  0x00,0x00,0x01,0x01
};

//�������߼�¼���,1Сʱ
CONST INT8U Def_C511_6[]=
{
  0x60,0x00,
  0x60,0x00,
  0x60,0x00,
  0x60,0x00,
  0x60,0x00,
  0x60,0x00,
};

//A����1-10����ʾ��Ŀ
CONST INT8U Def_C610_9[]=
{
0x01,0x00,0x00,0x00,   0x00,0x00,0x00,0x00,   0x02,
0x02,0x00,0x00,0x00,   0x00,0x01,0x00,0x00,   0x02,
0x03,0x00,0x00,0x00,   0x00,0x02,0x00,0x00,   0x02,
0x04,0x00,0x00,0x00,   0x00,0x03,0x00,0x00,   0x02,
0x05,0x00,0x00,0x00,   0x20,0x00,0x00,0x00,   0x02,
0x06,0x00,0x00,0x00,   0x40,0x00,0x00,0x00,   0x02,
0x07,0x00,0x00,0x00,   0x50,0x00,0x00,0x00,   0x02,
0x08,0x00,0x00,0x00,   0x60,0x00,0x00,0x00,   0x02,
0x09,0x00,0x00,0x00,   0x70,0x00,0x00,0x00,   0x02,
0x10,0x00,0x00,0x00,   0x00,0x00,0x01,0x00,   0x02,
};

//A����11-20����ʾ��Ŀ
CONST INT8U Def_C620_9[]=
{
0x11,0x00,0x00,0x00,   0x00,0x00,0x02,0x00,   0x02,
0x12,0x00,0x00,0x00,   0x00,0x00,0x08,0x00,   0x02,
0x13,0x00,0x00,0x00,   0x01,0x00,0x08,0x00,   0x02,

0x01,0x00,0x00,0x00,   0x00,0x00,0x00,0x00,   0x02,
0x02,0x00,0x00,0x00,   0x00,0x01,0x00,0x00,   0x02,
0x03,0x00,0x00,0x00,   0x00,0x02,0x00,0x00,   0x02,
0x04,0x00,0x00,0x00,   0x00,0x03,0x00,0x00,   0x02,
0x05,0x00,0x00,0x00,   0x20,0x00,0x00,0x00,   0x02,
0x06,0x00,0x00,0x00,   0x40,0x00,0x00,0x00,   0x02,
0x07,0x00,0x00,0x00,   0x50,0x00,0x00,0x00,   0x02,
};


//B��1-10����ʾ��Ŀ
CONST INT8U Def_C650_9[]=
{
0x20,0x00,0x00,0x00,   0x00,0x00,0x03,0x00,   0x02,
0x21,0x00,0x00,0x00,   0x00,0x01,0x03,0x00,   0x02,
0x22,0x00,0x00,0x00,   0x00,0x02,0x03,0x00,   0x02,
0x23,0x00,0x00,0x00,   0x00,0x03,0x03,0x00,   0x02,
0x24,0x00,0x00,0x00,   0x10,0x00,0x03,0x00,   0x02,
0x25,0x00,0x00,0x00,   0x10,0x01,0x03,0x00,   0x02,
0x26,0x00,0x00,0x00,   0x10,0x02,0x03,0x00,   0x02,
0x27,0x00,0x00,0x00,   0x10,0x03,0x03,0x00,   0x02,
0x28,0x00,0x00,0x00,   0x00,0x01,0x04,0x00,   0x02,
0x29,0x00,0x00,0x00,   0x00,0x02,0x04,0x00,   0x02
};

//B��11-20����ʾ��Ŀ
CONST INT8U Def_C660_9[]=
{
0x30,0x00,0x00,0x00,   0x00,0x03,0x04,0x00,   0x02,
0x31,0x00,0x00,0x00,   0x00,0x01,0x05,0x00,   0x02,
0x32,0x00,0x00,0x00,   0x00,0x02,0x05,0x00,   0x02,
0x33,0x00,0x00,0x00,   0x00,0x03,0x05,0x00,   0x02,  

0x20,0x00,0x00,0x00,   0x00,0x00,0x03,0x00,   0x02,
0x21,0x00,0x00,0x00,   0x00,0x01,0x03,0x00,   0x02,
0x22,0x00,0x00,0x00,   0x00,0x02,0x03,0x00,   0x02,
0x23,0x00,0x00,0x00,   0x00,0x03,0x03,0x00,   0x02,
0x24,0x00,0x00,0x00,   0x10,0x00,0x03,0x00,   0x02,
0x25,0x00,0x00,0x00,   0x10,0x01,0x03,0x00,   0x02 
};

//ͨ�Ź�Լ�汾��,45�ֽ�
CONST INT8U Def_C712[]=
{
 0 
};
//ʧѹ�жϷ�ֵ 78V 10%
CONST INT8U Def_CA10[]=
{
  //0x00,0x10,0x00,0x78
  0x78,0x00,0x10,0x00
};

//ʧ���жϷ�ֵ
CONST INT8U Def_CA11[]=
{
  //0x00,0x10,0x00,0x30
  0x30,0x00,0x10,0x00
};

//�ź����������
/*
CONST INT8U Def_CA12[]=
{0};
*/
#define Def_CA12 Zero

//���������л�ʱ��
CONST INT8U Def_CA13[]=
{
  0xFF,0xFF,0xFF,0xFF,0xFF 
};

//�û�Ȩ�޿�����
CONST INT8U Def_CA15[]=
{ 
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF 
};

//�й������޶�4.7520KW
CONST INT8U Def_CA16[]=
{
  0x20,0x75,0x04
};

//���ڹ����޶�4.7520KW
CONST INT8U Def_CA17[]=
{
  0x20,0x75,0x04
};

//�����ж���ֵ
CONST INT8U Def_CA19[]=
{
  0x00,0x00,0x00
};

//ע�⣬�±��г��ֵ����������϶���Data_Para_Storage�г���
CONST S_Def_Para_Info Def_Para[]=
{
  {PASSWORD_0,1,Def_PSW_0},
  {PASSWORD_1,1,Def_PSW_1},
  {PASSWORD_2,1,Def_PSW_2},
  
  {METER_ADDR0,1,Def_MeterAddr0},
  {METER_ADDR1,1,Def_MeterAddr1},

//Ĭ�ϵ������ݣ�CUR_ENERGY_BAK0�Ƕ�ȡ���������һ����ȡ����ѡ��Ϊ�����ṩĬ����,һ�¼����ͬ
  //{LOAD_DATA_INDEX,1,(INT8U CONST *)&Def_LoadData_Index},
  {LOAD_DATA_INDEX_BAK,1,(INT8U CONST *)&Def_LoadData_Index},
  
  {CUR_VOLSTAT,1,(INT8U CONST *)&Def_VolStat},
  {TOTAL_VOLSTAT,1,(INT8U CONST *)&Def_VolStat},
  //��1-13����ʷ����������������ʱ�䣬Ĭ��Ϊ0
  //{HIS_ENERGY,HIS_ENERGY_DATA_MONTHS,(INT8U CONST *)&Def_Energy},
  //{HIS_DEMAND,HIS_DEMAND_DATA_MONTHS,(INT8U CONST *)&Def_Demand},
  //{HIS_DEMAND_TIME,HIS_DEMAND_DATA_MONTHS,(INT8U CONST *)&Def_Demand_Time},
  //{HIS_VOLSTAT,HIS_VOLSTAT_DATA_MONTHS,(INT8U CONST *)&Def_VolStat},
  {PROG_RECORD,1,Zero},//���ʱ��ʹ���
  {CLR_DEMAND_RECORD,1,Zero},//������ʱ��ʹ���
  
  {COMM_BAUD0,3,Def_Comm_Baud},//ͨ�Ų�����
  {ENERGY_FREEZE_TIME,1,Def_Energy_Freeze_Time},//�ܵ�������ʱ��
  {REACTIVE_FREEZE_TIME,1,Def_Reactive_Freeze_Time},//�������޹�����ʱ��
  
/*
  { OCCUR_TOTAL_LOSS_VOL,1,Zero},
  { OCCUR_A_LOSS_VOL,1,Zero},             
  { OCCUR_B_LOSS_VOL,1,Zero},
  { OCCUR_C_LOSS_VOL,1,Zero},
  { OCCUR_AB_LOSS_VOL,1,Zero},
  { OCCUR_AC_LOSS_VOL,1,Zero},
  { OCCUR_BC_LOSS_VOL,1,Zero},
  { OCCUR_ABC_LOSS_VOL,1,Zero},
  //ȫʧѹ
  { OCCUR_ALL_LOSS_VOL,1,Zero},
  
  { TOTAL_TOTAL_LOSS_VOL,1,Zero},
  { TOTAL_A_LOSS_VOL,1,Zero},
  { TOTAL_B_LOSS_VOL,1,Zero},
  { TOTAL_C_LOSS_VOL,1,Zero},
  { TOTAL_AB_LOSS_VOL,1,Zero},
  { TOTAL_AC_LOSS_VOL,1,Zero},
  { TOTAL_BC_LOSS_VOL,1,Zero},
  { TOTAL_ABC_LOSS_VOL,1,Zero},
  //ȫʧѹ
  { TOTAL_ALL_LOSS_VOL,1,Zero},
  
  //ʧ��
  { OCCUR_TOTAL_LOSS_CUR,1,Zero},
  { OCCUR_A_LOSS_CUR,1,Zero},
  { OCCUR_B_LOSS_CUR,1,Zero},
  { OCCUR_C_LOSS_CUR,1,Zero},
  { OCCUR_AB_LOSS_CUR ,1,Zero},
  { OCCUR_AC_LOSS_CUR,1,Zero},
  { OCCUR_BC_LOSS_CUR,1,Zero},
  //ȫʧ��
  { OCCUR_ABC_LOSS_CUR,1,Zero},
  
  { TOTAL_TOTAL_LOSS_CUR,1,Zero},
  { TOTAL_A_LOSS_CUR,1,Zero},
  { TOTAL_B_LOSS_CUR,1,Zero},
  { TOTAL_C_LOSS_CUR,1,Zero},
  { TOTAL_AB_LOSS_CUR,1,Zero},
  { TOTAL_AC_LOSS_CUR,1,Zero},
  { TOTAL_BC_LOSS_CUR,1,Zero},
  { TOTAL_ABC_LOSS_CUR,1,Zero},
  
  //����
  { OCCUR_TOTAL_NEG_CUR,1,Zero},
  { OCCUR_A_NEG_CUR,1,Zero},
  { OCCUR_B_NEG_CUR,1,Zero},
  { OCCUR_C_NEG_CUR,1,Zero},
  
  { TOTAL_TOTAL_NEG_CUR,1,Zero},
  { TOTAL_A_NEG_CUR ,1,Zero},
  { TOTAL_B_NEG_CUR,1,Zero},
  { TOTAL_C_NEG_CUR,1,Zero},
  
  //����
  { OCCUR_TOTAL_BREAK_VOL,1,Zero},
  { OCCUR_A_BREAK_VOL,1,Zero},
  { OCCUR_B_BREAK_VOL,1,Zero},
  { OCCUR_C_BREAK_VOL,1,Zero},
  
  { TOTAL_TOTAL_BREAK_VOL,1,Zero},
  { TOTAL_A_BREAK_VOL,1,Zero},
  { TOTAL_B_BREAK_VOL,1,Zero},
  { TOTAL_C_BREAK_VOL,1,Zero},
  */
//--------------------------------------
  {0xB214,1,Zero},//��ع���ʱ��
  //{0xB710,7,Zero},
  //{0xB720,6,Zero},
  //{0xB730,4,Zero},
  //{0xB740,3,Zero},
  
  {0xC047,1,Def_C047},//ģʽ��1
  {0xC048,1,Def_C048},//ģʽ��2
  {0xC049,1,Def_C049},//ģʽ��3
  {0xC04A,1,Def_C04A},//ģʽ��4
  {0XC04B,1,Def_C04B},//ģʽ��5
  {0xC04C,1,Def_C04C},//ģʽ��6
  {0xC04D,1,Def_C04D},//ģʽ��7
  {0xC04E,1,Def_C04E},//ģʽ��8  
  {0xCA1A,1,Def_CA1A},//ģʽ��9
  
  {0xC111,6,Def_C111_6},//�������ڵȲ���
  {0xC117,1,Def_C117},//�Զ�������
  {0xC118,1,Def_C118},//���ɴ�����
  {0xC119,1,Def_C119},//�й���ʼ����
  {0xC11A,1,Def_C11A},//�޹���ʼ����
  
  {0xC128,1,Def_C128},//B����ʾ��Ŀ��
  {0xC211,1,Def_C211},//���������80ms
  {0xC213,1,Def_C213},//��ѹ���˲���
  
  {0xC214,1,Def_C214},//�û�����
  {0xC215,2,Def_C215_6},//��բ���բ��ʱ
  
  {0xC030,1,Def_C030},//�й����峣��
  {0xC031,1,Def_C031},//�޹����峣��
  {0xC032,3,Def_C032_4},//��ţ��û��ţ��豸��
  
  {0xC310,7,Def_C31F},//��һ����ʱ������
  {0xC32F,1,Def_C32F},//��һ����ʱ����
  
  {0xC33F,1,Def_C33F},//��һ����ʱ�α�
  {0xC34F,1,Def_C33F},
  {0xC35F,1,Def_C33F},
  {0xC36F,1,Def_C33F},
  {0xC37F,1,Def_C33F},
  {0xC38F,1,Def_C33F},
  {0xC39F,1,Def_C33F},
  {0xC3AF,1,Def_C33F},
  {0xC3BF,1,Def_C33F},
  {0xC3CF,1,Def_C33F},
  {0xC3DF,1,Def_C33F},
  {0xC3EF,1,Def_C33F},
  
  {0xC41F,1,Def_C41F},//��һ�׽ڼ��� 
  {0xC42F,1,Def_C41F},
  {0xC43F,1,Def_C41F},
  {0xC44F,1,Def_C41F},
  {0xC45F,1,Def_C41F},
  {0xC46F,1,Def_C41F},

  {0xCB10,7,Def_C31F},//�ڶ�����ʱ������
  {0xCB2F,1,Def_C32F},//�ڶ�����ʱ����
  
  {0xCB3F,1,Def_C33F},//�ڶ�����ʱ�α�
  {0xCB4F,1,Def_C33F},
  {0xCB5F,1,Def_C33F},
  {0xCB6F,1,Def_C33F},
  {0xCB7F,1,Def_C33F},
  {0xCB8F,1,Def_C33F},
  {0xCB9F,1,Def_C33F},
  {0xCBAF,1,Def_C33F},
  {0xCBBF,1,Def_C33F},
  {0xCBCF,1,Def_C33F},
  {0xCBDF,1,Def_C33F},
  {0xCBEF,1,Def_C33F},
  
  {0xC510,1,Def_C510},
  {0xC511,6,Def_C511_6},
  
  {0xC610,10,Def_C610_9},//A����1-10��
  {0xC620,10,Def_C620_9},//A����11-20��
  {0xC630,10,Def_C610_9},//A����21-30��
  {0xC640,10,Def_C610_9},//A����31-40��
  
  {0xC650,10,Def_C650_9},//B����01-10��
  {0xC660,10,Def_C660_9},//B����11-20��
  {0xC670,10,Def_C650_9},//B����21-30��
  {0xC680,10,Def_C650_9},//B����31-40��
  {0xC690,10,Def_C650_9},//B����41-50��
  {0xC6A0,10,Def_C650_9},//B����51-60��
  {0xC6B0,10,Def_C650_9},//B����61-70��
  {0xC6C0,10,Def_C650_9},//B����71-80��
  {0xC6D0,10,Def_C650_9},//B����81-90��
  {0xC6E0,10,Def_C650_9},//B����91-100�� 
  
  {0xC91F,1,Zero},
  {0xC92F,1,Zero},
  {0xC93F,1,Zero},
  {0xC94F,1,Zero},
  {0xC95F,1,Zero},
  {0xC96F,1,Zero},
  
  {0xCA10,1,Def_CA10},//ʧѹ�жϷ�ֵ 78V 10%
  {0xCA11,1,Def_CA11},//ʧ���жϷ�ֵ
  {0xCA12,1,Def_CA12},//�ź����������
  {0xCA13,1,Def_CA13},//���������л�ʱ��
  {0xCA15,1,Def_CA15},//�û�Ȩ�޿�����
  {0xCA16,1,Def_CA16},//�й������޶�4.7520KW
  {0xCA17,1,Def_CA17},//���ڹ����޶�4.7520KW
  {0xCA19,1,Def_CA19},//������ֵ
  
  {0xCC1F,1,Def_C41F}, //�ڶ��׽ڼ���
  {0xCC2F,1,Def_C41F},
  {0xCC3F,1,Def_C41F},
  {0xCC4F,1,Def_C41F},
  {0xCC5F,1,Def_C41F},
  {0xCC6F,1,Def_C41F},
  
  {ADJ_METER_PUL_VOL_CUR_SPEC,1,Def_ADJ_METER_PUL_VOL_CUR_SPEC},//���塢��ѹ���������
  {ADJ_METER_PARA_STATUS,1,Def_ADJ_METER_PARA_STATUS},//У�����״̬����
  {ADJ_METER_A_POW,12,Def_ADJ_METER_A_POW},//���ʡ���λ����ѹ���������ò���һ����12��Ŀ
  
  DEF_PARA_EXTEND
};

#endif
//дһ��Ĭ�ϲ�����������ʶΪDI
void Write_One_Def_Para(PROTO_DI DI)
{
  INT16U i;
  INT16U Len;
 
  if(Check_Meter_Factory_Status()==0)//��ǰ���ǹ���״̬���Ƴ�
  {
    DEBUG_PRINT(HUCK,DEBUG_0,"Write Def Para failed! not in factory status!");
    return;
  }
  
  for(i=0;i<S_NUM(Def_Para);i++)
  {
    if(DI>=Def_Para[i].DI && DI<Def_Para[i].DI+Def_Para[i].Num)
    {
      if(Check_Meter_Factory_Status()==0)//��ǰ���ǹ���״̬���Ƴ�
        return;
      Len=Get_Storage_Data_Len(Def_Para[i].DI);
      Write_Storage_Data(DI,(void *)(Def_Para[i].pPara+(DI-Def_Para[i].DI)*Len),Len);
      return;
    }
  }  
}
//����Ĭ�ϵ�У�����,��Ϊȫ0
void Set_Def_Adj_Para()
{
  PROTO_DI DI;
  INT8U Temp[4];
  
  Main_Dis_Info("CLr PArA");
  mem_set(Temp,0,sizeof(Temp),Temp,sizeof(Temp));
  Write_Storage_Data(0xCEE1,Temp,1);
  for(DI=0xCEE2;DI<=0xCEED;DI++)
  {
    Write_Storage_Data(DI,Temp,3);
    //Write_One_Def_Para(DI);
  }
}

//��������DI��Ĭ�ϲ���
INT16U Read_Def_Para(STORA_DI DI,void *pDst,INT16U Len,void *pDst_Start,INT16U DstLen)
{
  INT16U i;
  for(i=0;i<S_NUM(Def_Para);i++)
  {
    if(DI==Def_Para[i].DI ||\
      (DI>Def_Para[i].DI && DI<Def_Para[i].DI+Def_Para[i].Num))
    {
      mem_cpy(pDst,(INT8U *)Def_Para[i].pPara+(DI-Def_Para[i].DI)*Len,Len,pDst_Start,DstLen);
      return Len;
    }
  }
  return 0;
}

//������������ΪĬ������
void Set_All_Def_Data()
{
  if(Check_Meter_Factory_Status()==0)//��ǰ���ǹ���״̬���Ƴ�
    return; 
  
  Init_Clock(SYS_NORMAL);//������ʷ����ʱ��Ҫʱ��
  Data_Freeze_Time.DDHH[0]=0;
  Data_Freeze_Time.DDHH[1]=1;
  SET_STRUCT_SUM(Data_Freeze_Time);//����ʱ��
  
  Set_Def_Energy_Data();//����Ĭ�ϵĵ�������
  if(Check_Meter_Factory_Status()==0)//��ǰ���ǹ���״̬���Ƴ�
    return;
  Set_Def_Demand_Data();//����Ĭ�ϵ���������
  if(Check_Meter_Factory_Status()==0)//��ǰ���ǹ���״̬���Ƴ�
    return;
  Set_Def_VolStat_Data();//����Ĭ�ϵĵ�ѹͳ������
  if(Check_Meter_Factory_Status()==0)//��ǰ���ǹ���״̬���Ƴ�
    return;
  Set_Def_Load_Data_Index();
  if(Check_Meter_Factory_Status()==0)//��ǰ���ǹ���״̬���Ƴ�
    return;  
  Set_Def_Freeze_Data();//����Ĭ�ϵĶ�������
  if(Check_Meter_Factory_Status()==0)//��ǰ���ǹ���״̬���Ƴ�
    return;
  Set_Def_Event_Data();//����Ĭ�ϵ��¼�����   
  
}

//���ó�У�������������в���
void Set_Def_Para_Except_Adj()
{
  INT16U i,j,Len;
  
  Main_Dis_Info("CLr PArA");
  for(i=0;i<S_NUM(Def_Para);i++)
  {
    if(Check_Meter_Factory_Status()==0)//��ǰ���ǹ���״̬���Ƴ�
      return;
    
    Len=Get_Storage_Data_Len(Def_Para[i].DI);
    
    for(j=0;j<Def_Para[i].Num;j++)
    {
      if(Check_Meter_Factory_Status()==0)
        return;   
      if(!(Def_Para[i].DI+j>=0xCEE0 && Def_Para[i].DI+j<=0xCEEF))
        Write_Storage_Data(Def_Para[i].DI+j,(void *)(Def_Para[i].pPara+j*Len),Len);
    }
  }  
}

//дĬ�ϲ������洢����,�ú��������ڹ���״̬�²���ִ��
void Write_Def_Para()
{
  INT16U i,j;
  INT16U Len;
 
  DISP_CLR_DATA_INFO;
  for(i=0;i<S_NUM(Def_Para);i++)
  {
    if(Check_Meter_Factory_Status()==0)//��ǰ���ǹ���״̬���Ƴ�
      return;
    
    Len=Get_Storage_Data_Len(Def_Para[i].DI);
    
    for(j=0;j<Def_Para[i].Num;j++)
    {
      if(Check_Meter_Factory_Status()==0)
        return;   
      //if(!(Def_Para[i].DI+j>=0xCEE0 && Def_Para[i].DI+j<=0xCEED))//test
      Write_Storage_Data(Def_Para[i].DI+j,(void *)(Def_Para[i].pPara+j*Len),Len);
    }
  }
  
  Set_All_Def_Data(); 
  
  DEBUG_PRINT(HUCK,DEBUG_0,"--------------Set Def Para End!------------");
}

//���ĳ���������Ƿ���Ĭ�ϲ���,���򷵻�1�����򷵻�0
INT8U Check_Def_Para(STORA_DI DI)
{
  INT16U i;
 
  for(i=0;i<S_NUM(Def_Para);i++)
  {
    if(DI>=Def_Para[i].DI && DI<Def_Para[i].DI+Def_Para[i].Num)
    {
      return 1;
    }
  }  
  return 0;
}


//����Ƿ���Ҫ����Ĭ�ϲ���
void Check_Boot_On_Flag()
{
  INT32U Boot_Flag;
  INT8U Err;
 
/*
  Boot_Flag=0;
  Write_Storage_Data(BOOT_FLAG,&Boot_Flag,sizeof(Boot_Flag));
  
  Main_Dis_Info("CLr PArA");  
  while(1)
  {
    Clr_Ext_Inter_Dog();
  }
*/       
  if(Check_Meter_Factory_Status()==1)//ֻ���ڹ���״̬��������Ĭ�ϲ���
  {
    if(Check_Sys_Status()==SYS_NORMAL)//ϵͳ��Դ����������²Ž������ݶ������������
    {
      Check_Sys_Storage();//�洢ϵͳ�Լ�  
      
      Boot_Flag=0;
      if(Read_Storage_Data(BOOT_FLAG,&Boot_Flag,&Boot_Flag,sizeof(Boot_Flag),&Err)==sizeof(Boot_Flag) &&\
         FIRST_BOOT_ON_FLAG==Boot_Flag)
        return;
      else
      {
        Read_Ext_RTC_Status();//��һ���ϵ��ȡһ���ⲿʱ�ӣ�����ֹͣ״̬λ���,���ⱨ��

        Write_Def_Para();
        Boot_Flag=FIRST_BOOT_ON_FLAG;
        Write_Storage_Data(BOOT_FLAG,&Boot_Flag,sizeof(Boot_Flag));
      }
    }
  }
}

#undef DEF_PARA_C
