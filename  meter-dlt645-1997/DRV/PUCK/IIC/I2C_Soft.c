#define SOFT_I2C_C
#include "DrvPub.h"

        

typedef struct
{ 
  void (* const Set_Sclk_Dir)(INT8U);
  void (* const Set_Sda_Dir)(INT8U);
  void (* const Set_Sclk_Pin)(INT8U);
  void (* const Set_Sda_Pin)(INT8U);
  INT8U (* const Get_Sda_Pin)(void);
}CONST_SOFT_IIC;

CONST_SOFT_IIC  CONST_I2C_PORT[IIC_SOFT_MAX_ID+1]=
{
#ifdef IIC_SOFT_ID0
  {&Set_3231_Sclk_Dir,&Set_3231_Sda_Dir,&Set_3231_Sclk_Pin,&Set_3231_Sda_Pin,&Get_3231_Sda_Pin},    //----------------0
#endif
#ifdef IIC_SOFT_ID1
  {&Set_Cal_Sclk_Dir,&Set_Cal_Sda_Dir,&Set_Cal_Sclk_Pin,&Set_Cal_Sda_Pin,&Get_Cal_Sda_Pin}    //----------------0
#endif
};

/**********************************************************************************
�������ܣ���ʼ��ģ��IIC��
��ڣ�
���ڣ�
**********************************************************************************/ 
void I2cSoft_Open(INT8U Id)   //��������Ϊ����״̬
{
  if(Id>IIC_SOFT_MAX_ID)  //ֱ�Ӷ��ԣ�����Ӱ���ٶȣ�----------PUCK
  {
    ASSERT(A_WARNING,0);
    return ;
  }
  
  CONST_I2C_PORT[Id].Set_Sclk_Dir(DIR_OUTPUT);
  CONST_I2C_PORT[Id].Set_Sclk_Pin(1);             //��Ϊ���Ϊ1
  CONST_I2C_PORT[Id].Set_Sda_Dir(DIR_OUTPUT);
  CONST_I2C_PORT[Id].Set_Sda_Pin(1);              //��Ϊ���Ϊ1
}
/**********************************************************************************
�������ܣ��ر�ģ��IIC��
��ڣ�
���ڣ�
**********************************************************************************/ 
void I2cSoft_Close(INT8U Id)   //��������Ϊ����״̬
{
  if(Id>IIC_SOFT_MAX_ID)  //ֱ�Ӷ��ԣ�����Ӱ���ٶȣ�----------PUCK
  {
    ASSERT(A_WARNING,0);
    return ;
  }
  
  CONST_I2C_PORT[Id].Set_Sclk_Dir(DIR_INPUT);
  CONST_I2C_PORT[Id].Set_Sclk_Pin(1);         //��Ϊ���Ϊ1
  CONST_I2C_PORT[Id].Set_Sda_Dir(DIR_INPUT);
  CONST_I2C_PORT[Id].Set_Sda_Pin(1);           //��Ϊ���Ϊ1
}

/**********************************************************************************
�������ܣ��������ģ��I2C��,11.0592�£�����SCLKƵ��Ϊ73.5k
��ڣ�
���ڣ�
**********************************************************************************/ 
INT8U I2cSoft_Start(INT8U Id)
{
  if(Id>IIC_SOFT_MAX_ID)  //ֱ�Ӷ��ԣ�����Ӱ���ٶȣ�----------PUCK
  {
    ASSERT(A_WARNING,0);
#ifdef Soft_I2c_Env
    longjmp(Soft_I2c_Env.Env,1);
#else
    return 0;
#endif 
  }
  
  CONST_I2C_PORT[Id].Set_Sda_Pin(1);
  CONST_I2C_PORT[Id].Set_Sclk_Pin(1);

  CONST_I2C_PORT[Id].Set_Sda_Pin(0);        //SDA��SCLKΪ��ʱ������һ���½���,��ʼ��������---------PUCK
  return 1;
}
/**********************************************************************************
�������ܣ�ֹͣ3231
��ڣ�
���ڣ�
**********************************************************************************/ 
INT8U I2cSoft_Stop(INT8U Id)    //��SCLKΪ�ߵ�����£�SDA����һ�������أ���Ϊֹͣ����
{
  if(Id>IIC_SOFT_MAX_ID)  //ֱ�Ӷ��ԣ�����Ӱ���ٶȣ�----------PUCK
  {
#ifdef Soft_I2c_Env
    longjmp(Soft_I2c_Env.Env,1);
#else
    return 0;
#endif 
  }
  
  CONST_I2C_PORT[Id].Set_Sda_Dir(DIR_OUTPUT);
  CONST_I2C_PORT[Id].Set_Sda_Pin(0);  

  CONST_I2C_PORT[Id].Set_Sclk_Pin(1);
  CONST_I2C_PORT[Id].Set_Sda_Pin(1);
  return 1;
}
/**********************************************************************************
�������ܣ���ӦACK����NACK
��ڣ�
���ڣ�
**********************************************************************************/ 
INT8U I2cSoft_Send_N_Ack(INT8U Id,INT8U Ack_Nack)
{
  if(Id>IIC_SOFT_MAX_ID)  //ֱ�Ӷ��ԣ�����Ӱ���ٶȣ�----------PUCK
  {
#ifdef Soft_I2c_Env
    longjmp(Soft_I2c_Env.Env,1);
#else
    return 0;
#endif 
  }
  
  CONST_I2C_PORT[Id].Set_Sclk_Pin(0);  //��0����ס����-----------------PUCK
  CONST_I2C_PORT[Id].Set_Sda_Dir(DIR_OUTPUT);
  CONST_I2C_PORT[Id].Set_Sda_Pin(Ack_Nack);  //Ack_NackΪ0��ʾACK��Ϊ1��ʾNACK    
  
  CONST_I2C_PORT[Id].Set_Sclk_Pin(1);  //SCLKΪ��ʱ��SDAΪ�ͣ���ʾ����ACK
  CONST_I2C_PORT[Id].Set_Sclk_Pin(0);
  return 1;
}
/**********************************************************************************
�������ܣ�����Ƿ���ACK�ź�
��ڣ�
���ڣ�1-------------�ɹ���0----------ʧ��
**********************************************************************************/ 
INT8U I2cSoft_Check_Ack(INT8U Id)
{
  INT8U count;
    
  if(Id>IIC_SOFT_MAX_ID)  //ֱ�Ӷ��ԣ�����Ӱ���ٶȣ�----------PUCK
  {
#ifdef Soft_I2c_Env
    longjmp(Soft_I2c_Env.Env,1);
#else
    return 0;
#endif 
  }
  
  CONST_I2C_PORT[Id].Set_Sda_Pin(1);        //����SDA,�ͷ�����-------------PUCK
  CONST_I2C_PORT[Id].Set_Sda_Dir(DIR_INPUT);
  
  CONST_I2C_PORT[Id].Set_Sclk_Pin(1);     //�����ߣ���ѯACK

  for(count=0;count<100;count++)
  {
    if(CONST_I2C_PORT[Id].Get_Sda_Pin()==0)  //ACK��Ӧ,Ϊ0����ʾ��ACK
    {
      CONST_I2C_PORT[Id].Set_Sclk_Pin(0);
      CONST_I2C_PORT[Id].Set_Sda_Dir(DIR_OUTPUT);
      return 1;
    }    
  }  
  CONST_I2C_PORT[Id].Set_Sclk_Pin(0);
  CONST_I2C_PORT[Id].Set_Sda_Dir(DIR_OUTPUT);
    
   ASSERT(A_WARNING,0);   //ֱ�Ӷ��ԣ�����Ӱ���ٶȣ�----------PUCK
  
#ifdef HARD_I2c_ENV    
    longjmp(Soft_I2c_Env.Env,1);
#endif 
    return 0;
}

/**********************************************************************************
�������ܣ�iic�����Ϸ�����:8bits
��ڣ�
���ڣ�1-------------�ɹ���0----------ʧ��
**********************************************************************************/ 
INT8U I2cSoft_Send_Byte(INT8U Id,INT8U sbyte)
{	
  INT8U i;

  if(Id>IIC_SOFT_MAX_ID)  //ֱ�Ӷ��ԣ�����Ӱ���ٶȣ�----------PUCK
  {
#ifdef Soft_I2c_Env
    longjmp(Soft_I2c_Env.Env,1);
#else
    return 0;
#endif 
  }
  
  CONST_I2C_PORT[Id].Set_Sclk_Pin(0);
  for (i=0;i<8;i++)
  {
      if(sbyte&0x80)
          CONST_I2C_PORT[Id].Set_Sda_Pin(1);
      else
          CONST_I2C_PORT[Id].Set_Sda_Pin(0);
      CONST_I2C_PORT[Id].Set_Sclk_Pin(1);    //SCL��ߣ���������
      CONST_I2C_PORT[Id].Set_Sclk_Pin(0);
      sbyte <<=1;
  }
  return(I2cSoft_Check_Ack(Id));	 	    
}
/********************************************************************************
********************************************************************************/
void I2cSoft_Reset(INT8U Id)
{
  INT8U i;
  
  DEBUG_PRINT(PUCK,1,"IIC_Error----->Reset I2c_Soft Device!"); 
  ASSERT(A_WARNING,0);
  I2cSoft_Start(Id);
  
  CONST_I2C_PORT[Id].Set_Sclk_Pin(0);
  CONST_I2C_PORT[Id].Set_Sda_Pin(1);  //SDA��1,SCL���壬�ͷ�����
  for(i=0;i<=9;i++)
  { 
    CONST_I2C_PORT[Id].Set_Sclk_Pin(1);    //SCL��ߣ���������
    CONST_I2C_PORT[Id].Set_Sclk_Pin(0);
  }  
  I2cSoft_Start(Id);
  I2cSoft_Stop(Id);
  I2cSoft_Open(Id);
} 
/**********************************************************************************
�������ܣ�iic�����϶�����:8bits
��ڣ�
���ڣ�1-------------�ɹ���0----------ʧ��
**********************************************************************************/ 
INT8U I2cSoft_Read_Byte(INT8U Id,INT8U *Dst)
{
  INT8U i;
  INT8U temp;

  if(Id>IIC_SOFT_MAX_ID)  //ֱ�Ӷ��ԣ�����Ӱ���ٶȣ�----------PUCK
  {
#ifdef Soft_I2c_Env
    longjmp(Soft_I2c_Env.Env,1);
#else
    return 0;
#endif     
  }
  
  CONST_I2C_PORT[Id].Set_Sda_Pin(1);        //����SDA,�ͷ�����-------------PUCK
  CONST_I2C_PORT[Id].Set_Sda_Dir(DIR_INPUT);
  
  for(i=0,temp=0;i<8;i++)
  {
      temp<<=1;
      CONST_I2C_PORT[Id].Set_Sclk_Pin(1);
      if(CONST_I2C_PORT[Id].Get_Sda_Pin())
        temp|=1;
      CONST_I2C_PORT[Id].Set_Sclk_Pin(0);
  }
  
  *Dst=temp;
  return  1;
}
