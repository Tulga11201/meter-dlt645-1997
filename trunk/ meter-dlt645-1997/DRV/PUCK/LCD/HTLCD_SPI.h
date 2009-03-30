#ifndef HTLCDspi_h
#define HTLCDspi_h

#ifndef HTLCDSPI_C
#define HTLCDSPI_EXT extern
#else
#define HTLCDSPI_EXT
#endif


#define		SYS_DIS_CMD	0x0800	//ֻȡ��12λ
#define		SYS_EN_CMD      0x0802	//ֻȡ��12λ
#define		LCD_OFF_CMD	0x0804	//ֻȡ��12λ
#define		LCD_ON_CMD	0x0806	//ֻȡ��12λ
#define		RC_32K_CMD	0x0830	//ֻȡ��12λ
#define		WRITE_ID	0x0280	//��7λ���ַ����ֻ�����10λ


#define HTLCD_SYS_EN()    HTLCDWriteACommand(SYS_EN_CMD)  //������
#define HTLCD_SYS_DIS()   HTLCDWriteACommand(SYS_DIS_CMD)  //��������ƫѹ������
#define HTLCD_LCD_ON()    HTLCDWriteACommand(LCD_ON_CMD)  //��LCD��ʾ
#define HTLCD_LCD_OFF()   HTLCDWriteACommand(LCD_OFF_CMD)  //��LCD��ʾ
#define HTLCD_RC_32K()    HTLCDWriteACommand(RC_32K_CMD)  //ѡ��Ƭ��RC����

	

//#define SET_BIT  Bit_SET
//#define CLR_BIT  Bit_RESET

#define HTLCD_CS_0        LCD_CS_0
#define HTLCD_CS_1        LCD_CS_1

#define HTLCD_CLK_0       LCD_WR_0
#define HTLCD_CLK_1       LCD_WR_1

#define HTLCD_DATA_0      LCD_DATA_0
#define HTLCD_DATA_1      LCD_DATA_1


#define Turn_Light_On()          LCD_BACK_LIGHT_1
#define Turn_Light_Off()         LCD_BACK_LIGHT_0




void	HTLCDWriteACommand(INT32U command);
void	HTLCD_WRITE_MODE(INT8U LCD_RAM_ADDR);
void	HTLCD_SEND_DATA(INT8U LCD_RAM_ADDR, INT8U *DATA_ADDR,INT32U DATA_LENGTH);
void    Init_HTLCD_Mode(INT32U Mode);
void	HTLCDWriteMultiData(INT8U LCD_RAM_ADDR,INT8U *DATA_ADDR,INT32U	DATA_LENGTH);
void    InitHTLCDIOPort(void);
void    Clr_Screen_PUCK(void);
#endif
