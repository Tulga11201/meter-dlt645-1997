#ifndef DATA_PARA_H
#define DATA_PARA_H

#include "Data_Trans.h"

#undef EXT
#ifdef DATA_PARA_C
#define EXT
#else
#define EXT extern
#endif

#define MAX_INIT_CLR_DOG_COUTS 20000

//����洢�ڵ�eerom�еĵ������ݵĴ�С
#define ENERGY_SAVE_SIZE sizeof(S_Energy)//(S_OFF(S_Energy,CS))
#define ONE_DEMAND_SAVE_SIZE sizeof(S_One_Demand)//(S_OFF(S_One_Demand,CS))
#define DEMAND_SAVE_SIZE ((ONE_DEMAND_SAVE_SIZE+ROM_CS_BYTES)*(MAX_RATES+1)+ROM_CS_BYTES)//������������ΪMAX_RATES+1����ÿ������洢һ�����ʵ�����
#define LOAD_DATA_HOUR_INDEX_NUM ((INT16U)24*12*31*4)//ÿСʱһ���������� 090311�޸�Ϊû15����һ����������

#define HIS_ENERGY_DATA         0//��ʷ��������
#define HIS_DEMAND_DATA         1//��ʷ��������
#define HIS_DEMAND_TIME_DATA    2//��ʷ����ʱ������
#define HIS_VOLSTAT_DATA        3//��ʷ��ѹͳ������

//---------��������������ݵĴ洢��ʾ,����0x10000��ʼ,��Щ���������Protocol_Data�ж���-begin-----------------------//
#define BOOT_FLAG          0x010000//������־,�����Ƿ��ǵ�һ���ϵ�

#define CUR_ENERGY_PD      0x010001//��ǰ��������洢
#define CUR_DEMAND_PD      0x010002//��ǰ��������洢

#define CUR_VOLSTAT_PD     0x010003//���µ�ѹ�������
#define TOTAL_VOLSTAT_PD   0x010004//�ܵ�ѹ�������
#define CUR_EVENT_PD       0x010005//�¼��ۼ�����
#define CUMU_EVENT_PD      0x010006//�¼��ۼƵ���洢
#define TIME_PD            0x010008//����ʱ��
#define TIME_BAK_PD        0x010009//����ʱ�䱸��

#define CUR_ENERGY         0x01000A//��ǰ����
#define CUR_DEMAND         0x01000B//��ǰ����
#define CUR_DEMAND_TIME    0x01000C//��ǰ����ʱ��
#define CUR_VOLSTAT        0x01000D//��ǰ��ѹ�������
#define TOTAL_VOLSTAT      0x01000E//�ܵ�ѹ�������
#define EVENT_CUMU         0x01000F//�¼��ۼ�����

#define CUR_ENERGY_BAK0    0x010010//��ǰ��������
#define CUR_ENERGY_BAK1    0x010011
#define CUR_ENERGY_BAK2    0x010012
#define CUR_DEMAND_BAK     0x010013//��ǰ��������
#define CUR_VOLSTAT_BAK    0x010014//��ǰ��ѹ������ݱ���
#define TOTAL_VOLSTAT_BAK  0x010015//�ܵ�ѹ������ݱ���
//#define EVENT_CUMU_BAK     0x010016//�¼��ۼ����ݵı���
#define SAVE_PD_DATA_TIME  0x010016//�洢�������ʹ�õ�ʱ��

#define ADJ_METER_PARA     0x010020//У�����,256�ֽ�
#define METER_PARA0        0x010021//������5��1�ֽڵĽϱ����
#define METER_PARA1        0x010022
#define METER_PARA2        0x010023
#define METER_PARA3        0x010024
#define METER_PARA4        0x010025

#define HIS_ENERGY         0x010100//��ʷ����,HIS_ENERGY_DATA_MONTHS��������
                                   //����HIS_ENERGY_DATA_MONTHS��
#define HIS_DEMAND         0x010200//��ʷ����,HIS_ENERGY_DATA_MONTHS��������
                                   //����HIS_ENERGY_DATA_MONTHS��
#define HIS_VOLSTAT        0x010300//��ʷ��ѹͳ������,HIS_VOLSTAT_DATA_MONTHS��������
                                   //����HIS_VOLSTAT_DATA_MONTHS��
#define ENERGY_FREEZE_TIME   0x010400//�����ܵ������ڶ���ʱ��
#define REACTIVE_FREEZE_TIME 0x010401//�޹��������ڶ���ʱ��

#define PROG_RECORD          0x010402 //��̼�¼
#define CLR_DEMAND_RECORD    0x010403 //��������¼

#define LOAD_DATA_INDEX      0x010500//�������ߵĴ洢��Ϣ
#define LOAD_DATA_INDEX_BAK  0x010501//�������ߵĴ洢��Ϣ����
#define LOAD_DATA_INDEX_PD   0x010502//����������������洢

//�¼���¼���һ�δ洢DI�Ĵ洢
#define E_E400                0x01E400//
#define E_E900                0x01E900//�¼���¼
#define E_E910                0x01E910
#define E_E920                0x01E920
#define E_E930                0x01E930
#define E_E940                0x01E940
#define E_E950                0x01E950//�¼���¼
#define E_E960                0x01E960
#define E_E970                0x01E970
#define E_E980                0x01E980
#define E_E990                0x01E990
#define E_E9A0                0x01E9A0
#define E_E9B0                0x01E9B0
#define E_E9C0                0x01E9C0
#define E_E9D0                0x01E9D0
#define E_E9E0                0x01E9E0
#define E_E9F0                0x01E9F0

#define E_EA00                0x01EA00
#define E_EA10                0x01EA10
#define E_EA20                0x01EA20
#define E_EA30                0x01EA30
#define E_EA40                0x01EA40
#define E_EA50                0x01EA50
#define E_EA60                0x01EA60
#define E_EA70                0x01EA70
#define E_EA80                0x01EA80
#define E_EA90                0x01EA90
#define E_EAA0                0x01EAA0
#define E_EAB0                0x01EAB0
#define E_EAC0                0x01EAC0
#define E_EAD0                0x01EAD0
#define E_EAE0                0x01EAE0
#define E_EAF0                0x01EAF0

#define E_EB00                0x01EB00
#define E_EB10                0x01EB10
#define E_EB20                0x01EB20
#define E_EB30                0x01EB30
#define E_EB40                0x01EB40
#define E_EB50                0x01EB50
#define E_EB60                0x01EB60
#define E_EB70                0x01EB70
#define E_EB80                0x01EB80
#define E_EB90                0x01EB90
#define E_EBA0                0x01EBA0
#define E_EBB0                0x01EBB0
#define E_EBC0                0x01EBC0
#define E_EBD0                0x01EBD0
#define E_EBE0                0x01EBE0
#define E_EBF0                0x01EBF0

#define E_EC00                0x01EC00
#define E_EC10                0x01EC10
#define E_EC20                0x01EC20
#define E_EC30                0x01EC30
#define E_EC40                0x01EC40
#define E_EC50                0x01EC50
#define E_EC60                0x01EC60
#define E_EC70                0x01EC70
#define E_EC80                0x01EC80
#define E_EC90                0x01EC90
#define E_ECA0                0x01ECA0
#define E_ECB0                0x01ECB0
#define E_ECC0                0x01ECC0
#define E_ECD0                0x01ECD0
#define E_ECE0                0x01ECE0
#define E_ECF0                0x01ECF0

#define E_ED00                0x01ED00
#define E_ED10                0x01ED10
#define E_ED20                0x01ED20
#define E_ED30                0x01ED30
#define E_ED40                0x01ED40
#define E_ED50                0x01ED50
#define E_ED60                0x01ED60
#define E_ED70                0x01ED70
#define E_ED80                0x01ED80
#define E_ED90                0x01ED90
#define E_EDA0                0x01EDA0
#define E_EDB0                0x01EDB0
#define E_EDC0                0x01EDC0
#define E_EDD0                0x01EDD0
#define E_EDE0                0x01EDE0

/*
//ʧѹ����-ʱ��ʹ���
#define TOTAL_LOSS_VOL        0x01F000
#define A_LOSS_VOL            0x01F001
#define B_LOSS_VOL            0x01F002
#define C_LOSS_VOL            0x01F003
#define AB_LOSS_VOL           0x01F004
#define AC_LOSS_VOL           0x01F005
#define BC_LOSS_VOL           0x01F006
#define ABC_LOSS_VOL          0x01F007
#define ALL_LOSS_VOL          0x01F008

//ʧ������-ʱ��ʹ���
#define TOTAL_LOSS_CUR        0x01F010
#define A_LOSS_CUR            0x01F011
#define B_LOSS_CUR            0x01F012
#define C_LOSS_CUR            0x01F013
#define AB_LOSS_CUR           0x01F014
#define AC_LOSS_CUR           0x01F015
#define BC_LOSS_CUR           0x01F016
#define ALL_LOSS_CUR          0x01F017

//��������
#define TOTAL_BREAK_VOL       0x01F020
#define A_BREAK_VOL           0x01F021
#define B_BREAK_VOL           0x01F022
#define C_BREAK_VOL           0x01F023

#define TOTAL_REVERSE         0x01F030
#define A_REVERSE             0x01F031
#define B_REVERSE             0x01F032 
#define C_REVERSE             0x01F033
 
//ʧѹ�ۼƵ�������
#define _TOTAL_LOSS_VOL       0x01F040
#define _A_LOSS_VOL           0x01F041
#define _B_LOSS_VOL           0x01F042
#define _C_LOSS_VOL           0x01F043
#define _AB_LOSS_VOL          0x01F044 
#define _AC_LOSS_VOL          0x01F045
#define _BC_LOSS_VOL          0x01F046
#define _ABC_LOSS_VOL         0x01F047
#define _ALL_LOSS_VOL         0x01F048

//ʧ���ۼƵ�������
#define _TOTAL_LOSS_CUR       0x01F050
#define _A_LOSS_CUR           0x01F051
#define _B_LOSS_CUR           0x01F052
#define _C_LOSS_CUR           0x01F053
#define _AB_LOSS_CUR          0x01F054
#define _AC_LOSS_CUR          0x01F055
#define _BC_LOSS_CUR          0x01F056
#define _ALL_LOSS_CUR         0x01F057
*/
//ʧѹ
#define OCCUR_TOTAL_LOSS_VOL 0x020000
#define OCCUR_A_LOSS_VOL     0x020001
#define OCCUR_B_LOSS_VOL     0x020002
#define OCCUR_C_LOSS_VOL     0x020003
#define OCCUR_AB_LOSS_VOL    0x020004
#define OCCUR_AC_LOSS_VOL    0x020005
#define OCCUR_BC_LOSS_VOL    0x020006
#define OCCUR_ABC_LOSS_VOL   0x020007
//ȫʧѹ
#define OCCUR_ALL_LOSS_VOL   0x020008

#define TOTAL_TOTAL_LOSS_VOL 0x020010
#define TOTAL_A_LOSS_VOL     0x020011
#define TOTAL_B_LOSS_VOL     0x020012
#define TOTAL_C_LOSS_VOL     0x020013
#define TOTAL_AB_LOSS_VOL    0x020014
#define TOTAL_AC_LOSS_VOL    0x020015
#define TOTAL_BC_LOSS_VOL    0x020016
#define TOTAL_ABC_LOSS_VOL   0x020017
//ȫʧѹ
#define TOTAL_ALL_LOSS_VOL   0x020018

//ʧ��
#define OCCUR_TOTAL_LOSS_CUR 0x020020
#define OCCUR_A_LOSS_CUR     0x020021
#define OCCUR_B_LOSS_CUR     0x020022
#define OCCUR_C_LOSS_CUR     0x020023
#define OCCUR_AB_LOSS_CUR    0x020024
#define OCCUR_AC_LOSS_CUR    0x020025
#define OCCUR_BC_LOSS_CUR    0x020026
//ȫʧ��
#define OCCUR_ABC_LOSS_CUR   0x020027

#define TOTAL_TOTAL_LOSS_CUR 0x020030
#define TOTAL_A_LOSS_CUR     0x020031
#define TOTAL_B_LOSS_CUR     0x020032
#define TOTAL_C_LOSS_CUR     0x020033
#define TOTAL_AB_LOSS_CUR    0x020034
#define TOTAL_AC_LOSS_CUR    0x020035
#define TOTAL_BC_LOSS_CUR    0x020036
#define TOTAL_ABC_LOSS_CUR   0x020037

//����
#define OCCUR_TOTAL_NEG_CUR 0x020040
#define OCCUR_A_NEG_CUR     0x020041
#define OCCUR_B_NEG_CUR     0x020042
#define OCCUR_C_NEG_CUR     0x020043

#define TOTAL_TOTAL_NEG_CUR 0x020050
#define TOTAL_A_NEG_CUR     0x020051
#define TOTAL_B_NEG_CUR     0x020052
#define TOTAL_C_NEG_CUR     0x020053

//����
#define OCCUR_TOTAL_BREAK_VOL 0x020060
#define OCCUR_A_BREAK_VOL     0x020061
#define OCCUR_B_BREAK_VOL     0x020062
#define OCCUR_C_BREAK_VOL     0x020063

#define TOTAL_TOTAL_BREAK_VOL 0x020070
#define TOTAL_A_BREAK_VOL     0x020071
#define TOTAL_B_BREAK_VOL     0x020072
#define TOTAL_C_BREAK_VOL     0x020073

#define LOAD_DATA_HOUR_INDEX 0x030000//��������Сʱ�����洢,����24*31*12*4����Ŀ
#define LOAD_DATA            0x040000//��������,0x1000-->0x1000+LOAD_DATA_NUM
                             //����LOAD_DATA_NUM��

//////////����DI�����Data_trans.h�еı���һ��,��Ϊ������Ҫ�ⲿ��ͨ��Get_DLT645_Data����������
#define METER_ADDR0        0x0105//���ַ0
#define METER_ADDR1        0x0106//���ַ1
#define METER_ADDR2        0x0107//���ַ2

#define COMM_BAUD0         0x0108//��һ·������
#define COMM_BAUD1         0x0109//�ڶ�·������
#define COMM_BAUD2         0x010A//����·������

#define PASSWORD_0         0x010B//0������,Э�����޴����Ϊ����ܶ���Ҳ����ֱ��ͨ��DIд�����Ǹ���������PROTO_DI�����ʹ�С,��ΪSet_Prog_������ʹ�ø�DI
#define PASSWORD_1         0x010C//1������
#define PASSWORD_2         0x010D//2������

#define ADJ_METER_PUL_VOL_CUR_SPEC 0xCEE0//���塢��ѹ���������,3�ֽ�
#define ADJ_METER_PARA_STATUS      0xCEE1//У�����״̬����,1�ֽ�
#define ADJ_METER_A_POW            0xCEE2//A�๦�������������,3�ֽ�
#define ADJ_METER_B_POW            0xCEE3//B�๦�������������,3�ֽ�
#define ADJ_METER_C_POW            0xCEE4//C�๦�������������,3�ֽ�
#define ADJ_METER_A_PHASE          0xCEE5//A����λ�����������,3�ֽ�
#define ADJ_METER_B_PHASE          0xCEE6//B����λ�����������,3�ֽ�
#define ADJ_METER_C_PHASE          0xCEE7//B����λ�����������,3�ֽ�
#define ADJ_METER_A_VOL            0xCEE8//A���ѹ��������,3�ֽ�
#define ADJ_METER_B_VOL            0xCEE9//B���ѹ��������,3�ֽ�
#define ADJ_METER_C_VOL            0xCEEA//C���ѹ��������,3�ֽ�
#define ADJ_METER_A_CUR            0xCEEB//A�������������,3�ֽ�
#define ADJ_METER_B_CUR            0xCEEC//B�������������,3�ֽ�
#define ADJ_METER_C_CUR            0xCEED//C�������������,3�ֽ�

#define TOTAL_LOSS_VOL_OCCUR_TIME 0xB330
#define A_LOSS_VOL_OCCUR_TIME     0xB331
#define B_LOSS_VOL_OCCUR_TIME     0xB332
#define C_LOSS_VOL_OCCUR_TIME     0xB333
#define AB_LOSS_VOL_OCCUR_TIME    0xB334
#define AC_LOSS_VOL_OCCUR_TIME    0xB335
#define BC_LOSS_VOL_OCCUR_TIME    0xB336
#define ABC_LOSS_VOL_OCCUR_TIME   0xB337
//#define ALL_LOSS_VOL_OCCUR_TIME   0xB338

#define TOTAL_LOSS_VOL_END_TIME   0xB340
#define A_LOSS_VOL_END_TIME       0xB341
#define B_LOSS_VOL_END_TIME       0xB342
#define C_LOSS_VOL_END_TIME       0xB343
#define AB_LOSS_VOL_END_TIME      0xB344
#define AC_LOSS_VOL_END_TIME      0xB345
#define BC_LOSS_VOL_END_TIME      0xB346
#define ABC_LOSS_VOL_END_TIME     0xB347
//#define ALL_LOSS_VOL_END_TIME     0xB348


#define CHK_IMP0           0xFFFFFFF0  
#define CHK_IMP1           0xFFFFFFF1
#define CHK_IMP2           0xFFFFFFF2
#define CHK_IMP3           0xFFFFFFF3
#define CHK_IMP4           0xFFFFFFF4
#define CHK_IMP5           0xFFFFFFF5
#define CHK_IMP6           0xFFFFFFF6
#define CHK_IMP7           0xFFFFFFF7
//---------------����������ݵĴ洢��ʾ-end-----------------------//

//----------------��ʱ���ݳ���------------
#define LOSS_VOL_DATA_LEN ((19*4) + 13)//ʧѹ�ۼ����ݳ��� 
#define LOSS_CUR_DATA_LEN ((16*4) + 13)//ʧ���ۼ����ݳ���
#define NEG_CUR_DATA_LEN  ((8*4) + 13) //�����ۼ����ݳ���
#define ALL_LOSS_VOL_DATA_LEN 13     //ȫʧѹ�ۼ����ݳ���
#define ALL_LOSS_CUR_DATA_LEN 13
#define BREAK_VOL_DATA_LEN 13        //�����ۼ����ݳ���

//------------------------------------------------

#define ADJ_METER_PARA_SIZE  256
#define LOAD_DATA_SIZE       118//ÿ�������������ݵĴ�С
#define LOAD_DATA_INDEX_SIZE 5//ÿ��Сʱ�������ݵĴ�С
#define LOAD_DATA_INDEX_NUM  8544//�������ߵ�Сʱ��������,ÿСʱһ�������Դ�8544��

#define PSW0_DI            0x0001//0�������ʶ��
#define PSW1_DI            0x0002//1�������ʶ��
#define PSW2 DI            0x0003//2�������ʶ��

#define NULL_IMP 0xFF //һ�������ڵ�IMP��־
#define IMP0 0x00  //��Ҫ����,У�������ģʽ��
#define IMP1 0x01  //��ǰ��������������
#define IMP2 0x02  //��ʷ���ݺͱ�������
#define IMP3 0x03  //��ͨ�¼���¼
#define IMP4 0x04  //����
#define IMP5 0x05  //���������Լ���ز���
#define IMP6 0x06  //����洢����
#define IMP7 0x07  //��Ҫ�¼���¼

//#define HIS_HEAD sizeof(S_HEX_Time) //�洢��ʷ������������ʱ��ͷ����

#define IMP_LOG_MEM 5//ĳ����Ҫ���ݴ洢���߼��洢������,���ֵ
/*
#define IMP_ADJ     0x00 //��Ҫ����,У�������ģʽ��
#define IMP_ENERGY   0x01
#define IMP_HIS      0x02
#define IMP_EVENT    0x03
#define IMP_LOAD     0x04
#define IMP_POWD     0x05
*/
//������Ҫ���ø�����
/*
typedef struct
{
  INT8U Loss_Vol_Flag[4];
  INT32U Loss_Vol_Counts[4];//�ܡ�A��B��Cʧѹ���� 
  INT32U Loss_Vol_Time[4];//��ʧѹ�ۼ�ʱ��
  
  INT8U Loss_Cur_Flag[4];
  INT32U Loss_Cur_Counts[4];//��ʧ������
  INT32U Loss_Cur_Time[4];//��ʧ��ʱ��
  
  INT8U CS[CS_BYTES];
}S_Event_Cumu;
*/

typedef struct
{
  INT8U Imp_Flag;//���ݱ�־
  INT8U LOG_Mem[IMP_LOG_MEM];//��洢���߼��洢������һ����ԭʼ���ݣ��������Ǳ��ݣ�NULL_MEM��ʾû��
}S_Data_Mem_Map;

//#define RD_WR 0//�ɶ���д
#define WR 1   //ֻ��д
#define RD 2   //�ɶ�
typedef struct
{
  INT8U Imp_Flag;
  INT32U Offset;
}S_Data_Para_Info;

typedef struct{
  STORA_DI DI; 
//������ʶ,��DLT645���ݣ�ͬʱ�����䡣
  //INT8U RW_Flag;
//������д��־����READ��ʾ�ɶ�����WRITE ��ʾ��д,READ|WRITE��ʾ�ɶ���д
  //INT8U PSW_Flag;
//��������ȼ���־,PSW_N��ʾ��N���������ϲſ��޸ĸò���(N=0,1,2)
  INT8U Imp_Flag;
//��Ҫ�ȼ���־ ��IMP0��ʾ����Ҫ IMP1->IMP5��Ҫ�����εݼ�
  INT16U Len; //���ݻ��������
//�ɷ��ǼӶ�д��������������ɼ�ǿIMP��ͬ�Ĳ������ݴ�������
  INT16U Num;
  //�����ڴ���ĸ���
}S_Data_Para_Storage_Info;


EXT INT8U Check_SuperPSW_Jump();
EXT INT8U Check_Imp_Flag(INT8U Imp_Flag);
EXT INT8U Get_Storage_Data_ImpFlag(STORA_DI DI);
EXT INT32U Get_Storage_Data_Off(STORA_DI DI);
EXT INT16U Get_Storage_Data_Len(STORA_DI DI);
EXT INT32U Get_Imp_Data_Size(INT8U Imp_Flag);
EXT INT32U Get_Imp_Mem_Size(INT8U Imp_Flag);
EXT INT8U Read_Imp_Data(INT8U Imp_Flag,INT32U Offset,void *pDst,INT16U RD_Len,void *pDst_Start,INT16U DstLen);
EXT INT8U Write_Imp_Data(INT8U Imp_Flag,INT32U Offset,void *pSrc,INT16U SrcLen);

EXT INT16U Read_Storage_Data_Fix_Len(STORA_DI DI,INT16U Offset,INT16U Len,void *pDst,void *pDst_Start,INT16U DstLen,INT8U *pErr);
EXT INT8U Write_Storage_Data_Fix_Len(STORA_DI DI,INT16U Offset,void *pSrc,INT16U SrcLen);

EXT INT16U Read_Storage_Data(STORA_DI DI,void *pDst,void *pDst_Start,INT16U DstLen,INT8U *pErr);
EXT INT8U Write_Storage_Data(STORA_DI DI,void *pSrc,INT16U SrcLen);

EXT INT8U Check_Imp_Data_Storage();
EXT void Check_Sys_Storage();
//EXT INT16U Read_HIS_Data(INT8U Data_Flag,S_HEX_Time *pTime,void *pDst,void *pDst_Start,INT16U DstLen,INT8U *pErr);
//EXT INT8U Write_HIS_Data(INT8U Data_Flag,S_HEX_Time *pTime,void *pSrc,INT16U SrcLen);

EXT void Check_Data_Storage();
EXT void Debug_Print_Data_Storage();
EXT void Check_Sys_Storage();
#endif
