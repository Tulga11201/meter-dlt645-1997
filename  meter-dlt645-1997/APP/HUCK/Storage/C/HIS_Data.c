#define HIS_DATA_C
#include <includes.h>

//������ʷ�������������͵�ѹͳ�����ݵĴ洢DI
//��Ϊһ�㶼�Ǵ洢��N�µ����ݣ����Դ洢�������Ǹ������������ɵ�
STORA_DI Calc_HIS_Data_DI(INT8U Data_Flag,S_HEX_Time *pTime)
{
  INT8U Re;
  STORA_DI DI;
 
  if(ASSERT(A_WARNING,HIS_ENERGY_DATA==Data_Flag ||\
            HIS_DEMAND_DATA==Data_Flag ||\
            HIS_VOLSTAT_DATA==Data_Flag))
    return NULL_4BYTES;
  
  Re=Check_HEX_Time(pTime);
  if(ASSERT(A_WARNING,Re!=0))
    return NULL_4BYTES;    
  
  //����������������ݵ�Index
  if(HIS_ENERGY_DATA==Data_Flag)
  {
    DI=HIS_ENERGY+(pTime->Time[T_MONTH]+(pTime->Time[T_YEAR])*12)%HIS_ENERGY_DATA_MONTHS;
  }
  else if(HIS_DEMAND_DATA==Data_Flag)
  {
    DI=HIS_DEMAND+(pTime->Time[T_MONTH]+(pTime->Time[T_YEAR])*12)%HIS_DEMAND_DATA_MONTHS;
  }
  else if(HIS_VOLSTAT_DATA==Data_Flag)
  {
    DI=HIS_VOLSTAT+(pTime->Time[T_MONTH]+(pTime->Time[T_YEAR])*12)%HIS_VOLSTAT_DATA_MONTHS;  
  }
  else
  {
    return NULL_4BYTES;
  }
  return DI;
}

//��ȡǰ�����µ���ʷ���ݵ�DI
//Data_Flag���ݱ�־
//HIS_ENERGY_DATA;
//HIS_DEMAND_DATA;
//HIS_VOLSTAT_DATA;
//Bef_Monthǰ������
//�������ݵĴ洢DI
STORA_DI Calc_HIS_Data_DI_Bef_Month(INT8U Data_Flag,INT8U Bef_Month)
{
  S_HEX_Time Temp_Time;
  Time_Dec((S_HEX_Time *)&Cur_Time0,Bef_Month,UNIT_MON,(S_HEX_Time *)&Temp_Time);//��ʱ����ǰ����Bef_Mon����
  return Calc_HIS_Data_DI(Data_Flag,&Temp_Time);
}

//����ʷ������ѹͳ�Ƶ�����,������ʷ������Read_Demand_HIS_Data�����е�������
//pTime��������ѹͳ�Ƶ����ݵĴ洢ʱ��
//pDst������Ŀ�껺����
//pDst_Start��DstLenһ���޶�pDst�ͷ��س��ȵķ�Χ
//pErr�����־��
//���ض�ȡ�������ݳ���
//������Ϊ0�ǣ�*pErr��ʾ����ԭ��
INT16U Read_HIS_Data(INT8U Data_Flag,S_HEX_Time *pTime,void *pDst,void *pDst_Start,INT16U DstLen,INT8U *pErr)
{
  INT8U *p;
  INT16U Len;
  STORA_DI DI;
 
  DEBUG_PRINT(HUCK,DEBUG_0,"Read_HIS_Data Time:");
  Debug_Print_HEX_Time(pTime->Time);
  DI=Calc_HIS_Data_DI(Data_Flag,pTime);
  if(ASSERT(A_WARNING,NULL_4BYTES!=DI))
  {
    *pErr=RD_HIS_DATA_DI_ERR;
    return 0; 
  }

  Len=Get_Storage_Data_Len(DI); //���ݳ���
  //���ݳ��ȱ��������ڲ����涨��Χ��
  if(ASSERT(A_WARNING,0!=Len && (INT8U *)pDst>=(INT8U *)pDst_Start && (INT8U *)pDst+Len<=(INT8U *)pDst_Start+DstLen))
  {
    *pErr=RD_HIS_DATA_LEN_ERR;
    return 0;    
  }
  //��������
  if(Read_Storage_Data(DI,pDst,pDst_Start,DstLen,pErr)!=Len)
  {
    *pErr=RD_HIS_DATA_LEN_ERR;
    return 0;        
  }

  if(NO_ERR==*pErr)
  {
    if(HIS_ENERGY_DATA==Data_Flag)
      p=(((S_Energy *)pDst)->Time).Time;
    //else if(HIS_DEMAND==DI)
      //p=((S_Demand *)pDst)->Time;
    else if(HIS_VOLSTAT_DATA==Data_Flag)
      p=(((S_VolStat *)pDst)->Time).Time;
    else
    {
      *pErr=RD_HIS_DATA_DI_ERR;
      return 0;
    }
    //�Ƚ�ʱ���Ƿ�����Ҫ��ʱ��,�ա��¡��궼��ȣ���Ϊʱ�����
    //if(p[T_DATE]==pTime->Time[T_DATE] &&
     if(p[T_MONTH]==pTime->Time[T_MONTH] &&
        p[T_YEAR]==pTime->Time[T_YEAR])
      return Len;
    else 
    {
      *pErr=RD_HIS_DATA_TIME_ERR;
      return 0;
    }
  }
  else
  {
    ASSERT(A_WARNING,0);
    return 0;
  }
}


//д��ʷ������ѹͳ�Ƶ�����,д������ʷ��������Write_Demand_HIS_Data�����е������� 
//pTime��������ѹͳ�Ƶ����ݵĴ洢ʱ��
//pSrcд���ݻ�����
//SrcLen���ݳ���
//����ֵ
//����NO_ERR��ʾд�ɹ�
INT8U Write_HIS_Data(INT8U Data_Flag,S_HEX_Time *pTime,void *pSrc,INT16U SrcLen)
{
  //INT8U Index;
  INT8U Re;
  INT16U Len;
  STORA_DI DI;
 
  DI=Calc_HIS_Data_DI(Data_Flag,pTime);
  if(ASSERT(A_WARNING,NULL_4BYTES!=DI))
    return WR_HIS_DATA_DI_ERR;

  Len=Get_Storage_Data_Len(DI); //���ݳ���
  //���ݳ��ȱ��������ڲ����涨��Χ��
  if(ASSERT(A_WARNING,Len==SrcLen))
    return WR_HIS_DATA_LEN_ERR;    
 
  //д�洢����
  Re=Write_Storage_Data(DI,pSrc,Len);
  if(ASSERT(A_WARNING,NO_ERR==Re))//д������
    return Re;
  else
    return NO_ERR;
}

//����ʷ������������
//Rate ��Ҫ��ȡ�����ĸ����ʵ���������
//pTime�������������ݵĴ洢ʱ��
//pDst������Ŀ�껺����
//pDst_Start��DstLenһ���޶�pDst�ͷ��س��ȵķ�Χ
//pErr�����־��
//���ض�ȡ�������ݳ���
//������Ϊ0�ǣ�*pErr��ʾ����ԭ��
INT16U Read_Demand_HIS_Data(INT8U Rate,S_HEX_Time *pTime,void *pDst,void *pDst_Start,INT16U DstLen,INT8U *pErr)
{
  STORA_DI DI;
  INT32U Off;

  //�жϸ��������ݵķ��ʵĺϷ���
  if(ASSERT(A_WARNING,Rate<=Multi_Rate_Para.Rates && Rate<=MAX_RATES))
  {
    *pErr=RD_HIS_DATA_DATA_ERR;
    return 0;
  }
  //������ʷ���ݵ�DI
  DI=Calc_HIS_Data_DI(HIS_DEMAND_DATA,pTime);
  if(ASSERT(A_WARNING,NULL_4BYTES!=DI))
  {
    *pErr=RD_HIS_DATA_DI_ERR;
    return 0;
  }

  //��������
  Off=DEMAND_RATE_OFF(Rate);
  if(Read_Storage_Data_Fix_Len(DI,Off,ONE_DEMAND_SAVE_SIZE,pDst,pDst_Start,DstLen,pErr)!=ONE_DEMAND_SAVE_SIZE)
  {
    ASSERT(A_WARNING,0);
    *pErr=RD_HIS_DATA_LEN_ERR;
    return 0;        
  }

  //�Ƚ�ʱ���Ƿ�����Ҫ��ʱ��,�¡��궼��ȣ���Ϊʱ�����
  if((((S_One_Demand *)pDst)->Time.Time[T_MONTH]==pTime->Time[T_MONTH] &&
     (((S_One_Demand *)pDst)->Time.Time[T_YEAR]==pTime->Time[T_YEAR])))
    return ONE_DEMAND_SAVE_SIZE;
  else 
  {
    DEBUG_PRINT(HUCK,DEBUG_0,"Read Demand HIS Data Time !=:");
    Debug_Print_Time(pTime->Time);
    Debug_Print_Time(((S_One_Demand *)pDst)->Time.Time);
    *pErr=RD_HIS_DATA_TIME_ERR;
    return 0;
  }
}


//д��ʷ������������
//pTime�������������ݵĴ洢ʱ��
//pSrcд���ݻ�����
//SrcLen���ݳ���
//����ֵ
//����NO_ERR��ʾд�ɹ�
INT8U Write_Demand_HIS_Data(INT8U Rate,S_HEX_Time *pTime,void *pSrc,INT16U SrcLen)
{
  INT8U Re;
  STORA_DI DI;
  INT32U Off;

  //�жϸ��������ݵķ��ʵĺϷ���
  if(ASSERT(A_WARNING,Rate<=Multi_Rate_Para.Rates && Rate<=MAX_RATES &&\
            sizeof(S_One_Demand)==SrcLen))
  {
    return RD_HIS_DATA_DATA_ERR;
  }

  DI=Calc_HIS_Data_DI(HIS_DEMAND_DATA,pTime);
  if(ASSERT(A_WARNING,NULL_4BYTES!=DI))
    return WR_HIS_DATA_DI_ERR;

  //���ݳ��ȱ��������ڲ����涨��Χ��
  if(ASSERT(A_WARNING,ONE_DEMAND_SAVE_SIZE==SrcLen))
  {
    return WR_HIS_DATA_LEN_ERR;    
  }  
  //д�洢����,�ȼ��������ڸ�DI�ڵĴ洢ƫ��
  Off=DEMAND_RATE_OFF(Rate);
  Re=Write_Storage_Data_Fix_Len(DI,Off,pSrc,ONE_DEMAND_SAVE_SIZE);
  if(ASSERT(A_WARNING,NO_ERR==Re))//д������
    return Re;
  else
    return NO_ERR;
}
#undef HIS_DATA_C

        
