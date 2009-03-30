#ifndef PUB_DEBUG_H
#define PUB_DEBUG_H

#include "Pub.h"

#undef EXT
#ifdef PUB_DEBUG_C
#define EXT
#else
#define EXT extern
#endif

//���������Ϣ�����ʽ
#define PRINT_NULL  0 //�����
#define PRINT_STDIO 1 //��׼I/O���
#define PRINT_UART  2 //�������

#define DEBUG_PRINT(x,y,...) Debug_Print(__VA_ARGS__)

#define PRINT_TYPE PRINT_UART //�ݶ�Ϊ��׼IO���

//�����ӡ����ʱ�Ĵ�ӡ��ʽ
#define PRINT_HEX 0 //16���ƴ�ӡ
#define PRINT_DEC 1 //10���ƴ�ӡ

//���������Ϣ����Ҫ�ȼ�
#define DEBUG_0 0
#define DEBUG_1 1
#define DEBUG_2 2
#define DEBUG_3 3 

//���������Ϣ�����ID,�޸Ĵ˴�ʱ��ע���޸�PARA_ID_NUM
#define ASSERT_ID 0
#define TEST 1
#define HUCK 2
#define SUCK 3
#define PUCK 4
#define LUCK 5

#define A_RST 0 //��ʾ�����е������������Ļ�����λ
#define A_WARNING 1//��ʾ�����������������Ļ���ֻ���������Ϣ��Ȼ�󷵻�1

//�������,���ʹ�ã���������
//#define ASSERT(x,y) Assert(x,(y),__FILE__,__FUNCTION__,__LINE__)


EXT INT16U DEBUG_PRINT(INT8U ID,INT8U Debug_Flag,char *format,...);
EXT INT8U DEBUG_BUF_PRINT(INT8U Src[],INT16U SrcLen,INT8U Flag,INT8U Num);
#endif
