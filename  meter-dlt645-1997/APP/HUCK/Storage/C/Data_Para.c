#define DATA_PARA_C
#include "includes.h"

//����������ݵĴ洢�ֲ�
CONST S_Data_Mem_Map Data_Mem_Map[]=
{
  //����洢����ǰ�棬�����ڿ��ټ���
  {IMP6,{LOG_MEM9,NULL_LOG_MEM,NULL_LOG_MEM,NULL_LOG_MEM,NULL_LOG_MEM}},//����洢���ݻ��������
  
  {IMP0,{LOG_MEM0,LOG_MEM1,LOG_MEM4,LOG_MEM10,LOG_MEM13}},//��Ҫ����
  {IMP1,{LOG_MEM2,LOG_MEM5,LOG_MEM6,NULL_LOG_MEM,NULL_LOG_MEM}},//��ǰ��������������
  {IMP2,{LOG_MEM3,LOG_MEM11,LOG_MEM12,NULL_LOG_MEM,NULL_LOG_MEM}},//��ʷ��������
  {IMP3,{LOG_MEM7,NULL_LOG_MEM,NULL_LOG_MEM,NULL_LOG_MEM,NULL_LOG_MEM}},//�¼���¼
  {IMP4,{LOG_MEM14,LOG_MEM15,LOG_MEM16,LOG_MEM17,LOG_MEM18}},//������
  {IMP5,{LOG_MEM19,NULL_LOG_MEM,NULL_LOG_MEM,NULL_LOG_MEM,NULL_LOG_MEM}},//��������
  {IMP7,{LOG_MEM20,LOG_MEM21,NULL_LOG_MEM,NULL_LOG_MEM,NULL_LOG_MEM}},//��Ҫ�¼���¼
};

//���ݴ洢ӳ���
CONST S_Data_Para_Storage_Info Data_Para_Storage[]=
{
 {BOOT_FLAG,IMP1,4,1},//������־�������Ƿ��ǵ�һ������
 
 {CUR_ENERGY_PD,IMP6,ENERGY_SAVE_SIZE,1},//��ǰ����,����洢,ƽʱҲ��ʱ�洢
 {CUR_DEMAND_PD,IMP6,sizeof(S_Demand),1},//����ֻ�����ܺ͵�ǰ������������S_Demand_

 {CUR_VOLSTAT_PD,IMP6,sizeof(S_VolStat),1},//��ǰ��ѹͳ������
 {TOTAL_VOLSTAT_PD,IMP6,sizeof(S_VolStat),1},//�ܵ�ѹ�������
 //{CUR_EVENT_PD,IMP6,sizeof(S_Event_Cumu),1},//�¼��ۼ�����
 
 {LOAD_DATA_INDEX,IMP1,sizeof(S_LoadData_Index),1},
 //�������ߴ洢��Ϣ,ÿ�洢һ���������ߴ洢һ�θ�����,�洢Ƶ�������ѡ��FRAM��Ϊ�洢����

 {CUR_ENERGY,IMP6,ENERGY_SAVE_SIZE,1},//��ǰ����
 {CUR_DEMAND,IMP6,DEMAND_SAVE_SIZE,1},//�����������
 
 {TIME_PD,IMP6,sizeof(Cur_Time1),1},
 {TIME_BAK_PD,IMP6,sizeof(Cur_Time1),1},
 {CUMU_EVENT_PD,IMP6,sizeof(S_Event_Cumu_Data),1},//�¼���������
 
 {SAVE_PD_DATA_TIME,IMP6,4,1},//���������������ʱ�䣬��λms
 {LOAD_DATA_INDEX_PD,IMP6,sizeof(S_LoadData_Index),1},
 
 {CUR_VOLSTAT,IMP1,sizeof(S_VolStat),1},//��ǰ��ѹͳ������
 {TOTAL_VOLSTAT,IMP1,sizeof(S_VolStat),1},//�ܵ�ѹ�������
 //{EVENT_CUMU,IMP1,sizeof(S_Event_Cumu),1},//�¼��ۼ�����
 
 {METER_ADDR0,IMP1,6,1},//�豸��ַ0
 {METER_ADDR1,IMP1,6,1},//�豸��ַ1
 {METER_ADDR2,IMP1,6,1},//�豸��ַ2
 
 {COMM_BAUD0,IMP1,1,1},//��һ·������
 {COMM_BAUD1,IMP1,1,1},//�ڶ�·������
 {COMM_BAUD2,IMP1,1,1},//����·������
 
 {PASSWORD_0,IMP1,3,1},//0������
 {PASSWORD_1,IMP1,3,1},//1������
 {PASSWORD_2,IMP1,3,1},//2������

 {CUR_ENERGY_BAK0,IMP1,ENERGY_SAVE_SIZE,1},//��ǰ��������,ƽʱ��ʱ�洢
 {CUR_DEMAND_BAK,IMP1,DEMAND_SAVE_SIZE,1},//��������������䷢��ʱ��
 {CUR_ENERGY_BAK1,IMP1,ENERGY_SAVE_SIZE,1},//��ǰ��������,ƽʱ��ʱ�洢
 {CUR_ENERGY_BAK2,IMP2,ENERGY_SAVE_SIZE,1},//��ǰ��������,ƽʱ��ʱ�洢
 {CUR_VOLSTAT_BAK,IMP1,sizeof(S_VolStat),1},//��ǰ��ѹͳ�����ݱ���
 {TOTAL_VOLSTAT_BAK,IMP1,sizeof(S_VolStat),1},//�ܵ�ѹ������ݱ���
 //{EVENT_CUMU_BAK,IMP1,sizeof(S_Event_Cumu),1},//�¼��ۼ����ݱ���

 {ENERGY_FREEZE_TIME,IMP1,2,1},//���ڶ���ʱ��
 {REACTIVE_FREEZE_TIME,IMP1,2,1},//���ڶ���ʱ��
 
 {PROG_RECORD,IMP1,sizeof(Prog_Record),1},
 {CLR_DEMAND_RECORD,IMP1,sizeof(Clr_Demand_Record),1},
 
 {LOAD_DATA_INDEX_BAK,IMP1,sizeof(S_LoadData_Index),1},//�������ߴ洢�������ݵ�
 {LOAD_DATA_HOUR_INDEX,IMP5,2,LOAD_DATA_HOUR_INDEX_NUM},//���帺������Сʱ����,LOAD_DATA_HOUR_INDEX_NUM��
 {LOAD_DATA,IMP5,LOAD_DATA_SIZE,LOAD_DATA_NUM},//���帺������,LOAD_DATA_NUM��

 
 {HIS_ENERGY,IMP2,ENERGY_SAVE_SIZE,HIS_ENERGY_DATA_MONTHS},//��13�µ���
 {HIS_DEMAND,IMP2,DEMAND_SAVE_SIZE,HIS_DEMAND_DATA_MONTHS},//��13���������
 {HIS_VOLSTAT,IMP2,sizeof(S_VolStat),HIS_VOLSTAT_DATA_MONTHS},//��3���µ�ѹͳ������
//////////////////�¼���¼DI///////////
 {E_E400,IMP7,sizeof(STORA_DI),1},
 
 {E_E900,IMP7,sizeof(STORA_DI),1},
 {E_E910,IMP7,sizeof(STORA_DI),1},
 {E_E920,IMP7,sizeof(STORA_DI),1},
 {E_E930,IMP7,sizeof(STORA_DI),1},
 {E_E940,IMP7,sizeof(STORA_DI),1},
 {E_E950,IMP7,sizeof(STORA_DI),1},
 {E_E960,IMP7,sizeof(STORA_DI),1},
 {E_E970,IMP7,sizeof(STORA_DI),1},
 {E_E980,IMP7,sizeof(STORA_DI),1},
 {E_E990,IMP7,sizeof(STORA_DI),1},
 {E_E9A0,IMP7,sizeof(STORA_DI),1},
 {E_E9B0,IMP7,sizeof(STORA_DI),1},
 {E_E9C0,IMP7,sizeof(STORA_DI),1},
 {E_E9D0,IMP7,sizeof(STORA_DI),1},
 //{E_E9E0,IMP1,sizeof(STORA_DI),1},
 //{E_E9F0,IMP1,sizeof(STORA_DI),1},

 {E_EA00,IMP7,sizeof(STORA_DI),1},
 {E_EA10,IMP7,sizeof(STORA_DI),1},
 {E_EA20,IMP7,sizeof(STORA_DI),1},
 {E_EA30,IMP7,sizeof(STORA_DI),1},
 {E_EA40,IMP7,sizeof(STORA_DI),1},
 {E_EA50,IMP7,sizeof(STORA_DI),1},
 {E_EA60,IMP7,sizeof(STORA_DI),1},
 {E_EA70,IMP7,sizeof(STORA_DI),1},
 {E_EA80,IMP7,sizeof(STORA_DI),1},
 {E_EA90,IMP7,sizeof(STORA_DI),1},
 {E_EAA0,IMP7,sizeof(STORA_DI),1},
 {E_EAB0,IMP7,sizeof(STORA_DI),1},
 {E_EAC0,IMP7,sizeof(STORA_DI),1},
 {E_EAD0,IMP7,sizeof(STORA_DI),1},
 {E_EAE0,IMP7,sizeof(STORA_DI),1},
 {E_EAF0,IMP7,sizeof(STORA_DI),1},

 {E_EB00,IMP7,sizeof(STORA_DI),1},
 {E_EB10,IMP7,sizeof(STORA_DI),1},
 {E_EB20,IMP7,sizeof(STORA_DI),1},
 {E_EB30,IMP7,sizeof(STORA_DI),1},
 {E_EB40,IMP7,sizeof(STORA_DI),1},
 {E_EB50,IMP7,sizeof(STORA_DI),1},
 {E_EB60,IMP7,sizeof(STORA_DI),1},
 {E_EB70,IMP7,sizeof(STORA_DI),1},
 {E_EB80,IMP7,sizeof(STORA_DI),1},
 {E_EB90,IMP7,sizeof(STORA_DI),1},
 {E_EBA0,IMP7,sizeof(STORA_DI),1},
 {E_EBB0,IMP7,sizeof(STORA_DI),1},
 {E_EBC0,IMP7,sizeof(STORA_DI),1},
 {E_EBD0,IMP7,sizeof(STORA_DI),1},
 {E_EBE0,IMP7,sizeof(STORA_DI),1},
 {E_EBF0,IMP7,sizeof(STORA_DI),1},

 {E_EC00,IMP7,sizeof(STORA_DI),1},
 {E_EC10,IMP7,sizeof(STORA_DI),1},
 {E_EC20,IMP7,sizeof(STORA_DI),1},
 {E_EC30,IMP7,sizeof(STORA_DI),1},
 {E_EC40,IMP7,sizeof(STORA_DI),1},
 {E_EC50,IMP7,sizeof(STORA_DI),1},
 {E_EC60,IMP7,sizeof(STORA_DI),1},
 {E_EC70,IMP7,sizeof(STORA_DI),1},
 {E_EC80,IMP7,sizeof(STORA_DI),1},
 {E_EC90,IMP7,sizeof(STORA_DI),1},
 {E_ECA0,IMP7,sizeof(STORA_DI),1},
 {E_ECB0,IMP7,sizeof(STORA_DI),1},
 {E_ECC0,IMP7,sizeof(STORA_DI),1},
 {E_ECD0,IMP7,sizeof(STORA_DI),1},
 {E_ECE0,IMP7,sizeof(STORA_DI),1},
 {E_ECF0,IMP7,sizeof(STORA_DI),1},

 {E_ED00,IMP7,sizeof(STORA_DI),1},
 {E_ED10,IMP7,sizeof(STORA_DI),1},
 {E_ED20,IMP7,sizeof(STORA_DI),1},
 {E_ED30,IMP7,sizeof(STORA_DI),1},
 {E_ED40,IMP7,sizeof(STORA_DI),1},
 {E_ED50,IMP7,sizeof(STORA_DI),1},
 {E_ED60,IMP7,sizeof(STORA_DI),1},
 {E_ED70,IMP7,sizeof(STORA_DI),1},
 {E_ED80,IMP7,sizeof(STORA_DI),1},
 {E_ED90,IMP7,sizeof(STORA_DI),1},
 {E_EDA0,IMP7,sizeof(STORA_DI),1},
 {E_EDB0,IMP7,sizeof(STORA_DI),1},
 {E_EDC0,IMP7,sizeof(STORA_DI),1},
 {E_EDD0,IMP7,sizeof(STORA_DI),1},
 {E_EDE0,IMP7,sizeof(STORA_DI),1},
 
 //����ʧѹ����
 //{TOTAL_LOSS_VOL,IMP7,sizeof(S_Phase_Cumu),9},
 //����ʧ������
 //{TOTAL_LOSS_CUR,IMP7,sizeof(S_Phase_Cumu),8},
 //�����������
 //{TOTAL_BREAK_VOL,IMP7,sizeof(S_Phase_Cumu),4},
 //��������
 //{TOTAL_REVERSE,IMP7,sizeof(S_Reverse_Cumu),4},
 //����ʧѹ
 //{_TOTAL_LOSS_VOL,IMP7,sizeof(S_Loss_Vol_Cumu),9},
  //����ʧ��
 //{_TOTAL_LOSS_CUR,IMP7,sizeof(S_Loss_Cur_Cumu),8},

//////////////////���µ����������Protocol_Data�ж����˵�////////////////
 
 {0xB214,IMP1,4,1},//ʱ�ӵ�ع���ʱ��
 
// {0xB220,IMP1,36		R	��	36	��ѹ������ۼ����� ��ע1��
//B221		R	��	36	  ���µ�ѹ������ݣ�ע1��
//B222		R	��	36	��1�µ�ѹ������ݣ�ע1��
//B223		R	��	36	��2�µ�ѹ������ݣ�ע1��
//B224		R	��	36	��3�µ�ѹ������ݣ�ע1��
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

 //{0xB310,IMP7,4,4},//��ʧѹ����
 //{0xB311,IMP1,2,1},//A��ʧѹ����
 //{0xB312,IMP1,2,1},//B��ʧѹ����
 //{0xB313,IMP1,2,1},//C��ʧѹ����

 //{0xB320,IMP7,4,8},//��ʧѹ�ۼ�ʱ��    
 //{0xB321,IMP1,3,1},//A��ʧѹ�ۼ�ʱ��
 //{0xB322,IMP1,3,1},//B��ʧѹ�ۼ�ʱ��
 //{0xB323,IMP1,3,1},//C��ʧѹ�ۼ�ʱ��
 //{0xB324,IMP1,3,1},//��ȫʧѹ�ۼ�ʱ���
 //{0xB328,IMP1,3,1},//��ʧ���ۼ�ʱ��                            
 //{0xB329,IMP1,3,1},//A��ʧ���ۼ�ʱ�� 
 //{0xB32A,IMP1,3,1},//B��ʧ���ۼ�ʱ�� 
 //{0xB32B,IMP1,3,1},//C��ʧ���ۼ�ʱ�� 

 {0xB330,IMP1,4,1},//���һ��ʧѹ��ʼʱ��     
 {0xB331,IMP1,4,1},//A�����һ��ʧѹ��ʼʱ��  
 {0xB332,IMP1,4,1},//B�����һ��ʧѹ��ʼʱ��  
 {0xB333,IMP1,4,1},//C�����һ��ʧѹ��ʼʱ��  
 {0xB334,IMP1,4,1},//AB�����һ��ʧѹ��ʼʱ�� 
 {0xB335,IMP1,4,1},//AC�����һ��ʧѹ��ʼʱ�� 
 {0xB336,IMP1,4,1},//BC�����һ��ʧѹ��ʼʱ�� 
 {0xB337,IMP1,4,1},//ABC�����һ��ʧѹ��ʼʱ��
 {0xB338,IMP1,4,1},//ȫʧѹ���һ����ʼʱ��

 {0xB340,IMP1,4,1},//���һ��ʧѹ����ʱ��     
 {0xB341,IMP1,4,1},//A�����һ��ʧѹ����ʱ��  
 {0xB342,IMP1,4,1},//B�����һ��ʧѹ����ʱ��  
 {0xB343,IMP1,4,1},//C�����һ��ʧѹ����ʱ��  
 {0xB344,IMP1,4,1},//AB�����һ��ʧѹ����ʱ�� 
 {0xB345,IMP1,4,1},//AC�����һ��ʧѹ����ʱ�� 
 {0xB346,IMP1,4,1},//BC�����һ��ʧѹ����ʱ�� 
 {0xB347,IMP1,4,1},//ABC�����һ��ʧѹ����ʱ��
 {0xB348,IMP1,4,1},//ȫʧѹ���һ�ν���ʱ��

 //{0xB710,IMP7,sizeof(S_Loss_Vol_Cumu),7},//ʧѹ�ۼ�����   
 //{0xB720,IMP3,sizeof(S_Loss_Cur_Cumu),6},//ʧ���ۼ�����
 //{0xB730,IMP3,sizeof(S_Reverse_Cumu),4},//�����ۼ�����
 //{0xB740,IMP3,sizeof(S_Phase_Cumu),3},//�����ۼ�����   

 
 {0xC022,IMP4,1,1},//������״̬��
 {0xC023,IMP4,7,1},//������ʽ��1
 {0xC024,IMP4,7,1},//������ʽ��2

       
 {0xC030,IMP4,3,1},//�й�����
 {0xC031,IMP4,3,1},//�޹�����
 {0xC032,IMP4,6,1},//���
 {0xC033,IMP4,6,1},//�û���
 {0XC034,IMP4,6,1},//�豸��

 {0xC047,IMP0,1,1},//ģʽ��1
 {0xC048,IMP0,1,1},//ģʽ��2
 {0xC049,IMP0,1,1},//ģʽ��3
 {0xC04A,IMP4,1,1},//ģʽ��4//��������ģʽ��
 {0XC04B,IMP4,1,1},//ģʽ��5
 {0xC04C,IMP4,1,1},//ģʽ��6
 {0xC04D,IMP4,1,1},//ģʽ��7
 {0xC04E,IMP4,1,1},//ģʽ��8

 {0xC111,IMP4,1,1},//�����������                                               
 {0xC112,IMP4,1,1},//����ʱ��                                                     
 {0xC113,IMP4,1,1},//ѭ��ʱ��                                                     
 {0xC114,IMP4,1,1},//A����ʾ��Ŀ��                                                
 {0XC115,IMP4,1,1},//����[Э�����ʾ]С��λ[��Χ ��2��3]                          
 {0xC116,IMP4,1,1},//����&����[��ʾ]С��λ [��ʾС��λΪ2��3��4��Э��̶�Ϊ4] 
 {0xC117,IMP4,2,1},//�Զ��������� 
 {0XC118,IMP4,1,1},//���ɴ�����                        
 {0xC119,IMP4,4,1},//�й���ʼ����
 {0xC11A,IMP4,4,1},//�޹���ʼ����
 
 //{0xC121,IMP1,1,1},//�����������--ͬC111-C117����˲���                                               
 //{0xC122,IMP1,1,1},//����ʱ��                                                     
 //{0xC123,IMP1,1,1},//ѭ��ʱ��                                                     
 //{0xC124,IMP1,1,1},//A����ʾ��Ŀ��                                                
 //{0xC125,IMP1,1,1},//����[Э�����ʾ]С��λ[��Χ ��2��3]                          
 //{0xC126,IMP1,1,1},//����&����[��ʾ]С��λ [��ʾС��λΪ2��3��4��Э��̶�Ϊ4] 
 //{0xC127,IMP1,2,1},//�Զ���������                                                 
 {0xC128,IMP4,2,1},//B����ʾ��Ŀ��                                                
 {0xC129,IMP4,2,1},//����Լ�״̬��Ϣ��        
                          
 {0xC211,IMP4,2,1}, //���������                                         
 {0xC213,IMP4,12,1},//��ѹ�ϸ��ʲ���                                         
 {0xC214,IMP4,1,1}, //�û�����1��2��3                                      
 {0xC215,IMP4,1,1}, //��բ��ʱ                                               
 {0XC216,IMP4,1,1}, //��բ��ʱ                                               
 {0XC217,IMP4,1,1}, //�����������
 
 {0xC310,IMP4,1,1}, //��1����ʱ����P��12                                
 {0xC311,IMP4,1,1}, //��1����ʱ�α���q��8                               
 {0xC312,IMP4,1,1}, //��1����ʱ����m��14                                
 {0xC313,IMP4,1,1}, //��1�׷�����k��8                                   
 {0XC314,IMP4,1,1}, //��1�׹�����������90          
 {0xC315,IMP4,1,1}, //��1�������ղ��õ�ʱ�α��    
 {0xC316,IMP4,1,1}, //��1��������״̬�֣�����¼B8��                    
 
 {0xC32F,IMP4,3*MAX_YEAR_PERIODS,1}, //��1����ʱ��                                                  

 {0xC33F,IMP4,3*MAX_DATE_PERIODS,1}, //��1�׵�1ʱ�α�                                     
 {0xC34F,IMP4,3*MAX_DATE_PERIODS,1}, //��1�׵�2ʱ�α�                                    
 {0xC35F,IMP4,3*MAX_DATE_PERIODS,1}, //��1�׵�3ʱ�α�                                     
 {0xC36F,IMP4,3*MAX_DATE_PERIODS,1}, //��1�׵�4ʱ�α�
 {0xC37F,IMP4,3*MAX_DATE_PERIODS,1}, //��1�׵�5ʱ�α�                                                                           
 {0xC38F,IMP4,3*MAX_DATE_PERIODS,1}, //��1�׵�6ʱ�α�                                     
 {0xC39F,IMP4,3*MAX_DATE_PERIODS,1}, //��1�׵�7ʱ�α�                                     
 {0xC3AF,IMP4,3*MAX_DATE_PERIODS,1}, //��1�׵�8ʱ�α�
 {0xC3BF,IMP4,3*MAX_DATE_PERIODS,1}, //��1�׵�9ʱ�α�
 {0xC3CF,IMP4,3*MAX_DATE_PERIODS,1}, //��1�׵�10ʱ�α�
 {0xC3DF,IMP4,3*MAX_DATE_PERIODS,1}, //��1�׵�11ʱ�α�
 {0xC3EF,IMP4,3*MAX_DATE_PERIODS,1}, //��1�׵�12ʱ�α�

 
 {0xC41F,IMP4,45,1}, //��1�׵�1-13���������� 
 //{0xC41E,IMP1,3,1}, //�����ղ�����ʱ�α��  
 {0xC42F,IMP4,45,1}, //��1�׵�16-30���������� 
 {0xC43F,IMP4,45,1}, //��1�׵�31-45���������� 
 {0xC44F,IMP4,45,1}, //��1�׵�46-60���������� 
 {0xC45F,IMP4,45,1}, //��1�׵�61-75���������� 
 {0xC46F,IMP4,45,1}, //��1�׵�76-90����������
 
 {0xC510,IMP4,4,1},//���ɼ�¼��ʼʱ��       
 {0xC511,IMP4,2,1},//��������1�����ݼ�¼���
 {0xC512,IMP4,2,1},//��������2�����ݼ�¼���
 {0xC513,IMP4,2,1},//��������3�����ݼ�¼���
 {0xC514,IMP4,2,1},//��������4�����ݼ�¼���
 {0xC515,IMP4,2,1},//��������5�����ݼ�¼���
 {0xC516,IMP4,2,1},//��������6�����ݼ�¼���

 {0xC51A,IMP4,2,1},//�����Чʱ��       
 {0xC51B,IMP4,1,1},//ʧѹ�ж�ʱ��
 {0xC51C,IMP4,1,1},//ʧ���ж�ʱ��
 {0xC51D,IMP4,1,1},//�����ж�ʱ��


 {0xC610,IMP4,9,15},//A����0-15����ʾ
 {0xC620,IMP4,9,15},//A����16-30����ʾ
 {0xC630,IMP4,9,15},//A����31-45����ʾ
 {0xC640,IMP4,9,15},//A����46-60����ʾ

 {0xC650,IMP4,9,15},//B����0-15����ʾ
 {0xC660,IMP4,9,15},//B����16-30����ʾ
 {0xC670,IMP4,9,15},//B����31-45����ʾ
 {0xC680,IMP4,9,15},//B����46-60����ʾ
 {0xC690,IMP4,9,15},//B����61-75����ʾ
 {0xC6A0,IMP4,9,15},//B����76-90����ʾ
 {0xC6B0,IMP4,9,15},//B����91-105����ʾ
 {0xC6C0,IMP4,9,15},//B����106-120����ʾ
 {0xC6D0,IMP4,9,15},//B����121-135����ʾ
 {0xC6E0,IMP4,9,15},//B����136-150����ʾ

 {0xC712,IMP4,45,1},//ͨѶ��Լ�汾��(�μ����QG/OKRW013��2005,  QG/OKRW004.7-2004) 
 //{0xC713,IMP4,1,1}, //������Ƿ��ڹ���״̬��д�˳�����״̬
 
 {0xC91F,IMP4,36,1},//���й���ʼ������  ���ܺ�8���ַ��ʣ�
 {0xC92F,IMP4,36,1},//���й���ʼ������                   
 {0xC93F,IMP4,36,1},//1�����޹���ʼ������                
 {0xC94F,IMP4,36,1},//2�����޹���ʼ������                
 {0xC95F,IMP4,36,1},//3�����޹���ʼ������                
 {0xC96F,IMP4,36,1},//4�����޹���ʼ������                
                                                                                                          
 {0xCA10,IMP4,4,1},//ʧѹ�ж���ֵ                
 {0xCA11,IMP4,4,1},//ʧ���ж���ֵ                
 {0xCA12,IMP4,1,1},//��������л�  (����¼9)                                                          
 {0xCA13,IMP4,5,1},//���������л�ʱ��                                                                 
 {0xCA14,IMP4,2,1},//��ǰ�׷���,ִ�з���(����¼9)                                                     
 {0xCA15,IMP4,6,1},//�û�Ȩ�޿����֣�����¼10��  
 {0xCA16,IMP4,3,1},//�й������޶�                                                                      
 {0xCA17,IMP4,3,1},//���ڹ����޶�                 
 {0xCA18,IMP4,1,1},//��������� 
 {0xCA19,IMP4,3,1},//������ֵ 
 {0xCA1A,IMP4,1,1},//ģʽ��9                
 //{0xCA1B,IMP1,1,1},//�ڿ�״̬
 
 {0xCB10,IMP4,1,1},//��2����ʱ����P��12           
 {0xCB11,IMP4,1,1},//��2����ʱ�α���q��8          
 {0xCB12,IMP4,1,1},//��2����ʱ����m��14                                                              
 {0xCB13,IMP4,1,1},//��2�׷�����k��8                                                                 
 {0xCB14,IMP4,1,1},//��2�׹�����������90                                                             
 {0xCB15,IMP4,1,1},//��2�������ղ��õ�ʱ�α��    
 {0xCB16,IMP4,1,1},//��2��������״̬�֣�����¼B8��
 
 {0xCB2F,IMP4,3*MAX_YEAR_PERIODS,1}, //��2����ʱ��                                                    

 {0xCB3F,IMP4,3*MAX_DATE_PERIODS,1}, //��2�׵�1ʱ�α�                                     
 {0xCB4F,IMP4,3*MAX_DATE_PERIODS,1}, //��2�׵�2ʱ�α�                                    
 {0xCB5F,IMP4,3*MAX_DATE_PERIODS,1}, //��2�׵�3ʱ�α�                                     
 {0xCB6F,IMP4,3*MAX_DATE_PERIODS,1}, //��2�׵�4ʱ�α�
 {0xCB7F,IMP4,3*MAX_DATE_PERIODS,1}, //��2�׵�5ʱ�α�                                                                           
 {0xCB8F,IMP4,3*MAX_DATE_PERIODS,1}, //��2�׵�6ʱ�α�                                     
 {0xCB9F,IMP4,3*MAX_DATE_PERIODS,1}, //��2�׵�7ʱ�α�                                     
 {0xCBAF,IMP4,3*MAX_DATE_PERIODS,1}, //��2�׵�8ʱ�α�
 {0xCBBF,IMP4,3*MAX_DATE_PERIODS,1}, //��2�׵�9ʱ�α�
 {0xCBCF,IMP4,3*MAX_DATE_PERIODS,1}, //��2�׵�10ʱ�α�
 {0xCBDF,IMP4,3*MAX_DATE_PERIODS,1}, //��2�׵�11ʱ�α�
 {0xCBEF,IMP4,3*MAX_DATE_PERIODS,1}, //��2�׵�12ʱ�α� 
 
 {0xCC1F,IMP4,45,1}, //��2�׵�1-15���������� 
 //{0xCC1E,IMP1,3,1}, //�����ղ�����ʱ�α�� 
 {0xCC2F,IMP4,45,1}, //��2�׵�16-30���������� 
 {0xCC3F,IMP4,45,1}, //��2�׵�31-45���������� 
 {0xCC4F,IMP4,45,1}, //��2�׵�46-60���������� 
 {0xCC5F,IMP4,45,1}, //��2�׵�61-75���������� 
 {0xCC6F,IMP4,45,1}, //��2�׵�76-90���������� 

 //У����ز���,�����-----
 {ADJ_METER_PUL_VOL_CUR_SPEC,IMP0,3,1},//���塢��ѹ���������,3�ֽ�
 {ADJ_METER_PARA_STATUS,IMP0,1,1},//У�����״̬����
 {ADJ_METER_A_POW,IMP0,3,12},//ABC���๦�ʡ���λ����ѹ��������

 {0xE400,IMP3,10+1,ADJ_TIME_EVENT_NUM},//ǰ100��Уʱ�¼���¼��ע4��
 {0xE900,IMP3,149+1,3},//ǰ3���������¼��ע17��
 {0xE910,IMP3,86+1,10},//ǰ10��A��ʧѹ��¼��ע1��
 {0xE920,IMP3,86+1,10},//ǰ10��B��ʧѹ��¼��ע1��
 {0xE930,IMP3,86+1,10},//ǰ10��C��ʧѹ��¼��ע1��
 {0xE940,IMP3,86+1,10},//ǰ10��AB��ʧѹ��¼��ע1��
 {0xE950,IMP3,86+1,10},//ǰ10��AC��ʧѹ��¼��ע1��
 {0xE960,IMP3,86+1,10},//ǰ10��BC��ʧѹ��¼��ע1��
 {0xE970,IMP3,86+1,10},//ǰ10��ABC��ʧѹ��¼��ע1��
 {0xE980,IMP3,74+1,10},//ǰ10��Aʧ����¼��ע2��
 {0xE990,IMP3,74+1,10},//ǰ10��Bʧ����¼��ע2��
 {0xE9A0,IMP3,74+1,10},//ǰ10��Cʧ����¼��ע2��
 {0xE9B0,IMP3,74+1,10},//ǰ10��ABʧ����¼��ע2��
 {0xE9C0,IMP3,74+1,10},//ǰ10��ACʧ����¼��ע2��
 {0xE9D0,IMP3,74+1,10},//ǰ10��BCʧ����¼��ע2��

 {0xEA00,IMP3,42+1,10},//ǰ10��A�෴���¼��ע3��//��Լ �����д�
 {0xEA10,IMP3,42+1,10},//ǰ10��B�෴���¼��ע3��//��Լ �����д�
 {0xEA20,IMP3,42+1,10},//ǰ10��C�෴���¼��ע3��//��Լ �����д�
 
 {0xEA30,IMP3,10+1,10},//ǰ10��ȫʧѹ��¼��ע4��//��Լ �����д�
 {0xEA40,IMP3,10+1,10},//ǰ10��A������¼��ע4��//��Լ �����д�
 {0xEA50,IMP3,10+1,10},//ǰ10��B������¼��ע4��//��Լ �����д�
 {0xEA60,IMP3,10+1,10},//ǰ10��C������¼��ע4��//��Լ �����д�
 {0xEA70,IMP3,10+1,10}, //ǰ10�ε�ѹ�������¼��ע4��//��Լ �����д�
 
 {0xEA80,IMP3,13+1,10}, //ǰ10��A���ѹ���ϸ����޼�¼��ע5��
 {0xEA90,IMP3,13+1,10}, //ǰ10��B���ѹ���ϸ����޼�¼��ע5��
 {0xEAA0,IMP3,13+1,10}, //ǰ10��C���ѹ���ϸ����޼�¼��ע5��
 {0xEAB0,IMP3,13+1,10}, //ǰ10��A���ѹ���ϸ����޼�¼��ע5��
 {0xEAC0,IMP3,13+1,10}, //ǰ10��B���ѹ���ϸ����޼�¼��ע5��
 {0xEAD0,IMP3,13+1,10}, //ǰ10��C���ѹ���ϸ����޼�¼��ע5��
 {0xEAE0,IMP3,13+1,10}, //ǰ10�γ�����������¼��ע6��
 {0xEAF0,IMP3,8+1,10}, //ǰ10�γ�������բ��¼��ע7��

 {0xEB20,IMP3,10+1,10}, //ǰ10�����µ��¼��ע4��
 {0xEB30,IMP3,5+1,10}, //ǰ10�θ�λ��¼(ע8)
 {0xEB40,IMP3,38+1,10}, //ǰ10��ͨѶ��������¼��ע9�� 
 {0xEB50,IMP3,38+1,10}, //ǰ10���ֶ���������¼��ע9��
 {0xEB60,IMP3,5+1,10}, //ǰ10��ǰ10������̼�¼��ע8�� 
 {0xEB70,IMP3,5+1,10}, //ǰ10�����ѹ�ϸ��ʼ�¼��ע8�� 
 {0xEB80,IMP3,78+1,10}, //���ó�ʼ������¼��ע10��
 {0xEB90,IMP3,7+1,10}, //���ó�ʼ������¼��ע10��
 {0xEBA0,IMP3,5+1,10}, //ǰ10�ο��˸Ǽ�¼��ע8��--->�޸�Ϊ����ǣ�Ҳ���ǿ��ϸǣ���������,��Լ�����д��޸�֮
 {0xEBB0,IMP3,5+1,10}, //ǰ10�ο�Ǧ���ż�¼��ע8��
 {0xEBC0,IMP3,10+1,10}, //ǰ10��ʱ�ӵ��Ƿѹ��¼��ע4��
 {0xEBD0,IMP3,10+1,10}, //ǰ10�ε͹��ĵ��Ƿѹ��¼��ע4��
 {0xEBE0,IMP3,10+1,10}, //ǰ10��Уʱ��¼��ע4��
 {0xEBF0,IMP3,11+1,10}, //ǰ10������ʱ���Ҽ�¼��ע12�� 
 
 {0xEC00,IMP3,11+1,10}, //ǰ10���ϵ�ʱ���Ҽ�¼��ע12�� 
 {0xEC20,IMP3,6+1,10}, //ǰ10��EEPROM����¼��ע14��
 {0xEC30,IMP3,6+1,10}, //ǰ10��У���¼(ע14)
 {0xEC40,IMP3,10+1,ALL_LOSS_CUR_EVENT_NUM}, //ǰ100��ȫʧ����¼��ע4��
 /*
 {0xEC50,IMP3,10,10}, 
 {0xEC60,IMP3,10,10}, 
 {0xEC70,IMP3,10,10}, 
 {0xEC80,IMP3,10,10}, 
 {0xEC90,IMP3,10,10}, 
 {0xECA0,IMP3,10,10}, 
 {0xECB0,IMP3,10,10}, 
 {0xECC0,IMP3,10,10}, 
 {0xECD0,IMP3,10,10}, 
 */                     
 
 {0xED00,IMP3,6+1,1}, //ǰ1�ε�������ʱ�估���ͣ�ע16��
 {0xED01,IMP3,36+1,12}, //ǰ1�ε�������ǰ��ĵ��ܣ�ע16��  
 {0xED10,IMP3,6+1,1}, //ǰ2�ε�������ʱ�估���ͣ�ע16��
 {0xED11,IMP3,36+1,12}, //ǰ2�ε�������ǰ��ĵ��ܣ�ע16��
 {0xED20,IMP3,6+1,1}, //ǰ3�ε�������ʱ�估���ͣ�ע16��
 {0xED21,IMP3,36+1,12}, //ǰ3�ε�������ǰ��ĵ��ܣ�ע16��
 
 {0xED30,IMP3,13+1,10}, //ǰ10��A���ѹ��¼��ע5��
 {0xED40,IMP3,13+1,10}, //ǰ10��B���ѹ��¼��ע5��
 {0xED50,IMP3,13+1,10}, //ǰ10��C���ѹ��¼��ע5��
 {0xED60,IMP3,21+1,20}, //ǰ20���ܵ������������¼��ע18��
 //{0xED70,IMP3,21,10}, //ǰ10-20���ܵ������������¼��ע18��
 {0xED90,IMP3,5+1,10}, //ǰ10�ο��˸ǽ�����¼��ע8��--->�޸�Ϊ����ǣ�Ҳ���ǿ��ϸǣ���������,��Լ�����д��޸�֮
 {0xEDA0,IMP3,5+1,10}, //ǰ10�ο�Ǧ���Ž�����¼��ע8��
 {0xEDB0,IMP3,5+1,10}, //ǰ1�ο������ʼ��¼��ע8��---->�޸�Ϊ���˸�,��Լ�����д��޸�֮
 {0xEDC0,IMP3,5+1,10}, //ǰ10�ο���ǽ�����¼��ע8��---->�޸�Ϊ���˸�,��Լ�����д��޸�֮
 {0xEDD0,IMP3,5+1,10}, //ǰ10�ο�����������ʼ��¼��ע8��
 {0xEDE0,IMP3,5+1,10}, //ǰ10�ο��������Ž�����¼��ע8��
 
 //{0xEF00,IMP1,122,1},//��ǰ�������ݼ�˲ʱ��
 {0xEF01,IMP1,127,1},//����������ݼ�����˲ʱ��
 //{0xEF02,IMP1,144,1},//��ǰ�������޹�����
 {0xEF03,IMP1,149,1},//�����������޹�����
 /*
 {0xED80,IMP3,175,12}, //ǰ12��ָ������������ݼ�����˲ʱ����ע19��(����) 
 {0xED90,IMP3,175,12}, //ǰ12��˲ʱ����������ݼ�����˲ʱ����ע19��(����)
 {0xEDA0,IMP3,175,12}, //ǰ12��Լ������������ݼ�����˲ʱ����ע19��(����)
 {0xEDB0,IMP3,175,13}, //ǰ13�ν��������ڰ��춳�������ע19��(����)
 {0xEDC0,IMP3,13,13}, //ǰ14-26�ν��������ڰ��춳�������ע19��(����)
 */

//ʧѹ�ۼ�
{ OCCUR_TOTAL_LOSS_VOL,IMP7,LOSS_VOL_DATA_LEN,8},
{ TOTAL_TOTAL_LOSS_VOL,IMP7,LOSS_VOL_DATA_LEN,8},
//ȫʧѹ
{ OCCUR_ALL_LOSS_VOL,IMP7,ALL_LOSS_VOL_DATA_LEN,1},
{ TOTAL_ALL_LOSS_VOL,IMP7,ALL_LOSS_VOL_DATA_LEN,1},
//ʧ���ۼ�                               
{ OCCUR_TOTAL_LOSS_CUR,IMP7,LOSS_CUR_DATA_LEN,7}, 
{ TOTAL_TOTAL_LOSS_CUR,IMP7,LOSS_CUR_DATA_LEN,7},
//ȫʧ��
{ OCCUR_ABC_LOSS_CUR,IMP7,ALL_LOSS_CUR_DATA_LEN,1},
{ TOTAL_ABC_LOSS_CUR,IMP7,ALL_LOSS_CUR_DATA_LEN,1}, 

//����
{ OCCUR_TOTAL_NEG_CUR,IMP7,NEG_CUR_DATA_LEN,4},  
{ TOTAL_TOTAL_NEG_CUR,IMP7 ,NEG_CUR_DATA_LEN,4},  
//����                              
{ OCCUR_TOTAL_BREAK_VOL,IMP7, BREAK_VOL_DATA_LEN,4},
{ TOTAL_TOTAL_BREAK_VOL,IMP7, BREAK_VOL_DATA_LEN,4},

 STORA_EXTEND

 {CHK_IMP0,IMP0,1,1}, //IMPÿ�����ݵĲ����� 
 {CHK_IMP1,IMP1,1,1},
 {CHK_IMP2,IMP2,1,1},
 {CHK_IMP3,IMP3,1,1},
 {CHK_IMP4,IMP4,1,1},
 {CHK_IMP5,IMP5,1,1},
 {CHK_IMP6,IMP6,1,1},
 {CHK_IMP7,IMP7,1,1}
};

//��鳬������������Ƿ������ˣ����Ϸ���1�����򷵻�0
INT8U Check_SuperPSW_Jump()
{
  return 1;  
}

//���Imp_Flag��־�ĺϷ��ԣ���ȷ����1�����򷵻�0
INT8U Check_Imp_Flag(INT8U Imp_Flag)
{
  if(Imp_Flag<=IMP7)
    return 1;
  else
    return 0;
}
//��ȡĳ���洢��������������Ҫ��־
INT8U Get_Storage_Data_ImpFlag(STORA_DI DI)
{
  INT16U i;
  
  for(i=0;i<S_NUM(Data_Para_Storage);i++)
  {
    if(Data_Para_Storage[i].DI==DI ||\
      (Data_Para_Storage[i].Num>1 && Data_Para_Storage[i].DI<DI && DI<Data_Para_Storage[i].DI+Data_Para_Storage[i].Num))
    {
      return Data_Para_Storage[i].Imp_Flag;
    }
  }
  ASSERT(A_WARNING,0);
  return NULL_IMP;
}

//��ȡĳ���洢��������Ĵ洢ƫ�ƣ���ƫ�Ʊ�ʾ����������ͬImp_Flag�����еĴ洢Ʒƫ��
//Ҳ��ʾ���߼��洢���е�����ƫ��
INT32U Get_Storage_Data_Off(STORA_DI DI)
{
  INT16U i;
  INT32U Offset=0;
  INT8U Imp_Flag,Re;
  
  Imp_Flag=Get_Storage_Data_ImpFlag(DI);
  Re=Check_Imp_Flag(Imp_Flag);
  ASSERT(A_WARNING,0!=Re);
  
  for(i=0;i<S_NUM(Data_Para_Storage);i++)
  {
    if(Data_Para_Storage[i].DI==DI)
    {
      return Offset;
    }
    else if(Data_Para_Storage[i].Num>1 && Data_Para_Storage[i].DI<DI && DI<Data_Para_Storage[i].DI+Data_Para_Storage[i].Num)
    {
      Offset+=(Data_Para_Storage[i].Len+ROM_CS_BYTES)*(DI-Data_Para_Storage[i].DI);
      return Offset;     
    }
    else
    {
      if(Data_Para_Storage[i].Imp_Flag==Imp_Flag)//����ƫ��
      {
        //if(Data_Para_Storage[i].Num==1)
         // Offset+=Data_Para_Storage[i].Len+ROM_CS_BYTES; 
        //else
          Offset+=(Data_Para_Storage[i].Len+ROM_CS_BYTES)*Data_Para_Storage[i].Num;
    
      }
    }
  }

  DEBUG_PRINT(HUCK,DEBUG_0,"Get_Storage_Data_Off Error,Data 0x%x Not Found\r\n",DI);
  return NULL_4BYTES; 
}

//��ȡĳ���洢��������ĳ���,DIֻ����Data_Para_Storage�ж��������
INT16U Get_Storage_Data_Len(STORA_DI DI)
{
  INT16U i;
  
  for(i=0;i<S_NUM(Data_Para_Storage);i++)
  {
    if(Data_Para_Storage[i].DI==DI ||\
       (Data_Para_Storage[i].Num>1 &&\
        Data_Para_Storage[i].DI<DI &&\
        Data_Para_Storage[i].DI+Data_Para_Storage[i].Num>DI))
    {
      return Data_Para_Storage[i].Len;
    }
  }
  ASSERT(A_WARNING,0);
  return 0;  
}

//��ȡĳ��Imp_Flag��Ҫ�ȼ����ݵ��������ݳ���Get_Imp_Data_Size�ķ���ֵӦ��<=Get_Imp_Mem_Size
INT32U Get_Imp_Data_Size(INT8U Imp_Flag)
{
  INT8U Re;
  INT16U i;
  INT32U Size=0;
  
  Re=Check_Imp_Flag(Imp_Flag);
  ASSERT(A_WARNING,Re!=0);
  for(i=0;i<S_NUM(Data_Para_Storage);i++)
  {
    if(Data_Para_Storage[i].Imp_Flag==Imp_Flag)
    {
      Size+=((INT32U)Data_Para_Storage[i].Len+ROM_CS_BYTES)*Data_Para_Storage[i].Num;
    }
  }
  ASSERT(A_WARNING,Size!=0);
  return Size;
}

//��÷����ĳ��Imp_Flag�ȼ������ݵĴ洢�ռ��С
INT32U Get_Imp_Mem_Size(INT8U Imp_Flag)
{
  INT16U i,j;
  INT32U Size=0;//����һ�������ڵ�size
  INT8U Re;
  
  Re=Check_Imp_Flag(Imp_Flag);
  ASSERT(A_WARNING,Re!=0);
  
  for(i=0;i<S_NUM(Data_Mem_Map);i++)
  {
    if(Data_Mem_Map[i].Imp_Flag==Imp_Flag)//���ҵ������ڴ�ӳ����еĶ�Ӧ��
    {
      Size=0xFFFFFFFF;//����һ������ֵ
      for(j=0;j<IMP_LOG_MEM;j++)
      { 
        if(Data_Mem_Map[i].LOG_Mem[j]!=NULL_LOG_MEM)
        {
         //�ҳ���С��һ��Log_Mem���Ƿ�������ݵĴ洢�ռ��С
         if(Get_LOG_Mem_Size(Data_Mem_Map[i].LOG_Mem[j])<Size)
           Size=Get_LOG_Mem_Size(Data_Mem_Map[i].LOG_Mem[j]);
        }
      }
      break;
    }
  }
  //ASSERT(A_WARNING,Size!=0 && Size!=0xFFFFFFFF);
  if(0==Size || 0xFFFFFFFF==Size)
  {
    DEBUG_PRINT(HUCK,DEBUG_0,"Imp%d Data Mem_map error",Imp_Flag);
  } 
  return Size; 
}

//�Ӵ洢���ж�ȡĳ����Ҫ�ȼ�������
//Imp_Flag����ʾ���ݵ���Ҫ�ȼ���־
//Offset,��ʾ�����ڴ洢���е�ƫ��
//pDst����ʾ���ݶ�ȡ���Ŀ��ָ��
//RD_Len����ʾ��Ҫ��ȡ�����ݵĳ���
//pDst_Start��DstLenyһ���pDst��RD_Len�ķ�Χ����Լ��
//����NO_ERR��ʾ�ɹ�
INT8U Read_Imp_Data(INT8U Imp_Flag,INT32U Offset,void *pDst,INT16U RD_Len,void *pDst_Start,INT16U DstLen)
{
  INT16U i,j;
  INT32U Sum;
  INT8U Re;

  Re=Check_Imp_Flag(Imp_Flag);
  ASSERT(A_WARNING,Re!=0);
  ASSERT(A_WARNING,(INT8U *)pDst>=(INT8U *)pDst_Start && (INT8U *)pDst+RD_Len<=(INT8U *)pDst_Start+DstLen);
  
  for(i=0;i<S_NUM(Data_Mem_Map);i++)
  {
    if(Data_Mem_Map[i].Imp_Flag==Imp_Flag)//�ҵ������ڴ�ӳ����еĶ�Ӧ��
    {
      for(j=0;j<IMP_LOG_MEM;j++)//��ȡ�洢���߼��洢��
      {
        if(j!=0)//ǰһ�ζ�ȡû�гɹ� ������ʱһ�£���ֹ��Ϊ���߸��ų�����
          OS_TimeDly_Ms(10);
        
        if(Data_Mem_Map[i].LOG_Mem[j]!=NULL_LOG_MEM)//�ҵ�һ���洢�����ݵ��߼��洢��
        {
          //�����߼��洢���е�����
          Re=Read_LOG_Mem(Data_Mem_Map[i].LOG_Mem[j],Offset,pDst,RD_Len,pDst_Start,DstLen);
          if(ASSERT(A_WARNING,NO_ERR==Re)) //ȷ��������ȷ
            continue;
          //��У���
          Re=Read_LOG_Mem(Data_Mem_Map[i].LOG_Mem[j],Offset+RD_Len,&Sum,ROM_CS_BYTES,&Sum,sizeof(Sum));
          if(ASSERT(A_WARNING,NO_ERR==Re))
            continue;
          //���У����Ƿ���ȷ
          if(Check_Sum(pDst,RD_Len,&Sum,ROM_CS_BYTES))//У�����ȷ��ֱ�ӷ���NO_ERR�����������ȡ�¸�LOG_MEM
            return NO_ERR;
          else
            continue; 
        }
      }
      ASSERT(A_WARNING,0);
      return RD_IMP_DATA_ERR;
    }
  }
  ASSERT(A_WARNING,0);
  return RD_IMP_DATA_ERR;
}

//�Ӵ洢���ж�ȡĳ����Ҫ�ȼ�������
//Imp_Flag����ʾ���ݵ���Ҫ�ȼ���־
//Offset,��ʾ�����ڴ洢���е�ƫ��
//pDst����ʾ���ݶ�ȡ���Ŀ��ָ��
//RD_Len����ʾ��Ҫ��ȡ�����ݵĳ���
//pDst_Start��DstLenyһ���pDst��RD_Len�ķ�Χ����Լ��
//����NO_ERR��ʾ�ɹ�
INT8U PD_Read_Imp_Data(INT8U Imp_Flag,INT32U Offset,void *pDst,INT16U RD_Len,void *pDst_Start,INT16U DstLen)
{
  INT16U i,j;
  INT32U Sum;
  INT8U Re;

  Power_Down_Check();
  
  Re=Check_Imp_Flag(Imp_Flag);
  ASSERT(A_WARNING,Re!=0);
  ASSERT(A_WARNING,(INT8U *)pDst>=(INT8U *)pDst_Start && (INT8U *)pDst+RD_Len<=(INT8U *)pDst_Start+DstLen);
  
  for(i=0;i<S_NUM(Data_Mem_Map);i++)
  {
    if(Data_Mem_Map[i].Imp_Flag==Imp_Flag)//�ҵ������ڴ�ӳ����еĶ�Ӧ��
    {
      for(j=0;j<IMP_LOG_MEM;j++)//��ȡ�洢���߼��洢��
      {
        if(Data_Mem_Map[i].LOG_Mem[j]!=NULL_LOG_MEM)//�ҵ�һ���洢�����ݵ��߼��洢��
        {
          Re=Read_LOG_Mem(Data_Mem_Map[i].LOG_Mem[j],Offset,(void *)Pub_Buf,RD_Len+ROM_CS_BYTES,(void *)Pub_Buf,sizeof(Pub_Buf));
          if(ASSERT(A_WARNING,NO_ERR==Re)) //ȷ��������ȷ
            continue;
          Sum=0;
          mem_cpy(&Sum,(INT8U *)Pub_Buf+RD_Len,ROM_CS_BYTES,&Sum,sizeof(Sum));
          if(Check_Sum(pDst,RD_Len,&Sum,ROM_CS_BYTES))//У�����ȷ��ֱ�ӷ���NO_ERR�����������ȡ�¸�LOG_MEM
          {
            mem_cpy(pDst,(void *)Pub_Buf,RD_Len,pDst_Start,DstLen);
            return NO_ERR;
          }
          else
            continue; 
        }
      }
      ASSERT(A_WARNING,0);
      return RD_IMP_DATA_ERR;
    }
  }
  ASSERT(A_WARNING,0);
  return RD_IMP_DATA_ERR;
}
//��ĳ����Ҫ��־������д�뵽�洢����
//Imp_Flag����ʾ���ݵ���Ҫ�ȼ���־
//Offset,��ʾ�����ڴ洢���е�ƫ��
//pSrc����ʾ���ݵ���ʼָ��
//SrcLen����ʾ���ݵĳ���
//����NO_ERR��ʾд�ɹ�
//����WR_IMP_DATA_ERR��ʾд����ʧ��
INT8U Write_Imp_Data(INT8U Imp_Flag,INT32U Offset,void *pSrc,INT16U SrcLen)
{
  INT8U i,j;
  INT8U Re;
  INT32U Sum;
  INT8U Err_Flag=0;
  
  Power_Down_Check();
  
  Re=Check_Imp_Flag(Imp_Flag);
  ASSERT(A_WARNING,Re!=0);
  Set_Sum(pSrc,SrcLen,&Sum,ROM_CS_BYTES,&Sum,sizeof(Sum));//����У���
  
  for(i=0;i<S_NUM(Data_Mem_Map);i++)
  {
    if(Data_Mem_Map[i].Imp_Flag==Imp_Flag)
    {
      Err_Flag=0;//ֻҪ�ɹ���һ�ξ� Err_Flag|=1;
      for(j=0;j<IMP_LOG_MEM;j++)
      { 
        if(j!=0 && Err_Flag==0)//ǰһ��û��д�ɹ�������ʱһ����д
          OS_TimeDly_Ms(10);
        
        if(Data_Mem_Map[i].LOG_Mem[j]!=NULL_LOG_MEM)
        {
          Re=Write_LOG_Mem(Data_Mem_Map[i].LOG_Mem[j],Offset,pSrc,SrcLen);//д����
          ASSERT(A_WARNING,NO_ERR==Re);
          if(NO_ERR==Re)
          {
            Re=Write_LOG_Mem(Data_Mem_Map[i].LOG_Mem[j],Offset+SrcLen,&Sum,ROM_CS_BYTES);//дУ���
            ASSERT(A_WARNING,NO_ERR==Re);
            if(NO_ERR==Re)
              Err_Flag|=1;
          }
        }
      }
      if(Err_Flag!=0)//����д�ɹ���һ��
        return NO_ERR;
      else 
        return WR_IMP_DATA_ERR;
    }
  }
  ASSERT(A_WARNING,0);
  return WR_IMP_DATA_ERR;
}

//��ĳ����Ҫ��־������д�뵽�洢����
//Imp_Flag����ʾ���ݵ���Ҫ�ȼ���־
//Offset,��ʾ�����ڴ洢���е�ƫ��
//pSrc����ʾ���ݵ���ʼָ��
//SrcLen����ʾ���ݵĳ���
//����NO_ERR��ʾд�ɹ�
//����WR_IMP_DATA_ERR��ʾд����ʧ��
INT8U PD_Write_Imp_Data(INT8U Imp_Flag,INT32U Offset,void *pSrc,INT32U SrcLen)
{
  INT8U i,j;
  INT8U Re;
  INT32U Sum;
  INT8U Err_Flag=0;
  
  Re=Check_Imp_Flag(Imp_Flag);
  ASSERT(A_WARNING,Re!=0);
  Set_Sum(pSrc,SrcLen,&Sum,ROM_CS_BYTES,&Sum,sizeof(Sum));//����У���
  mem_cpy((INT8U *)Pub_Buf,pSrc,SrcLen,(void *)Pub_Buf,sizeof(Pub_Buf));
  mem_cpy((INT8U *)Pub_Buf+SrcLen,&Sum,ROM_CS_BYTES,(void *)Pub_Buf,sizeof(Pub_Buf));
  
  for(i=0;i<S_NUM(Data_Mem_Map);i++)
  {
    if(Data_Mem_Map[i].Imp_Flag==Imp_Flag)
    {
      Err_Flag=0;//ֻҪ�ɹ���һ�ξ� Err_Flag|=1;
      for(j=0;j<IMP_LOG_MEM;j++)
      { 
        if(Data_Mem_Map[i].LOG_Mem[j]!=NULL_LOG_MEM)
        {
          Re=Write_LOG_Mem(Data_Mem_Map[i].LOG_Mem[j],Offset,(void *)Pub_Buf,SrcLen+ROM_CS_BYTES);//д����
          ASSERT(A_WARNING,NO_ERR==Re);
          if(NO_ERR==Re)
              Err_Flag|=1;
        }
      }
      if(Err_Flag!=0)//����д�ɹ���һ��
        return NO_ERR;
      else 
        return WR_IMP_DATA_ERR;
    }
  }
  ASSERT(A_WARNING,0);
  return WR_IMP_DATA_ERR;
}

//��ȡ�洢���е�ĳ�����ݵĹ̶����ȣ�DI��ֵ�ɲο�Data_Para_Storage�Ķ���
//DI,��Ҫ��ȡ���������ʶ
//Offset,��ȡDI���ݵ���ʼƫ��
//Len,��Ҫ��ȡ�����ݳ���
//pDst��ʾ��ȡ������ŵ��û�����
//pDst_Start��DstLenһ��綨Ŀ�껺�����ķ�Χ
//*pErr��ʾ��ȡʧ��ʱ��ԭ��,NO_ERR��ʾ��ȡ�ɹ�,��������ԭ��μ�Pub_Err.h
//����ֵ����ȡ�����ݳ���,��ȡʧ��ʱ����0
INT16U Read_Storage_Data_Fix_Len(STORA_DI DI,INT16U Offset,INT16U Len,void *pDst,void *pDst_Start,INT16U DstLen,INT8U *pErr)
{
  INT32U Off;
  INT8U Imp_Flag;

  DEBUG_PRINT(HUCK,DEBUG_0,"Read Storage Data:0x%lx,Off=%d,Len=%d",DI,Offset,Len);
  
  if(ASSERT(A_WARNING,(INT8U *)pDst>=(INT8U *)pDst_Start && (INT8U *)pDst+Len<=(INT8U *)pDst_Start+DstLen))
    return 0;
  
  Imp_Flag=Get_Storage_Data_ImpFlag(DI);//��ȡ�����ݵ���Ҫ��־ 
 
  Off=Get_Storage_Data_Off(DI);//��ȡ����ƫ��
  if(ASSERT(A_WARNING,NULL_4BYTES!=Off))
  {
    *pErr=RD_STORAGE_DATA_DI_ERR;
    return 0;
  }
  
  Off+=Offset;//+�ڲ�ƫ��

  OS_Sem_Pend(PUB_RW_ROM_ID);//����дROM���ź���ID
  //if(Check_Power_Status()==POWER_ON_STATUS)
    *pErr=Read_Imp_Data(Imp_Flag,Off,pDst,Len,pDst_Start,DstLen);
  //else
    //*pErr=PD_Read_Imp_Data(Imp_Flag,Off,pDst,Len,pDst_Start,DstLen);
  OS_Sem_Post(PUB_RW_ROM_ID);//�ͷ�дROM���ź���ID
  if(NO_ERR==*pErr)
    return Len;
  else//���洢ʧ�����ȡĬ�ϲ���
  { 
    *pErr=RD_FIX_DATA_ERR;
    return 0;
  }
  //return 0;  
}

//д�洢���е�ĳ�����ݵĹ̶����ȣ�DI��ֵ�ɲο�Data_Para_Storage�Ķ���
//DI,��Ҫд���������ʶ
//Offset,дDI���ݵ���ʼƫ��
//SrcLen,��Ҫд�����ݳ���
//pSrc��ʾд��Դ���ݻ�����
//SrcLen��ʾԴ���ݵĳ���
//����NO_ERR��ʾ�ɹ���������ʾʧ��
INT8U Write_Storage_Data_Fix_Len(STORA_DI DI,INT16U Offset,void *pSrc,INT16U SrcLen)
{
  INT32U Off;
  INT8U Imp_Flag,Re;

  DEBUG_PRINT(HUCK,DEBUG_0,"Write Storage Data:0x%lx,Off=%d,Len=%d",DI,Offset,SrcLen);
  
  Imp_Flag=Get_Storage_Data_ImpFlag(DI);//��ȡ�����ݵ���Ҫ��־ 
  
  Off=Get_Storage_Data_Off(DI);//��ȡ����ƫ��
  if(ASSERT(A_WARNING,NULL_4BYTES!=Off))
  {
    return WR_STORAGE_DATA_DI_ERR;
  }
  
  Off+=Offset;//+�ڲ�ƫ��
  OS_Sem_Pend(PUB_RW_ROM_ID); 
  //if(Check_Power_Status()==POWER_ON_STATUS)
    Re=Write_Imp_Data(Imp_Flag,Off,pSrc,SrcLen);
  //else
    //Re=PD_Write_Imp_Data(Imp_Flag,Off,pSrc,SrcLen);    
  OS_Sem_Post(PUB_RW_ROM_ID);

  //OS_TimeDly_Ms(20);//��ʱ20ms
  
  if(NO_ERR==Re)
    return NO_ERR;
  else//���洢ʧ�����ȡĬ�ϲ���
  { 
    return WR_FIX_DATA_ERR;
  }
 
}


//��ȡ�洢���е�ĳ�����ݣ�DI��ֵ�ɲο�Data_Para_Storage�Ķ���
//DI,��Ҫ��ȡ���������ʶ
//pPara���ڶ�ȡĳЩ����������ʱ��Ҫ�Ĳ���������HIS_ENERGY,HIS_DEMAND,HIS_DEMAND_TIMEʱ��Ҫ����ʱ�����
//ʱ������ĸ�ʽ��������pPara[0]-pPara[4]�ֱ��Ƿ֡�ʱ���ա��¡���,��������¸ò���������
//pDst��ʾ��ȡ������ŵ��û�����
//pDst_Start��DstLenһ��綨Ŀ�껺�����ķ�Χ
//*pErr��ʾ��ȡʧ��ʱ��ԭ��,NO_ERR��ʾ��ȡ�ɹ�,��������ԭ��μ�Pub_Err.h
//����ֵ����ȡ�����ݳ���,��ȡʧ��ʱ����0
INT16U Read_Storage_Data(STORA_DI DI,void *pDst,void *pDst_Start,INT16U DstLen,INT8U *pErr)
{
  INT16U Len,Len1;
  
  //Clear_CPU_Dog();    //��CPU�ڲ����Ź�
  //Clear_Ext_Dog();    //��CPU�ⲿ���Ź�
  
  //Cur_Task_ID=Get_Cur_Task_ID();
  //DEBUG_PRINT(HUCK,DEBUG_0,"Read Storage Data:0x%lx",DI,Tcb[Cur_Task_ID].Name);
  Len=Get_Storage_Data_Len(DI);
  if(Len>0)
  {
    //OS_TimeDly_Ms(20);//��ʱ���������񣬷�ֹĳ�����������������ռ��CPU
    Len1=Read_Storage_Data_Fix_Len(DI,0,Len,pDst,pDst_Start,DstLen,pErr);
    if(ASSERT(A_WARNING,Len==Len1 && NO_ERR==*pErr))
    {
      Len1=Read_Def_Para(DI,pDst,Len,pDst_Start,DstLen);
      DEBUG_PRINT(HUCK,DEBUG_0,"Read_Def_Para,Len = %u",Len1);
      if(ASSERT(A_WARNING,Len1==Len))
      {
        *pErr=RD_STORAGE_DATA_DI_ERR;
        return 0; 
      }
      else
      {
        *pErr=NO_ERR;
        return Len;        
      }
    }
    else
    {
      *pErr=NO_ERR;
      return Len;
    }
  }
  else
  {
    ASSERT(A_WARNING,0);
    *pErr=RD_STORAGE_DATA_DI_ERR;
    return 0; 
  }
}

//��洢����дĳ�����ݣ�DI��ֵ�ɲο�Data_Para_Storage�Ķ���
//DI,��Ҫд���������ʶ
//pPara����дĳЩ����������ʱ��Ҫ�Ĳ���������HIS_ENERGY,HIS_DEMAND,HIS_DEMAND_TIMEʱ��Ҫ����ʱ�����
//ʱ������ĸ�ʽ��������pPara[0]-pPara[4]�ֱ��Ƿ֡�ʱ���ա��¡���,��������¸ò���������
//pSrc��ʾд���ݵ�Դ������
//����ֵ��NO_ERR��ʾ�ɹ���������ʾʧ��
INT8U Write_Storage_Data(STORA_DI DI,void *pSrc,INT16U SrcLen)
{
  volatile INT16U Len;
  INT8U Re;

  //Cur_Task_ID=Get_Cur_Task_ID();
  //DEBUG_PRINT(HUCK,DEBUG_0,"Write Storage Data:0x%lx",DI,Tcb[Cur_Task_ID].Name);
  //��ȡ���Ƚ����ݳ���
  Len=Get_Storage_Data_Len(DI);
  if(ASSERT(A_WARNING,Len==SrcLen))
  {
    DEBUG_PRINT(HUCK, DEBUG_0, "WR_Data_Err DI=0x%lx, Len=%d, WR_Len=%d", DI, Len, SrcLen);
    return WR_STORAGE_DATA_LEN_ERR;
  }
  //дImp����
  //OS_Sem_Pend(PUB_RW_ROM_ID);//����дROM���ź���ID
  Re=Write_Storage_Data_Fix_Len(DI,0,pSrc,SrcLen);
  //OS_Sem_Post(PUB_RW_ROM_ID);//�ͷŸ��ź���
  if(ASSERT(A_WARNING,NO_ERR==Re))
    return Re;
  return NO_ERR;  
}

//���洢ӳ���Ƿ����,��Ҫ�Ǽ��
void Check_Storage_Map()
{
  INT8U i,j,Count;
  INT32U Size;
  
  //Re=Check_Mem_Map();
  //ASSERT(A_WARNING,NO_ERR==Re);//����ڴ���������ӳ���Ƿ���ȷ
  //Get_Imp_Data_Size(IMP0);
  for(i=0;i<S_NUM(Data_Mem_Map);i++)
  {
    Count=0;
    Size=Get_Imp_Data_Size(Data_Mem_Map[i].Imp_Flag);
    for(j=0;j<IMP_LOG_MEM;j++)
    {
      if(Data_Mem_Map[i].LOG_Mem[j]!=NULL_LOG_MEM)
      {
         if(Get_LOG_Mem_Size(Data_Mem_Map[i].LOG_Mem[j])>=Size)
           Count++;
         else
           ASSERT(A_WARNING,0);

      }
    }
    ASSERT(A_WARNING,(Data_Mem_Map[i].Imp_Flag==IMP5 && Count>=1)||\
                     (Data_Mem_Map[i].Imp_Flag!=IMP5 && Count>=2));//ÿ������������2���洢�ռ�,������һ������,�����������������
  }
  
}

//�������Ĵ洢��
INT8U Check_Imp_Data_Storage()
{
  INT8U i,j,Count,Test,Re,Re1,Err;
  INT32U DataSize,MemSize;
  
  Re = NO_ERR;
  Clr_Ext_Inter_Dog();
  //�ȼ������ÿ��Imp_Flag�����ݵ��߼��洢���Ĵ�С�͸����Ƿ�Ϸ�
  DEBUG_PRINT(HUCK,DEBUG_0,"----PHY_IMP_LOG_MEM Map Check Start!----");
  for(i=0;i<S_NUM(Data_Mem_Map);i++)
  {
    Count=0;
    DataSize=Get_Imp_Data_Size(Data_Mem_Map[i].Imp_Flag);
    DEBUG_PRINT(HUCK,DEBUG_0,"Imp%d Data size=%ld",Data_Mem_Map[i].Imp_Flag,DataSize); 

    for(j=0;j<IMP_LOG_MEM;j++)
    {
      if(Data_Mem_Map[i].LOG_Mem[j]!=NULL_LOG_MEM)
      {         
        MemSize = Get_LOG_Mem_Size(Data_Mem_Map[i].LOG_Mem[j]);
        DEBUG_PRINT(HUCK,DEBUG_0,"----Log_Mem%d size=%ld",Data_Mem_Map[i].LOG_Mem[j],MemSize);        
        if(MemSize>=DataSize)
         Count++;
        else
        {
         DEBUG_PRINT(HUCK,DEBUG_0,"!!!!Log_Mem%d have not enough space!",Data_Mem_Map[i].Imp_Flag,Data_Mem_Map[i].LOG_Mem[j]); 
         Re |= IMP_DATA_STORAGE_ERR;
        }
      }
    }

    if((Count==0))
    {
      DEBUG_PRINT(HUCK,DEBUG_0,"Imp%d Data do not have enough LOG Mems",Data_Mem_Map[i].Imp_Flag);
      Re |= IMP_DATA_STORAGE_ERR;
    }
  }
 
  DataSize=0;
  MemSize=0;
  for(j=0;j<S_NUM(Data_Mem_Map);j++)
  {
    i=Data_Mem_Map[j].Imp_Flag;
    DataSize=Get_Imp_Data_Size(i);
    MemSize=Get_Imp_Mem_Size(i);
    DEBUG_PRINT(HUCK,DEBUG_0,"IMP%d Data_size=%ld,Mem_Size=%ld",i,DataSize,MemSize);
    if(DataSize>=MemSize)
    {
      DEBUG_PRINT(HUCK,DEBUG_0,"IMP%d Data Mem not enough space!",i);
      Re |= IMP_DATA_STORAGE_ERR;
    }
  }
  
  //��ÿ��IMP�����ݽ���һ�ζ���д����������
  for(i=0;i<S_NUM(Data_Mem_Map);i++)
  {
    Test=0x5A;
    Re1=Write_Storage_Data(CHK_IMP0+i,&Test,1);
    if(NO_ERR==Re1)
    {
      Test=0;
      Re1=Read_Storage_Data(CHK_IMP0+i,&Test,&Test,sizeof(Test),&Err);
      if(0!=Re1 && NO_ERR==Err && 0x5A==Test)
        continue;
    }
    DEBUG_PRINT(HUCK,DEBUG_0,"IMP%d Data write && read test error",i);
    Re |= IMP_DATA_STORAGE_ERR;
  }
  
  DEBUG_PRINT(HUCK,DEBUG_0,"----PHY_IMP_LOG_MEM Map Check End!----");
  return Re;
}

//��ӡ������Ϣ�������ݵĴ洢��ַ�ͳ��ȴ�ӡ����
void Debug_Print_Data_Storage()
{
  INT8U Imp_Flag;
  INT16U i,j;
  INT8U Num;
  INT16U Addr,Len;
  
  DEBUG_PRINT(HUCK,DEBUG_0,"PRINT Data_Para_Storage Info-------------");
  for(Imp_Flag=IMP0;Imp_Flag<IMP5;Imp_Flag++)
  {
    for(i=0;i<S_NUM(Data_Para_Storage);i++)
    {
      if(Data_Para_Storage[i].Imp_Flag==Imp_Flag)
      {
        if(Data_Para_Storage[i].Num==0)
          Num=1;//Data_Para_Storage[i].Num+1;
        else
          Num=Data_Para_Storage[i].Num;
        
        for(j=0;j<Num;j++)
        {
          Addr=Get_Storage_Data_Off(Data_Para_Storage[i].DI+j);
          Len=Data_Para_Storage[i].Len;
          DEBUG_PRINT(HUCK,DEBUG_0,"DI:0x%x,Addr:%d,Len:%d",\
                                   Data_Para_Storage[i].DI+j,\
                                   Addr,\
                                   Len);
        }
      } 
    }
  }
}

//��������洢ϵͳ�Ƿ���ȷ
void Check_Sys_Storage()
{
  INT8U Re;
  
  if(Check_Meter_Factory_Status())
  {
    DEBUG_PRINT(HUCK,DEBUG_0,"------System Storage_SelfCheck Start!-----");
    //����洢����д���
    //����߼�������洢��֮���ӳ��
    //���IMP�����ݵĴ洢ӳ��
    //���Protocol_Data�Ĵ洢ӳ��
    Re = NO_ERR;
    
    Re |= Check_PHY_Mem();
    Re |= Check_LOG_Mem_Map();
    Re |= Check_Imp_Data_Storage();
    Re |= Check_Protocol_Data_Storage();
    if(Re == NO_ERR)
    {
      DEBUG_PRINT(HUCK,DEBUG_0,"------System Storage_SelfCheck Succeed!-----");
    }
    else
    {
      DEBUG_PRINT(HUCK,DEBUG_0,"------System Storage_SelfCheck failed!-----");
    }      
  }
}

#undef DATA_PARA_C

