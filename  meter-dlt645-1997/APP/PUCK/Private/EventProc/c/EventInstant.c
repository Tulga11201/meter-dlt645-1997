#define EVENTINSTANT_C
#include "Pub_PUCK.h"
/*
typedef struct
{
  INT32U Qual_Up_Vol[3];//Խ�ϸ����޵�ѹֵ,0-2�ֱ��ʾA-B-C��
  INT32U Qual_Low_Vol[3];//Խ�ϸ����޵�ѹֵ
  
  INT32U Over_Vol[3];//��ѹ�����޵�ѹֵ
}S_Event_Vol_Cur;
����ӱ 17:25:37
EXT S_Event_Vol_Cur Event_Vol_Cur;
����ӱ 17:26:00
Over_Vol[3] �����
*/

/***********************************************************************
�������ܣ���ʼ����ȡ˲̬�ֵ�ȫ������
��ڣ���
���ڣ���
***********************************************************************/
void Init_Event_Instant_Para(void)
{
  INT8U Flag,temp[4];
  Flag=Read_Storage_Data_PUCK(DI_LOSS_VOLT,temp,4); 
  if(Flag)
  {
    EventInsParaVar.LossVolt_I=Bcd2Hex(temp+1,3)/(FP32S)10000;   //����������1000��4λС��
    EventInsParaVar.LossVolt_Per=Bcd2Hex(temp,1)/(FP32S)100;   //��������������78
  }
  
  Flag&=Read_Storage_Data_PUCK(DI_LOSS_CURR,temp,4);
  if(Flag)
  {
    EventInsParaVar.LossCurr_I=Bcd2Hex(temp+1,3)/(FP32S)10000;
    EventInsParaVar.LossCurr_Per=Bcd2Hex(temp,1)/(FP32S)100;
    
   /* if(EventInsParaVar.LossCurr_I<=ALL_LOSS_CURR_VALUE)    //ȫʧ����ֵ�����ʧ��������ֵС
      EventInsParaVar.LossCurr_I=ALL_LOSS_CURR_VALUE*5;
    */
  }  
  if(!Flag)
  {
      DEBUG_PRINT(PUCK,PRINT_PUCK_EVENT_EN,"Get Instant Para Error!");  
  }

#ifdef LOSS_VOLT_ONLY           //ʧѹֻ�ж���ѹ 
    EventInsParaVar.LossVolt_I=0;      //ʧѹ���жϵ���
    EventInsParaVar.LossVolt_Per=0.5;   //ʧѹ��ѹ��ֵ50%Un
#endif

#ifdef LOSS_CURR_ONLY           //ʧ��ֻ�ж�����
    EventInsParaVar.LossCurr_I=0.3;       //ʧ���������в�ƽ����
    EventInsParaVar.LossCurr_Per=0.1;     //ʧ��������Ч��ֻ�ж� 0.001In��Ϊ��ֵ
#endif
  SET_STRUCT_SUM(EventInsParaVar);
}


/***********************************************************************
�������ܣ��Ա�λ�¼����ж�����ʧѹ��ʧ�������ʷ���
��ڣ���
���ڣ���
***********************************************************************/
void Get_Change_Status(INT8U CurrStat,INT8U StartBit,INT8U EventId,volatile EVENT_CHANGE *Result)
{
 
  if(GET_BIT(CurrStat,StartBit))        					//A��
    SET_BIT(Result->NewStatus,StartBit);
  else
    CLR_BIT(Result->NewStatus,StartBit);
  
  if(GET_BIT(CurrStat,StartBit+1))        					//B��
    SET_BIT(Result->NewStatus,StartBit+1);
  else
    CLR_BIT(Result->NewStatus,StartBit+1);
    
  if(GET_BIT(CurrStat,StartBit+2))        					//C��
    SET_BIT(Result->NewStatus,StartBit+2);
  else
    CLR_BIT(Result->NewStatus,StartBit+2);
  
  
  if(Result->OldStatus==Result->NewStatus)  //�ޱ�λ����������
  {
    Result->Counts=0;
    return ;
  }
  
  //������λ
  if(0==Result->OldStatus)   //����
  {
    Set_Event_Instant(EventId);
    Result->Counts++;
    if(MAX_CHANGE_SEC)  //ȷ���Ѿ��洢���ж����
    {
      Result->OldStatus=Result->NewStatus;
      Result->Counts=0;
    }    
  }
  else if(0!=Result->OldStatus && 0==Result->NewStatus)  //����
  {    
    Clr_Event_Instant(EventId);
    Result->Counts++;
    if(MAX_CHANGE_SEC)   //ȷ���Ѿ��洢���ж����
    {
      Result->OldStatus=Result->NewStatus;
      Result->Counts=0;
    }
  }
  else if(0!=Result->OldStatus && 0!=Result->NewStatus)  //����Ϊ0��������ȣ��¼����� ����/���� ����
  {
    Clr_Event_Instant(EventId);
    Result->Counts++;
    if(MAX_CHANGE_SEC)   //ȷ���Ѿ��洢���ж����
    {
      Result->OldStatus=0;         //���ν�����������0�������账��������Ϊ�´��¼��Ŀ�ʼ
      Result->Counts=0;
    }     
  }  
}
/********************************************************************************
����ԭ�ͣ�void Event_Para_Modi(void)
���ܣ������в�������ά��������������ͨ�����¼��ȡ�

*********************************************************************************/
void Event_Para_Modi(void)
{
  INT16U temp;
  
  while(Get_Para_Modify(&temp))
  {
    DEBUG_PRINT(PUCK,PRINT_PUCK_CHANNEL_EN,"Para Modified In Event Task:%x",temp);
    switch(temp)
    {
      case DI_LOSS_VOLT:      
      case DI_LOSS_CURR:
          Init_Event_Instant_Para();
       break;  
    }    
  }   
}
/***********************************************************************
�������ܣ������¼�����ǰ����
��ڣ���
���ڣ�0-----------�����¼���Ҫ��һ���������¼���1-------------�����¼�����Ϊ����
�����ѹ������70%Un��
����
***********************************************************************/
INT8U Check_Power_Grid_Event(void)
{
  FP32S temp;
  INT8U Flag1,Flag2;
  
  if(Get_Sys_Status()!=SYS_NORMAL)
    return 1;
  
  Flag1=Flag2=0;
  temp=Get_Max_Num(Measu_InstantData_ToPub_PUCK.Volt.A,Measu_InstantData_ToPub_PUCK.Volt.B,Measu_InstantData_ToPub_PUCK.Volt.C);
  temp/=UNIT_V;
  if(temp<Get_Un()*(FP32S)0.7)        //���е�ѹ������0.7Un, ���е�ѹ������AUXIL_POWER_RATIO*Unʱ������Ϊ�Ǹ�����Դ
    Flag1=1;
  
  temp=Measu_InstantData_ToPub_PUCK.Volt.A+Measu_InstantData_ToPub_PUCK.Volt.B+Measu_InstantData_ToPub_PUCK.Volt.C;
  temp/=UNIT_V;
  if((temp-10)<Get_Un()*(FP32S)0.7)   //(���е�ѹ֮��-10)<0.7Un   
    Flag2=1;
  
  if(Flag1&&Flag2)      //�����¼�����
    return 1;
  
  return 0;
}

/***********************************************************************
�������ܣ�331��B��ʧѹ����
��ڣ���
���ڣ�
***********************************************************************/
INT8U B_331_LossVolt(void)
{
  INT8U Result=0;
  FP32S temp;
  
  if((FP32S)Measu_InstantData_ToPub_PUCK.Volt.A/UNIT_V<=10 || \
     (FP32S)Measu_InstantData_ToPub_PUCK.Volt.B/UNIT_V<=10)
    Result=0;
       
  if((FP32S)Measu_InstantData_ToPub_PUCK.Volt.A/UNIT_V!=0 && \
     (FP32S)Measu_InstantData_ToPub_PUCK.Volt.B/UNIT_V!=0 &&(FP32S)Measu_InstantData_ToPub_PUCK.Volt.C/UNIT_V!=0)
  {
    Result=0;  
    //(Ua��Uc)/Ub
    temp=((FP32S)Measu_InstantData_ToPub_PUCK.Volt.A/UNIT_V+(FP32S)Measu_InstantData_ToPub_PUCK.Volt.C/UNIT_V)/(FP32S)Measu_InstantData_ToPub_PUCK.Volt.B/UNIT_V;
    if(temp>=0.9 && temp<=1.1)
    {
      temp=(FP32S)Measu_InstantData_ToPub_PUCK.Volt.A/(FP32S)Measu_InstantData_ToPub_PUCK.Volt.B; //Ua/Ub
      if(temp>0.1)
      {
        temp=(FP32S)Measu_InstantData_ToPub_PUCK.Volt.C/(FP32S)Measu_InstantData_ToPub_PUCK.Volt.B; //Uc/Ub
        if(temp>0.1)
          Result=1;        
      }      
    }
  }
  
  if( (Result||(FP32S)Measu_InstantData_ToPub_PUCK.Angle.B/UNIT_DEGREE>=74) && \
      ((FP32S)Measu_InstantData_ToPub_PUCK.Curr.A/UNIT_A >EventInsParaVar.LossVolt_I ||
       (FP32S)Measu_InstantData_ToPub_PUCK.Curr.C/UNIT_A >EventInsParaVar.LossVolt_I) )
    return 1;
  
  return 0;
  
  
}
/***********************************************************************
�������ܣ���ȡʧѹ˲ʱ״̬��
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_EVENT_A_LOSS_VOLT
void Check_Loss_Volt(void)
{
  INT8U Flag;
  FP32S temp;
  
  if(Check_Power_Grid_Event())
  {
    Clr_Event_Instant(ID_EVENT_A_LOSS_VOLT);  //A��ѹʧѹ���
    Clr_Event_Instant(ID_EVENT_B_LOSS_VOLT);  //B��ѹʧѹ���
    Clr_Event_Instant(ID_EVENT_C_LOSS_VOLT);  //C��ѹʧѹ���
    Clr_Event_Instant(ID_EVENT_AB_LOSS_VOLT);  //AB��ѹʧѹ���
    Clr_Event_Instant(ID_EVENT_BC_LOSS_VOLT);  //BC��ѹʧѹ���
    Clr_Event_Instant(ID_EVENT_AC_LOSS_VOLT);  //AC��ѹʧѹ���
    Clr_Event_Instant(ID_EVENT_ABC_LOSS_VOLT);  //ABC��ѹʧѹ���
    
   return ;
  }
    
  temp=Get_Un();
  if((((FP32S)Measu_InstantData_ToPub_PUCK.Volt.A/UNIT_V)<=(temp*EventInsParaVar.LossVolt_Per))&&(((FP32S)Measu_InstantData_ToPub_PUCK.Curr.A/UNIT_A)>=EventInsParaVar.LossVolt_I))
  {
    Set_Event_Instant(ID_EVENT_A_LOSS_VOLT);  //A��ʧѹ
  }
  else
  {
    Clr_Event_Instant(ID_EVENT_A_LOSS_VOLT);  //A��û��ʧѹ
  }
  
  if((((FP32S)Measu_InstantData_ToPub_PUCK.Volt.B/UNIT_V)<=(temp*EventInsParaVar.LossVolt_Per))&&(((FP32S)Measu_InstantData_ToPub_PUCK.Curr.B/UNIT_A)>=EventInsParaVar.LossVolt_I))
  {
    Set_Event_Instant(ID_EVENT_B_LOSS_VOLT);  //B��ʧѹ
  }
  else
  {
    Clr_Event_Instant(ID_EVENT_B_LOSS_VOLT);  //B��û��ʧѹ
  }
  
  if((((FP32S)Measu_InstantData_ToPub_PUCK.Volt.C/UNIT_V)<=(temp*EventInsParaVar.LossVolt_Per))&&(((FP32S)Measu_InstantData_ToPub_PUCK.Curr.C/UNIT_A)>=EventInsParaVar.LossVolt_I))
  {
    Set_Event_Instant(ID_EVENT_C_LOSS_VOLT);  //C��ʧѹ
  }
  else
  {
     Clr_Event_Instant(ID_EVENT_C_LOSS_VOLT);  //C��û��ʧѹ
  }

  Flag=Get_SysParse_Mode();
  if(Flag==PARSE_331)  
  {
    if(B_331_LossVolt())
    {
      Set_Event_Instant(ID_EVENT_B_LOSS_VOLT);  //B��ʧѹ
      Clr_Event_Instant(ID_EVENT_A_LOSS_VOLT);  //A�಻�ж�ʧѹ
      Clr_Event_Instant(ID_EVENT_C_LOSS_VOLT);  //C�಻�ж�ʧѹ        
    }
    else
    {
      Clr_Event_Instant(ID_EVENT_B_LOSS_VOLT);  //B��û��ʧѹ      
    }
#ifdef MULTI_LOSS_VOLT_EN   //�ж�����ʧѹ
    if(Get_Event_Instant(ID_EVENT_A_LOSS_VOLT)&&(Get_Event_Instant(ID_EVENT_C_LOSS_VOLT)))   //A��Cʧѹ
    {
      Set_Event_Instant(ID_EVENT_AC_LOSS_VOLT);  //AC��ʧѹ
      Clr_Event_Instant(ID_EVENT_A_LOSS_VOLT);  //A��û��ʧѹ
      Clr_Event_Instant(ID_EVENT_C_LOSS_VOLT);  //C��û��ʧѹ
    }
    else
    {
      Clr_Event_Instant(ID_EVENT_AC_LOSS_VOLT);  //AC��ʧѹ
    }
    //331���� AB/BC/ABCʧѹ
    Clr_Event_Instant(ID_EVENT_AB_LOSS_VOLT);  //AB�಻��ʧѹ
    Clr_Event_Instant(ID_EVENT_BC_LOSS_VOLT);  //BC�಻��ʧѹ
    Clr_Event_Instant(ID_EVENT_ABC_LOSS_VOLT);  //ABC��ʧѹ 
#endif
  }

  else                          //341                               
  {
#ifdef MULTI_LOSS_VOLT_EN    //�ж�����ʧѹ
    if(Get_Event_Instant(ID_EVENT_A_LOSS_VOLT)&&(Get_Event_Instant(ID_EVENT_B_LOSS_VOLT)))
      Set_Event_Instant(ID_EVENT_AB_LOSS_VOLT);  //AB��ʧѹ
    else
      Clr_Event_Instant(ID_EVENT_AB_LOSS_VOLT);  //AB��ûʧѹ
    
    if(Get_Event_Instant(ID_EVENT_A_LOSS_VOLT)&&(Get_Event_Instant(ID_EVENT_C_LOSS_VOLT)))
      Set_Event_Instant(ID_EVENT_AC_LOSS_VOLT);  //AC��ʧѹ
    else
      Clr_Event_Instant(ID_EVENT_AC_LOSS_VOLT);  //AC��ûʧѹ
    
    if(Get_Event_Instant(ID_EVENT_B_LOSS_VOLT)&&(Get_Event_Instant(ID_EVENT_C_LOSS_VOLT)))
      Set_Event_Instant(ID_EVENT_BC_LOSS_VOLT);  //BC��ʧѹ
    else
      Clr_Event_Instant(ID_EVENT_BC_LOSS_VOLT);  //BC��ûʧѹ      
    
    if(Get_Event_Instant(ID_EVENT_AB_LOSS_VOLT)&&(Get_Event_Instant(ID_EVENT_AC_LOSS_VOLT)))
      Set_Event_Instant(ID_EVENT_ABC_LOSS_VOLT);  //ABC��ʧѹ
    else
      Clr_Event_Instant(ID_EVENT_ABC_LOSS_VOLT);  //ABC��ûʧѹ
    
    if(Get_Event_Instant(ID_EVENT_AB_LOSS_VOLT))
    {
      Clr_Event_Instant(ID_EVENT_A_LOSS_VOLT);  //A��û��ʧѹ
      Clr_Event_Instant(ID_EVENT_B_LOSS_VOLT);  //B��û��ʧѹ
    }
    if(Get_Event_Instant(ID_EVENT_AC_LOSS_VOLT))
    {
      Clr_Event_Instant(ID_EVENT_A_LOSS_VOLT);  //A��û��ʧѹ
      Clr_Event_Instant(ID_EVENT_C_LOSS_VOLT);  //C��û��ʧѹ
    }
    if(Get_Event_Instant(ID_EVENT_BC_LOSS_VOLT))
    {
      Clr_Event_Instant(ID_EVENT_B_LOSS_VOLT);  //B��û��ʧѹ
      Clr_Event_Instant(ID_EVENT_C_LOSS_VOLT);  //C��û��ʧѹ
    }
    if(Get_Event_Instant(ID_EVENT_ABC_LOSS_VOLT))
    {
      Clr_Event_Instant(ID_EVENT_A_LOSS_VOLT);  //A��û��ʧѹ
      Clr_Event_Instant(ID_EVENT_B_LOSS_VOLT);  //B��û��ʧѹ
      Clr_Event_Instant(ID_EVENT_C_LOSS_VOLT);  //C��û��ʧѹ
      Clr_Event_Instant(ID_EVENT_AB_LOSS_VOLT);  //AB��ʧѹ
      Clr_Event_Instant(ID_EVENT_BC_LOSS_VOLT);  //BC��ʧѹ
      Clr_Event_Instant(ID_EVENT_AC_LOSS_VOLT);  //AC��ʧѹ
    }
#else            //ֻ�ж�����ʧѹ
    Clr_Event_Instant(ID_EVENT_AB_LOSS_VOLT);  //AB��ѹʧѹ���
    Clr_Event_Instant(ID_EVENT_BC_LOSS_VOLT);  //BC��ѹʧѹ���
    Clr_Event_Instant(ID_EVENT_AC_LOSS_VOLT);  //AC��ѹʧѹ���
    Clr_Event_Instant(ID_EVENT_ABC_LOSS_VOLT);  //ABC��ѹʧѹ���
#endif    
  }

}
#endif

/***********************************************************************
�������ܣ���ȡʧ��˲ʱ״̬��
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_EVENT_A_LOSS_CURR
void Check_Loss_Curr(void)
{

  INT8U Flag;
  FP32S max;
  
  if(Check_Power_Grid_Event())
  {
    Clr_Event_Instant(ID_EVENT_A_LOSS_CURR);  //A��û��ʧ��
    Clr_Event_Instant(ID_EVENT_B_LOSS_CURR);  //B��û��ʧ��
    Clr_Event_Instant(ID_EVENT_C_LOSS_CURR);  //C��û��ʧ��
    Clr_Event_Instant(ID_EVENT_AB_LOSS_CURR);  //AB��û��ʧ��
    Clr_Event_Instant(ID_EVENT_AC_LOSS_CURR);  //AC��û��ʧ��
    Clr_Event_Instant(ID_EVENT_BC_LOSS_CURR);  //BC��û��ʧ��
    Clr_Event_Instant(ID_EVENT_ALL_LOSS_CURR);  //ABC��û��ʧ��    
 
    return ;
  }
  
  max=Get_Max_Num(Measu_InstantData_ToPub_PUCK.Curr.A,Measu_InstantData_ToPub_PUCK.Curr.B,Measu_InstantData_ToPub_PUCK.Curr.C);
  max/=UNIT_A;
  
  //if(max<=(Get_In()*ALL_LOSS_CURR_VALUE))  //�������ͬʱС��2%In,ȫʧ��
  if(max<=Get_Start_Current())  //�������ͬʱС��0.001*In,ȫʧ��
  {
#ifdef MULTI_LOSS_CURR_EN    //�ж�����ʧ��
    Set_Event_Instant(ID_EVENT_ALL_LOSS_CURR);  //ABC��ʧ��
    Clr_Event_Instant(ID_EVENT_A_LOSS_CURR);  //A��û��ʧ��
    Clr_Event_Instant(ID_EVENT_B_LOSS_CURR);  //B��û��ʧ��
    Clr_Event_Instant(ID_EVENT_C_LOSS_CURR);  //C��û��ʧ��
#else
    Clr_Event_Instant(ID_EVENT_ALL_LOSS_CURR);  //ABC��ûʧ��
    Set_Event_Instant(ID_EVENT_A_LOSS_CURR);  //A��ʧ��
    Set_Event_Instant(ID_EVENT_B_LOSS_CURR);  //B��ʧ��
    Set_Event_Instant(ID_EVENT_C_LOSS_CURR);  //C��ʧ��    
#endif
    Clr_Event_Instant(ID_EVENT_AB_LOSS_CURR);  //AB��û��ʧ��
    Clr_Event_Instant(ID_EVENT_AC_LOSS_CURR);  //AC��û��ʧ��
    Clr_Event_Instant(ID_EVENT_BC_LOSS_CURR);  //BC��û��ʧ��
      
    if(Get_SysParse_Mode()==PARSE_331)           //331�������ʧ��, B�಻�ж�ʧ��,ͬһʱ�̣�A��C����ͬʱʧ��
      Clr_Event_Instant(ID_EVENT_B_LOSS_CURR);
    return;  
  } 
  else      //�ж�����ʧ��
  {
#ifdef LOSS_CURR_ONLY           //ʧ��ֻ�ж������������ƽ�����޹�
    if(((FP32S)Measu_InstantData_ToPub_PUCK.Curr.A/UNIT_A)<=Get_Start_Current())
       Set_Event_Instant(ID_EVENT_A_LOSS_CURR);  //A��ʧ��
    else
       Clr_Event_Instant(ID_EVENT_A_LOSS_CURR);  //A��û��ʧ��
    
    if(((FP32S)Measu_InstantData_ToPub_PUCK.Curr.B/UNIT_A)<=Get_Start_Current())
       Set_Event_Instant(ID_EVENT_B_LOSS_CURR);  //B��ʧ��
    else
       Clr_Event_Instant(ID_EVENT_B_LOSS_CURR);  //B��û��ʧ��
    
    if(((FP32S)Measu_InstantData_ToPub_PUCK.Curr.C/UNIT_A)<=Get_Start_Current())
       Set_Event_Instant(ID_EVENT_C_LOSS_CURR);  //C��ʧ��
    else
       Clr_Event_Instant(ID_EVENT_C_LOSS_CURR);  //C��û��ʧ��
    
    if(Get_SysParse_Mode()==PARSE_331)           //331�������ʧ��, B�಻�ж�ʧ��,ͬһʱ�̣�A��C����ͬʱʧ��
      Clr_Event_Instant(ID_EVENT_B_LOSS_CURR);
    
#else                             //ʧ�����ж�������ͬʱҲ�����ƽ�����й�
    FP32S temp;
    temp=(max-(FP32S)Measu_InstantData_ToPub_PUCK.Curr.A/UNIT_A)/max;  //������ƽ����
    if(temp<0)  temp*=-1;
    if((temp>=EventInsParaVar.LossCurr_Per)&&(max>=EventInsParaVar.LossCurr_I))
    {
      Set_Event_Instant(ID_EVENT_A_LOSS_CURR);  //A��ʧ��
    }
    else
    {
      Clr_Event_Instant(ID_EVENT_A_LOSS_CURR);  //A��û��ʧ��
    }
    
    temp=(max-(FP32S)Measu_InstantData_ToPub_PUCK.Curr.B/UNIT_A)/max;   //������ƽ����
    if(temp<0)  temp*=-1;
    if((temp>=EventInsParaVar.LossCurr_Per)&&(max>=EventInsParaVar.LossCurr_I))
    {
      Set_Event_Instant(ID_EVENT_B_LOSS_CURR);  //B��ʧ��
    }
    else
    {
      Clr_Event_Instant(ID_EVENT_B_LOSS_CURR);  //B��û��ʧ��
    }      
    
    temp=(max-(FP32S)Measu_InstantData_ToPub_PUCK.Curr.C/UNIT_A)/max;   //������ƽ����
    if(temp<0)  temp*=-1;
    if((temp>=EventInsParaVar.LossCurr_Per)&&(max>=EventInsParaVar.LossCurr_I))
    {
      Set_Event_Instant(ID_EVENT_C_LOSS_CURR);  //C��ʧ��
    }
    else
    {
      Clr_Event_Instant(ID_EVENT_C_LOSS_CURR);  //C��û��ʧ��
    }
#endif
  }
  
  Flag=Get_SysParse_Mode();
  if(Flag==PARSE_331)           //331�������ʧ��, B�಻�ж�ʧ��,ͬһʱ�̣�A��C����ͬʱʧ��
  {
    Clr_Event_Instant(ID_EVENT_B_LOSS_CURR);
  }
  else                          //341                             
  {
#ifdef MULTI_LOSS_CURR_EN    //�ж�����ʧ��
    if(Get_Event_Instant(ID_EVENT_A_LOSS_CURR)&&(Get_Event_Instant(ID_EVENT_B_LOSS_CURR)))
      Set_Event_Instant(ID_EVENT_AB_LOSS_CURR);  //AB��ʧ��     
    else
      Clr_Event_Instant(ID_EVENT_AB_LOSS_CURR);  //AB��ʧ��
    
    if(Get_Event_Instant(ID_EVENT_A_LOSS_CURR)&&(Get_Event_Instant(ID_EVENT_C_LOSS_CURR)))
      Set_Event_Instant(ID_EVENT_AC_LOSS_CURR);  //AC��ʧ��
    else
      Clr_Event_Instant(ID_EVENT_AC_LOSS_CURR);  //AC��ʧ��
    
    if(Get_Event_Instant(ID_EVENT_B_LOSS_CURR)&&(Get_Event_Instant(ID_EVENT_C_LOSS_CURR)))
      Set_Event_Instant(ID_EVENT_BC_LOSS_CURR);  //BC��ʧ��      
    else
      Clr_Event_Instant(ID_EVENT_BC_LOSS_CURR);  //BC��ʧ��
    
    if(Get_Event_Instant(ID_EVENT_AB_LOSS_CURR)&&(Get_Event_Instant(ID_EVENT_BC_LOSS_CURR)))
      Set_Event_Instant(ID_EVENT_ALL_LOSS_CURR);   //ABC��ʧ�� 
    else
      Clr_Event_Instant(ID_EVENT_ALL_LOSS_CURR);   //ABC��ʧ��
     
    if(Get_Event_Instant(ID_EVENT_AB_LOSS_CURR))
    {
      Clr_Event_Instant(ID_EVENT_A_LOSS_CURR);  //A��û��ʧ��
      Clr_Event_Instant(ID_EVENT_B_LOSS_CURR);  //B��û��ʧ��
    }
    if(Get_Event_Instant(ID_EVENT_AC_LOSS_CURR))
    {
      Clr_Event_Instant(ID_EVENT_A_LOSS_CURR);  //A��û��ʧ��
      Clr_Event_Instant(ID_EVENT_C_LOSS_CURR);  //C��û��ʧ��
    }
    if(Get_Event_Instant(ID_EVENT_BC_LOSS_CURR))
    {
      Clr_Event_Instant(ID_EVENT_B_LOSS_CURR);  //B��û��ʧ��
      Clr_Event_Instant(ID_EVENT_C_LOSS_CURR);  //C��û��ʧ��
    }
    if(Get_Event_Instant(ID_EVENT_ALL_LOSS_CURR))
    {
      Clr_Event_Instant(ID_EVENT_A_LOSS_CURR);  //A��û��ʧ��
      Clr_Event_Instant(ID_EVENT_B_LOSS_CURR);  //B��û��ʧ��
      Clr_Event_Instant(ID_EVENT_C_LOSS_CURR);  //C��û��ʧ��
      Clr_Event_Instant(ID_EVENT_AB_LOSS_CURR);  //AB��ʧ��
      Clr_Event_Instant(ID_EVENT_BC_LOSS_CURR);  //BC��ʧ��
      Clr_Event_Instant(ID_EVENT_AC_LOSS_CURR);  //AC��ʧ��
    }   
#else
    Clr_Event_Instant(ID_EVENT_AB_LOSS_CURR);  //AB��ʧ��
    Clr_Event_Instant(ID_EVENT_BC_LOSS_CURR);  //BC��ʧ��
    Clr_Event_Instant(ID_EVENT_AC_LOSS_CURR);  //AC��ʧ��
    Clr_Event_Instant(ID_EVENT_ALL_LOSS_CURR);  //ABC��û��ʧ��    
#endif
  }

}
#endif

/***********************************************************************
�������ܣ���ȡ����˲ʱ״̬��
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_EVENT_A_LOSS_PARSE
void Check_Loss_Parse(void)
{
  INT8U Flag;
  FP32S temp;
  
  Flag=Check_Power_Grid_Event();
  if(Flag)
  {
    Clr_Event_Instant(ID_EVENT_A_LOSS_PARSE);  //A��û�ж���
    Clr_Event_Instant(ID_EVENT_B_LOSS_PARSE);  //B��û�ж���
    Clr_Event_Instant(ID_EVENT_C_LOSS_PARSE);  //C��û�ж���
    return ;
  }
    
  temp=Get_Un();
  if((((FP32S)Measu_InstantData_ToPub_PUCK.Volt.A/UNIT_V)<=(temp*EventInsParaVar.LossVolt_Per))&&(((FP32S)Measu_InstantData_ToPub_PUCK.Curr.A/UNIT_A)<=EventInsParaVar.LossVolt_I))
    Set_Event_Instant(ID_EVENT_A_LOSS_PARSE);  //A�����
  else
     Clr_Event_Instant(ID_EVENT_A_LOSS_PARSE);  //A��û�ж���
  
  if((((FP32S)Measu_InstantData_ToPub_PUCK.Volt.B/UNIT_V)<=(temp*EventInsParaVar.LossVolt_Per))&&(((FP32S)Measu_InstantData_ToPub_PUCK.Curr.B/UNIT_A)<=EventInsParaVar.LossVolt_I))
    Set_Event_Instant(ID_EVENT_B_LOSS_PARSE);  //B�����
  else
     Clr_Event_Instant(ID_EVENT_B_LOSS_PARSE);  //B��û�ж���
  
  if((((FP32S)Measu_InstantData_ToPub_PUCK.Volt.C/UNIT_V)<=(temp*EventInsParaVar.LossVolt_Per))&&(((FP32S)Measu_InstantData_ToPub_PUCK.Curr.C/UNIT_A)<=EventInsParaVar.LossVolt_I))
    Set_Event_Instant(ID_EVENT_C_LOSS_PARSE);  //C�����
  else
     Clr_Event_Instant(ID_EVENT_C_LOSS_PARSE);  //C��û�ж���
  
  Flag=Get_SysParse_Mode();
  if(Flag==PARSE_331)
  {
    if((((FP32S)Measu_InstantData_ToPub_PUCK.Curr.B/UNIT_A)<=EventInsParaVar.LossVolt_I)&&(((FP32S)Measu_InstantData_ToPub_PUCK.Curr.C/UNIT_A)<=EventInsParaVar.LossVolt_I))
      Set_Event_Instant(ID_EVENT_B_LOSS_PARSE);  //B�����
    else
      Clr_Event_Instant(ID_EVENT_B_LOSS_PARSE);  //B��û�ж���
  }
}
#endif
/***********************************************************************
�������ܣ���ȡ����(����)˲̬��
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_EVENT_A_NEG_CURR
void Check_Neg_Curr(void)
{
  FP32S temp;
  
  if(Check_Power_Grid_Event())
  {
    Clr_Event_Instant(ID_EVENT_A_NEG_CURR); //A��������
    Clr_Event_Instant(ID_EVENT_B_NEG_CURR);  //B��������
    Clr_Event_Instant(ID_EVENT_C_NEG_CURR);  //C��������
    return ;
  }
  temp=Get_In();
  
  //����>0.1%In,��ѹ����10v�����й����ʷ���
  if(((FP32S)Measu_InstantData_ToPub_PUCK.Curr.A/UNIT_A>temp/1000)&&\
     ((FP32S)Measu_InstantData_ToPub_PUCK.Volt.A/UNIT_V>10)&&\
     (Measu_Status_Mode_ToPub_PUCK.A_APwrDir))
    Set_Event_Instant(ID_EVENT_A_NEG_CURR); ///A��������
  else
    Clr_Event_Instant(ID_EVENT_A_NEG_CURR); //A������δ��
  

    //����>0.1%In,��ѹ����10v�����й����ʷ���
  if(((FP32S)Measu_InstantData_ToPub_PUCK.Curr.B/UNIT_A>temp/1000)&&\
     ((FP32S)Measu_InstantData_ToPub_PUCK.Volt.B/UNIT_V>10)&&\
     (Measu_Status_Mode_ToPub_PUCK.B_APwrDir))
    Set_Event_Instant(ID_EVENT_B_NEG_CURR); //B��������
  else
    Clr_Event_Instant(ID_EVENT_B_NEG_CURR); //B������δ��
  
    //����>0.1%In,��ѹ����10v�����й����ʷ���
  if(((FP32S)Measu_InstantData_ToPub_PUCK.Curr.C/UNIT_A>temp/1000)&&\
     ((FP32S)Measu_InstantData_ToPub_PUCK.Volt.C/UNIT_V>10)&&\
     (Measu_Status_Mode_ToPub_PUCK.C_APwrDir))
    Set_Event_Instant(ID_EVENT_C_NEG_CURR); //C��������
  else
    Clr_Event_Instant(ID_EVENT_C_NEG_CURR); //C������δ��
}
#endif



/***********************************************************************
�������ܣ���ȡʧѹ�仯״̬��
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_EVENT_LOSS_VOL
void Get_Loss_Volt_Change(void)
{
 Get_Change_Status(Meter_Run_Status.Volt_LossMiss.Byte,4,ID_EVENT_LOSS_VOL,&Loss_Volt_Change); 
}
#endif

/***********************************************************************
�������ܣ���ȡʧ���仯״̬��
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_EVENT_LOSS_CUR
void Get_Loss_Curr_Change(void)
{
  Get_Change_Status(Meter_Run_Status.Meter_Stat3.Byte,4,ID_EVENT_LOSS_CUR,&Loss_Curr_Change); 
}
#endif
/***********************************************************************
�������ܣ���ȡ��������仯״̬��
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_EVENT_NEG_CUR
void Get_Curr_Neg_Change(void)
{ 
  Get_Change_Status(Meter_Run_Status.Meter_Stat2.Byte,0,ID_EVENT_NEG_CUR,&Curr_Neg_Change);  
}
#endif

/***********************************************************************
�������ܣ���ȡ��ѹ����������˲̬��
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_EVENT_VOLT_NEG_SEQ
void Check_Volt_Curr_Seq(void)
{

  if(Check_Power_Grid_Event())
  {
    Clr_Event_Instant(ID_EVENT_VOLT_NEG_SEQ); //��ѹ������ȷ���¼�����
    Clr_Event_Instant(ID_EVENT_CUR_NEG_SEQ);  //����������ȷ���¼�����
    return ;
  }
  
  if(Measu_Status_Mode_ToPub_PUCK.V_SeqErr)
    Set_Event_Instant(ID_EVENT_VOLT_NEG_SEQ); //��ѹ�����
  else
    Clr_Event_Instant(ID_EVENT_VOLT_NEG_SEQ); //��ѹ������ȷ
 
    
  //���࣬����������
  if((FP32S)Get_Min_Num(Measu_InstantData_ToPub_PUCK.Volt.A,Measu_InstantData_ToPub_PUCK.Volt.B,Measu_InstantData_ToPub_PUCK.Volt.C)<UNIT_V*60.0)
     Clr_Event_Instant(ID_EVENT_VOLT_NEG_SEQ); //��ѹ�������
  
  //331��ABCʧѹʱ������������
  if(Get_SysParse_Mode()==PARSE_331)  //331����������
  {
     if(((FP32S)Measu_InstantData_ToPub_PUCK.Volt.A/UNIT_V)<=65  || \
                         Get_Event_Instant(ID_EVENT_B_LOSS_VOLT) || \
        ((FP32S)Measu_InstantData_ToPub_PUCK.Volt.C/UNIT_V)<=65)
      Clr_Event_Instant(ID_EVENT_VOLT_NEG_SEQ); //��ѹ�������
  }
  
  if(Measu_Status_Mode_ToPub_PUCK.I_SeqErr)
    Set_Event_Instant(ID_EVENT_CUR_NEG_SEQ);  //���������
  else
    Clr_Event_Instant(ID_EVENT_CUR_NEG_SEQ);  //����������ȷ
}
#endif
/***********************************************************************
�������ܣ���ȡ��ѹ����˲ʱ״̬��
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_EVENT_A_VOLT_OVERLOAD
void Check_Overload_Volt(void)
{
  
  if(Check_Power_Grid_Event())
  {
    Clr_Event_Instant(ID_EVENT_A_VOLT_OVERLOAD);  //A��ѹ��ѹ���
    Clr_Event_Instant(ID_EVENT_B_VOLT_OVERLOAD);  //B��ѹ��ѹ���
    Clr_Event_Instant(ID_EVENT_C_VOLT_OVERLOAD);  //C��ѹ��ѹ���
    return ;
  }
  
  if((FP32S)Measu_InstantData_ToPub_PUCK.Volt.A/(FP32S)UNIT_V>Get_Un()*(FP32S)1.25)
  {
    Set_Event_Instant(ID_EVENT_A_VOLT_OVERLOAD);  //A��ѹ��ѹ
    Event_Vol_Cur.Over_Vol[0]=Measu_InstantData_ToPub_PUCK.Volt.A;
  }
  if((FP32S)Measu_InstantData_ToPub_PUCK.Volt.A/(FP32S)UNIT_V<Get_Un()*(FP32S)1.20)  //���ߵ���,����ϵ�������
    Clr_Event_Instant(ID_EVENT_A_VOLT_OVERLOAD);  //A��ѹ��ѹ���

  if((FP32S)Measu_InstantData_ToPub_PUCK.Volt.B/(FP32S)UNIT_V>Get_Un()*(FP32S)1.25)
  {
    Set_Event_Instant(ID_EVENT_B_VOLT_OVERLOAD);  //B��ѹ��ѹ
    Event_Vol_Cur.Over_Vol[1]=Measu_InstantData_ToPub_PUCK.Volt.B;
  }
  if((FP32S)Measu_InstantData_ToPub_PUCK.Volt.B/(FP32S)UNIT_V<Get_Un()*(FP32S)1.20)  //���ߵ���,����ϵ�������
    Clr_Event_Instant(ID_EVENT_B_VOLT_OVERLOAD);  //B��ѹ��ѹ���

  if((FP32S)Measu_InstantData_ToPub_PUCK.Volt.C/(FP32S)UNIT_V>Get_Un()*(FP32S)1.25)
  {
    Set_Event_Instant(ID_EVENT_C_VOLT_OVERLOAD);  //B��ѹ��ѹ
    Event_Vol_Cur.Over_Vol[2]=Measu_InstantData_ToPub_PUCK.Volt.C;
  }
  if((FP32S)Measu_InstantData_ToPub_PUCK.Volt.C/(FP32S)UNIT_V<Get_Un()*(FP32S)1.20)  //���ߵ���,����ϵ�������
    Clr_Event_Instant(ID_EVENT_C_VOLT_OVERLOAD);  //B��ѹ��ѹ���

  if(Get_SysParse_Mode()==PARSE_331)
    Clr_Event_Instant(ID_EVENT_B_VOLT_OVERLOAD);  //B�಻�ж�
}
#endif

/***********************************************************************
�������ܣ��ж��Ƿ��ǹ���ģʽ
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_EVENT_FAC_ON
void Check_Fac_Status(void)
{
  if(Get_Sys_Status()!=SYS_NORMAL)
  {
    Clr_Event_Instant(ID_EVENT_FAC_ON);
    return ;
  }
  if(Get_Meter_Hard_Mode()==MODE_FAC)
    Set_Event_Instant(ID_EVENT_FAC_ON);
  else
    Clr_Event_Instant(ID_EVENT_FAC_ON);  
}
#endif

/***********************************************************************
�������ܣ��ж��Ƿ����߶̽�
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_EVENT_KEY_SWITCH
void Check_Key_Switch(void)
{
  if(Get_Sys_Status()!=SYS_NORMAL)
  {
    Clr_Event_Instant(ID_EVENT_KEY_SWITCH);
    return ;
  }
  if(Get_Meter_Hard_Mode()!=MODE_RUN)
    Set_Event_Instant(ID_EVENT_KEY_SWITCH);
  else
    Clr_Event_Instant(ID_EVENT_KEY_SWITCH);  
}
#endif
/***********************************************************************
�������ܣ��жϱ�̿����Ƿ��
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_EVENT_PRGKEY_ON
void Check_Prg_Key(void)
{
  if(Get_Sys_Status()!=SYS_NORMAL)   //VCC
  {
    Clr_Event_Instant(ID_EVENT_PRGKEY_ON);
    return ;
  }
  if(B_PRG_KEY_STATUS)  //�����ߵ�ƽ
   KeyInitStatus.Prg=KEY_INIT_STATUS;
  
  if(KEY_INIT_STATUS==KeyInitStatus.Prg)
  {
    if(Key_Value_Pub.Key.Bit.PrgKey)
      Set_Event_Instant(ID_EVENT_PRGKEY_ON);
    else
      Clr_Event_Instant(ID_EVENT_PRGKEY_ON);
  }
  else
  {
    Clr_Event_Instant(ID_EVENT_PRGKEY_ON);
  }
}
#endif

/***********************************************************************
�������ܣ��ж��ֶ���������ť�Ƿ��
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_CLR_DEMAND_KEY
void Check_ClrDemand_Key(void)
{
 if(Get_Sys_Status()!=SYS_NORMAL)    //VCC
 {
    Clr_Event_Instant(ID_CLR_DEMAND_KEY);
    return ;
 }
 
 if(B_PRG_KEY_STATUS)  //�����ߵ�ƽ
   KeyInitStatus.Prg=KEY_INIT_STATUS;
 
 if(KEY_INIT_STATUS==KeyInitStatus.Prg)
 {
  if(B_PRG_KEY_STATUS==0)
    Set_Event_Instant(ID_CLR_DEMAND_KEY);
  else
    Clr_Event_Instant(ID_CLR_DEMAND_KEY);
 }
 else
 {
   Clr_Event_Instant(ID_CLR_DEMAND_KEY);   
 }
}
#endif

/***********************************************************************
�������ܣ��ж����ñ��ַ�����Ƿ��
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_METER_ADDR_EN
void Check_MeterAddr_Key(void)
{
  if(Inter_Right_Key_STATUS)                  //���ñ��ַ��ť
    Clr_Event_Instant(ID_METER_ADDR_EN);
  else
    Set_Event_Instant(ID_METER_ADDR_EN);  
}
#endif
/***********************************************************************
�������ܣ��ж��ϸ��Ƿ��
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_EVENT_UP_COVER_OPEN
void Check_UpCover(void)
{
 if(Get_Sys_Status()!=SYS_NORMAL)    //VCC
 {
    Clr_Event_Instant(ID_EVENT_UP_COVER_OPEN);
    Clr_Event_Instant(ID_EVENT_UP_COVER_CLOSE); 
    return ;
 }
  
  if(UP_COVER_STATUS)   //����������ǰ���ȥ��
  {
    Set_Event_Instant(ID_EVENT_UP_COVER_OPEN);
    Clr_Event_Instant(ID_EVENT_UP_COVER_CLOSE); 
  }
  else
  {
    Clr_Event_Instant(ID_EVENT_UP_COVER_OPEN); 
    Set_Event_Instant(ID_EVENT_UP_COVER_CLOSE);
  }
}
#endif
/***********************************************************************
�������ܣ��жϺ��(Ǧ��)�Ƿ��
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_EVENT_UP_COVER_OPEN
void Check_DownCover(void)
{
 if(Get_Sys_Status()!=SYS_NORMAL)    //VCC
 {
    Clr_Event_Instant(ID_EVENT_LEAD_COVER_OPEN);
    Clr_Event_Instant(ID_EVENT_LEAD_COVER_CLOSE); 
    
    Clr_Event_Instant(ID_EVENT_DOWN_COVER_OPEN);
    Clr_Event_Instant(ID_EVENT_DOWN_COVER_CLOSE); 
    
    return ;
 }
 
  if(DOWN_COVER_STATUS)  //����������ǰ���ȥ��,�˸��ǰ�װ�ں���ϵ�
  {
    Set_Event_Instant(ID_EVENT_LEAD_COVER_OPEN);
    Clr_Event_Instant(ID_EVENT_LEAD_COVER_CLOSE);  
    
    Set_Event_Instant(ID_EVENT_DOWN_COVER_OPEN);
    Clr_Event_Instant(ID_EVENT_DOWN_COVER_CLOSE);  
  }
  else
  {
    Clr_Event_Instant(ID_EVENT_LEAD_COVER_OPEN);  
    Set_Event_Instant(ID_EVENT_LEAD_COVER_CLOSE);
    
    Set_Event_Instant(ID_EVENT_DOWN_COVER_OPEN);
    Clr_Event_Instant(ID_EVENT_DOWN_COVER_CLOSE);  
  }
}
#endif
/***********************************************************************
�������ܣ���ȡʱ�ӵ��Ƿѹ״̬��
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_EVENT_RTC_BAT_LOW
void Check_RTCBat_Low(void)
{
  if(Get_Sys_Status()!=SYS_NORMAL)
  {
    Clr_Event_Instant(ID_EVENT_RTC_BAT_LOW);
    return ;
  }
  if(B_BATLOWRTC_TEST_STATUS)
    Clr_Event_Instant(ID_EVENT_RTC_BAT_LOW);
  else
    Set_Event_Instant(ID_EVENT_RTC_BAT_LOW);  
}
#endif
/***********************************************************************
�������ܣ���ȡ�͹��ĵ��Ƿѹ״̬��
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_EVENT_RTC_BAT_LOW
void Check_LPWBat_Low(void)
{
  if(Get_Sys_Status()!=SYS_NORMAL)
  {
    Clr_Event_Instant(ID_EVENT_LOWPWR_BAT_LOW);
    return ;
  }
  
  if(B_BATLOW_TEST_STATUS)
    Clr_Event_Instant(ID_EVENT_LOWPWR_BAT_LOW);
  else
    Set_Event_Instant(ID_EVENT_LOWPWR_BAT_LOW);  
}
#endif
/***********************************************************************
�������ܣ���ȡAB�л�ģʽ��ť
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_EVENT_AB_FUNC_KEY
void Check_AB_Func_Key(void)
{
  if((Inter_Up_Key_STATUS==1)&&(Inter_Down_Key_STATUS==1))  //û�а�ť����
    Clr_Event_Instant(ID_EVENT_AB_FUNC_KEY);
  else                         //��һ����ť����
    Set_Event_Instant(ID_EVENT_AB_FUNC_KEY);  
}
#endif
/***********************************************************************
�������ܣ���ȡAB�л�ģʽ��ť
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_EVENT_ADJUST_MEASU
void Set_Cal_Event(void)
{
  INT8U FLag,temp;
  INT32U bootflag;
  
  FLag=Read_Storage_Data_PUCK(DI_CAL_STATUS,&temp,1);
  if(0==FLag)
  {
    ASSERT(A_WARNING,0);
    return ;
  }
  if(2!=temp)   //У���¼�������û������0����1
  {
    Set_Event_Instant(ID_EVENT_ADJUST_MEASU);
    return ;
  }
    
  FLag=Read_Storage_Data_PUCK(BOOT_FLAG,&bootflag,4);   //ϵͳ������ʼ����־
  if(0==FLag || FIRST_BOOT_ON_FLAG!=bootflag)  //�����������߶�����ֵ��Ϊ FIRST_BOOT_ON_FLAG
  {
   Set_Event_Instant(ID_EVENT_ADJUST_MEASU);
    return ;
  } 
  Clr_Event_Instant(ID_EVENT_ADJUST_MEASU);
}
#endif
/********************************************************************************
����ԭ�ͣ�
���ܣ����ϵͳʱ�ӹ���

*********************************************************************************/
void Monitor_Meter_System_Osc(void)
{
  if(SYS_NORMAL==Sys_Status.Status)
  {
    if(CSC!=0x01 ||CKC!=0x38)
    {
      Beep_For_OSC_Alarm_PUCK();
      DEBUG_PRINT(PUCK,1,"MCU Osc System Error:MSTOP=%d,HIOSTOP=%d,XTSTOP=%d",MSTOP,HIOSTOP,XTSTOP);  
      Set_Event_Instant(ID_EVENT_OSC_ERR); 
      return ;
    }
    Clr_Event_Instant(ID_EVENT_OSC_ERR);
    return ;
  }
  
  if(CSC!=0x01 ||CKC!=(0x38|RSUME_CLOCK_DIV))
  {
    Beep_For_OSC_Alarm_PUCK();
    DEBUG_PRINT(PUCK,1,"MCU Osc System Error:MSTOP=%d,HIOSTOP=%d,XTSTOP=%d",MSTOP,HIOSTOP,XTSTOP);  
    Set_Event_Instant(ID_EVENT_OSC_ERR); 
    return ;
  }
  Clr_Event_Instant(ID_EVENT_OSC_ERR);
}

/********************************************************************************
����ԭ�ͣ�
���ܣ���ȡ����ϵ�״̬��

*********************************************************************************/
void Get_Meter_PowerOn(void)
{    
  if(Get_Sys_Status()==SYS_NORMAL)
  {
    if(POWER_OFF==Power_Status.Power)
    {
      Clr_Event_Instant(ID_EVENT_POWER_OFF);  //�����¼�����
      Power_Status.Power=POWER_ON;           //�ϵ��¼�����
      SET_STRUCT_SUM(Power_Status);  
    }
    if(ABNORMAL_RESET==Power_Status.Power)
    {
      Set_Event_Instant(ID_EVENT_RESET);     //��λ�¼�
      Power_Status.Power=POWER_ON;           //�ϵ��¼�����
      SET_STRUCT_SUM(Power_Status);  
    }
  }
}