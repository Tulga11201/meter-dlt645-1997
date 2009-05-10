#ifndef EXTEND_GD_H
#define EXTEND_GD_H

#undef EXT
#ifdef EXTEND_GD_C
#define EXT
#else
#define EXT extern
#endif

#define EXTEND_OPEN_SET_AUTH_TIME 30 //������ȷ�򿪷�Ȩ��30����

#define EVENT_MULTITIMES_DI_EXTEND //�ִ��¼�DI����չ
#define EVENT_MULTITIMES_EXTEND //��չ�ķִ��¼�
#define DATA_TRANS_EXTEND     //��չ�Ĵ�������
#define STORA_EXTEND  //�洢����չ
#define DEF_PARA_EXTEND

#define COMM_PROTO_VERSION "1.00-1.00-090318-Guangdong-XXXXXXXXXX"

EXT void Extend_Init();
EXT INT8U Extend_Set_Data_Proc(PROTO_DI DI,INT8U *pSrc, INT16U SrcLen);
EXT INT16U Extend_Event_MultiTimes_Proc(INT8U Event_ID,INT8U Occur_Or_End,INT8U Flag,INT8U *pReturn_Flag);
EXT INT16U Extend_Event_Cumu_Proc(INT8U Event_ID,INT8U Occur_Or_End,INT8U Flag,INT8U *pReturn_Flag);
EXT INT16U Extend_Get_Proto_Data(PROTO_DI DI, INT8U *pDst, INT8U *pDst_Start, INT16U DstLen,INT8U *pErr);
EXT INT16U Extend_Get_Single_Proto_Data_Proc(PROTO_DI DI,INT8U *pDst, INT8U *pDst_Start, INT16U DstLen, INT8U *pErr);
EXT void Extend_Set_Prog_Flag(PROTO_DI DI);
EXT void Extend_Save_PD_Data();
EXT void Extend_Main_Proc();
EXT void Extend_Def_Event_MultiTimes_Data();
EXT void Extend_Set_Def_Event_Cumu_Data();
EXT void Extend_Set_Def_Energy_Data();

#endif