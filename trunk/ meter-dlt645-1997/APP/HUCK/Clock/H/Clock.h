#ifndef CLOCK_H
#define CLOCK_H

#undef EXT
#ifdef CLOCK_C
#define EXT
#else
#define EXT extern
#endif

#define GET_CLOCK_PERIOD 50//��ȡ�ⲿʱ�����ڣ���δ�øú�

#define USE_EXT_RTC 0
#define USE_INTER_RTC 1

#define T_MIN 0
#define T_HOUR 1
#define T_DATE 2
#define T_MONTH 3
#define T_YEAR 4

//��ǰʱ�䶨��,BCD��ʽ
//Time[0]��
//Time[1]ʱ
//Time[2]��
//Time[3]��
//Time[4]��
typedef struct
{
  INT8U Time[5];
  INT8U Week;//0��ʾ����,1-6�ֱ��ʾ��1->��6
  INT8U CS[CS_BYTES];
}S_HEX_Time;

//ʱ�䶨��ṹ��
typedef struct
{
  INT8U Sec;
  INT8U Min;
  INT8U Hour;
  INT8U Week;//0��ʾ����,1-6�ֱ��ʾ��1->��6
  INT8U Date;
  INT8U Month;
  INT8U Year;
  
  INT8U CS[CS_BYTES];//У���
}S_BCD_Time;

typedef struct
{
  INT8U EXT_RTC_Err_Counts:6;  //�ⲿʱ�Ӵ������
  INT8U Set_INTER_RTC_Flag:1;//�ڲ�ʱ�ӱ����ñ�־��1��ʾ�ڲ�ʱ���������ù�,0��ʾ���ϵ���ڲ�ʱ�ӻ�û�����ù�
  INT8U Clock_Ready_Flag:1;  //ʱ�����ݾ�����־��1��ʾCur_Time0��Cur_Time1�������Ѿ�����
  INT8U CS[CS_BYTES];        //У���
}S_Clock_Info;

EXT NO_INIT volatile S_HEX_Time Cur_Time0;             //��ǰʱ��0
EXT NO_INIT volatile S_Clock_Info Clock_Info;

EXT NO_INIT volatile S_BCD_Time Cur_Time1;             //��ǰʱ��1

EXT volatile INT8U Err_Time[5];//����ʱ��,���ڼ�¼�¼���¼ʱ��

EXT NO_INIT volatile S_BCD_Time Cur_Time_Bak;          //Cur_Tim1��һ������


#ifdef CLOCK_C
//����ô��ʾ?
CONST S_BCD_Time Def_BCD_Time={.Sec=0x00,.Min=0x00,.Hour=0x00,.Week=0x01,.Date=0x01,.Month=0x01,.Year=0x01,.CS={0}};
#endif





EXT INT8U _Check_BCD_Time(INT8U Time[]);
EXT INT8U _Check_HEX_Time(INT8U Time[]);

EXT INT8U Check_HEX_Time(S_HEX_Time *pTime);
EXT INT8U Check_BCD_Time(S_BCD_Time *pTime);

EXT void Set_BCD_Time(INT8U Time[],S_BCD_Time *pBCD_Time);

EXT INT8U Get_Time_From_EXT_RTC(S_BCD_Time *pBCD_Time);
//��ʱ�����õ��ⲿRTC
EXT INT8U Set_Time_To_EXT_RTC(S_BCD_Time *pBCD_Time);
//���ڲ�RTC��ȡʱ������
EXT INT8U Get_Time_From_INTER_RTC(S_BCD_Time *pBCD_Time);
//��ʱ�����õ��ڲ�RTC
EXT INT8U Set_Time_To_INTER_RTC(S_BCD_Time *pBCD_Time);

EXT void Resume_Clock_Update();
EXT void Get_Timer_From_CPU_Inter(S_BCD_Time *pBCD_Time);

EXT void Save_PD_Time();
EXT void Save_Bak_PD_Time();
EXT void Init_Clock_Ram_Para();
EXT void Clock_Proc();
EXT void Clock_Update();
EXT INT8U Check_Time_Diff(S_BCD_Time *pTime0,S_BCD_Time *pTime1,INT8U Mins);
EXT INT8U Set_Time_EXT_INTER_Ram_RTC(S_BCD_Time * pBCD_Time);

EXT INT8U Convert_BCD_2_HEX_Time(S_BCD_Time *pBCD_Time,S_HEX_Time *pHEX_Time);
EXT INT8U Convert_HEX_2_BCD_Time(S_HEX_Time *pHEX_Time,S_BCD_Time *pBCD_Time);

EXT void Wait_Clock_Ready();
EXT void Check_Clock_Data_Avail();
EXT void Simulate_Clock();
EXT void Init_Clock(INT32U Mode);
#endif
