#ifndef DRV_CFG_H
#define DRV_CFG_H



#ifndef DRV_PUB
#define DRV_PUB_EXT  extern
#else
#define DRV_PUB_EXT 
#endif



#include "includes.h"

#include "DrvCfg.h"
#include "TAU.h"
#include "Int.h"
#include "LVI.h"

#include "CPUPub.h"
#include "Epp_Soft.h"
#include "IIC0_Hard.h"
#include "I2C_Soft.h"
#include "Epp_Hard.h"
#include "DS3231_soft.h"
#include "App_Epp_All.h"
#include "ICcardDrv.h"


#define DIR_OUTPUT  0
#define DIR_INPUT   1

DRV_PUB_EXT volatile INT32U Timeout_Ms_Timer;
DRV_PUB_EXT volatile INT8U  Timeout_Ms_Num;

//��������Ϊ�������ĳ�ʱ��conditionΪ1����mstimeout��ʱ�����˳�,mstimeout�ڲ��޶��� OS_MS_PER_TICK��
#define  IF_WAITFOR_DRV_MS_CONDITION(Condition,MsTimeout) \
do{\
    if(Condition)  break;   \
    if(MsTimeout>OS_MS_PER_TICK) Timeout_Ms_Num=OS_MS_PER_TICK; else Timeout_Ms_Num=MsTimeout+1;\
      Timeout_Ms_Timer=Ms_Timer_Pub;\
    while((Timeout_Ms_Num)&&(!(Condition)))\
     if(Timeout_Ms_Timer!=Ms_Timer_Pub) {Timeout_Ms_Num--; Timeout_Ms_Timer=Ms_Timer_Pub;} \
}while(0);\
if(!(Condition))    //����ж��Ƿ�ʱ��1��ʾ�Ѿ���ʱ,0��ʾ����������û�г�ʱ


//������������ʱ��,��ڣ�ms���ڲ���Χ�޶���[1,OS_MS_PER_TICK]
#define  WAITFOR_DRV_MS_TIMEOUT(MsTimeout) {IF_WAITFOR_DRV_MS_CONDITION(0,MsTimeout);}
    


#define  CYCLE_NUM_IN_1MS     12000 //����һ��ms�� nop�ĸ���
DRV_PUB_EXT volatile INT32U  Timeout_Cycle_Num;
//��������Ϊ�������ĳ�ʱ��conditionΪ1����nop�������������˳�
#define  IF_WAITFOR_DRV_CYCLE_CONDITION(Condition,cycle) \
do{\
    if(Condition)  break;   \
    if(cycle>CYCLE_NUM_IN_1MS) Timeout_Cycle_Num=CYCLE_NUM_IN_1MS/4; else if(cycle<=4) Timeout_Cycle_Num=1; else Timeout_Cycle_Num=cycle/4;\
      while((Timeout_Cycle_Num)&&(!(Condition)))    Timeout_Cycle_Num--;\
}while(0);\
if(!(Condition))    //����ж��Ƿ�ʱ��1��ʾ�Ѿ���ʱ,0��ʾ����������û�г�ʱ

//����������nop��ʱ��,��ڣ�nop�������ڲ���Χ�޶���[4,CYCLE_NUM_IN_1MS]
#define  WAITFOR_DRV_CYCLE_TIMEOUT(cycle) {IF_WAITFOR_DRV_CYCLE_CONDITION(0,cycle);}


void Read_DS3231(INT8U *src);
INT8U Write_DS3231(INT8U *src);
void Drv_WaitFor_TimeOut(INT32U MsTimeout);
void Init_IIC_Soft(void);
void Init_DS3231_IIC_Soft(void);
void Init_U27_IIC_Soft(void);
void Close_DS3231_IIC_Soft(void);
void Close_U27_IIC_Soft(void);
#endif
