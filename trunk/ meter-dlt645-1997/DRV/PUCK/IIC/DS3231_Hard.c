
#include "DrvPub.h"

#ifndef DRV_SIMU_DS3231
/**********************************************************************************
�������ܣ�
��ڣ�
���ڣ����ڣ�1------------------��ȡ�ɹ���0----------��ȡʧ��
**********************************************************************************/   
INT8U DS3231_Read_Buf(INT8U addr,INT8U Len,INT8U *Dst)
{
 INT8U i,Flag;
 
#ifdef HARD_I2C_ENV
   if(setjmp(Hard_I2c_Env.Env)==0)
   {
#endif 
     
    IICE0=1;               //��II2C����ʱ�ӣ����п��ܻ�ر�-----------PUCK
    Flag=I2cStartCondition();	
    Flag&=I2cPutAddress(0xd0);	
    Flag&=I2cPutData(addr);
    I2cStart();
    Flag&=I2cPutData(0xd1);	 //������
    for(i=0;i<Len-1;i++)
        Flag&=I2cGetDataAckSet(Dst+i);
    Flag&=I2cGetDataNackSet(Dst+Len-1);
    I2cStopCondition();
#ifdef HARD_I2C_ENV
    return 1;
   }
   else
#else
    if(!OkFlag)
#endif
   {
      DEBUG_PRINT(PUCK,1,"IIC_Error----->Reset I2c_Hard Device!");  
      I2cReset();
   }
  return Flag;
}
/**********************************************************************************
�������ܣ�
��ڣ�
���ڣ����ڣ�1------------------д��ɹ���0----------д��ʧ��
**********************************************************************************/   
INT8U DS3231_Write_Buf(INT8U Addr,INT8U Len,INT8U *Src)
{
  INT8U i,Flag;
  IICE0=1;               //��II2C����ʱ�ӣ����п��ܻ�ر�-----------PUCK
  Flag=I2cStartCondition();	
  Flag&=I2cPutAddress(0xd0);	
  Flag&=I2cPutData(Addr);
  for(i=0;i<Len;i++)
    Flag&=I2cPutData(Src[i]);
  I2cStopCondition();
  if(!OkFlag)
  {
    DEBUG_PRINT(PUCK,1,"IIC_Error----->Reset I2c_Hard Device!");  
    I2cReset();
  }
  return Flag;
}
#endif
