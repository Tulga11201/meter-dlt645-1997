#ifndef METER_CFG_H
#define METER_CFG_H

#ifdef METER_CFG_C
#define EXT
#else
#define EXT extern
#endif

//#define TEST_MODE

#define CS_BYTES          2//�ڴ�����Ҫ���ݽṹ���CS�ֽ���  
#define ROM_CS_BYTES      2//ROM�д洢���ݵ�У����ֽ���
#define MAX_RATES         8///��������
#define HIS_ENERGY_DATA_MONTHS  13//������ʷ���ݵ��·���,��ò�Ҫ����12��
#define HIS_DEMAND_DATA_MONTHS  13
#define HIS_VOLSTAT_DATA_MONTHS 3//��ʷ��ѹͳ�����ݵı�������
#define LOAD_DATA_NUM        8000//�洢�ĸ�����������

#define USE_ENERGY_RAM_BAK   1//�Ƿ����ڴ���ʹ��һ�ݵ������ݵı���

#define MAX_YEAR_PERIODS   12//�����ʱ����,��ʱ����ʾ��һ���Ϊ����ʱ���
#define MAX_DATE_TABLES     8//�����ʱ�α���,��ʱ�α�ʾ��һ��ֳɼ���ʱ���
#define MAX_DATE_PERIODS   14//ÿ��ʱ�α����ʱ����
#define MAX_YEAR_HOLIDAYS  90//ÿ����ʱ�����Ӧ�����ڼ�����,Ӧ��Ϊ15�ı���

#define ADJ_TIME_EVENT_NUM 50
#define ALL_LOSS_CUR_EVENT_NUM 50

#define SOFT_VERSION {0x11,0x14,0x24,0x04,0x09}
#endif
