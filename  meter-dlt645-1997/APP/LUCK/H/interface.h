
/**                                                                                                
 * @file interface.h                                                                                    
 *     { comment block }
 * @brief                                                                                           
 *     { brief description @ref interface.cpp }                                                                              
 * @author li.yao (nardoo@sohu.com)                                                                                  
 * @version v1.00                                                                               
 * @date 05/29/2008 08:40                                                                                   
 * @note 
 *     { paragraph where a note can be entered. }                                                   
 */                                                                                                 


#ifndef __INTERFACE__
#define __INTERFACE__

#define  MAXDLEN  32  //��ʾ��������ַ���Ŀ
#define  MAXBITS  6   //��ʾ����λ��


typedef signed   char      s8;  ///< unsigned  8 bit quantity.
typedef unsigned char      u8;  ///< unsigned  8 bit quantity.
typedef unsigned short     u16; ///< unsigned 16 bit quantity.
typedef signed   short     s16; ///< signed   16 bit quantity.
typedef unsigned long      u32; ///< unsigned 32 bit quantity.
typedef signed   long      s32; ///< signed   32 bit quantity.
//typedef _ULonglong         u64; ///< unsigned 64 bit quantity.
//typedef _Longlong          s64; ///< signed   64 bit quantity.

#define TRUE 1
#define FALSE 0
typedef  u8 bool;

typedef u32  code_t; ///< display code type.


typedef u16  item_t; ///< dataitem type.


typedef u16  offs_t; ///< dataitem numbers.
typedef s8   curs_t; ///< cursor position.


/// mode element.
typedef struct {
    u8 bit0 : 1; ///< mode2.bit0 ? "ͣ��ʱ��" : "��ǰʱ��";
    u8 bit1 : 1; ///< mode4.bit1 ? "�澯��ʾ" : "�澯�ر�";
    u8 bit2 : 1; ///< mode3.bit2 ? ʧѹ��־"��˸" : "��ʧ";
    u8 bit3 : 1; ///< mode4.bit3 ? "��λ��0" : "��λ����0";
    u8 bit4 : 1; ///< mode4.bit4 ? "����", "���" : "����", "����";
    u8 bit5 : 1; ///< mode4.bit5 ? "����", "������" : "��1��", "��2��";
    u8 bit6 : 1; ///< mode8.bit6 ? ���������� : ��������
    u8 bit7 : 1; ///< mode4.bit7 ? "��ʱ��" : "˳ʱ��";
} mode_t;

/// status element.
typedef union 
{
    struct 
    {
        u32 loss_voltage  : 3; ///< ��ѹ״̬(ʧѹ/����,Ϩ��)(Ua,Ub,Uc)
        u32 over_voltage  : 3; ///< ��ѹ(Ua,Ub,Uc)(��˸)
        u32 loss_current  : 3; ///< ����״̬(ʧ��/ȫʧ��)(Ia,Ib,Ic)
        u32 Cur_reverse   : 3; ///< ����������(-Ia,-Ib,-Ic)(��˸)
        u32 cell_lowvolt  : 3; ///< ��ص�ѹ��(������Ϊ��˸)
        u32 stat_communi  : 4; ///< ͨ��״̬(RS1,RS2,����)(����)
        u32 volt_reverse  : 1; ///< ��ѹ"������"(��˸)
        u32 event_warning : 1; ///< �¼��澯(��˸)
        u32 switch_opened : 1; ///< ��̼���(����)
        u32 fac_status    : 1; ///< ����(����)
        u32 jumper_short  : 1; ///< ���߶̽�(����)
        u32 reset_demand  : 1; ///< ������λ(����)        
        u32 signal_scale  : 3; ///< ͨѶģ���ź�ǿ��ָʾ(����)
        u32 status_tariff : 4; ///< ��ʾ��ǰ���ʣ�"��, ��, ƽ, ��, T5, ...Tx",
        
        u32 meter_locked  : 1; ///< �������(����)
        u32 status_online : 1; ///< ͨѶģ������ָʾ(����)
        u32  num_tariff   : 2; //��ʾ����ʱ��1����ʱ�Σ�2����ʱ��
        u32  CalMeter     : 1; //У���¼�
        u32  reserved     : 27; //Ԥ��
    };
    struct 
    {
        u32 bit1maps; //< �¼�״̬λͼ
        u32 bit2maps; //< �¼�״̬λͼ
    };    
} stat_t;


/*
typedef enum {
    none = 0x00, 
    key1 = 0x01, 
    key2 = 0x02, 
    key3 = 0x04,
    key4 = 0x08,
    key5 = 0x10,
} pkey_t;
*/
typedef enum {
    modeA, modeB, modeC,
} type_t;

// ��ȡ����ֵ
u8 getpkey (void);

// ����Һ������
void lcdlight (u8 stat);

// ��ȡģʽ��
mode_t getmode (void);
// mode_t : ģʽ�ֽṹ��

// �ж��Ƿ�ͣ��
bool poweroff (void);

// �ж��Ƿ�Ϊʵʱ����
bool rtvalue (item_t item);

// ������ʼ��
void lcdinit (void);

// A������ʱ��
s16 rolltime ();

// ��ȡЭ����������
s16 getdata (item_t id, void* buff, void* start, s16 maxlen);
// id    : ��Ӧ���ݵı�ʶ��
// buff  : ���뻺����׵�ַ
// start : ����������ʼ��ַ
// maxlen: ���뻺�����󳤶�
// return: ����д���ʵ�ʳ���

// ������ʾԪ�أ�������ʾ������Ҫ��˸��
void lcd_total     (u8 flg); ///< "��",
void lcd_phase     (u8 flg); ///< "A/B/C��",
void lcd_voltage   (u8 flg); ///< "��ѹ",
void lcd_current   (u8 flg); ///< "����",
void lcd_positive  (u8 flg); ///< mode4.bit4 ? "����" : "����";
void lcd_negative  (u8 flg); ///< mode4.bit4 ? "���" : "����";
void lcd_reactive  (u8 flg); ///< "�޹�",
void lcd_active    (u8 flg); ///< "�й�",
void lcd_power     (u8 flg); ///< "����",
void lcd_factor    (u8 flg); ///< "����",
void lcd_angle     (u8 flg); ///< "���",
void lcd_energy    (u8 flg); ///< "����",
void lcd_demand    (u8 flg); ///< "����",
void lcd_time      (u8 flg); ///< "ʱ��",
void lcd_charge    (u8 flg); ///< "���",
void lcd_lostvolt  (u8 flg); ///< "ʧѹ",
void lcd_lostcurt  (u8 flg); ///< "ʧ��",
void lcd_periods   (u8 flg); ///< "ʱ��",
void lcd_feerate   (u8 flg); ///< "����", 
void lcd_thismonth (u8 flg); ///< "����",
void lcd_lastmonth (u8 flg); ///< mode4.bit5 ? "����", "������" : "��1��", "��2��";
void lcd_assemble  (u8 flg); ///< "�޹���Ϸ�ʽ1 or 2",
void lcd_quadrant  (u8 flg); ///< "XX����",
void lcd_tariff    (u8 flg); ///< ��ʾ"����Tx",
void lcd_times     (u8 flg); ///< ��ʾ"��XX��",

// �����ʾ���ݵ�����
void lcd_data (item_t item, const char* frmt,u8 signpos);

// �����ʾ���������
void lcd_code (code_t code, curs_t curs);

// �����ʾ����������
void lcd_mode (u8 type);

// ��ʾ����������
void lcd_update (void);

// �����ʾ�¼�״̬
void lcd_events (void);

bool Lcd_Para_Modi(item_t item);
#endif
