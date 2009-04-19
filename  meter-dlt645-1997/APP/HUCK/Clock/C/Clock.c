#define CLOCK_C
#include "Includes.h"
/*
INT8U Read_PHY_Mem_PUCK(INT8U MemNo,INT32U Offset,void *pDst,INT16U RD_Len,void *pDst_Start,INT16U DstLen);
INT8U Write_PHY_Mem_PUCK(INT8U MemNo,INT32U Offset,void *pSrc,INT16U SrcLen);
INT8U Write_ExtRTC_PUCK(INT8U *Src);
INT8U Read_ExtRTC_PUCK(INT8U *Dst,INT8U DstLen);
*/
/*
void init_DS3231(void);
��ds3231ʱ�䣬���������ֵ��{�룬�֣�ʱ�����ڣ��գ��£���}
void Read_DS3231(unsigned char *src);
дds3231ʱ�䣬д�������ֵ��{�룬�֣�ʱ�����ڣ��գ��£���}
��ȷ����1��������err
unsigned char Write_DS3231(unsigned char *src);
*/

//�ڻ��ѵ�����¸���ʱ��
INT8U Resume_Clock_Update()
{
  INT8U Re;
  S_BCD_Time Temp_Time;
  
  Re = CHECK_STRUCT_SUM(Clock_Info);
  ASSERT(A_WARNING, 1==Re);
  
  Re = 0;
  
  if(Get_Time_From_EXT_RTC((S_BCD_Time *)&Temp_Time))
    Re=1;
  
  if(Read_Ext_RTC_Status()!=EXT_RTC_OK)//�ⲿʱ���Ƿ�λ?
  {
    DEBUG_PRINT(HUCK,DEBUG_0,"Read_Ext_RTC_Status Error!");
    ASSERT(A_WARNING,0);
    Re=0;
  }
  
  if(Re==0)//��ȡ�ⲿʱ�����ݴ�����߶�ȡ������������0���ȡ�ڲ�ʱ�ӻ����ڴ��е�ʱ������
  {
    DEBUG_PRINT(HUCK,DEBUG_0,"Get_Time_From_EXT_RTC error,Set_INTER_RTC_Flag=%d",Clock_Info.Set_INTER_RTC_Flag);
    Get_Timer_From_CPU_Inter(&Temp_Time);
    Set_Time_To_EXT_RTC((S_BCD_Time *)&Temp_Time);//�����ⲿʱ��
  }
  
  Clock_Info.Set_INTER_RTC_Flag=1;//ͬ��һ���ڲ�RTC
  Set_Time_To_INTER_RTC((S_BCD_Time *)&Temp_Time);
 
 
  //����õ�ʱ�����ݸ��Ƶ�Cur_Time1,Cur_Time_Bak��Cur_Time0
  mem_cpy((void *)&Cur_Time1,&Temp_Time,sizeof(Temp_Time),(void *)&Cur_Time1,sizeof(Cur_Time1));
  SET_STRUCT_SUM(Cur_Time1);
  
  mem_cpy((void *)&Cur_Time_Bak,&Temp_Time,sizeof(Temp_Time),(void *)&Cur_Time_Bak,sizeof(Cur_Time_Bak));
  SET_STRUCT_SUM(Cur_Time_Bak); 
  
  Convert_BCD_2_HEX_Time((S_BCD_Time *)&Cur_Time1,(S_HEX_Time *)&Cur_Time0);
  
  Clock_Info.Clock_Ready_Flag=1;
  SET_STRUCT_SUM(Clock_Info);//�������ڴ�����У��� 
  return Re;
}


//���ⲿRTC��ȡʱ������
INT8U Get_Time_From_EXT_RTC(S_BCD_Time *pBCD_Time)
{
  INT8U Re,i;
  INT8U Temp[10];
  
  for(i=0;i<3;i++)
  {
    Re=Read_ExtRTC_PUCK(Temp,7);
    ASSERT(A_WARNING,1==Re);
    DEBUG_PRINT(HUCK,DEBUG_0,"Get_EXT_Time:%x-%x-%x %x:%x:%x,Week:%x",Temp[6],Temp[5],Temp[4],Temp[2],Temp[1],Temp[0],Temp[3]);
    if(1==Re)
    {
      if(Temp[3]>=7)//DLT645��DS3231���������ݸ�ʽ ��һ��
        Temp[3]=0;
      pBCD_Time->Sec=Temp[0];
      pBCD_Time->Min=Temp[1];
      pBCD_Time->Hour=Temp[2];
      pBCD_Time->Week=Temp[3];
      pBCD_Time->Date=Temp[4];
      pBCD_Time->Month=Temp[5];
      pBCD_Time->Year=Temp[6];
      Set_STRUCT_Sum(pBCD_Time,sizeof(S_BCD_Time),pBCD_Time->CS,sizeof(pBCD_Time->CS));
      if(Check_BCD_Time(pBCD_Time))//������ݸ�ʽ?
        return 1;
    }
    OS_TimeDly_Ms(200);
  }
  
  return 0;
}

//��ʱ�����õ��ⲿRTC
INT8U Set_Time_To_EXT_RTC(S_BCD_Time *pBCD_Time)
{
  INT8U i;
  INT8U Re;
  INT8U Temp[10];
  
  Re=Check_BCD_Time(pBCD_Time);
  if(ASSERT(A_WARNING,1==Re))
    return 0;
  
  for(i=0;i<3;i++)
  {
    Temp[0]=pBCD_Time->Sec;
    Temp[1]=pBCD_Time->Min;
    Temp[2]=pBCD_Time->Hour;
    Temp[3]=pBCD_Time->Week;
    Temp[4]=pBCD_Time->Date;
    Temp[5]=pBCD_Time->Month;
    Temp[6]=pBCD_Time->Year;
    if(Temp[3]==0 || Temp[3]>7)//DLT645��DS3231���������ݸ�ʽ ��һ��
      Temp[3]=7;
    
    DEBUG_PRINT(HUCK,DEBUG_0,"Set_EXT_Time:%x-%x-%x %x:%x:%x,Week:%x",Temp[6],Temp[5],Temp[4],Temp[2],Temp[1],Temp[0],Temp[3]);
    
    if(Write_ExtRTC_PUCK(Temp))
      return 1;
      
    OS_TimeDly_Ms(200);
  }
  ASSERT(A_WARNING,0);
  return 0;
}

//��Time�������õ�pBCD_Time������
//Time���ݵĸ�ʽ��--sec,min,hour,week,date,month,year
void Set_BCD_Time(INT8U Time[],S_BCD_Time *pBCD_Time)
{
  if(Time[3]>=7)//DLT645��DS3231���������ݸ�ʽ ��һ��
    Time[3]=0;
  pBCD_Time->Sec=Time[0];
  pBCD_Time->Min=Time[1];
  pBCD_Time->Hour=Time[2];
  pBCD_Time->Week=Time[3];
  pBCD_Time->Date=Time[4];
  pBCD_Time->Month=Time[5];
  pBCD_Time->Year=Time[6];  
  Set_STRUCT_Sum(pBCD_Time,sizeof(S_BCD_Time),pBCD_Time->CS,sizeof(pBCD_Time->CS));  
}

//���ڲ�RTC��ȡʱ������
INT8U Get_Time_From_INTER_RTC(S_BCD_Time *pBCD_Time)
{
  INT8U Re;
  INT8U Temp[10];
  
  Re=Read_InterRTC_PUCK(Temp,7);
  ASSERT(A_WARNING,1==Re);
  //DEBUG_PRINT(HUCK,DEBUG_0,"Get_INTER_Time:%x-%x-%x %x:%x:%x,Week:%x",Temp[6],Temp[5],Temp[4],Temp[2],Temp[1],Temp[0],Temp[3]);
  if(1==Re)
  {/*
    if(Temp[3]>=7)//DLT645��DS3231���������ݸ�ʽ ��һ��
      Temp[3]=0;
    pBCD_Time->Sec=Temp[0];
    pBCD_Time->Min=Temp[1];
    pBCD_Time->Hour=Temp[2];
    pBCD_Time->Week=Temp[3];
    pBCD_Time->Date=Temp[4];
    pBCD_Time->Month=Temp[5];
    pBCD_Time->Year=Temp[6];
    Set_STRUCT_Sum(pBCD_Time,sizeof(S_BCD_Time),pBCD_Time->CS,sizeof(pBCD_Time->CS));    
    */
    Set_BCD_Time(Temp,pBCD_Time);

    Re=Check_BCD_Time(pBCD_Time);//������ݸ�ʽ?
    if(ASSERT(A_WARNING,1==Re))
      return 0;
    else 
      return 1;
  }
  else
    return 0;
}

//��ʱ�����õ��ڲ�RTC
INT8U Set_Time_To_INTER_RTC(S_BCD_Time *pBCD_Time)
{ 
  INT8U Re;
  INT8U Temp[10];
  
  Re=Check_BCD_Time(pBCD_Time);
  if(ASSERT(A_WARNING,1==Re))
    return 0;
  Temp[0]=pBCD_Time->Sec;
  Temp[1]=pBCD_Time->Min;
  Temp[2]=pBCD_Time->Hour;
  Temp[3]=pBCD_Time->Week;
  Temp[4]=pBCD_Time->Date;
  Temp[5]=pBCD_Time->Month;
  Temp[6]=pBCD_Time->Year;
  if(Temp[3]==0 || Temp[3]>7)//DLT645��DS3231���������ݸ�ʽ ��һ��
    Temp[3]=7;
  
  Re=Write_InterRTC_PUCK(Temp);
  return Re;
}

//�ж�ʱ�����ȷ��
INT8U _Check_HEX_Time(INT8U Time[])
{
  if(Time[T_MIN]<60 && Time[T_HOUR]<24 &&\
     Time[T_DATE]>0 && Time[T_DATE]<32 &&\
     Time[T_MONTH]>0 && Time[T_MONTH]<13 &&\
     Time[T_YEAR]<=99)
    return 1;
  else
  {
    //ASSERT(A_WARNING,0);
    return 0;
  }
}

//�ж�ʱ�����ȷ��
INT8U _Check_BCD_Time(INT8U Time[])
{
  if(Check_BCD_Data(Time,5)==0)
    return 0;
  
  if(Time[T_MIN]<0x60 && Time[T_HOUR]<0x24 &&\
     Time[T_DATE]>0 && Time[T_DATE]<0x32 &&\
     Time[T_MONTH]>0 && Time[T_MONTH]<0x13 &&\
     Time[T_YEAR]<=0x99)
    return 1;
  else
  {
    ASSERT(A_WARNING,0);
    return 0;
  }
}

//���һ��S_HEX_Time�����Ƿ���ȷ
INT8U Check_HEX_Time(S_HEX_Time *pTime)
{
  if(Check_STRUCT_Sum(pTime,sizeof(S_HEX_Time),pTime->CS,sizeof(pTime->CS)))
  {
    if(_Check_HEX_Time(pTime->Time))
      return 1;
  }
  ASSERT(A_WARNING,0);
  return 0;
}
/*
  INT8U Sec;
  INT8U Min;
  INT8U Hour;
  INT8U Week;
  INT8U Date;
  INT8U Month;
  INT8U Year;

*/
//���һ��S_BCD_Time�����Ƿ���ȷ
INT8U Check_BCD_Time(S_BCD_Time *pTime)
{
  if(Check_STRUCT_Sum(pTime,sizeof(S_BCD_Time),pTime->CS,sizeof(pTime->CS))==1 &&
     Check_BCD_Data(pTime,S_OFF(S_BCD_Time,CS))==1)
  {
    if(pTime->Sec<0x60 && pTime->Min<0x60 && pTime->Hour<0x24 &&\
       pTime->Date>0x00 && pTime->Date<0x32 &&\
       pTime->Month>0x00 && pTime->Month<0x13 &&\
       pTime->Year<=0x99 && pTime->Week<7)
      return 1;
  }
  ASSERT(A_WARNING,0);
  return 0;
}

INT8U Set_Time_EXT_INTER_Ram_RTC(S_BCD_Time * pBCD_Time)
{
  if(Set_Time_To_EXT_RTC(pBCD_Time))
  {
    if(Set_Time_To_INTER_RTC(pBCD_Time))
    {
      //mem_cpy((S_BCD_Time *)&Cur_Time1,&TempTime,sizeof(TempTime),(S_BCD_Time *)&Cur_Time1,sizeof());
      Get_Time_From_INTER_RTC((S_BCD_Time *)&Cur_Time1);
      Convert_BCD_2_HEX_Time((S_BCD_Time *)&Cur_Time1,(S_HEX_Time *)&Cur_Time0);
      return 1;
    }
  } 
  ASSERT(A_WARNING,0);
  return 0;
}
//ʱ�Ӵ���
//ÿ��GET_CLOCK_PERIOD��ˢ��һ��ʱ��
void Clock_Proc()
{
  INT8U Re;
  S_BCD_Time TempTime;

  static S_Int32U Sec_Bak={CHK_BYTE,0xFFFFFFFF,CHK_BYTE};
  static S_Int8U Sec={CHK_BYTE,0xFF,CHK_BYTE};
  
  //��ʱˢ��ʱ�ӣ���ģ����ʱ��
  Re=CHECK_STRUCT_VAR(Sec_Bak);
  ASSERT(A_WARNING,1==Re);
  
  if(Sec_Bak.Var!=Sec_Timer_Pub)//ʱ�����һ��
  {
    Sec_Bak.Var=Sec_Timer_Pub;
    
    Re=Check_BCD_Time((S_BCD_Time *)&Cur_Time1);
    if(ASSERT(A_WARNING,1==Re))//ʱ�䲻����ˢ��ʱ��
      Clock_Update();

    Set_Soft_RTC_PUCK(ID_RAM_RTC);//����ʱ�䵽PUCK��ʱ������
    
    Get_Time_From_INTER_RTC((S_BCD_Time *)&TempTime);//��ȡ�ڲ�ʱ��
    if(Check_Time_Diff(&TempTime,(S_BCD_Time *)&Cur_Time1,5)==0)//�ڴ��е��������ڲ�RTC����ʱ����5����,��Ϊ����
    {
      ASSERT(A_WARNING,0);
      Clock_Update();
      Get_Time_From_INTER_RTC((S_BCD_Time *)&TempTime);//���¶�ȡ�ڲ�ʱ��
    }
    
    mem_cpy((void *)&Cur_Time1,&TempTime,sizeof(TempTime),(void *)&Cur_Time1,sizeof(Cur_Time1));
    
    Sec.Var++; //��ʱ��+1
    if(Sec.Var>60 ||\
       Bcd2Hex_Byte(Cur_Time1.Min)!=Cur_Time0.Time[T_MIN])//һ����֮���ض�һ��Ӳʱ��
    {
      Clock_Update();
      Sec.Var=Bcd2Hex_Byte(Cur_Time1.Sec);
    }
  }
}

//���ڴ���ȡ��һ����ȷ��ʱ������
INT8U Get_Time_From_Ram_Rom(S_BCD_Time *pBCD_Time)
{
  INT8U Re,Err;
  INT8U i;
  
  Re=0;
  if(1==CHECK_STRUCT_SUM(Cur_Time1) &&\
     1==Check_BCD_Time((S_BCD_Time *)&Cur_Time1))
  {
     mem_cpy(pBCD_Time,(void *)&Cur_Time1,sizeof(Cur_Time1),pBCD_Time,sizeof(S_BCD_Time));
     Re=1;
  }
  else if(1==CHECK_STRUCT_SUM(Cur_Time_Bak) &&\
          1==Check_BCD_Time((S_BCD_Time *)&Cur_Time_Bak))
  {
     mem_cpy(pBCD_Time,(void *)&Cur_Time_Bak,sizeof(Cur_Time_Bak),pBCD_Time,sizeof(S_BCD_Time));
     Re=1;
  }
  else if(1==CHECK_STRUCT_SUM(Cur_Time0) &&\
          1==Check_HEX_Time((S_HEX_Time *)&Cur_Time0))
  {
    Convert_HEX_2_BCD_Time((S_HEX_Time *)&Cur_Time0,pBCD_Time);
    Re=1;
  }
  else if(Read_Storage_Data(TIME_PD,pBCD_Time,pBCD_Time,sizeof(S_BCD_Time),&Err))//��ȡ�洢ʱ��
  {
    Re = 1;
  }
  else if(Read_Storage_Data(TIME_BAK_PD,pBCD_Time,pBCD_Time,sizeof(pBCD_Time),&Err))//��ȡ�洢����ʱ��
  {
    Re = 1; 
  }
  else//û���κ�ʱ����������ȷ�ģ�����������~~
  {
    for(i=0; i<3; i++)//���´�Rom�ж�ȡʱ�����ݣ���3�Σ���ֹ����ԭ���¶�ȡ����
    {
      if(Read_Storage_Data(TIME_PD,pBCD_Time,pBCD_Time,sizeof(S_BCD_Time),&Err))//��ȡ�洢ʱ��
      {
        Re = 1;
        break;
      }
      OS_TimeDly_Ms(100);//��ʱ100ms
      if(Read_Storage_Data(TIME_BAK_PD,pBCD_Time,pBCD_Time,sizeof(pBCD_Time),&Err))//��ȡ�洢����ʱ��
      {
        Re = 1;
        break;
      } 
      OS_TimeDly_Ms(100);//��ʱ100ms
    } 
    
    if(Re == 0)
    {
      DEBUG_PRINT(HUCK,DEBUG_0,"No Correct Time Find,Use Def start Time");
      mem_cpy(pBCD_Time,(void *)&Def_BCD_Time,sizeof(Def_BCD_Time),pBCD_Time,sizeof(S_BCD_Time));
      Re=0;
    }
  }
  
  Set_STRUCT_Sum(pBCD_Time,sizeof(S_BCD_Time),pBCD_Time->CS,sizeof(pBCD_Time->CS));  
  return Re;
}

//��CPU�ڲ���ȡʱ������
void Get_Timer_From_CPU_Inter(S_BCD_Time *pBCD_Time)
{
    if(1==Clock_Info.Set_INTER_RTC_Flag &&\
       1==Get_Time_From_INTER_RTC(pBCD_Time) &&\
       1==Check_BCD_Time(pBCD_Time))
    {
      return;
    }
    else Get_Time_From_Ram_Rom(pBCD_Time);
  
}

//�������ʱ������֮��Ĳ��Ƿ�����?�Ƿ���Mins����֮��?
INT8U Check_Time_Diff(S_BCD_Time *pTime0,S_BCD_Time *pTime1,INT8U Mins)
{
  static S_HEX_Time TempTime;//��̬��������ռ�ö�ջ
  static S_HEX_Time Time0,Time1;
  
  Convert_BCD_2_HEX_Time(pTime0,&Time0);
  Convert_BCD_2_HEX_Time(pTime1,&Time1);
  
  if(Cmp_Time(&Time0,&Time1)==TIME_AFT)
  {
    Time_Dec(&Time0,Mins,UNIT_MIN,&TempTime);
    if(Cmp_Time(&TempTime,&Time1)==TIME_BEF)
      return 1;
  }
  else
  {
    Time_Inc(&Time0,Mins,UNIT_MIN,&TempTime);
    if(Cmp_Time(&TempTime,&Time1)==TIME_AFT)
      return 1; 
  }
  return 0;
  /*
  INT32U Sec0,Sec1;
  Sec0=mktime((INT16U)Bcd2Hex_Byte(pTime0->Year)+2000,\
              Bcd2Hex_Byte(pTime0->Month),\
              Bcd2Hex_Byte(pTime0->Date),\
              Bcd2Hex_Byte(pTime0->Hour),\
              Bcd2Hex_Byte(pTime0->Min),\
              0);
  Sec1=mktime((INT16U)Bcd2Hex_Byte(pTime1->Year)+2000,\
              Bcd2Hex_Byte(pTime1->Month),\
              Bcd2Hex_Byte(pTime1->Date),\
              Bcd2Hex_Byte(pTime1->Hour),\
              Bcd2Hex_Byte(pTime1->Min),\
              0);
  if((Sec0>Sec1 && Sec0-Sec1>180) ||\
    (Sec0<Sec1 && Sec1-Sec0>180))
      return 0;
  else
    return 1;
  */
}

void Set_Err_Time(S_BCD_Time *pBCD_Time)
{
  Err_Time[0]=pBCD_Time->Min;
  Err_Time[1]=pBCD_Time->Hour;
  Err_Time[2]=pBCD_Time->Date;
  Err_Time[3]=pBCD_Time->Month;
  Err_Time[4]=pBCD_Time->Year;  
}
//ʱ�ӵ�ˢ��
void Clock_Update()
{
  INT8U i;
  INT8U Re,EXT_RTC_Status_Err_Flag;
  S_BCD_Time Temp_Time;
  static S_BCD_Time Temp_Time0;
  static S_BCD_Time Temp_Time1;
  
  EXT_RTC_Status_Err_Flag=0;
  Re=CHECK_STRUCT_SUM(Clock_Info);
  if(ASSERT(A_WARNING,1==Re))//У����ȷ
  {
    mem_set((void *)&Clock_Info,0,sizeof(Clock_Info),(void *)&Clock_Info,sizeof(Clock_Info));
    SET_STRUCT_SUM(Clock_Info);
  }

  //�ȶ�ȡ�ⲿRTC�����ܷ������ȷ����,����ȷ�Ļ���������3��
  Re=0;//��ȡ��һ����ȷ��ʱ������
  if(Get_Time_From_EXT_RTC((S_BCD_Time *)&Temp_Time))
    Re=1;
  
  if(Read_Ext_RTC_Status()!=EXT_RTC_OK)
  {
    DEBUG_PRINT(HUCK,DEBUG_0,"Read_Ext_RTC_Status Error!");
    ASSERT(A_WARNING,0);
    
    if(Re==1)//���ܹ������ⲿʱ�����ݵ�����²���ʱ�Ӵ�����һ���ⲿʱ����Ӳ����������ܵ���1����дһ���¼���¼
    {
      Set_Err_Time((S_BCD_Time *)&Cur_Time1);
      Set_Event_Instant(ID_EVENT_RTCERR_RUN);//ʱ�����¼���¼
    }
    
    Re=0;    
    EXT_RTC_Status_Err_Flag=1;//��ȡ�ⲿRTC״̬����!
  }
  
  if(Re==1)
    Clock_Info.EXT_RTC_Err_Counts=0; 
  else
    Clock_Info.EXT_RTC_Err_Counts++;//�ⲿRTC�������  
  
  if(Re==0)//��ȡ�ⲿʱ�����ݴ�����߶�ȡ������������0���ȡ�ڲ�ʱ�ӻ����ڴ��е�ʱ������
  {
    DEBUG_PRINT(HUCK,DEBUG_0,"Get_Time_From_EXT_RTC error,Set_INTER_RTC_Flag=%d",Clock_Info.Set_INTER_RTC_Flag);
    Get_Timer_From_CPU_Inter(&Temp_Time);
  }

  //����ʱ���֮���ʱ���̫���ˣ�������10���ӣ�����������ȡ3�ν����һ��
  for(i=0;i<3;i++)
  {
    if(Check_Time_Diff(&Temp_Time,(S_BCD_Time *)&Cur_Time1,10)==0)//����ⲿʱ�����ڲ�ʱ�Ӳ��10����,���ض���ʱ�ӣ���ֹ����
    {
      OS_TimeDly_Ms(200);
      Get_Time_From_EXT_RTC(&Temp_Time);
    }
    else
      break;
  }
  
  if(Check_Time_Diff(&Temp_Time,(S_BCD_Time *)&Cur_Time1,10)==0)//����ⲿʱ�����ڲ�ʱ�Ӳ��10���ӣ�
  {
    if(Clock_Info.Set_INTER_RTC_Flag==1)//�ڲ�ʱ�����������ù�
    {
      Get_Time_From_INTER_RTC((S_BCD_Time *)&Temp_Time0);
      Convert_HEX_2_BCD_Time((S_HEX_Time *)&Cur_Time0,(S_BCD_Time *)&Temp_Time1);
      //CPU��4��ʱ�����ݶ�û�г���5���ӵĲ��Ϊ�ڲ�ʱ����ȷ
      if(Check_Time_Diff((S_BCD_Time *)&Temp_Time0,(S_BCD_Time *)&Cur_Time1,5)==1 &&\
         Check_Time_Diff((S_BCD_Time *)&Temp_Time0,(S_BCD_Time *)&Cur_Time_Bak,5)==1 &&\
         Check_Time_Diff((S_BCD_Time *)&Temp_Time0,(S_BCD_Time *)&Temp_Time1,5)==1)
      {
        //Set_Err_Time(&Temp_Time);
        //Set_Event_Instant(ID_EVENT_RTCERR_RUN);//ʱ�����¼���¼
        mem_cpy(&Temp_Time,(S_BCD_Time *)&Temp_Time0,sizeof(Temp_Time0),(S_BCD_Time *)&Temp_Time,sizeof(Temp_Time));
        EXT_RTC_Status_Err_Flag=1; 
      }
    }
  }
  
  Clock_Info.Set_INTER_RTC_Flag=1;//ͬ��һ���ڲ�RTC
  Set_Time_To_INTER_RTC((S_BCD_Time *)&Temp_Time);
  
  //������Ϊ0����������ζ�RTC����,�������ⲿRTC
  if(Clock_Info.EXT_RTC_Err_Counts>5 || EXT_RTC_Status_Err_Flag==1)//�ⲿʱ����������5��,�����ⲿʱ��
  {
    DEBUG_PRINT(HUCK,DEBUG_0,"Reset EXT RTC!!!!!!!!!!!!");
    Set_Time_To_EXT_RTC((S_BCD_Time *)&Temp_Time);//�����ⲿʱ��
    //Set_Event_Instant(ID_EVENT_RTCERR_RUN);//ʱ�����¼���¼
    Clock_Info.EXT_RTC_Err_Counts=0;
  }   
 
  //����õ�ʱ�����ݸ��Ƶ�Cur_Time1,Cur_Time_Bak��Cur_Time0
  mem_cpy((void *)&Cur_Time1,&Temp_Time,sizeof(Temp_Time),(void *)&Cur_Time1,sizeof(Cur_Time1));
  SET_STRUCT_SUM(Cur_Time1);
  
  mem_cpy((void *)&Cur_Time_Bak,&Temp_Time,sizeof(Temp_Time),(void *)&Cur_Time_Bak,sizeof(Cur_Time_Bak));
  SET_STRUCT_SUM(Cur_Time_Bak); 
  
  Convert_BCD_2_HEX_Time((S_BCD_Time *)&Cur_Time1,(S_HEX_Time *)&Cur_Time0);
  
  Clock_Info.Clock_Ready_Flag=1;
  SET_STRUCT_SUM(Clock_Info);//�������ڴ�����У���
}


//S_BCD_Timeת��ΪS_HEX_Time
//ת���ɹ�����1��ʧ�ܷ���0,ʧ��������ԭ���ݸ�ʽ����У��Ͳ���
INT8U Convert_BCD_2_HEX_Time(S_BCD_Time *pBCD_Time,S_HEX_Time *pHEX_Time)
{
  INT8U Re;

  Re=Check_BCD_Time(pBCD_Time);
  ASSERT(A_WARNING,1==Re);

  pHEX_Time->Time[T_MIN]=Bcd2Hex_Byte(pBCD_Time->Min);
  pHEX_Time->Time[T_HOUR]=Bcd2Hex_Byte(pBCD_Time->Hour);
  pHEX_Time->Time[T_DATE]=Bcd2Hex_Byte(pBCD_Time->Date);
  pHEX_Time->Time[T_MONTH]=Bcd2Hex_Byte(pBCD_Time->Month); 
  pHEX_Time->Time[T_YEAR]=Bcd2Hex_Byte(pBCD_Time->Year);
  pHEX_Time->Week=Bcd2Hex_Byte(pBCD_Time->Week);
  Set_STRUCT_Sum(pHEX_Time,sizeof(S_HEX_Time),pHEX_Time->CS,sizeof(pHEX_Time->CS));

  return Re;
}

//S_HEX_Timeת��ΪS_BCD_Time
//1��ʾת���ɹ���0��ʾʧ��,ʧ��������ԭ���ݸ�ʽ����У��Ͳ���
INT8U Convert_HEX_2_BCD_Time(S_HEX_Time *pHEX_Time,S_BCD_Time *pBCD_Time)
{
  INT8U Re;

  Re=Check_HEX_Time(pHEX_Time);
  ASSERT(A_WARNING,1==Re);

  pBCD_Time->Min=Hex2Bcd_Byte(pHEX_Time->Time[T_MIN]);
  pBCD_Time->Hour=Hex2Bcd_Byte(pHEX_Time->Time[T_HOUR]);
  pBCD_Time->Date=Hex2Bcd_Byte(pHEX_Time->Time[T_DATE]);
  pBCD_Time->Month=Hex2Bcd_Byte(pHEX_Time->Time[T_MONTH]); 
  pBCD_Time->Year=Hex2Bcd_Byte(pHEX_Time->Time[T_YEAR]);
  pBCD_Time->Week=Hex2Bcd_Byte(pHEX_Time->Week);
  Set_STRUCT_Sum(pBCD_Time,sizeof(S_BCD_Time),pBCD_Time->CS,sizeof(pBCD_Time->CS));

  return Re;
}
//��ʼ��ʱ����ز���
void Init_Clock_Ram_Para()
{
  mem_set((void *)&Clock_Info,0,sizeof(Clock_Info),(void *)&Clock_Info,sizeof(Clock_Info));
  SET_STRUCT_SUM(Clock_Info);
}


//���ʱ�����ݵ���Ч��
void Check_Clock_Data_Avail()
{
  INT8U Re;
   
  //Cur_Time0,Cur_Time1��Cur_Time_Bak֮�以��������౸��
  //������ݶ����ˣ��ܲ���ֻ�����¶�ȡ�ⲿʱ����
  Re=Check_HEX_Time((S_HEX_Time *)&Cur_Time0);
  if(ASSERT(A_WARNING,1==Re))
  {
    if(Check_BCD_Time((S_BCD_Time *)&Cur_Time1))
      Convert_BCD_2_HEX_Time((S_BCD_Time *)&Cur_Time1,(S_HEX_Time *)&Cur_Time0);
    else if(Check_BCD_Time((S_BCD_Time *)&Cur_Time_Bak))
      Convert_BCD_2_HEX_Time((S_BCD_Time *)&Cur_Time_Bak,(S_HEX_Time *)&Cur_Time0);
    else 
      Clock_Update();
  }
  
  Re=Check_BCD_Time((S_BCD_Time *)&Cur_Time1);
  if(ASSERT(A_WARNING,1==Re))
  {
    if(Check_HEX_Time((S_HEX_Time *)&Cur_Time0))
      Convert_HEX_2_BCD_Time((S_HEX_Time *)&Cur_Time0,(S_BCD_Time *)&Cur_Time1);
    else if(Check_BCD_Time((S_BCD_Time *)&Cur_Time_Bak))
      mem_cpy((void *)&Cur_Time1,(void *)&Cur_Time_Bak,sizeof(Cur_Time_Bak),(void *)&Cur_Time1,sizeof(Cur_Time1));
    else 
      Clock_Update();
  }
  
  Re=Check_BCD_Time((S_BCD_Time *)&Cur_Time_Bak);
  if(ASSERT(A_WARNING,1==Re))
  {
    if(Check_HEX_Time((S_HEX_Time *)&Cur_Time0))
      Convert_HEX_2_BCD_Time((S_HEX_Time *)&Cur_Time0,(S_BCD_Time *)&Cur_Time_Bak);
    else if(Check_BCD_Time((S_BCD_Time *)&Cur_Time1))
      mem_cpy((void *)&Cur_Time_Bak,(void *)&Cur_Time1,sizeof(Cur_Time1),(void *)&Cur_Time_Bak,sizeof(Cur_Time_Bak));
    else 
      Clock_Update();
  }
}
//����ʱ�������ʱ��
void Save_PD_Time()
{
  if(Check_BCD_Time((S_BCD_Time *)&Cur_Time1))
  {
    Write_Storage_Data(TIME_PD,(void *)&Cur_Time1,sizeof(Cur_Time1));   
    
  }
}

void Save_Bak_PD_Time()
{
  if(Check_BCD_Time((S_BCD_Time *)&Cur_Time1))
  {
    Write_Storage_Data(TIME_BAK_PD,(void *)&Cur_Time1,sizeof(Cur_Time1));   
    
  }  
}

//�ȴ�ʼ��׼����,��Ҫʱ�ӵ�������Ҫ�����������ǰ���øú���
void Wait_Clock_Ready()
{
  OS_Waitfor(1==Clock_Info.Clock_Ready_Flag);
}

//��ʼ��ʱ��
void Init_Clock(INT32U Mode)
{
  //INT16U Len;
  //S_BCD_Time Temp_Time;
  //INT8U Temp[7];
  //INT8U Re,Err;
  
  Clock_Info.Set_INTER_RTC_Flag=0;
  SET_STRUCT_SUM(Clock_Info);
   
  DEBUG_PRINT(HUCK,DEBUG_0,"Init Clock!!");
  if(Resume_Clock_Update()==0)//�ⲿʱ�ӳ��������£��γ�һ���¼���¼
  {
    Set_Err_Time((S_BCD_Time *)&Def_BCD_Time);//Ĭ��ʱ����Ϊ����ǰʱ�䣬��Ϊ�����ⲿʱ�Ӷ�����������֪������ǰʱ��
    Event_MultiTimes_Proc(ID_EVENT_RTCERR_PWRON,EVENT_OCCUR,EVENT_REAL);
  }
/*  
  if(SYS_SLEEP==Mode)//��ǰΪ˯��̬,��������̬���縴λ������Ϊ��ʡ�磬���ڴ���ȡʱ���������õ��ڲ�RTC
  {
     if(Get_Time_From_Ram_Rom(&Temp_Time)==0)//���������ڲ�ʱ�ӣ���Ϊ��λ���ڲ�ʱ����0
       Get_Time_From_EXT_RTC(&Temp_Time);

     Set_Time_To_INTER_RTC((S_BCD_Time *)&Temp_Time);
     Clock_Info.Set_INTER_RTC_Flag=1;
     SET_STRUCT_SUM(Clock_Info);
  }
  else  //������˯��ģʽ����Ҫ��ȡ�ⲿRTC,�������߻���ģʽ
  {
    Re=Get_Time_From_EXT_RTC((S_BCD_Time *)&Temp_Time);
    if(Read_Ext_RTC_Status()!=EXT_RTC_OK)
    {
      DEBUG_PRINT(HUCK,DEBUG_0,"Read_Ext_RTC_Status Error!");
      ASSERT(A_WARNING,0);
      Re=0;
    }
    
    if(0==Re)//û�д��ⲿRTCȡ����ȷ����
    {
      DEBUG_PRINT(HUCK,DEBUG_0,"RTC Err,Reset EXT RTC!!!!!!!!!!!!");
      
      Set_Err_Time(&Temp_Time);
      Set_Event_Instant(ID_EVENT_RTCERR_RUN);//ʱ�����¼���¼
      
      //���ڴ���ȡһ����ȷ��ʱ��������䵽Cur_Time1
      if(Get_Soft_RTC_PUCK(Temp,sizeof(Temp)))//�ϵ�ǰ�����ǵ͹���״̬,��Ҫ���͹���ʱ���������赽�ڲ�RTC��
      {
        Set_BCD_Time(Temp,(S_BCD_Time *)&Temp_Time);
        if(Check_BCD_Time(&Temp_Time))
          mem_cpy((void *)&Cur_Time1,&Temp_Time,sizeof(Temp_Time),(void *)&Cur_Time1,sizeof(Cur_Time1));
        else
          Get_Time_From_Ram_Rom((S_BCD_Time *)&Cur_Time1);
      }
      else
      {
        Len=Read_Storage_Data(TIME_PD,&Temp_Time,&Temp_Time,sizeof(Temp_Time),&Err); 
        if(Len>0 && Check_BCD_Time(&Temp_Time))
        {
          mem_cpy((void *)&(Cur_Time1),&Temp_Time,sizeof(Temp_Time),(void *)&Cur_Time1,sizeof(Cur_Time1));
          DEBUG_PRINT(HUCK,DEBUG_0,"No correct time,use TIME_PD Data!");
        }
        else
        {
          Len=Read_Storage_Data(TIME_BAK_PD,&Temp_Time,&Temp_Time,sizeof(Temp_Time),&Err); 
          if(Len>0 && Check_BCD_Time(&Temp_Time))
          {
            mem_cpy((void *)&(Cur_Time1),&Temp_Time,sizeof(Temp_Time),(void *)&Cur_Time1,sizeof(Cur_Time1));
            DEBUG_PRINT(HUCK,DEBUG_0,"No correct time,use TIME_BAK_PD Data!");
          } 
        }
      }
      
      if(Check_BCD_Time((S_BCD_Time *)&Cur_Time1)==0)//���ڴ���ȡһ��ʱ�����ݣ����õ��ⲿRTC
      {
        DEBUG_PRINT(HUCK,DEBUG_0,"Reset EXT RTC 01-01-01 00:00!!!!!!!!!!!!");
        mem_cpy((void *)&Cur_Time1,(void *)&Def_BCD_Time,sizeof(Def_BCD_Time),(void *)&Cur_Time1,sizeof(Cur_Time1));
        SET_STRUCT_SUM(Cur_Time1);
      }
      //��ʱCur_Time1��һ����ȷ���ݣ������������õ��ⲿRTC
      Set_Time_To_EXT_RTC((S_BCD_Time *)&Cur_Time1);
    }
    else
      mem_cpy((void *)&Cur_Time1,(void *)&Temp_Time,sizeof(Temp_Time),(void *)&Cur_Time1,sizeof(Cur_Time1));
   
    Convert_BCD_2_HEX_Time((S_BCD_Time *)&Cur_Time1,(S_HEX_Time *)&Cur_Time0);
    
    Set_Time_To_INTER_RTC((S_BCD_Time *)&Cur_Time1);
    mem_cpy((void *)&Cur_Time_Bak,(void *)&Cur_Time1,sizeof(Cur_Time1),(void *)&Cur_Time_Bak,sizeof(Cur_Time_Bak));
    Clock_Info.Set_INTER_RTC_Flag=1;
    SET_STRUCT_SUM(Clock_Info);       
  }
  */
}
#undef CLOCK_C
