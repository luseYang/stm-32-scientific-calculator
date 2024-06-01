#ifndef __LCD1602_H
#define __LCD1602_H

#include "stm32f10x.h"
#include "systick_delay.h"
#include "stdio.h"

#define  RS 	OUTPUTA(11)  //PA11ʹ��bit_bandλ���궨�巽��
#define  RW 	OUTPUTA(12) //PA12ʹ��bit_bandλ���궨�巽��
#define  E 	    OUTPUTA(13) //PA13ʹ��bit_bandλ���궨�巽��

extern char Temp_Strings[16];//����ת������ַ������ٴ˶�Ӧ��.h�ļ�������

void LCD1602_Init(void);//LCD1602��ʼ��.
void LCD1602_Write_Data(u16 data);//LCD1602д����
void LCD1602_Write_Command(u16 command);//LCD1602д����
void LCD1602_Clear_Screen(void);//LCD1602�������ڶ�Ӧ��.h�ļ�����������
void LCD1602_Clear_Row(u8 row_x);//LCD1602����ڼ����С��ڶ�Ӧ��.h�ļ�����������
void LCD1602_Clear_Row_Column_Length(u8 row_x, u8 column_y, u8 length);//LCD1602ָ���ӵڼ��С��ڼ��п�ʼ���������������ڶ�Ӧ��.h�ļ�����������
void LCD1602_Display_Character(u8 row_x, u8 column_y, u8 character);//LCD1602��ʾ�����ַ����ڶ�Ӧ��.h�ļ�����������
void LCD1602_Display_String(u8 row_x, u8 column_y, char *string);//LCD1602��ʾ�ַ������ڶ�Ӧ��.h�ļ�����������

#endif

