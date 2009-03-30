#ifndef DEMAND_H
#define DEMAND_H

#undef EXT
#ifdef DEMAND_C
#define EXT
#else
#define EXT extern
#endif
/*
�������ݴ洢���ص�:
CUR_DEMAND���Լ����з��ʵ�����
CUR_DEMAND_BAK�洢��ʽ��CUR_DEMANDһ��
CUR_DEMAND_PD��Ҫ�ǵ���洢,ֻ�洢S_Demand�ṹ��Cur_Demand
HIS_DEMAND��Ҫ�洢ǰN���µ����ݣ�ÿ���������CUR_DEMAND��ʽһ��
*/
#define MAX_PERIOD_SLIDE_RATIO 15//��������/����ʱ������ֵ

#define POWER_DIRECT_N 0//���幦�ʷ�������
#define POWER_DIRECT_P 1//����

#define POWER_DATA_RATIO 100

#define DEMAND_RATE_OFF(x) ((ONE_DEMAND_SAVE_SIZE+ROM_CS_BYTES)*(INT32U)x)//����ĳ�����ʵ��������������������洢���е�ƫ��
//������ز���
typedef struct
{
  INT8U Period;//�������ʱ��
  INT8U Slide_Time;//����ʱ��
  
  INT8U CS[CS_BYTES];	
}S_Demand_Para;

typedef struct
{
  //INT8U Period;//��������
  //INT8U Slide_Time;//����ʱ��
  
  INT32U Pos_Active[MAX_PERIOD_SLIDE_RATIO];//�����й�15�������ۼӵ�Ԫ,��λ0.0001kw
  INT32U Neg_Active[MAX_PERIOD_SLIDE_RATIO];//�����й�15�������ۼӵ�Ԫ,��λ0.0001kw
  INT32U Pos_Reactive[MAX_PERIOD_SLIDE_RATIO];//�����޹�15�������ۼӵ�Ԫ,��λ0.0001kvar
  INT32U Neg_Reactive[MAX_PERIOD_SLIDE_RATIO];//�����޹�15�������ۼӵ�Ԫ,��λ0.0001kvar
  INT16U Counts[MAX_PERIOD_SLIDE_RATIO];//ÿ���ۼӵ�Ԫ���ۼӴ�������
  INT8U Mins[MAX_PERIOD_SLIDE_RATIO];//ÿ����Ԫ�ۼ��˶��ٷ���?
  //INT8U Init_Flag[MAX_PERIOD_SLIDE_RATIO];//��ʼ����־��������ʼ������Ϊ1����һ����������counts������
  
  INT32U Cur_Pos_Active;//��ǰ��������,��λ0.0001kw
  INT32U Cur_Neg_Active;//��ǰ��������,��λ0.0001kw
  INT32U Cur_Pos_Reactive;//��ǰ��������,��λ0.0001kvar
  INT32U Cur_Neg_Reactive;//��ǰ��������,��λ0.0001kvar
  
  INT8U CS[CS_BYTES];
}S_Demand_Accu;//�����ۼ�

#ifdef DEMAND_C
CONST S_Demand_Para Def_Demand_Para={0x15,1,{0}};
#endif

//����һ����������������ݽṹͨ����������ĳ�����ʻ��ܵ�������������
typedef struct
{
  //INT8U Time[5];//����ʱ��㣬��ʾ�����ݵĶ���ʱ���,������ɺ����ϸ���Ϊ�´ζ����ʱ���
  S_HEX_Time Time;
  
  INT8U Temp;//���ã���������ṹ�����
  //�����й����䷢��ʱ��
  INT32U Pos_Active;
  INT8U Pos_Active_Time[5];
  //�����й����䷢��ʱ��
  INT32U Neg_Active;
  INT8U Neg_Active_Time[5];
  //�������޹����䷢��ʱ��
  INT32U Quad_Reactive[4];
  INT8U Quad_Reactive_Time[4][5];
  //�����޹����䷢��ʱ��
  INT32U Pos_Reactive;
  INT8U Pos_Reactive_Time[5];
  //�����޹����䷢��ʱ��
  INT32U Neg_Reactive;
  INT8U Neg_Reactive_Time[5];
  //����У���
  INT8U CS[CS_BYTES];
}S_One_Demand;

//�������ݽṹ�壬��ʾÿ�����ʵ�������Ϣ
typedef struct 
{
  INT8U Head;//ͷ
  
  INT8U Rate;//��ǰ����
  S_One_Demand Demand[2];//�����ܺ͵�ǰ���ʵ��������� 
  
  INT32U Data_Ready_Flag;   
  
  INT8U CS[CS_BYTES];
  
  INT8U Tail;//β
}S_Demand;//

EXT volatile S_Demand_Para Demand_Para;
EXT volatile S_Demand_Accu Demand_Accu;
EXT NO_INIT volatile S_Demand Cur_Demand;     //��ǰ����������ݽṹ��

EXT volatile INT8U Clear_Demand_Way;//��������ʽ

EXT INT8U Check_Demand_Data(S_Demand *pDemand);
EXT void Read_Demand_Para_From_Rom();
EXT void Read_Demand_Data_From_Rom();
EXT INT16U Read_Demand_Rate_Data(INT8U Rate,void *pDst,void *pDst_Start,INT16U DstLen);
EXT void Save_Cur_Demand_Data();
EXT void Save_Cur_Demand_PD_Data();
EXT void Save_Cur_Demand_Bak_Data();
EXT void Set_Def_Cur_Demand_Data();
EXT void Set_Def_Demand_Data();
EXT void Check_Man_Clr_Demand();
EXT void Freeze_Demand_Data(S_HEX_Time *pTime);
EXT void Demand_Check_Rate_Change();
EXT void Check_Demand_Para_Avail();
EXT void Demand_Calc();
EXT void Demand_Accu_Clear();
EXT void Demand_Clear(S_HEX_Time *pTime);
EXT void Demand_Proc();
EXT void Clear_Demand_Record();
EXT void Debug_Print_Time(INT8U Time[]);
EXT void Debug_Print_HEX_Time(INT8U Time[]);
EXT void PowerOn_Demand_Proc();
EXT void Check_Demand_Data_Avail();
EXT void Clear_Cur_Demand_Data();
EXT void Clear_All_Demand_Data();
EXT void Get_Last_Freeze_Time(S_HEX_Time *pSrc,S_HEX_Time *pDst);
EXT void Get_Next_Freeze_Time(S_HEX_Time *pSrc,S_HEX_Time *pDst);
EXT void Get_NowMonth_Freeze_Time(S_HEX_Time *pSrc,S_HEX_Time *pDst);
EXT void Set_One_Demand_Time(S_One_Demand *pSrc,S_HEX_Time *pTime);
EXT void PowerOn_Demand_Data_Freeze();
EXT void PowerDown_Save_Demand_Data();
EXT void Debug_Print_Cur_Demand_Info();
#endif
