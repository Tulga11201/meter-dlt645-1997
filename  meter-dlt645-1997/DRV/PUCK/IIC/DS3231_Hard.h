#ifndef HARD_DS3231_H
#define HARD_DS3231_H

//  osc =8(7.3728)
/*��ʼ��ʱ��IIC�Ľӿ�����*/
void init_DS3231(void);
/*
��ds3231ʱ�䣬���������ֵ��{�룬�֣�ʱ�����ڣ��գ��£���}
*/
INT8U DS3231_Read_Buf(INT8U addr,INT8U Len,INT8U *Dst);
INT8U DS3231_Write_Buf(INT8U addr,INT8U Len,INT8U *Src);

#endif