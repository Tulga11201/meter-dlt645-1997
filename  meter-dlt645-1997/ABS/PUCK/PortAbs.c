#define PORT_ABS_PUCK
#include "Pub_PUCK.h"
#include "Includes.h"


/********************************************************************************
void  Get_Meter_Hard_Mode(void)
�������ܣ���ȡ�������ģʽ
��ڣ�  
���أ�
    ��
********************************************************************************/
INT8U Get_Meter_Hard_Mode(void)
{
  if(B_TEST_FAC_STATUS && B_TEST_HARD_STATUS)  //�����������ģʽ��
    return MODE_RUN;
  
  if(B_TEST_FAC_STATUS && B_TEST_HARD_STATUS==0)
    return MODE_DEBUG;
  
  if(B_TEST_FAC_STATUS==0 && B_TEST_HARD_STATUS)
    return MODE_FAC;
  
  if(B_TEST_FAC_STATUS==0 && B_TEST_HARD_STATUS==0)  //����ģʽ����
    return MODE_TEST;  
  
  //�쳣��
  return MODE_RUN;
}


/********************************************************************************
********************************************************************************/

void PORT_ChangeP142Output_PUCK(INT8U Flag)
{
  PORT_ChangeP142Output(0,Flag);
  
}

#pragma pack(1)
typedef struct
{
  INT8U NeedInit:1;                 //��Ҫ��ʼ����־
  INT8U InitLevel:1;                //���������£�����ʱ�ĵ�ƽֵ��
  INT8U SleepLevel:1;               //�͹�������£���Ҫ��ʼ�ĵ�ƽֵ��
  INT8U ValidLevel:1;               //��ƽģʽ�£������Ч�ĵ�ƽֵ��
  INT8U MultiFlag:2;                //�Ƿ��Ǹ��϶��ӱ�־����3��1��0-------���Ǹ��϶��ӣ�1------�Ǹ��϶��ӣ�2------�������
  INT8U LevelProprty:1;             //�ö����ǵ�ƽ����
  INT8U LoopFlag:1;                 //�������巽ʽ��Ч 
  void  (* const FuncPtr)(INT8U);
  INT8U (* const MultiPortEn)(void); //���һ����(MultiFlagΪ1ʱ)�����ݴ������ж����
}CONST_PORT_STATUS;

//���¶���������ڵĳ�����
CONST_PORT_STATUS  Const_Port_Status[MAX_PORT_NUM]={
  {0},
  {1,0,0,0,0,LEVEL_MODE,0,&PORT_ChangeP81Output,&Get_GridAlarm_Out_En},    //������Ϣ�������(�糬����)------------------------------1
  {1,0,0,0,0,LEVEL_MODE,0,&PORT_ChangeP81Output,&Get_FeeAlarm_Out_En},    //Ԥ����Ƿ�ѱ���------------------------------------------2
  {1,0,0,0,0,LEVEL_MODE,0,&PORT_ChangeP80Output,0},    //��������բ���----------------------------------------------------------3
  {0,1,0,0,0,PULSE_MODE,0,&PORT_ChangeP66Output,0},    //�й��������------------------------------------------------------------4
  {0,1,0,0,0,PULSE_MODE,0,&PORT_ChangeP67Output,0},    //�޹��������------------------------------------------------------------5
  {0,1,0,0,0,LEVEL_MODE,0,&PORT_ChangeP64Output,0},    //�й��������------------------------------------------------------------6
  {0,1,0,0,0,LEVEL_MODE,0,&PORT_ChangeP65Output,0},    //�޹��������------------------------------------------------------------7
  {1,1,0,0,0,LEVEL_MODE,0,&PORT_ChangeP82Output,&Get_Sec_Out_En},    //������ʹ��------------------------------------------------8
  
  {1,1,0,0,2,PULSE_MODE,0,&PORT_ChangeP83Output,&Get_Demand_Out_En},    //�������ڵ����-----------------------------------------9
  {1,1,0,0,2,PULSE_MODE,0,&PORT_ChangeP83Output,&Get_Slipe_Out_En},     //�������ڵ����-----------------------------------------10 
  
  {1,1,0,0,0,PULSE_MODE,0,&PORT_ChangeP84Output,&Get_Parse_Out_En},    //ʱ�����-----------------------------------------------11
  {0,1,0,0,0,PULSE_MODE,0,&PORT_ChangeP150Output,0},   //���й������----------------------------------------------12
  {0,1,0,0,0,PULSE_MODE,0,&PORT_ChangeP151Output,0},   //���޹������----------------------------------------------13
#if METER_HARD_TYPE==HARD_TYPE_20081005
  {1,0,0,1,0,PULSE_MODE,0,&PORT_ChangeP54Output,0},    //����ָʾ��------------------------------------------------14
#endif
#if METER_HARD_TYPE>=HARD_TYPE_20090224
  {1,0,0,1,0,PULSE_MODE,0,&PORT_ChangeP157Output,0},    //����ָʾ��-----------------------------------------------14
#endif
  {1,0,0,1,0,PULSE_MODE,0,&PORT_ChangeP142Output_PUCK,0}  //���ȱ��� ----------------------------------------------15
};

#pragma pack()

/********************************************************************************
INT8U  Get_Sec_Out_En(void)
�������ܣ�����ģʽ�֣���ȡ���������ʹ��
��ڣ�  
���أ�
    ��
********************************************************************************/
INT8U Get_Sec_Out_En(void)
{
  INT8U Err,Len;
  INT8U Temp;
  
  Len=Get_DLT645_Data(0xCA12,&Temp,&Temp,1,&Err);
  if(NO_ERR==Err && 1==Len)
  {
    if(Temp&0x03==0x00)
     return 1;  
  }
  return 0;  
}
/********************************************************************************
INT8U  Get_Parse_Out_En(void)
�������ܣ�����ģʽ�֣���ȡʱ�����ʹ��
��ڣ�  
���أ�
    ��
********************************************************************************/
INT8U Get_Parse_Out_En(void)
{
  INT8U Err,Len;
  INT8U Temp;
  
  Len=Get_DLT645_Data(0xCA12,&Temp,&Temp,1,&Err);
  if(NO_ERR==Err && 1==Len)
  {
    if(Temp&0x03==0x01)
     return 1;  
  }  
  return 0;
}
/********************************************************************************
INT8U  Get_Demand_Out_En(void)
�������ܣ�����ģʽ�֣���ȡ�������ʹ��
��ڣ�  
���أ�
    ��
********************************************************************************/
INT8U Get_Demand_Out_En(void)
{
  INT8U Err,Len;
  INT8U Temp;
  
  if(Const_Port_Status[EXT_ID_DEMAND].MultiFlag!=Const_Port_Status[EXT_ID_DEMAND].MultiFlag)  //��������������һ�����ӣ���������һֱ
     ASSERT(A_WARNING,0);
     
  if(Mode_Word.Mode[2].Bit.Bit4==0)  //ģʽ��3 bit4:�����ź������ʽ,1:����������,0:������ʱ��
    return 0;
  
  if(Const_Port_Status[EXT_ID_DEMAND].MultiFlag==2)  //���Ǹ��϶��ӣ��������
      return 1;
  
  Len=Get_DLT645_Data(0xCA12,&Temp,&Temp,1,&Err);
  if(NO_ERR==Err && 1==Len)
  {
    if(Temp&0x03==0x02)
     return 1;  
  }  
  return 0;
}
/********************************************************************************
INT8U  Get_Slipe_Out_En(void)
�������ܣ�����ģʽ�֣���ȡ����ʱ�䵽���ʹ��
��ڣ�  
���أ�
    ��
********************************************************************************/
INT8U Get_Slipe_Out_En(void)
{
  INT8U Err,Len;
  INT8U Temp;
  
  if(Const_Port_Status[EXT_ID_DEMAND].MultiFlag!=Const_Port_Status[EXT_ID_DEMAND].MultiFlag)  //��������������һ�����ӣ���������һֱ
     ASSERT(A_WARNING,0);
  
  if(Mode_Word.Mode[2].Bit.Bit4==1)  //ģʽ��3 bit4:�����ź������ʽ,1:����������,0:������ʱ��
    return 0;
   
  if(Const_Port_Status[EXT_ID_SLIPE].MultiFlag==2) //���Ǹ��϶��ӣ��������
      return 1;
      
  Len=Get_DLT645_Data(0xCA12,&Temp,&Temp,1,&Err);  //���϶���
  if(NO_ERR==Err && 1==Len)
  {
    if(Temp&0x03==0x02)
     return 1;  
  }  
  return 0;
}
/********************************************************************************
INT8U  Get_FeeAlarm_Out_En(void)
�������ܣ�����ģʽ�֣���ȡǷ�ѱ������ʹ��
��ڣ�  
���أ�
    ��
********************************************************************************/
INT8U Get_FeeAlarm_Out_En(void)
{
  INT8U Err,Len;
  INT8U Temp;
  
  Len=Get_DLT645_Data(0xCA12,&Temp,&Temp,1,&Err);
  if(NO_ERR==Err && 1==Len)
  {
    if(Temp&0x03==0x03 && Mode_Word.Mode[1].Bit.Bit5==1)   //ģʽ��2 bit5��1��Ԥ���ѹ���
     return 1;  
  }  
  return 0;
}
/********************************************************************************
INT8U  Get_GridAlarm_Out_En(void)
�������ܣ�����ģʽ�֣���ȡ����ʱ�䵽���ʹ��
��ڣ�  
���أ�
    ��
********************************************************************************/
INT8U Get_GridAlarm_Out_En(void)
{
  INT8U Err,Len;
  INT8U Temp;
  
  Len=Get_DLT645_Data(0xCA12,&Temp,&Temp,1,&Err);
  if(NO_ERR==Err && 1==Len)
  {
    if(Temp&0x03==0x03 && Mode_Word.Mode[1].Bit.Bit4==1)  //ģʽ��2 bit4��1�����ع��ܹ���
     return 1;  
  }  
  return 0;
}

/********************************************************************************
void void Init_All_Device_Port(INT8U Mode)
�������ܣ���ʼ�����ж˿�,
��ڣ�   ���ݲ�ͬ״̬���趨�˿�״̬
���أ�
    ��
********************************************************************************/
void Init_All_Port(INT32U Mode)
{
   INT8U i;
   
  for(i=MIN_PORT_DI;i<=MAX_PORT_DI;i++)
  {
    if(0==Const_Port_Status[i].NeedInit)
    {
      Ext_Port_Hander[i].InitFlag=1;
      continue;
    }
    
    if(SYS_NORMAL==Mode)
    {
      Const_Port_Status[i].FuncPtr(Const_Port_Status[i].InitLevel);    //����ģʽ�������Ϊ��Чλ
    }
    //����ģʽ���Ѿ���Init_All_IO_XX()��������
    
    Ext_Port_Hander[i].InitFlag=1;
  }
}
/********************************************************************************
void Port_Level_Out(INT8U Id,INT16U StartOrEnd)
�������ܣ����ⲿ�����ŵĵ�ƽ�����������
��ڣ�
    Id -------�ⲿ���ӹ���Id����
    StartOrEnd---------����ߵ�ƽ���ǵ͵�
���أ�
    ��
ע�⣺������ڲ�����Port_Pulse_Out����һ�£�
********************************************************************************/
void Port_Level_Out(INT8U Id,INT8U Level)
{
  if(Id<MIN_PORT_DI || Id>MAX_PORT_DI)
    return ;
 
  if(Const_Port_Status[Id].LevelProprty==PULSE_MODE)
    return ;
  
  //��ƽģʽ���,ֱ�ӶԶ˿������ƽ
  if(Const_Port_Status[Id].ValidLevel==Level)  //����
  {
    Const_Port_Status[Id].FuncPtr(Const_Port_Status[Id].ValidLevel);
  }
  else
  {
      Const_Port_Status[Id].FuncPtr(!Const_Port_Status[Id].ValidLevel);
  }
}

/********************************************************************************
void Ext_Port_Out(INT8U Id,INT16U MsCounts)
�������ܣ����ⲿ�����ŵĳ��������������
��ڣ�
    Id -------�ⲿ���ӹ���Id����
    PulseWidth ---�ⲿ����Ϊ�������ʱ�������ȣ���λms����ƽ���ʱ���˲�����Ч
���أ�
    ��
********************************************************************************/
void Port_Pulse_Out(INT8U Id,INT16U PulseWidth)
{
  if(Id<MIN_PORT_DI || Id>MAX_PORT_DI)
    return ;
  
 
  //����ģʽ������˿������ExtPort_xMs_Hook�е��á�  
  if(PulseWidth==0)  //������ӵ���ʱ���
  {
    Ext_Port_Hander[Id].Status=0;
    Ext_Port_Hander[Id].CurCount=0;
    Ext_Port_Hander[Id].CurCountBak=0;
    Ext_Port_Hander[Id].LoopCount=0;
    return ;
  }
  
  if(Const_Port_Status[Id].LoopFlag)
    Ext_Port_Hander[Id].LoopCount++;
  else
    Ext_Port_Hander[Id].LoopCount=1;
  
  Ext_Port_Hander[Id].CurCountBak=PulseWidth/MS_HOOK_NUM;   //ÿ�ζ�����һ��
  if(Ext_Port_Hander[Id].LoopCount==1)   //�״�����
  {    
    Ext_Port_Hander[Id].Status=1;
  }
}
/********************************************************************************
void Port_Out_Pub(INT8U Id,INT16U Para)
��ڣ�
    Id -------���ӹ���Id����
    Para -------���ڵ�ƽ���壬PORT_START ��ʾ������Ч��ƽ��PORT_END Ϊ��Ч��ƽ�����������������ʾ������
���أ�
    ��
********************************************************************************/
void Port_Out_Pub(INT8U Id,INT16U Para)
{
  if(Id<MIN_PORT_DI || Id>MAX_PORT_DI)
    return ;
  
  if(Const_Port_Status[Id].MultiFlag) //���Ǹ��϶���
  {
    if(Const_Port_Status[Id].MultiPortEn==0 || Const_Port_Status[Id].MultiPortEn()==0) //�Ǹ��϶��ӣ���������ö������
      return ;
  }
    
  if(Const_Port_Status[Id].LevelProprty==LEVEL_MODE)      //��ƽ��ʽ
  {
    if(PORT_START==Para)  //�����������Ч��ƽ
      Port_Level_Out(Id,Const_Port_Status[Id].ValidLevel);
    
     if(PORT_END==Para)   //�����������Ч��ƽ
      Port_Level_Out(Id,!(Const_Port_Status[Id].ValidLevel));
     
     return ;
  }
  
  //���巽ʽ
  Port_Pulse_Out(Id,Para); 
}
/********************************************************************************
void Beep_For_Measu_Alarm_PUCK(void)
�������ܣ���������������
��ڣ�
���أ�
    ��
********************************************************************************/
void Beep_For_Measu_Alarm_PUCK(void)
{
  //���У��¼����¼���¼�ж���������
 //Port_Out_Pub(INTER_ID_ALARM_BEEP,BEEP_MODE_100);
 //Port_Out_Pub(INTER_ID_ALARM_DIS,150); 
}
/********************************************************************************
void Beep_For_OSC_Alarm_PUCK(void)
�������ܣ���������������
��ڣ�
���أ�
    ��
********************************************************************************/
void Beep_For_OSC_Alarm_PUCK(void)
{
 Port_Out_Pub(INTER_ID_ALARM_BEEP,BEEP_MODE_150); 
 Port_Out_Pub(INTER_ID_ALARM_DIS,150); 
}
/********************************************************************************
void Beep_For_Test_Alarm_PUCK(void)
�������ܣ���������������
��ڣ�
���أ�
    ��
********************************************************************************/
void Beep_For_Test_Alarm_PUCK(void)
{
 Port_Out_Pub(INTER_ID_ALARM_BEEP,BEEP_MODE_200);
}
/********************************************************************************
void ExtPort_xMs_Hook(void)
�������ܣ�1ms���ⲿIO�ڵĹ��Ӻ���
��ڣ�
���أ�
    ��
********************************************************************************/
//ms�˿ڹ��Ӻ���,���뼶��λ��MS_HOOK_NUM
void ExtPort_xMs_Hook(void)
{
  INT8U i;
  
  for(i=MIN_PORT_DI;i<=MAX_PORT_DI;i++)
  {
    if(Const_Port_Status[i].NeedInit && 0==Ext_Port_Hander[i].InitFlag)
      continue ;
    
    if((Ext_Port_Hander[i].LoopCount)&&(Const_Port_Status[i].LevelProprty==PULSE_MODE))
    {
      switch(Ext_Port_Hander[i].Status)
      {
      case 0:   //�޶���
        break;
      case 1:                                 //�ֻ�����
        //���ö˿ڲ�����������ƽ��PULSE_OUT
        Const_Port_Status[i].FuncPtr(Const_Port_Status[i].ValidLevel);
        Ext_Port_Hander[i].Status=2;
        break;
      case 2:  //������
        if(Ext_Port_Hander[i].CurCount>=Ext_Port_Hander[i].CurCountBak)  //������һ�ֻ�
        {
            Ext_Port_Hander[i].CurCount=0;
            Ext_Port_Hander[i].Status=1;
            Ext_Port_Hander[i].LoopCount--;   
            Const_Port_Status[i].FuncPtr(!Const_Port_Status[i].ValidLevel);
            if(Ext_Port_Hander[i].LoopCount==0) //����
            { 
              Ext_Port_Hander[i].Status=0;     //����
              Ext_Port_Hander[i].CurCount=0;
              Ext_Port_Hander[i].CurCountBak=0;   //
            }
         }
         else                               //��ǰ�ֻ�
         {  
           Ext_Port_Hander[i].CurCount++;         
         }
        break;
      }
    }
  }
}
