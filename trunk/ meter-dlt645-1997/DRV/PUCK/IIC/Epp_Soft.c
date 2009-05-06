#include "DrvPub.h"


//�����һ·IC epprom
#ifdef ID_MEM_IIC_CAL
/**********************************************************************************/
/**********************************************************************************/ 
void Set_Cal_Sclk_Dir(INT8U Dir)
{
  if(Dir==DIR_OUTPUT)
    SET_CAL_SCLK_OUTPUT;
  else
    SET_CAL_SCLK_INPUT;  
}
/**********************************************************************************
**********************************************************************************/ 
void Set_Cal_Sda_Dir(INT8U Dir)
{
  if(Dir==DIR_OUTPUT)
    SET_CAL_SDA_OUTPUT;
  else
    SET_CAL_SDA_INPUT; 
}
/**********************************************************************************
**********************************************************************************/ 
void Set_Cal_Sclk_Pin(INT8U Level)
{
  if(Level)
    SET_CAL_SCLK_1; 
  else
    CLR_CAL_SCLK_0; 
}
/**********************************************************************************
**********************************************************************************/ 
void Set_Cal_Sda_Pin(INT8U Level)
{
  if(Level)
    SET_CAL_SDA_1; 
  else
    CLR_CAL_SDA_0; 
}
/**********************************************************************************
**********************************************************************************/ 
INT8U Get_Cal_Sda_Pin(void)
{
  return (GET_CAL_STATUS);  
}
#endif


#ifdef I2C_SOFT_EPP_EN
#pragma pack(1)
typedef struct
{ 
  INT8U   EppType:5;
  INT8U   Single:1;
  INT8U   BitFill:2;
  INT16U  PageSize;               //ҳ���ֽ���
  INT32U  MaxSize;                //IC����ֽ���
  INT8U   PageDlyFlg:1;           //дҳ����ʱ��־
  INT8U   PageDelay:7;            //��ҳ����ʱʱ�䣺ms
}CONST_EPPROM_SOFT;

#define MAX_EPPROM_TYPE  (M24256+1)

CONST CONST_EPPROM_SOFT  Const_Epprom_Soft[MAX_EPPROM_TYPE]={
  {M2401,1,0,8,EPP_2401_SIZE,0,0},
  {M2402,1,0,8,EPP_2402_SIZE,0,0},
  {M2404,1,1,16,EPP_2404_SIZE,1,8},
  {M2408,1,2,16,EPP_2408_SIZE,0,0},
  {M2416,1,3,16,EPP_24016_SIZE,0,0},
  {M2432,0,0,32,EPP_24032_SIZE,0,0},
  {M2464,0,0,32,EPP_24064_SIZE,0,1},
  {M24128,0,0,64,EPP_240128_SIZE,0,0},
  {M24256,0,0,64,EPP_240256_SIZE,1,8}
};
#pragma pack()


/**********************************************************************************
��ַ���У���������ַ�����ֽڵ�ַ(��ѡ)�����ֽڵ�ַ
24C01/2:  1 0 1 0 A2  A1 A0 R/W
24C04:    1 0 1 0 A2  A1 a8 R/W        ������ַ�����˸ߵ�ַ��a8��      2^8=256�� ʵ�ʽ�512�ֽڷ�Ϊ2��ҳ��ÿ��ҳ256�ֽ�
24C08:    1 0 1 0 A2  a9 a8 R/W        ������ַ�����˸ߵ�ַ��a9a8��    2^10=1024��ʵ�ʽ�1024�ֽ�Ϊ4��ҳ��ÿ��ҳ256�ֽ�
24C16:    1 0 1 0 a10 a9 a8 R/W        ������ַ�����˸ߵ�ַ��a10a9a8�� 2^11=2048��ʵ�ʽ�2048�ֽ�Ϊ8��ҳ��ÿ��ҳ256�ֽ�
24C32��24C256��   1 0 1 0 A2 A1 A0 R/W +AddrH+AddrL

**********************************************************************************/

/**********************************************************************************
�������ܣ�
��ڣ�
���ڣ�1----------------�ɹ���0----------------ʧ��
**********************************************************************************/   
INT8U Write_Soft_EEPROM(INT8U VirtualID,INT8U SlvAdr,INT16U SubAddr,INT16U size,INT8U Type,INT8U *Src)
{
    INT16U WrNum;
    INT16U Page;
    INT8U AddrH,AddrL;
    INT8U OkFlag;
    
    if(Type>MAX_EPPROM_TYPE)                           return 0;
    if(size>Const_Epprom_Soft[Type].MaxSize)           return 0;
    if(SubAddr>Const_Epprom_Soft[Type].MaxSize)        return 0;        
    if((size+SubAddr)>Const_Epprom_Soft[Type].MaxSize) return 0;  
    
#ifdef SOFT_I2c_ENV
    if(setjmp(Soft_I2c_Env.Env)==0)
    {
#endif     
    //-------------------------------------------------IIC_HARD_WP_EN;       //����д����
    WAITFOR_DRV_CYCLE_TIMEOUT(100);
    WrNum=0;
    AddrH=(INT8U)(SubAddr/256);
    AddrL=(INT8U)(SubAddr%256);
    do{
        OkFlag=I2cSoft_Start(VirtualID);	
        Page=AddrL+WrNum; 
        if(Const_Epprom_Soft[Type].Single) //��ַΪһ���ֽڵ�����------PUCK
        {
          if(Const_Epprom_Soft[Type].BitFill==0) //��������ַ�ǹ̶���
            I2cSoft_Send_Byte(VirtualID,SlvAdr);
         else                                 //��������ַ���ݸ��ֽ��޸�
          { 
            if(Const_Epprom_Soft[Type].BitFill>=((SubAddr+WrNum)/256))  //��ǰ����ҳ��>=������ҳ�ţ���������
              OkFlag&=I2cSoft_Send_Byte(VirtualID,SlvAdr|Get_Modi_Value(((SubAddr+WrNum)/256)));   //��������ַ�޸ģ����·�
          }  
        }
        else
        {
          OkFlag&=I2cSoft_Send_Byte(VirtualID,SlvAdr); 
          OkFlag&=I2cSoft_Send_Byte(VirtualID,AddrH+(Page>>8));      
        }       
        
        OkFlag&=I2cSoft_Send_Byte(VirtualID,(Page&0x00FF)) ;	
        do
        {
           OkFlag&=I2cSoft_Send_Byte(VirtualID,*Src); 					
           Src++;WrNum++;
        }while((WrNum<size)&&(((AddrL+WrNum)&(Const_Epprom_Soft[Type].PageSize-1))!=0));
        
        OkFlag&=I2cSoft_Stop(VirtualID);
        if(Const_Epprom_Soft[Type].PageDlyFlg)
          WAITFOR_DRV_MS_TIMEOUT(Const_Epprom_Soft[Type].PageDelay)
        else
          WAITFOR_DRV_CYCLE_TIMEOUT(100)  //û����ʱ��־����ʱ100��nop
        }while(WrNum<size);
        //-------------------------------------------------IIC_HARD_WP_DIS;     //��WP����Ϊ�ߣ���ֹд--------PUCK
#ifdef SOFT_I2c_ENV
    return 1;
    }
   else
#else
   if(!OkFlag)
#endif
   {
      //-------------------------------------------------IIC_HARD_WP_DIS;     //��WP����Ϊ�ߣ���ֹд--------PUCK
      I2cSoft_Reset(VirtualID);
      OkFlag=0;
   }
    return OkFlag;
}


/**********************************************************************************
�������ܣ�iic�����϶�����:8bits,������ACK��Ӧ�����һ�ֽڣ�����NACK��Ӧ
��ڣ�
���ڣ�1-------------�ɹ���0----------ʧ��
**********************************************************************************/ 
INT8U I2cSoft_Read_nByteS(INT8U Id,INT16U Len,INT8U *Dst)
{
  INT8U i,OkFlag;
  OkFlag=1;
  for(i=0;i<Len-1;i++)           //ǰLen�ֽڣ����գ���ACK��Ӧ
  {
      OkFlag&=I2cSoft_Read_Byte(Id,Dst+i);
      OkFlag&=I2cSoft_Send_N_Ack(Id,0);
  }   
  OkFlag&=I2cSoft_Read_Byte(Id,Dst+Len-1);  //���1�ֽڣ����գ���NACK��Ӧ
  OkFlag&=I2cSoft_Send_N_Ack(Id,1);
  return OkFlag;
}

/**********************************************************************************
�������ܣ�
��ڣ�
���ڣ�1----------------�ɹ���0----------------ʧ��
**********************************************************************************/
INT8U Read_Soft_2Addrs_EEPROM(INT8U VirtualID,INT8U SlvAdr,INT16U SubAddr,INT8U Type,INT16U size,INT8U *Dst)
 {
   INT8U AddrL,OkFlag;
  
   AddrL=(INT8U)(SubAddr%256);
#ifdef SOFT_I2c_ENV
   if(setjmp(Soft_I2c_Env.Env)==0)
   { 
#endif   

   WAITFOR_DRV_CYCLE_TIMEOUT(50);
   OkFlag=I2cSoft_Start(VirtualID);
   OkFlag&=I2cSoft_Send_Byte(VirtualID,SlvAdr);
   OkFlag&=I2cSoft_Send_Byte(VirtualID,AddrL);
   OkFlag&=I2cSoft_Start(VirtualID);	   //������ʼ����------------PUCK
   OkFlag&=I2cSoft_Send_Byte(VirtualID,SlvAdr|0x1);  //������-----------PUCK
   OkFlag&=I2cSoft_Read_nByteS(VirtualID,size,Dst);
   OkFlag&=I2cSoft_Stop(VirtualID);
#ifdef SOFT_I2c_ENV
    return 1;
   }
   else
#else
    if(!OkFlag)
#endif
  {
     I2cSoft_Reset(VirtualID);
     OkFlag=0;
   }
   return OkFlag;
}

/**********************************************************************************
�������ܣ�
��ڣ�
���ڣ�1----------------�ɹ���0----------------ʧ��
**********************************************************************************/
INT8U Read_Soft_3Addrs_EEPROM(INT8U VirtualID,INT8U SlvAdr,INT16U SubAddr,INT8U Type,INT16U size,INT8U *Dst)
{
    INT8U AddrH,AddrL,OkFlag;
     
    AddrH=(INT8U)(SubAddr/256);
    AddrL=(INT8U)(SubAddr%256);
  
#ifdef SOFT_I2c_ENV
   if(setjmp(Soft_I2c_Env.Env)==0)
   { 
#endif    
    
    WAITFOR_DRV_CYCLE_TIMEOUT(50);
    OkFlag=I2cSoft_Start(VirtualID);
    OkFlag&=I2cSoft_Send_Byte(VirtualID,SlvAdr);
    
    if(Const_Epprom_Soft[Type].Single==0) 
      OkFlag&=I2cSoft_Send_Byte(VirtualID,AddrH);
     
    OkFlag&=I2cSoft_Send_Byte(VirtualID,AddrL);
    I2cStart();   //������ʼ����------------PUCK
    OkFlag&=I2cSoft_Send_Byte(VirtualID,SlvAdr+1);  //������-----------PUCK
    OkFlag&=I2cSoft_Read_nByteS(VirtualID,size,Dst);
    OkFlag&=I2cSoft_Stop(VirtualID);
#ifdef SOFT_I2c_ENV
    return 1;
   }
   else
#else
    if(!OkFlag)
#endif
    {
      I2cSoft_Reset(VirtualID);
      OkFlag=0;
    }
    return OkFlag;
}

/**********************************************************************************
�������ܣ�
��ڣ�
���ڣ�1----------------�ɹ���0----------------ʧ��
**********************************************************************************/
INT8U Read_Soft_EEPROM(INT8U VirtualID,INT8U SlvAdr,INT16U SubAddr,INT8U Type,INT16U size,INT8U *Dst)
{
    INT8U Flag;

  
   if(Type>MAX_EPPROM_TYPE)                              return 0;
   if(size>Const_Epprom_Soft[Type].MaxSize)          return 0;
   if(SubAddr>Const_Epprom_Soft[Type].MaxSize)        return 0;        
   if((size+SubAddr)>Const_Epprom_Soft[Type].MaxSize) return 0;  
   
   //��������ַ����ݶ��ĸ��ֽڵ�ַ�������޸�
   if((Const_Epprom_Soft[Type].Single)&&(Const_Epprom_Soft[Type].BitFill))  //Ŀǰֻʵ��M2404(��256��2��ҳ),M2408/M2416δʵ��----------PUCK
   {
     if(SubAddr+size<256) //��һҳ����ͷ
     {
       Flag=Read_Soft_2Addrs_EEPROM(VirtualID,SlvAdr,SubAddr,Type,size,Dst);
       return Flag;
     }
     else if(SubAddr>=256) //�ڶ�ҳ����ͷ
     {
       SlvAdr|=0x20;
       Flag=Read_Soft_2Addrs_EEPROM(VirtualID,SlvAdr,SubAddr,Type,size,Dst);
       return Flag;
     }
     else
     {
       Flag=Read_Soft_2Addrs_EEPROM(VirtualID,SlvAdr,SubAddr,Type,256-SubAddr,Dst);
       Flag&=Read_Soft_2Addrs_EEPROM(VirtualID,SlvAdr|0x20,256,Type,size-256+SubAddr,Dst+256-SubAddr);
       return Flag;
     }
   }
   else  //��������ַ�����������޸�
     Flag=Read_Soft_3Addrs_EEPROM(VirtualID,SlvAdr,SubAddr,Type,size,Dst);
  
     return Flag; 
}

#endif