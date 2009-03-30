#ifndef AUTHORITY_H
#define AUTHORITY_H

#undef EXT
#ifdef AUTHORITY_C
#define EXT 
#else
#define EXT extern 
#endif

//����645Э��Ŀ�����
#define C_READ_DATA  0x01       //������
#define C_READ_FOLLOW_DATA 0x02 //����������
#define C_SET_DATA 0x04         //д����
#define C_ADJUST_METER 0x05     //У��
#define C_ADJUST_TIME 0x08      //�㲥Уʱ
#define C_SET_ADDR 0x0A         //д�豸��ַ
#define C_SET_COM_BAUD 0x0C     //��ͨ���ٶ�
#define C_SET_PSW 0x0F          //�޸�����
#define C_CLR_ALL 0x09          //����0���߶�������
#define C_CLR_DEMAND 0x10       //������
#define C_CLR_EVENT 0x0B        //�����(�¼�)
#define C_CLR_STAT 0x0D         //���ѹ�ϸ���(ͳ��)

/*
�߼���J1�̽�	��	��	��	��	��	��
�������	��	��	��	��	��	��
���뼶������	��	��	��	��	��	��
�û�Ȩ��	��	��	��	��	��	��
�������	1	1	2	2	2	3

���������
1����ȷ���á�2�����ش��󣬵����ۼ�������������3�����ش�����������������1��
*/

//���ݵ������־
#define PSW_NULL  0xFF//û����������
#define PSW_FACTORY 0//���������������ϲ������õĲ���
#define PSW_0 1  //0������
#define PSW_1 2  //1������
#define PSW_2 3  //2������
#define PSW_3 4  //3�����룬Э������δ��


//����������Ҫ����һ�������е����ݷ���
#define PSW_NULL_FLAG 0xFF
#define PSW_SET_PSW0  1     //0������Ȩ��
#define PSW_SET_PSW1  2     //1������Ȩ��
#define PSW_SET_PSW2  3     //2������Ȩ��
#define PSW_ADJ_TIME  4     //�㲥Уʱ
#define PSW_SET_DATE  5     //��������
#define PSW_SET_TIME  6     //����ʱ��
#define PSW_CLR_ALL   7     //���������
#define PSW_CLR_DATA  8     //�����������̡���ѹ�ϸ���
#define PSW_SET_ENSTART 9   //���õ׶���
#define PSW_SET_PARA 10     //������ͨ����(��������)
#define PSW_SET_MODE45 11   //����ģʽ��4��5
#define PSW_SET_MODE678 12  //����ģʽ��6��7��8
#define PSW_FACTORY_STATUS 13  //��Ǳ��״̬
#define PSW_RD_ONLY 14 //����ֻ����û��дȨ��

//�û�Ȩ�޿�����
typedef struct{
  INT16U PSW[3];
  INT8U CS[CS_BYTES];//У���  
}S_User_Authority_Ctrl;//�û�Ȩ�޿�����

//��������Flag�����û�Ȩ�޿������е�λ�õ�ӳ���
typedef struct{
  INT8U PSW_Flag;
  INT8U Posi;
}S_PSW_Map;

//��������Ȩ��״̬
typedef struct{
  INT8U Head;
  INT8U PSW[3][3];//��ǰ���������룬ÿ������3���ֽ�
  INT8U CS[CS_BYTES];//У���
  INT8U Tail;
}S_PSW_Status;

#ifdef AUTHORITY_C
const S_PSW_Map PSW_Map[]=
{
  //��һ���û�Ȩ����
  { PSW_SET_PSW0,  7}, //0������Ȩ��
  { PSW_SET_PSW1,  6}, //1������Ȩ��
  { PSW_SET_PSW2,  5}, //2������Ȩ��
  { PSW_ADJ_TIME,  4}, //�㲥Уʱ
  { PSW_SET_DATE,  3}, //��������
  { PSW_SET_TIME,  2}, //����ʱ��
  //�ڶ����û�Ȩ����  
  { PSW_CLR_ALL,   14},  //���������
  { PSW_CLR_DATA,  13},  //�����������̡���ѹ�ϸ���
  { PSW_SET_ENSTART, 12},//���õ׶���
  { PSW_SET_PARA, 10},   //������ͨ����(��������)
  { PSW_SET_MODE45, 9},   //����ģʽ��4��5
  { PSW_SET_MODE678, 8}   //����ģʽ��6��7��8
};
#endif

EXT volatile S_User_Authority_Ctrl User_Authority_Ctrl;//�û�Ȩ�޿�����
EXT volatile S_PSW_Status Cur_PSW;

EXT INT8U Check_Debug_En();
EXT INT8U Check_Set_ADDR_Key();
EXT void Clear_PSW_Err_Info();
EXT INT8U Check_Clear_Data_Authority();
EXT INT8U Check_Meter_Factory_Status();
EXT INT8U Check_Meter_Prog_Status();
EXT INT8U Get_User_Authority(INT8U Ctrl_Code,INT8U *pSrc,INT8U SrcLen,INT8U *pErr);
EXT INT8U Get_Protocol_Data_Authority(INT8U Ch,INT8U Ctrl_Code,INT8U *pSrc,INT8U SrcLen);
#endif
