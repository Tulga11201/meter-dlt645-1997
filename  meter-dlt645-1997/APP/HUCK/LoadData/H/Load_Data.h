#ifndef LOAD_DATA_H
#define LOAD_DATA_H

#undef EXT
#ifdef LOAD_DATA_C
#define EXT
#else
#define EXT extern
#endif

#define NULL_LOAD_INDEX 0xFFFF

#define LOAD_DATA_HEAD_SIZE 7//��������ͷ���ݵĴ�С����2�ֽڵ�0xA0��5���ֽڵ�ʱ��
#define LOAD_DATA_TYPE_NUM 6//�������ߵ�6������

//���������������
typedef struct{
  INT16U Start; //��һ��������
  INT16U Last; //���һ��������
  
  INT16U Last_Read;
  INT16U Hour_Index;
  
  INT8U CS[CS_BYTES];//У���
}S_LoadData_Index;

//�������ߴ洢�����Ϣ��������Ҫ�洢��������
typedef struct{
  INT16U DI;
  INT16U Len;
  INT8U Type;
}S_LoadData_Info;

//�������߲���
typedef struct{
 INT8U Time[4];
 INT16U Period[6];
 INT8U CS[CS_BYTES]; 
}S_LoadData_Para;

#ifdef LOAD_DATA_C
CONST S_LoadData_Info LoadData_Info[]=
{
  //ģʽ��bit0
  {DI_A_VOL,3,0},//��ѹ
  {DI_B_VOL,3,0},//��ѹ
  {DI_C_VOL,3,0},//��ѹ
  {DI_A_CUR_3,3,0},//����
  {DI_B_CUR_3,3,0},//����
  {DI_C_CUR_3,3,0},//����
  {0xB660,2,0},//Ƶ��
  //ģʽ��bit1
  {DI_ACTIVE_DIRECT,1,1},//�й������ʶ��
  {DI_REACTIVE_DIRECT,1,1},//�޹������ʶ��
  //{0xB63F,12,1},//�й�����
  {0xB631,3,1},
  {0xB632,3,1},
  {0xB633,3,1},
  {0xB630,3,1},

  {DI_REACTIVE_A,3,1},//�޹�����
  {DI_REACTIVE_B,3,1},//�޹�����
  {DI_REACTIVE_C,3,1},//�޹�����
  {DI_REACTIVE_ALL,3,1},//�޹�����  
  
  //ģʽ��bit2
  {0xB65F,8,2},//��������
  //ģʽ��bit3
  {0x9010,4,3},//�����й���
  {0x9110,4,3},//�����޹��ܣ�(����޹�1��)
  {0x9020,4,3},//�����й���
  {0x9120,4,3},//�����޹��ܣ�(����޹�2��)
  //ģʽ��bit4
  {0x9130,4,4},//һ�����޹���
  {0x9150,4,4},//�������޹���
  {0x9160,4,4},//�������޹���
  {0x9140,4,4},//�������޹���
  //ģʽ��bit5 
  {DI_ACTIVE_DEMAND,3,5},//�й�����
  {DI_REACTIVE_DEMAND,3,5}//�޹�����
};
#endif

//EXT volatile INT8U LoadData_Buf[150];
EXT NO_INIT volatile S_LoadData_Para LoadData_Para;
EXT NO_INIT volatile S_LoadData_Index LoadData_Index;
EXT NO_INIT volatile S_LoadData_Index LoadData_Index_Bak;

EXT void Read_LoadData_Para_From_Rom();
EXT void Read_LoadData_Index_Data_From_Rom();
EXT INT16U Read_Load_Data_With_Time(S_HEX_Time *pTime,void *pDst,void *pDst_Start,INT16U DstLen,INT8U *pErr);
EXT INT16U Read_Load_Data(PROTO_DI DI,INT8U Para[],INT8U ParaLen,void *pDst,void *pDst_Start,INT16U DstLen,INT8U *pErr);
EXT void Set_Def_Load_Data_Index();
EXT void Save_LoadData_Index();
EXT void Save_LoadData_Index_Bak();
EXT INT8U Write_Load_Data(INT8U *pSrc,INT16U SrcLen);
EXT void Check_LoadData_Index_Avail();
EXT void Check_LoadData_Para_Avail();
EXT INT16U Get_LoadData_Hour_Index(INT8U Time[]);
EXT INT8U Check_LoadData_Index(S_LoadData_Index *pInfo);
EXT void Save_LoadData_PD_Data();
EXT INT16U Make_LoadData();
EXT INT16U Get_LoadData_All_Len();
EXT INT16U Get_LoadData_Type_Len(INT8U Type);
EXT void LoadData_Proc();

#endif
