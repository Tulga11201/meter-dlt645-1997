#ifndef MEM_CFG_H
#define MEM_CFG_H

//����洢������
#define PHY_MEM0 0 //512 EEROM
#define PHY_MEM1 1 //32K EEROM
#define PHY_MEM2 2 //32K EEROM
#define PHY_MEM3 3 //32K EEROM
#define PHY_MEM4 4 //8K FRAM
#define PHY_MEM5 5 //2M FLASH

//ÿ���洢��Ԥ��10���ֽ����ڲ���
#define MEM_TEST_BYTES 10L

#define PHY_MEM0_SIZE (512L-MEM_TEST_BYTES)
#define PHY_MEM1_SIZE (32*1024L-MEM_TEST_BYTES)
#define PHY_MEM2_SIZE (32*1024L-MEM_TEST_BYTES)
#define PHY_MEM3_SIZE (32*1024L-MEM_TEST_BYTES)
#define PHY_MEM4_SIZE (8*1024L-MEM_TEST_BYTES)
#define PHY_MEM5_SIZE (2000*1024L-MEM_TEST_BYTES)

//�߼��洢�����壬ÿ���߼��洢������һ������洢����һƬ�����ռ���
#define NULL_LOG_MEM 0xFF//����һ�������ڵĴ洢�� 

//��PHY_MEM0��
#define LOG_MEM0 0//���ڴ洢�������������õĲ���������У������Ͳ���ģʽ��,IMP0������

//��PHY_MEM1��
#define LOG_MEM1 1//���ڴ洢�������������õĲ���������У������Ͳ���ģʽ�ֵ�һ������,IMP0������
#define LOG_MEM2 2//���ڴ洢��ǰ��Ҫ�������ݺͲ�����,IMP1������
#define LOG_MEM3 3//���ڴ洢��ʷ�����������ݵ�,IMP2������

//��PHY_MEM2��
#define LOG_MEM4 4//���ڴ洢�������������õĲ���������У������Ͳ���ģʽ�ֵ�һ������,IMP0������
#define LOG_MEM5 5//���ڴ洢��ǰ��Ҫ�������ݺͲ����ȵ�һ������,IMP1������
#define LOG_MEM6 6//���ڴ洢��ǰ��Ҫ�������ݺͲ����ȵ�һ������,IMP1������

//��PHY_MEM3��
#define LOG_MEM7 7//���ڴ洢�¼���¼


//��PHY_MEM4��
#define LOG_MEM8 8//���ڴ洢�¼���¼��һ������
#define LOG_MEM9 9//���ڴ洢����洢������,IMP4������

//��PHY_MEM5��
#define LOG_MEM10 10//���ڴ洢�������������õĲ���������У������Ͳ���ģʽ�ֵ�һ������
#define LOG_MEM11 11//���ڴ洢��ʷ�����������ݵȵ�һ������,IMP2������
#define LOG_MEM12 12//���ڴ洢��ʷ�����������ݵȵ�һ������,IMP2������
#define LOG_MEM13 13//���ڴ洢�������������õĲ���������У������Ͳ���ģʽ�ֵ�һ������

//���ڴ洢��Ҫ����
#define LOG_MEM14 14//��PHY_MEM1��
#define LOG_MEM15 15//��PHY_MEM2��
#define LOG_MEM16 16//��PHY_MEM5��
#define LOG_MEM17 17//��PHY_MEM5��
#define LOG_MEM18 18//��PHY_MEM5��

#define LOG_MEM19 19//���ڴ洢��������

#define LOG_MEM20 20//���ڴ洢��Ҫ�¼���¼
#define LOG_MEM21 21//���ڴ洢��Ҫ�¼���¼�ı���

/************************�������߼��ڴ��������Ϣ**********************/
//��PHY_MEM0��
#define LOG_MEM0_START 0
#define LOG_MEM0_SIZE (PHY_MEM0_SIZE)               //�������������õĲ���,�洢IMP0������


//��PHY_MEM1��
#define LOG_MEM1_START 0
#define LOG_MEM1_SIZE (LOG_MEM0_SIZE)              //�������������õĲ�����һ������,�洢IMP0������ 

#define LOG_MEM2_START (LOG_MEM1_START+LOG_MEM1_SIZE)    
#define LOG_MEM2_SIZE 3000 //������������������Ҫ����,�洢IMP1������

#define LOG_MEM3_START (LOG_MEM2_START+LOG_MEM2_SIZE)
#define LOG_MEM3_SIZE 20000L //���ڴ洢��ʷ�����������ݵ�

#define LOG_MEM14_START (LOG_MEM3_START+LOG_MEM3_SIZE)
#define LOG_MEM14_SIZE 8000//���ڴ洢��Ҫ����IMP4������

//��PHY_MEM2��
#define LOG_MEM4_START 0
#define LOG_MEM4_SIZE (LOG_MEM0_SIZE)              //�������������õĲ�����һ������,�洢IMP0������ 

#define LOG_MEM5_START (LOG_MEM4_START+LOG_MEM4_SIZE)
#define LOG_MEM5_SIZE LOG_MEM2_SIZE //������������������Ҫ���ݵı���,�洢IMP1������

#define LOG_MEM6_START (LOG_MEM5_START+LOG_MEM5_SIZE)
#define LOG_MEM6_SIZE LOG_MEM2_SIZE //������������������Ҫ���ݵı���,�洢IMP1������

#define LOG_MEM15_START (LOG_MEM6_START+LOG_MEM6_SIZE)
#define LOG_MEM15_SIZE (PHY_MEM2_SIZE-LOG_MEM15_START)//���ڴ洢��Ҫ����,IMP4������

//��PHY_MEM3��
#define LOG_MEM7_START 0
#define LOG_MEM7_SIZE (PHY_MEM3_SIZE-8200)      //���ڴ洢�¼���¼

#define LOG_MEM20_START (LOG_MEM7_START+LOG_MEM7_SIZE)//���ڴ洢��Ҫ�¼���¼,IMP7������
#define LOG_MEM20_SIZE 4100

#define LOG_MEM21_START (LOG_MEM20_START+LOG_MEM20_SIZE)//���ڴ洢��Ҫ�¼���¼�ı���,IMP7������
#define LOG_MEM21_SIZE 4100

//��PHY_MEM4��
//#define LOG_MEM8_START 0
//#define LOG_MEM8_SIZE PHY_MEM4_SIZE/2

#define LOG_MEM9_START 0//(LOG_MEM8_START+LOG_MEM8_SIZE)
#define LOG_MEM9_SIZE PHY_MEM4_SIZE //�洢IMP4������,������洢������

//��PHY_MEM5��
#define LOG_MEM10_START 0
#define LOG_MEM10_SIZE LOG_MEM0_SIZE //����У�������IMP0������

#define LOG_MEM11_START (LOG_MEM10_START+LOG_MEM10_SIZE)
#define LOG_MEM11_SIZE LOG_MEM3_SIZE  //��ʷ�����������ݵı���

#define LOG_MEM12_START (LOG_MEM11_START+LOG_MEM11_SIZE)
#define LOG_MEM12_SIZE LOG_MEM3_SIZE  //��ʷ�����������ݵı���

#define LOG_MEM13_START (LOG_MEM12_START+LOG_MEM12_SIZE)
#define LOG_MEM13_SIZE LOG_MEM0_SIZE  //����У�������IMP0������

#define LOG_MEM16_START (LOG_MEM13_START+LOG_MEM13_SIZE)
#define LOG_MEM16_SIZE LOG_MEM14_SIZE  //��Ҫ����,IMP4������

#define LOG_MEM17_START (LOG_MEM16_START+LOG_MEM16_SIZE)
#define LOG_MEM17_SIZE LOG_MEM14_SIZE  //��Ҫ����,IMP4������

#define LOG_MEM18_START (LOG_MEM17_START+LOG_MEM17_SIZE)
#define LOG_MEM18_SIZE LOG_MEM14_SIZE  //��Ҫ����,IMP4������

#define LOG_MEM19_START (LOG_MEM18_START+LOG_MEM18_SIZE)
#define LOG_MEM19_SIZE (PHY_MEM5_SIZE-20000-LOG_MEM18_START)  //��������

/************************�������߼��ڴ��������Ϣ**********************/

//����洢����Ϣ
typedef struct
{
  INT8U MemNo;//����洢�����
  INT32U Mem_Addr;//�洢����ʼ��ַ
  INT32U Mem_Size;//�洢������
}S_PHY_Mem_Info;

//ϵͳ���߼��洢��Ϣ
typedef struct
{
  INT8U LOG_MemNo;//�߼��洢�����
  S_PHY_Mem_Info PHY_Mem_Info;//��Ӧ������洢����Ϣ
}S_LOG_Mem_Info;

#ifdef MEMORY_C
//��������洢����Ϣ
const S_PHY_Mem_Info Sys_PHY_Mem[]=
{
  {PHY_MEM0,0,PHY_MEM0_SIZE},
  {PHY_MEM1,0,PHY_MEM1_SIZE},
  {PHY_MEM2,0,PHY_MEM2_SIZE},
  {PHY_MEM3,0,PHY_MEM3_SIZE},
  {PHY_MEM4,0,PHY_MEM4_SIZE},
  {PHY_MEM5,0,PHY_MEM5_SIZE}
};

//�����߼��洢����Ϣ,λ���ĸ�����洢��������������洢���е���ʼλ�úʹ�С
const S_LOG_Mem_Info Sys_LOG_Mem[]=
{
  //PHY_MEM0��
  {LOG_MEM0,{PHY_MEM0,LOG_MEM0_START,LOG_MEM0_SIZE}},//
  //PHY_MEM1��
  {LOG_MEM1,{PHY_MEM1,LOG_MEM1_START,LOG_MEM1_SIZE}},
  {LOG_MEM2,{PHY_MEM1,LOG_MEM2_START,LOG_MEM2_SIZE}},
  {LOG_MEM3,{PHY_MEM1,LOG_MEM3_START,LOG_MEM3_SIZE}},
  {LOG_MEM14,{PHY_MEM1,LOG_MEM14_START,LOG_MEM14_SIZE}},
  //PHY_MEM2��
  {LOG_MEM4,{PHY_MEM2,LOG_MEM4_START,LOG_MEM4_SIZE}},
  {LOG_MEM5,{PHY_MEM2,LOG_MEM5_START,LOG_MEM5_SIZE}},
  {LOG_MEM6,{PHY_MEM2,LOG_MEM6_START,LOG_MEM6_SIZE}},
  {LOG_MEM15,{PHY_MEM2,LOG_MEM15_START,LOG_MEM15_SIZE}},
  //PHY_MEM3��
  {LOG_MEM7,{PHY_MEM3,LOG_MEM7_START,LOG_MEM7_SIZE}},
  {LOG_MEM20,{PHY_MEM3,LOG_MEM20_START,LOG_MEM20_SIZE}},
  {LOG_MEM21,{PHY_MEM3,LOG_MEM21_START,LOG_MEM21_SIZE}},
  //PHY_MEM4��
  //{LOG_MEM8,{PHY_MEM4,LOG_MEM8_START,LOG_MEM8_SIZE}},//�ô洢����ʱδ��
  {LOG_MEM9,{PHY_MEM4,LOG_MEM9_START,LOG_MEM9_SIZE}},
  //PHY_MEM5��
  {LOG_MEM10,{PHY_MEM5,LOG_MEM10_START,LOG_MEM10_SIZE}},
  {LOG_MEM11,{PHY_MEM5,LOG_MEM11_START,LOG_MEM11_SIZE}},
  {LOG_MEM12,{PHY_MEM5,LOG_MEM12_START,LOG_MEM12_SIZE}},
  {LOG_MEM13,{PHY_MEM5,LOG_MEM13_START,LOG_MEM13_SIZE}},
  
  {LOG_MEM16,{PHY_MEM5,LOG_MEM16_START,LOG_MEM16_SIZE}},
  {LOG_MEM17,{PHY_MEM5,LOG_MEM17_START,LOG_MEM17_SIZE}},
  {LOG_MEM18,{PHY_MEM5,LOG_MEM18_START,LOG_MEM18_SIZE}},
  {LOG_MEM19,{PHY_MEM5,LOG_MEM19_START,LOG_MEM19_SIZE}},
};

//ע�⣺Sys_PHY_Mem��Sys_LOG_Mem���������൱����ϵͳ�洢��������
//һ��ϵͳ������洢�ṹ�����仯������Ҫ�޸�Sys_PHY_Mem��Sys_LOG_Mem��������
//����޸ĺ�Ĵ洢�ֲ���С��������洢��Ҫ���������Ҫ�޸�Data_Mem_Map����
#endif
#endif

