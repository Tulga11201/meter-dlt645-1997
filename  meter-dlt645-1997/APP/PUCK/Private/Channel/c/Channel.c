#define CHANNEL_C
#include "Pub_PUCK.h"


/********************************************************************************

*********************************************************************************/
INT32U Get_Baud_Spec(INT8U Baud)
{
  if(Baud&0x01)
    return 1200;
  
  if(Baud&0x02)
    return 300;
  
  if(Baud&0x04)
    return 600;
  
  if(Baud&0x10)
    return 2400;
  
  if(Baud&0x20)
    return 4800;
  
  if(Baud&0x40)
    return 9600;
  
    return 1200;  //Ĭ��1200
}


/********************************************************************************
����ԭ�ͣ�void Init_All_Cannel(void)
���ܣ���ʼ������ͨ��
*********************************************************************************/
void Init_All_Cannel(void)
{
  INT16U Len;
  INT8U temp,Err;
  
  Len=Read_Storage_Data(DI_CHANEL_485_1,&temp,&temp,1,&Err);
  if((Len==1)&&(NO_ERR==Err))
  {
      Chanel_Para[CHANEL_485_1].Baud=Get_Baud_Spec(temp);
      SET_STRUCT_SUM(Chanel_Para[CHANEL_485_1]);
  }
    
  Len=Read_Storage_Data(DI_CHANEL_485_2,&temp,&temp,1,&Err);
  if((Len==1)&&(NO_ERR==Err))
  {
    Chanel_Para[CHANEL_485_2].Baud=Get_Baud_Spec(temp);
    SET_STRUCT_SUM(Chanel_Para[CHANEL_485_2]);
  }
  
  if(CHANEL_IRDA!=CHANEL_DEBG)    //���Կڵ�����ʼ����
    Open_Channel_PUCK(CHANEL_IRDA,Chanel_Para[CHANEL_IRDA].Baud,SAU_PARITY_EVEN);
    
  if(CHANEL_485_1!=CHANEL_DEBG)     //���Կڵ�����ʼ����
    Open_Channel_PUCK(CHANEL_485_1,Chanel_Para[CHANEL_485_1].Baud,SAU_PARITY_EVEN);  
    
  if(DI_CHANEL_485_2!=CHANEL_DEBG)  //���Կڵ�����ʼ����
     Open_Channel_PUCK(CHANEL_485_2,Chanel_Para[CHANEL_485_2].Baud,SAU_PARITY_EVEN); 
  
#ifdef CHANEL_MOUDEL 
  Chanel_Para[CHANEL_MOUDEL].Baud=BAUD_MOUDLE;
  SET_STRUCT_SUM(Chanel_Para[CHANEL_MOUDEL]);
  if(CHANEL_MOUDEL!=CHANEL_DEBG)  //���Կڵ�����ʼ����
     Open_Channel_PUCK(CHANEL_MOUDEL,Chanel_Para[CHANEL_MOUDEL].Baud,SAU_PARITY_EVEN); 
#endif
}
/********************************************************************************
����ԭ�ͣ�INT8U  Send_HostData_Public_Puck(INT8U Channl,INT8U *Srcbuf,INT16U len)
�������ܣ���ĳͨ����������
��ڲ�����Channl,ͨ����
          Srcbuf�����͵�������ʼ��ַ 
          Src_Len,Դ���ݵĳ���
���ڲ�����1�����ͳɹ���0������ʧ��
*********************************************************************************/
INT8U  Send_HostData_Public_Puck(INT8U Channl,INT8U *Srcbuf,INT16U Src_Len)
{
  INT8U Flag;
  
  /*645һ����С���ܵ���10�ֽ�
  Flag=ASSERT(A_WARNING,Src_Len>=10);
  if(Flag)
    return 0;
  */
  
  Flag=Channel_DataSend_PUCK(Channl,Srcbuf,Src_Len);  
  return Flag;
}
/********************************************************************************
����ԭ�ͣ�INT8U  Send_HostData_Public_Puck(INT8U Channl,INT8U *Srcbuf,INT16U len)
�������ܣ���ĳͨ����������
��ڲ�����Channl,ͨ����
          Srcbuf�����͵�������ʼ��ַ 
          Src_Len,Դ���ݵĳ���
���ڲ�����1�����ͳɹ���0������ʧ��
*********************************************************************************/
INT8U  Debug_Out_Public_Puck(INT8U *Srcbuf,INT16U Src_Len)
{
 INT8U Flag;
 Flag=Channel_DataSend_PUCK(CHANEL_DEBG,Srcbuf,Src_Len);  
  return Flag;
}
/********************************************************************************
����ԭ�ͣ�void DataRec_Monitor_PUCK(void)
���ܣ���ȡ����ͨ����645����

*********************************************************************************/
void Channel_Data_Proc_PUCK(INT32U Status)
{
  INT8U i;
  
  for(i=CHANEL_MIN;i<=CHANEL_MAX;i++)
  {      
      Channel_DataReceive_PUCK(i,Status);     
  }
  Remote_Key_Proc();   //resumeģʽ�£������Թ���
}

void Debug_Channel_Switch(INT32U Mode)
{    
  if((Check_Debug_En()==1)&&(Chanel_Para[CHANEL_IRDA].Baud!=BAUD_DEBG))  //���ÿ��л������Կ�
  {
    Chanel_Para[CHANEL_DEBG].Baud=BAUD_DEBG;
    Open_Channel_PUCK(CHANEL_DEBG,BAUD_DEBG,SAU_PARITY_NONE);
    Debug_Out_Public_Puck("\r\nPUCK:Switch To Debug CHannel!",31);
    DIS_UART0_REC;        //����ģʽ�£��ر�UART0�ڵĽ��գ������ж�
    SET_STRUCT_SUM(Chanel_Para[CHANEL_IRDA]);
  }
  else
  {
    if((Check_Debug_En()==0)&&(Chanel_Para[CHANEL_IRDA].Baud!=BAUD_IRDA))  //���ÿ��л���������
    {
      if(SYS_NORMAL==Mode)
      {        
        Chanel_Para[CHANEL_IRDA].Baud=BAUD_IRDA;
        Open_Channel_PUCK(CHANEL_IRDA,BAUD_IRDA,SAU_PARITY_EVEN);
        SET_STRUCT_SUM(Chanel_Para[CHANEL_IRDA]); 
      }
      if(SYS_RESUME==Mode &&Check_Resume_Source(IRAD_RESUME)) //���⻽��ģʽ
      {
        if(IRDA_READ_METER_EN)   //��key�Ѿ������£����⻽�ѣ�HUCK������� Init_ExtDevice_PUCK()
        {
          //IRDA_FAR_REC_EN;              //������տ���
          BAK_POWER_FOR_IRDA;            //Զ�����Դ�ɵ͹��ĵ�ع���;
          //Debug_Out_Public_Puck("\r\nPUCK:Switch To IRDA CHannel!",30);
          Chanel_Para[CHANEL_IRDA].Baud=BAUD_IRDA;
          Open_Channel_PUCK(CHANEL_IRDA,BAUD_IRDA,SAU_PARITY_EVEN);
          SET_STRUCT_SUM(Chanel_Para[CHANEL_IRDA]); 
        }
      }
    }  
  } 
}
/********************************************************************************
����ԭ�ͣ�void Channel_Switch_PUCK(INT32U Mode)
���ܣ�ͨ�����л������ݹ���״̬�����״̬���������ڵ����á�

*********************************************************************************/
void Channel_Switch_PUCK(INT32U Mode)
{ 
  if(CHANEL_DEBG==CHANEL_IRDA)
  {
     Debug_Channel_Switch(Mode);
  }  
}
/********************************************************************************
����ԭ�ͣ�void Monitor_Para_Modi_PUCK(void)
���ܣ������в�������ά��������������ͨ�����¼��ȡ�

*********************************************************************************/
void Para_Modi_Monitor_PUCK(void)
{
  INT16U temp;
  
  while(Get_Para_Modify(&temp))
  {
    DEBUG_PRINT(PUCK,PRINT_PUCK_CHANNEL_EN,"Para Modified In Channel Task:0x%x",temp);
    switch(temp)
    {
      case DI_CHANEL_485_1:  //��һ·485�����޸�
      case DI_CHANEL_485_2:   //�ڶ�·485�����޸�
          Init_All_Cannel();
          DEBUG_PRINT(PUCK,PRINT_PUCK_CHANNEL_EN,"CHANEL_485_1/CHANEL_485_2 Baud Changed");
      break; 
      default:   //���²������Ż�
      if(((temp>=VARHMODE1)&&(temp<=VARHMODE2))||((temp>=ROLLCYCLE)&&(temp<=POWERBITS))||(temp==NUMBMODEB))
        Lcd_Para_Modi(temp);                              //Һ�����������޸�  
        break;
    }    
  }   
}

/********************************************************************************
����ԭ�ͣ�void Init_All_UART(void)
���ܣ���ʼ������ͨ��
*********************************************************************************/
void Init_All_UART(INT32U Mode)
{
  INT8U i;
  switch(Mode)
  {
  case SYS_NORMAL:
    Init_DebugChanel_PUCK(0);         //���Կڳ�ʼ��
    Init_All_Cannel();
    break;
    
  case SYS_RESUME:    //ֻ�����Ǻ��⡢��ť������⻽�ѣ��������Ѳ������˺���----------PUCK
    for(i=CHANEL_MIN;i<=CHANEL_MAX;i++)
    {
      if(i!=CHANEL_DEBG)   //���ǵ��Կ�
        Close_Channel_PUCK(i); 
      else             //�ǵ��Կ�
        Init_DebugChanel_PUCK(1);
    }
      
    break;    
  case SYS_SLEEP:
   //�ر����д���
    for(i=CHANEL_MIN;i<=CHANEL_MAX;i++)
       Close_Channel_PUCK(i);   //�ر�ȫ������------------PUCK
    break;
    
  }
}

/********************************************************************************
����ԭ�ͣ�void Init_DebugChanel_PUCK(INT8U FacFlag)
���ܣ���ʼ�����Կ�ͨ��
FacFlag-----1:��Ҫ�ж�����״̬��0--------����Ҫ
*********************************************************************************/
void Init_DebugChanel_PUCK(INT8U FacFlag)
{
  if(POWER_OFF_STATUS==0)  //������
    return ;
  
  if(CHANEL_DEBG==CHANEL_IRDA)
  {
    Chanel_Para[CHANEL_DEBG].Baud=BAUD_DEBG;
    SET_STRUCT_SUM(Chanel_Para[CHANEL_DEBG]);    
    if(FacFlag)         //��Ҫ�ж�����״̬
    {
      if(Check_Debug_En())  //�ǹ���״̬��ӡ)
        Open_Channel_PUCK(CHANEL_DEBG,BAUD_DEBG,SAU_PARITY_NONE); 
    }
    else               //����Ҫ�ж�����״̬     
        Open_Channel_PUCK(CHANEL_DEBG,BAUD_DEBG,SAU_PARITY_NONE); 
  }  
}
/********************************************************************************
����ԭ�ͣ�void Close_DebugChanel_PUCK(INT8U FacFlag)
���ܣ���ʼ�����Կ�ͨ��
FacFlag-----1:��Ҫ�ж�����״̬��0--------����Ҫ
*********************************************************************************/
void Close_DebugChanel_PUCK(INT8U FacFlag)
{
  if(CHANEL_DEBG==CHANEL_IRDA)
  {
    Chanel_Para[CHANEL_DEBG].Baud=0;
    SET_STRUCT_SUM(Chanel_Para[CHANEL_DEBG]);    
    if(FacFlag)         //��Ҫ�ж�����״̬
    {
      if(Check_Debug_En())  //�ǹ���״̬��ӡ)
        Close_Channel_PUCK(CHANEL_DEBG); 
    }
    else               //����Ҫ�ж�����״̬     
        Close_Channel_PUCK(CHANEL_DEBG); 
  }  
}
/**********************************************************************************
�������ܣ����ͨ�Ų����ṹ���У���
��ڣ���
���ڣ���
**********************************************************************************/	
void Check_Channel_ParaCS(void)
{
  INT8U i,Flag;
  
  Flag=0;
  
  for(i=CHANEL_MIN;i<=CHANEL_MAX;i++)
  {
    Flag=CHECK_STRUCT_SUM(Chanel_Para[i]); 
    ASSERT(A_WARNING,1==Flag);
    if(!Flag)
    DEBUG_PRINT(PUCK,PRINT_PUCK_CHANNEL_EN,"Channel_Error----->Channel_Para Struct CS Error In Channel Proc!");
  }

  Flag=CHECK_STRUCT_VAR(S_Buf_PUCK);
  ASSERT(A_WARNING,1==Flag);
}

/**********************************************************************************
�������ܣ�
��ڣ���
���ڣ���
**********************************************************************************/	
void Init_Channel_Sram(void)
{
#ifdef CHANNEL_FAST_EN
  INIT_STRUCT_VAR(Rec_Frame_Status);
#endif
}
/********************************************************************************
����ԭ�ͣ�void Channel_Main_PUCK(INT8U Flag)
�������ܣ�ͨ��ͨ������������
*********************************************************************************/
void Channel_Main_PUCK(INT8U Flag)  //10ms����һ��
{
  static volatile S_Int32U Sec_Timer_Bak={CHK_BYTE,0xFFFFFFFF,CHK_BYTE};
  INT32U Status;
  
  Status=Get_Sys_Status();
  if(Status==SYS_SLEEP) //ֻ��������ģʽ�£������¼��Ĵ���
    return ;
  
  if(Flag)
  {
    Init_Channel_Sram();
    return ;
  }
  
  Channel_Data_Proc_PUCK(Status);  //10ms����һ��  
  if(Sec_Timer_Bak.Var!=Sec_Timer_Pub)  //����ģʽ�£�1���һ��
  {
    if(Status==SYS_NORMAL)
    {
      Para_Modi_Monitor_PUCK();   //1s
      Check_Channel_ParaCS();    //1s
      Check_LCDVar_Cs();    //1s��һ��
    }
    Channel_Switch_PUCK(Status);     //1s 
    Sec_Timer_Bak.Var=Sec_Timer_Pub;
  }
}
