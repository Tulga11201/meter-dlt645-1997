#ifndef DATA_TRANS_H
#define DATA_TRANS_H

#include "Authority.h"
#include "Demand.h"

#undef EXT
#ifdef DATA_TRANS_C
#define EXT
#else
#define EXT extern
#endif

#define CH_RS485_1  CHANEL_485_1//0//��һ·485
#define CH_RS485_2  CHANEL_485_2//1//�ڶ�·485
#define CH_MODULE   2//����ģ��
#define CH_IRAD     CHANEL_IRDA//3//����


#define MAX_SINGLE_DATA_LEN 10     //����DLT645��������ݳ���
#define MAX_DLT645_DATA_LEN 230    //DLT645��������󳤶�
#define AUTHORITY_FLAG 0x55aa55aa  //Ȩ�ޱ�־

#define SPEC_NO 0           //��������
#define SPEC_RATE 1         //���������,0xXXXX�е����һ��X����������
#define SPEC_HOLIDAY 2      //�ڼ������
#define SPEC_PHASE_ENERGY 3 //�������
#define SPEC_LOAD_DATA 4    //��������
#define SPEC_POW_DIRECT 5   //������������ʹ�õĹ��ʷ���
#define SPEC_CUR_TIME 6     //��ǰʱ���(����)
#define SPEC_DATE     7     //��ǰ����(������)
#define SPEC_TIME     8     //��ǰʱ��
#define SPEC_ADJ_CLR  9     //У����0
#define SPEC_FREEZE_DATA 10 //��������(��ǰ����)
#define SPEC_MULTI_DATA 11 
#define SPEC_CUMU_EVENT 12   //�ۼƵ������������

#define SPEC_PSW_LOCK   13   //����״̬��
#define SPEC_VOLSTAT    14   //��ѹͳ������
#define SPEC_BAUD       15   //������״̬��
#define SPEC_EVENT_TIME 16   //�¼�����ʱ��
#define SPEC_BAT_TIME   17   //��ع���ʱ��
#define SPEC_RD_ROM     18   //��ROM����
#define SPEC_YEAR_PERIOD 19 //��ʱ����
#define SPEC_DATE_PERIOD 20 //��ʱ�α�
#define SPEC_MULTI_EVENT 21 //�ִ��¼�
#define SPEC_SET_ENSTART 22 //���ó�ʼ����
#define SPEC_EXTEND      99 //��չ����

//���������Ϣ״̬��
#define ILLEGAL_DATA_ERR 0//�Ƿ�����
#define DI_ERR 1          //���ݱ�ʶ��
#define PSW_ERR 2         //�������
#define YEAR_PERIOD_ERR 4 //��ʱ������
#define DATE_PERIOD_ERR 5 //��ʱ������
#define RATES_NUM_ERR   6 //��������

//���û�ȡЭ�����ݵĺ���ʱ���Data_Flagֵ
#define FOR_DISP 1//��ʾΪ��ʾ
#define FOR_COMM 2//��ʾΪͨ��,���ܵ�С��λλ������Լ��
#define FOR_EVENT 4//��ʾΪ�¼�,����������ݶ�����������
#define FOR_SRC 8

#define CLEAR_ALL_FLAG     0x05AA5ABC//�����־
#define CLEAR_ENERGY_FLAG  0x0055AABB//�������־ 
#define CLEAR_DEMAND_FLAG  0xAABBCCDD//��������־
#define CLEAR_VOLSTAT_FLAG 0x11223344//���ѹͳ�Ʊ�־
#define CLEAR_EVENT_FLAG   0x33445566//���¼���־
#define CLEAR_END_FLAG     0x00000000//�����������־

//������������ʱ�ķ���ֵ
//#define SET_ERR 0           //����ʱ��������      
//#define SET_OK  1           //���óɹ�
//#define SET_NOT_SPEC_DATA 2 //����Set_DLT645_Spec_Data��������ʱ��ʾ���������������
//#define SET_NO_DATA 3
//#define SET_AUTH_ERR 4

//�����Լ����
#define PROTOCOL_DLT645 0 

typedef struct{
  INT8U Energy_Digs;
  INT8U Power_Digs;
  INT8U CS[CS_BYTES];
}S_Disp_Digs;//���幦�ʺ͵��ܵ���ʾλ��

typedef struct{
  INT8U Addr[3][6];
  INT8U CS[CS_BYTES];
}S_Meter_Addr;

typedef struct
{
  INT8U Head;
  INT8U Ch;
  INT8U Tail;
}S_Cur_Comm_Ch;

//����Դ���ݴ洢����
#define S_RAM 0x00
#define S_ROM 0x01

///����Դ��������,ͨ��645������ʱ���ɸ���һ�������ж�,S_BCD���͵�����Ҫ��һ����BCD������
//�������BCD���ͼ��
#define S_INTS 0x01//�Ƿ��з���INT����
#define S_INTU 0x02//�Ƿ��޷���INT����
#define S_BCD  0x03//�Ƿ�ΪBCD����,���������Դ����->Ŀ������������и�ʽת��
#define S_BIN  0x04//������״̬��֮���

//����Դ���ݳ��� 
#define S_LEN8 0x08
#define S_LEN7 0x07
#define S_LEN6 0x06
#define S_LEN5 0x05
#define S_LEN4 0x04
#define S_LEN3 0x03
#define S_LEN2 0x02
#define S_LEN1 0x01

//����Ŀ��������ȡ��ʱ����ʼ�ֽ�
#define D_START4 0x04
#define D_START3 0x03
#define D_START2 0x02
#define D_START1 0x01
#define D_START0 0x00

//����Ŀ�����ݵĳ���
#define D_LEN19 0x04
#define D_LEN18 0x03
#define D_LEN17 0x02
#define D_LEN16 0x01
#define D_LEN15 0x00
#define D_LEN14 0x04
#define D_LEN13 0x03
#define D_LEN12 0x02
#define D_LEN11 0x01
#define D_LEN10 0x00
#define D_LEN9 0x04
#define D_LEN8 0x03
#define D_LEN7 0x02
#define D_LEN6 0x01
#define D_LEN5 0x00
#define D_LEN4 0x04
#define D_LEN3 0x03
#define D_LEN2 0x02
#define D_LEN1 0x01
#define D_LEN0 0x00


//#define D_S_SAME 0x80

#define DI_EQU_NULL 0

//�û�Ȩ�ޱ�־��
typedef struct
{
  INT8U Head;
  INT32U Flag; 
  INT8U CS[CS_BYTES];
  INT8U Tail;
}S_User_Authority_Flag;

typedef struct{
 INT8U Src_Off;
 INT8U Src_Len;
 INT8U Src_Format;
 
 INT8U Dst_Start;
 INT8U Dst_Len; 
}S_Data_Item;

typedef struct{
  INT8U Num;
  S_Data_Item Data_Item[25]; 
}S_Multi_Data;

typedef struct{
  INT8U Time[5];//���һ�α��ʱ��
  INT32U Counts;//��̴���
  INT8U CS[CS_BYTES];
}S_Prog_Record;

typedef struct
{
  INT8U Time[5];//���һ�����������0ʱ��
  INT32U Counts;//������0����
  INT8U CS[CS_BYTES];
}S_Clr_Demand_Record;

EXT S_Prog_Record Prog_Record;//��̴�����ʱ��
EXT S_Clr_Demand_Record Clr_Demand_Record;//������������ʱ��

//���嵱ǰͨ��ͨ��
#ifdef DATA_TRANS_C
EXT S_Cur_Comm_Ch Cur_Comm_Ch={CHK_BYTE,0,CHK_BYTE};
#endif
extern S_Cur_Comm_Ch Cur_Comm_Ch;

typedef struct{
  PROTO_DI DI;   //645Э���ID,��IDҲ�Ǵ洢ID
  PROTO_DI DI_Equ;//����DI��ȫ��Ч�ı�ʾ������������Э���ڱ�׼645Э���Ӧ

  INT8U DI_Set_Flag:1;//DI�������Ƿ�������ݼ���
  INT8U DI_Equ_Set_Flag:1;//DI_Equ�Ƿ�������ݼ���?
        
  INT8U PSW_Flag:4;       //�޸ĵ�����ȼ�
  
  INT8U Storage:2;        //Դ�洢����,S_ROM����S_RAM
  //INT16U Storage_DI;    //����洢��Rom�У�Storage_DI��ʾ�洢�ı��
  
  volatile void * pSrc; //����Դ���ݵ�ָ��
  INT16U Src_Off;       //��pSrc��ȡԴ���ݵ�ƫ��
  
  INT8U Src_Len;        //Դ���ݳ���,��Դ����ΪS_INTU��S_INTSʱ�ɸ��ݸó��ȵ�֪���ݾ�������	
  INT8U Src_Format;     //Դ���ݵĸ�ʽ
  
  INT8U Dst_Start;      //Ŀ��������Դ���ݵ�BCD������ȡ���ݵ���ʼλ��,���Դ
                              //������S_INTU��������,��Ŀ�����ݵ�Ӧ����Դ����/Dst_Start��ת��ΪBCD��
  INT8U Dst_Len;        //Ŀ�����ݵ���ȡ����,�����S_BCD����,��ֱ�Ӵ�Դ���ݵ�Dst_Start�ֽڴ���ʼȡ��

  INT16U Num;            //����������Ƶ����������
        
  INT8U Spec_Flag;      //�Ƿ��������������� Num��������Ϊ�������һ������
}S_Protocol_Data_Info;


//EXT volatile S_Prog_Flag Prog_Flag;//��̱�ʶ��
////���������DI,��������ݱ�ʶ����0x01��ʼ,��������ݴ洢��ROM�У���Data_Para_Storage��Ҳ�����������//
//��������ȫ���ӵ�ǰram����ȡ������Ͷ�ȡ�洢���ݳ�ͻ
#define DI_REG_CKC                 0x0001
#define DI_REG_CSC                 0x0002

#define DI_LOW_VOL                 0x0100
#define DI_CURRENT_QUADRANT        0x0101
#define DI_METER_PERIPHERY         0x0102
#define DI_MODULE_STATUS           0x0103
#define DI_POWER_DOWN_TIME         0x0104

#define DI_METER_ADDR0             0x0105//��һ·���ַ,��METER_ADDR0һ��
#define DI_METER_ADDR1             0x0106//�ڶ�·���ַ
#define DI_METER_ADDR2             0x0107//����·���ַ

#define DI_COMM_BAUD0              0x0108//��һ·������,��COMM_BAUD0һ��
#define DI_COMM_BAUD1              0x0109//�ڶ�·������
#define DI_COMM_BAUD2              0x010A//����·������

#define DI_METER_SOFTWARE_VERSION  0x0110//����汾��
#define DI_METER_SPECIFI           0x0111//�����

///һ��������Ϊ������������,��Ҫ�ٴ˷�Χ������������
#define DI_ACTIVE_DIRECT           0x0120//�й�����
#define DI_REACTIVE_DIRECT         0x0121//�޹�����

//#define _DI_ACTIVE_DIRECT          0x0122//�й����򣬰�����
//#define _DI_REACTIVE_DIRECT        0x0123//�޹����򣬰�����

#define DI_REACTIVE_ALL            0x0130//���޹�����
#define DI_REACTIVE_A              0x0131//A��B��C�����޹�����
#define DI_REACTIVE_B              0x0132
#define DI_REACTIVE_C              0x0133

#define DI_CUR_TIME                0x0134//��ǰBCDʱ�� ������ʱ��

#define DI_ACTIVE_DEMAND           0x0140//�й�����
#define DI_REACTIVE_DEMAND         0x0141//�޹�����

#define _DI_TOTAL_AH                0x0142//��AH,��λС��
#define _DI_A_AH                    0x0143//A����AH
#define _DI_B_AH                    0x0144//B����AH
#define _DI_C_AH                    0x0145//C����AH

#define DI_TOTAL_AH                0x0151//��AH
#define DI_A_AH                    0x0152//A����AH
#define DI_B_AH                    0x0153//B����AH
#define DI_C_AH                    0x0154//C����AH

#define DI_A_VOL                   0x0155//A���ѹ,2λС��,3�ֽ�
#define DI_B_VOL                   0x0156//B���ѹ,2λС��
#define DI_C_VOL                   0x0157//C���ѹ,2λС��

#define DI_A_CUR                   0x0158//A�����,4λС��,3�ֽ�
#define DI_B_CUR                   0x0159//B�����,4λС��
#define DI_C_CUR                   0x015A//C�����,4λС��

#define DI_A_ANGLE                 0x015B//A�����,2λС��,3�ֽ�
#define DI_B_ANGLE                 0x015C//B�����,2λС��,3�ֽ�
#define DI_C_ANGLE                 0x015D//C�����,2λС��,3�ֽ�
#define DI_SUM_ANGLE               0x015E//�����,2λС��,3�ֽ�

#define DI_PROG_FLAG0              0x0160//��̱�ʶ��1
#define DI_PROG_FLAG1              0x0161//��̱�ʶ��2

#define DI_ERR_TIME                0x0162//�����ʱ������
#define DI_ERR_ROM                 0x0163//EEROM�����ʶ��

#define DI_CUR_DEMAND              0x0164//��ǰ����
#define DI_CLR_DEMAND_WAY          0x0165//��������ʽ
#define DI_ADJ_FLAG                0x0166//У���ʶ��
#define DI_NULL_1BYTE              0x0167//������ı�ʶ�� 

#define DI_EVENT_VOL               0x0168//��ѹ���޻��߹�ѹʱ�ĵ�ѹֵ

#define DI_ALL_LOSS_VOL_START_TIME 0x0170//ȫʧѹ��ʼʱ��
#define DI_ALL_LOSS_VOL_END_TIME   0x0171//ȫʧѹ����ʱ��

#define DI_EVENT_TIME              0x0172//�¼�����ʱ��

#define DI_A_VOL_1                 0x0173//A���ѹ,1λС��,3�ֽ�
#define DI_B_VOL_1                 0x0174//B���ѹ,1λС��
#define DI_C_VOL_1                 0x0175//C���ѹ,1λС��

#define DI_A_CUR_3                 0x0176//A�����,3λС��,3�ֽ�
#define DI_B_CUR_3                 0x0177//B�����,3λС��
#define DI_C_CUR_3                 0x0178//C�����,3λС��

#define DI_PROG_TIME               0x0179//���һ�α��ʱ��

#define DI_BROAD_ADJ_TIME          0x017A //����㲥УʱDI,Э�鴫������ʱδ��


#define DI_EXTNED_START            0x0300//�����DI����ʼ
/////�������߲������

////���������DI����///////

//ע�⣬��ȡCUR_ENERGY����HIS_ENERGYΪID�����ݺ�Ҫ���ݵ�ǰ��ģʽ�ּ��㵱ǰ������޹�
//HIS_ENERGY��HIS_DEMAND��HIS_DEMAND_TIME���ݶ���Ҫ���⴦��
//


extern CONST S_Multi_Data Loss_Vol_Data;
extern CONST S_Multi_Data Loss_Cur_Data;
extern CONST S_Multi_Data Phase_Reverse_Data;
extern CONST S_Multi_Data Phase_Break;

#define CHK_PARA_NUM 15
typedef struct{
  INT8U Head;
  INT8U Posi[OS_TASK_NUM];
  PROTO_DI Buf[OS_TASK_NUM][CHK_PARA_NUM];
  INT8U CS[CS_BYTES];
  INT8U Tail;
}S_Para_Modify;

EXT volatile S_Para_Modify Para_Modify;

EXT volatile S_Disp_Digs Disp_Digs;//���幦�ʺ͵��ܵ���ʾλ��
EXT volatile S_Meter_Addr Meter_Addr;
EXT volatile S_User_Authority_Flag User_Authority_Flag;

typedef struct{
  INT8U Head;
  INT32U Flag;
  INT8U CS[CS_BYTES];
  INT8U Tail;
}S_Clear_Flag;

typedef struct{
  INT8U Head;
  INT8U Set_En_Mins;
  INT8U Err_Times;
  INT16U Clr_Err_Times_Mins;//��������ʣ��ʱ��
  INT16U Lock_Mins;//����ʱ�䣬���ǽ���ʣ��ʱ��
  INT8U CS[CS_BYTES];
  INT8U Tail;
}S_PSW_Err_Info;

extern const S_Protocol_Data_Info Protocol_Data[];
EXT volatile S_Clear_Flag Clear_Flag;
EXT volatile S_PSW_Err_Info PSW_Err_Info;
EXT volatile S_Int8U Time_Modify_Flag;

EXT void Init_Data_Trans_Ram_Para();
EXT void Check_Data_Trans_Data_Avail();
EXT void Read_Data_Trans_Para_From_Rom();
EXT void Set_Para_Modify(PROTO_DI DI);
EXT INT8U Check_Para_Modify(PROTO_DI DI);
EXT INT8U Get_Para_Modify(PROTO_DI *pDI);
EXT INT32U Pow_10x(INT8U a);

EXT INT16U Get_Protocol_Data_Index(PROTO_DI DI);
EXT INT8U Get_Protocol_Data_PSW_Flag(PROTO_DI DI);
EXT INT8U Get_Energy_Disp_Digs();
EXT INT16U Get_Multi_Item_Data(INT8U *pSrc,S_Multi_Data *p,INT8U *pDst,INT8U *pDst_Start,INT16U DstLen);
EXT INT16U _Get_DLT645_Single_Data(INT16U Index,PROTO_DI DI,void *pPara,INT8U ParaLen,INT8U *pDst,INT8U *pDst_Start,INT16U DstLen,INT8U Data_Flag,INT8U *pErr);
EXT INT16U Get_DLT645_Single_Data(INT16U Index,PROTO_DI DI,void *pPara,INT8U ParaLen,INT8U *pDst,INT8U *pDst_Start,INT16U DstLen,INT8U Data_Flag,INT8U *pErr);
EXT INT16U _Get_DLT645_Data(PROTO_DI DI,void *pPara,INT8U ParaLen,INT8U *pDst,INT8U *pDst_Start,INT16U DstLen,INT8U Data_Flag,INT8U *pNextFlag,INT8U *pErr);
EXT INT16U Get_DLT645_Data(PROTO_DI DI,INT8U *pDst,INT8U *pDst_Start,INT16U DstLen,INT8U *pErr);
EXT INT16U Get_DLT645_Data_For_Disp(PROTO_DI DI,INT8U *pDst,INT8U *pDst_Start,INT16U DstLen);
EXT INT16U _Get_DLT645_Normal_Data(PROTO_DI DI,void *pPara,INT8U ParaLen,INT8U *pDst,INT8U *pDst_Start,INT16U DstLen,INT8U Data_Flag,INT8U *pFollowFlag,INT8U *pErr);

EXT INT16U Simple_Search_Frame(INT8U *pSrc,INT16U SrcLen,INT16U *pOffset);
EXT INT16U Rcv_DLT645_Data_Proc(INT8U Ch,INT8U *pFrame,INT8U FrameLen,INT8U *pDst,INT8U *pDst_Start,INT16U DstLen);
EXT INT8U Check_Protocol_Data_Single(INT16U Index,PROTO_DI DI,INT8U Data_Flag,INT8U *pSpec_Flag);
EXT INT8U Check_Protocol_Data_Storage();
EXT INT8U Get_DLT645_Data_Storage_Type(PROTO_DI DI);
EXT INT16U Search_Protocol_Frame(INT8U *pSrc,INT16U SrcLen,INT16U *pOffset);
EXT INT16U Rcv_PROTOCOL_Frame_Proc(INT8U Ch,INT8U *pSrc,INT16U SrcLen,INT8U *pDst,INT8U *pDst_Start,INT16U DstLen);

EXT INT8U Adj_Time(S_BCD_Time *pTime);
EXT void Wait_Event_Data_Proc_End(INT8U Event_ID);
EXT void Set_Clear_Data_Flag(INT32U Flag);
EXT INT32U Check_Clear_Data_Flag();
EXT void Clear_Data_End();
#endif
