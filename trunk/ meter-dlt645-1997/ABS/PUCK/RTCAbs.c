#define RTC_ABS_PUCK
#include "Includes.h"
#include "Pub_PUCK.h"


/**********************************************************************************
�������ܣ���ȡ�ⲿʱ�ӵ�״̬
**********************************************************************************/
INT8U Read_Ext_RTC_Status(void)
{
  INT8U temp,Re;  
  Re=DS3231_Read_Buf(0xf,1,&temp);
  if(0==Re)
    ASSERT(A_WARNING,0);

  Re=EXT_RTC_OK;
  if(GET_BIT(temp,7))    //OSFֹͣ
  {
    CLR_BIT(temp,7);
    DS3231_Write_Buf(0x0f,1,&temp);
    Re|=EXT_RTC_COUNT_STOP;
    DEBUG_PRINT(PUCK,1,"Ext_RTC Error----->Found EXT RTC Osc Stop!");
  } 
  return Re;
}

/**********************************************************************************
�������ܣ����ʱ���Ƿ�æ
��ڣ�
���ڣ�
**********************************************************************************/
INT8U Check_ExtRTC_Busy(void)
{
  INT8U temp,Re;  
  Re=DS3231_Read_Buf(0xf,1,&temp);
  if(0==Re)
    ASSERT(A_WARNING,0);

  Re=EXT_RTC_OK;  
  if(GET_BIT(temp,2))
  {
    Re|=EXT_RTC_BUSY;
    DEBUG_PRINT(PUCK,1,"Ext_RTC Error----->Found EXT RTC BUSY!");    
  }   
  return Re;
}
/**********************************************************************************
�������ܣ���ʼ���ⲿ������
��ڣ�
      Flag----0��ʾ�ر��ⲿ�����壻1��ʾʹ���ⲿ������
���ڣ�
**********************************************************************************/
void Init_ExtRTC_Pulse(INT8U Flag)
{
  INT8U temp;
  /*
  Re=DS3231_Read_Buf(0xe,1,&temp);
  ASSERT(A_WARNING,1==Re);  */
  if(!Flag)        //�ر��ⲿ������
    temp=0x04;//temp|=0x04;      
  else             //���ⲿ������
    temp=0x00;//temp&=0xE0;
  
  if(DS3231_Write_Buf(0x0e,1,&temp)==0)
    ASSERT(A_WARNING,0);  
  if(Flag)
     Port_Out_Pub(EXT_ID_SEC_EN,PORT_START);
}
/**********************************************************************************
�������ܣ����ⲿʵʱʱ��
��ڣ�
Dst---------------Ŀ�껺����,BCD��,˳��Ϊ�ӵ͵���:��/��/ʱ/����/��/��/��
DstLen-------------Ŀ�껺��������
���ڣ�1---------��ȡ�ɹ���0--------��ȡʧ��
ע��:
1: ���������ݲ����BCD��ĺϷ���;
2: ���������ݲ������/��/��/����/ʱ/��/��ĺϷ���;
**********************************************************************************/
INT8U Read_ExtRTC_PUCK(INT8U *Dst,INT8U DstLen)
{
 INT8U Flag;
 
 if(DstLen!=7)
 {   
   DEBUG_PRINT(PUCK,1,"Ext_RTC Error----->Dst_Buf Length is Error!");
   return 0;
 }
 
 if(Check_ExtRTC_Busy()!=EXT_RTC_OK)
   return 0;
 
 Flag=DS3231_Read_Buf(0,7,Dst);
 return Flag;
}
/**********************************************************************************
�������ܣ�д�ⲿʵʱʱ��
��ڣ�
Src---------------˳��Ϊ�ӵ͵���:��/��/ʱ/����/��/��/��
���ڣ�1---------дʱ�ӳɹ���0--------дʱ��ʧ��
ע��:
1: д������ݲ����BCD��ĺϷ���;
2: д������ݲ������/��/��/����/ʱ/��/��ĺϷ���;
**********************************************************************************/
INT8U Write_ExtRTC_PUCK(INT8U *Src)
{
  INT8U Flag;
  
  if(Check_ExtRTC_Busy()!=EXT_RTC_OK)
   return 0;
  
  Flag=DS3231_Write_Buf(0,7,Src);
  return Flag;
}


/**********************************************************************************
�������ܣ�����ⲿʱ��״̬
��ڣ�
���ڣ� EXT_RTC_OK��EXT_RTC_NOACK��EXT_RTC_CLOCK_ERROR��EXT_RTC_FIRST_PWRON��EXT_RTC_COUNT_STOP

void Chcek_Ext_RTC_Status(void)
{
  
  DS3231_Read_Buf

  
  
  
}
**********************************************************************************/
/**********************************************************************************
�������ܣ����ⲿʵʱʱ��
��ڣ�
Dst---------------Ŀ�껺����,BCD��,˳��Ϊ�ӵ͵���:��/��/ʱ/����/��/��/��
DstLen-------------Ŀ�껺��������
���ڣ�1---------��ȡ�ɹ���0--------��ȡʧ��
ע��:
1: ���������ݲ����BCD��ĺϷ���;
2: ���������ݲ������/��/��/����/ʱ/��/��ĺϷ���;
**********************************************************************************/
INT8U Read_InterRTC_PUCK(INT8U *Dst,INT8U DstLen)
{
  struct RTCCounterValue temp;
  INT8U Flag;
  
  if(DstLen!=7)
  {   
    DEBUG_PRINT(PUCK,1,"Inter_RTC Error----->Dst_Buf Length is Error!");
    return 0;
  }
  Flag=RTC_CounterGet( &temp );
  
  if(Flag!=MD_OK)
  {
    DEBUG_PRINT(PUCK,1,"Inter_RTC Error----->Return Value Not Equal MD_OK!");
    return 0;
  }
  
  Dst[0]=temp.Sec;
  Dst[1]=temp.Min;
  Dst[2]=temp.Hour;
  Dst[4]=temp.Day;
  Dst[3]=temp.Week;
  Dst[5]=temp.Month;
  Dst[6]=temp.Year; 
  return 1;
}
/**********************************************************************************
�������ܣ�д�ⲿʵʱʱ��
��ڣ�
Src---------------˳��Ϊ�ӵ͵���:��/��/ʱ/����/��/��/��
���ڣ�1---------дʱ�ӳɹ���0--------дʱ��ʧ��
ע��:
1: д������ݲ����BCD��ĺϷ���;
2: д������ݲ������/��/��/����/ʱ/��/��ĺϷ���;
**********************************************************************************/
INT8U Write_InterRTC_PUCK(INT8U *Src)
{
 struct RTCCounterValue CwriteVal;
  CwriteVal.Sec = Src[0];
  CwriteVal.Min = Src[1];
  CwriteVal.Hour = Src[2];
  CwriteVal.Day = Src[4];
  CwriteVal.Week= Src[3];
  CwriteVal.Month = Src[5];
  CwriteVal.Year = Src[6]; 
  RTC_CounterEnable( );
  RTC_CounterSet(CwriteVal );     
  RTC_CounterEnable( );
  return 1;
}

/**********************************************************************************
�������ܣ���sleepģʽ�ڣ����پ����£���RTC(3���ݴ�)
��ڣ� Time:  �֡�ʱ���ա��¡���
���ڣ�1----------------�ɹ���0----------------ʧ��
**********************************************************************************/ 
void Refresh_CPU_RTC(void)
{
    INT8U i,times;
    
   for(times=0;times<3;times++)
   {
      RWAIT = 1;
      for(i = 0; i<(RTC_WAITTIME/8);i++ ) 
      {
        if(RWST)
          break;
      }
      Clear_CPU_Dog();
      
      if(i==(RTC_WAITTIME/8-1))
        continue;  
      
      CPU_RTC_Time.RTC.Sec=SEC;
      CPU_RTC_Time.RTC.Min=MIN;
      CPU_RTC_Time.RTC.Hour=HOUR;
      CPU_RTC_Time.RTC.Week=WEEK;
      CPU_RTC_Time.RTC.Date=DAY;
      CPU_RTC_Time.RTC.Month=MONTH;
      CPU_RTC_Time.RTC.Year=YEAR;
      SET_VAR_CS_PUCK(CPU_RTC_Time.RTC);
      RWAIT=0;
      for ( i = 0; i < RTC_WAITTIME/8; i++) 
      {
        if(RWST==0)
          return ;
      }
      Clear_CPU_Dog();
      
      if(i==(RTC_WAITTIME/8-1)) 
        continue;
    }
}

/**********************************************************************************
�������ܣ���ȡCPU Sram ��RTC
��ڣ�
Dst---------------Ŀ�껺����,BCD��,˳��Ϊ�ӵ͵���:��/��/ʱ/����/��/��/��
DstLen-------------Ŀ�껺��������
���ڣ�1---------��ȡ�ɹ���0--------��ȡʧ��
ע��:
1: ���������ݲ����BCD��ĺϷ���;
2: ���������ݲ������/��/��/����/ʱ/��/��ĺϷ���;
**********************************************************************************/
INT8U Get_Soft_RTC_PUCK(INT8U *Dst,INT8U DstLen)
{
  if(DstLen!=7)
    return 0;
  
  if(CHECK_STRUCT_VAR(CPU_RTC_Time)==0)   //���ͷβ
  {
    ASSERT(A_WARNING,0);
    return 0;
  }
  
  if(CHK_VAR_CS_PUCK(CPU_RTC_Time.RTC)==0)          //���У���
  {
    ASSERT(A_WARNING,0);
    return 0;
  }
  if(Check_BCD_Data((void *)(&CPU_RTC_Time.RTC),sizeof(CPU_RTC_Time.RTC)-1)==0)
    return 0;
  
  mem_cpy(Dst,(void *)(&CPU_RTC_Time.RTC),sizeof(CPU_RTC_Time.RTC)-1,Dst,sizeof(CPU_RTC_Time.RTC)-1);
  return 1;
}

/***********************************************************************
�������ܣ�����sleep�µ���ʱ�ӣ�3������
��ڣ�Flag:ID_EXT_RTC�Ⱥ�
���ڣ���
***********************************************************************/
void Set_Soft_RTC_PUCK(INT8U Flag)
{   
 INT8U i;
 static INT8U Entry=0;
 
 if(0x51==Entry)
 {
  if(CHECK_STRUCT_VAR(CPU_RTC_Time)==0 || CHK_VAR_CS_PUCK(CPU_RTC_Time.RTC)==0)   //���ͷβ ,���У���
  {
    ASSERT(A_WARNING,0);
  }   
 }
 
 Entry=0x51;
 for(i=0;i<3;i++)
 {
     switch(Flag)
     {
       case ID_EXT_RTC:
         Read_ExtRTC_PUCK((INT8U *)(&CPU_RTC_Time.RTC),7);
       break;
         
       case ID_CPU_RTC:
         Read_InterRTC_PUCK((INT8U *)(&CPU_RTC_Time.RTC),7);
       break;
       
        case ID_RAM_RTC:
          mem_cpy((void *)(&CPU_RTC_Time.RTC),(void *)(&Cur_Time1),sizeof(CPU_RTC_Time.RTC)-1,\
                  (void *)(&CPU_RTC_Time.RTC),sizeof(CPU_RTC_Time.RTC)-1);
       break;         
     }
    
     if(Check_BCD_Data((void *)(&CPU_RTC_Time.RTC),sizeof(CPU_RTC_Time.RTC)-1)==0)
     {
       DEBUG_PRINT(PUCK,1,"Sleep RTC Get Error(Src=%d):----->%x-%x-%x (%x) %x:%x:%x",Flag,CPU_RTC_Time.RTC.Year,CPU_RTC_Time.RTC.Month,\
       CPU_RTC_Time.RTC.Date,CPU_RTC_Time.RTC.Week,CPU_RTC_Time.RTC.Hour,CPU_RTC_Time.RTC.Min,CPU_RTC_Time.RTC.Sec);
     }
     else
     {
       INIT_STRUCT_VAR(CPU_RTC_Time);    //����ͷβ
       SET_VAR_CS_PUCK(CPU_RTC_Time.RTC);  //����У���
       return ;
     }       
  }   
  DEBUG_PRINT(PUCK,1,"CPU Soft RTC Got Failed!");
  INIT_STRUCT_VAR(CPU_RTC_Time);           //����ͷβ
  SET_VAR_CS_PUCK(CPU_RTC_Time.RTC);       //����У���
}
