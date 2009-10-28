
#ifndef CHANNEL_CVS
#define CHANNEL_CVS

#ifndef CHANNEL_C
#define CHANNEL_EXT  extern
#else
#define CHANNEL_EXT 
#endif


#define MIN_FRAME_PROCO_SIZE  11  //Э����С�ֽ���
#define MAX_UART_REC_SIZE UART3_RX_BUFF_MAXSIZE

 //��ȡͨ��������ID
#define DI_CHANEL_485_1      COMM_BAUD0    //��һ·485
#define DI_CHANEL_485_2      COMM_BAUD1    //�ڶ�·485


//����ͨ�����壬��Const_Uart_Attib[MAX_UART_NUM] ���Ӧ
#define CHANEL_IRDA     UART0           //����ͨ������---------UART0
#define CHANEL_485_1    UART2           //485ͨ������---------UART2
#define CHANEL_485_2    UART3           //485ͨ������---------UART3
#ifdef UART1
#define CHANEL_MOUDEL   UART1           //ģ��ͨ������---------UART1
#endif

#define  CHANEL_MIN CHANEL_IRDA
#define  CHANEL_MAX (MAX_UART_NUM-1)


#define BAUD_IRDA    1200            //����ڲ�����,
#define CHANEL_DEBG  CHANEL_IRDA    //���Կ�ͨ����
#define BAUD_DEBG    115200         //���Կڲ�����,
#define BAUD_MOUDLE  19200         //ģ��ڲ�����,



typedef struct
{  
  INT32U  Baud;
  INT8U ExitFlag;  
  INT8U CS[CS_BYTES]; 
}CHANEL_PARA;
CHANNEL_EXT  CHANEL_PARA Chanel_Para[CHANEL_MAX+1];

//CHANNEL_EXT  INT32U Com_Delay_Count;

INT8U Get_Buf_MulitByte_Sum(INT8U *Src,INT16U SrcLen,INT8U ByteGroup,INT8U *Dst,INT8U DstLen);
INT8U  Send_HostData_Public_Puck(INT8U Channl,INT8U *Srcbuf,INT16U Src_Len);
INT16U  Get_HostData_Public_Puck(INT8U *Channl);

INT8U  Debug_Out_Public_Puck(INT8U *Srcbuf,INT16U Src_Len);
void Init_DebugChanel_PUCK(INT8U);
void Close_DebugChanel_PUCK(INT8U FacFlag);
void Init_Debug_Uart(void);
void Init_All_UART(INT32U Mode);
void Channel_Switch_PUCK(INT32U Mode);
void Init_Channel_Sram(void);
void Channel_Data_Proc_PUCK(INT32U Status);
#endif
