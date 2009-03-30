#ifndef Pulse_h
#define Pulse_h


//#undef MeasuProc_PUCK_EXT
#ifndef MeasuPulse_PUCK
#define MeasuPulse_PUCK_EXT  extern
#else
#define MeasuPulse_PUCK_EXT 
#endif



#define DI_AC_PULSE     0xc030    //�й����峣��
#define DI_REAC_PULSE   0xc031    //�޹����峣��
#define DI_PULSE_WIDTH   0xc211    //��������ȣ�����


typedef struct
{ 
  INT32U Ac_Pulse;               //�й�����
  INT32U Rea_Pulse;               //�޹�����
  INT8U Ac_Pulse_Freq;           //�й������Ƶϵ��
  INT8U Reac_Pulse_Freq;         //�޹������Ƶϵ��
  INT16U Pulse_Width;             //��������ȣ�����,���޹�һ�¡�
  INT8U CS[CS_BYTES];            //��Ҫ������SRAM��У���
}PULSE_STRUC;                    //MeasuICϵͳģʽ��


MeasuPulse_PUCK_EXT PULSE_STRUC Sys_Pulse_Var;

INT8U Get_Pulse_Para(void);
void Send_Acpower_Pulse(void);
void Send_Reacpower_Pulse(void);
#endif

