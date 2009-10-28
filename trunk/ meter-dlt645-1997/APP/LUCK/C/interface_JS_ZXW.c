
/**
 * @file interface.c
 *     { comment block }
 * @brief
 *     { brief description @ref interface.cpp }
 * @author li.yao (nardoo@sohu.com)
 * @version v1.00
 * @date 05/29/2008 08:41
 * @note
 *     { paragraph where a note can be entered. }
 */

//#include <ctype.h>
//#include <string.h>

#include "Pub_PUCK.h"

#if LCD_PROPERTY==LCD_JS_ZXW
void Check_LCDVar_Cs(void)
{
  if(CHECK_STRUCT_VAR(Pub_Bit8_Len5_PUCK)==0)//ͷβ����
    ASSERT(A_WARNING,0);
  
  if(CHECK_STRUCT_VAR(Pub_Bit16_Len4_PUCK)==0)//ͷβ����
    ASSERT(A_WARNING,0);
  
  if(CHECK_STRUCT_VAR(Sleep_Sec_Timer)==0)//ͷβ����
  ASSERT(A_WARNING,0);
  
  if(CHECK_STRUCT_VAR(Key_Value_Pub)==0)//ͷβ����
  {
    mem_set((void *)(&Key_Value_Pub),0,sizeof(Key_Value_Pub),\
                 (void *)(&Key_Value_Pub),sizeof(Key_Value_Pub));   
    ASSERT(A_WARNING,0);
  }  
}


// ��ȡЭ����������
s16 getdata (item_t item, void* dst, void* dststart, s16 maxlen) 
{ 
  s16 nlen = 0,sign=0;
  void *buff=Dis_GetData_Buf; 
  void *start=Dis_GetData_Buf;
  u8 temp;
  
  if(maxlen>DIS_BUF_LEN)  //Խ�籣��
    return 0;
  
  if (item == DI_COMM_BAUD0)   //��һ·ͨ�Ų���
  {
      u32 type = Chanel_Para[CHANEL_485_1].Baud;
      Hex2Bcd(type, (u8*)buff, sizeof(type), start, maxlen);
      nlen = sizeof(u32);
  }
  else if (item == DI_COMM_BAUD1)   //�ڶ�·ͨ�Ų���
  {
      u32 type = Chanel_Para[CHANEL_485_2].Baud;
      Hex2Bcd(type, (u8*)buff, sizeof(type), start, maxlen);
      nlen = sizeof(u32);
  } 
  else if((item>=0xB630)&&(item<=0xB633))  //�й�����
  {
      nlen = Get_DLT645_Data_For_Disp(item,(u8*)buff,(u8*)start, maxlen);
      if(item==0xB630&& Measu_Status_Mode_ToPub_PUCK.SUM_APwrDir)
        sign=-1;
      if(item==0xB631&& Measu_Status_Mode_ToPub_PUCK.A_APwrDir)
        sign=-1;        
      if(item==0xB632&& Measu_Status_Mode_ToPub_PUCK.B_APwrDir)
        sign=-1;        
      if(item==0xB633&& Measu_Status_Mode_ToPub_PUCK.C_APwrDir)
        sign=-1;
  }
  else if((item>=DI_REACTIVE_ALL)&&(item<=DI_REACTIVE_C))  //�޹����� 
  {
      nlen = Get_DLT645_Data_For_Disp(item,(u8*)buff,(u8*)start, maxlen);
      if(item==DI_REACTIVE_ALL&& Measu_Status_Mode_ToPub_PUCK.SUM_RPwrDir)
        sign=-1;
      if(item==DI_REACTIVE_A&& Measu_Status_Mode_ToPub_PUCK.A_RPwrDir)
        sign=-1;        
      if(item==DI_REACTIVE_B&& Measu_Status_Mode_ToPub_PUCK.B_RPwrDir)
        sign=-1;        
      if(item==DI_REACTIVE_C&& Measu_Status_Mode_ToPub_PUCK.C_RPwrDir)
        sign=-1;
  } 
  else if(((item>=0xC331)&&(item<=0xC36E))|| ((item>=0xCB21)&&(item<=0xCB6E)))  // ��1/2�׷��ʵ�n��ʱ�α��nʱ����ʼʱ�ּ�����ʺ�
  {
      nlen = Get_DLT645_Data_For_Disp(item,(u8*)buff,(u8*)start, maxlen);
      temp=Dis_GetData_Buf[0];
      Dis_GetData_Buf[0]=Dis_GetData_Buf[2];
      Dis_GetData_Buf[2]=temp;
      
      temp=Dis_GetData_Buf[0];
      Dis_GetData_Buf[0]=Dis_GetData_Buf[1];
      Dis_GetData_Buf[1]=temp;
  } 
  else 
  {
      nlen = Get_DLT645_Data_For_Disp(item,(u8*)buff,(u8*)start, DIS_BUF_LEN);
  }
  nlen=(nlen>maxlen)?maxlen:nlen;
  mem_cpy(dst, start, nlen, dststart, maxlen);
  mem_set((u8*)dst + nlen, 0, maxlen - nlen, dststart, maxlen);
  
  if(CHECK_STRUCT_VAR(_Dis_GetData_Buf)==0)
     ASSERT(A_WARNING,0);
  
  if(sign==0)
    return nlen;
    
  return (sign);
}

// �ж��Ƿ�ͣ��
bool poweroff (void) {
    return  (Get_MeterPowerStatus_PUCK());
}

// �ж��Ƿ�Ϊʵʱ����
bool rtvalue (item_t item) 
{
  if(DI_COMM_BAUD0==item || DI_COMM_BAUD1==item)
     return 1;
     
  return (S_RAM == Get_DLT645_Data_Storage_Type(item));
}

/********************************************************************************
PUCK:
�������ܣ��ڿ�����������sram��������ʼ��
��ڣ�
���أ�
********************************************************************************/
void lcdinit (void) {
    u8     stat,Err;
    u8     cycle;
    s16    temp;
    offs_t numb;

    temp=Read_Storage_Data(VARHMODE1,&stat, &stat, sizeof(stat),&Err);
    if(!temp)
      stat = 0x03;   //Ĭ�ϲ���0x03���޹����1-------PUCK_LCD
    varhmode1 = stat;
    
    temp=Read_Storage_Data(VARHMODE2,&stat, &stat, sizeof(stat),&Err);
    if(!temp)
      stat = 0x0c;    //Ĭ�ϲ���0x0c���޹����2-------PUCK_LCD
    varhmode2 = stat;
    
    cycle = 0;
    temp=Read_Storage_Data(ROLLCYCLE,&cycle, &cycle, sizeof(cycle),&Err); 
    if((!temp)||(cycle<5)||(cycle>180))  //��СΪ5�룬���180�룬ѭ��ʱ��------PUCK_LCD
      cycle=5;
    rollcycle = (u8)Bcd2Hex((u8*)&cycle, 1);     
    
    numb=0;
    temp=Read_Storage_Data(NUMBMODEA,&numb, &numb, sizeof(numb),&Err); 
    if((!temp) ||(!numb))
      numb=0x13;   //BCD��,1�ֽ�------PUCK_LCD
    MODE_A_NUM = (u16)Bcd2Hex((u8*)&numb, 1);
    
    numb=0;
    temp=Read_Storage_Data(NUMBMODEB,&numb, &numb, sizeof(numb),&Err); 
     if((!temp)||(!numb))
      numb=0x14;   //BCD�룬2�ֽ�------PUCK_LCD
    MODE_B_NUM = (u16)Bcd2Hex((u8*)&numb, 2);
}

// A������ʱ��
s16 rolltime () {
    return (rollcycle);
}

// ����Һ������
void lcdlight (u8 stat) {
    if (stat > 0) {
        Turn_Light_On();
    } else {
        Turn_Light_Off();
    }
}


// ��ȡ״̬��
stat_t getstat (void) 
{
    static INT8U disflag=0;
    static INT32U SecTimerBak=0;
  
    u16 data;
    stat_t stat;
    stat.bit1maps = 0;
    stat.bit2maps = 0;
    
    data = 0;
    
    if(0==disflag)
    {
      SecTimerBak=Sec_Timer_Pub;
      disflag=1;
    }
    else if(disflag==1 &&Sec_Timer_Pub-SecTimerBak<50)  //�¼��ж����ƻ�û������
      Init_Event_DIS_PUCK();
    else
      disflag=2;
    
    //getdata(DI_LOW_VOL, &data, &data, sizeof(data));
    data=Meter_Run_Status.Volt_LossMiss.Byte;
    stat.loss_voltage  = (data&0x07)|(data >> 0x4); ///< ��ѹ״̬(ʧѹ/����)(Ua,Ub,Uc)
    data = 0;
    
    //getdata(0xC044, &data, &data, sizeof(data));            //12ms
    data=Meter_Run_Status.Grid_Stat.Byte;
    stat.over_voltage  = (data >> 0x4); ///< ��ѹ(Ua,Ub,Uc)(��˸)
    data = 0;
       
    //getdata(0xC042, &data, &data, sizeof(data));            //12ms
    data=Meter_Run_Status.Meter_Stat3.Byte;
    stat.loss_current  = (data >> 0x4); ///< ����״̬(ʧ��/ȫʧ��)(Ia,Ib,Ic)
    stat.volt_reverse  = (data>>0x1); ///< ��ѹ"������"(��˸)
    data = 0;
    
    //getdata(DI_CURRENT_QUADRANT, &data, &data, sizeof(data));
    data=Meter_Run_Status.NegCurr_Qudrant.Byte;
    stat.Cur_reverse  = (data >> 0x4); ///< ����������(-Ia,-Ib,-Ic)(��˸)
    stat.stat_communi  = Get_Curr_ComType_PUCK(LUCK); ///< ͨ��״̬(RS1,RS2,����)(����)

    data = 0;
    //getdata(0xC043, &data, &data, sizeof(data));       //13ms
    data=Meter_Run_Status.Meter_Stat4.Byte;
    stat.cell_lowvolt  = (data >> 0x5) | (data >> 0x2); ///< ��ص�ѹ��(����)
    
    data = 0;
    //getdata(DI_METER_PERIPHERY, &data, &data, sizeof(data));
    data=Meter_Run_Status.Key_Event.Byte;
    stat.switch_opened = (data & 0x1); ///< ��̼���(����)
    stat.fac_status  = (data>>1);    // ����ģʽ(����)
    stat.reset_demand  = (data>>2); ///< ������λ(����)
    stat.meter_locked  = (data>>3); ///< �������(����)
    stat.event_warning = (data>>4); ///< �¼��澯(��˸)
    stat.jumper_short  = (data>>5);    // ���߶̽�(��˸)
    
    data = 0;
    //getdata(DI_MODULE_STATUS, &data, &data, sizeof(data));
    data=Meter_Run_Status.Comm_Status.Byte;
    stat.status_online = (data &  0x1); ///< ͨѶģ������ָʾ(����)
    stat.signal_scale  = (data >> 0x1); ///< ͨѶģ���ź�ǿ��ָʾ(����)
    data = 0;
    //getdata(0xCA14, &data, &data, sizeof(data));   //18ms
    data=Rate_Status.Status[0].Byte+Rate_Status.Status[1].Byte*((INT16U)256);
    stat.status_tariff = (data >> 0x8); ///< ��ʾ��ǰ���ʣ�"��, ��, ƽ, ��, T5, ...Tx",
    stat.num_tariff = (data&0x03); ///��ʾ����ʱ��1����ʱ�Σ�2����ʱ��",
    
    
    stat.CalMeter=Meter_Run_Status.Key_Event.Bit.Bit6;
    return (stat);
}

// ��ȡģʽ��
mode_t getmode (void) {
    mode_t mode;
    mode.bit0 = Mode_Word.Mode[1].Bit.Bit0;
    mode.bit1 = Mode_Word.Mode[3].Bit.Bit1;
    mode.bit2 = Mode_Word.Mode[2].Bit.Bit2;
    mode.bit3 = Mode_Word.Mode[3].Bit.Bit3;
    mode.bit4 = Mode_Word.Mode[3].Bit.Bit4;
    mode.bit5 = Mode_Word.Mode[3].Bit.Bit5;
    mode.bit6 = Mode_Word.Mode[7].Bit.Bit6;
    mode.bit7 = Mode_Word.Mode[3].Bit.Bit7;
    return (mode);
}

// ������ʾԪ�أ�������ʾ������Ҫ��˸��
void lcd_total (u8 flg) { ///< ��ʾ"��",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_ZONG);

}

void lcd_phase (u8 flg) { ///< ��ʾ"A/B/C/N��",
    if (flg & 0x01) {
        SetOnDevice_PUCK(S_A);
    }
    if (flg & 0x02) {
        SetOnDevice_PUCK(S_B);
    }
    if (flg & 0x04) {
        SetOnDevice_PUCK(S_C);
    }
    //��N����ʾ��ABCB
    /*
    if (flg & 0x08) {
        SetOnDevice_PUCK(S_N);
    }
    */
}

void lcd_voltage (u8 flg) { ///< ��ʾ"��ѹ",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_DIAN);
    SetOnDevice_PUCK(S_YA);

}

void lcd_current (u8 flg) { ///< ��ʾ"����",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_DIAN);
    SetOnDevice_PUCK(S_LIU);

}

void lcd_positive (u8 flg) { ///< ��ʾ"����",
    if (flg == 0) {
        return;
    }
    /*
    if (getmode().bit4) {
        SetOnDevice_PUCK(S_SHURU);
    } else {
        SetOnDevice_PUCK(S_ZHENG);
        SetOnDevice_PUCK(S_XIANG);
    }
    */
     SetOnDevice_PUCK(S_ZHENG);
     SetOnDevice_PUCK(S_XIANG);

}

void lcd_negative (u8 flg) { ///< ��ʾ"����",
    if (flg == 0) {
        return;
    }
    /*
    if (getmode().bit4) {
        SetOnDevice_PUCK(S_SHUCHU);
    } else {
        SetOnDevice_PUCK(S_FAN);
        SetOnDevice_PUCK(S_XIANG);
    }
    */
    SetOnDevice_PUCK(S_FAN);
    SetOnDevice_PUCK(S_XIANG);

}

void lcd_reactive (u8 flg) { ///< ��ʾ"�޹�",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_WU);
    SetOnDevice_PUCK(S_GONG);

}

void lcd_active (u8 flg) { ///< ��ʾ"�й�",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_YOU);
    SetOnDevice_PUCK(S_GONG);

}

void lcd_power (u8 flg) { ///< ��ʾ"����",
    if (flg == 0) {
        return;
    }
    /*
    SetOnDevice_PUCK(S_GONG);
    SetOnDevice_PUCK(S_LV);
    */
    SetOnDevice_PUCK(S_GONGLV);
}

void lcd_factor (u8 flg) { ///< ��ʾ"����",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_COS);
    SetOnDevice_PUCK(S_FAI);

}

void lcd_angle (u8 flg) { ///< "���",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_FAI);
}

void lcd_energy (u8 flg) { ///< ��ʾ"����",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_DIAN);
    SetOnDevice_PUCK(S_LIANG);

}

void lcd_demand (u8 flg) { ///< ��ʾ"����",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_XU);
    SetOnDevice_PUCK(S_LIANG);

}

void lcd_time (u8 flg) { ///< ��ʾ"ʱ��",
    if (flg == 0) {
        return;
    }
    /*
    SetOnDevice_PUCK(S_SHI);
    SetOnDevice_PUCK(S_JIAN);
    */
    SetOnDevice_PUCK(S_SHIJIAN);
    
}

void lcd_charge (u8 flg) { ///< ��ʾ"���",
    if (flg == 0) {
        return;
    }
    /*
    SetOnDevice_PUCK(S_DIAN);
    SetOnDevice_PUCK(S_FEI);
    */
}

void lcd_lostvolt  (u8 flg) { ///< "ʧѹ",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_SHI1);
    SetOnDevice_PUCK(S_YA);
}

void lcd_lostcurt  (u8 flg) { ///< "ʧ��",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_SHI1);
    SetOnDevice_PUCK(S_LIU);
}

void lcd_periods   (u8 flg) { ///< "ʱ��"
    if (flg == 0) {
        return;
    }
    /*
    SetOnDevice_PUCK(S_SHI);
    SetOnDevice_PUCK(S_DUAN);
    */
}

void lcd_feerate   (u8 flg) { ///< "����", 
    if (flg == 0) {
        return;
    }
    /*
    SetOnDevice_PUCK(S_FEI);
    SetOnDevice_PUCK(S_LV);
    */
    SetOnDevice_PUCK(S_FEIlLV);
}

void lcd_thismonth (u8 flg) { ///< ��ʾ"����",
    if (flg == 0) {
        return;
    }
    /*
    SetOnDevice_PUCK(S_BEN);
    SetOnDevice_PUCK(S_YUE);
    */
    SetOnDevice_PUCK(S_DANGQIAN);

}

void lcd_lastmonth (u8 flg) { ///< mode4.bit5 ? "����", "������" : "��1��", "��2��";
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_SHANG);
    if (getmode().bit5) {
        if (flg == 1) {
            SetOnDevice_PUCK(S_YUE);
            return;
        }
        if (flg == 2) {
            SetOnDevice_PUCK(S_SHANG);
            SetOnDevice_PUCK(S_YUE);
            return;
        }
    }
    if (flg > 9) {
        SetOnDevice_PUCK(S_SHIYUE);
    }
    SetOnLED8Device_PUCK(N_LED(1), '0' + (flg % 10));
    SetOnDevice_PUCK(S_YUE);
}


void lcd_assemble (u8 flg) 
{
    static u8 flag=0,num=0,SwitFlg=0;
    static u8 stat;
    
    
    if (flg > 0)  //�޹����ģʽ�֣���˸
    {
      num++;
      if(num>SECOND_2(1))
      {        
        if(SwitFlg!=flg)
          flag=0;
        
        SwitFlg=flg;
        
        stat = (flg == 1) ? varhmode1 : varhmode2;
        stat&=0x0f;
        
         // ��Һ��ֻ֧����ʱ��
        switch(stat&0x0f)
        {
          case 3:
            stat=9;
            break;
          case 5:
            stat=5;
            break;
          case 9:
            stat=3;
            break;
          case 6:
            stat=6;
            break;
          case 10:
            stat=10;
            break;
          case 12:
            stat=6;
            break;  
         }

        flag=(flag&stat)^stat;  //��˸
        stat = flag; 
        num=0;
      }
    }
    else                  //�й�
    {
      getdata(DI_CURRENT_QUADRANT, &stat, &stat, sizeof(stat));
      if(stat&0x0f)   //1/2/4/8
      {
          // ��Һ��ֻ֧����ʱ��
          switch(stat&0x0f)   //�������߳���
          {
            case 1:
              stat=14;
              break;
            case 2:
              stat=7;
              break;
            case 4:
              stat=11;
              break;
            case 8:
              stat=13;
              break;   
          default:
            return;
         }
      }
      else
        return ;
    }
    if (stat & 0x01) {
        SetOnDevice_PUCK(S_XIANGXIAN1);
    }
    if (stat & 0x02) {
        SetOnDevice_PUCK(S_XIANGXIAN2);
    }
    if (stat & 0x04) {
        SetOnDevice_PUCK(S_XIANGXIAN3);
    }
    if (stat & 0x08) {
        SetOnDevice_PUCK(S_XIANGXIAN4);
    }
}

void lcd_quadrant (u8 flg) { ///< ��ʾ"I����",
    switch (flg) {
        case 0x04 : {
           SetOnDevice_PUCK(S_I3);
           SetOnDevice_PUCK(S_V);
           break;
        }
        case 0x03 : {
           SetOnDevice_PUCK(S_I3);
        }
        case 0x02 : {
           SetOnDevice_PUCK(S_I2);
        }
        case 0x01 : {
           SetOnDevice_PUCK(S_I1);
           break;
        }
    }
}

void lcd_tariff (u8 flg) { ///< ��ʾ"����Tx",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_FEIlLV);
    SetOnLED8Device_PUCK(N_LED(2), '0' + (flg % 10));
}

void lcd_times (u8 flg) { ///< ��ʾ"��XX��",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_SHANG);
    if (flg > 9) {
        SetOnDevice_PUCK(S_SHIYUE);
    }
    SetOnLED8Device_PUCK(N_LED(1), '0' + (flg % 10));
    SetOnDevice_PUCK(S_CI);
}

// ʮ������ת�ַ���
static const char hex2cha[] = {
    '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', 'A', 'b', 'C', 'd', 'E', 'F',
};

// ��ʾ��λ"kMVAWvarHhz",
const char* lcd_units (const char* s) {
    const char* p;
    for (p = s + strlen(s); p >= s; --p) {
        switch (*p) {
            case '2': {
                break;
            }
            case 'k': {
                SetOnDevice_PUCK(S_M_55);
                SetOnDevice_PUCK(S_M_56);
                break;
            }
            case 'M': {
                SetOnDevice_PUCK(S_M_55);
                SetOnDevice_PUCK(S_M_57);
                break;
            }
            case 'V': {
                SetOnDevice_PUCK(S_M_58);
                break;
            }
            case 'A': {
                SetOnDevice_PUCK(S_M_61);
                SetOnDevice_PUCK(S_M_62);
                SetOnDevice_PUCK(S_M_63);
                SetOnDevice_PUCK(S_M_64);
                break;
            }
            case 'W': {
                SetOnDevice_PUCK(S_M_58);
                SetOnDevice_PUCK(S_M_59);
                SetOnDevice_PUCK(S_M_60);
                SetOnDevice_PUCK(S_M_61);
                SetOnDevice_PUCK(S_M_62);
                break;
            }
            case 'H': {
                SetOnDevice_PUCK(S_M_67);
                SetOnDevice_PUCK(S_M_68);
                break;
            }
            case 'h': {
                SetOnDevice_PUCK(S_M_67);
                 break;
            }
            case 'z': {
                SetOnDevice_PUCK(S_M_69);
                break;
            }
            case 'v': {
                SetOnDevice_PUCK(S_M_60);
                SetOnDevice_PUCK(S_M_62);
                break;
            }
            case 'a': {
                SetOnDevice_PUCK(S_M_64);
                SetOnDevice_PUCK(S_M_65);
                break;
            }
            case 'r': {
                SetOnDevice_PUCK(S_M_66);
                break;
            }
            case 'o': {
                SetOnDevice_PUCK(S_DU);
                break;
            }
            case '|': {
                return (--p);
            }
        }
    }
    return (p);
}

// ������ʾ�ӿڣ������ַ�����ʽ
void lcd_value (const char* s) {
    typedef struct {
        u16 id;
        u16 dp1;
        u16 dp2;
    } addr_t;

    static const addr_t addr[] = {
        {N_LED(12), D_( 0), D_( 0)}, {N_LED(11), D_( 0), D_( 0)}, {N_LED(10), D_(10), D_(11)},
        {N_LED( 9), D_( 9), D_( 0)}, {N_LED( 8), D_( 8), D_( 7)}, {N_LED( 7), D_( 0), D_( 0)},
        {N_LED( 6), D_( 4), D_( 4)}, {N_LED( 5), D_( 0), D_( 0)}, {N_LED( 4), D_( 4), D_( 4)},
        {N_LED( 3), D_( 0), D_( 0)}
    };
    s16 n = 0;
    for (const char* p = lcd_units(s); p >= s   //��ʾ�ָ���|����ĵ�λ������ȡ�ָ��ǰ���λ��--------PUCK
        && (n < sizeof(addr) / sizeof(addr_t)); --p) {
        switch (*p) {
            case '?': {
                break;
            }
            case ' ': {
                n++;
                break;
            }
            case '.': {
                SetOnDevice_D_PUCK(addr[n].dp1);
                break;
            }
            case ':': {
                SetOnDevice_D_PUCK(addr[n].dp1);
                SetOnDevice_D_PUCK(addr[n].dp2);
                break;
            }
            default: {
                SetOnLED8Device_PUCK(addr[n++].id, *p);     //�����ַ���������Ӧ��LED---------PUCK
            }
        }
    }
}

typedef struct {
    u32 low;
    u32 high;
    u32 higher;
} dval_t;

bool isnull (dval_t* val) {
    return ((val->low == 0) && (val->high == 0)&& (val->higher == 0));
}

char dshift (dval_t* val) {
	  u8 bits = val->low % 16;
	  val->low = (val->high << 28) | (val->low >> 4);    //���°��ֽ�---------PUCK
	  val->high >>= 4;
		return hex2cha[bits];
}

//bit��ʾ��ʽ
char bshift (dval_t* val) 
{
  u8 bits=val->low&0x01;
  val->low=(val->low)>>1;
  return hex2cha[bits];
}

/********************************************************************************
PUCK:
�������ܣ������ʾ���ݵ�����
��ڣ�
     type-----ģʽ����;curs-----���λ��
���أ�
********************************************************************************/
// �����ʾ���ݵ�����
// mode4.bit3 1 "��λ��0" : Ϊ0��"��λ����0";
// ����[Э�����ʾ]С��λ[��Χ: 2��3]
// ����&����[��ʾ]С��λ[��Χ: 2��3��4; Э��̶�Ϊ4]
void lcd_data (item_t item, const char* s,u8 singpos) 
{
  INT8S frmt[32];

  if(strlen(s)<=sizeof(frmt))
    strcpy(frmt,(INT8S *)s);
  else
  {
    ASSERT(A_WARNING,0);
    return ;
  }

 //������ʾλ�����й����ܣ��޹����� HUCK��3λС��������5���ֽڣ���ʾ���� SHOW_ENERG_BIT����ʾ
 //������ʾλ�����й�/���ڹ��ʣ���ʾʱȡ��׼ID��HUCK����4λ����׼Ҳ��4λ���޹������б�׼ID(2λ)�������3λ
    if(SHOW_ENERG_BIT == 3 && ((item&0xf000)==0x6000 || (item&0xf000)==0x9000|| (item&0xff00)==0xE700)) 
    {
      if(strstr((const INT8S *)frmt, "kvarh"))  //������ʾλ�������2λ
      {          
         strcpy(frmt,"XXXXXX#.###|kvarh");
      }  
      if(strstr((const INT8S *)frmt, "kWh"))  //������ʾλ�������պ�������
      {
           strcpy(frmt,"XXXXXX#.###|kWh");
      } 
    }
     //������ʾ���������ñ�Ĭ������ʾ
   if (strstr((const INT8S *)frmt, "tm")) 
   {
        if (!getmode().bit6)  //�����͸������ߵ�ʱ�귽ʽ��HUCK�ܸ��꣬5�ֽڣ�4�ֽ�ʱ(��ʾ������)����Ҫ����-----09-03-12
        {
          strcpy(frmt,"##:##:##:##:##|tm");
        }
    }

    if(((item>=0xC331)&&(item<=0xC36E))|| ((item>=0xCB21)&&(item<=0xCB6E)))  // ��1/2�׷��ʵ�n��ʱ�α��nʱ����ʼʱ�ּ�����ʺ�
    {
       strcpy(frmt,"##-##:##|");
    }

    if (poweroff() && getmode().bit0 && (item == 0xC010)) //�͹�����ʾʱ��
    {
        item = DI_POWER_DOWN_TIME;
        strcpy(frmt,"##:##:##:##:##|tm");
    } 
    
    u8   NegFlag=0;
    static s16    _dlen = 0;
    static item_t _item = 0;
    static dval_t _dval = {0,0,0};
    //��ʾ��Ŀ�����ı�;�ϴλ�ȡ����ȷ����Ҫ�ٴλ�ȡ;��SRAM���ݣ����������޸�-------------��ʱ��ȡ��ʾ����
    if((_item!= item)||(_dlen == 0)||rtvalue(item)||Get_Para_Modi_Flag())
    { 
        _dlen = getdata(item, &_dval, &_dval, sizeof(_dval));     //��ȡ��Ҫ��ʾ�ı�������
        _item = item;
    }    
    if (_dlen == 0) {
        lcd_value("rEAd Error|");
        return;
    }

    if(_dlen>0 && singpos==4)  //��������
    {
      if(_dval.high&0x00000080)         //���λλ����λ
      {
        _dlen=-1;
        _dval.high=_dval.high&0xffffff7f;         //ȥ�����λλ����λ    
      }      
    }
    char   buff[MAXDLEN] = {0};
    size_t nlen = strlen(frmt);
    dval_t dval = _dval;
    mem_cpy(buff, (char*)frmt, nlen, buff, sizeof(buff));    //����ʾ��ʽ������buff---------PUCK
    for (char* next = buff + nlen; next >= buff; --next)   //�������
    {
        switch (*next) 
        {
            case 'X':    //���λ��ʶ
                if (!getmode().bit3 &&isnull(&dval))   //��λ����0���ҵ�ǰ��������0�ˣ��ÿո����-----PUCK
                {
                  if(-1==_dlen&&0==NegFlag)   //��ʾ����
                  {
                    *next = '-';
                    NegFlag=1;
                  }
                  else
                    *next = ' ';
                } 
                else    //��λ�貹0������ʵ����д 
                {
                    *next = dshift(&dval);  //��ȡ��ʾ�İ���ַ����������buff--------PUCK
                }
                break;
            case '#': 
                *next = dshift(&dval);      //��ȡ��ʾ�İ���ַ����������buff--------PUCK
                break;
               
            case 'B':
                *next=  bshift(&dval);
                break;
            case '?': 
                dshift(&dval);
                 break;
        }
    }
    lcd_value(buff); //��ʱbuff�����ݸ�ʽ��-12.3:-4|��λ
}

/********************************************************************************
PUCK: �����ʾ���������
�������ܣ�������ʾģʽ,��ģʽƫ�ƣ���ȡ�������ʾԪ�ص���Ϣ
��ڣ�
     type-----ģʽ����;offs-----��ģʽ����ʾ����Ŀ˳��
���أ�
********************************************************************************/
void lcd_code (code_t code, curs_t curs,u8 dlen) 
{
    typedef struct {
        u16 id;
        u16 dp;
    } addr_t;

    static const addr_t addr[] = {
        {N_LED(21), D_( 0)}, {N_LED(20), D_(20)}, 
        {N_LED(19), D_(19)}, {N_LED(18), D_(22)},
        {N_LED(17), D_(21)}, {N_LED(16), D_( 0)}, 
     // {N_LED(15), D_( 0)}, {N_LED(14), D_( 0)},
    };
    
    char ch = ' ';
    static u8 flag = 0;
    for (curs_t n = 0; n < sizeof(addr) / sizeof(addr_t); ++n) 
    {
      if(curs==-1)  //����˸
      {
        if(n>=dlen)
          break;
        ch = hex2cha[code % 16];
        code /= 16;
        if((n>=2)&&(n%2==0))  //��ʾ��ʽ00.01
          SetOnDevice_D_PUCK(addr[n].dp);
      }
      else  //��˸
      {
        if ((n == curs) && (flag ^= 1)) //�ǹ������λ�ã�����ʾ��������´��ٵ������γ���˸Ч��----------PUCK
        {
            ch = ' ';
            code /= 16;
        } 
        else if (code > 0)              //����ʾ�������----------PUCK
        {
            ch = hex2cha[code % 16];
            code /= 16;
        } else 
        {
            ch = '0';
        }
      }
      SetOnLED8Device_PUCK(addr[n].id, ch);
    }
}

// �����ʾ����������
void lcd_mode (u8 type) {
    switch (type) {
        case modeA: {
            SetOnDevice_PUCK(S_K1);
            break;
        }
        case modeB: {
            SetOnDevice_PUCK(S_K2);
            break;
        }
        default : {
            SetOnDevice_PUCK(S_K3);
            break;
        }
    }
}

// ��ʾ����������
void lcd_update (void) 
{
  UpdataLcdShow();
}

// �����ʾ�¼�״̬
void lcd_events (void) 
{
  static stat_t flag;
  static u8 num=0;
  
  stat_t stat = getstat();
    
  stat.event_warning &= getmode().bit1; // mode4.bit1 ,1-------�澯"��ʾ" :0------ �澯"�ر�";
  flag.bit1maps &= stat.bit1maps;
  flag.bit2maps &= stat.bit2maps;
  num++;
 
  if(num>=SECOND_2(1))
  {
      num=0;
      flag.bit1maps ^= stat.bit1maps;     //ȡ�����γ���˸Ч��------PUCK
      flag.bit2maps ^= stat.bit2maps;     //ȡ�����γ���˸Ч��------PUCK
  }
  
  //��ѹ�޹�ѹ������״̬(����)
  if(!GET_BIT(stat.loss_voltage,0)&& !GET_BIT(stat.over_voltage,0))  //��ûʧѹҲû��ѹ����ѹ����,����
    SetOnDevice_PUCK(S_Ua);
  if(!GET_BIT(stat.loss_voltage,0)&&GET_BIT(stat.over_voltage,0)&& !GET_BIT(flag.over_voltage,0))  //ûʧѹ,����ѹ����˸
  {
      SetOnDevice_PUCK(S_Ua_UP);
      SetOnDevice_PUCK(S_Ua);
  }
  
  if(!GET_BIT(stat.loss_voltage,1)&& !GET_BIT(stat.over_voltage,1))  //��ûʧѹҲû��ѹ����ѹ����,����
    SetOnDevice_PUCK(S_Ub);
  if(!GET_BIT(stat.loss_voltage,1)&& GET_BIT(stat.over_voltage,1)&& !GET_BIT(flag.over_voltage,1))  //ûʧѹ,����ѹ����˸
  {
      SetOnDevice_PUCK(S_Ub_UP);
      SetOnDevice_PUCK(S_Ub);
  }
      
  if(!GET_BIT(stat.loss_voltage,2)&& !GET_BIT(stat.over_voltage,2))  //��ûʧѹҲû��ѹ����ѹ����,����
    SetOnDevice_PUCK(S_Uc);
  if(!GET_BIT(stat.loss_voltage,2)&& GET_BIT(stat.over_voltage,2)&& !GET_BIT(flag.over_voltage,2))  //ûʧѹ,����ѹ����˸
  {
      SetOnDevice_PUCK(S_Uc_UP);
      SetOnDevice_PUCK(S_Uc);
  }

  //�������ࣺ��ʾ����Ϩ��--------------PUCK
  if (stat.Cur_reverse&0x01 && !GET_BIT(stat.loss_current,0))  //A�෴����,��û��ʧ��
      SetOnDevice_PUCK(S_Ia_);
  if (stat.Cur_reverse&0x02 && !GET_BIT(stat.loss_current,1))  //B�෴����,��û��ʧ��
      SetOnDevice_PUCK(S_Ib_);
  if (stat.Cur_reverse&0x04 && !GET_BIT(stat.loss_current,2))  //C�෴����,��û��ʧ��
      SetOnDevice_PUCK(S_Ic_);
  
   //����״̬(����������˸)
  if(!GET_BIT(stat.loss_current,0)&&!GET_BIT(stat.Cur_reverse,0))//û��ʧ������û�з��࣬����
      SetOnDevice_PUCK(S_Ia);
  if(!GET_BIT(stat.loss_current,0)&&GET_BIT(stat.Cur_reverse,0)&& !GET_BIT(flag.Cur_reverse,0))//û��ʧ�����ҷ��࣬��˸
      SetOnDevice_PUCK(S_Ia);
  
  if(!GET_BIT(stat.loss_current,1)&&!GET_BIT(stat.Cur_reverse,1))//û��ʧ������û�з��࣬����
      SetOnDevice_PUCK(S_Ib);
  if(!GET_BIT(stat.loss_current,1)&&GET_BIT(stat.Cur_reverse,1)&& !GET_BIT(flag.Cur_reverse,1))//û��ʧ�����ҷ��࣬��˸
      SetOnDevice_PUCK(S_Ib);
  
  if(!GET_BIT(stat.loss_current,2)&&!GET_BIT(stat.Cur_reverse,2))//û��ʧ������û�з��࣬����
      SetOnDevice_PUCK(S_Ic);
  if(!GET_BIT(stat.loss_current,2)&&GET_BIT(stat.Cur_reverse,2)&& !GET_BIT(flag.Cur_reverse,2))//û��ʧ�����ҷ��࣬��˸
      SetOnDevice_PUCK(S_Ic);
  

  ///< ��ص�ѹ��(����)
  if (flag.cell_lowvolt & 0x01) {  //ʱ�ӵ��----��˸
      SetOnDevice_PUCK(S_BAT2);
  }
  if (flag.cell_lowvolt & 0x02) {  //�͹��ĵ��----��˸
      SetOnDevice_PUCK(S_BAT1);
  }
  
  if (flag.cell_lowvolt & 0x04)
  {
    /*    
    SetOnDevice_PUCK(S_BAT3);
   */
  }
  ///< ͨ��״̬(RS1,RS2,����)(����)
  if (stat.stat_communi &(1<<CHANEL_IRDA)) 
  {
      SetOnDevice_PUCK(S_HONGWAI);
  }
  
  if (stat.stat_communi &(1<<CHANEL_485_1)) 
  {
      SetOnDevice_PUCK(S_RS1);
  }
  
  if (stat.stat_communi &(1<<CHANEL_485_2)) 
  {
      SetOnDevice_PUCK(S_RS2);
  }
  
#ifdef CHANEL_MOUDEL
  if (stat.stat_communi &(1<<CHANEL_MOUDEL)) 
  {
    /*  
      SetOnDevice_PUCK(S_ARROW_LEFT);
      SetOnDevice_PUCK(S_ARROW_RIGHT);
    */
    SetOnDevice_PUCK(S_BASE_TOWER);    
  }
#endif
  
  ///< ��ѹ"������"(��˸)
  if (flag.volt_reverse > 0x00)
  {
      SetOnDevice_PUCK(S_NIXIANGXU);
  }
  ///< �¼��澯(��˸)
  if (flag.event_warning & 0x01) 
  {
      SetOnDevice_PUCK(S_LIGHT);
  }
  ///< ��̼���(����)
  if (stat.switch_opened & 0x01) 
  {
      SetOnDevice_PUCK(S_BUTTON);
  }    
  //����ģʽ(����)
  if (stat.fac_status & 0x01) 
  {
      SetOnDevice_PUCK(S_HOUSE);
  }
  ///< ������λ(����)
  if (stat.reset_demand & 0x01) 
  {
      SetOnDevice_PUCK(S_KEY);
  }    
    
  //���߶̽�(��˸)
  if (flag.jumper_short & 0x01) 
  {
      SetOnDevice_PUCK(S_SHOT);
  }
  ///< �������(����)
  if (stat.meter_locked & 0x01) 
  {
      SetOnDevice_PUCK(S_LOCK);
  }
  ///< ͨѶģ������ָʾ(����)
  if (stat.status_online & 0x01)
  {
      //SetOnDevice_PUCK(S_CIRCLE);
    SetOnDevice_PUCK(S_BASE_TOWER);
  }
  ///< ͨѶģ���ź�ǿ��ָʾ
  switch (stat.signal_scale) 
  {   
    case 0x00 :
          break;
    case 0x01 :
          SetOnDevice_PUCK(S_CSQ1);
          break;
    case 0x02 :
          SetOnDevice_PUCK(S_CSQ2);
          SetOnDevice_PUCK(S_CSQ1);
          break;
    case 0x03 :
          SetOnDevice_PUCK(S_CSQ3);
          SetOnDevice_PUCK(S_CSQ2);
          SetOnDevice_PUCK(S_CSQ1);
          break;      
      default:
          SetOnDevice_PUCK(S_CSQ4);
          SetOnDevice_PUCK(S_CSQ3);
          SetOnDevice_PUCK(S_CSQ2);
          SetOnDevice_PUCK(S_CSQ1);
         break;
  }
  ///< ��ʾ��ǰ���ʣ�"��, ��, ƽ, ��, T5, ...Tx",
  switch (stat.status_tariff) 
  {
      case 0x00 : {
          break;
      }
      case 0x01 : {
          SetOnDevice_PUCK(S_JIAN1);
          break;
      }
      case 0x02 : {
          SetOnDevice_PUCK(S_FENG);
          break;
      }
      case 0x03 : {
          SetOnDevice_PUCK(S_PING);
          break;
      }
      case 0x04 : {
          SetOnDevice_PUCK(S_GU);
          break;
      }
      default : {
          SetOnDevice_PUCK(S_TT);
          SetOnLED8Device_PUCK(N_LED(13), '0'+stat.status_tariff);
          break;
      }
  }
  
  ///��ʾ����ʱ��1����ʱ�Σ�2����ʱ��",
  if(1==stat.num_tariff)
    SetOnDevice_PUCK(S_1);
  if(2==stat.num_tariff)
    SetOnDevice_PUCK(S_2);
  
  if(Read_Event_Status(ID_METER_ADDR_EN))
    SetOnDevice_PUCK(S_SHOT);
  
  //if (flag.CalMeter & 0x01)   //����δУ����˸С����
  //  SetOnDevice_PUCK(S_BASE_TOWER);
  
  if(Read_Event_Status(ID_EVENT_UP_COVER_OPEN))  //�϶˸�
    SetOnDevice_PUCK(S_UPCOVERP);

  if(Read_Event_Status(ID_EVENT_DOWN_COVER_OPEN))  //�϶˸�
    SetOnDevice_PUCK(S_DOWNCOVERP);
  
}
#endif
