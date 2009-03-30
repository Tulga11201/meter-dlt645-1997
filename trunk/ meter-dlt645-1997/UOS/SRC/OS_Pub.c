#define OS_PUB_C
#include "OS_Core.h"
#include "stdarg.h"
#include "stdio.h"
#include "string.h"
#include "Pub_Debug.h"

CONST OS_INT16U Crc_Table0[16]={0x0000,0x1021,0x2042,0x3063,0x4084,0x50a5,0x60c6,0x70e7,
                                0x8108,0x9129,0xa14a,0xb16b,0xc18c,0xd1ad,0xe1ce,0xf1ef};

CONST OS_INT16U Crc_Table1[256]={ 
  0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
  0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
  0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
  0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
  0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
  0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
  0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
  0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
  0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
  0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
  0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
  0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
  0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
  0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
  0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
  0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
  0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
  0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
  0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
  0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
  0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
  0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
  0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
  0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
  0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
  0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
  0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
  0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
  0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
  0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
  0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
  0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0};

extern void Clr_Ext_Inter_Dog(void);
#if OS_ASSERT_HOOK_EN
extern INT8U OS_Assert_Hook();
INT8U OS_ASSERT_Hook()
{
  INT8U Temp;
  INT8U Re;
  Temp=Assert_Info.On_Off_Flag;
  OS_Assert_Ctrl(0);
  Re=OS_Assert_Hook();
  OS_Assert_Ctrl(Temp);
  return Re;  
}
#else
#define OS_ASSERT_Hook()
#endif

extern INT8U Check_Debug_En();



//����format��ap���������������Ϣ
void OS_vsPrintf(CONST OS_INT8S *format, va_list ap)
{
  
  static const OS_INT8S Chr[] = "0123456789ABCDEF";

  static const OS_INT32U Oct[12]=
  {
    01,010,0100,01000,010000,0100000,01000000,010000000,
    0100000000,01000000000,010000000000,010000000000,
  }; //�˽���
   static const OS_INT32U Dec[11]=
  {
    1,10,100,1000,10000,100000,1000000,
    10000000,100000000,1000000000,1000000000,
  }; //ʮ����
  static const OS_INT32U Hex[8]=
  {
    0x1,0x10,0x100,0x1000,0x10000,
    0x100000,0x1000000,0x10000000,
  }; //ʮ������
  
  OS_INT8U LintFlag;
  OS_INT32U const *p;
  OS_INT8S *ptr;
  
  unsigned long int uParaValue;//�޷�����
  long int sParaValue;//�з�����
  
  OS_INT8U c;
  OS_INT8U i,Width,Len;
 
  for(;;)    //��������������
  {
    while((c=*format++)!='%')//%����֮ǰȫ���ַ���
    {
      if(!c)
        return;
      Debug_Out_Public_Puck(&c,1);
    }

    c=*format++;
    //����ֵ���ʹ���
    switch(c)
    {
      case 'c':
        c = va_arg(ap, int);
        Debug_Out_Public_Puck(&c,1);
        break;
      case 's':
        ptr= va_arg(ap,OS_INT8S *);
        while((c = *ptr++)!=0)
          Debug_Out_Public_Puck(&c,1);
        break;
    }
    
    //��ֵ���ʹ���
    if(c>='1' && c<='9')
    {
      Width=c-'0';
      c=*format++;
    }
    else
      Width=1;//���ٴ�ӡһ���ַ�
    
    if(c=='l' || c=='L')//�Ƿ���һ��������?
    {
      LintFlag=1;
      c=*format++;
    }
    else
      LintFlag=0;
    
    switch(c)//��ӡ��������
    {
      case 'o':
        p=Oct;
        Len=12;
        break;
      case 'd':
      case 'u':
        p=Dec;
        Len=11;
        break;
      case 'x':
        p=Hex;
        Len=8;
        break;

      default:
        continue;
    }
    
    //��ȡ������ֵ
    if(c=='d')//�з�����
    {
      if(LintFlag)//������
        sParaValue=va_arg(ap,long int);
      else
        sParaValue=va_arg(ap,int);
      
      if(sParaValue<0)
      {
        c='-';
        Debug_Out_Public_Puck(&c,1);
        sParaValue=0-sParaValue;
      }
      uParaValue=(unsigned long int)sParaValue;//��ֵ��uParaValue,ͳһ����
    }
    else//�޷�����
    {
      if(LintFlag)//������
        uParaValue=va_arg(ap,unsigned long int);
      else
        uParaValue=va_arg(ap,unsigned int);  
    }
    
    //�������ݱ���ĳ���
    for(i=0;i<Len;i++)
    {
       if(uParaValue<*(p+i))
         break;
    }
    
    if(Width<i)//i��ʾ���ݱ����ȣ�Width��ʾ��Ҫ��ӡ�ĳ���
      Width=i;
    
    //�ֱ��ӡÿ���ַ�
    i=0;//��ʾ�Ƿ��Ѿ��ҵ���һ����0λ
    for(;Width!=0;Width--)
    {
      c=uParaValue/(*(p+Width-1));
      uParaValue=uParaValue%(*(p+Width-1));
      //ǰ���0ȫ����ɿո�

      if(c==0 && i==0 && Width>1)//��λΪ0����֮ǰ��λҲ��Ϊ0,�Ҳ������һλ(��ֵ����Ϊ0)
        c=' ';
      else
      {
        i=1;//��ʾ�Ѿ���һ����0λ��
        c=Chr[c];
      }
      Debug_Out_Public_Puck(&c,1);
    }
  }
}

//������Ϣ�������
//ע��Ŀǰֻ֧��%c,%s,%d,%u,%o,%x���ݲ�֧�ָ�����
void OS_Debug_Print(CONST OS_INT8S *format, ...)
{
  va_list ap;
  va_start(ap,format);
  OS_vsPrintf(format,ap);
  va_end(ap);
}

//���Դ򿪹رյĿ��ƹ���
void OS_Assert_Ctrl(OS_INT32U Flag)
{
  Assert_Info.On_Off_Flag=Flag;//�򿪶���
}

//�������
//Condition��ʾ����
//File�������ڵ��ļ�
//Function�������ڵĺ���
//Line�������ڵ��к�
//������������0������������1
#if OS_ASSERT_FUNC_EN>0
OS_INT8U OS_Assert(OS_INT8U Condition,CONST OS_INT8U File[],CONST OS_INT8S Function[],OS_INT16U Line)
{
#else
OS_INT8U OS_Assert(OS_INT8U Condition,CONST OS_INT8U File[],OS_INT16U Line)
{
  const INT8U Function[]="Func";
#endif 
  
  OS_INT8U i,j;
  OS_INT16U Len;  
  //static OS_INT8U Flag=0;
  
  Condition=((Condition!=0)?0:1);
  if(Check_Debug_En()==0)//���ǵ���״̬����ӡ
    return Condition;

  //���Թرյ�����²���ӡ������Ϣ�ͼ�¼��������
#if OS_ASSERT_CTRL_EN==1
  if(GET_BIT(Assert_Info.On_Off_Flag,Task_Info.Cur_Task_ID)==0)
    return Condition;   
#endif 

  //Flag=1;//��ʾ�Ѿ���Assert�������ˣ���ֹ�ظ�����  
  if(1==Assert_Info.Flag)
  {
    DEBUG_PRINT(ASSERT_ID,DEBUG_0,"ASSERT Reentry!\r\n");
    return Condition;
  }
  
  Assert_Info.Flag=1;//��ʾ�Ѿ�����
  OS_ASSERT_Hook();

  Len=strlen((char *)File)+1;
  
  if(Len>OS_ASSERT_BUF_LEN)
    File=File+Len-OS_ASSERT_BUF_LEN;//ȡ�ļ�������ʼλ��
    
  if(Condition)//Conditon�Ѿ�ת����0��ʾ�����棬1��ʾ��
  {
    //��ӡ�������ֻ���ID
    DEBUG_PRINT(ASSERT_ID,DEBUG_0,"ASSERT:-----------------");
#if OS_USE_TASK_NAME    
    DEBUG_PRINT(ASSERT_ID,DEBUG_0,"ASSERT:Task Name:%s",Tcb[Task_Info.Cur_Task_ID].Name);
#else
    DEBUG_PRINT(ASSERT_ID,DEBUG_0,"ASSERT:Task ID:%d",Task_Info.Cur_Task_ID);
#endif
  
    //��ӡ�����ļ�
   // if(Condition)
      DEBUG_PRINT(ASSERT_ID,DEBUG_0,"ASSERT:Err File:%s,Function:%s,Line:%d",File,Function,Line);

    //��ӡǰ���ε��õĺ���
    if(Assert_Info.Index>=OS_ASSERT_NUM)
    {
      DEBUG_PRINT(ASSERT_ID,DEBUG_0,"ASSERT:ASSERT Index error %d",Assert_Info.Index);
      Assert_Info.Index=0;
    }
    
    j=Assert_Info.Index; //���һ�ε�����Ϣ����   
    for(i=0;i<OS_ASSERT_NUM;i++)//��ӡ��ǰAS_BUF_NUM�ε��õĺ���
    {
      Clr_Ext_Inter_Dog();
      Assert_Info.File[j][OS_ASSERT_BUF_LEN-1]=0;
      
      DEBUG_PRINT(ASSERT_ID,DEBUG_0,"ASSERT:Call:Task:%u,Line:%u,Counts:%u,File:%s",\
        *(OS_INT8U *)&Assert_Info.Task_ID[j],\
        *(OS_INT16U *)&Assert_Info.Line[j],\
        *(OS_INT16U *)&Assert_Info.Counts[j],\
        Assert_Info.File[j]);
      //ǰһ�ε�����Ϣ
      if(j==0)
        j=OS_ASSERT_NUM-1;
      else
        j--;
    } 
  }

  //��¼�µ��˵��õĺ���
  //�ôε��ú��ϴε��õ��кŲ����,�������ε��õĺ������ֲ�һ��,���߲�����ͬһ��������,��Ϊ�����β�ͬ�ĵ���
  if(Assert_Info.Line[Assert_Info.Index]!=Line ||\
     strcmp(Assert_Info.File[Assert_Info.Index],(char *)File)!=0 ||\
     Assert_Info.Task_ID[Assert_Info.Index]!=Task_Info.Cur_Task_ID)
  {
    Assert_Info.Index++;
    if(Assert_Info.Index>=OS_ASSERT_NUM)
      Assert_Info.Index=0;
    
    //��¼��ǰ�����,���к�
    Assert_Info.Task_ID[Assert_Info.Index]=Task_Info.Cur_Task_ID;//��������ID
    Assert_Info.Line[Assert_Info.Index]=Line;//�����к�
    Assert_Info.Counts[Assert_Info.Index]=1;//���ô���
    //��¼�ļ���
    memcpy(Assert_Info.File[Assert_Info.Index],File,OS_ASSERT_BUF_LEN-1);//��¼�¸ôε��õĺ�������
    //memcpy(Assert_Info.Function[Assert_Info.Index],(void *)Function,OS_ASSERT_BUF_LEN-1);//��¼�¸ôε��õĺ�������
    //���һ���ַ���0
    Assert_Info.File[Assert_Info.Index][OS_ASSERT_BUF_LEN-1]=0;
  }
  else
  {
    Assert_Info.Counts[Assert_Info.Index]++;//��Ϊ�ڷ�������ͬһ�����������ӵ��ô����ļ�¼
  }
  
  //Flag=1��ʾ�Ѿ���Assert�������ˣ���ֹ�ظ�����
  Assert_Info.Flag=0;
  return Condition;
}

/*****************************************
����ԭ�ͣ�
OS_INT16U OS_Debug_Print(char *format,...)
�������ܣ�
��ӡ������Ϣ�����Խ�������Ϣ��ӡ�����ڻ�IAR��i/o������
��ڲ����������б�
���ڲ�������ӡ��Ϣ����
******************************************/
/*
OS_INT16U OS_Debug_Print(OS_INT8S *format,...)
{
  va_list ap;
  OS_INT16U n=0;

  if(OS_PRINT_TYPE==OS_PRINT_NULL)//�����
    return 0;
  else if(OS_PRINT_TYPE==OS_PRINT_COMM)//ͨ�ſ����
  {
    va_start(ap,format);
    n=vsprintf(OS_Debug_Buf,format,ap);
    
    //���߽�
    if(n>=sizeof(OS_Debug_Buf))
      Debug_Out_Public_Puck("OS_Deubg_Buf Overflow!",strlen("OS_Deubg_Buf Overflow"));//�����������
    //���ô������
    Debug_Out_Public_Puck(OS_Debug_Buf,n);
    va_end(ap);
    return n;
  }
  else if(OS_PRINT_TYPE==OS_PRINT_STDIO)//��������׼IO���
  {
    va_start(ap,format);
    OS_Debug_Buf[0]=OS_Debug_Buf[sizeof(OS_Debug_Buf)-1]=CHK_BYTE;
    n=vsprintf(OS_Debug_Buf,format,ap);
    
    //���߽�
    if(n>=sizeof(OS_Debug_Buf))
      printf("OS_Deubg_Buf Overfow!");
    
    printf("%s",OS_Debug_Buf);
    va_end(ap);
    return n;
  }
  else
    return 0;
}
*/

//memcpy����
//pDst��ʾĿ�껺����
//pSrc��ʾԴ������
//SrcLen��ʾ��������
//pDst_Start��DstLenһ������pDst��SrcLen�ķ�Χ
//��������ASSERT(A_WARNING,(OS_INT8U *)pDst>=(OS_INT8U *)pDst_Start && (OS_INT8U *)pDst+SrcLen<=(OS_INT8U *)pDst_Start+DstLen);
void OS_memcpy(void *pDst,void *pSrc,OS_INT32U SrcLen,void *pDst_Start,OS_INT32U DstLen)
{
  if(!((OS_INT8U *)pDst>=(OS_INT8U *)pDst_Start && (OS_INT8U *)pDst+SrcLen<=(OS_INT8U *)pDst_Start+DstLen))//pDst�������������
  {
    ASSERT(A_WARNING,0);
    return;
  }
  memcpy(pDst,pSrc,SrcLen);
}

//memset����
//pDst��ʾĿ�껺����
//Value��ʾ��Ҫ���õ�ֵ
//SetLen��ʾ��������
//pDst_Start��DstLenһ������pDst��SetLen�ķ�Χ
//��������ASSERT(A_WARNING,(OS_INT8U *)pDst>=(OS_INT8U *)pDst_Start && (OS_INT8U *)pDst+SetLen<=(OS_INT8U *)pDst_Start+DstLen);
void OS_memset(void *pDst, OS_INT8U Value,OS_INT32U SetLen,void *pDst_Start,OS_INT32U DstLen)
{
  if(!((OS_INT8U *)pDst>=(OS_INT8U *)pDst_Start && (OS_INT8U *)pDst+SetLen<=(OS_INT8U *)pDst_Start+DstLen))//pDst�������������
  {
    ASSERT(A_WARNING,0);
    return;
  }
  memset(pDst,Value,SetLen);
}


//CRCУ���㷨0�����ڿռ�Ƚ�С�����,���ٶ�Ҫ�󲻸ߵ����
OS_INT16U OS_Crc16_0(OS_INT8U *pSrc, OS_INT16U Len) 
{
  OS_INT16U Crc;
  OS_INT8U Temp;
  
  Crc=0;
  while(Len--!=0)
   {
     Temp=(OS_INT8U)(Crc>>12); 
     Crc<<=4; 
     Crc^=Crc_Table0[Temp^(*pSrc/16)]; 
                                
     Temp=(OS_INT8U)(Crc>>12); 
     Crc<<=4; 
     Crc^=Crc_Table0[Temp^(*pSrc&0x0f)]; 
     pSrc++;
  }
  return(Crc);
}

//CRCУ���㷨1�����ڿռ�Ƚϴ�����,���ٶ�Ҫ��ϸߵ����
OS_INT16U OS_Crc16_1(OS_INT8U *pSrc, OS_INT16U Len)
{
  OS_INT16U Crc=0x00;
  OS_INT16U i,Temp;
  
  for(i=0;i<Len;i++)
  {
    Temp=Crc;
    Crc=Crc_Table1[(Temp>>8)^*pSrc++];
    Crc=Crc^(Temp<<8);
  }
  return(Crc);
}

//ͨ�ü��У��ͺ���
//pSrc��ʾ��Ҫ�������ݻ�����
//SrcLen��ʾ���ݻ���������
//pCS��ʾУ��͵���ʼ��ַ
//CS_Bytes��ʾУ��ͳ���
//ע�⣺�������Ҫ��Set_Sum�ɶ�ʹ�ã���Ϊ�ڲ����Ǽ���򵥵�У���
OS_INT8U OS_Check_Sum(void *pSrc,OS_INT16U SrcLen,void *pCS,OS_INT8U CS_Bytes)
{
  OS_INT32U Sum=0;
  
  if(!(CS_Bytes==1 || CS_Bytes==2 || CS_Bytes==4))//�ֽ���������1��2��3
    OS_ASSERT(0);
  
#if OS_CS_TYPE==CS_CRC16_0
  Sum=(OS_INT32U)OS_Crc16_0((OS_INT8U *)pSrc,SrcLen);
#elif OS_CS_TYPE==CS_CRC16_1
  Sum=(OS_INT32U)OS_Crc16_1((OS_INT8U *)pSrc,SrcLen);
#else
  while(SrcLen!=0)
  {
    SrcLen--;
    Sum+=*((OS_INT8U *)pSrc+SrcLen);
  }
#endif
  
  Sum=Sum^CHK_CS_BYTES;//���м򵥱任,ĳЩλȡ��  
  if(memcmp(&Sum,pCS,CS_Bytes)==0)
    return 1;
  else
    return 0;
}

//ͨ������У��ͺ���
//pSrc��ʾ��Ҫ����У��͵����ݻ�����
//SrcLen��ʾ���ݻ���������
//pDst��ʾУ��͵���ʼ��ַ
//CS_Bytes��ʾУ��ͳ���
//pDst_Start��pDst��Χ���޶�
//DstLen��pDst��Χ���޶�,
//��Ҫ����ASSERT(A_WARNING,(OS_INT8U *)pDst>=(OS_INT8U *)pDst_Start && (OS_INT8U *)pDst+CS_Bytes<=(OS_INT8U *)pDst_Start+DstLen);
//�������Ҫ��Check_Sum�ɶ�ʹ�ã���Ϊ���ɵ�У�鲻�Ǽ򵥵�У��ͣ����ǽ����˼򵥵ı任
void OS_Set_Sum(void *pSrc,OS_INT16U SrcLen,void *pDst,OS_INT8U CS_Bytes,void *pDst_Start,OS_INT16U DstLen)
{
  OS_INT32U Sum=0;
  
  if(!(CS_Bytes==1 || CS_Bytes==2 || CS_Bytes==4))
    OS_ASSERT(0);
  
  if(!((OS_INT8U *)pDst>=(OS_INT8U *)pDst_Start && (OS_INT8U *)pDst+CS_Bytes<=(OS_INT8U *)pDst_Start+DstLen))
  {
    OS_ASSERT(0);
    return;
  }
  
#if OS_CS_TYPE==CS_CRC16_0
  Sum=(OS_INT32U)OS_Crc16_0((OS_INT8U *)pSrc,SrcLen);
#elif OS_CS_TYPE==CS_CRC16_1
  Sum=(OS_INT32U)OS_Crc16_1((OS_INT8U *)pSrc,SrcLen);
#else
  while(SrcLen!=0)
  {
    SrcLen--;
    Sum+=*((OS_INT8U *)pSrc+SrcLen);
  }
#endif
  
  Sum=Sum^CHK_CS_BYTES;//���м򵥱任,ĳЩλȡ��  
  OS_memcpy(pDst,&Sum,CS_Bytes,pDst_Start,DstLen);
}

//���ĳ���ṹ���У����Ƿ���ȷ,�ýṹ��Ķ�������������·�ʽ
//
//typedef struct{
//     ...
//     ...
//     OS_INT8U CS[OS_CS_BYTES];//���һ���������У��ͣ��ҳ���ΪOS_CS_BYTES
//    }sturct_name;
//
//pSrcΪ�ṹ���������ʼָ��
//SrcLenΪ�ṹ���������
//CSΪ�ṹ�������У���,ע��ñ�������Ϊ�ṹ���е�һ����
//ע�⣺�������Ҫ��Set_STRUCT_Sum�ɶ�ʹ�ã���ΪУ������㷨һ��
OS_INT8U OS_Check_STRUCT_Sum(void *pSrc,OS_INT16U SrcLen,OS_INT8U *pCS,OS_INT8U CS_Bytes)
{
  OS_INT16U Len;
  
  if(!(pCS>(OS_INT8U *)pSrc && pCS+CS_Bytes<=(OS_INT8U *)pSrc+SrcLen))//�ж�CS��λ���Ƿ�Ϸ�
  {
    OS_ASSERT(0);
    return 0;
  }
  
  Len=(OS_INT16U)((OS_INT8U *)pCS-(OS_INT8U *)pSrc);//������Ҫ����У��͵����ݳ���
  return OS_Check_Sum(pSrc,Len,pCS,CS_Bytes);
}

//���ýṹ�������У���,�ýṹ��Ķ�������������·�ʽ
//
//typedef struct{
//     ...
//     ...
//     OS_INT8U CS[OS_CS_BYTES];//���һ���������У��ͣ��ҳ���ΪOS_CS_BYTES
//    }sturct_name;
//
//pSrcΪ�ṹ���������ʼָ��
//SrcLenΪ�ṹ���������
//CSΪ�ṹ�������У���,ע��ñ�������Ϊ�ṹ���е�һ����
//ע�⣺�������Ҫ��Check_STRUCT_Sum�ɶ�ʹ�ã���ΪУ������㷨һ��
void OS_Set_STRUCT_Sum(void *pSrc,OS_INT16U SrcLen,OS_INT8U *pCS,OS_INT8U CS_Bytes)
{
  OS_INT16U Len;

  if(!(pCS>(OS_INT8U *)pSrc && pCS+CS_Bytes<=(OS_INT8U *)pSrc+SrcLen))//�ж�CS��λ���Ƿ�Ϸ�
  {
    OS_ASSERT(0);
    return;
  }
  
  Len=(OS_INT16U)((OS_INT8U *)pCS-(OS_INT8U *)pSrc);//������Ҫ����У��͵����ݳ���
  OS_Set_Sum(pSrc,Len,pCS,CS_Bytes,pSrc,SrcLen);
}

#undef OS_PUB_C
