#ifndef EVENT_CUMU_H
#define EVENT_CUMU_H

#undef EXT
#ifdef EVENT_CUMU_C
#define EXT
#else
#define EXT extern
#endif

#define PHASE_A   0x01
#define PHASE_B   0x02
#define PHASE_C   0x04
#define PHASE_AB  0x03
#define PHASE_AC  0x05
#define PHASE_BC  0x06
#define PHASE_ABC 0x07
#define PHASE_ALL 0x08

#define NULL_EVENT 0xFF//�¼�������־���κ겻��ȡ0�����ܺ��κ�һ��Event_ID�غ�

//��������¼��ۼ���Ϣ
typedef struct
{
  INT32U Counts;//ʧѹ���� 
  INT32U Time;//ʧѹ�ۼ�ʱ��
  
  INT8U CS[CS_BYTES];
}S_Phase_Cumu;

//ʧѹ�ۼ�����
typedef struct
{
  INT32U Counts;//ʧѹ���� 
  INT32U Time;//ʧѹ�ۼ�ʱ��
  
  INT32U Phase_Pos_Active[4];//�ܡ�A��B��C���ۼ��й�����
  INT32S Phase_Pos_Reactive[4];//�ܡ�A��B��C���������޹�������޹�1
  INT32U Phase_Neg_Active[4];//�ܡ�A��B��C���෴���й�
  INT32S Phase_Neg_Reactive[4];//�ܡ�A��B��C���෴���޹�������޹�2
  INT32U Phase_AH[3];//A��B��C���ల��ʱ��
  
  INT8U CS[CS_BYTES]; 
}S_Loss_Vol_Cumu;


//ʧ���ۼ�����
typedef struct
{
  INT32U Counts;//ʧѹ���� 
  INT32U Time;//ʧѹ�ۼ�ʱ��
  
  INT32U Phase_Pos_Active[4];//�ܡ�A��B��C���ۼ��й�����
  INT32S Phase_Pos_Reactive[4];//�ܡ�A��B��C���������޹�������޹�1
  INT32U Phase_Neg_Active[4];//�ܡ�A��B��C���෴���й�
  INT32S Phase_Neg_Reactive[4];//�ܡ�A��B��C���෴���޹�������޹�2
  //INT32U Phase_AH[3];//A��B��C���ల��ʱ��
  
  INT8U CS[CS_BYTES]; 
}S_Loss_Cur_Cumu;

//�����ڼ��ۼ�����
typedef struct
{
  INT32U Counts;
  INT32U Time;
  
  INT32U Phase_Pos_Active[4];//�ܡ�A��B��C���ۼ��й�����
  INT32U Phase_Neg_Active[4];//�ܡ�A��B��C���෴���й�
  INT8U CS[CS_BYTES];
}S_Reverse_Cumu;//


//ȫʧѹ��ȫʧ���������ۼ�����
typedef struct
{
  INT32U Counts;
  INT32U Time;
  INT8U CS[CS_BYTES];
}S_Phase_Break_Cumu;

typedef struct
{
  INT8U Loss_Vol_Flag;      //ʧѹ��־
  INT8U Loss_Cur_Flag;      //ʧ����־
  INT8U All_Loss_Cur_Flag;  //ȫʧ����־��ȫʧ����ĳ��ʧ���ǿ���ͬʱ�����ģ���˶���һ�����־
  
  INT8U Phase_Reverse_Flag; //�����־
  INT8U Phase_Break_Flag;   //�����־

  INT8U Loss_Vol_Flag_Bak;      //ʧѹ��־
  INT8U Loss_Cur_Flag_Bak;      //ʧ����־
  INT8U All_Loss_Cur_Flag_Bak;  //ȫʧ����־��ȫʧ����ĳ��ʧ���ǿ���ͬʱ�����ģ���˶���һ�����־
  
  INT8U Phase_Reverse_Flag_Bak; //�����־
  INT8U Phase_Break_Flag_Bak;   //�����־ 
  
  INT8U CS[CS_BYTES];
}S_Event_Flag;

//�ܵ��¼��ۼ���
typedef struct
{
  INT8U Head;
  
  S_BCD_Time Event_Time;
  INT8U Temp0;//���ã���֤����Ľṹ�����
  
  EVENT_INSTANT_STATUS Meter_Instant_Status;//�¼�״̬��Ϣ
  INT8U Temp1;//���ñ�֤����Ľṹ�����
 
  S_Prog_Flag Prog_Flag;//��̼�¼
  
  S_Event_Flag Event_Flag; //ʧѹʧ���ȵķ�����־

  S_Phase_Cumu Phase_Loss_Vol[9];//�ܡ�A��B��C��AB��AC��BC��ABC��ȫʧѹ��
  S_Phase_Cumu Phase_Loss_Cur[8];//�ܡ�A��B��C��AB��AC��BC��ȫʧ��
  S_Phase_Cumu Phase_Break[4];//�������(������AB,BC,AC,ABC�����)�ܡ�A��B��C
  S_Reverse_Cumu Phase_Reverse[4];//���෴��(������AB,BC,AC,ABC�����)�ܡ�A��B��C

  
  S_Loss_Vol_Cumu Loss_Vol;//ʧѹ�ڼ��ۼƵ��ܵ�,���뿼�Ǻ�������
  S_Loss_Cur_Cumu Loss_Cur;//ʧ���ڼ��ۼƵ��ܵ�

  INT8U CS[CS_BYTES];
  INT8U Tail;
}S_Event_Cumu;

typedef struct
{
  INT32S Pos_Reactive[4];//A��B��C���������޹�  
  INT32U Neg_Reactive[4];//A��B��C���ܷ����޹�
}S_Phase_Reactive;


EXT NO_INIT volatile S_Event_Cumu Event_Cumu;     //�¼��ۼ�����
EXT volatile S_Phase_Reactive Cumu_Phase_Reactive; //��������޹��ۼ�����

EXT void Calc_Total_Loss_Vol();
EXT void Calc_Total_Loss_Cur();
EXT void Calc_Total_Phase_Break();
EXT void Calc_Total_Phase_Reverse();

EXT INT8U Check_Phase_Event(INT8U Flag,INT8U Phase);
EXT void Event_Cumu_Proc(INT8U Event_ID,INT8U Occur_Or_End);
EXT void Read_Event_Cumu_Data_From_Rom();
//EXT void Save_Event_Cumu_PD_Data();
//EXT void Event_Energy_Cumu(MEASU_ENERG *pEnergy);
EXT INT8U Check_Event_Occuring(INT8U Event_ID);
//EXT void Save_Event_Cumu_Bak_Data();
EXT void Set_Def_Event_Cumu_Data();

EXT void Init_Event_Cumu_Data();

#endif
