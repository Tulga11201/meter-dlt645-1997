#define DATA_TRANS_C
#include "Includes.h"

CONST INT8U Software_Version[5]=SOFT_VERSION;//����汾��
CONST INT8U Comm_Proto_Version[]={COMM_PROTO_VERSION};
CONST INT8U No_Var[10]={0};

//���ò�������ʱ��
#ifdef EXTEND_OPEN_SET_AUTH_TIME
#define OPEN_SET_AUTH_TIME EXTEND_OPEN_SET_AUTH_TIME
#else
#define OPEN_SET_AUTH_TIME 0
#endif

const S_Protocol_Data_Info Protocol_Data[]=
{
  DATA_TRANS_EXTEND 

  
//��ʶ����	���ݸ�ʽ	���ݳ���	��λ	  ��	д	����������
  {0x6000,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_ROM,(void *)0,0,4,S_INTU,1,4,0x3010|((HIS_ENERGY_DATA_MONTHS+1)<<8)|(MAX_RATES+1),SPEC_RATE},//�����й�
  {0x6010,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_ROM,(void *)0,0,4,S_INTS,1,4,0x3010|((HIS_ENERGY_DATA_MONTHS+1)<<8)|(MAX_RATES+1),SPEC_RATE},//�����޹�
  {0x6020,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_ROM,(void *)0,0,4,S_INTU,1,4,0x3010|((HIS_ENERGY_DATA_MONTHS+1)<<8)|(MAX_RATES+1),SPEC_RATE},//�����й�
  {0x6030,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_ROM,(void *)0,0,4,S_INTS,1,4,0x3010|((HIS_ENERGY_DATA_MONTHS+1)<<8)|(MAX_RATES+1),SPEC_RATE},//�����޹�
  {0x6040,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_ROM,(void *)0,0,4,S_INTU,1,4,0x3040|((HIS_ENERGY_DATA_MONTHS+1)<<8)|(MAX_RATES+1),SPEC_RATE},//�������޹� 
  
  //�������й�����
  {0x9010,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_ROM,(void *)0,0,4,S_INTU,1,4,0x1120|(MAX_RATES+1),SPEC_RATE},
  //�������޹���1-4�����޹�����
  {0x9110,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_ROM,(void *)0,0,4,S_INTS,1,4,0x1120|(MAX_RATES+1),SPEC_RATE},
  {0x9130,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_ROM,(void *)0,0,4,S_INTU,1,4,0x1140|(MAX_RATES+1),SPEC_RATE},
  //�����������й�����
  {0x9410,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_ROM,(void *)0,0,4,S_INTU,1,4,0x1120|(MAX_RATES+1),SPEC_RATE},
  //�����������޹���1-4�����޹�����
  {0x9510,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_ROM,(void *)0,0,4,S_INTS,1,4,0x1120|(MAX_RATES+1),SPEC_RATE},
  {0x9530,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_ROM,(void *)0,0,4,S_INTU,1,4,0x1140|(MAX_RATES+1),SPEC_RATE},
  //�������������й�����
  {0x9810,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_ROM,(void *)0,0,4,S_INTU,1,4,0x1120|(MAX_RATES+1),SPEC_RATE},
  //�������������޹���1-4�����޹�����
  {0x9910,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_ROM,(void *)0,0,4,S_INTS,1,4,0x1120|(MAX_RATES+1),SPEC_RATE},
  {0x9930,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_ROM,(void *)0,0,4,S_INTU,1,4,0x1140|(MAX_RATES+1),SPEC_RATE},
  
  {0xE701,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_ROM,(void *)0,0,4,S_INTU,1,4,0x11E3,SPEC_PHASE_ENERGY},//�������,����
  {0xE704,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_ROM,(void *)0,0,4,S_INTS,1,4,0x11E3,SPEC_PHASE_ENERGY},//�������,����
  {0xE707,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_ROM,(void *)0,0,4,S_INTU,1,4,0x11E3,SPEC_PHASE_ENERGY},//�������,����
  {0xE70A,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_ROM,(void *)0,0,4,S_INTS,1,4,0x11E3,SPEC_PHASE_ENERGY},//�������,����
  
  //ͭ��
  {0x9A00,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Cur_Energy.CopperLoss[0],0,4,S_INTU,0,4,1,SPEC_NO},//��ͭ��
  {0x9A01,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Cur_Energy.CopperLoss[1],0,4,S_INTU,0,4,1,SPEC_NO},//A��ͭ��
  {0x9A02,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Cur_Energy.CopperLoss[2],0,4,S_INTU,0,4,1,SPEC_NO},//B��ͭ��
  {0x9A03,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Cur_Energy.CopperLoss[3],0,4,S_INTU,0,4,1,SPEC_NO},//C��ͭ��
  //����
  {0x9B00,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Cur_Energy.IronLoss[0],0,4,S_INTU,0,4,1,SPEC_NO},//������
  {0x9B01,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Cur_Energy.IronLoss[1],0,4,S_INTU,0,4,1,SPEC_NO},//A������
  {0x9B02,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Cur_Energy.IronLoss[2],0,4,S_INTU,0,4,1,SPEC_NO},//B������
  {0x9B03,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Cur_Energy.IronLoss[3],0,4,S_INTU,0,4,1,SPEC_NO},//C������
  //����ʱ
  {0x9C00,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Cur_Energy.TransErr[0],0,4,S_INTU,0,4,1,SPEC_NO},//������
  {0x9C01,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Cur_Energy.TransErr[1],0,4,S_INTU,0,4,1,SPEC_NO},//A������
  {0x9C02,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Cur_Energy.TransErr[2],0,4,S_INTU,0,4,1,SPEC_NO},//B������
  {0x9C03,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Cur_Energy.TransErr[3],0,4,S_INTU,0,4,1,SPEC_NO},//C������
  
  //�������й��������
  {0xA010,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_ROM,(void *)0,0,4,S_INTU,0,4,0x1120|(MAX_RATES+1),SPEC_RATE},
  //�������޹���1-4�����޹��������
  {0xA110,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_ROM,(void *)0,0,4,S_INTU,0,4,0x1160|(MAX_RATES+1),SPEC_RATE},
  //�����������й��������
  {0xA410,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_ROM,(void *)0,0,4,S_INTU,0,4,0x1120|(MAX_RATES+1),SPEC_RATE},
  //�����������޹���1-4�����޹��������
  {0xA510,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_ROM,(void *)0,0,4,S_INTU,0,4,0x1160|(MAX_RATES+1),SPEC_RATE},
  //�������������й��������
  {0xA810,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_ROM,(void *)0,0,4,S_INTU,0,4,0x1120|(MAX_RATES+1),SPEC_RATE},
  //�������������޹���1-4�����޹��������
  {0xA910,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_ROM,(void *)0,0,4,S_INTU,0,4,0x1160|(MAX_RATES+1),SPEC_RATE},
 
  //�������й������������ʱ�� 
  {0xB010,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_ROM,(void *)0,0,4,S_INTU,0,4,0x1120|(MAX_RATES+1),SPEC_RATE},
  //�������޹���1-4�����޹������������ʱ��
  {0xB110,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_ROM,(void *)0,0,4,S_INTU,0,4,0x1160|(MAX_RATES+1),SPEC_RATE},
  //�����������й������������ʱ��  
  {0xB410,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_ROM,(void *)0,0,4,S_INTU,0,4,0x1120|(MAX_RATES+1),SPEC_RATE},
  //�����������޹���1-4�����޹������������ʱ��
  {0xB510,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_ROM,(void *)0,0,4,S_INTU,0,4,0x1160|(MAX_RATES+1),SPEC_RATE},
  //�������������й������������ʱ��
  {0xB810,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_ROM,(void *)0,0,4,S_INTU,0,4,0x1120|(MAX_RATES+1),SPEC_RATE},
  //�������������޹���1-4�����޹������������ʱ��
  {0xB910,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_ROM,(void *)0,0,4,S_INTU,0,4,0x1160|(MAX_RATES+1),SPEC_RATE},
 
//	
  {0xB210,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,(void *)&Prog_Record.Time[0],0,4,S_BCD,0,4,1,SPEC_NO},//���һ�α��ʱ��
  {0xB211,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,(void *)&Clr_Demand_Record.Time[0],0,4,S_BCD,0,4,1,SPEC_NO},//���һ��������0ʱ��
  {0xB212,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,(void *)&Prog_Record.Counts,0,4,S_INTU,0,2,1,SPEC_NO},//��̴���
  {0xB213,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,(void *)&Clr_Demand_Record.Counts,0,4,S_INTU,0,2,1,SPEC_NO},//������0����
  
  {0xB214,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,3,S_BCD,0,3,0x1111,SPEC_BAT_TIME},//�͹��ĵ�ع���ʱ��
//��ʶ����	���ݸ�ʽ	����	��λ	���ݳ���	����������
  {0xB220,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,(void *)0,0,36,S_BCD,0,36,0x1115,SPEC_VOLSTAT},//B220		R	��	36	��ѹ������ۼ����� ��ע1��
  {0xE501,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,(void *)0,0,3,S_BCD,0,3,0x1113,SPEC_VOLSTAT},//B221		R	��	36	  ���µ�ѹ������ݣ�ע1��
  {0xE511,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,(void *)0,0,3,S_BCD,0,3,0x1113,SPEC_VOLSTAT},//B222		R	��	36	��1�µ�ѹ������ݣ�ע1��
  {0xE521,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,(void *)0,0,3,S_BCD,0,3,0x1113,SPEC_VOLSTAT},//B223		R	��	36	��2�µ�ѹ������ݣ�ע1��
  {0xE531,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,(void *)0,0,3,S_BCD,0,3,0x1113,SPEC_VOLSTAT},//B224		R	��	36	��3�µ�ѹ������ݣ�ע1��
//E501		R	%	3	����A���ѹ�ϸ��ʣ�ע7��
//E502		R	%	3	����B���ѹ�ϸ��ʣ�ע7��
//E503		R	%	3	����C���ѹ�ϸ��ʣ�ע7��
//E511		R	%	3	��1��A���ѹ�ϸ��ʣ�ע7��
//E512		R	%	3	��1��B���ѹ�ϸ��ʣ�ע7��
//E513		R	%	3	��1��C���ѹ�ϸ��ʣ�ע7��
//E521		R	%	3	��2��A���ѹ�ϸ��ʣ�ע7��
//E522		R	%	3	��2��B���ѹ�ϸ��ʣ�ע7��
//E523		R	%	3	��2��C���ѹ�ϸ��ʣ�ע7��
//E531		R	%	3	��3��A���ѹ�ϸ��ʣ�ע7��
//E532		R	%	3	��3��B���ѹ�ϸ��ʣ�ע7��
//E533		R	%	3	��3��C���ѹ�ϸ��ʣ�ע7��
/*
  //ʧѹ�ۼƴ����¼�����
  {0xB310,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,(void *)&Event_Cumu.Phase_Loss_Vol[0].Counts,0,4,S_INTU,0,2,1,SPEC_CUMU_EVENT},      //���Լ�A\B\C����ʧѹ����  
  {0xB311,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,(void *)&Event_Cumu.Phase_Loss_Vol[1].Counts,0,4,S_INTU,0,2,1,SPEC_CUMU_EVENT},      //���Լ�A\B\C����ʧѹ���� 
  {0xB312,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,(void *)&Event_Cumu.Phase_Loss_Vol[2].Counts,0,4,S_INTU,0,2,1,SPEC_CUMU_EVENT},      //���Լ�A\B\C����ʧѹ���� 
  {0xB313,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,(void *)&Event_Cumu.Phase_Loss_Vol[3].Counts,0,4,S_INTU,0,2,1,SPEC_CUMU_EVENT},      //���Լ�A\B\C����ʧѹ����
  //ʧѹ�ۼ�ʱ���¼�����
  {0xB320,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,(void *)&Event_Cumu.Phase_Loss_Vol[0].Time,0,4,S_INTU,0,3,1,SPEC_CUMU_EVENT},      //���Լ�A\B\C����ʧѹʧ���ۼ�ʱ�� 
  {0xB321,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,(void *)&Event_Cumu.Phase_Loss_Vol[1].Time,0,4,S_INTU,0,3,1,SPEC_CUMU_EVENT},      //���Լ�A\B\C����ʧѹʧ���ۼ�ʱ�� 
  {0xB322,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,(void *)&Event_Cumu.Phase_Loss_Vol[2].Time,0,4,S_INTU,0,3,1,SPEC_CUMU_EVENT},      //���Լ�A\B\C����ʧѹʧ���ۼ�ʱ�� 
  {0xB323,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,(void *)&Event_Cumu.Phase_Loss_Vol[3].Time,0,4,S_INTU,0,3,1,SPEC_CUMU_EVENT},      //���Լ�A\B\C����ʧѹʧ���ۼ�ʱ�� 
  {0xB324,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,(void *)&Event_Cumu.Phase_Loss_Vol[8].Time,0,4,S_INTU,0,3,1,SPEC_CUMU_EVENT},      //���Լ�A\B\C����ʧѹʧ���ۼ�ʱ��
  //ʧ���ۼ�ʱ��
  {0xB328,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,(void *)&Event_Cumu.Phase_Loss_Cur[0].Time,0,4,S_INTU,0,3,1,SPEC_CUMU_EVENT},      //���Լ�A\B\C����ʧѹʧ���ۼ�ʱ�� 
  {0xB329,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,(void *)&Event_Cumu.Phase_Loss_Cur[1].Time,0,4,S_INTU,0,3,1,SPEC_CUMU_EVENT},      //���Լ�A\B\C����ʧѹʧ���ۼ�ʱ�� 
  {0xB32A,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,(void *)&Event_Cumu.Phase_Loss_Cur[2].Time,0,4,S_INTU,0,3,1,SPEC_CUMU_EVENT},      //���Լ�A\B\C����ʧѹʧ���ۼ�ʱ�� 
  {0xB32B,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,(void *)&Event_Cumu.Phase_Loss_Cur[3].Time,0,4,S_INTU,0,3,1,SPEC_CUMU_EVENT},      //���Լ�A\B\C����ʧѹʧ���ۼ�ʱ��
 */ 
  {0xB330,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_ROM,(void *)0,0,4,S_BCD,0,4,4,SPEC_NO},      //���һ��ʧѹ��ʼʱ��,B330-B333����鳭���ݼ�
  {0xB334,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_ROM,(void *)0,0,4,S_BCD,0,4,5,SPEC_NO},      //���һ��ʧѹ��ʼʱ��,B334-B338������鳭���ݼ�  
  {0xB340,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_ROM,(void *)0,0,4,S_BCD,0,4,4,SPEC_NO},      //���һ��ʧѹ����ʱ��,B340-B343����鳭���ݼ�
  {0xB344,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_ROM,(void *)0,0,4,S_BCD,0,4,5,SPEC_NO},      //���һ��ʧѹ����ʱ��,B344-B348������鳭���ݼ�              
   
//B347		4	����ʱ��	*		ABC�����һ��ʧѹ����ʱ��
  {0xB611,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.Volt.A,0,4,S_INTU,4,2,1,SPEC_NO},  //B611		2		*		A���ѹ
  {0xB612,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.Volt.B,0,4,S_INTU,4,2,1,SPEC_NO},  //B612		2		*		B���ѹ
  {0xB613,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.Volt.C,0,4,S_INTU,4,2,1,SPEC_NO},  //B613		2		*		C���ѹ
//B61F		6		*		��ѹ���ݴ��
  {0xB621,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.Curr.A,0,4,S_INTU,2,2,1,SPEC_NO},//B621	XX.XX	2	A	*		A�����
  {0xB622,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.Curr.B,0,4,S_INTU,2,2,1,SPEC_NO},//B622		2		*		B�����
  {0xB623,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.Curr.C,0,4,S_INTU,2,2,1,SPEC_NO},//B623		2		*		C�����
//B62F		6		*		�������ݴ��
  {0xB630,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.AcPower.Sum,0,4,S_INTU,2,3,1,SPEC_NO},//B630	XX.XXXX	3	kW	*		˲ʱ�й�����
  {0xB631,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.AcPower.A,0,4,S_INTU,2,3,1,SPEC_NO},//B631		3		*		A���й�����
  {0xB632,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.AcPower.B,0,4,S_INTU,2,3,1,SPEC_NO},//B632		3		*		B���й�����
  {0xB633,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.AcPower.C,0,4,S_INTU,2,3,1,SPEC_NO},//B633		3		*		C���й�����
//B63F		12		*		�й��������ݴ��
  {0xB640,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.ReacPower.Sum,0,4,S_INTU,4,2,1,SPEC_NO},//B640	XX.XX	2	kvar	*		˲ʱ�޹�����
  {0xB641,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.ReacPower.A,0,4,S_INTU,4,2,1,SPEC_NO},//B641		2		*		A���޹�����
  {0xB642,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.ReacPower.B,0,4,S_INTU,4,2,1,SPEC_NO},//B642		2		*		B���޹�����
  {0xB643,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.ReacPower.C,0,4,S_INTU,4,2,1,SPEC_NO},//B643		2		*		C���޹�����
//B64F		8		*		�޹��������ݴ��
  {0xB650,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.PFactor.Sum,0,4,S_INTU,3,2,1,SPEC_NO},//B650		2		*		�ܹ�������
  {0xB651,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.PFactor.A,0,4,S_INTU,3,2,1,SPEC_NO},  //B651		2		*		A�๦������
  {0xB652,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.PFactor.B,0,4,S_INTU,3,2,1,SPEC_NO},  //B652	X.XXX	2		*		B�๦������
  {0xB653,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.PFactor.C,0,4,S_INTU,3,2,1,SPEC_NO},  //B653		2		*		C�๦������
//B65F		8		*		�����������ݴ��
  {0xB660,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.Freq.Sum,0,4,S_INTU,4,2,1,SPEC_NO},//B660	XX.XX	2	Hz	*		Ƶ��
  
  {0xB670,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.Angle.Sum,0,4,S_INTU,1,2,1,SPEC_NO},//B670	XXX.X	2	��	*		���
  {0xB671,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.Angle.A,0,4,S_INTU,1,2,1,SPEC_NO},  //B671		2		*		A�����
  {0xB672,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.Angle.B,0,4,S_INTU,1,2,1,SPEC_NO},  //B672		2		*		B�����
  {0xB673,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.Angle.C,0,4,S_INTU,1,2,1,SPEC_NO},  //B673		2		*		C�����
//B67F		8		*		������ݴ��
  {0xB680,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.AppPower.Sum,0,4,S_INTU,2,3,1,SPEC_NO},//B680		3		*		�����ڹ���
  {0xB681,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.AppPower.A,0,4,S_INTU,2,3,1,SPEC_NO},  //B681		3		*		A�����ڹ���
  {0xB682,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.AppPower.B,0,4,S_INTU,2,3,1,SPEC_NO},  //B682	XX.XXXX	3	kVA	*		B�����ڹ���
  {0xB683,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.AppPower.C,0,4,S_INTU,2,3,1,SPEC_NO},  //B683		3		*		C�����ڹ���
//B68F		12		*		���ڹ������ݴ��
//B6FF		62		*		˲ʱ�����ݴ���   
//						������2~9������������С���⣩�ļ���
/*
  {0xB710,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,(void *)0,0,4,S_INTU,0,4,0x1117,SPEC_CUMU_EVENT},	
  {0xB720,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,(void *)0,0,4,S_INTU,0,4,0x1116,SPEC_CUMU_EVENT},
  {0xB730,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,(void *)0,0,4,S_INTU,0,4,0x1114,SPEC_CUMU_EVENT},
  {0xB740,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,(void *)0,0,4,S_INTU,0,4,0x1115,SPEC_CUMU_EVENT},
 */ 
  {0xB7A0,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,(void *)0,0,4,S_INTU,0,4,0x1111,SPEC_PSW_LOCK},
//
  {0xBE70,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.Curr.Sum,0,4,S_INTU,2,2,1,SPEC_NO},//B621	XX.XX	2	A	*		A�����

  {0xC010,DI_EQU_NULL,1,1,PSW_SET_DATE,S_RAM,&Cur_Time1.Week,0,4,S_BCD,0,4,0x1111,SPEC_DATE},//C010	YYMMDDWW	4	��������	*	*	���ڼ��ܴ�                                                                                                                                                                                            
  {0xC011,DI_EQU_NULL,1,1,PSW_SET_TIME,S_RAM,&Cur_Time1.Sec,0,3,S_BCD,0,3,0x1111,SPEC_TIME}, //C011	hhmmss	3	ʱ����	*	*	ʱ��                                                                                       
  //{0xC020,0xC040,1,1,PSW_RD_ONLY,S_RAM,&Meter_Run_Status.Stat1.Byte,0,1,S_BCD,0,1,1,SPEC_NO},//0xc020                                                      //C020	״̬��	1		*		�������״̬��                                                                                   
  //0xc021                                                      //C021		1		*		����״̬��                                                                                             
  //{0xC022,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},      //C030	NNNNNN	3	imp/kWh	*	*	�й����峣��          
  //0xc022                                                      //C022		1		*	*	������״̬��                                                                                           
  //0xc025                                                      //C025		1		*	*	�������߼�¼ģʽ��              
  //0xc026                                                      //C026		1		*	*	�������״̬��2                 
  //0xc027                                                      //C027		1		*	*	�������״̬��3                 
  //0xc028                                                      //C028		1		*	*	�������״̬��4                 
                                                                       
  {0xC030,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,3,S_BCD,0,3,1,SPEC_NO},      //C030	NNNNNN	3	imp/kWh	*	*	�й����峣��          
  {0xC031,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,3,S_BCD,0,3,1,SPEC_NO},      //C031	NNNNNN	3	imp/kvarh	*	*	�޹����峣��        HK_PARA_NUM];
  {0xC032,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,6,S_BIN,0,6,1,SPEC_NO},      //C032	NNNNNNNNNNNN	6		*	*	���                  
  {0xC033,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,6,S_BIN,0,6,1,SPEC_NO},      //C033	NNNNNNNNNNNN 	6		*	*	�û���                
  {0xC034,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,6,S_BIN,0,6,1,SPEC_NO},      //C034	NNNNNNNNNNNN	6		*	*	�豸��                

  {0xC040,0xC020,1,1,PSW_RD_ONLY,S_RAM,&Meter_Run_Status.Meter_Stat1.Byte,0,1,S_BCD,0,1,1,SPEC_NO},//C040		1		*		�������״̬��1        (����¼B1)                                                              
  {0xC041,0xC026,1,0,PSW_RD_ONLY,S_RAM,&Meter_Run_Status.Meter_Stat2.Byte,0,1,S_BCD,0,1,1,SPEC_NO},//C041		1		*		�������״̬��2        (����¼B2)                                                              E
  {0xC042,0xC027,1,0,PSW_RD_ONLY,S_RAM,&Meter_Run_Status.Meter_Stat3.Byte,0,1,S_BCD,0,1,1,SPEC_NO},//C042		1		*		�������״̬��3        (����¼B3)                                                              E
  {0xC043,0xC028,1,0,PSW_RD_ONLY,S_RAM,&Meter_Run_Status.Meter_Stat4.Byte,0,1,S_BCD,0,1,1,SPEC_NO},//C043		1		*		�������״̬��4        (����¼B4)                                                              E
  {0xC044,0xC021,1,1,PSW_RD_ONLY,S_RAM,&Meter_Run_Status.Grid_Stat.Byte,0,1,S_BCD,0,1,1,SPEC_NO},//C044		1		*		����״̬��             ������¼B5��                                                            E
  {0xC045,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,&Meter_Run_Status.Meter_Stat6,0,1,S_BCD,0,1,1,SPEC_NO},//C045		1		*		����״̬��             ������¼B6��                                                            
  {0xC046,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,(void *)0,0,1,S_BCD,0,1,0x1111,SPEC_BAUD},//C045		1		*		����״̬��             ������¼B6��                                                            

//C046		1		*		������״̬��           ������¼B7��                                                            #endif
  {0xC047,DI_EQU_NULL,1,1,PSW_FACTORY_STATUS,S_ROM,(void *)0,0,1,S_BIN,0,1,1,SPEC_NO},      //C047		1		*	*	ģʽ��1(��ȫ)          ������¼B11��                                                           
  {0xC048,DI_EQU_NULL,1,1,PSW_FACTORY_STATUS,S_ROM,(void *)0,0,1,S_BIN,0,1,1,SPEC_NO},      //C048		1		*	*	ģʽ��2(����)          ������¼B12��                                                           
  {0xC049,DI_EQU_NULL,1,1,PSW_FACTORY_STATUS,S_ROM,(void *)0,0,1,S_BIN,0,1,1,SPEC_NO},      //C049		1		*	*	ģʽ��3(����)          ������¼B13��                                                           
  {0xC04A,DI_EQU_NULL,1,1,PSW_SET_MODE45,S_ROM,(void *)0,0,1,S_BIN,0,1,1,SPEC_NO},       //C04A		1		*	*	ģʽ��4(�û�)          ������¼B14��                                                           
  {0xC04B,DI_EQU_NULL,1,1,PSW_SET_MODE45,S_ROM,(void *)0,0,1,S_BIN,0,1,1,SPEC_NO},       //C04B		1		*	*	ģʽ��5(�û�)          ������¼B15��                                                           
  {0xC04C,DI_EQU_NULL,1,1,PSW_SET_MODE678,S_ROM,(void *)0,0,1,S_BIN,0,1,1,SPEC_NO},      //C04C		1		*	*	ģʽ��6(�޹����1)    ������¼B16��                                                            
  {0xC04D,DI_EQU_NULL,1,1,PSW_SET_MODE678,S_ROM,(void *)0,0,1,S_BIN,0,1,1,SPEC_NO},      //C04D		1		*	*	ģʽ��7(�޹����2)    ������¼B16��                                                            
  {0xC04E,0xC025,1,0,PSW_SET_MODE678,S_ROM,(void *)0,0,1,S_BIN,0,1,1,SPEC_NO},      //C04E		1		*	*	ģʽ��8(��������)      ������¼B17��                                                           

  {0xC111,0xC121,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},      //C111	NN	1	��	*	*	�����������                  
  {0xC112,0xC122,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},      //C112	NN	1	��	*	*	����ʱ��                      
  {0xC113,0xC123,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},      //C113	NN	1	��	*	*	ѭ��ʱ��                      
  {0xC114,0xC124,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},      //C114	NN	1		*	*	ѭ����Ŀ��                      
  {0xC115,0xC125,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},      //C115	NN	1		*	*	��ʾ����С��λ��                
  {0xC116,0xC126,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},      //C116	NN	1		*	*	��ʾ���ʣ����������С��λ��    
  {0xC117,0xC127,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,2,S_BCD,0,2,1,SPEC_NO},      //C117	DDhh	2	����	*	*	�Զ���������              
  {0xC118,DI_EQU_NULL,1,0,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},      //C115	NN	1		*	*	��ʾ����С��λ��                
  {0xC119,DI_EQU_NULL,1,0,PSW_SET_PARA,S_ROM,(void *)0,0,4,S_BCD,0,4,1,SPEC_NO},      //C116	NN	1		*	*	��ʾ���ʣ����������С��λ��    
  {0xC11A,DI_EQU_NULL,1,0,PSW_SET_PARA,S_ROM,(void *)0,0,4,S_BCD,0,4,1,SPEC_NO},      //C117	DDhh	2	����	*	*	�Զ���������              

  //{0xC121,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},         //C121	XX	1	��	*	*	�����������                                                                               
  //{0xC122,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},         //C122	��	1	��	*	*	����ʱ��                                                                                   
  //{0xC123,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},         //C123	��	1	��	*	*	ѭ��ʱ��                                                                                   
  //{0xC124,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},         //C124	XX	1		*	*	A����ʾ��Ŀ��                                                                                
  //{0xC125,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},         //C125	NN	1		*	*	����[Э�����ʾ]С��λ[��Χ ��2��3]                                                          
  //{0xC126,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},         //C126	NN	1		*	*	����&����[��ʾ]С��λ                                                                        
//						[��ʾС��λΪ2��3��4��Э��̶�Ϊ4]                                                                 
  //{0xC127,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,2,S_BCD,0,2,1,SPEC_NO},         //C127	DDhh	2	��ʱ	*	*	�Զ���������                                                                           
  {0xC128,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,2,S_BCD,0,2,1,SPEC_NO},         //C128	NNNN	2		*	*	B����ʾ��Ŀ��                                                                              
  {0xC129,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,(void *)&Meter_Self_Test,0,2,S_BCD,0,2,1,SPEC_NO},         //C129	NNNN	2		*		����Լ�״̬��Ϣ�֣���¼19��                                                               
  
  {0xC211,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,2,S_BCD,0,2,1,SPEC_NO},         //C211	NNNN	2	����	*	 	���������                                                                           
  {0xC213,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,12,S_BCD,0,12,1,SPEC_NO},       //C213	4�� XXXX.XX	12	V	*	*	��ѹ�ϸ��ʲ�����ע1��                                                              
  {0xC214,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},         //C214	NN	1		*	*	�û�����1��2��3��ע2��                                                                     
  {0xC215,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},         //C215	NN	1	��	*	*	��բ��ʱ                                                                                   
  {0xC216,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},         //C216	NN	1	��	*	*	��բ��ʱ                                                                                   
  {0xC217,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},         //C217	XX	1				��������������                                                                             
  
  {0xC310,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},         //C310	NN	1		*	*	��1����ʱ����P��12                                                                           
  {0xC311,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},         //C311		1		*	*	��1����ʱ�α���q��8                                                                            
  {0xC312,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},         //C312	��	1		*	*	��1����ʱ����m��14                                                                           
  {0xC313,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},         //C313		1		*	*	��1�׷�����k��8                                                                                
  {0xC314,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},         //C314		1		*	*	��1�׹�����������90                                                                            
  {0xC315,0xC41E,1,0,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},         //C315		1		*	*	��1�������ղ��õ�ʱ�α��                                                                      
  {0xC316,0xC022,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BIN,0,1,1,SPEC_NO},         //C316		1		*	*	��1��������״̬�֣�����¼B8��                                                                  
  
  {0xC321,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,3,S_BCD,0,3,0x1110|MAX_YEAR_PERIODS,SPEC_YEAR_PERIOD},         //C321	MMDDNN	3	����ʱ�α�	*	*	��1ʱ��               ����1�ף�                                                  
  {0xC32F,DI_EQU_NULL,0,0,PSW_SET_PARA,S_ROM,(void *)0,0,3*MAX_YEAR_PERIODS,S_BCD,0,3*MAX_YEAR_PERIODS,1,SPEC_NO},        //C331	hhmmNN	3	ʱ�ַ���	*	*	��1ʱ�α��1ʱ��      ����1�ף�                                                  
  
  {0xC331,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,3,S_BCD,0,3,0x1110|MAX_DATE_PERIODS,SPEC_DATE_PERIOD},        //C331	hhmmNN	3	ʱ�ַ���	*	*	��1ʱ�α��1ʱ��      ����1�ף�                                                  
  {0xC341,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,3,S_BCD,0,3,0x1110|MAX_DATE_PERIODS,SPEC_DATE_PERIOD},        //C341	hhmmNN	3	ʱ�ַ���	*	*	��2ʱ�α��1ʱ��      ����1�ף�                                                  
  {0xC351,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,3,S_BCD,0,3,0x1110|MAX_DATE_PERIODS,SPEC_DATE_PERIOD},        //C351	hhmmNN	3	ʱ�ַ���	*	*	��3ʱ�α��1ʱ��      ����1�ף�                                                  
  {0xC361,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,3,S_BCD,0,3,0x1110|MAX_DATE_PERIODS,SPEC_DATE_PERIOD},        //C361	hhmmNN	3	ʱ�ַ���	*	*	��4ʱ�α��1ʱ��      ����1�ף�                                                  
  {0xC371,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,3,S_BCD,0,3,0x1110|MAX_DATE_PERIODS,SPEC_DATE_PERIOD},        //C37F	hhmmNN	3*14	ʱ�ַ���	*	*	��5ʱ�α��           ����1�ף�                                              
  {0xC381,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,3,S_BCD,0,3,0x1110|MAX_DATE_PERIODS,SPEC_DATE_PERIOD},        //C38F						��6ʱ�α��                                                                                    
  {0xC391,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,3,S_BCD,0,3,0x1110|MAX_DATE_PERIODS,SPEC_DATE_PERIOD},        //C39F	��					��7ʱ�α��                                                                                  
  {0xC3A1,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,3,S_BCD,0,3,0x1110|MAX_DATE_PERIODS,SPEC_DATE_PERIOD},        //C3AF						��8ʱ�α��                                                                                    
  {0xC3B1,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,3,S_BCD,0,3,0x1110|MAX_DATE_PERIODS,SPEC_DATE_PERIOD},        //C3BF	
  {0xC3C1,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,3,S_BCD,0,3,0x1110|MAX_DATE_PERIODS,SPEC_DATE_PERIOD},        //C3CF	
  {0xC3D1,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,3,S_BCD,0,3,0x1110|MAX_DATE_PERIODS,SPEC_DATE_PERIOD},        //C3DF	
  {0xC3E1,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,3,S_BCD,0,3,0x1110|MAX_DATE_PERIODS,SPEC_DATE_PERIOD},        //C3EF	

  {0xC33F,DI_EQU_NULL,0,0,PSW_SET_PARA,S_ROM,(void *)0,0,3*MAX_DATE_PERIODS,S_BCD,0,3*MAX_DATE_PERIODS,1,SPEC_NO},        //C331	hhmmNN	3	ʱ�ַ���	*	*	��1ʱ�α��1ʱ��      ����1�ף�                                                  
  {0xC34F,DI_EQU_NULL,0,0,PSW_SET_PARA,S_ROM,(void *)0,0,3*MAX_DATE_PERIODS,S_BCD,0,3*MAX_DATE_PERIODS,1,SPEC_NO},        //C341	hhmmNN	3	ʱ�ַ���	*	*	��2ʱ�α��1ʱ��      ����1�ף�                                                  
  {0xC35F,DI_EQU_NULL,0,0,PSW_SET_PARA,S_ROM,(void *)0,0,3*MAX_DATE_PERIODS,S_BCD,0,3*MAX_DATE_PERIODS,1,SPEC_NO},        //C351	hhmmNN	3	ʱ�ַ���	*	*	��3ʱ�α��1ʱ��      ����1�ף�                                                  
  {0xC36F,DI_EQU_NULL,0,0,PSW_SET_PARA,S_ROM,(void *)0,0,3*MAX_DATE_PERIODS,S_BCD,0,3*MAX_DATE_PERIODS,1,SPEC_NO},        //C361	hhmmNN	3	ʱ�ַ���	*	*	��4ʱ�α��1ʱ��      ����1�ף�                                                  
  {0xC37F,DI_EQU_NULL,0,0,PSW_SET_PARA,S_ROM,(void *)0,0,3*MAX_DATE_PERIODS,S_BCD,0,3*MAX_DATE_PERIODS,1,SPEC_NO},        //C37F	hhmmNN	3*14	ʱ�ַ���	*	*	��5ʱ�α��           ����1�ף�                                              
  {0xC38F,DI_EQU_NULL,0,0,PSW_SET_PARA,S_ROM,(void *)0,0,3*MAX_DATE_PERIODS,S_BCD,0,3*MAX_DATE_PERIODS,1,SPEC_NO},        //C38F						��6ʱ�α��                                                                                    
  {0xC39F,DI_EQU_NULL,0,0,PSW_SET_PARA,S_ROM,(void *)0,0,3*MAX_DATE_PERIODS,S_BCD,0,3*MAX_DATE_PERIODS,1,SPEC_NO},        //C39F	��					��7ʱ�α��                                                                                  
  {0xC3AF,DI_EQU_NULL,0,0,PSW_SET_PARA,S_ROM,(void *)0,0,3*MAX_DATE_PERIODS,S_BCD,0,3*MAX_DATE_PERIODS,1,SPEC_NO},        //C3AF						��8ʱ�α��                                                                                    
  {0xC3BF,DI_EQU_NULL,0,0,PSW_SET_PARA,S_ROM,(void *)0,0,3*MAX_DATE_PERIODS,S_BCD,0,3*MAX_DATE_PERIODS,1,SPEC_NO},        //C3BF	
  {0xC3CF,DI_EQU_NULL,0,0,PSW_SET_PARA,S_ROM,(void *)0,0,3*MAX_DATE_PERIODS,S_BCD,0,3*MAX_DATE_PERIODS,1,SPEC_NO},        //C3CF	
  {0xC3DF,DI_EQU_NULL,0,0,PSW_SET_PARA,S_ROM,(void *)0,0,3*MAX_DATE_PERIODS,S_BCD,0,3*MAX_DATE_PERIODS,1,SPEC_NO},        //C3DF	
  {0xC3EF,DI_EQU_NULL,0,0,PSW_SET_PARA,S_ROM,(void *)0,0,3*MAX_DATE_PERIODS,S_BCD,0,3*MAX_DATE_PERIODS,1,SPEC_NO},        //C3EF	

  {0xC411,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,3,S_BCD,0,3,0x111D,SPEC_HOLIDAY},//�ڼ������⴦��

  {0xC41F,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,45,S_BCD,0,45,1,SPEC_NO},         //C411	MMDDNN	3		*	*	��1�׵�1����������                                                                       
  //{0xC41E,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},         //C411	MMDDNN	3		*	*	��1�׵�1����������                                                                       
  {0xC42F,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,45,S_BCD,0,45,1,SPEC_NO},                                                                         
  {0xC43F,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,45,S_BCD,0,45,1,SPEC_NO},                                                                            
  {0xC44F,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,45,S_BCD,0,45,1,SPEC_NO},                                                                           
  {0xC45F,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,45,S_BCD,0,45,1,SPEC_NO},                                                                           
  {0xC46F,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,45,S_BCD,0,45,1,SPEC_NO},                                                                             
  
  {0xC510,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,4,S_BCD,0,4,1,SPEC_NO},         //C510	MMDDhhmm	4	����ʱ��	*	*	���ɼ�¼��ʼʱ��                                                                              
  {0xC511,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,2,S_BCD,0,2,1,SPEC_NO},         //C511	Mmmm	2	��	*	*	��������1�����ݼ�¼���                                                                  
  {0xC512,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,2,S_BCD,0,2,1,SPEC_NO},         //C512	��	��	��	*	*	��������2�����ݼ�¼���                                                                  
  {0xC513,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,2,S_BCD,0,2,1,SPEC_NO},         //C513	��	��	��	*	*	��������3�����ݼ�¼���                                                                                                                                        
  {0xC514,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,2,S_BCD,0,2,1,SPEC_NO},         //C514	��	��	��	*	*	��������4�����ݼ�¼���                                                                                                                                             
  {0xC515,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,2,S_BCD,0,2,1,SPEC_NO},         //C515	��	��	��	*	*	��������5�����ݼ�¼���                                                                                                                                    
  {0xC516,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,2,S_BCD,0,2,1,SPEC_NO},         //C516	��	��	��	*	*	��������6�����ݼ�¼���                                                                                                                                          
  
  {0xC51A,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,2,S_BCD,0,2,1,SPEC_NO},         //C51A	NNNN	2	��	*	*	�����Чʱ��                                                                                                                                                        
  {0xC51B,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},         //C51B	NN	1	��	*	*	ʧѹ�ж�ʱ��                                                                                                                                                 
  {0xC51C,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},         //C51C	NN	1	��	*	*	ʧ���ж�ʱ��                                                                                 
  {0xC51D,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},         //C51D	NN	1	��	*	*	�����ж�ʱ��                                                                                                                                            
                                                                             
  {0xC610,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,9,S_BIN,0,9,15,SPEC_NO},        //C610	 NNNNNNNN,NNNNNNNN,NN	9		*	*	��01����ʾ��Ŀ      ��A����                                                
  {0xC620,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,9,S_BIN,0,9,15,SPEC_NO},
  {0xC630,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,9,S_BIN,0,9,15,SPEC_NO},
  {0xC640,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,9,S_BIN,0,9,15,SPEC_NO},
  
  {0xC650,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,9,S_BIN,0,9,15,SPEC_NO},        //C650	 NNNNNNNN,NNNNNNNN,NN	9		*	*	��01����ʾ��Ŀ      ��B����                                                                            
  {0xC660,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,9,S_BIN,0,9,15,SPEC_NO},                                               
  {0xC670,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,9,S_BIN,0,9,15,SPEC_NO},                                               
  {0xC680,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,9,S_BIN,0,9,15,SPEC_NO},                                               
  {0xC690,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,9,S_BIN,0,9,15,SPEC_NO},                                               
  {0xC6A0,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,9,S_BIN,0,9,15,SPEC_NO},                                               
  {0xC6B0,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,9,S_BIN,0,9,15,SPEC_NO},                                               
  {0xC6C0,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,9,S_BIN,0,9,15,SPEC_NO},
  {0xC6D0,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,9,S_BIN,0,9,15,SPEC_NO},
  {0xC6E0,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,9,S_BIN,0,9,15,SPEC_NO},

  {0xC712,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,(void *)Comm_Proto_Version,0,45,S_BCD,0,45,1,SPEC_NO},       //ͨѶ��Լ�汾��(�μ����QG/OKRW013��2005,  QG/OKRW004.7-2004) 
  {0xC713,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},         //������Ƿ��ڹ���״̬��д�˳�����״̬

  {0xC91F,DI_EQU_NULL,0,0,PSW_SET_ENSTART,S_ROM,(void *)0,0,36,S_BCD,0,36,0x1111,SPEC_SET_ENSTART},   //C91F	����ÿ�����ݸ�ʽΪ��	4*9	kWh	*	*	���й���ʼ������  ���ܺ�8���ַ��ʣ�                                                                             
  {0xC92F,DI_EQU_NULL,0,0,PSW_SET_ENSTART,S_ROM,(void *)0,0,36,S_BCD,0,36,0x1111,SPEC_SET_ENSTART},   //C92F	XXXXXX.XX��XXXXX.XXX			*	*	���й���ʼ������                                                           
  {0xC93F,DI_EQU_NULL,0,0,PSW_SET_ENSTART,S_ROM,(void *)0,0,36,S_BCD,0,36,0x1111,SPEC_SET_ENSTART},   //C93F		��		*	*	1�����޹���ʼ������                                                                          
  {0xC94F,DI_EQU_NULL,0,0,PSW_SET_ENSTART,S_ROM,(void *)0,0,36,S_BCD,0,36,0x1111,SPEC_SET_ENSTART},   //C94F				*	*	2�����޹���ʼ������                                                                            
  {0xC95F,DI_EQU_NULL,0,0,PSW_SET_ENSTART,S_ROM,(void *)0,0,36,S_BCD,0,36,0x1111,SPEC_SET_ENSTART},   //C95F		��		*	*	3�����޹���ʼ������                                                                          
  {0xC96F,DI_EQU_NULL,0,0,PSW_SET_ENSTART,S_ROM,(void *)0,0,36,S_BCD,0,36,0x1111,SPEC_SET_ENSTART},   //C96F				*	*	"4�����޹���ʼ������(����������MB3�޳�ʼ�������ã�                                             

  {0xCA10,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,4,S_BCD,0,4,1,SPEC_NO},         //CA10	NN, XX.XXXX	4	%,A	*	*	ʧѹ�ж���ֵ��ע4��                                             
  {0xCA11,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,4,S_BCD,0,4,1,SPEC_NO},         //CA11	NN, XX.XXXX	4	%,A	*	*	ʧ���ж���ֵ��ע5��                                                                
  {0xCA12,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BIN,0,1,1,SPEC_NO},         //CA12	NN	1		*	*	����һ�ź����������(����¼18)                                                               
  {0xCA13,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,5,S_BIN,0,5,1,SPEC_NO},         //CA13	YYMMDDhhmm	5	������ʱ��	*	*	���������л�ʱ��                                                           
  {0xCA14,DI_EQU_NULL,1,1,PSW_SET_PARA,S_RAM,(void *)&Rate_Status,0,2,S_BCD,0,2,1,SPEC_NO},         //CA14	NN,NN	2		*		��ǰ�׷���,ִ�з���(����¼B9)                                                              
  {0xCA15,DI_EQU_NULL,1,1,PSW_FACTORY_STATUS,S_ROM,(void *)0,0,6,S_BIN,0,6,1,SPEC_NO},         //CA15	NN, �� ,NN	6		*	*	�û�Ȩ�޿����֣�����¼B10��                                                          
  {0xCA16,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,3,S_BCD,0,3,1,SPEC_NO},         //CA16	XX.XXXX	3	kW	*	*	�й������޶�                                                                           
  {0xCA17,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,3,S_BCD,0,3,1,SPEC_NO},         //CA17	XX.XXXX	3	kVA	*	*	���ڹ����޶��������ʱû�ã�                                                         
  {0xCA18,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},         //CA18	NN	1		*	*	�������������������ʱû�ã�                                                                 
  {0xCA19,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,3,S_BCD,0,3,1,SPEC_NO},         //�����ж���ֵ
  {0xCA1A,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BIN,0,1,1,SPEC_NO},         //CA1A	NN	1		*	*	ģʽ��9��b0��1�������塢�������ں�ʱ���л�3��1�����b0��0�����塢�������ں�ʱ���л����������
  //{0xCA1B,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},         //CA1B	NN	1		*		�ڿ�״̬1���й��ϣ�0��������b0���ڿ�1��b1���ڿ�2��b2�����ڿ�3��b3�����ڿ�4��                 

  {0xCB10,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},         //CB10	NN	1		*	*	��2����ʱ����P��12                                                                           
  {0xCB11,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},         //CB11		1		*	*	��2����ʱ�α���q��8                                                                            
  {0xCB12,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},         //CB12	��	1		*	*	��2����ʱ����m��14                                                                           
  {0xCB13,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},         //CB13		1		*	*	��2�׷�����k��8                                                                                
  {0xCB14,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},         //CB14		1		*	*	��2�׹�����������90                                                                            
  {0xCB15,0xCC1E,1,0,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},         //CB15		1		*	*	��2�������ղ��õ�ʱ�α��                                                                      
  {0xCB16,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BIN,0,1,1,SPEC_NO},         //CB16		1		*	*	��2��������״̬�֣�����¼B8��                                                                  
  
  {0xCB21,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,3,S_BCD,0,3,0x1110|MAX_YEAR_PERIODS,SPEC_YEAR_PERIOD},         //CB21	MMDDNN	3	����ʱ�α�	*	*	��1ʱ��               ����2�ף�                                                                                                               
  {0xCB2F,DI_EQU_NULL,0,0,PSW_SET_PARA,S_ROM,(void *)0,0,3*MAX_YEAR_PERIODS,S_BCD,0,3*MAX_YEAR_PERIODS,1,SPEC_NO},        //C331	hhmmNN	3	ʱ�ַ���	*	*	��1ʱ�α��1ʱ��      ����1�ף�                                                  
  
  {0xCB31,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,3,S_BCD,0,3,0x1110|MAX_DATE_PERIODS,SPEC_DATE_PERIOD},        //CB31	hhmmNN	3	ʱ�ַ���	*	*	��1ʱ�α��1ʱ��      ����2�ף�                                                  
  {0xCB41,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,3,S_BCD,0,3,0x1110|MAX_DATE_PERIODS,SPEC_DATE_PERIOD},        //CB41	hhmmNN	3	ʱ�ַ���	*	*	��2ʱ�α��1ʱ��      ����2�ף�                                                  
  {0xCB51,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,3,S_BCD,0,3,0x1110|MAX_DATE_PERIODS,SPEC_DATE_PERIOD},        //CB51	hhmmNN	3	ʱ�ַ���	*	*	��3ʱ�α��1ʱ��      ����2�ף�                                                  
  {0xCB61,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,3,S_BCD,0,3,0x1110|MAX_DATE_PERIODS,SPEC_DATE_PERIOD},        //CB61	hhmmNN	3	ʱ�ַ���	*	*	��4ʱ�α��1ʱ��      ����2�ף�                                                  
  {0xCB71,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,3,S_BCD,0,3,0x1110|MAX_DATE_PERIODS,SPEC_DATE_PERIOD},        //CB7F	hhmmNN	3*14	ʱ�ַ���	*	*	��5ʱ�α��           ����2�ף�                                              
  {0xCB81,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,3,S_BCD,0,3,0x1110|MAX_DATE_PERIODS,SPEC_DATE_PERIOD},        //CB8F						��6ʱ�α��                                                                                    
  {0xCB91,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,3,S_BCD,0,3,0x1110|MAX_DATE_PERIODS,SPEC_DATE_PERIOD},        //CB9F	��					��7ʱ�α��                                                                                  
  {0xCBA1,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,3,S_BCD,0,3,0x1110|MAX_DATE_PERIODS,SPEC_DATE_PERIOD},        //CBAF						��8ʱ�α��                                                                                    
  {0xCBB1,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,3,S_BCD,0,3,0x1110|MAX_DATE_PERIODS,SPEC_DATE_PERIOD},        //CBBF	
  {0xCBC1,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,3,S_BCD,0,3,0x1110|MAX_DATE_PERIODS,SPEC_DATE_PERIOD},        //CBCF	
  {0xCBD1,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,3,S_BCD,0,3,0x1110|MAX_DATE_PERIODS,SPEC_DATE_PERIOD},        //CBDF	
  {0xCBE1,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,3,S_BCD,0,3,0x1110|MAX_DATE_PERIODS,SPEC_DATE_PERIOD},        //CBEF                                                                 

  {0xCB3F,DI_EQU_NULL,0,0,PSW_SET_PARA,S_ROM,(void *)0,0,3*MAX_DATE_PERIODS,S_BCD,0,3*MAX_DATE_PERIODS,1,SPEC_NO},        //C331	hhmmNN	3	ʱ�ַ���	*	*	��1ʱ�α��1ʱ��      ����1�ף�                                                  
  {0xCB4F,DI_EQU_NULL,0,0,PSW_SET_PARA,S_ROM,(void *)0,0,3*MAX_DATE_PERIODS,S_BCD,0,3*MAX_DATE_PERIODS,1,SPEC_NO},        //C341	hhmmNN	3	ʱ�ַ���	*	*	��2ʱ�α��1ʱ��      ����1�ף�                                                  
  {0xCB5F,DI_EQU_NULL,0,0,PSW_SET_PARA,S_ROM,(void *)0,0,3*MAX_DATE_PERIODS,S_BCD,0,3*MAX_DATE_PERIODS,1,SPEC_NO},        //C351	hhmmNN	3	ʱ�ַ���	*	*	��3ʱ�α��1ʱ��      ����1�ף�                                                  
  {0xCB6F,DI_EQU_NULL,0,0,PSW_SET_PARA,S_ROM,(void *)0,0,3*MAX_DATE_PERIODS,S_BCD,0,3*MAX_DATE_PERIODS,1,SPEC_NO},        //C361	hhmmNN	3	ʱ�ַ���	*	*	��4ʱ�α��1ʱ��      ����1�ף�                                                  
  {0xCB7F,DI_EQU_NULL,0,0,PSW_SET_PARA,S_ROM,(void *)0,0,3*MAX_DATE_PERIODS,S_BCD,0,3*MAX_DATE_PERIODS,1,SPEC_NO},        //C37F	hhmmNN	3*14	ʱ�ַ���	*	*	��5ʱ�α��           ����1�ף�                                              
  {0xCB8F,DI_EQU_NULL,0,0,PSW_SET_PARA,S_ROM,(void *)0,0,3*MAX_DATE_PERIODS,S_BCD,0,3*MAX_DATE_PERIODS,1,SPEC_NO},        //C38F						��6ʱ�α��                                                                                    
  {0xCB9F,DI_EQU_NULL,0,0,PSW_SET_PARA,S_ROM,(void *)0,0,3*MAX_DATE_PERIODS,S_BCD,0,3*MAX_DATE_PERIODS,1,SPEC_NO},        //C39F	��					��7ʱ�α��                                                                                  
  {0xCBAF,DI_EQU_NULL,0,0,PSW_SET_PARA,S_ROM,(void *)0,0,3*MAX_DATE_PERIODS,S_BCD,0,3*MAX_DATE_PERIODS,1,SPEC_NO},        //C3AF						��8ʱ�α��                                                                                    
  {0xCBBF,DI_EQU_NULL,0,0,PSW_SET_PARA,S_ROM,(void *)0,0,3*MAX_DATE_PERIODS,S_BCD,0,3*MAX_DATE_PERIODS,1,SPEC_NO},        //C3BF	
  {0xCBCF,DI_EQU_NULL,0,0,PSW_SET_PARA,S_ROM,(void *)0,0,3*MAX_DATE_PERIODS,S_BCD,0,3*MAX_DATE_PERIODS,1,SPEC_NO},        //C3CF	
  {0xCBDF,DI_EQU_NULL,0,0,PSW_SET_PARA,S_ROM,(void *)0,0,3*MAX_DATE_PERIODS,S_BCD,0,3*MAX_DATE_PERIODS,1,SPEC_NO},        //C3DF	
  {0xCBEF,DI_EQU_NULL,0,0,PSW_SET_PARA,S_ROM,(void *)0,0,3*MAX_DATE_PERIODS,S_BCD,0,3*MAX_DATE_PERIODS,1,SPEC_NO},        //C3EF	
  
  {0xCC11,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,3,S_BCD,0,3,0x111D,SPEC_HOLIDAY},
  
  {0xCC1F,DI_EQU_NULL,0,0,PSW_SET_PARA,S_ROM,(void *)0,0,45,S_BCD,0,45,1,SPEC_NO},         //CC11	MMDDNN	3		*	*	��2�׵�1����������                                                                       
  //{0xCC1E,DI_EQU_NULL,1,1,PSW_SET_PARA,S_ROM,(void *)0,0,1,S_BCD,0,1,1,SPEC_NO},         //CC11	MMDDNN	3		*	*	��2�׵�1����������                                                                       
  {0xCC2F,DI_EQU_NULL,0,0,PSW_SET_PARA,S_ROM,(void *)0,0,45,S_BCD,0,45,1,SPEC_NO},                                                                         
  {0xCC3F,DI_EQU_NULL,0,0,PSW_SET_PARA,S_ROM,(void *)0,0,45,S_BCD,0,45,1,SPEC_NO},                                                                            
  {0xCC4F,DI_EQU_NULL,0,0,PSW_SET_PARA,S_ROM,(void *)0,0,45,S_BCD,0,45,1,SPEC_NO},                                                                           
  {0xCC5F,DI_EQU_NULL,0,0,PSW_SET_PARA,S_ROM,(void *)0,0,45,S_BCD,0,45,1,SPEC_NO},                                                                           
  {0xCC6F,DI_EQU_NULL,0,0,PSW_SET_PARA,S_ROM,(void *)0,0,45,S_BCD,0,45,1,SPEC_NO}, 

  {0xCDE0,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_ROM,(void *)0,0,1,S_BIN,0,1,0x1111,SPEC_RD_ROM},
  
//14��У�����
  {0xCEE0,DI_EQU_NULL,1,1,PSW_FACTORY_STATUS,S_ROM,(void *)0,0,3,S_BIN,0,3,1,SPEC_NO},
  {0xCEE1,DI_EQU_NULL,1,1,PSW_FACTORY_STATUS,S_ROM,(void *)0,0,1,S_BIN,0,1,1,SPEC_NO},
  {0xCEE2,DI_EQU_NULL,1,1,PSW_FACTORY_STATUS,S_ROM,(void *)0,0,3,S_BIN,0,3,12,SPEC_NO},
  {0xCEEE,DI_EQU_NULL,0,0,PSW_FACTORY_STATUS,S_ROM,(void *)0,0,1,S_BIN,0,1,0x1111,SPEC_ADJ_CLR},

//У���������

  {0xD110,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_ROM,(void *)0,0,4,S_INTU,0,4,0x1116,SPEC_LOAD_DATA},//��������
  
//{0xEF00,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,(void *)0,0,122,S_BCD,0,122,0x1111,SPEC_FREEZE_DATA},//ע��:EF00��EF02����Get_Freeze_Data�����е��������
  {0xEF01,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_ROM,(void *)0,0,127,S_BCD,0,127,1,SPEC_NO},
  //{0xEF02,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,(void *)0,0,144,S_BCD,0,144,0x1111,SPEC_FREEZE_DATA},
  {0xEF03,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_ROM,(void *)0,0,149,S_BCD,0,149,1,SPEC_NO}, 
  
//////////
  ////////////////////��չ�ı�ʾ��//////////////
  //��ʾ������Ҫ�ı���
  {DI_REG_CKC,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&CKC,0,1,S_BCD,0,1,1,SPEC_NO},//����ʧѹ/���࣬DI:DI_LOW_VOL                                                            
  {DI_REG_CSC,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&CSC,0,1,S_BCD,0,1,1,SPEC_NO},//����ʧѹ/���࣬DI:DI_LOW_VOL                                                            
  
  {DI_LOW_VOL,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Meter_Run_Status.Volt_LossMiss.Byte,0,1,S_BCD,0,1,1,SPEC_NO},//����ʧѹ/���࣬DI:DI_LOW_VOL                                                            
  {DI_CURRENT_QUADRANT,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Meter_Run_Status.NegCurr_Qudrant.Byte,0,1,S_BCD,0,1,1,SPEC_NO},//�������������/��������ޣ�DI_CURRENT_QUADRANT                                                            
  {DI_METER_PERIPHERY,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Meter_Run_Status.Key_Event.Byte,0,1,S_BCD,0,1,1,SPEC_NO},//�����̼���/���߶̽�/������λ/���������DI:DI_METER_ PERIPHERY                                                      
  {DI_MODULE_STATUS,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Meter_Run_Status.Comm_Status.Byte,0,1,S_BCD,0,1,1,SPEC_NO},//����ͨ��״̬�֣�DI:DI_MODULE_STATUS
  {DI_POWER_DOWN_TIME,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,(volatile void *)&No_Var[0],0,5,S_BCD,0,5,1,SPEC_NO},

  {DI_METER_ADDR0,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_ROM,(void *)0,0,6,S_BCD,0,6,SPEC_NO},//��һ·���ַ
  {DI_METER_ADDR1,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_ROM,(void *)0,0,6,S_BCD,0,6,SPEC_NO},//�ڶ�·���ַ
  {DI_METER_ADDR2,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_ROM,(void *)0,0,6,S_BCD,0,6,SPEC_NO},//����·���ַ

  {DI_COMM_BAUD0,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_ROM,(void *)0,0,1,S_BCD,0,1,SPEC_NO},//��һ·������
  {DI_COMM_BAUD1,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_ROM,(void *)0,0,1,S_BCD,0,1,SPEC_NO},//�ڶ�·������
  {DI_COMM_BAUD2,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_ROM,(void *)0,0,1,S_BCD,0,1,SPEC_NO},//����·������

  {DI_METER_SOFTWARE_VERSION,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,(volatile void *)&Software_Version,0,5,S_BCD,0,5,1,SPEC_NO},//����汾��
  {DI_METER_SPECIFI,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,(volatile void *)&MeasuSysMode.ParseMode,0,5,S_BCD,0,5,1,SPEC_NO},                                                                                                                           //                                                               E
  //���޹����򣬸�������ʹ�ø�����
  {DI_ACTIVE_DIRECT,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,(volatile void *)&Meter_Run_Status.Ext_Ac_Power_Dir,0,1,S_BCD,0,1,1,SPEC_NO},
  {DI_REACTIVE_DIRECT,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,(volatile void *)&Meter_Run_Status.Ext_Reac_Power_Dir,0,1,S_BCD,0,1,1,SPEC_NO},
  //���Լ������޹�����,��������ʹ�ø�����
  {DI_REACTIVE_ALL,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.ReacPower.Sum,0,4,S_INTU,2,3,1,SPEC_NO},//B630	XX.XXXX	3	kW	*		˲ʱ�й�����
  {DI_REACTIVE_A,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.ReacPower.A,0,4,S_INTU,2,3,1,SPEC_NO},//B631		3		*		A���й�����
  {DI_REACTIVE_B,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.ReacPower.B,0,4,S_INTU,2,3,1,SPEC_NO},//B632		3		*		B���й�����
  {DI_REACTIVE_C,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.ReacPower.C,0,4,S_INTU,2,3,1,SPEC_NO},//B633		3		*		C���й�����
  //���޹���������������ʹ�ø�����
  {DI_ACTIVE_DEMAND,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Demand_Accu.Cur_Pos_Active,0,4,S_INTU,0,3,1,SPEC_NO},//B631		3		*		A���й�����
  {DI_REACTIVE_DEMAND,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Demand_Accu.Cur_Pos_Reactive,0,4,S_INTU,0,3,1,SPEC_NO},//B632		3		*		B���й�����

  {DI_CUR_TIME,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,(volatile void *)&No_Var[0],0,5,S_BCD,0,5,0x1111,SPEC_CUR_TIME},//��ǰʱ�� ��
  {DI_EVENT_TIME,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,(volatile void *)&No_Var[0],0,5,S_BCD,0,5,0x1111,SPEC_EVENT_TIME},//��ǰʱ�� ��

  //A��B��C����AH
  {_DI_TOTAL_AH,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Cur_Energy.Phase_AH[0],0,4,S_INTU,0,4,1,SPEC_NO},//A����AH  
  {_DI_A_AH,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Cur_Energy.Phase_AH[1],0,4,S_INTU,0,4,1,SPEC_NO},//A����AH
  {_DI_B_AH,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Cur_Energy.Phase_AH[2],0,4,S_INTU,0,4,1,SPEC_NO},//B����AH
  {_DI_C_AH,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Cur_Energy.Phase_AH[3],0,4,S_INTU,0,4,1,SPEC_NO},//C����AH
  
  //A��B��C����AH
  {DI_TOTAL_AH,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Cur_Energy.Phase_AH[0],0,4,S_INTU,1,4,1,SPEC_NO},//A����AH  
  {DI_A_AH,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Cur_Energy.Phase_AH[1],0,4,S_INTU,1,4,1,SPEC_NO},//A����AH
  {DI_B_AH,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Cur_Energy.Phase_AH[2],0,4,S_INTU,1,4,1,SPEC_NO},//B����AH
  {DI_C_AH,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Cur_Energy.Phase_AH[3],0,4,S_INTU,1,4,1,SPEC_NO},//C����AH
  
  //A��B��C�����ѹ
  {DI_A_VOL,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.Volt.A,0,4,S_INTU,2,3,1,SPEC_NO},//A���ѹ,2С��
  {DI_B_VOL,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.Volt.B,0,4,S_INTU,2,3,1,SPEC_NO},//B����AH,2С��
  {DI_C_VOL,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.Volt.C,0,4,S_INTU,2,3,1,SPEC_NO},//C����AH,2С��
  {DI_EVENT_VOL,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Event_Vol_Cur.Pub_Vol,0,4,S_INTU,2,3,1,SPEC_NO},//������ѹ���ѹ����ʱ�ĵ�ѹֵ

  {DI_A_VOL_1,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.Volt.A,0,4,S_INTU,3,2,1,SPEC_NO},//A���ѹ,1С��
  {DI_B_VOL_1,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.Volt.B,0,4,S_INTU,3,2,1,SPEC_NO},//B����AH,1С��
  {DI_C_VOL_1,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.Volt.C,0,4,S_INTU,3,2,1,SPEC_NO},//C����AH,1С��

  {DI_A_CUR,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.Curr.A,0,4,S_INTU,0,3,1,SPEC_NO},//B621	XX.XX	2	A	*		A�����
  {DI_B_CUR,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.Curr.B,0,4,S_INTU,0,3,1,SPEC_NO},//B622		2		*		B�����
  {DI_C_CUR,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.Curr.C,0,4,S_INTU,0,3,1,SPEC_NO},//B623		2		*		C�����

  {DI_A_CUR_3,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.Curr.A,0,4,S_INTU,1,3,1,SPEC_NO},//B621	XX.XX	2	A	*		A�����
  {DI_B_CUR_3,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.Curr.B,0,4,S_INTU,1,3,1,SPEC_NO},//B622		2		*		B�����
  {DI_C_CUR_3,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.Curr.C,0,4,S_INTU,1,3,1,SPEC_NO},//B623		2		*		C�����


  {DI_A_ANGLE,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.Angle.A,0,4,S_INTU,0,3,1,SPEC_NO},  //B671  	2		*		A�����
  {DI_B_ANGLE,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.Angle.B,0,4,S_INTU,0,3,1,SPEC_NO},  //B672		2		*		B�����
  {DI_C_ANGLE,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.Angle.C,0,4,S_INTU,0,3,1,SPEC_NO},  //B673		2		*		C�����
  {DI_SUM_ANGLE,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Measu_InstantData_ToPub_PUCK.Angle.Sum,0,4,S_INTU,0,3,1,SPEC_NO},  //�����

//��ǰ����
  {DI_CUR_DEMAND,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Demand_Accu.Cur_Pos_Active,0,4,S_INTU,0,3,1,SPEC_NO},//��ǰ����
  //���һ����������ʽ
  {DI_CLR_DEMAND_WAY,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Clear_Demand_Way,0,1,S_BIN,0,1,1,SPEC_NO},//��������ʽ
  {DI_ADJ_FLAG,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,(volatile void *)&No_Var[0],0,1,S_BIN,0,1,1,SPEC_NO},//У���ʶ��
  //������̱�ʶ��
  {DI_PROG_FLAG0,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Event_Cumu_Data.Prog_Flag.Flag[0],0,1,S_BIN,0,1,1,SPEC_NO},//��̱�ʶ��1
  {DI_PROG_FLAG1,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Event_Cumu_Data.Prog_Flag.Flag[1],0,1,S_BIN,0,1,1,SPEC_NO},//��̱�ʶ��2
  {DI_PROG_TIME,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Prog_Record.Time[0],0,5,S_BCD,0,5,1,SPEC_NO},//�����ʼʱ��
  //���һ�εĴ���ʱ��
  {DI_ERR_TIME,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,Err_Time,0,5,S_BCD,0,5,1,SPEC_NO},//ʱ�Ӿ���ǰ��ʱ������
  {DI_ERR_ROM,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Rom_Err_Flag,0,1,S_BCD,0,1,1,SPEC_NO},//��дROM����
  {DI_NULL_1BYTE,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,(volatile void *)&No_Var[0],0,1,S_BCD,0,1,1,SPEC_NO},//��ʶ�֣�������
  
  {DI_ALL_LOSS_VOL_START_TIME,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&All_Loss_Vol_Time.Start_Time,0,5,S_BCD,0,5,1,SPEC_NO},//��дROM����
  {DI_ALL_LOSS_VOL_END_TIME,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&All_Loss_Vol_Time.End_Time,0,5,S_BCD,0,5,1,SPEC_NO},//��ʶ�֣�������  
  ////////////////////��չ�ı�ʾ��--end//////////////////
};
CONST INT8U BROAD_ADDR_99[]={0x99,0x99,0x99,0x99,0x99,0x99};
CONST INT8U BROAD_ADDR_AA[]={0xAA,0xAA,0xAA,0xAA,0xAA,0xAA};

//��ʼ�����ݴ�����ص��ڴ����
void Init_Data_Trans_Ram_Para()
{
  //�����޸Ļ�����
  mem_set((void *)&Para_Modify,0,sizeof(Para_Modify),(void *)&Para_Modify,sizeof(Para_Modify));
  INIT_STRUCT_VAR(Para_Modify);
  SET_STRUCT_SUM(Para_Modify);
  
  INIT_STRUCT_VAR(User_Authority_Flag);
  User_Authority_Flag.Flag=0;
  SET_STRUCT_SUM(User_Authority_Flag);
  
  INIT_STRUCT_VAR(Clear_Flag);
  Clear_Flag.Flag=CLEAR_END_FLAG;
  SET_STRUCT_SUM(Clear_Flag);
  
  INIT_STRUCT_VAR(PSW_Err_Info);
  PSW_Err_Info.Err_Times=0;
  PSW_Err_Info.Lock_Mins=0;
  SET_STRUCT_SUM(PSW_Err_Info);

  //INIT_STRUCT_VAR(Event_Cumu_Data.Prog_Flag);
  //Event_Cumu_Data.Prog_Flag.Flag[0]=0;
  //Event_Cumu_Data.Prog_Flag.Flag[1]=0;
  //SET_STRUCT_SUM(Prog_Flag);
  INIT_STRUCT_VAR(Time_Modify_Flag);
  Time_Modify_Flag.Var=0;
  
  INIT_STRUCT_VAR(Cur_PSW);
}

//���Э�鴫����ز��������ݵ���ȷ��
void Check_Data_Trans_Data_Avail()
{
  INT8U Re;
  
  //�����־��ȷ��
  Re=1;
  Re&=CHECK_STRUCT_SUM(Clear_Flag);
  Re&=CHECK_STRUCT_VAR(Clear_Flag);
  if(0==Re)
  {
    ASSERT(A_WARNING,0);
    INIT_STRUCT_VAR(Clear_Flag);
    Clear_Flag.Flag=CLEAR_END_FLAG;
    SET_STRUCT_SUM(Clear_Flag);
  }
  
  //��̱�־��ȷ
  /*
  Re=1;
  Re&=CHECK_STRUCT_SUM(Prog_Flag);
  Re&=CHECK_STRUCT_VAR(Prog_Flag);
  if(0==Re)
  {
    ASSERT(A_WARNING,0);
    INIT_STRUCT_VAR(Prog_Flag);
    Prog_Flag.Flag[0]=0;
    Prog_Flag.Flag[1]=0;
    SET_STRUCT_SUM(Prog_Flag);    
  }
  */
  //�û�Ȩ�ޱ�־��ȷ?
  Re=1;
  Re&=CHECK_STRUCT_SUM(User_Authority_Flag);
  Re&=CHECK_STRUCT_VAR(User_Authority_Flag);
  if(0==Re)
  {
    ASSERT(A_WARNING,0);
    INIT_STRUCT_VAR(User_Authority_Flag);
    User_Authority_Flag.Flag=0;
    SET_STRUCT_SUM(User_Authority_Flag);    
  }
  
  //�����޸Ļ����������˱仯?
  Re=1;
  Re&=CHECK_STRUCT_SUM(Para_Modify);
  Re&=CHECK_STRUCT_VAR(Para_Modify);
  Re&=CHECK_STRUCT_SUM(Disp_Digs);
  Re&=CHECK_STRUCT_SUM(Meter_Addr);
  Re&=CHECK_STRUCT_VAR(Cur_PSW);
  Re&=CHECK_STRUCT_SUM(Cur_PSW);
  if(0==Re)
  {
    ASSERT(A_WARNING,0);
    Read_Data_Trans_Para_From_Rom();
  }
}

//��ȡ����ת����ز���
void Read_Data_Trans_Para_From_Rom()
{
  INT8U Err;
  //������ʾС��λ��
  if(Read_Storage_Data(0xC115,(void *)(&Disp_Digs.Energy_Digs),(void *)(&Disp_Digs.Energy_Digs),1,&Err)!=1 || Err!=NO_ERR)
  {
    DEBUG_PRINT(HUCK,DEBUG_0,"Read 0xC125 Para Err");
    Disp_Digs.Energy_Digs=3;
  }    
  Disp_Digs.Energy_Digs=Bcd2Hex_Byte(Disp_Digs.Energy_Digs);
  SET_STRUCT_SUM(Disp_Digs);
  
  //������������ʾС��λ��
  if(Read_Storage_Data(0xC116,(void *)(&Disp_Digs.Power_Digs),(void *)(&Disp_Digs.Power_Digs),1,&Err)!=1 || Err!=NO_ERR)
  {
    DEBUG_PRINT(HUCK,DEBUG_0,"Read 0xC126 Para Err");
    Disp_Digs.Power_Digs=3;
  }
  Disp_Digs.Power_Digs=Bcd2Hex_Byte(Disp_Digs.Power_Digs);
  SET_STRUCT_SUM(Disp_Digs);
  
  //�û�Ȩ�޿�����
  if(Read_Storage_Data(0xCA15,(void *)User_Authority_Ctrl.PSW,(void *)User_Authority_Ctrl.PSW,sizeof(User_Authority_Ctrl.PSW),&Err)!=6 || Err!=NO_ERR)
  {
    DEBUG_PRINT(HUCK,DEBUG_0,"Read 0xCA15 Para Err");
    Read_Def_Para(0xCA15,(void *)User_Authority_Ctrl.PSW,6,(void *)User_Authority_Ctrl.PSW,sizeof(User_Authority_Ctrl.PSW));
  }
  SET_STRUCT_SUM(User_Authority_Ctrl);
  
  //��ȡ����ʱ��ʹ���
  if(Read_Storage_Data(PROG_RECORD,(void *)(&Prog_Record),(void *)(&Prog_Record),sizeof(Prog_Record),&Err)!=sizeof(Prog_Record) || Err!=NO_ERR)
  {
    DEBUG_PRINT(HUCK,DEBUG_0,"Read 0x%lx Para Err",PROG_RECORD);
    Read_Def_Para(PROG_RECORD,(void *)(&Prog_Record),sizeof(Prog_Record),(void *)(&Prog_Record),sizeof(Prog_Record));
  }
  SET_STRUCT_SUM(Prog_Record); 

  //��ȡ������ʱ��ʹ���
  if(Read_Storage_Data(CLR_DEMAND_RECORD,(void *)(&Clr_Demand_Record),(void *)(&Clr_Demand_Record),sizeof(Clr_Demand_Record),&Err)!=sizeof(Clr_Demand_Record) || Err!=NO_ERR)
  {
    DEBUG_PRINT(HUCK,DEBUG_0,"Read 0x%lx Para Err",CLR_DEMAND_RECORD);
    mem_set((void *)(&Clr_Demand_Record),0,sizeof(Clr_Demand_Record),(void *)(&Clr_Demand_Record),sizeof(Clr_Demand_Record));
  }
  SET_STRUCT_SUM(Clr_Demand_Record); 
  
  //�����ַ0-2,�����ַ������Get_DLT645_Data����
  if(Read_Storage_Data(METER_ADDR0,(void *)(Meter_Addr.Addr[0]),(void *)(Meter_Addr.Addr[0]),sizeof(Meter_Addr.Addr[0]),&Err)!=sizeof(Meter_Addr.Addr[0]) || Err!=NO_ERR)
    DEBUG_PRINT(HUCK,DEBUG_0,"Read 0x%lx Para Err",METER_ADDR0); 
  if(Read_Storage_Data(METER_ADDR1,(void *)(Meter_Addr.Addr[1]),(void *)(Meter_Addr.Addr[1]),sizeof(Meter_Addr.Addr[1]),&Err)!=sizeof(Meter_Addr.Addr[1]) || Err!=NO_ERR)
    DEBUG_PRINT(HUCK,DEBUG_0,"Read 0x%lx Para Err",METER_ADDR1);
    SET_STRUCT_SUM(Meter_Addr);
  //��ȡ�������  
  if(Read_Storage_Data(PASSWORD_0,(void *)Cur_PSW.PSW[0],(void *)Cur_PSW.PSW[0],sizeof(Cur_PSW.PSW[0]),&Err)!=sizeof(Cur_PSW.PSW[0]))
      DEBUG_PRINT(HUCK,DEBUG_0,"Read 0x%lx Para Err",PASSWORD_0);
  if(Read_Storage_Data(PASSWORD_1,(void *)Cur_PSW.PSW[1],(void *)Cur_PSW.PSW[1],sizeof(Cur_PSW.PSW[1]),&Err)!=sizeof(Cur_PSW.PSW[1]))
      DEBUG_PRINT(HUCK,DEBUG_0,"Read 0x%lx Para Err",PASSWORD_1);
  if(Read_Storage_Data(PASSWORD_2,(void *)Cur_PSW.PSW[2],(void *)Cur_PSW.PSW[2],sizeof(Cur_PSW.PSW[2]),&Err)!=sizeof(Cur_PSW.PSW[2]))
      DEBUG_PRINT(HUCK,DEBUG_0,"Read 0x%lx Para Err",PASSWORD_2);
  SET_STRUCT_SUM(Cur_PSW);

}

//��ȡ�������ݵ���ʾС��λ��
INT8U Get_Energy_Disp_Digs()
{
  INT8U Re;
  
  Re=CHECK_STRUCT_SUM(Disp_Digs);
  ASSERT(A_WARNING,0!=Re);//�˺�����Get_DLT_645�����е��ã����ɽ���Check_Data_Avail();
  
  if(Disp_Digs.Energy_Digs==3)
    return 3; 
  else
    return 2;
}

//��ȡ�������ݵ���ʾС��λ��
INT8U Get_Power_Disp_Digs()
{
  //INT8U Re;
  
  //������ʾС��λ��ֻ����2��3��4
  if(Disp_Digs.Power_Digs>=2 && Disp_Digs.Power_Digs<=4)
    return Disp_Digs.Power_Digs; 
  else
    return 3;//Ĭ��ȡ3
}

/*
        ��ʶ��1��0λ�����õ����
              1λ������������״̬
                  2λ�����ñ�š��豸�š��û���
                  3λ����������������ڼ������ʱ��
                  4λ������ѭ����ʾ������ѭ����ʾ�����ѭ����ʾ��Ŀ������
                  5λ�����õ��ĵ��ʹ��ʱ��
                  6λ�����ý�����
                  7λ����������
        ��ʶ��2�� 0λ����������
                  1λ������ʱ�β���  //��Ϊ���÷��ʺ�ʱ�β���!!!!!!!!!!
                  2λ�����ø������߼�¼���� 
                  3λ�����÷��ʣ�ʣ���ѱ����޶� //��Ϊʣ������ͱ����޶�!!!!!
                  4λ�����ù����޶�
                  5λ����������բ��ʱ���û�����
                  6λ�����õ�ѹ�ϸ��ʲ���
*/
//����DIֵ���±�̱�ʶ��
void Set_Pog_Flag(PROTO_DI DI)
{
  INT8U Re;
  
  Extend_Set_Prog_Flag(DI);
  
  Re=1;
  Re&=CHECK_STRUCT_SUM(Event_Cumu_Data.Prog_Flag);
  ASSERT(A_WARNING,1==Re);

  if(Read_Event_Status(ID_EVENT_PROG)==0)//��ǰû�б���¼�������Ҳ���ǲ���һ����̵�10����������
  {
    Event_Cumu_Data.Prog_Flag.Flag[0]=0;
    Event_Cumu_Data.Prog_Flag.Flag[1]=0;
    SET_STRUCT_SUM(Event_Cumu_Data.Prog_Flag);
    SET_STRUCT_SUM(Event_Cumu_Data);
    
    Set_Event_Instant(ID_EVENT_PROG);//����¼�
    
    //�����̴��������һ�α��ʱ��
    Prog_Record.Time[0]=Cur_Time1.Min;
    Prog_Record.Time[1]=Cur_Time1.Hour;
    Prog_Record.Time[2]=Cur_Time1.Date;
    Prog_Record.Time[3]=Cur_Time1.Month;
    Prog_Record.Time[4]=Cur_Time1.Year;
    Prog_Record.Counts++;
    SET_STRUCT_SUM(Prog_Record);
    Write_Storage_Data(PROG_RECORD,(void *)&Prog_Record,sizeof(Prog_Record));
  }
  
  if(0xC030==DI || 0xC031==DI)
    SET_BIT(Event_Cumu_Data.Prog_Flag.Flag[0],0);
  else if(0xC316==DI || 0xC022==DI || 0xCB16==DI)//������״̬��
    SET_BIT(Event_Cumu_Data.Prog_Flag.Flag[0],1);
  else if((0xC032<=DI && DI<=0xC034) ||\
          METER_ADDR0==DI || METER_ADDR1==DI || METER_ADDR2==DI)//���ַ����š��豸�š��û���
    SET_BIT(Event_Cumu_Data.Prog_Flag.Flag[0],2);
  else if(0xC111==DI || 0xC112==DI || 0xC121==DI || 0xC122==DI)//�������ںͻ���ʱ��
    SET_BIT(Event_Cumu_Data.Prog_Flag.Flag[0],3);
  else if((0xC113<=DI && DI<=0xC116) || (0xC123<=DI && DI<=0xC126) || 0xC128==DI)//ѭ����ʾ����
    SET_BIT(Event_Cumu_Data.Prog_Flag.Flag[0],4);
  else if(0xB214==DI)//���ʹ��ʱ��
    SET_BIT(Event_Cumu_Data.Prog_Flag.Flag[0],5);
  else if(0xC117==DI || 0xC127==DI)//������
    SET_BIT(Event_Cumu_Data.Prog_Flag.Flag[0],6);
  
  else if(PASSWORD_0==DI || PASSWORD_1==DI || PASSWORD_2==DI)//�޸�����
    SET_BIT(Event_Cumu_Data.Prog_Flag.Flag[1],0);
  else if((DI & 0xFF00)==0xC300 || (DI & 0xFF00)==0xCB00)//���ʺ�ʱ�β���
    SET_BIT(Event_Cumu_Data.Prog_Flag.Flag[1],1);
  else if(0xC510<=DI && DI<=0xC516)
    SET_BIT(Event_Cumu_Data.Prog_Flag.Flag[1],2);//�������߲���
  //else if()//ʣ������ͱ����޶�
    //;
  else if(0xCA16==DI || 0xCA17==DI)//�����޶�
    SET_BIT(Event_Cumu_Data.Prog_Flag.Flag[1],4);
  else if(0xC214<=DI && DI<=0xC216)//����բ��ʱ���û�����
    SET_BIT(Event_Cumu_Data.Prog_Flag.Flag[1],5);
  else if(0xC213==DI)//��ѹ�ϸ���
    SET_BIT(Event_Cumu_Data.Prog_Flag.Flag[1],6);
  else if((DI>=0xC047 && DI<=0xC04E) || 0xC025==DI)
    SET_BIT(Event_Cumu_Data.Prog_Flag.Flag[1],7);
  else       //��������
    SET_BIT(Event_Cumu_Data.Prog_Flag.Flag[0],7);
  
  SET_STRUCT_SUM(Event_Cumu_Data.Prog_Flag);
  SET_STRUCT_SUM(Event_Cumu_Data);  
}

/*****************************************
  ��ԭ�ͣ�
void Set_Para_Modify(PROTO_DI DI)
  �����ܣ�
  ĳ����������ʱ���øú���
��ڲ�����DI,�����ı�ʾ��
 ��ڲ������?
******************************************/
void Set_Para_Modify(PROTO_DI DI)
{
  
  INT8U i,Posi,Re;
  INT8U Task_Num;
  
  Task_Num=Get_Cur_Task_Num();
  
  Re=CHECK_STRUCT_SUM(Para_Modify);
  if(ASSERT(A_WARNING,0!=Re))
    Check_Data_Avail();  
    
  for(i=0;i<Task_Num && i<OS_TASK_NUM;i++)
  {
    if(ASSERT(A_WARNING,Para_Modify.Posi[i]<CHK_PARA_NUM))
      Para_Modify.Posi[i]=0;
    
    Para_Modify.Posi[i]++;//��0���ֽڼ�¼��ǰ�޸Ĳ�����ʾ��Ĵ��λ��
    if(Para_Modify.Posi[i]>=CHK_PARA_NUM)
      Para_Modify.Posi[i]=0;
    
    Posi=Para_Modify.Posi[i];
    if(0!=Para_Modify.Buf[i][Posi])//�ж��Ѿ��޸��˵Ĳ����Ƿ񱻶���ȥ��?
    {
     // DEBUG_PRINT(HUCK,DEBUG_0,"Waitfor Set_Para_Modify %s Task ara_Modify.Buf[%d][%d]==%d",\
                               // Tcb[i].Name,i,Posi,Para_Modify.Buf[i][Posi]);
      SET_STRUCT_SUM(Para_Modify);
      OS_Waitfor_Sec(0==Para_Modify.Buf[i][Posi],5);//�ȴ�5S��λ�ñ�Ϊ0
      
      if(0!=Para_Modify.Buf[i][Posi])
        DEBUG_PRINT(HUCK,DEBUG_0,"Para_Modify.Buf[%d][%d]==%d error",i,Posi,Para_Modify.Buf[i][Posi]);
    }
    Para_Modify.Buf[i][Posi]=DI;
  }
  SET_STRUCT_SUM(Para_Modify);
  Set_Para_Modi_DI(DI);//����������־
  Set_Pog_Flag(DI);//���ñ�̱�־
}

/*****************************************
  ��ԭ�ͣ�
INT8U Check_Para_Modify(PROTO_DI DI)
  �����ܣ�
 �ѯĳ�������Ƿ����޸?ע�ⲻͬ�ĳ���λ�ò�ѯͬһ��������Ҫʹ�ò�ͬ��ID
��ڲ�����
DI,�����ı�ʾ��
 ��ڲ����?��ʾ�������޸�,0��ʾû�з����޸�
******************************************/
INT8U Check_Para_Modify(PROTO_DI DI)
{
  INT8U i,Cur_Task_ID;

  Cur_Task_ID=Get_Cur_Task_ID();
    
  if(ASSERT(A_WARNING,Cur_Task_ID<OS_TASK_NUM))
    return 0;
  
  for(i=1;i<CHK_PARA_NUM;i++)
  {
    if(DI==Para_Modify.Buf[Cur_Task_ID][i])
    {
      Para_Modify.Buf[Cur_Task_ID][i]=0;
      return 1; 
    }
  }
  return 0;
}

//��ȡĳ��DI�����Ĵ洢����,����S_ROM����S_RAM
//ע�⣺ÿ�����ﶼӦ�õ��øú������ҵ��øú�����Ƶ��Ӧ�ýϸߣ���Ϊ
INT8U Get_DLT645_Data_Storage_Type(PROTO_DI DI)
{
  INT16U i;
  //INT16U Index;
  INT8U Spec_Flag;
  
  if((DI & 0xF000) == 0x6000)//��������
  {
    if((DI & 0x0F00)==0)
      return S_RAM;
    else
      return S_ROM;
  }
  else if((DI & 0xF000) == 0x7000 || (DI & 0xF000) == 0x8000)//����������ʱ������
  {
    if((DI & 0x0F00)==0)//��������
    {
      if((DI & 0x000F)==0 || (DI & 0x000F)==Cur_Demand.Rate)//��������Ҳ�в�����Ҫ��ROM�ж�ȡ
        return S_RAM;
      else
        return S_ROM; //���ܺ͵�ǰ���ʵ�������Ҫ��ROM�ж�ȡ
    }
    else
      return S_ROM;    
  }
  
  for(i=0;i<S_NUM(Protocol_Data);i++)
  {
    if(Check_Protocol_Data_Single(i,DI,FOR_EVENT,&Spec_Flag))
    {
      return Protocol_Data[i].Storage;
    }
  }  
  return S_ROM;
}
/*****************************************
  ��ԭ�ͣ�
INT8U Get_Para_Modify(PROTO_DI *pDI)
  �����ܣ�
 ����Ƿ��в��������޸ģ�������޸ģ��򷵻?������*pDIΪ�޸ĵ�DIֵ
��ڲ�����
*pDI,�޸ĵ�DI�ķ���
 ��ڲ����?��ʾ�������޸�,0��ʾû�з����޸�
******************************************/
INT8U Get_Para_Modify(PROTO_DI *pDI)
{
  INT8U i,Posi,Re,Cur_Task_ID;
  INT8U Count=0;

  Cur_Task_ID=Get_Cur_Task_ID();
  
  if(ASSERT(A_WARNING,Cur_Task_ID<OS_TASK_NUM))
    return 0;
  
  Re=CHECK_STRUCT_SUM(Para_Modify);
  if(ASSERT(A_WARNING,0!=Re))
    Check_Data_Avail();
  
  Posi=Para_Modify.Posi[Cur_Task_ID];//��������޸Ĳ����洢λ��
  if(ASSERT(A_WARNING,Posi<CHK_PARA_NUM))
    Posi=0;
  
  Count=0;//��ѯ����������ÿ������ѯCHK_PARA_NUM������ 
  i=(Posi+1)%CHK_PARA_NUM;//��Posi+1��ʼ��ѯ��Posi
  while(Count<=CHK_PARA_NUM)
  {
    if(Para_Modify.Buf[Cur_Task_ID][i]!=0)//!=0��ʾ�ò�����δ����
    {
      *pDI=Para_Modify.Buf[Cur_Task_ID][i];
      if(Cur_Task_ID<OS_TASK_NUM)
        Para_Modify.Buf[Cur_Task_ID][i]=0;
      
      SET_STRUCT_SUM(Para_Modify);
      return 1; 
    }
    Count++;
    i=(i+1)%CHK_PARA_NUM;
  }
  SET_STRUCT_SUM(Para_Modify);
  return 0;//û���ҵ��򷵻�0 
}

//��ȡЭ�����ݵ�����ȼ�
INT8U Get_Protocol_Data_PSW_Flag(PROTO_DI DI)
{
  INT16U i;
//��ʱ���������ó�ʼ��������  
/*  
  //��������������
  if(((DI & 0xF000)==0x9000 || (DI & 0xF000)==0xA000 || (DI & 0xF000)==0xB000) &&\
     ((DI & 0x0C00)==0x0000 || (DI & 0x0C00)==0x0400 || (DI & 0x0C00)==0x0800) &&\
     ((DI & 0x0300)==0x0000 || (DI & 0x0300)==0x0100))
    return PSW_SET_ENSTART;
  
  if((DI & 0xF000)==0x6000 || (DI & 0xF000)==0x7000 || (DI & 0xF000)==0x8000)
    return PSW_SET_ENSTART;

  if((DI & 0xFF00)==0xE700 && ((DI & 0x00F0)>>4)<=0x0D)//��ʷ�������
    return PSW_SET_ENSTART;
*/
  
  for(i=0;i<S_NUM(Protocol_Data);i++)
  {
    if(Protocol_Data[i].Spec_Flag==SPEC_NO)
    {
      if((Protocol_Data[i].DI==DI ||\
         (Protocol_Data[i].Num!=0 && DI>Protocol_Data[i].DI && DI<Protocol_Data[i].DI+Protocol_Data[i].Num)) ||\
         (Protocol_Data[i].DI_Equ!=DI_EQU_NULL &&\
         (Protocol_Data[i].DI_Equ==DI ||\
         (Protocol_Data[i].Num!=0 && DI>Protocol_Data[i].DI_Equ && DI<Protocol_Data[i].DI_Equ+Protocol_Data[i].Num))))
        return Protocol_Data[i].PSW_Flag;
    }
    else
    {
      if(Protocol_Data[i].DI==DI ||\
        (Protocol_Data[i].Num!=0 && DI>Protocol_Data[i].DI && DI<=Protocol_Data[i].DI+Protocol_Data[i].Num-0x1111))
        return Protocol_Data[i].PSW_Flag;
    }
  }
  ASSERT(A_WARNING,0);
  return PSW_NULL_FLAG;
}


//�ж��Ƿ���Դ�Protocol_Data[Index]���DI����
//DI��������0xXXXF��������
//����1��ʾ��Protocol_Data�е�������.DI�����2��ʾ��.DI_EQU���͵�������,0��ʾ��Protocol_Data��û�����������
INT8U Check_Protocol_Data_Block(INT16U Index,PROTO_DI DI,INT8U Data_Flag,INT8U *pSpec_Flag)
{
  INT16U TempDI;
  INT8U Re;
  
  if(SPEC_NO==Protocol_Data[Index].Spec_Flag)
  {
    *pSpec_Flag=SPEC_NO;
    if(((Protocol_Data[Index].DI & 0xFFF0)==(DI & 0xFFF0) &&\
       Protocol_Data[Index].DI_Set_Flag==1))
      return 1;
    else if(Protocol_Data[Index].DI_Equ!=DI_EQU_NULL &&\
            (Protocol_Data[Index].DI_Equ & 0xFFF0)==(DI & 0xFFF0) &&\
            Protocol_Data[Index].DI_Equ_Set_Flag==1)//�ҵ�����������������Set_Flag��1��ʾ��������������ݼ���
    {
      return 2;
    }
    return 0;
  }
  else
  {
    TempDI=(DI & 0xFFF0)+(Protocol_Data[Index].DI & 0x000F);//�����һ��FF����Protocol_Data[Index].DI���������XX
    Re=Check_Protocol_Data_Single(Index,TempDI,Data_Flag,pSpec_Flag);
    if(1==Re)
    {
      *pSpec_Flag=Protocol_Data[Index].Spec_Flag;
      if(Protocol_Data[Index].DI_Set_Flag==1)
        return 1;
    }
    else if(2==Re)
    {
      *pSpec_Flag=Protocol_Data[Index].Spec_Flag;
      if(Protocol_Data[Index].DI_Equ_Set_Flag==1)
        return 2;      
    }
    return 0;
  }
}

//���һ��DI�Ƿ�һ���Ϸ��Ŀ�DI,�ǵĻ�����1����Ļ�����0
INT8U Check_Block_DI(PROTO_DI DI,INT8U Data_Flag)
{
  INT16U i;
  INT8U Spec_Flag;
  
  for(i=0;i<S_NUM(Protocol_Data);i++)
  {
    if(Check_Protocol_Data_Block(i,DI,Data_Flag,&Spec_Flag)>0)
      return 1;
  }
  return 0;
}

//�ж��Ƿ���Դ�Protocol_Data[Index]���DI����
//DIΪ�����ݼ������ݿ�����ݣ�DI��������0xXXFF��������
INT8U Check_Protocol_Data_Set(INT16U Index,PROTO_DI DI,INT8U Data_Flag,INT8U *pSpec_Flag)
{
  INT16U TempDI;
  INT8U Re;
  
  if(SPEC_NO==Protocol_Data[Index].Spec_Flag)
  {
    *pSpec_Flag=SPEC_NO;
    if(((Protocol_Data[Index].DI & 0xFF00)==(DI & 0xFF00) &&\
       Protocol_Data[Index].DI_Set_Flag==1))
      return 1;
    else if(Protocol_Data[Index].DI_Equ!=DI_EQU_NULL &&\
            (Protocol_Data[Index].DI_Equ & 0xFF00)==(DI & 0xFF00) &&\
            Protocol_Data[Index].DI_Equ_Set_Flag==1)//�ҵ�����������������Set_Flag��1��ʾ��������������ݼ���
    {
      return 2;
    }
    return 0;
  }
  else
  {
    *pSpec_Flag=Protocol_Data[Index].Spec_Flag;
    TempDI=(DI & 0xFF00)+(Protocol_Data[Index].DI & 0x00FF);//���������FF����Protocol_Data[Index].DI���������XX
    Re=Check_Protocol_Data_Single(Index,TempDI,Data_Flag,pSpec_Flag);
    if(1==Re)
    {
      if(Protocol_Data[Index].DI_Set_Flag==1)
        return 1;
    }
    else if(2==Re)
    {
      if(Protocol_Data[Index].DI_Equ_Set_Flag==1)
        return 2;      
    }
    return 0;  
  }
}

//��ȡĳ���������ֺ�����������������ݣ����Ƕ���Spec_Flag==SPEC_MULTI_DATA������ 
INT16U Get_Multi_Item_Data(INT8U *pSrc,S_Multi_Data *p,INT8U *pDst,INT8U *pDst_Start,INT16U DstLen)
{
  INT8U i;
  INT16U Src_Off,Src_Len,Dst_Len;
  INT32U Data;
  
  Dst_Len=0;
  for(i=0;i<p->Num;i++)
  {
    Src_Off=p->Data_Item[i].Src_Off;//Դ���ݵ�ƫ��
    Src_Len=p->Data_Item[i].Src_Len;
    if(p->Data_Item[i].Src_Format==S_INTU)
    {
      Data=0;
      mem_cpy(&Data,pSrc+Src_Off,Src_Len,&Data,sizeof(Data));
      if(p->Data_Item[i].Dst_Start!=0)
        Data=Data/Pow_10x(p->Data_Item[i].Dst_Start);
      Hex2Bcd(Data,pDst+Dst_Len,p->Data_Item[i].Dst_Len,pDst_Start,DstLen);
      Dst_Len+=p->Data_Item[i].Dst_Len;
    }  
  }
  return Dst_Len;
}

//��ȡĳ��������������
//Index��ʾDI��ʾ����Protocol_Data�е�����
//pPara��ʾ�������
//pDst��ʾĿ�껺������ʼ��ַ
//pDst_Start��DstLenһ���޶�pDst�ͷ������ݳ��� 
//Data_Flag,FOR_COMM��ʾ�����ṩ��ͨ��,FOR_DISP��ʾ�����ṩ����ʾ
//pErr,����״̬������
//��ȡ�ɹ�������:���س���>0����NO_ERR==*pErr
INT16U Get_DLT645_Single_Data(INT16U Index,PROTO_DI DI,void *pPara,INT8U ParaLen,INT8U *pDst,INT8U *pDst_Start,INT16U DstLen,INT8U Data_Flag,INT8U *pErr)
{
  INT16U Len;
  
  Clr_Ext_Inter_Dog();
  
  OS_Sem_Pend(PUB_BUF_SEM_ID);//���溯���ڲ����õ�Pub_Buf,���ʹ���ź�������
  Len=_Get_DLT645_Single_Data(Index,DI,pPara,ParaLen,pDst,pDst_Start,DstLen,Data_Flag,pErr); 
  OS_Sem_Post(PUB_BUF_SEM_ID);
  return Len;
}

//10��a�η�
INT32U Pow_10x(INT8U a)
{
  INT8U i;
  INT32U Val=1;
  for(i=0;i<a;i++)
    Val=Val*10;
  return Val;
}

//�ж��Ƿ���Դ�Protocol_Data[Index]���DI����
//DIΪ�����ݼ������ݿ������
//*pSec_Flag���ڷ��ظ������ݵ������־
//����1��ʾ��Protocol_Data�е�������.DI�����2��ʾ��.DI_EQU���͵�������,0��ʾ��Protocol_Data��û�����������
INT8U Check_Protocol_Data_Single(INT16U Index,PROTO_DI DI,INT8U Data_Flag,INT8U *pSpec_Flag)
{
  INT16U Num,i;
  INT16U TempDI;
  
  if(SPEC_NO==Protocol_Data[Index].Spec_Flag)
  {
    *pSpec_Flag=SPEC_NO;
    if(Protocol_Data[Index].DI==DI ||\
       (Protocol_Data[Index].Num>1 &&\
       DI>Protocol_Data[Index].DI &&\
       DI<Protocol_Data[Index].DI+Protocol_Data[Index].Num))    
    {
      return 1;
    }
    else if(Protocol_Data[Index].DI_Equ!=DI_EQU_NULL &&\
         (Protocol_Data[Index].DI_Equ==DI ||\
         (Protocol_Data[Index].Num>1 &&\
          DI>Protocol_Data[Index].DI_Equ &&\
          DI<Protocol_Data[Index].DI_Equ+Protocol_Data[Index].Num)))
    {
      return 2;   
    }
    else
      return 0;
  }
  else
  {
    *pSpec_Flag=Protocol_Data[Index].Spec_Flag;
    
    //����������������Ϊ�ͷ�����أ���Ҫ���⴦��
    if(SPEC_RATE==Protocol_Data[Index].Spec_Flag)//������ص����������ַ��ʵ��ܵ�
    {
      if(Multi_Rate_Para.Rates<=MAX_RATES && (Data_Flag & FOR_EVENT)!=FOR_EVENT)
        Num=(Protocol_Data[Index].Num & 0xFFF0)+(Multi_Rate_Para.Rates+1);
      else
        Num=(Protocol_Data[Index].Num & 0xFFF0)+(MAX_RATES+1);
    }
    else
      Num=Protocol_Data[Index].Num;
    
    //�ֱ��ÿ4λ���бȽϣ����ڸ÷�Χ��
    for(i=0;i<16;i+=4)
    {
      TempDI=(DI>>i) & 0x000F;
      if(TempDI==((Protocol_Data[Index].DI>>i) & 0x000F) ||\
         (TempDI>((Protocol_Data[Index].DI>>i) & 0x000F) &&\
         TempDI<(((Protocol_Data[Index].DI+Num)>>i) & 0x000F)))
      {
         continue;
      }
      else
         break;
    }
    if(i==16)
    {
      return 1;  
    }
    else
    {
      //////////////�ж�Equ/////////////////////
      for(i=0;i<16;i+=4)
      {
        TempDI=(DI>>i) & 0x000F;
        if(Protocol_Data[Index].DI_Equ!=DI_EQU_NULL &&\
          TempDI>=((Protocol_Data[Index].DI_Equ>>i) & 0x000F) &&\
          TempDI<(((Protocol_Data[Index].DI_Equ+Num)>>i) & 0x000F))
        {
          continue;     
        }
        else
          break;
      }
      if(i==16)
      {
        return 2;
      }
      else
        return 0;
    }
 }
}

//��ȡĳ��DI����Protocol_Data�е�Index
INT16U Get_Protocol_Data_Index(PROTO_DI DI)
{
  INT8U Spec_Flag;
  INT16U i;
  
  Clr_Ext_Inter_Dog();
  
  for(i=0;i<S_NUM(Protocol_Data);i++)
  {
    if(Check_Protocol_Data_Single(i,DI,FOR_EVENT,&Spec_Flag)>0)
    {
      return i;
    }
  }  
  return NULL_2BYTES;
}

//Index��ʾDI��ʾ����Protocol_Data�е�����
//pPara��ʾ�������
//pDst��ʾĿ�껺������ʼ��ַ
//pDst_Start��DstLenһ���޶�pDst�ͷ������ݳ��� 
//Data_Flag,FOR_COMM��ʾ�����ṩ��ͨ��,FOR_DISP��ʾ�����ṩ����ʾ
//pErr,����״̬������
//��ȡ�ɹ�������:���س���>0����NO_ERR==*pErr
INT16U _Get_DLT645_Single_Data(INT16U Index,PROTO_DI DI,void *pPara,INT8U ParaLen,INT8U *pDst,INT8U *pDst_Start,INT16U DstLen,INT8U Data_Flag,INT8U *pErr)
{
  INT8U *pSrc;
  INT8U Re,Spec_Flag;
  INT16U Len;//Bef_Mon;
  INT32U Data;

  *pErr=NO_ERR;

  //ȡ��Դ����
  if(ASSERT(A_WARNING,Index<S_NUM(Protocol_Data)))
  {
    *pErr=PROTOCOL_DI_ERR; 
    return 0;
  }
  
  //�ҵ������������ڵ�Protocol_Data�е�����
  //������Protocol_Data�е�ĳ��DI�������Ӧ��DI_Equ
  Re=Check_Protocol_Data_Single(Index,DI,Data_Flag,&Spec_Flag);
  if(SPEC_NO==Spec_Flag)//����������
  {
    if(1==Re)
    {
      DI=DI;
    }
    else if(2==Re)
    {
      DI=Protocol_Data[Index].DI+DI-Protocol_Data[Index].DI_Equ;//��DIת��ΪProtocol_Data[i].DI,��������Ķ�ȡ�洢
    }
    else
    {
      *pErr=PROTOCOL_DI_ERR;
      return 0;
    }
  }
  else//����������
  {
    if(Re>0)//��һ������������
    {
      Len=Get_DLT645_Spec_Single_Data(DI,Spec_Flag,pPara,ParaLen,pDst,pDst_Start,DstLen,Data_Flag,pErr);//�ȵ��������������ȡ
      return Len;
    }
    else
    {
      *pErr=PROTOCOL_DI_ERR;//���ǵ���������
      return 0;      
    }
  }
  
  if(S_RAM==Protocol_Data[Index].Storage)//���ݴ洢��RAM��
  {
    pSrc=(INT8U *)(Protocol_Data[Index].pSrc)+Protocol_Data[Index].Src_Off;
    pSrc+=(DI-Protocol_Data[Index].DI)*Protocol_Data[Index].Src_Len;
  }
  else if(S_ROM==Protocol_Data[Index].Storage)//���ݴ洢��EEROM����Flash��
  {
    Len=0;
    //��EEROM����Flash�ж�ȡ���ݣ�ƫ���Ѿ��ڴ洢���γɣ���˲���Ҫpsrc��ֵʱȡƫ��
    Len=Read_Storage_Data(DI,(void *)Pub_Buf,(void *)Pub_Buf,sizeof(Pub_Buf),pErr);
    if(ASSERT(A_WARNING,Len>0))
    {
      if(NO_ERR==*pErr)
        *pErr=PROTOCOL_DATA_ERR;
      return 0;
    }
    pSrc=(INT8U *)Pub_Buf+Protocol_Data[Index].Src_Off;
  }
  else
  {
    ASSERT(A_WARNING,0);
    return 0;
  }
  
  //��������ת��
  if(S_INTU==Protocol_Data[Index].Src_Format)//Դ���ݵ��������޷�������
  {
    Data=0;
    if(S_LEN4==Protocol_Data[Index].Src_Len)
      mem_cpy(&Data,pSrc,4,&Data,sizeof(Data));//Data=*(INT32U *)(pSrc);
    else if(S_LEN2==Protocol_Data[Index].Src_Len)
      mem_cpy(&Data,pSrc,2,&Data,sizeof(Data));//Data=*(INT16U *)(pSrc);
    else if(S_LEN1==Protocol_Data[Index].Src_Len)
      mem_cpy(&Data,pSrc,1,&Data,sizeof(Data));//Data=*(INT8U *)(pSrc);
    else 
    {
      ASSERT(A_WARNING,0);
      return 0;
    }
    
    if((FOR_SRC & Data_Flag)==FOR_SRC)//��ȡԴ����
    {
      if(Protocol_Data[Index].Src_Len!=Protocol_Data[Index].Dst_Len || Protocol_Data[Index].Dst_Len!=4)
        ASSERT(A_WARNING,0);
      mem_cpy(pDst,&Data,Protocol_Data[Index].Dst_Len,pDst_Start,DstLen);      
    }
    else
    {
      Len=Protocol_Data[Index].Dst_Len;//ת��������BCD���ݵĳ���
      Data=Data/Pow_10x(Protocol_Data[Index].Dst_Start);//Դ����/Dst_Start��ʾ��Ҫ��Ŀ������
      Hex2Bcd(Data,(INT8U *)Pub_Buf,Len,(void *)Pub_Buf,sizeof(Pub_Buf));//ת����BCD��
      mem_cpy(pDst,(INT8U *)Pub_Buf,Protocol_Data[Index].Dst_Len,pDst_Start,DstLen);//��ȡ���ݸ��Ƶ�Ŀ�껺����
    }
    return Protocol_Data[Index].Dst_Len;
  }
  else if(S_INTS==Protocol_Data[Index].Src_Format)//Դ�����������з�������
  {
    //Ŀǰ�޸����� 
  }
  else if(S_BCD==Protocol_Data[Index].Src_Format || S_BIN==Protocol_Data[Index].Src_Format)//Դ����������BCD���ͣ���ʾ������и�ʽת��
  {
    mem_cpy(pDst,pSrc+Protocol_Data[Index].Dst_Start,Protocol_Data[Index].Dst_Len,pDst_Start,DstLen);//���Ƶ�Ŀ�껺����  
    return Protocol_Data[Index].Dst_Len;    
  }
  ASSERT(A_WARNING,0);
  return 0;
}

//��һ�����ݿ������,����0x901F֮��,��������0x90FF֮��ģ�������ֻ��DI[0]L=0F
//DI��ʾ���ݱ�ʶ��,��������DI[0]L=0F;
//pDst��ʾĿ�����ݻ�����
//pDst_Start��DstLenһ��綨Ŀ�����ݳ���
INT16U Get_DLT645_Block_Data(PROTO_DI DI,INT8U *pDst,INT8U *pDst_Start,INT16U DstLen,INT8U Data_Flag,INT8U *pErr)
{
  INT16U i,j;
  INT16U Len,TempLen;
  PROTO_DI TempDI;
  INT8U Re,Spec_Flag,Num;
  
  if(ASSERT(A_WARNING,pDst>=pDst_Start &&  pDst<pDst_Start+DstLen))
    return 0;
  
  Len=0;
  Clr_Ext_Inter_Dog();
  
  for(i=0;i<S_NUM(Protocol_Data);i++)
  {
    Re=Check_Protocol_Data_Block(i,DI,Data_Flag,&Spec_Flag);
    if(0<Re)
    {
      if(1==Re)
        TempDI=(DI & 0xFFF0)+(Protocol_Data[i].DI & 0x000F);
      else
        TempDI=(DI & 0xFFF0)+(Protocol_Data[i].DI_Equ & 0x000F);
      
      if(SPEC_RATE==Spec_Flag)//�Ƿ�����ص�������?
      {
        if((FOR_EVENT & Data_Flag)==FOR_EVENT)//�¼���ȡ�����ݶ�������������
          Num=MAX_RATES+1;
        else
        {
          if(Multi_Rate_Para.Rates<=MAX_RATES)
            Num=Multi_Rate_Para.Rates+1;
          else
            Num=MAX_RATES+1;
        }
      }
      else 
        Num=(Protocol_Data[i].Num & 0x000F);
      
      for(j=0;j<Num;j++)
      {
        //��ȡÿ������
        if(pDst+Len+Protocol_Data[i].Src_Len>pDst_Start+DstLen)
        {
          ASSERT(A_WARNING,0);
          *pErr=PROTOCOL_DATA_ERR;
          return 0;
        }
        //OS_TimeDly_Ms(20);//�ó�����������,Refresh_Para_From_Rom���ܽ�������̣�Ҫ�ó�����������
        TempLen=Get_DLT645_Single_Data(i,TempDI+j,(void *)0,0,pDst+Len,pDst_Start,DstLen,Data_Flag,pErr);
        
        if(!(TempLen>0 && *pErr==NO_ERR))
          ASSERT(A_WARNING,0);
        
        if(!(pDst+Len+TempLen<=pDst_Start+DstLen))
        {
          ASSERT(A_WARNING,0);
          *pErr=PROTOCOL_DATA_ERR;
          return 0;
        }
        Len+=TempLen;          
      }
    }
  }
  if(ASSERT(A_WARNING,Len!=0))
    *pErr=PROTOCOL_DI_ERR;
  return Len;  
}

//��һ�����ݿ������,����0x90FF֮��,��������0x900F֮��ģ�����DI[0]H=F0
//DI��ʾ���ݱ�ʶ��
//pDst��ʾĿ�����ݻ�����
//pDst_Start��DstLenһ��綨Ŀ�����ݳ���
//*pFollowFlag��ʾ�Ƿ��к���֡������1��ʾ�У�0��ʾû��
INT16U Get_DLT645_Set_Data(PROTO_DI DI,INT8U *pDst,INT8U *pDst_Start,INT16U DstLen,INT8U Data_Flag,INT8U *pFollowFlag,INT8U *pErr)
{
  INT16U i,Len,TempLen;
  PROTO_DI TempDI;
  
  DECLARE_VAR_TYPE(PROTO_DI,S_PROTO_DI);

  static S_PROTO_DI DI_Bak={CHK_BYTE,0xFFFF,CHK_BYTE};
  static S_Int16U i_Bak={CHK_BYTE,0xFFFF,CHK_BYTE};
  
  *pErr=NO_ERR;
  
  if(DI_Bak.Var!=DI)//��ʾ����Ƕ�ȡһ���µ�������
  {
    i_Bak.Var=0;
    *pFollowFlag=0;
  }
  
  if(ASSERT(A_WARNING,DI!=0xFFFF))//ȷ�����ᴫ��һ��DI=0xFFFF�Ĳ������ú�DI_Bak����Ч��־һ��
  {
    i_Bak.Var=0;
    *pFollowFlag=0;
    *pErr=PROTOCOL_DI_ERR;
    return 0;
  }
  
  Len=0;
  TempLen=0;
  //��������һ֡��û�ж��괦������
  for(i=i_Bak.Var;i<0x0F;i++)//����:��901F->90FF������Ҷ�ȡ
  {
    TempDI=(DI & 0xFF0F)+(i<<4);//����0x901F�������
    if(Check_Block_DI(TempDI,Data_Flag)==1)//���DI�Ƿ���һ����DI��
    {
      TempLen=Get_DLT645_Block_Data(TempDI|0x000F,pDst+Len,pDst_Start,DstLen,Data_Flag,pErr);

      if(TempLen+Len>=MAX_DLT645_DATA_LEN)//���ȳ���199
      {
        DI_Bak.Var=DI;
        i_Bak.Var=i;//����ôε�i
        *pFollowFlag=1;//��ʾ���к���֡
        
        pDst[Len]=0xAA;//��ָ���
        Len++;//��������
        return Len;
      }
      else
      {
        Len+=TempLen;//����û�г���200��������һ�����ݿ�
        pDst[Len]=0xAA;
        Len++;
      }
     }
  }
  DI_Bak.Var=0xFFFF;//û�к���֡�ˣ���DI_Bak�ó�һ����Чֵ���´ν���ú����ͻ���Ϊ�Ǹ���������
  i_Bak.Var=0;
  *pFollowFlag=0;//û�к���֡
  return Len;
}

//PROTO_DI
INT16U _Get_DLT645_Spec_Data(PROTO_DI DI, void *pPara, INT8U ParaLen, void *pDst, void *pDst_Start, INT16U DstLen, INT8U Data_Flag, INT8U *pErr)
{
  //INT8U Err;
  INT16U Len;
  //��Protocol_Data��û���ҵ���������ͬʱҲ�������ݼ������ݿ�,����Ǳ�������
  //if(Single_Flag==0 && (DI & 0x00F0)!=0x00F0 && (DI & 0x000F)!=0x000F)
 // if(Single_Flag==0 && (DI & 0x000F)!=0x000F)  
  //{
    Len = Extend_Get_Proto_Data(DI,pDst,pDst_Start,DstLen,pErr);//��չ��������
    if(Len > 0 || *pErr EQ NO_ERR)
      return Len;
    
    Len=Get_Freeze_Data(DI,pDst,pDst_Start,DstLen,pErr);//��ΪEF00��EF02��������������Ҫ����_Get_DLT645_Data������Ҫ��������
    if(Len>0 || *pErr EQ NO_ERR)
      return Len;
    
    Len=Get_MultiTimes_Event_Data(DI,pDst,pDst_Start,DstLen,pErr);
    if(Len>0 || *pErr EQ NO_ERR)
      return Len;

    Len = Get_Cumu0_Event_Data(DI,pDst,pDst_Start,DstLen,pErr);
    if(Len > 0 || *pErr EQ NO_ERR)
      return Len;

    *pErr=PROTOCOL_DI_ERR;//��ʾ����������
    return 0;

  //}  
  
}

//INT16U Get_Protocol_Single_Data_Index
//��ȡ645����
//DI,645Э���ʶ
//pPara,��ڲ���,����֡��������
//pDst,Ŀ�����ݻ�����
//pDst_Start��DstLenһ���޶�pDst�Ͷ������ݳ��ȵķ�Χ
//DataFlag,FOR_DISP��ʾ��ȡ�������Ǹ���ʾ�ã�FOR_DISP��ʾ����ʾ��
//����ʱ��ȡ�������ݳ���
INT16U _Get_DLT645_Normal_Data(PROTO_DI DI,void *pPara,INT8U ParaLen,INT8U *pDst,INT8U *pDst_Start,INT16U DstLen,INT8U Data_Flag,INT8U *pFollowFlag,INT8U *pErr)
{
  INT8U Single_Flag,Spec_Flag;
  INT16U Len,i;

  *pErr=NO_ERR;
  *pFollowFlag=0;
  
  if(ASSERT(A_WARNING,(DI & 0xF000)!=0xF000))
  {
    *pErr=PROTOCOL_DI_ERR;
    return 0;
  }
  //���������ʾ����һ������������
  
  Single_Flag=0;//�Ƿ��Ǹ���������������������ݼ�֮��
  Len=0;
  for(i=0;i<S_NUM(Protocol_Data);i++)
  {
    if(Check_Protocol_Data_Single(i,DI,Data_Flag,&Spec_Flag)>0)
    {
      Single_Flag=1;
      break;
    }
  }
  
  if(Single_Flag==1)//��������������
  {
    Len=Get_DLT645_Single_Data(i,DI,pPara,ParaLen,pDst,pDst_Start,DstLen,Data_Flag,pErr);
  }
  else
  {
    if((DI & 0x00F0)==0x00F0)//��ȡ���ݼ�
      Len=Get_DLT645_Set_Data(DI,pDst,pDst_Start,DstLen,Data_Flag,pFollowFlag,pErr);
    else if((DI & 0x000F)==0x000F)//��ȡ���ݿ�
      Len=Get_DLT645_Block_Data(DI,pDst,pDst_Start,DstLen,Data_Flag,pErr);
    else//���ݱ�ʶ��
    { 
      *pErr=PROTOCOL_DI_ERR;
      Len=0;
    }
  }
  
  if(ASSERT(A_WARNING,Len>0))
  {
    if(NO_ERR==*pErr)
      *pErr=PROTOCOL_DATA_ERR;
    return 0;
  }
  else
  {
    *pErr=NO_ERR;
    return Len;
  }
}

INT16U _Get_DLT645_Data(PROTO_DI DI,void *pPara,INT8U ParaLen,INT8U *pDst,INT8U *pDst_Start,INT16U DstLen,INT8U Data_Flag,INT8U *pFollowFlag,INT8U *pErr)
{
  INT8U FollowFlag;
  INT16U Len;
  
  *pErr=NO_ERR;
  
  Len = _Get_DLT645_Spec_Data(DI,pPara,ParaLen,pDst,pDst_Start,DstLen,Data_Flag,pErr);
  if(Len > 0 || *pErr EQ NO_ERR)
    return Len;
  
  Len = _Get_DLT645_Normal_Data(DI,pPara,ParaLen,pDst,pDst_Start,DstLen,Data_Flag,&FollowFlag,pErr);
  if(ASSERT(A_WARNING,Len>0))
  {
    if(NO_ERR==*pErr)
      *pErr=PROTOCOL_DATA_ERR;
    return 0;
  }
  else
  {
    *pErr=NO_ERR;
    return Len;
  }  
  
}

//��ȡ645���ݵļ򵥺���
INT16U Get_DLT645_Data(PROTO_DI DI,INT8U *pDst,INT8U *pDst_Start,INT16U DstLen,INT8U *pErr)
{
  INT8U FollowFlag;
  INT16U Len;
  
  Len = _Get_DLT645_Spec_Data(DI,(void *)0,0,pDst,pDst_Start,DstLen,FOR_COMM,pErr);
  if(Len > 0 || *pErr EQ NO_ERR)
    return Len;
  
  Len = _Get_DLT645_Data(DI,(void *)0,0,pDst,pDst_Start,DstLen,FOR_COMM,&FollowFlag,pErr);
  if(ASSERT(A_WARNING,Len>0))
  {
    if(NO_ERR==*pErr)
      *pErr=PROTOCOL_DATA_ERR;
    return 0;
  }
  else
  {
    *pErr=NO_ERR;
    return Len;
  }
}

//��ȡ645���ݵļ򵥺���,ר�ṩ����ʵ�������
INT16U Get_DLT645_Data_For_Disp(PROTO_DI DI,INT8U *pDst,INT8U *pDst_Start,INT16U DstLen)
{
  INT8U FollowFlag;
  INT16U Len;
  INT8U Err;
  
  Len=_Get_DLT645_Data(DI,(void *)0,0,pDst,pDst_Start,DstLen,FOR_DISP,&FollowFlag,&Err);
  return Len;
  /*
  if(ASSERT(A_WARNING,Len>0))
    return 0;
  else
    return Len;
  */
}

//#define PROTOCOL_DLT645 0
//Protocol_Type��PROTOCOL_DLT645��
//DI���ݱ�ʶ��
//pDstĿ�껺����
//pDst_Start��DstLenһ���޶�pDst�ͷ��س���(Len):
//ASSERT(A_WARNING,pDst>=pDst_Start && pDst+Len<=pDst_Start+DstLen)
//Data_Flag��ʾ�ú����ṩ��ͨ�Ż�����ʾ,FOR_DISP��ʾ����ʾ��FOR_COMM��ʾ��ͨ��
//*pFollowFlag��ʾ�Ƿ��к���֡,*pFollowFlag==1��ʾ�к���֡
//�к���֡������£����Ҫ��ȡ����֡������һ�ε��øú������ɣ�DI������ǰ֡��ͬ��DI
INT16U Get_Meter_Protocol_Data(INT8U Protocol_Type,PROTO_DI DI,INT8U *pDst,INT8U *pDst_Start,INT16U DstLen,INT8U Data_Flag,INT8U *pFollowFlag)
{
  INT16U Len;//���س���
  INT8U Err;
  
  if(PROTOCOL_DLT645==Protocol_Type)
  {
    Len=_Get_DLT645_Data(DI,(S_HEX_Time *)&Cur_Time0,0,pDst,pDst_Start,DstLen,Data_Flag,pFollowFlag,&Err);
    if(ASSERT(A_WARNING,pDst>=pDst_Start && pDst+Len<=pDst_Start+DstLen))
      return 0;
    
    if(ASSERT(A_WARNING,Len>0 && NO_ERR==Err))
      return 0;
    
    return Len;
  }
  else
  {
    ASSERT(A_WARNING,0);
    return 0;
  }
}

//����յ���DLT645���ݵĳ����Ƿ�Ϸ�
INT8U Check_DLT645_Data_Len(INT8U Ctrl_Code,INT8U *pSrc,INT8U SrcLen)
{
  if(Ctrl_Code==C_READ_DATA && SrcLen>=2)//һ�������ǣ����ֽڵı�ʶ�����Ƕ�ȡ����ʱ���ĸ��������ǣ��ֽ�
    return NO_ERR;
  else if(Ctrl_Code==C_READ_FOLLOW_DATA)
    return NO_ERR;
  if(Ctrl_Code==C_SET_DATA && SrcLen>=2)
    return NO_ERR;
  else if(Ctrl_Code==C_ADJUST_METER && SrcLen>2)
    return NO_ERR;
  else if(Ctrl_Code==C_ADJUST_TIME)
  {
    if(Mode_Word.Mode[0].Bit.Bit4==1 && SrcLen==0x0A)//�㲥Уʱ
      return NO_ERR;
    else if(SrcLen==0x06)
      return NO_ERR;
  }
  else if(Ctrl_Code==C_SET_ADDR && SrcLen==0x06)//д�豸��ַ
    return NO_ERR;
  else if(Ctrl_Code==C_SET_COM_BAUD && SrcLen==0x01)//д������
    return NO_ERR;
  else if(Ctrl_Code==C_SET_PSW && SrcLen==0x08)//�޸�����
    return NO_ERR;
  else if(Ctrl_Code==C_CLR_ALL && (SrcLen==0x04 || SrcLen==0x03))//����������߶���
    return NO_ERR;
  else if(Ctrl_Code==C_CLR_DEMAND && SrcLen==0x04)//������
    return NO_ERR;
  else if(Ctrl_Code==C_CLR_EVENT && SrcLen==0x04)//�����(�¼�)
    return NO_ERR;
  else if(Ctrl_Code==C_CLR_STAT && SrcLen==0x04)//���ѹ�ϸ���(ͳ��)
    return NO_ERR;
  
  return PROTOCOL_DATA_ERR;
}




//����ĳDI������
//DI,���ݱ�ʶ
//pSrc,Դ������ʼָ��
//SrcLen,Դ���ݳ���
INT8U Set_DI_Data_Proc(INT16U Index,PROTO_DI DI,INT8U *pSrc,INT8U SrcLen)
{
  INT8U Re,Spec_Flag;
  
  //��Protocol_Data�в��ҵ�����
  //for(i=0;i<S_NUM(Protocol_Data);i++)
  Re=Check_Protocol_Data_Single(Index,DI,FOR_COMM,&Spec_Flag);
  if(1==Re)
  {
    if(Protocol_Data[Index].Src_Format==S_BCD)//�ҵ�����Ҹ���Ҫ����BCD��ʽ
    {
      if(!Check_BCD_Data(pSrc,SrcLen))//��������������BCD?
        return PROTOCOL_DATA_ERR;
    }
  }
  else if(2==Re)
  {
    DI=Protocol_Data[Index].DI+DI-Protocol_Data[Index].DI_Equ;//��DIת��ΪDI_Equ,��ʹ���洢��Ч
    if(Protocol_Data[Index].Src_Format==S_BCD)//�ҵ�����Ҹ���Ҫ����BCD��ʽ
    {
      if(!Check_BCD_Data(pSrc,SrcLen))
        return PROTOCOL_DATA_ERR;
    }
  }
  else
    return PROTOCOL_DI_ERR;
  
  Re=Write_Storage_Data(DI,pSrc,SrcLen);
  return Re;
}

//����������ݵĸ�ʽ����ȷ����1�����󷵻�0
INT8U Set_Data_Format_Check(INT16U Index,PROTO_DI DI,INT8U *pSrc,INT8U SrcLen)
{
  if(DI==0xC310 || DI==0xCB10)//��ʱ����
  {
    if(Bcd2Hex_Byte(*pSrc)>MAX_YEAR_PERIODS)
    {
      SET_BIT(Sys_Run_Flag.Err_Flag,4);
      return 0;
    }
  }
  else if(DI==0xC312 || DI==0xCB12)//��ʱ������
  {
    if(Bcd2Hex_Byte(*pSrc)>MAX_DATE_PERIODS)
    {
      SET_BIT(Sys_Run_Flag.Err_Flag,5);  
      return 0;
    }
  }
  else if(DI==0xC313 || DI==0xCB13)//��������
  {
    if(Bcd2Hex_Byte(*pSrc)>MAX_RATES)
    {
      SET_BIT(Sys_Run_Flag.Err_Flag,6);
      return 0;
    }
  }
  return 1;
  
}

//�������ݴ���
INT8U Set_Data_Proc(INT8U *pSrc,INT8U SrcLen)
{
  INT8U Re;
  PROTO_DI DI;
  INT16U i;
  INT8U Single_Flag,Spec_Flag;
 
  DI=0;
  mem_cpy(&DI,pSrc,2,&DI,sizeof(DI));//DI=*(INT16U *)pSrc;
  if(SrcLen>6)//������ʶ������������6�ֽ�
  {
    Single_Flag=0;//�Ƿ��Ǹ���������������������ݼ�֮��
    for(i=0;i<S_NUM(Protocol_Data);i++)
    {
      if(Check_Protocol_Data_Single(i,DI,FOR_COMM,&Spec_Flag)>0)
      {
        if(Protocol_Data[i].PSW_Flag==PSW_RD_ONLY)//�����ݲ���д
          return PROTOCOL_DI_ERR;
        
        Single_Flag=1;
        break;
      }
    }
  
    if(Single_Flag==0)//����������������
    {
      SET_BIT(Sys_Run_Flag.Err_Flag,1);//���ݱ�ʶ��
      return PROTOCOL_DI_ERR;
    }
    
    Re=Set_Data_Format_Check(i,DI,pSrc+6,SrcLen-6);//������ݸ�ʽ��
    if(0==Re)
      return PROTOCOL_DATA_ERR;
    
    //DI������֮����6�ֽڵ�����Ŷ
    if(SPEC_NO==Spec_Flag)
      Re=Set_DI_Data_Proc(i,DI,pSrc+6,SrcLen-6);//�����������
    else
      Re=Set_Spec_Data_Proc(DI,Spec_Flag,pSrc+6,SrcLen-6);

    if(NO_ERR==Re)
      Set_Para_Modify(DI);
    else
    {
      SET_BIT(Sys_Run_Flag.Err_Flag,0);//�Ƿ�����
    }
    return Re;
  }
  else
  {
    SET_BIT(Sys_Run_Flag.Err_Flag,0);//�Ƿ�����
    return PROTOCOL_DATA_ERR;
  }
}

//У����
INT8U Adjust_Meter_Proc(INT8U *pSrc,INT8U SrcLen)
{
  return NO_ERR;
}

INT8U Adj_Time(S_BCD_Time *pTime)
{
    //�����¼�ʱ��
    mem_cpy((void *)&Event_Cumu_Data.Time, (void *)&Cur_Time1, sizeof(Cur_Time1),\
            (void *)&Event_Cumu_Data.Time, sizeof(Event_Cumu_Data.Time));
    SET_STRUCT_SUM(Event_Cumu_Data);
    
    if(Set_Time_EXT_INTER_Ram_RTC(pTime))
    {
      //Set_Event_Instant(ID_EVENT_ADJUST_TIME);//Уʱ��ʼ
      //OS_Waitfor_Sec(Read_Event_Status(ID_EVENT_ADJUST_TIME)==1,5);//�ȴ�5s��û�д������򱨶��Դ���
      //if(Read_Event_Status(ID_EVENT_ADJUST_TIME)!=1)
        //ASSERT(A_WARNING,0);
      Event_MultiTimes_Proc(ID_EVENT_ADJUST_TIME,EVENT_OCCUR,EVENT_REAL);
      
      //�����¼�ʱ��
      mem_cpy((void *)&Event_Cumu_Data.Time, (void *)&Cur_Time1, sizeof(Cur_Time1),\
              (void *)&Event_Cumu_Data.Time, sizeof(Event_Cumu_Data.Time));
      SET_STRUCT_SUM(Event_Cumu_Data);
      
      //Clr_Event_Instant(ID_EVENT_ADJUST_TIME);//Уʱ����
      Event_MultiTimes_Proc(ID_EVENT_ADJUST_TIME,EVENT_END,EVENT_REAL);
      
      Time_Modify_Flag.Var = 1;
      return NO_ERR;
    }
    
    return ADJ_TIME_ERR;
  
}

//�㲥Уʱ����
INT8U Adjust_Time_Proc(INT8U *pSrc,INT8U SrcLen)
{
  S_BCD_Time TempTime;
  S_HEX_Time TempTime1,Temp_Cur_Time;
  static S_BCD_Time Last_Adj_Time={0}; //�ϴ�Уʱʱ��  
  INT8U y,m,d;//���ڼ�������
  INT8U Re;
  
  if(Last_Adj_Time.Date EQ Cur_Time1.Date &&\
     Last_Adj_Time.Month EQ Cur_Time1.Month &&\
     Last_Adj_Time.Year EQ Cur_Time1.Year) //�������Ѿ�Уʱһ����
  {
    DEBUG_PRINT(HUCK,DEBUG_0,"Adj Time >1 times today!");
    return ADJ_TIME_ERR;
  }
  if(Mode_Word.Mode[0].Bit.Bit4==1)//��Ҫ����,ǰ3���ֽ�������ȼ�������
    pSrc=pSrc+4;;
  //else
  {
    TempTime.Sec=*pSrc;
    TempTime.Min=*(pSrc+1);
    TempTime.Hour=*(pSrc+2);
    TempTime.Date=*(pSrc+3);
    TempTime.Month=*(pSrc+4);
    TempTime.Year=*(pSrc+5);
    y=Bcd2Hex_Byte(TempTime.Year); 
    m=Bcd2Hex_Byte(TempTime.Month);
    d=Bcd2Hex_Byte(TempTime.Date);
    TempTime.Week=Week(y,m,d);
    SET_STRUCT_SUM(TempTime);
    if(Check_BCD_Time(&TempTime))
    {
      Convert_BCD_2_HEX_Time(&TempTime,&TempTime1);
      //��ǰʱ�䳬����ǰʱ�������10���ӣ��򷵻�ʧ��
      Time_Inc((S_HEX_Time *)&Cur_Time0,10,UNIT_MIN,&Temp_Cur_Time);//��ǰʱ�������10����
      if(Cmp_Time(&TempTime1,&Temp_Cur_Time)==TIME_AFT)
      {
        ASSERT(A_WARNING,0);
        return ADJ_TIME_ERR;
      }
      
      Time_Dec((S_HEX_Time *)&Cur_Time0,10,UNIT_MIN,&Temp_Cur_Time);
      if(Cmp_Time(&TempTime1,&Temp_Cur_Time)==TIME_BEF)
      {
        ASSERT(A_WARNING,0);
        return ADJ_TIME_ERR;
      }
      
      //������ͬһ���ڲſ�Уʱ
      if(!(TempTime.Date==Cur_Time1.Date && TempTime.Month == Cur_Time1.Month && TempTime.Year == Cur_Time1.Year))
      {
        DEBUG_PRINT(HUCK,DEBUG_0,"Adj Time must be the in same day!");
        return ADJ_TIME_ERR;
      }
      //Extend_Set_Prog_Flag(DI_BROAD_ADJ_TIME);//�㲥Уʱ��̼�¼
      
      Re = Adj_Time(&TempTime);
      if(Re EQ NO_ERR)
       mem_cpy((void *)&Last_Adj_Time,(void *)&Cur_Time1,sizeof(Cur_Time1),(void *)&Last_Adj_Time,sizeof(Last_Adj_Time));
      ASSERT(A_WARNING,Re==NO_ERR);
      return Re;
    }
  }
  ASSERT(A_WARNING,0);
  return ADJ_TIME_ERR;  
}

//д�豸��ַ����
//Ch��ʾ���ݵ�ͨ��
//pSrc,������ʼ��ַ
//SrcLen,���ݳ���
INT8U Set_MeterAddr_Proc(INT8U Ch,INT8U *pSrc,INT8U SrcLen)
{
  INT8U Re;
  
  if(Check_Set_ADDR_Key()==0)
    return SET_ADDR_ERR;
  
  if(CH_RS485_1==Ch || CH_IRAD==Ch)//��һ·485���ñ��ַ
  {
    Re=Write_Storage_Data(METER_ADDR0,pSrc,6);
    if(NO_ERR==Re)
      Set_Para_Modify(DI_METER_ADDR0);
  }
  else if(CH_RS485_2==Ch)//�ڶ�·485���ñ��ַ
  {
    Re=Write_Storage_Data(METER_ADDR1,pSrc,6);
    if(NO_ERR==Re)
      Set_Para_Modify(DI_METER_ADDR1);
  }

  return Re;
}

//��ͨ�Ų����ʴ���
INT8U Set_CommBaud_Proc(INT8U Ch,INT8U *pSrc,INT8U SrcLen)
{
  if(Ch==CH_RS485_1)//��һ·485
  {
    Write_Storage_Data(DI_COMM_BAUD0,pSrc,1);
    Set_Para_Modify(DI_COMM_BAUD0);
    return NO_ERR;
  }
  else if(Ch==CH_RS485_2)//��2·485
  {
    Write_Storage_Data(DI_COMM_BAUD1,pSrc,1);
    Set_Para_Modify(DI_COMM_BAUD1); 
    return NO_ERR;
  }
  return WR_STORAGE_DATA_AUTH_ERR;  
}

//�޸����봦��
INT8U Set_PSW_Proc(INT8U *pSrc,INT8U SrcLen,INT8U *pDst,INT8U *pDst_Start,INT16U DstLen)
{
  INT8U Level;
  INT8U Re;
  STORA_DI DI;
  
  Level=pSrc[4];//��������ļ���
  if(Level<3)
  {
    if(Level==0)
      DI=PASSWORD_0;
    else if(Level==1)
      DI=PASSWORD_1;
    else if(Level==2)
      DI=PASSWORD_2;
    else
      return SET_PSW_ERR;
    
    mem_cpy((void *)Cur_PSW.PSW[Level],pSrc+5,3,(void *)Cur_PSW.PSW[Level],sizeof(Cur_PSW.PSW[Level]));
    SET_STRUCT_SUM(Cur_PSW);
    Re=Write_Storage_Data(DI,(void *)Cur_PSW.PSW[Level],sizeof(Cur_PSW.PSW[Level]));

    if(NO_ERR==Re)
    {
      Set_Para_Modify(DI);
      mem_cpy(pDst,pSrc+4,4,pDst_Start,DstLen);
      return NO_ERR;
    }
    else
      ASSERT(A_WARNING,0);
  }
  return SET_PSW_ERR;
  
}

//�������崦��
INT8U Clear_AllData_Proc(INT8U *pSrc,INT8U SrcLen)
{
  Clear_Energy_Data();
  Clear_All_Demand_Data();
  Clear_VolStat_Data();
  Clear_Event_Data();
  return NO_ERR;  
}

//����������
INT8U Clear_Demand_Proc(INT8U *pSrc,INT8U SrcLen)
{
  Clear_Cur_Demand_Data();
  return NO_ERR;  
}

//����̴���(��ʱ��)
INT8U Clear_Event_Proc(INT8U *pSrc,INT8U SrcLen)
{
  Clear_Event_Data();
  return NO_ERR;  
}

//���ѹ�ϸ������ݴ���(��ͳ��)
INT8U Clear_Stat_Proc(INT8U *pSrc,INT8U SrcLen)
{
  Clear_VolStat_Data();
  return NO_ERR;  
}

//���ݴ��
//Ch��ʾͨ����
//Ctrl_Code������
//pSrc��Ҫ�����������
//SrcLen�����򳤶�
//pDstĿ�껺����
//pDst_Start��DstLenһ���޶�pDst��֡��
INT16U DLT645_Data_Pack(INT8U Ch,INT8U Ctrl_Code,INT8U *pSrc,INT16U SrcLen,INT8U *pDst,INT8U *pDst_Start,INT16U DstLen)
{
  INT8U i;
  
  if(ASSERT(A_WARNING,pDst>=pDst_Start && pDst+SrcLen+15<=pDst_Start+DstLen))
    return 0;
  
  Clear_Ext_Dog();
  
  *(pDst)=0x68;
  if(CH_RS485_1==Ch || CH_IRAD==Ch)//���ݲ�ͬͨ����䲻ͬ�ı��ַ
    mem_cpy(pDst+1,(void *)Meter_Addr.Addr[0],6,pDst_Start,DstLen);
  else
    mem_cpy(pDst+1,(void *)Meter_Addr.Addr[1],6,pDst_Start,DstLen);
  
  *(pDst+7)=0x68;
  *(pDst+8)=Ctrl_Code;//������
  *(pDst+9)=(INT8U)SrcLen;
  mem_cpy(pDst+10,pSrc,SrcLen,pDst_Start,DstLen);
  
  for(i=0;i<SrcLen;i++)//������+0x33
    *(pDst+10+i)+=0x33;
  Get_Buf_MulitByte_Sum(pDst,SrcLen+10,1,pDst+10+SrcLen,1);
  *(pDst+SrcLen+11)=0x16;
  return SrcLen+12;
}

//���645֡��ʽ,pFrame��ʾ֡��ʼ��ַ,FrameLen��ʾ֡�ĳ���
INT8U Check_Frame_Format(INT8U *pFrame,INT8U FrameLen)
{
  INT8U Sum;
  if(!(0x68==*pFrame && 0x68==*(pFrame+7) && 0x16==*(pFrame+FrameLen-1)))//�ж�֡ͷ��֡β
    return 0;

  Get_Buf_MulitByte_Sum(pFrame,FrameLen-2,1,&Sum,1);//�ж�У���
  if(!(Sum==*(pFrame+FrameLen-2)))
    return 0; 
     
  return 1;
}
//���645֡�еı��ַ�Ƿ���ȷ?
//Ch��֡����Դͨ��
//Addr��֡�еı��ַ
//Ctrl_Code��֡�еĿ�����
INT8U Check_Frame_Meter_Addr(INT8U Ch,INT8U Addr[],INT8U Ctrl_Code)
{
  INT8U i;

  if(CH_RS485_1==Ch || CH_IRAD==Ch)
  {
    if(memcmp(Addr,(void *)Meter_Addr.Addr[0],6)==0)
      return 1;
  }
  else
  {
    if(memcmp(Addr,(void *)Meter_Addr.Addr[1],6)==0)
      return 1;
  }
  
//֡�еı��ַ��Meter_Addr�����еı��ַ��һ�£������ж��Ƿ��ǹ㲥��ַ
  if(memcmp(Addr,BROAD_ADDR_99,6)==0)
  {
    //�㲥��ַ99�߱���Ȩ�ޣ������ݡ�У����ʱ������ַ����������
    //C_CLR_ALL��Ҫ����������
    if(C_READ_DATA==Ctrl_Code ||\
       C_READ_FOLLOW_DATA==Ctrl_Code ||\
       C_CLR_ALL==Ctrl_Code ||  
       C_ADJUST_METER==Ctrl_Code ||\
       C_ADJUST_TIME==Ctrl_Code ||\
       C_SET_ADDR==Ctrl_Code)
      return 1;
    else if(C_SET_DATA==Ctrl_Code)//д������Ϊ�ڽϱ�ʱҲ��Ҫ��������Ҫ�ù㲥��ַ������ڹ���״̬Ҳ���ù㲥��ַд����
    {
      //�ڹ���״̬�¿����ù㲥��ַд���ݣ�����У��
      if(Check_Meter_Factory_Status()==1)
        return 1;
      else
        return 0;
    } 

    return 0;
  }
  else if(memcmp(Addr,(void *)BROAD_ADDR_AA,6)==0)//ȫAA��ַ,ֻ�ܾ߱���Ȩ��
  {
    //��ַAA�߱���Ȩ�ޣ�������
    if(C_READ_DATA==Ctrl_Code ||\
       C_READ_FOLLOW_DATA==Ctrl_Code)
      return 1;
    else
      return 0;
  }
  else
  {
    //��λΪ0xAA,��λΪ���ַ��ͬ���������ñ�����ȣ��͵�ַ����Ҫ��3�ֽ�ƥ��
    for(i=0;i<6;i++)
    {
     if(Addr[5-i]!=0xAA)
     {
        if(i<=3)//���3��
        {
          if(CH_RS485_1==Ch || CH_IRAD==Ch)
          {
            if(memcmp(Addr,(void *)Meter_Addr.Addr[0],6-i)==0)
              return 1;
          }
          else
          {
            if(memcmp(Addr,(void *)Meter_Addr.Addr[1],6-i)==0)
              return 1;             
          }
        }
     }
    }
  }
  return 0;
}

//�ȴ�ĳ�¼�
void Wait_Event_Data_Proc_End(INT8U Event_ID)
{
  OS_Waitfor_Sec(Check_Event_End(Event_ID)==0,5);//�ȴ�5s��û�д������򱨶��Դ���
  if(Check_Event_End(Event_ID)==1)
    ASSERT(A_WARNING,0);
  OS_Waitfor(Check_Event_End(Event_ID));
}
//645����֡�Ĵ���
//Ctrl_Code������
//pSrc,645֡��ʼ
//SrcLen,֡��
//pDst,Ŀ�껺����
//pDst_Start,Ŀ�껺������ʼ��ַ
//DstLen,Ŀ�껺��������
INT16U Rcv_DLT645_Data_Proc(INT8U Ch,INT8U *pFrame,INT8U FrameLen,INT8U *pDst,INT8U *pDst_Start,INT16U DstLen)
{
  INT8U FollowFlag,Meter_Addr_Modify_Flag;
  INT8U Data_PSW;//�޸�������Ҫ��Ȩ��
  INT8U User_PSW;//��ǰ�û�ӵ�е�Ȩ��
  INT8U Re,ErrFlag;
  static PROTO_DI DI;
  INT16U Len;
  INT8U Ctrl_Code,SrcLen;
  INT8U *pSrc,i;
  
  ErrFlag=NO_ERR;
  Sys_Run_Flag.Err_Flag=0;//������Ϣ������
  
  if(Check_Frame_Format(pFrame,FrameLen)==0)
    return 0;
  
  Ctrl_Code=*(pFrame+8);
  if(Check_Frame_Meter_Addr(Ch,pFrame+1,Ctrl_Code)==0)
    return 0;


  //�жϱ��ַ
  //ErrFlag=Err_Info.ErrFlag;
  pSrc=pFrame+10;//��������ʼ��ַ
  SrcLen=FrameLen-12;//�����򳤶�
  
  for(i=0;i<SrcLen;i++)
    *(pSrc+i)=*(pSrc+i)-0x33;
  
  Re=Check_DLT645_Data_Len(Ctrl_Code,pSrc,SrcLen);//�ж����ݳ���
  if(ASSERT(A_WARNING,Re==NO_ERR))//���ݳ��Ȳ���
  {
    SET_BIT(Sys_Run_Flag.Err_Flag,ILLEGAL_DATA_ERR);//�Ƿ�����
    *(pDst+10)=Sys_Run_Flag.Err_Flag;
    return DLT645_Data_Pack(Ch,Ctrl_Code|0xC0,pDst+10,1,pDst,pDst_Start,DstLen);
  }
  
  //��ȡִ�иò�����Ҫ��Ȩ�޼���
  Data_PSW=Get_Protocol_Data_Authority(Ch,Ctrl_Code,pSrc,SrcLen);
  if(ASSERT(A_WARNING,Data_PSW!=PSW_NULL))//û���ҵ������ݵ�������
  {
    SET_BIT(Sys_Run_Flag.Err_Flag,ILLEGAL_DATA_ERR);//�Ƿ�����
    *(pDst+10)=Sys_Run_Flag.Err_Flag;
    return DLT645_Data_Pack(Ch,Ctrl_Code|0xC0,pDst+10,1,pDst,pDst_Start,DstLen);
  }
  
  //��ȡ��ǰ�û�ӵ�е�Ȩ�޼���
  User_PSW=Get_User_Authority(Ctrl_Code,pSrc,SrcLen,&ErrFlag);//��鵱ǰ�û�ӵ�е�Ȩ��
  if(User_PSW==PSW_NULL)//�����û�Ȩ�޲���
  {
    if(ErrFlag!=PROTOCOL_PSW_ERR)//����������������б�������
    {
      DEBUG_PRINT(HUCK,DEBUG_0,"User Authority Error");
      SET_BIT(Sys_Run_Flag.Err_Flag,PSW_ERR);//Ȩ�޲���,Ҳ��Ϊ�������
      *(pDst+10)=Sys_Run_Flag.Err_Flag;
      return DLT645_Data_Pack(Ch,Ctrl_Code|0xC0,pDst+10,1,pDst,pDst_Start,DstLen);
    }
  }
  
  if(Check_Meter_Factory_Status()==0)//���ڹ���״̬������ż���û�Ȩ��
  { 
    if(PSW_Err_Info.Set_En_Mins EQ 0)//û�п�������Ȩ��,������ȷһ�Σ�����30��������Ȩ��
    {
      if(PSW_Err_Info.Lock_Mins>0 && PSW_Err_Info.Lock_Mins <= 1440)//������������£���Ϊ�û�ֻ�߱����Ȩ��
        User_PSW=PSW_3; 
      
      if(User_PSW>Data_PSW)//��ǰ�û�Ȩ�޸��ڻ���ڵ�ǰ����������Ҫ��Ȩ��,Ȩ�޲���!
      {
        if(PSW_Err_Info.Err_Times<99)
        {
          PSW_Err_Info.Clr_Err_Times_Mins=1440;//1����Զ��������������
          PSW_Err_Info.Err_Times++;
          if(PSW_Err_Info.Err_Times==5)
          {
            PSW_Err_Info.Lock_Mins=1440;//����1440����
            Set_Event_Instant(ID_EVENT_METER_LOCK);  //�������¼�����
          }
          SET_STRUCT_SUM(PSW_Err_Info);
        }
       
        DEBUG_PRINT(HUCK,DEBUG_0,"User do not have the authority!");
        SET_BIT(Sys_Run_Flag.Err_Flag,PSW_ERR);
        *(pDst+10)=Sys_Run_Flag.Err_Flag;
        return DLT645_Data_Pack(Ch,Ctrl_Code|0xC0,pDst+10,1,pDst,pDst_Start,DstLen);
      }
      
      if(Data_PSW <= PSW_2)//��Ҫ��дȨ�ޣ���������ȶ���ȷ���򿪷�д����30����
      {
        PSW_Err_Info.Set_En_Mins = OPEN_SET_AUTH_TIME;
        SET_STRUCT_SUM(PSW_Err_Info);
      }
    }
    else
      DEBUG_PRINT(HUCK,DEBUG_0,"PSW Set_En_Mins:%u",PSW_Err_Info.Set_En_Mins);
  }
  
  Meter_Addr_Modify_Flag=0;//���ַ���ñ�־  
  Cur_Comm_Ch.Ch=Ch;//���浱ǰͨ��ͨ��
  //�����û������뼶��
  Re=CHECK_STRUCT_SUM(User_Authority_Flag);
  ASSERT(A_WARNING,1==Re);
  User_Authority_Flag.Flag=AUTHORITY_FLAG;//Ȩ�ޱ�־�����Ӱ�ȫ��
  SET_STRUCT_SUM(User_Authority_Flag);
  
  Clr_Ext_Inter_Dog();//����ⲿ�Լ��ڲ����Ź�
  
  //Extend_Rcv_Data_Proc();
  //�����Ҫ�������ݣ������pDst+10��ʼ��λ��
  switch(Ctrl_Code)
  {
  case C_READ_DATA:    //������
    DI=(PROTO_DI)(*pSrc)+(PROTO_DI)(*(pSrc+1))*256;  
    Len=_Get_DLT645_Data(DI,pSrc+2,SrcLen-2,pDst+12,pDst_Start,DstLen,FOR_COMM,&FollowFlag,&Re);
    mem_cpy(pDst+10,&DI,2,pDst_Start,DstLen);
    Len+=2;
    break;
  case C_READ_FOLLOW_DATA://����������
    //pSrc+2����������DI�����ֽں������
    Len=_Get_DLT645_Data(DI,pSrc+2,SrcLen-2,pDst+12,pDst_Start,DstLen,FOR_COMM,&FollowFlag,&Re);
    mem_cpy(pDst+10,&DI,2,pDst_Start,DstLen);
    Len+=2;
    break;
  case C_SET_DATA:     //д����
    Re=Set_Data_Proc(pSrc,SrcLen);
    if(Re==NO_ERR) //�ɹ����ò����������������������Ϣ
      Clear_PSW_Err_Info();
    Len=0;
    break;
  case C_ADJUST_METER://У��
    Re=CalibMeterProc_PUCK(*(INT16U *)pSrc,pSrc+2,SrcLen-2);
    Len=0;
    break;
  case C_ADJUST_TIME:  //�㲥Уʱ
    Re=Adjust_Time_Proc(pSrc,SrcLen);
    Len=0;
    //break;
    return 0;//Уʱ��Ҫ��Ӧ��
  case C_SET_ADDR:    //д���ַ
    Meter_Addr_Modify_Flag=0;
    Re=Set_MeterAddr_Proc(Ch,pSrc,SrcLen);
    if(Re==NO_ERR)
    {
      if(CH_RS485_1==Ch || CH_IRAD==Ch)
        Meter_Addr_Modify_Flag=1;//��һ·���ַ�����޸�
      else
        Meter_Addr_Modify_Flag=2;//�ڶ�·���ַ�����޸�
    }
    Len=0;
    break;
  case C_SET_COM_BAUD: //��ͨ���ٶ�
    Re=Set_CommBaud_Proc(Ch,pSrc,SrcLen);
    Len=0;
    break;
  case C_SET_PSW:   //�޸�����
    Re=Set_PSW_Proc(pSrc,SrcLen,pDst+10,pDst_Start,DstLen);
    if(Re==NO_ERR)
      Len=4;
    else
      Len=0;
    break;
  case C_CLR_ALL:      //����0���߳��涳��
    if(SrcLen==0x04)//����
    {
      Set_Event_Instant(ID_EVENT_CLR_ALL_DATA);//������
      Wait_Event_Data_Proc_End(ID_EVENT_CLR_ALL_DATA);//�ȴ��¼��������
      Set_Clear_Data_Flag(CLEAR_ALL_FLAG);
      OS_Waitfor(Check_Clear_Data_Flag()==CLEAR_END_FLAG);
      Re=NO_ERR;
      Len=0;
    }
    else if(SrcLen==0x03)//����
    {
      DEBUG_PRINT(HUCK,DEBUG_0,"Freez Data Time:%x-%x",*(pSrc+1),*(pSrc+2));      
      if(*pSrc==0x13)//�ܵ�����������
      {//�ܵ�������������������洢���ݣ�ֻ�����¼���¼���洢����
        DEBUG_PRINT(HUCK,DEBUG_0,"Total Energy Data Freeze RightNow!");
        Set_Event_Instant(ID_EVENT_ENERG_FREEZ);//�ܵ�����������
        Wait_Event_Data_Proc_End(ID_EVENT_ENERG_FREEZ);//�ȴ��¼��������
        Re=NO_ERR;
      }
      else if(*pSrc==0x03)//˳ʱ���͵�������
      {
        if(*(pSrc+1)==0x99 && *(pSrc+2)==0x99)//��������99��ʾ��������
        {
          DEBUG_PRINT(HUCK,DEBUG_0,"Instant and Energy Data Freeze RightNow!");
          Freeze_Right_Now(0);//����˲ʱ��
          Freeze_Right_Now(1);//�������
          Re=NO_ERR;
        }
        else//���ö���ʱ��,���ڶ���
        {
          if(*(pSrc+1)<0x60 && *(pSrc+2)<0x24)
          {
            Re=Write_Storage_Data(ENERGY_FREEZE_TIME,pSrc+1,2);
            Read_Freeze_Data_Para_From_Rom();//���¶�ȡ����ʱ��
            Re=NO_ERR;
          }
          else
            Re=PROTOCOL_DATA_ERR;
        }
      }
      else
        Re=PROTOCOL_DATA_ERR;

      Len=0;
    }
    break;
  case C_CLR_DEMAND:   //������
    Set_Event_Instant(ID_EVENT_CLR_DEMAND_COM);//ͨѶ�������¼�
    Wait_Event_Data_Proc_End(ID_EVENT_CLR_DEMAND_COM);//�ȴ��¼��������
    Set_Clear_Data_Flag(CLEAR_DEMAND_FLAG);
    OS_Waitfor(Check_Clear_Data_Flag()==CLEAR_END_FLAG);
    Re=NO_ERR;
    Len=0;
    break;
  case C_CLR_EVENT:    //�����(�¼�)
    Set_Event_Instant(ID_EVENT_CLR_PROCESS);//�����
    Wait_Event_Data_Proc_End(ID_EVENT_CLR_PROCESS);//�ȴ��¼��������
    Set_Clear_Data_Flag(CLEAR_EVENT_FLAG);
    OS_Waitfor(Check_Clear_Data_Flag()==CLEAR_END_FLAG);
    Re=NO_ERR;
    Len=0;
    break;
  case C_CLR_STAT:     //���ѹ�ϸ���(ͳ��)
    Set_Event_Instant(ID_EVENT_CLR_VOLT_PASS);//���ѹ�ϸ���
    Wait_Event_Data_Proc_End(ID_EVENT_CLR_VOLT_PASS);//�ȴ��¼��������
    Set_Clear_Data_Flag(CLEAR_VOLSTAT_FLAG);
    OS_Waitfor(Check_Clear_Data_Flag()==CLEAR_END_FLAG);
    Re=NO_ERR;
    Len=0;
    break;
  default:
    Re=PROTOCOL_DATA_ERR;
    Len=0;
    break;  
  }
  User_Authority_Flag.Flag=0;
  SET_STRUCT_SUM(User_Authority_Flag);
  
  if(Re==NO_ERR)
  {
    Len=DLT645_Data_Pack(Ch,Ctrl_Code|0x80,pDst+10,Len,pDst,pDst_Start,DstLen);
    
    //�жϱ��ַ�Ƿ������޸ģ�����Ѿ��޸ģ���Ҫ���¶�ȡ��Meter_Addr�����У���ȡֻ���ڴ��������
    //��ΪӦ��֡��Ȼ�����ϵı��ַ
    if(Meter_Addr_Modify_Flag==1)
      Read_Storage_Data(METER_ADDR0,(void *)Meter_Addr.Addr[0],(void *)Meter_Addr.Addr[0],6,&ErrFlag);
    else if(Meter_Addr_Modify_Flag==2)
      Read_Storage_Data(METER_ADDR1,(void *)Meter_Addr.Addr[1],(void *)Meter_Addr.Addr[1],6,&ErrFlag);

    ASSERT(A_WARNING,NO_ERR==ErrFlag);
    return Len;
  }
  else
  {
    //��Ӧ��������ʾ��
    if(0==Sys_Run_Flag.Err_Flag)
    {
      SET_BIT(Sys_Run_Flag.Err_Flag,DI_ERR);
    }
    *(pDst+10)=Sys_Run_Flag.Err_Flag;
    Len=1;

    return DLT645_Data_Pack(Ch,Ctrl_Code|0xC0,pDst+10,Len,pDst,pDst_Start,DstLen);
  }
}

//���ñ��Э������
//����ֵ
//pSrc��֡��ʼλ�ã�Ҳ���ǵ�һ��68��λ��
//SrcLen��֡������68��16�ĳ���
INT8U Rcv_Meter_Protocol_Data_Proc(INT8U Ch,INT8U Protocol_Type,INT8U *pFrame,INT8U FrameLen,INT8U *pDst,INT8U *pDst_Start,INT16U DstLen)
{
  if(PROTOCOL_DLT645==Protocol_Type)
  {
    return Rcv_DLT645_Data_Proc(Ch,pFrame,FrameLen,pDst,pDst_Start,DstLen);
  }
  return 0;
}

//�ڻ���������645֡,������֮������Ӧ��֡
//Ch,��ʾ������Դͨ��
//pSrc,Դ������
//SrcLen,Դ����������
//pDst,Ŀ�껺��������
//pDst_Start,��DstLenһ���޶�Ӧ��֡����
//���س���,0��ʶû��Ӧ��֡��>0��Ӧ��֡����Ϊ֡��
INT16U Rcv_PROTOCOL_Frame_Proc(INT8U Ch,INT8U *pSrc,INT16U SrcLen,INT8U *pDst,INT8U *pDst_Start,INT16U DstLen)
{
  INT16U Len;//Offset;
  
  //Len=Search_Protocol_Frame(pSrc,SrcLen,&Offset);
  //if(Len>0)
  //{
    Len=Rcv_DLT645_Data_Proc(Ch,pSrc,SrcLen,pDst,pDst_Start,DstLen);
    return Len;
  //}

  //return 0;
}

//Ѱ��Э��֡����ĳ��pSrc��ʼ��buf��
//Ѱ��һ��645֡
//pSrc�������Ļ�������ʼλ��
//SrcLen,����������
//pOffset,�ҵ���֡����ʼƫ�ƣ������SrcLen
//����ֵ:�ҵ���֡��
INT16U Search_Protocol_Frame(INT8U *pSrc,INT16U SrcLen,INT16U *pOffset)
{
  INT16U i;
  INT16U Len;
  
  if(SrcLen<10)
    return 0;
  
  for(i=0;i<SrcLen-10;i++)
  {
    if(*(pSrc+i)==0x68 &&*(pSrc+i+7)==0x68)
    {
      Len=*(pSrc+i+9);//�����򳤶�
      Len+=12;//����֡ͷβ
      if((i+Len)<=SrcLen && Check_Frame_Format(pSrc+i,Len)==1)//֡��ʽ��ȷ
      {
        *pOffset=i;
        return Len;       
      }
    }
  }
  return 0;
}

//Ѱ��Э��֡����ĳ��pSrc��ʼ��buf��
//Ѱ��һ��645֡
//pSrc�������Ļ�������ʼλ��
//SrcLen,����������
//pOffset,�ҵ���֡����ʼƫ�ƣ������SrcLen
//����ֵ:�ҵ���֡��
INT16U Simple_Search_Frame(INT8U *pSrc,INT16U SrcLen,INT16U *pOffset)
{
  INT16U i;
  INT16U Len;
  
  if(SrcLen<10)
    return 0;
  
  for(i=0;i<SrcLen-10;i++)
  {
    if(*(pSrc+i)==0x68 &&*(pSrc+i+7)==0x68)
    {
      Len=*(pSrc+i+9);//�����򳤶�
      Len+=12;//����֡ͷβ
      
      if(0x16==*(pSrc+i+Len-1))//�ж�֡ͷ��֡β
      return Len;
    }
  }
  return 0;
}

//���Э�����ݵĴ洢��Protocol_Data��S_ROM���Ե�����Ӧ���ڴ洢�ж�������
INT8U Check_Protocol_Data_Storage()
{ 
  INT16U i;
  INT8U Re;
  
  Re = NO_ERR;
  Clear_Ext_Dog();
  for(i=0;i<S_NUM(Protocol_Data);i++)
  {
    if(S_ROM==Protocol_Data[i].Storage && Protocol_Data[i].Spec_Flag==SPEC_NO)
    {    
      if(Get_Storage_Data_Len(Protocol_Data[i].DI)==0)
      {
        DEBUG_PRINT(HUCK,DEBUG_0,"Protocol_Data %x Storage Err",Protocol_Data[i].DI);
        Re |= PROTOCOL_DATA_STORAGE_ERR;
      }
    }
  }
  return Re;
}

//������Ҫ������ݱ�־
//��ڲ���:
//CLEAR_END_FLAG��û��������Ҫ���
//CLEAR_ENERGY_FLAG,��Ҫ�������
//CLEAR_DEMAND_FLAG,��Ҫ�������
//CLEAR_VOSTAT_FLAG,��Ҫ�����ѹͳ��
void Set_Clear_Data_Flag(INT32U Flag)
{
  INT8U Re;
  Re=CHECK_STRUCT_SUM(Clear_Flag);
  ASSERT(A_WARNING,1==Re);
  Clear_Flag.Flag=Flag;
  SET_STRUCT_SUM(Clear_Flag); 
}

//����Ƿ���Ҫ�������
//����ֵ:
//CLEAR_END_FLAG��û��������Ҫ���
//CLEAR_ENERGY_FLAG,��Ҫ�������
//CLEAR_DEMAND_FLAG,��Ҫ�������
//CLEAR_VOSTAT_FLAG,��Ҫ�����ѹͳ��
//CLEAR_EVENT_FLAG,��Ҫ�����ѹͳ��
INT32U Check_Clear_Data_Flag()
{
  INT8U Re;
  
  Re=1;
  Re&=CHECK_STRUCT_VAR(Clear_Flag);
  Re&=CHECK_STRUCT_SUM(Clear_Flag);
  if(ASSERT(A_WARNING,1==Re))
    return CLEAR_END_FLAG;
  else
    return Clear_Flag.Flag;
}

//֪ͨͨ�����̣�����������
//�ڲ���Clear_Flag.Flag�ó�CLEAR_END_FLAG
//�Ӷ�ʹ�´ε���Check_Clear_Data_Flag����CLEAR_END_FLAG
void Clear_Data_End()
{
  INT8U Re;
  Re=CHECK_STRUCT_SUM(Clear_Flag);
  ASSERT(A_WARNING,1==Re);
  Clear_Flag.Flag=CLEAR_END_FLAG;
  SET_STRUCT_SUM(Clear_Flag);
}
#undef DATA_TRANS_C

