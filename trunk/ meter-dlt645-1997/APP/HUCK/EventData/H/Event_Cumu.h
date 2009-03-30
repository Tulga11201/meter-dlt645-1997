#ifndef EVENT_CUMU0_H
#define EVENT_CUMU0_H

#undef EXT
#ifdef EVENT_CUMU0_C
#define EXT
#else
#define EXT extern
#endif

#define NULL_EVENT_ID 0xFF

#define DATA_ADD 0
#define DATA_DEC 1


#define ID_EVENT_TOTAL_LOSS_VOL 0xD0//��ʧѹ�¼�
#define ID_EVENT_TOTAL_LOSS_CUR 0xD1//��ʧ���¼�
#define ID_EVENT_TOTAL_NEG_CUR  0xD2//�ܷ����¼�
#define ID_EVENT_TOTAL_BREAK_VOL 0xD3//�ܶ����¼�


typedef struct
{
  INT8U Flag[2];
  INT8U CS[CS_BYTES];
}S_Prog_Flag;

#define ARRAY_DI_NUM 20

typedef struct 
{
	INT8U DI_Num;
	PROTO_DI DI[ARRAY_DI_NUM];
}S_DI_Array;

//�����¼����ۼӴ���
typedef struct{
	INT8U Event_ID;//�¼� ID
	
	//�¼����ۼ�ʱ��ʹ�����Ҫ���⴦��
	//STORA_DI Counts_DI;//�����ۼ�DI,��ͬ��ͨ��Э��DI
	//INT8U Counts_Start;
	//INT8U Counts_Len;
	
	//STORA_DI Mins_DI;//ʱ���ۼ�DI,��ͬ��ͨ��Э��DI
	//INT8U Mins_Start;
	//INT8U Mins_Len;
	
	///////////////////////���沿����ʱ��ʹ������ۼӣ���׼��Լ���涼�е�//////////////////////////////
	
	///////////////////////���沿���ǵ��ܵ����ۼ�///////////////////////////
	STORA_DI Occur_Stora_DI;//����ʱ�ĵ������ݴ洢DI
	STORA_DI Total_Stora_DI;//�ܵĵ������ݵ�DI,��ͬ��Э��DI
	
	S_DI_Array const *pDI_Array;
		
}S_Event_Cumu_Data_Info;

typedef struct
{
  INT32U Min_Timer;
  INT8U Temp;
  
  EVENT_INSTANT_STATUS Meter_Instant_Status;//�¼�״̬��Ϣ
  INT8U Temp1;//���ñ�֤����Ľṹ�����
  
  S_Prog_Flag Prog_Flag;//��̼�¼
  INT8U Temp2;
  S_PSW_Err_Info PSW_Err_Info;//����������¼
  INT8U Temp3;
  S_BCD_Time Time;
  
  INT8U CS[CS_BYTES];
  
}S_Event_Cumu_Data;

EXT S_Event_Cumu_Data Event_Cumu_Data;
EXT void Event_Cumu_Mins_Proc();
EXT INT16U Event_Cumu_Data_Proc(INT8U Event_ID,INT8U Start_End_Flag,INT8U Flag);
EXT void All_Loss_Vol_Counts_Time_Proc(INT32U Counts,INT32U Mins);
EXT void Power_On_Event_Proc();
EXT void Save_Event_Cumu_PD_Data();
EXT INT16U Get_Cumu0_Event_Data(PROTO_DI DI, INT8U *pDst, INT8U *pDst_Start, INT16U DstLen,INT8U *pErr);
EXT INT8U Get_Total_Event_ID(INT8U Event_ID);
EXT void Set_Def_Event_Cumu0_Data();
EXT INT8U Check_Total_Event_ID(INT8U Event_ID);
EXT void Check_Event_Cumu_Avail();
EXT INT8U Check_Event_Total_Proc(INT8U Event_ID, INT8U Occur_Or_End);
EXT INT16U Get_Event_Cumu_Proto_Data(STORA_DI DI, INT8U *pDst, INT8U *pDst_Start, INT16U DstLen);
EXT INT16U Proto_Data_Add_Dec(INT8U Data_Flag,INT8U Add_Or_Dec,PROTO_DI DI[], INT8U DI_Num, INT8U *pData0, INT8U *pData1,INT8U *pDst, INT8U *pDst_Start, INT16U DstLen);
#endif
