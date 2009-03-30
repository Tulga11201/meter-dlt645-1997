
/**
 * @file support.c
 *     { comment block }
 * @brief
 *     { brief description @ref support.cpp }
 * @author li.yao (nardoo@sohu.com)
 * @version v1.00
 * @date 05/29/2008 08:41
 * @note
 *     { paragraph where a note can be entered. }
 */

#include "Pub_PUCK.h"
#include "config.h"

// screen model words.
typedef struct {
    code_t user;     //A/Bģʽ�µ��û���ʾ����-----PUCK
    code_t code;     //Cģʽ�µ���ʾ����-----PUCK
    u8     dlen;
} list_t;

#define BYTE0(x)      (INT8U)(x&0x000000ff)
#define BYTE1(x)      (INT8U)((x&0x0000ff00)>>8)
#define BYTE2(x)      (INT8U)((x&0x00ff0000)>>16)
#define BYTE3(x)      (INT8U)((x&0xff000000)>>24)

#if PROC_645_TYPE==PROC_645_2007
INT8U Get_Code (scrn_t *temp,INT32U DI)
{
  INT8U Modi;
  
  if(DI==temp->item)
  {
    Modi=0;
  }
  else
  {
    if(BYTE3(DI)==BYTE3(temp->item) && BYTE2(DI)==BYTE2(temp->item) && BYTE1(DI)==BYTE1(temp->item))
    {
      if(0!=temp->BytePos)
        return 0;
      Modi=BYTE0(DI);
    }
    
    if(BYTE3(DI)==BYTE3(temp->item) && BYTE2(DI)==BYTE2(temp->item) && BYTE0(DI)==BYTE0(temp->item))
    {
      if(1!=temp->BytePos)
        return 0;
      Modi=BYTE1(DI);
    }
    
    if(BYTE3(DI)==BYTE3(temp->item) && BYTE1(DI)==BYTE1(temp->item) && BYTE0(DI)==BYTE0(temp->item))
    {
      if(2!=temp->BytePos)
        return 0;
      Modi=BYTE2(DI);
    }
    
    if(BYTE2(DI)==BYTE2(temp->item) && BYTE1(DI)==BYTE1(temp->item) && BYTE0(DI)==BYTE0(temp->item))
     {
      if(3!=temp->BytePos)
        return 0;
      Modi=BYTE3(DI);
     }
  }
  temp->item=DI;
  switch(temp->GroupFlag)
  {
    case GROUP_TARIFF:      
      if(Modi)
      {
        temp->elem.feerate=1;           //��ʾ "����"
        temp->elem.tariff=Modi;         //��ʾ "Txx"
      }
      else
        temp->elem.total=1;      
    break;
    case GROUP_SETTLE:      
      if(Modi)
      {
        temp->elem.lastmonth=Modi;         //��ʾ "��xx��"
      }
      else
        temp->elem.thismonth=1;          //��ǰ  
    break;
    
    
    
  }
  
  return 1;
}
#endif


// ��ʾ������
static volatile list_t vlist;

/********************************************************************************
PUCK:
�������ܣ���ȡ��ʾ����ĸ�����Ҳ���ǹ��ķ�Χ
��ڣ�
���أ�
********************************************************************************/
curs_t maxcurs () 
{
    return (curs_t)vlist.dlen;
}
/********************************************************************************
PUCK:
�������ܣ���ȡ��Ӧģʽ��A����B���µľ�����ʾ��Ŀ
��ڣ�
     item-----��ʾ��Ŀ��ͬ645��ʶ;offs-----����Ŀ�µĺ�����Ŀ����ƫ��
���أ�
********************************************************************************/
list_t getlist (item_t item, offs_t offs) 
{
  INT8U Err;
  INT16U Len;
  list_t list = {0, 0, 0};

#if PROC_645_TYPE==PROC_645_1997
  if(item&0xFF00!=0xC600)
    ASSERT(A_WARNING,0); 
#endif
 
#if PROC_645_TYPE==PROC_645_2007
    ;  //��������Ӵ���
#endif
  
  Len=Read_Storage_Data(item+(offs/10)*16+(offs%10),&list,&list,sizeof(list),&Err);
  if(0==Len || Err!=NO_ERR)
    ASSERT(A_WARNING,0);
  
#if PROC_645_TYPE==PROC_645_2007
  list.code=list.user;  //��ʾ������Э�����DI���
#endif
  return list;

  //getdata(item + (offs / 10) * 16 + (offs % 10), &list, &list, sizeof(list));

}
/********************************************************************************
PUCK:
�������ܣ������޸ĵ�DIֵ������Cģʽ�µ���ʾcode
��ڣ�
���أ�
********************************************************************************/
u32 Set_ParaModi_Proc(u16 ModiDI) 
{
  const scrn_t* p;
  u32 DisCode=0;
  
   for(p=&table[0];p!= &table[MAXCOUNT];++p) 
   {
     if (ModiDI==p->item)
     {
       DisCode=p->code;
       break;
      }
   }
   return DisCode;
}
/********************************************************************************
PUCK:
�������ܣ���λ����ʾ���ݣ�ʵ��ֻ����A/Bģʽ
��ڣ�
     type-----ģʽ����;offs-----��ģʽ����ʾ����Ŀ˳��
���أ�
********************************************************************************/
void lcdshow (u8 type, offs_t offs) 
{
    switch (type) 
    {
        case modeA: //Aģʽ�£�����645��ʶ����ƫ�ƻ�ȡ��ʾԪ��-----------PUCK
        {
            vlist = getlist(ITEMMODEA, offs % MODE_A_NUM);
            vlist.dlen = 2;
            break;
        }
        case modeB: //Bģʽ�£�����645��ʶ����ƫ�ƻ�ȡ��ʾԪ��-----------PUCK
        {
            vlist = getlist(ITEMMODEB, offs % MODE_B_NUM);
            vlist.dlen = 2;
            break;
        }
        default :   //Cģʽ�£����ݱ��ƫ�ƻ�ȡ��ʾԪ��-----------PUCK
        {
            vlist.user = table[offs % MAXCOUNT].code; 
            vlist.dlen = MAXBITS;
            break;
        }
    }
}
/********************************************************************************
PUCK:
�������ܣ�����ģʽ����,��ʾ���룬��ȡ��ʾ��Ϣ��
��ڣ�
     type-----ģʽ����;code-----��ģʽ����ʾ����Ŀ˳��
���أ�
********************************************************************************/
unsigned char Ser_Support_Code(item_t code)
{
  const scrn_t* p;
  for(p=&table[0];p!=&table[MAXCOUNT];++p) 
  {
    if (code==p->item) 
    {
      return 1;
    }
 }
 return 0;
}
/********************************************************************************
PUCK:
�������ܣ���������ʾ���ݣ�ʵ��Cģʽ��ʾ
��ڣ�
     type-----ģʽ����;code-----��ģʽ����ʾ����Ŀ˳��
���أ�
********************************************************************************/
void display(u8 type, code_t code) 
{
    vlist.user = code;
    switch (type) 
    {
        case modeA: 
        {
            for (offs_t offs = MODE_A_NUM; offs > 0; --offs) 
            {
                list_t list = getlist(ITEMMODEA, offs);
                if (code == list.user) 
                {
                    vlist = list;
                    break;
                }
            }
            break;
         }
        case modeB: 
         {
            for (offs_t offs = MODE_B_NUM; offs > 0; --offs) 
            {
                list_t list = getlist(ITEMMODEB, offs);
                if (code == list.user) 
                {
                    vlist = list;
                    break;
                }
            }
            break;
        }
        default : 
        {
            vlist.code = code;
            vlist.dlen = MAXBITS;
            break;
        }
    }
}
/********************************************************************************
PUCK:
�������ܣ���ȡ��Ļ��ʾ��Ϣ������ʾ
��ڣ�
     type-----ģʽ����;curs-----���λ��
���أ�
********************************************************************************/
void screen (u8 type, curs_t curs) 
{
   const scrn_t* p;
  //�ڴ�ǰ��vlist����Ϣ�Ѿ�����-----PUCK
#if PROC_645_TYPE==PROC_645_1997 
    static scrn_t scrn={0xff,0xff,"",{0}};   //��Ϊ0����֤��һ�ξ��ܸ��£���Ϊ0x000000�п��ܵ�һ�ξ���0---PUCK
    if(scrn.code != vlist.code)              //����ȫ�Դ�������������Ѿ����£���Ҫ����vlist�ı����ȡ�µ���ʾԪ��-----------PUCK
#endif
      
#if PROC_645_TYPE==PROC_645_2007
    static scrn_t scrn={0xff,0xff,GROUP_NO,0,"",{0}};   //��Ϊ0����֤��һ�ξ��ܸ��£���Ϊ0x000000�п��ܵ�һ�ξ���0---PUCK
    if (scrn.item != vlist.code)     //����������������A/Bģʽ��ΪЭ��DI���룬Cģʽ�»�����ʾ����
#endif
    {
        for (p=&table[0];p!=&table[MAXCOUNT];++p) 
        {
#if PROC_645_TYPE==PROC_645_1997
            if ( p->code==vlist.code)  //������ʾ�������
            {
                scrn = *p;
                break;
            }  
#endif
            
#if PROC_645_TYPE==PROC_645_2007
            scrn=*p;        
            {
              if(Get_Code(&scrn,vlist.code))  //����������������
                break;
            }
#endif                  
        }
    }
    if(p==&table[MAXCOUNT]) //�Ҳ�����ʾ�Ĵ���,ֻ��ʾ���룬�¼�����������ʾ-------PUCK
    {
      lcd_code     (vlist.user, curs);
      lcd_events();
      lcd_update();  
      return ;
    }
    
    curs %= vlist.dlen;
    lcd_data     (scrn.item, scrn.frmt,scrn.elem.signpos);   //18ms
    lcd_code     (vlist.user, curs);       //26ms
    lcd_mode     (type);                ///A/B/C 3��ģʽ
    lcd_total    (scrn.elem.total    ); ///< "��",
    lcd_phase    (scrn.elem.phase    ); ///< "A/B/C��",
    lcd_voltage  (scrn.elem.voltage  ); ///< "��ѹ",
    lcd_current  (scrn.elem.current  ); ///< "����",
    lcd_positive (scrn.elem.positive ); ///< mode4.bit4 ? "����" : "����";
    lcd_negative (scrn.elem.negative ); ///< mode4.bit4 ? "���" : "����";
    lcd_reactive (scrn.elem.reactive ); ///< "�޹�",
    lcd_active   (scrn.elem.active   ); ///< "�й�",
    lcd_power    (scrn.elem.power    ); ///< "����",
    lcd_factor   (scrn.elem.factor   ); ///< "����",
    lcd_angle    (scrn.elem.angle    ); ///< "���",
    lcd_energy   (scrn.elem.energy   ); ///< "����",
    lcd_demand   (scrn.elem.demand   ); ///< "����",
    lcd_time     (scrn.elem.time     ); ///< "ʱ��",
    lcd_charge   (scrn.elem.charge   ); ///< "���",
    lcd_lostvolt (scrn.elem.lostvolt ); ///< "ʧѹ",
    lcd_lostcurt (scrn.elem.lostcurt ); ///< "ʧ��",
    lcd_periods  (scrn.elem.periods  ); ///< "ʱ��",
    lcd_feerate  (scrn.elem.feerate  ); ///< "����",    
    lcd_thismonth(scrn.elem.thismonth); ///< "����",
    lcd_lastmonth(scrn.elem.lastmonth); ///< mode4.bit5 ? "����", "������" : "��1��", "��2��";
    lcd_assemble (scrn.elem.assemble ); ///< "�޹���Ϸ�ʽ1 or 2", mode4.bit7 ? "��ʱ��" : "˳ʱ��";
    lcd_quadrant (scrn.elem.quadrant ); ///< "XX����",
    lcd_tariff   (scrn.elem.tariff   ); ///< ��ʾ"����Tx",
    lcd_times    (scrn.elem.times    ); ///< ��ʾ"��XX��",
    lcd_events   ();    //8ms
    lcd_update   ();
}
