#ifndef __LCD1602_H
#define __LCD1602_H

#include "stm32f10x.h"
#include "systick_delay.h"
#include "stdio.h"

#define  RS 	OUTPUTA(11)  //PA11使用bit_band位带宏定义方法
#define  RW 	OUTPUTA(12) //PA12使用bit_band位带宏定义方法
#define  E 	    OUTPUTA(13) //PA13使用bit_band位带宏定义方法

extern char Temp_Strings[16];//保存转换后的字符串。再此对应的.h文件中声明

void LCD1602_Init(void);//LCD1602初始化.
void LCD1602_Write_Data(u16 data);//LCD1602写数据
void LCD1602_Write_Command(u16 command);//LCD1602写命令
void LCD1602_Clear_Screen(void);//LCD1602清屏。在对应的.h文件中声明函数
void LCD1602_Clear_Row(u8 row_x);//LCD1602清除第几整行。在对应的.h文件中声明函数
void LCD1602_Clear_Row_Column_Length(u8 row_x, u8 column_y, u8 length);//LCD1602指定从第几行、第几列开始清除和清除个数。在对应的.h文件中声明函数
void LCD1602_Display_Character(u8 row_x, u8 column_y, u8 character);//LCD1602显示单个字符。在对应的.h文件中声明函数
void LCD1602_Display_String(u8 row_x, u8 column_y, char *string);//LCD1602显示字符串。在对应的.h文件中声明函数

#endif

