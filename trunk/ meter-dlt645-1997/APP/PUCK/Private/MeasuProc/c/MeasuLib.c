#define MEASULIB_PUCK
#include "Pub_PUCK.h"
#include   "MeasuLib.h"


/******************************�ļ�����*********************************************
�ļ����ܣ������⺯����������

***********************************************************************************/
/**********************************************************************************/
void Delayn10MS(INT32U n)
{
  INT32U i;
  for(i=0;i<n;i++)
  {
    WAITFOR_DRV_MS_TIMEOUT(10);
  }
}

/**********************************************************************************
�������ܣ�����������е��ܼĴ�������,���ܳ�ֵΪ0
��ڣ� ��   
���ڣ� 1---------�ɹ�;
       0---------ʧ��;
**********************************************************************************/
INT8U Clr_Energ_Reg_PwrOn(void)
{
  INT8U i,Flag,temp[4];
  
  //��A��B��C�������й����ܣ��޹����ܣ�����ܼĴ�������-------------------------------PUCK
  for(i=REG_R_AENERG_CLR;i<=REG_R_SUMENERG_CLR;i++)
  {
    Flag=Measu_RdAndCompData_3Times(i,temp);
    if(Flag==0)
      break;
  }
  return  Flag;
}  

/**********************************************************************************
�������ܣ�Ӳ����λ
��ڣ�    
LastData-----�����Ĵ�����ַ
LastPara-------����
���ڣ� 1---------SIG��Ӳ���źŶ���ȷ,��λ�ɹ�;
       0---------SIG��Ӳ���ź��κ�һ������,��λʧ��;
**********************************************************************************/
INT8U MeasuIC_HardRst(void)
{
  INT8U i,flag;
  INT32U temp;
  
  //CLOSE_MEASU_PWR;
  //SYS_TimeDly_Ms(200);                  //��ʱ200ms
  OPEN_MEASU_PWR;
  SYS_TimeDly_Ms(20);            //��ʱ200ms 
  for(i=0;i<5;i++)
  {
    MEASU_RST_0;
    SYS_TimeDly_Ms(10);           //ԭ������ʱ25us���ɣ�
    MEASU_RST_1;
    SYS_TimeDly_Ms(10);            //ԭ���ϸ�λ��500us���ܲ���SPI
    if(!MEASU_SIG_STAT)          //�ж�SIG���Ƿ�Ϊ0�����ǣ����ʾ����------------------PUCK  
    {
      //SYS_TimeDly_Ms(10);           //��ʱ10mS
      flag=Measu_RdAndCompData_3Times(REG_R_SIG,(INT8U *)&temp);
           
      if((flag==0)||(temp==0xffffff))
      {
        continue;
      }
      if(GET_BIT(temp,7))        //�ж�Sflag.7״̬�Ƿ�Ϊ1�����ǣ����ʾ����------------------PUCK
      {
        DEBUG_PRINT(PUCK,PRINT_PUCK_MEA_EN,"MeasuIC Reset Ok,SIG=0X%lx!",temp);  
        return 1;
      }
      SYS_TimeDly_Ms(50);            //��ʱ50mS
    }
    else
    {
      SYS_TimeDly_Ms(50);               //��ʱ50mS
    }    
  }
  MeasuStatusMode.HardRstErr=1;
  SET_STRUCT_SUM(MeasuStatusMode);
  return  0;
}
/**********************************************************************************
�������ܣ� ����ϵ�У��������
��ڣ�   void
���ڣ� 1-------��ʾ��ҪУ����0--------------��ʾ����ҪУ��
**********************************************************************************/
void Clr_Cal_Requst(void)
{
  INT8U Flag,i;
  INT32U temp;
  
  for(i=0;i<3;i++)
  {
    Flag=Measu_RdAndCompData_3Times(REG_R_ENFLAG,(INT8U *)&temp);
    if((Flag==0)||(temp==0xffffff))  //����״̬�Ĵ��������󣬶Ե��ܵ�Ӱ�죬��ֵ�����ܶ�Ϊ0xffffff
    continue;
    
    if(GET_BIT(temp,16)==0)           //�ж�Sflag.16״̬�Ƿ�Ϊ1�����ǣ����ʾУ������
      return ;
  }
}
/**********************************************************************************
�������ܣ��Լ���оƬ��para���ڿ�para�ȶԣ�����װ�ز���
��ڣ�    
���ڣ�1----------װ�سɹ� 
**********************************************************************************/
INT8U Load_MeasureIC_Para(void)
{
  INT8U Flag;
  
  Flag=Load_All_Para_To_IC();      
  if(Flag)                     //д��ɹ�
  {
    //Clr_Energ_Reg_PwrOn();    //������ܼĴ���
    Pri_MeasuStatVar.MeasuIntOk=1;   //����оƬ��ʼ����ɣ�����������������
    Init_Pulse_Port(1);
    SET_STRUCT_SUM(Pri_MeasuStatVar);
    DEBUG_PRINT(PUCK,PRINT_PUCK_MEA_EN,"Write To IC Para Succeed!");
    Clr_Cal_Requst();
  }
  else
  {
    MeasuStatusMode.Retry=1;   //����оƬ����д��������
    SET_STRUCT_SUM(MeasuStatusMode);
    DEBUG_PRINT(PUCK,PRINT_PUCK_MEA_EN,"Write To IC Para Failed,Waiting For Retry!");
  }
  return Flag;  
}
/**********************************************************************************
�������ܣ��ϵ��ʼ��MeasuIC
��ڣ�    
LastData-----�����Ĵ�����ַ
LastPara-------����
���ڣ� ��ʾ��λ�ɹ�;����0����ʾ��λʧ��
**********************************************************************************/
INT8U InitMeasuAfterPwrOn(void)
{
  INT8U Flag;
  
  Flag=MeasuIC_HardRst();
  if(!Flag)     //Ӳ����λʧ��
  {
    DEBUG_PRINT(PUCK,PRINT_PUCK_MEA_EN,"Measure_Error----->Hard Reset Error After Power On!");
    return 0;
  }
  
  //Flag=Clr_Energ_Reg_PwrOn();    //���Ӳ���ɿ���λ��оƬ�ڲ�����������˾��������
  Flag=Load_MeasureIC_Para();
  Clr_Energ_Accu();   //������ڼ�����������ļĴ���
  return Flag;
}
/**********************************************************************************
�������ܣ������ϴθ�λ���ϵͳ״̬����������ʼ��MeasuIC�ķ�ʽ
��ڣ�    
LastData-----�����Ĵ�����ַ
LastPara-------����
���ڣ� ��ʾ��λ�ɹ�;����0����ʾ��λʧ��
**********************************************************************************/
void Init_Measure_IC(void)
{
  InitMeasuAfterPwrOn();
  SET_STRUCT_SUM(Pri_MeasuStatVar);
}
/**********************************************************************************
�������ܣ����SIG����״̬�Լ�У������У����Ƿ���ȷ
��ڣ���
���ڣ�1-------״̬����;0--------״̬�쳣
**********************************************************************************/
INT8U ChkMeasuICWorkStatus(void)
{
  INT8U i,num;

  if(MEASU_SIG_STAT) //����
    return MEASU_NO_ERR;
  
  for(i=0,num=0;i<5;i++)  //������5��
  {
    SYS_TimeDly_Ms(10);
    if(!MEASU_SIG_STAT)      //�쳣
      num++;
  }
  
  if(num<=2)   //5������3��������������
     return MEASU_NO_ERR;

  DEBUG_PRINT(PUCK,PRINT_PUCK_MEA_EN,"Measure_Error----->MeasuIC SIG_Signal=0!"); 
  MeasuStatusMode.Retry=1;
  SET_STRUCT_SUM(MeasuStatusMode);
  return MEASU_SIGN_ERR; 
}
/**********************************************************************************
�������ܣ���ȡ��ǰ 331/341ģʽ��
��ڣ���
���ڣ�331/341ģʽ��
**********************************************************************************/
INT8U Get_SysParse_Mode(void)
{ 
  if(MeasuSysMode.ParseMode<=PARSE_341)
    return MeasuSysMode.ParseMode;
  
  ASSERT(A_WARNING,0);
  return DEFAULT_PARSE_SPEC;
}

/**********************************************************************************
�������ܣ���ȡ��ѹͨ��ADC���汶��
��ڣ���
���ڣ���ѹͨ��ADC���汶��
**********************************************************************************/
INT32U Get_Volt_Adj_Rate(void)
{  
  INT8U ParseMode;
  INT32U temp;
  
  ParseMode=Get_SysParse_Mode();
   if(ParseMode==PARSE_331)    //331ģʽ�µ�ѹͨ��ADC����ѡ��Ϊ2��
    temp=V_GAIN_RATE2;
  else                         //341ģʽ�µ�ѹͨ��ADC����ѡ��Ϊ1��
    temp=V_GAIN_RATE1;  
  return temp;
}
/**********************************************************************************
�������ܣ���ȡ��ǰ ��ѹ���ģʽ��
��ڣ���
���ڣ���ѹģʽ��
**********************************************************************************/
INT8U Get_SysVolt_Mode(void)
{  
  if(MeasuSysMode.V_Spec<=VOLT_3380)
    return MeasuSysMode.V_Spec;
  
  ASSERT(A_WARNING,0); 
  return DEFAULT_VOLT_SPEC;
}

/**********************************************************************************
�������ܣ���ȡ��ǰ �������ģʽ��
��ڣ���
���ڣ�����ģʽ��
**********************************************************************************/
INT8U Get_SysCurr_Mode(void)
{
  if(MeasuSysMode.I_Spec<=CURR_30_100)
    return MeasuSysMode.I_Spec;
  
  ASSERT(A_WARNING,0);
  return DEFAULT_CURR_SPEC;
}
/**********************************************************************************
�������ܣ���ȡ��ǰ���峣��ģʽ��
��ڣ���
���ڣ�331/341ģʽ��
**********************************************************************************/
INT8U Get_SysPulse_Mode(void)
{  
  if(MeasuSysMode.P_Spec<=PULSE_TYPE2)
    return MeasuSysMode.P_Spec;
  
  ASSERT(A_WARNING,0);
  return DEFAULT_PULSE_SPEC;
}

/**********************************************************************************
�������ܣ���ȡTH��TFģʽ��
��ڣ���
���ڣ�TH_MODE/TF_MODEģʽ��
**********************************************************************************/
INT8U Get_SysTHF_Mode(void)
{
  if(MeasuSysMode.T_FH<=TF_MODE)
    return MeasuSysMode.T_FH;
  
  ASSERT(A_WARNING,0);
  return DEFAULT_TFH_SPEC;
}

/**********************************************************************************
�������ܣ�����331/341��TF/THģʽ��������MeasuIC���������ۼӼĴ�����
��ڣ���
���ڣ�
        ENERG_SUM_MODE0-------341���Ժͼӣ�331������
        ENERG_SUM_MODE1--------341�����ͼӣ�331����
**********************************************************************************/
INT32U GetEnergSumMode(void)
{
  INT8U THF_Spec,ParseMode;
  INT32U WrPara;
  
  THF_Spec=Get_SysTHF_Mode();
  ParseMode=Get_SysParse_Mode();
   
     
  if(THF_Spec==TF_MODE)    //������
  {
    if(ParseMode==PARSE_341)    //341���Ժͼӣ�331������
      WrPara=ENERG_SUM_MODE0;
    else                        //341�����ͼӣ�331���Ժ�
      WrPara=ENERG_SUM_MODE1;
  }
  else                   //˫����    
  {
    if(ParseMode==PARSE_341)    //341�����ͼӣ�331���Ժ�
      WrPara=ENERG_SUM_MODE1;
    else                        //341���Ժͼӣ�331������
      WrPara=ENERG_SUM_MODE0;
  }
  return WrPara;
}

/**********************************************************************************
�������ܣ�����A/B/C/��������ֵ
��ڣ���
���ڣ�1/2/3/4������
ע�� P-----�����ꣻQ-------�����꣬��ʱ�뷽��1/2/3/4��
**********************************************************************************/
INT8U	GetQuadrant(INT8U AcpowerDir,INT8U ReacPowerDir)
{	
  if(AcpowerDir==ReacPowerDir)      //1����3����
  {
    if(AcpowerDir==0)     //P+ Q+
      return QUADRANT1;
    else                  //P- Q-
      return QUADRANT3;    
  }
  else
  {
    if(AcpowerDir==0)     //P+ Q-
      return QUADRANT4;
    else                  //P- Q+
      return QUADRANT2;     
  }  
}
/**********************************************************************************
�������ܣ��������ޣ��޹����ʣ��й����ʣ������ѹ����ʵ�ʼн�
��ڣ���
���ڣ���ʵ�Ƕ�
**********************************************************************************/
INT32U	GetAngle(INT8U Quadrant,INT32U Reacower,INT32U ActiPower,INT8U Reg)
{	
  FP32S Dgree;
  
#ifdef MEASU_ANGLE_RD 
  INT8U Flag;
  INT32U Angle;
#endif

#ifdef MEASU_ANGLE_RD
    Flag=Measu_RdAndCompData_3Times(Reg,(INT8U *)&Angle);
    if(Flag==0)
    return 0;
    Dgree=(FP32S)Angle*0.001366;  //ע�ⵥλ��UNIT_DEGREE
#else
    if(ActiPower<=5)  //��ֹ��0�����0.005w,�������ʣ�0.33w
      Dgree=0L;
    else
    {
      Dgree=atan((FP32S)Reacower/ActiPower);
      Dgree=(Dgree*180*UNIT_DEGREE)/PAI;	//��λ0.01�ȣ��ǶȲ��ǴӼĴ���ȡ�������Լ������
    }
#endif    
  switch(Quadrant)
  {
  case QUADRANT1:				//��1����
    break;
  case QUADRANT2:				//��2����
    Dgree=18000-Dgree;
    break;	
  case QUADRANT3:				//��3����
    Dgree=18000+Dgree;
    break;	
  default:			        //��4����
    Dgree=36000-Dgree;
    break;
  }
  return (INT32U)Dgree;
}
/**********************************************************************************
�������ܣ�����У���֣�У�����ݣ�У��
��ڣ�
       Code-----------У��ָ��
       Para3----------У������
       ParaLen-------У�������ֽڳ���
���ڣ�1------------�ɹ���0-----------------ʧ��
**********************************************************************************/
INT8U CalibMeterProc_PUCK(INT16U Code,INT8U Para[],INT8U ParaLen)
{
   return 1;
}
/**********************************************************************************
�������ܣ���ȡIC�Ĳ���У���

���ڣ�1---------���ɹ������Ƚ���ȷ;0--------��ʾʧ��
**********************************************************************************/
INT8U Get_IC_ParaSum3(INT32U *Cs)
{
  INT32U Sum;
  INT8U Flag;
  
  Flag=Measu_RdAndCompData_3Times(REG_R_SUM,(INT8U *)&Sum);     //��ICУ��������У���
  if(Flag==0)
  {
    DEBUG_PRINT(PUCK,PRINT_PUCK_MEA_EN,"Measure_Error----->Get IC Cs Failed!"); 
    return 0;
  }
  
  *Cs=Sum;  
  return 1;
}
/**********************************************************************************
�������ܣ���ȡʵ���õĲ���Ĭ�ϲ�����У���
**********************************************************************************/
INT8U Get_User_All_ParaSum3(INT32U *Cs)
{
  INT8U i,Flag,temp[3];
  INT32U Sum;
  
  Flag=1;
  for(Sum=0,i=1;i<IC_PARA_NUM;i++)
  {
    if(InitMeasuPara[i].ParaFlag==DEFA_TYPE)
      Sum+=InitMeasuPara[i].Para;
    if(InitMeasuPara[i].ParaFlag==SPEC_TYPE)
      Sum+=InitMeasuPara[i].FuncPtr();
    if(InitMeasuPara[i].ParaFlag==ADJU_TYPE)
    {
      Flag=Read_Storage_Data_PUCK(InitMeasuPara[i].Di,temp,3);
      ASSERT(A_WARNING,1==Flag); 
      Sum+=(INT32U)(temp[2]*65536L+temp[1]*256L+temp[0]);
    }
  }
  if(!Flag)
    return 0;
  
  *Cs=(Sum&0xffffff);
  return 1;  
}
/**********************************************************************************
�������ܣ���ȡ��Ƶ�������
��ڣ���
���ڣ���Ƶ���峣������
**********************************************************************************/
INT32U Get_HighPulse_Const(void)
{  
  INT32U temp;
  INT8U U_spec,I_spec;
  
  U_spec=Get_SysVolt_Mode();
  I_spec=Get_SysCurr_Mode();
  
  temp=HighPulseConst[U_spec][I_spec];

  if((INT32U)temp<0x04 || (INT32U)temp>0x0D00)
  {
    DEBUG_PRINT(PUCK,PRINT_PUCK_MEA_EN,"Measure_Error----->Hight Pulse Const < 0x04");
    temp=0x04;
  }
  
  if((INT32U)temp>0x0D00)
  {
    DEBUG_PRINT(PUCK,PRINT_PUCK_MEA_EN,"Measure_Error----->Hight Pulse Const > 0x0d00");
    temp=0x0D00;
  }
  
  return  (((INT32U)temp)&0xFFFFFF);
}

/**********************************************************************************
�������ܣ���ȡ������������
��ڣ���
���ڣ�
**********************************************************************************/
INT32U Get_Istart_Const(void)
{
  INT8U I_Spec;
  I_Spec=Get_SysCurr_Mode();
  return (Startup_Current[I_Spec]);  
}

/**********************************************************************************
�������ܣ���ȡIregion4
��ڣ���
���ڣ�

INT32U Get_Iregion4(void)
{
  FP32S temp;
  
  temp=0.648*I_REGION_AREA*Get_In()*pow(2,23);
  
  return ((INT32U)temp&0XFFFFFF);  
}
**********************************************************************************/

/***********************************************************************
�������ܣ����ݷ������¼�Id��״̬��������Ӧ��״̬
��ڣ���
���ڣ���
***********************************************************************
void Clr_All_Cal_Status(void)
{ 
  mem_set((void *)(&Cal_Status_Var),
          0x00,
          sizeof(Cal_Status_Var),
          (void *)(&Cal_Status_Var),
          sizeof(Cal_Status_Var));
  SET_STRUCT_SUM(Cal_Status_Var); 

}
***********************************************************************
�������ܣ����ݷ������¼�Id��״̬��������Ӧ��״̬
��ڣ���
���ڣ���
***********************************************************************
void Set_Cal_Status_Byte(INT16U Id,INT8U Status)
{
  
  INT8U Byte,Bit;
  if((Id< ADJ_METER_A_POW)||(Id>ADJ_METER_C_CUR))
    return ;
  
  Byte=(INT8U)(Id-ADJ_METER_A_POW)/8;
  Bit=(INT8U)(INT8U)(Id-ADJ_METER_A_POW)%8;
  if(Status)
    SET_BIT(Cal_Status_Var.Cal_Status[Byte],Bit);
  else
    CLR_BIT(Cal_Status_Var.Cal_Status[Byte],Bit);    
  SET_STRUCT_SUM(Cal_Status_Var);
}

***********************************************************************
�������ܣ����ݷ������¼���������Ӧ��˲̬״̬��
��ڣ���
���ڣ���
***********************************************************************
void Set_Cal_Status(INT16U Id)
{
  Set_Cal_Status_Byte(Id,1);
}
***********************************************************************
�������ܣ�����λ�����ֽڵ�λ�������Ӧ��λ��Ϣ���ֽ���Ϣ
��ڣ���
���ڣ���
***********************************************************************
void Clr_Cal_Status(INT16U Id)
{
  Set_Cal_Status_Byte(Id,0); 
}
***********************************************************************
�������ܣ�����λ�����ֽڵ�λ����ȡ��Ӧ��λ��Ϣ���ֽ���Ϣ
��ڣ���
���ڣ���
***********************************************************************
INT8U Get_Cal_Status(INT16U Id)
{
  INT8U Byte,Bit,temp;
  if((Id< ADJ_METER_A_POW)||(Id>ADJ_METER_C_CUR))
    return 0;
  
  Byte=(INT8U)(Id-ADJ_METER_A_POW)/8;
  Bit=(INT8U)(Id-ADJ_METER_A_POW)%8;
  
  temp=CHECK_STRUCT_SUM(Cal_Status_Var); 
  ASSERT(A_WARNING,1==temp);  

  temp=GET_BIT(Cal_Status_Var.Cal_Status[Byte],Bit);  
  return temp;    
}
**********************************************************************************
�������ܣ����ݲ�ͬ�����ͣ���ȡ���ֵ=(����ֵ-��ʵֵ)/��ʵֵ
���ڣ����

**********************************************************************************
FP32S Get_Error(INT8U Parse,INT8U Flag)
{
  FP32S err,Measu;
  INT8U Re;
  
  Re=CHECK_STRUCT_SUM(Measu_InstantData_ToPub_PUCK);
  ASSERT(A_WARNING,1==Re);
  ASSERT(A_WARNING,Parse<3);
  
  switch(Flag)
  {
    case TYPE_POWER:
      Measu=(FP32S)(*(&(Measu_InstantData_ToPub_PUCK.AcPower.A)+Parse));  
      if(Measu==0)
        return 1.0;
      err=(Measu*1000)/((FP32S)330*UNIT_KW_KAR)-1;
      return err;
    case TYPE_ANGLE:
      Measu=(FP32S)(*(&(Measu_InstantData_ToPub_PUCK.Angle.A)+Parse)); 
      if(Measu==0)
        return 1.0;
      err=Measu/((FP32S)60*UNIT_DEGREE)-1;
      return err;
    case TYPE_VOLT:
      Measu=(FP32S)(*(&(Measu_InstantData_ToPub_PUCK.Volt.A)+Parse));
      if(Measu==0)
        return 1.0;
      err=Measu/(Get_Un()*UNIT_V)-1;
      return err;
    case TYPE_CURR:
      Measu=(FP32S)(*(&(Measu_InstantData_ToPub_PUCK.Curr.A)+Parse));
      if(Measu==0)
      return 1.0;
      err=Measu/(Get_In()*UNIT_A)-1;
      return err;
  }  
  return 1.0;
}
**********************************************************************************
�������ܣ����ݲ�ͬ�����ͣ���ȡ���ֵ=(����ֵ-��ʵֵ)/��ʵֵ
���ڣ����

**********************************************************************************
void Set_Modi_Offset(INT8U Parse, FD32S err,INT8U Reg,INT8U RegLast,INT8U RegNum)
{
  INT32U para;
  INT8U Wrflag,Flag=0;
  
  switch(Parse)
  {
    case TYPE_POWER:
    case TYPE_VOLT:
    case TYPE_CURR:
      err=-err/(1+err);
      if(err>=0)
        para=(INT32U)(err*pow(2,23));
      else
        para=(INT32U)(pow(2,24)+err*pow(2,23));
      Flag=1;
      break;
      
    case TYPE_ANGLE:
      err=acos((1+err)*0.5)-PAI/3;
      if(err>=0)
        para=(INT32U)(err*pow(2,23));
      else
        para=(INT32U)(pow(2,24)+err*pow(2,23));
      Flag=1;
      break;
  }  
  if(!Flag)
    return ;
  Wrflag=Measu_WrAndCompData_3Times(Reg,para);
  ASSERT(A_WARNING,1==Wrflag); 
  for(Flag=0;Flag<RegNum;Flag++)
    Wrflag&=Measu_WrAndCompData_3Times(RegLast+Flag,para);
  ASSERT(A_WARNING,1==Wrflag); 
}
**********************************************************************************
�������ܣ�
���ڣ�
ע�⣺
**********************************************************************************
FP32S Get_Calc_Err(INT8U Type,FP32S Err)
{
  FD32S data;
  
  data=(FP32S)Err/MIN_ER_COFI;
  data=MIN_CAL_STEP*data;  
  return data;
}
**********************************************************************************
�������ܣ�
���ڣ�
ע�⣺
**********************************************************************************/
void Cal_Reg_Write(INT8U Reg,INT8U Reg1ast,INT8U Num,INT32U CalData)
{
  INT8U i;
  
  if(Measu_WrAndCompData_3Times(Reg,CalData)==0)
    ASSERT(A_WARNING,0);
  
  for(i=0;i<Num;i++)  //�Ժ����Ĳ����Ĵ���д
  {
    if(Measu_WrAndCompData_3Times(Reg1ast+i,CalData)==0)
      ASSERT(A_WARNING,0);
  }
}     
/**********************************************************************************
�������ܣ���У���õ�ĳһ������д�����оƬ
���ڣ�1---------д�ɹ���;0--------дʧ��
ע�⣺���е�У����������3���ֽڣ�
**********************************************************************************/
void Load_Adj_OnePara_To_IC(INT16U TempDI)
{
  INT8U Reg;
  //FD32S err;
  
  INT32U CalData;
  INT8U Rdflag;
  INT8U temp[3];
  
  if((TempDI<DI_POWER_A_0)||(TempDI>DI_CLR_PARA))
    return ;
  
  Rdflag=Read_Storage_Data_PUCK(TempDI,temp,3);
  if(!Rdflag)
    ASSERT(A_WARNING,0); 
  CalData=(INT32U)(temp[2]*65536L+temp[1]*256L+temp[0]);
  DEBUG_PRINT(PUCK,PRINT_PUCK_CHANNEL_EN,"Measure_Info----->Cal_Meter DI=0x%x,CalData=0x%lx",TempDI,CalData);
  
  EnMeasuCal();                             //У������дʹ��
  if((TempDI>=ADJ_METER_A_POW)&&(TempDI<=ADJ_METER_C_POW))     //�����������
  {
    Reg=REG_W_PGAIN_A0+(INT8U)(TempDI-ADJ_METER_A_POW);
    Cal_Reg_Write(Reg,Reg+3,1,CalData);
  }
  
  if((TempDI>=ADJ_METER_A_PHASE)&&(TempDI<=ADJ_METER_C_PHASE)) //��λ�������
  {
    Reg=REG_W_PHSREG_A0+(INT8U)(TempDI-ADJ_METER_A_PHASE)*5;
    Cal_Reg_Write(Reg,Reg+1,4,CalData);
  }
  
  if((TempDI>=ADJ_METER_A_VOL)&&(TempDI<=ADJ_METER_C_VOL))     //��ѹ����
  {
     Reg=REG_W_UGAIN_A+(INT8U)(TempDI-ADJ_METER_A_VOL);
     Cal_Reg_Write(Reg,0,0,CalData);
   }


  if((TempDI>=ADJ_METER_A_CUR)&&(TempDI<=ADJ_METER_C_CUR))    //��������
  {
     Reg=REG_W_IGAIN_A+(INT8U)(TempDI-ADJ_METER_A_CUR); 
     Cal_Reg_Write(Reg,0,0,CalData);
 }
  //����У��ͣ����ڱȶ�
  DisMeasuCal(); 
  
  /*
  OS_TimeDly_Ms(400);  //for Cs Refresh
  Rdflag=Get_User_All_ParaSum3(&CalData);
  if(Rdflag)
  {
    MeasuPara_CS.EppRom_Cs=CalData;
    SET_STRUCT_SUM(MeasuPara_CS);
    Rdflag=Get_IC_ParaSum3(&CalData);
    if(Rdflag)
    {
      MeasuPara_CS.IC_Cs=CalData;
      SET_STRUCT_SUM(MeasuPara_CS);
      return ;
    }
    ASSERT(A_WARNING,0); 
  }
  ASSERT(A_WARNING,0); 
  */
 
}
/**********************************************************************************
�������ܣ���ʹ�õ�У������д�����оƬ
���ڣ�1---------д�ɹ���;0--------дʧ��
**********************************************************************************/
INT8U Load_Spec_Adj_Para_To_IC(void)
{
  INT8U i,Rdflag,Wrflag,temp[3],Flag;
  INT32U para,CS;
  
  CS=0;
  EnMeasuCal();                             //У������дʹ��
  DEBUG_PRINT(PUCK,PRINT_PUCK_MEA_EN,"Measure_Info----->Load Epprom Para To Measure IC........");
  for(Flag=1,i=1;i<IC_PARA_NUM;i++)
  {
    if(InitMeasuPara[i].ParaFlag==DEFA_TYPE)
    {
      CS+=InitMeasuPara[i].Para;
      continue;
    }
    if(InitMeasuPara[i].ParaFlag==SPEC_TYPE)
      para=InitMeasuPara[i].FuncPtr();
    if(InitMeasuPara[i].ParaFlag==ADJU_TYPE)
    {
      Rdflag=Read_Storage_Data_PUCK(InitMeasuPara[i].Di,temp,3);
      ASSERT(A_WARNING,1==Rdflag); 
      para=(INT32U)(temp[2]*65536L+temp[1]*256L+temp[0]);
      Flag&=Rdflag;
    }
     Wrflag=Measu_WrAndCompData_3Times(i|0x80,para);
     ASSERT(A_WARNING,1==Rdflag); 
     Flag&=Wrflag;
     CS+=para;
  }
  
  DisMeasuCal();
  MeasuPara_CS.EppRom_Cs=CS&0xffffff;
  SET_STRUCT_SUM(MeasuPara_CS);
  
  OS_TimeDly_Ms(400);  //for Cs Refresh
  
  if(Flag && Get_IC_ParaSum3(&CS))
  {
    if(CS==MeasuPara_CS.EppRom_Cs)
    {
      MeasuPara_CS.IC_Cs=CS;
      SET_STRUCT_SUM(MeasuPara_CS);  
      return 1;
    }
  }
  return 0;
}
/**********************************************************************************
�������ܣ���MeasuICУ�����ݼĴ��������ݻָ����ϵ��ʼֵ����ʼ����У��������صĲ���
          EPROM�е�У������ͬ���ı�
��ڣ���
���ڣ�1---------�ָ��ɹ���0-----------�ָ�ʧ��
**********************************************************************************/
INT8U Load_All_Para_To_IC(void)
{
  INT8U Flag;
  INT32U Cs;
  
  Flag=0;
  
  EnMeasuCal();
  ClrMeasuCal();     //��У�����ݼĴ��������ݻָ����ϵ��ʼֵ
  DisMeasuCal();
  
  
  Flag=Measu_RdAndCompData_3Times(REG_R_SUM,(INT8U *)&Cs);     //��7022��У��������У���
  if(Flag==0)
  {
    MeasuStatusMode.Retry=1;
    SET_STRUCT_SUM(MeasuStatusMode);
    return 0;
  }
  
  if((Get_SysParse_Mode()==PARSE_341) && (Cs!=CHKSUM_INIT_341))  //�����ϵ�ʱ���CS
    DEBUG_PRINT(PUCK,PRINT_PUCK_MEA_EN,"Measure_Info----->Measure_IC Para Data(341) !=Default Value!");
  
  if((Get_SysParse_Mode()==PARSE_331) && (Cs!=CHKSUM_INIT_331)) //�����ϵ�ʱ���CS
    DEBUG_PRINT(PUCK,PRINT_PUCK_MEA_EN,"Measure_Info----->Measure_IC Para Data(331) !=Default Value!");
     
  Flag=Load_Spec_Adj_Para_To_IC();
  
  if(Flag==1)
  {
    DEBUG_PRINT(PUCK,PRINT_PUCK_MEA_EN,"Measure_Info----->All Cal Para Write Succeed!");
    return 1;  
  }
  if(Flag==0)
  {
    MeasuStatusMode.Retry=1;
    SET_STRUCT_SUM(MeasuStatusMode);
    DEBUG_PRINT(PUCK,PRINT_PUCK_MEA_EN,"Measure_Error----->Load Spec&&Adj Para Failed!");
    return 0;
  }
  return 0;
}

/**********************************************************************************
�������ܣ�������������д
��ڣ�3��
���ڣ����
**********************************************************************************/
void Retry_WritePara_To_IC(void)   //���й����У�IC��CS��EPPROM��CS��һ�£�����ĳ��д��������������Ҫ����д�Ʊ����
{
  INT8U Flag;
  
  Flag=CHECK_STRUCT_SUM(MeasuStatusMode); 
  if(ASSERT(A_WARNING,1==Flag)) //����״̬�ֿ��ܱ��ƻ���
   return ;
  
  if(MeasuStatusMode.Retry==1)
  {
    DEBUG_PRINT(PUCK,PRINT_PUCK_MEA_EN,"Measure_Error----->Retry Write IC Para.........");
    Flag=Load_Spec_Adj_Para_To_IC();
    SYS_TimeDly_Sec(5);
    if(Flag)
    {      
      DEBUG_PRINT(PUCK,PRINT_PUCK_MEA_EN,"Measure_Info----->Retry Write IC Para Succeed!");
      MeasuStatusMode.Retry=0;   //�Ѿ�д��ȷ,������д
      SET_STRUCT_SUM(MeasuStatusMode);
    }  
    else
      SYS_TimeDly_Sec(3);   //�����´�д�Ĺ���
  }
}
/**********************************************************************************
�������ܣ�
��ڣ���
���ڣ�
**********************************************************************************/
void PrintParaComp(void)
{
  INT8U Flag,temp[3],i;
  INT32U paraic,para;
  
  for(i=1;i<IC_PARA_NUM;i++)
  {
    Flag=Measu_RdAndCompPara_3Times(i,temp);
    ASSERT(A_WARNING,(1==Flag)); 
    paraic=(INT32U)(temp[2]*65536L+temp[1]*256L+temp[0]);
    
    if(InitMeasuPara[i].ParaFlag==DEFA_TYPE)
    {
      if(paraic!=InitMeasuPara[i].Para)
      DEBUG_PRINT(PUCK,PRINT_PUCK_MEA_EN,"Measure_Error-----Reg=%d,Rd=0x%lx,Real=0x%lx",i,paraic,(InitMeasuPara[i].Para&0xffffff)); 
    }
    
    if(InitMeasuPara[i].ParaFlag==SPEC_TYPE)
    {
      if(paraic!=InitMeasuPara[i].FuncPtr())
      DEBUG_PRINT(PUCK,PRINT_PUCK_MEA_EN,"Measure_Error-----Reg=%d,Rd=0x%lx,Real=0x%lx",i,paraic,InitMeasuPara[i].FuncPtr()); 
    }
    
    if(InitMeasuPara[i].ParaFlag==ADJU_TYPE)
    {
      Flag=Read_Storage_Data_PUCK(InitMeasuPara[i].Di,temp,3);
      ASSERT(A_WARNING,1==Flag); 
      para=(INT32U)(temp[2]*65536L+temp[1]*256L+temp[0]);
      if(paraic!=para)
      DEBUG_PRINT(PUCK,PRINT_PUCK_MEA_EN,"Measure_Error-----Reg=%d,Rd=0x%lx,Real=%0xlx",i,paraic,para); 
    }
  }
}
