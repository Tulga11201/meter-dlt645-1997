#define AUTHORITY_C
#include "Includes.h"

//extern const S_Protocol_Data_Info Protocol_Data[];
//������ڲ��������Ƿ�������
INT8U Check_Meter_Factory_Status()
{
  if(Get_Meter_Hard_Mode()!=MODE_FAC)
    return 0;  //�ǹ���״̬
  else
    return 1;  //����״̬  
}

//����Ƿ��ܷ����������Ϣ
INT8U Check_Debug_En()
{
  if(Get_Meter_Hard_Mode()==MODE_RUN)
    return 0;
  else
    return 1;
}

//������Ƿ��ڱ��״̬���ǵķ���1�����򷵻�0
INT8U Check_Meter_Prog_Status()
{
  //return 1;//test
  return Check_Prog_Status();
}

//�������ͨ�ŵ�ַ�İ����Ƿ��£����·���1�����򷵻�0
INT8U Check_Set_ADDR_Key()
{
  return Check_MeterAddr_Status();
}

//���������ݵ�Ȩ��,Ҫ���ڹ���״̬���߱��״̬��Ȩ�ޱ�־
INT8U Check_Clear_Data_Authority()
{
  if((Check_Meter_Prog_Status()==0 && Check_Meter_Factory_Status()==0) ||\
     CHECK_STRUCT_VAR(User_Authority_Flag)==0 ||\
     CHECK_STRUCT_SUM(User_Authority_Flag)==0 ||\
    User_Authority_Flag.Flag!=AUTHORITY_FLAG)
    return 0;
  else
    return 1;
  
}

//������������Ϣ
void Clear_PSW_Err_Info()
{
  mem_set((void *)&PSW_Err_Info,0,sizeof(PSW_Err_Info),(void *)&PSW_Err_Info,sizeof(PSW_Err_Info));
  INIT_STRUCT_VAR(PSW_Err_Info);
  SET_STRUCT_SUM(PSW_Err_Info);
}

//��ȡ��ǰ���û�Ȩ��,Ҳ��������,������͵����ݲ���Ҫ���룬��ֱ�ӷ���Ȩ��PSW_0
INT8U Get_User_Authority(INT8U Ctrl_Code,INT8U *pSrc,INT8U SrcLen,INT8U *pErr)
{
  INT8U Posi;//���������ݻ����е���ʼλ��
  INT8U Level;//��ǰ���뼶��
 
  *pErr=NO_ERR;
  
  //��ʱ���� test
  if(Check_Meter_Factory_Status())//�������������ˣ��߱�����Ȩ��
    return PSW_FACTORY;
  
  if(PSW_Err_Info.Set_En_Mins>0)//��Ȩ�޿��ŵ�ʱ������Ϊ�û��߱�0��Ȩ��
    return PSW_0;
  
//���¶�û�����ϱ�������  
  if(Ctrl_Code==C_READ_DATA || Ctrl_Code==C_READ_FOLLOW_DATA)
  {
    return PSW_0;//����Ҫ���������£���Ϊ�߱���0������
  }
  else if(Ctrl_Code==C_SET_DATA)//д����
  {
    if(Check_Meter_Prog_Status()==0)//û�д��ڱ��״̬�����߱��κ�дȨ��
    {
      *pErr=PROTOCOL_AUTH_ERR;
      return PSW_NULL;
    }
    Level=pSrc[2];//���뼶��
    Posi=3;//���뿪ʼλ��
  }
  else if(Ctrl_Code==C_ADJUST_METER)//У��,У������ڹ���״̬
  {
    *pErr=PROTOCOL_AUTH_ERR;
    return PSW_NULL;//��ʱû�д�������״̬
  }
  else if(Ctrl_Code==C_ADJUST_TIME)//Զ��Уʱ
  {
    if(Mode_Word.Mode[0].Bit.Bit4==1)//��Ҫ���룿
    {
      Level=pSrc[0];//���뼶��
      Posi=1;//������ʼλ��
    }
    else
    {
      return PSW_0;//����Ҫ���������£���Ϊ�߱���0������
    }
  }
  else if(Ctrl_Code==C_SET_ADDR)//���ñ��ַ����Ҫ����Ȩ�ޣ�ֻ��Ҫ����ĳ������
  {
    if(Check_Set_ADDR_Key()==0)//����û�а��£�����Ȩ�޴�
    {
      *pErr=PROTOCOL_AUTH_ERR;
      return PSW_NULL;
    }
    else 
      return PSW_0;//����Ҫ���������£���Ϊ�߱���0������
  }
  else if(Ctrl_Code==C_SET_COM_BAUD)//����ͨ�Ų�����
  {
    return PSW_0;//����Ҫ����
  }
  else if(Ctrl_Code==C_SET_PSW)//�޸�����
  { 
    if(Check_Meter_Prog_Status()==0)//û�д��ڱ��״̬�����߱��κ�дȨ��
    {
      *pErr=PROTOCOL_AUTH_ERR;
      return PSW_NULL;
    }
    
    Level=pSrc[0];//�������0�ֽھ������뼶��
    Posi=1;    
  }
  else if((Ctrl_Code==C_CLR_ALL && 4==SrcLen) || Ctrl_Code==C_CLR_DEMAND ||\
          Ctrl_Code==C_CLR_EVENT || Ctrl_Code==C_CLR_STAT)
  {
    if(Check_Meter_Prog_Status()==0)//û�д��ڱ��״̬�����߱��κ�дȨ��
    {
      *pErr=PROTOCOL_AUTH_ERR;
      return PSW_NULL;
    }
    
    Level=pSrc[0];
    Posi=1;         
  }
  else if(Ctrl_Code==C_CLR_ALL && 3==SrcLen)
  {
    if(*pSrc==(0x36-0x33) || *pSrc==(0x46-0x33))//���ݳ���Ϊ4�����壬����3�Ƕ���
      return PSW_0;//��������
  }
  else
  {
    *pErr=PROTOCOL_AUTH_ERR;   
    return PSW_NULL;
  }
  //���뼶����0-2֮�������ȷ��
  if(Level>2)
  {
    *pErr=PROTOCOL_PSW_ERR;//�������
    return PSW_NULL;
  }
  
  //�Ƚ������Ƿ���ͬ
  if(memcmp(pSrc+Posi,(void *)Cur_PSW.PSW[Level],3)!=0)
  {
    *pErr=PROTOCOL_PSW_ERR;//�������
    return PSW_NULL;
  }
  
  if(Level==0)
    return PSW_0;
  else if(Level==1)
    return PSW_1;
  else
    return PSW_2;    
}

//����޸�ĳ��������Ҫ��Ȩ��
INT8U Get_Protocol_Data_Authority(INT8U Ch,INT8U Ctrl_Code,INT8U *pSrc,INT8U SrcLen)//INT16U DI)
{
  INT8U i,PSW_Flag,Posi;
  INT16U DI;
  
  //�Ȼ��������ݵ�������
  if(Ctrl_Code==C_READ_DATA || Ctrl_Code==C_READ_FOLLOW_DATA)
  {
    return PSW_3;//��ȡ���ݺͺ������ݲ���Ҫ���룬���Ĭ�Ϸ�������3,��͵ȼ�
  }
  else//���¶���д�������
  {
    /*
    Ch=CHANEL_485;//����
    if(CHANEL_MOUDEL==Ch)//ģʽ��1��bit3�Ƿ�����Ӵ���2�������0��ʾ������
    {
      if(Ctrl_Code!=C_ADJUST_TIME && 0==Mode_Word.Mode[0].Bit.Bit3)
        return PSW_NULL;     
    }
    */
    
    if(Ctrl_Code==C_SET_DATA)
    {
       DI=0;
       mem_cpy(&DI,pSrc,2,&DI,sizeof(DI));//DI=*(INT16U *)pSrc;
       PSW_Flag=Get_Protocol_Data_PSW_Flag(DI);
       
       //û���ҵ���������Ӧ��������
       if(ASSERT(A_WARNING,PSW_Flag!=PSW_NULL_FLAG && PSW_Flag!=PSW_RD_ONLY))
         return PSW_NULL;
       
       //���������Ϊ����,ֱ�ӷ���PSW_SUPPER
       if(PSW_Flag==PSW_FACTORY_STATUS)
         return PSW_FACTORY;
      
       //��PSW_Map����Ѱ�Ҹ����ݵ�����������״̬���е�λ��
       Posi=0xFF;
       for(i=0;i<S_NUM(PSW_Map);i++)
       {
         if(PSW_Map[i].PSW_Flag==PSW_Flag)
         {
           Posi=PSW_Map[i].Posi;
           break;
         }
       }
       if(ASSERT(A_WARNING,Posi<15))//��ʱPosi==0xFF,��ʾû���ҵ�λ��
         return PSW_NULL;
    }
    else if(Ctrl_Code==C_ADJUST_METER)//У��
    {
      /*
      if(Mode_Word.Mode[0].Bit.Bit2==0)//����������ϱ�,����Ҫ�ڹ���״̬
        return PSW_FACTORY;//��Ҫ��������,�������������ϣ�ͬʱ���ڱ��״̬
      else
        Posi=14;//����������߱���Ҫͬ����Ȩ��?�Ǵ�Posi?�˴�����
      */
      return PSW_FACTORY;//��Ҫ��������,�������������ϣ�ͬʱ���ڱ��״̬
    }
    else if(Ctrl_Code==C_ADJUST_TIME)//�㲥Уʱ
    {
      if(Mode_Word.Mode[0].Bit.Bit4==1)//��Ҫ���룿
        Posi=0x04;
      else
        return PSW_3;//��Ϊ����Ҫ���룬���Ը���һ����ͼ�����(���ж��û�����ʱ���һ���ϸ߼�����) 
    }
    else if(Ctrl_Code==C_SET_ADDR)
    {
      return PSW_3; //����ַ����Ϊ����Ҫ���룬���Ը���һ����ͼ�����(���ж��û�����ʱ���һ���ϸ߼�����) 
    }
    else if(Ctrl_Code==C_SET_COM_BAUD)
    {
      return PSW_3; //�貨���ʣ���Ϊ����Ҫ���룬���Ը���һ����ͼ�����     
    }
    else if(Ctrl_Code==C_SET_PSW)
    {
      if(pSrc[4]==0)//���õ����뼶��
        Posi=0x07; //������Ȩ�޿������е�λ��
      else if(pSrc[4]==1)
        Posi=0x06;
      else if(pSrc[4]==2)
        Posi=0x05;
      else
        return PSW_NULL;//���������Ȩ�� 
      
      if(pSrc[0]>pSrc[4])//����û�Ȩ�ޱ����õ�����Ȩ�޵ͣ���ȻҲ��������
        return PSW_NULL;
    }
    else if(Ctrl_Code==C_CLR_ALL)//����
    {
      if(SrcLen==4)//Դ����4�ֽ�������
      {
        if(Mode_Word.Mode[0].Bit.Bit2==0)//������������壬����Ҫ�ڹ���״̬
          return PSW_FACTORY;
        else
          Posi=14;
      }
      else//Դ����3�ֽ��Ƕ�������,����Ҫ������������Ը���һ����ͼ�������Ҫ��
        return PSW_3;
    }
    else if(Ctrl_Code==C_CLR_DEMAND || Ctrl_Code==C_CLR_EVENT || Ctrl_Code==C_CLR_STAT)
    {
      Posi=13;
    }
    else 
      return PSW_NULL;
  }
  
 //�ҵ��ļ�����Ȩ�޿������������˸��������Ȩ��
 for(i=3;i>=1;i--)
 {
   if(GET_BIT(User_Authority_Ctrl.PSW[i-1],Posi))
   {
     if(i==1)
       return PSW_0;
     else if(i==2)
       return PSW_1;
     else if(i==3)
       return PSW_2;
   }
 }
 return PSW_0;//���0-2������Ȩ�޶�û�����ø����Ĭ��Ϊ0���������
}
#undef AUTHORITY_C
