#ifndef PUB_H
#define PUB_H

#undef EXT
#ifdef PUB_C
#define EXT
#else
#define EXT extern
#endif

#define SYS_TRUE 1
#define SYS_FALSE 0

#define EQ ==
//#define NO_INIT //__no_init

//����ṹ�����ݰ��ֽڶ���Ŀ�ʼ�ͽ�����
//ʹ������:
//
//DATA_PACKED_BEGIN//�����￪ʼ����Ľṹ�嶼���ֽڶ���� 
//
//...������Ҫ�ֽڶ���Ľṹ��
//
//DATA_PACKED_END//�����濪ʼ�Ľṹ�嶼�ָ�ԭ�еĶ��뷽ʽ
//
#define DATA_PACKED_BEGIN
#define DATA_PACKED_END

#define CONST const

#define NULL_1BYTES 0xFF
#define NULL_2BYTES 0xFFFF
#define NULL_4BYTES 0xFFFFFFFF

#define NULL_STORA_DI 0xFFFFFFFF
#define NULL_PROTO_DI 0xFFFF

//����ĳ�ṹ���Ա��Ըýṹ����ʼλ�õ�ƫ��
#define S_OFF(X,Y) ((INT32U)(&(((X *)0)->Y)))//���һ���ṹ���ƫ��

//ȡ��һ���ṹ����������ĳ�Ա����,XΪ�ṹ���������
#define S_NUM(X) (sizeof(X)/sizeof(X[0]))

//��������ĳ�������ĺ귽��
#define SET_VAR(X,Y,X_START,X_LEN) do{ASSERT(A_WARNING,((INT8U *)&(X))>=(INT8U *)(X_START) && ((INT8U *)&(X))<(INT8U *)(X_START)+X_LEN);X=Y;}while(0)

//�������x=y/z,���ڲ��ж�Z!=0
#define DIV(x,y,z) do{ASSERT(z!=0);x=y/z;}while(0)

//Ϊ�˱�֤Buf����ʼ��ַ��ż����ַ��Head��Tail����ΪINT16U��
#define DECLARE_BUF_TYPE(Type,Len,Name) typedef struct{\
                                          INT16U Head;\
                                          Type Buf[Len];\
                                          INT16U Tail;\
                                          }Name

#define DECLARE_VAR_TYPE(Type,Name) typedef struct{\
                                      INT8U Head;\
                                      Type Var;\
                                      INT8U Tail;\
                                      }Name;

//�������Ӧ����Ҫ�ĺ���
#define ASSERT(x,y) OS_ASSERT(y)

#define SET_BIT(x,y) (x)|=0x01<<(y)
#define CLR_BIT(x,y) (x)&=~(0x01<<(y))
#define GET_BIT(x,y) (((x)>>(y))&0x01)

//��ĳ��������ֵ,���뱣֤�ñ����ںϷ��ķ�Χ
//��ĳ���������±���������ָ�븳ֵ,Ҫ�������º�,�Ա���Ի�������д���
//����ͨ��ָ���Test_Bufд����
//for(i=0;i<100;i++)
// Set_Var(Test_Buf[i],0xaa,Test_Buf,sizeof(Test_Buf))//��ͬ��Test_Buf[i]=0xaa;
#define Set_Var(x,value,start_addr,x_len)\
do\
{  ASSERT((OS_INT8U *)&(x)>=(OS_INT8U *)(start_addr) && (OS_INT8U *)&(x)+sizeof(value)<=(OS_INT8U *)(start_addr)+x_len);\
   x=value;\
}while(0)

//�������x=y/z,���ڲ��ж�Z!=0
#define DIV(x,y,z) do{ASSERT(z!=0);x=y/z;}while(0)

#define STR(x) #x

//���ڴ���صĲ�������������º������Ա�֤�������д���
//�ڴ���غ���
#define mem_set OS_memset
#define mem_cpy OS_memcpy

//У����غ���
#define Check_Sum OS_Check_Sum
#define Set_Sum OS_Set_Sum

//ȫ�ֱ�����ȫ�����ýṹ��Ķ��巽ʽ�����Ҹýṹ���CS����,����:
//typedef struct
//{
//  INT8U a;
//  ...
//  INT8U CS[CS_BYTES];
//}S_test;
//�ڶ�ȡ�ṹ�����ǰ��ʹ�ýṹ����麯�������ýṹ���Ƿ�Ϸ�
//�޸���ýṹ�����ݺ�ʹ�����ü���ͺ�������CS��
//�Խṹ���У����غ���

#define DATA_READY 0x5AA56734
#define SET_DATA_READY_FLAG(Var) do{Var.Data_Ready_Flag=DATA_READY;}while(0)
#define RESET_DATA_READY_FLAG(Var) do{Var.Data_Ready_Flag=0;}while(0)

#define Check_STRUCT_Sum OS_Check_STRUCT_Sum
#define Set_STRUCT_Sum OS_Set_STRUCT_Sum

#define CHECK_STRUCT_SUM(Var) OS_Check_STRUCT_Sum((void *)&(Var),sizeof(Var),(OS_INT8U *)(Var.CS),sizeof(Var.CS))
#define SET_STRUCT_SUM(Var) OS_Set_STRUCT_Sum((void *)&(Var),sizeof(Var),(OS_INT8U *)(Var.CS),sizeof(Var.CS))
//����ĳ���ṹ�������ʱ����
#define SET_STRUCT_TIME(Var,Tim)  do{ASSERT(A_WARNING,sizeof(Tim)==sizeof(S_HEX_Time));\
                                  mem_cpy((void *)&(Var.Time),(void *)&(Tim),sizeof(Tim),(void *)&(Var.Time),sizeof(Var.Time));\
                                    SET_STRUCT_SUM(Var);}while(0)

#define CHECK_STRUCT_VAR(Var) ((CHK_BYTE==Var.Head  && CHK_BYTE==Var.Tail)?1:0)
#define INIT_STRUCT_VAR(Var)  do{Var.Head=CHK_BYTE;Var.Tail=CHK_BYTE;}while(0)

//��������
typedef unsigned long int INT32U;
typedef long int INT32S;
typedef unsigned int INT16U;
typedef int INT16S;
typedef unsigned char INT8U;
typedef char INT8S;
typedef float FP32S;
typedef double FD32S;

typedef unsigned int PROTO_DI;
typedef unsigned long int STORA_DI;

//�����λѰַ���ֽ�����
typedef struct
{
  INT8U Bit0:1;
  INT8U Bit1:1;
  INT8U Bit2:1;
  INT8U Bit3:1;
  INT8U Bit4:1;
  INT8U Bit5:1;
  INT8U Bit6:1;
  INT8U Bit7:1;	
}S_Bit;

//�����ֽ���λ����������
typedef union 
{
  S_Bit Bit;
  INT8U Byte;
}U_Byte_Bit;

DECLARE_BUF_TYPE(INT8U,400,S_Pub_Buf0);
DECLARE_VAR_TYPE(INT8U,S_Int8U);
DECLARE_VAR_TYPE(INT16U,S_Int16U);
DECLARE_VAR_TYPE(INT32U,S_Int32U);
/*
tpedef struct
{
  INT8U Head;  
  INT8U Buf[200];
  INT8U Tail;
}S_Pub_Buf0;
*/

typedef struct
{
  INT8U Head;
  INT32U Sec_Timer;
  INT32U Ms10_Timer;
  INT32U Ms_Timer;  
  INT8U Tail;
}S_Pub_Timer;

EXT volatile S_Pub_Timer Pub_Timer;

#define Sec_Timer_Pub Pub_Timer.Sec_Timer
#define Ms10_Timer_Pub Pub_Timer.Ms10_Timer
#define Ms_Timer_Pub Pub_Timer.Ms_Timer
/*
EXT volatile INT32U Sec_Timer_Pub;
EXT volatile INT32U Ms10_Timer_Pub;
EXT volatile INT32U Ms_Timer_Pub;
*/
#define MAX_SIZE(a,b,c) ((a)>(b)?(a):(b))>(c)?((a)>(b)?(a):(b)):(c)


//EXT volatile INT16U Pub_Buf0[200];//������Ҫ��buf�ĵط�ʹ�ø�buf
EXT volatile S_Pub_Buf0 _Pub_Buf0;
#define Pub_Buf0 _Pub_Buf0.Buf

EXT INT8U Check_BCD_Data(void *pBCD,INT16U Len);

EXT INT8U GetBufSum_Pub(INT8U Src[],INT16U Src_Len);

EXT void Hex2Bcd(INT32U Data,INT8U *pDst,INT16U Len,INT8U *pDst_Start,INT16U DstLen);
EXT void S_Hex2Bcd(INT32S Data,INT8U *pDst,INT16U Len,INT8U *pDst_Start,INT16U DstLen);
EXT INT32U Bcd2Hex(INT8U Src[],INT8U SrcLen);
EXT INT8U Bcd2Hex_Byte(INT8U Byte);
EXT INT8U Hex2Bcd_Byte(INT8U Byte);
EXT void Bcd_Dec(INT8U Type,INT8U *pData0,INT8U *pData1,INT8U *pDst,INT8U Len,INT8U *pDst_Start,INT16U DstLen);
EXT void Hex2Bcd_Buf(void *pSrc,INT16U SrcLen,void *pDst,void *pDst_Start,INT16U DstLen);
EXT void Bcd2Hex_Buf(void *pSrc,INT16U SrcLen,void *pDst,void *pDst_Start,INT16U DstLen);

#endif