#define MEMORY_C
#include "Includes.h"

//����洢������,��ÿ������洢����дһ���ֽڽ��в���
INT8U Check_PHY_Mem()
{
  INT8U Re,i,Test[5];
  INT8U Bak;
  
  Re=NO_ERR;
  DEBUG_PRINT(HUCK,DEBUG_0,"PHY_MEM Write & Read Check Start");
  for(i=0;i<S_NUM(Sys_PHY_Mem);i++)
  {
    Read_PHY_Mem(Sys_PHY_Mem[i].MemNo,Sys_PHY_Mem[i].Mem_Size-1,Test,1,Test,1);//�Ƚ�ԭ�ֽڱ���
    Bak=Test[0];
    Test[0]=0x5A;
    Write_PHY_Mem(Sys_PHY_Mem[i].MemNo,Sys_PHY_Mem[i].Mem_Size-1,Test,1);//д������ֽ�
    Test[0]=0x00;
    Read_PHY_Mem(Sys_PHY_Mem[i].MemNo,Sys_PHY_Mem[i].Mem_Size-1,Test,1,Test,1);//���������ֽ�
    if(Test[0]!=0x5A)
    {
      DEBUG_PRINT(HUCK,DEBUG_0,"PHY Mem%d Write && Read Test failed!",Sys_PHY_Mem[i].MemNo);
      Re=PHY_MEM_ERR;
    }
    Test[0]=Bak;
    Write_PHY_Mem(Sys_PHY_Mem[i].MemNo,Sys_PHY_Mem[i].Mem_Size-1,Test,1);
  }
  
  //if(Re==NO_ERR)
    //DEBUG_PRINT(HUCK,DEBUG_0,"PHY_MEM Write & Read Test Succeed!");
  
  DEBUG_PRINT(HUCK,DEBUG_0,"PHY_MEM Write & Read Check End");
  return Re;
}

//����ڴ�ֲ��Ƿ����,��Ҫ�Ǽ���߼��洢��������洢��֮���ӳ��
//NO_ERR��ʾ���ɹ�
//MEM_MAP_ERR��ʾ���ʧ��
INT8U Check_LOG_Mem_Map()
{
  INT8U i,j,Re;
  INT32U Size;
  
  Re=NO_ERR;
  //��������ڴ����
  DEBUG_PRINT(HUCK,DEBUG_0,"----PHY_LOG_MEM Map Check Start!----");
  
  for(i=0;i<sizeof(Sys_PHY_Mem)/sizeof(S_PHY_Mem_Info);i++)
  {
    DEBUG_PRINT(HUCK,DEBUG_0,"PHY Mem %d size=%ld",i,Sys_PHY_Mem[i].Mem_Size);    
    Size=0;
    //���ÿ���߼��ڴ��Ӧ�������ڴ�ֲ��Ƿ����
    for(j=0;j<sizeof(Sys_LOG_Mem)/sizeof(S_LOG_Mem_Info);j++)
    {
       //��i���߼��ڴ�ʹ���˸������ڴ�
       if(Sys_LOG_Mem[j].PHY_Mem_Info.MemNo==Sys_PHY_Mem[i].MemNo) 
       {
         DEBUG_PRINT(HUCK,DEBUG_0,"----LOG Mem %2d Size:%5ld,Addr:%5ld-->%5ld ",\
                 Sys_LOG_Mem[j].LOG_MemNo,Sys_LOG_Mem[j].PHY_Mem_Info.Mem_Size,
                 Sys_LOG_Mem[j].PHY_Mem_Info.Mem_Addr,Sys_LOG_Mem[j].PHY_Mem_Info.Mem_Addr + Sys_LOG_Mem[j].PHY_Mem_Info.Mem_Size);
 
         //����������ڴ���ʼ��ַӦ���ڣ��ѷ���Ŀռ���
         if(Sys_LOG_Mem[j].PHY_Mem_Info.Mem_Addr != Size)//��ʼ��ַ��Ӧ���Ѿ�����ķ�Χ��
         {
           //ASSERT(A_WARNING,0);
           DEBUG_PRINT(HUCK,DEBUG_0,"LOG Mem %d Map Error",j);
           Re |= LOG_MEM_MAP_ERR;
         }
         //����������ڴ����ѷ���Ŀռ��ܺ�
         Size+=Sys_LOG_Mem[j].PHY_Mem_Info.Mem_Size;
       }     
    }
    if(Size>Sys_PHY_Mem[i].Mem_Size)//�ܵĴ�С��Ӧ�ó��������ڴ��С
    {
      DEBUG_PRINT(HUCK,DEBUG_0,"PHY Mem %d not enough space",i);
      Re |= LOG_MEM_MAP_ERR;
    }
  }
  DEBUG_PRINT(HUCK,DEBUG_0,"----PHY_LOG_MEM Map Check End!----");
  return Re;
}

//��ȡĳ���߼��洢���Ĵ�С
INT32U Get_LOG_Mem_Size(INT8U MemNo)
{
  INT8U i;

  for(i=0;i<S_NUM(Sys_LOG_Mem);i++)
  {
    if(Sys_LOG_Mem[i].LOG_MemNo==MemNo)
      return Sys_LOG_Mem[i].PHY_Mem_Info.Mem_Size;
  }
  ASSERT(A_WARNING,0);
  return 0;
  
}

//��ȡĳ������洢���Ĵ�С
INT32U Get_PHY_MEM_Size(INT8U MemNo)
{
  INT8U i;

  for(i=0;i<sizeof(Sys_PHY_Mem)/sizeof(S_PHY_Mem_Info);i++)
  {
    if(Sys_PHY_Mem[i].MemNo==MemNo)
      return Sys_PHY_Mem[i].Mem_Size;
  }
  ASSERT(A_WARNING,0);
  return 0;  
}

//������洢��������
//MemNo������洢�����
//Offset,����洢���ڵ�ƫ��
//pDst, д��Դ����
//RD_Len,��Ҫ��ȡ�����ݳ��� 
//pDst_Start,Ŀ�껺�����Ľ綨��ʼ��ַ
//DstLen��Ŀ�껺�����Ľ綨����
//���ؽ��:NO_ERR��ʾ��ȡ�ɹ�
INT16U Read_PHY_Mem(INT8U MemNo,INT32U Offset,void *pDst,INT16U RD_Len,void *pDst_Start,INT16U DstLen)
{
  INT8U i,j;
  INT8U Re;
  INT8U Head,Tail;
  
  ASSERT(A_WARNING,(INT8U *)pDst>=(INT8U *)pDst_Start && (INT8U *)pDst_Start+RD_Len<=(INT8U *)pDst_Start+DstLen);
  
  for(i=0;i<S_NUM(Sys_PHY_Mem);i++)
  {
    if(Sys_PHY_Mem[i].MemNo==MemNo)
    {
      if(Offset+RD_Len<=Sys_PHY_Mem[i].Mem_Size)
      {
        Head=*((INT8U *)pDst-1);//�ȱ���Ŀ�껺������ͷ��β,��������ж�ͷ��β�Ƿ����仯,��֤������������
        Tail=*((INT8U *)pDst+RD_Len);
        
        for(j=0;j<3;j++)
        {
          Re=Read_PHY_Mem_PUCK(MemNo,Offset,pDst,RD_Len,pDst_Start,DstLen);
          if(1==Re)
            break;
          OS_TimeDly_Ms(50);
          ASSERT(A_WARNING,0);
        }
        
        if(Head!=*((INT8U *)pDst-1) || Tail!=*((INT8U *)pDst+RD_Len))
        {
          ASSERT(A_WARNING,0);
          DEBUG_PRINT(HUCK,DEBUG_0,"Read_PHY_Mem Error,Mem_ID=%d,Offset=%d,RD_Len=%d,%s",MemNo,Offset,RD_Len,(Head!=*((INT8U *)pDst-1))?"Head Error":"Tail Error");
          DEBUG_PRINT(HUCK,DEBUG_0,"Bef_Head=0x%x,Bef_Tail=0x%x,Aft_Head=0x%x,Aft_Tail=0x%x",Head,Tail,*((INT8U *)pDst-1),*((INT8U *)pDst+RD_Len));
          DEBUG_BUF_PRINT((INT8U *)pDst+RD_Len,20,PRINT_HEX,0);
        }
        if(1==Re)
          return NO_ERR;
      }
    }
  }
  ASSERT(A_WARNING,0);
  return PHY_MEM_NO_ERR;
}

//������洢��д����
//MemNo������洢�����
//Offset,����洢���ڵ�ƫ��
//pSrc, д��Դ����
//д��Դ���ݳ���
//���ؽ��:
//NO_ERR��ʾд�ɹ�
INT8U Write_PHY_Mem(INT8U MemNo,INT32U Offset,void *pSrc,INT16U SrcLen)
{
  INT8U i;
  INT8U Re;
  INT8U Head,Tail;
  
  for(i=0;i<S_NUM(Sys_PHY_Mem);i++)
  {
    if(Sys_PHY_Mem[i].MemNo==MemNo)
    {
      if(Offset+SrcLen<=Sys_PHY_Mem[i].Mem_Size) 
      {
        Head=*((INT8U *)pSrc);//�ȱ���Դ��������ͷ��β,��������ж�ͷ��β�Ƿ����仯,��֤д�����ƻ�Դ����
        Tail=*((INT8U *)pSrc+SrcLen-1);
        Re=Write_PHY_Mem_PUCK(MemNo,Offset,pSrc,SrcLen);
        if(Head!=*((INT8U *)pSrc) || Tail!=*((INT8U *)pSrc+SrcLen-1))
        {
          ASSERT(A_WARNING,0);
          DEBUG_PRINT(HUCK,DEBUG_0,"Write_PHY_Mem Error,Mem_ID=%d,Offset=%d,SrcLen=%d,%s",MemNo,Offset,SrcLen,(Head!=*((INT8U *)pSrc))?"Head Error":"Tail Error");
          DEBUG_PRINT(HUCK,DEBUG_0,"Bef_Head=0x%x,Bef_Tail=0x%x,Aft_Head=0x%x,Aft_Tail=0x%x",Head,Tail,*(INT8U *)pSrc,*((INT8U *)pSrc+SrcLen-1));
          DEBUG_BUF_PRINT((INT8U *)pSrc,20,PRINT_HEX,0);
        }
        if(1==Re)
          return NO_ERR;
      }
    }
    
  }
  ASSERT(A_WARNING,0);
  return PHY_MEM_NO_ERR;//����洢����Ŵ�
}

//��д�洢�����е�ι��
void WR_Memory_Clear_Dog()
{
  INT8U Re; 
  static S_Int16U Clr_Dog_Counts={CHK_BYTE,0,CHK_BYTE};  
  static S_Int32U Clr_Dog_Counts0={CHK_BYTE,0,CHK_BYTE};
  static S_Int32U Clr_Dog_Counts1={CHK_BYTE,0,CHK_BYTE};
  static S_Int8U Sec={CHK_BYTE,0xFF,CHK_BYTE};
  static S_Int8U Task_ID={CHK_BYTE,0xFF,CHK_BYTE};
  
  Re=1;
  Re &= CHECK_STRUCT_VAR(Clr_Dog_Counts);
  Re &= CHECK_STRUCT_VAR(Clr_Dog_Counts0);
  Re &= CHECK_STRUCT_VAR(Clr_Dog_Counts1);
  Re &= CHECK_STRUCT_VAR(Sec);
  Re &= CHECK_STRUCT_VAR(Task_ID);
  
  if(Re!=1)
    ASSERT(A_WARNING,0);
  
  if(Get_Cur_Task_Num()==1 || CLEAR_END_FLAG!=Clear_Flag.Flag)//��ǰֻ��һ������Ҳ����ֻ���������ڽ��г�ʼ����������幷
  {
    if(Clr_Dog_Counts.Var<=MAX_INIT_CLR_DOG_COUTS)
    {
      Clr_Ext_Inter_Dog();
      Clr_Dog_Counts.Var++;
    }
    else
    {
      ASSERT(A_WARNING,0);
      Soft_Reset();
    }
  }
  else//���������Ѿ��������У���ʱ�ж�һ������ι�����ٴ�?
  {
    if(Sec.Var!=Cur_Time1.Sec)//ʱ���б仯��˵�������ó����ˣ�����������ִ��
    {
      Clr_Dog_Counts0.Var=0;
      Sec.Var=Cur_Time1.Sec;
    }
    
    Clr_Ext_Inter_Dog();    //��CPU�ⲿ���Ź� 
    Clear_Task_Dog();  
    //һ��������������д����1000�Σ�˵���Ѿ������ڶ�д��������,
    Clr_Dog_Counts0.Var++;

    if(Clr_Dog_Counts0.Var > MAX_INIT_CLR_DOG_COUTS)
    {
      ASSERT(A_WARNING,0);
      DEBUG_PRINT(HUCK,DEBUG_0,"WR_Memory_Clear_Dog Error,soft reset");
      Soft_Reset();
    }
  }
  
  //ͬһ��������������д����MAX_INIT_CLR_DOG_COUTS�Σ�˵���Ѿ�������
  if(Get_Cur_Task_ID()!=Task_ID.Var)//��ͬ������ִ�ж�д������˵��û������
  {
    Task_ID.Var=Get_Cur_Task_ID();
    Clr_Dog_Counts1.Var=0;
  }
  else
  {
    Clr_Dog_Counts1.Var++;
    if(Clr_Dog_Counts1.Var > MAX_INIT_CLR_DOG_COUTS)
    {
      ASSERT(A_WARNING,0);
      Soft_Reset();
    }
  }
}

//���߼��洢��������
//MemNo���߼��洢�����
//Offset,�߼��洢���ڵ�ƫ��
//pSrc, д��Դ����
//д��Դ���ݳ���
//���ؽ��:1��ʾд�ɹ���0��ʾдʧ��
INT16U Read_LOG_Mem(INT8U MemNo,INT32U Offset,void *pDst,INT16U RD_Len,void *pDst_Start,INT16U DstLen)
{
  INT8U i,Re;

  WR_Memory_Clear_Dog();
  
  ASSERT(A_WARNING,(INT8U *)pDst>=(INT8U *)pDst_Start && (INT8U *)pDst_Start+RD_Len<=(INT8U *)pDst_Start+DstLen);
  
  for(i=0;i<sizeof(Sys_LOG_Mem)/sizeof(S_LOG_Mem_Info);i++)
  {
    if(Sys_LOG_Mem[i].LOG_MemNo==MemNo)
    {
      if(Offset+RD_Len<=Sys_LOG_Mem[i].PHY_Mem_Info.Mem_Size)
      {
        //������洢���е�����
        Power_Down_Check();
        Re=Read_PHY_Mem(Sys_LOG_Mem[i].PHY_Mem_Info.MemNo,\
                        Sys_LOG_Mem[i].PHY_Mem_Info.Mem_Addr+Offset,\
                        pDst,\
                        RD_Len,\
                        pDst_Start,\
                        DstLen);
        if(ASSERT(A_WARNING,Re==NO_ERR))
         return Re;
        else
         return NO_ERR;
      }
      else
      {
         ASSERT(A_WARNING,0);
         return LOG_MEM_ADDR_ERR;//�߼��洢����ַ��
      }
    }
  }
  ASSERT(A_WARNING,0);
  return LOG_MEM_NO_ERR;//�߼��洢����Ŵ�
}

//���߼��洢��д����
//MemNo���߼��洢�����
//Offset,�߼��洢���ڵ�ƫ��
//pSrc, д��Դ����
//д��Դ���ݳ���
//���ؽ��:Re��ʾд�ɹ���������ʾдʧ��
INT8U Write_LOG_Mem(INT8U MemNo,INT32U Offset,void *pSrc,INT16U SrcLen)
{
  INT8U i,Re;
  
  WR_Memory_Clear_Dog();
  
  for(i=0;i<S_NUM(Sys_LOG_Mem);i++)
  {
    if(Sys_LOG_Mem[i].LOG_MemNo==MemNo)
    {
      if(Offset+SrcLen<Sys_LOG_Mem[i].PHY_Mem_Info.Mem_Size)
      {
        Power_Down_Check();
        Re=Write_PHY_Mem(Sys_LOG_Mem[i].PHY_Mem_Info.MemNo,\
                        Sys_LOG_Mem[i].PHY_Mem_Info.Mem_Addr+Offset,\
                        pSrc,\
                        SrcLen);
        if(ASSERT(A_WARNING,Re==NO_ERR))
         return Re;
        else
         return NO_ERR;
      }
      else
      {
         ASSERT(A_WARNING,0);
         return LOG_MEM_ADDR_ERR;
      }
    }
  }
  return LOG_MEM_NO_ERR;
}
#undef MEMORY_C

