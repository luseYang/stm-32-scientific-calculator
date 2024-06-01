#ifndef __KEY_H
#define __KEY_H
#include "bit_band.h"
#include "systick_delay.h"

#define  PB0 	OUTPUTB(0) //PB0使用bit_band位带宏定义方法
#define  PB1 	OUTPUTB(1) //PB1使用bit_band位带宏定义方法
#define  PB2 	OUTPUTB(2) //PB2使用bit_band位带宏定义方法
#define  PB3 	OUTPUTB(3) //PB3使用bit_band位带宏定义方法
#define  PB4 	OUTPUTB(4) //PB4使用bit_band位带宏定义方法
#define  PB5 	OUTPUTB(5) //PB5使用bit_band位带宏定义方法
#define  PB6 	OUTPUTB(6) //PB6使用bit_band位带宏定义方法
#define  PB7 	OUTPUTB(7) //PB7使用bit_band位带宏定义方法

#define  PB8 	INPUTB(8)  //PB8使用bit_band位带宏定义方法
#define  PB9 	INPUTB(9)  //PB9使用bit_band位带宏定义方法
#define  PB10 	INPUTB(10) //PB10使用bit_band位带宏定义方法
#define  PB11 	INPUTB(11) //PB11使用bit_band位带宏定义方法

void KEY_Init(void);//按键初始化
u8 Get_Key_Value(void);//获取矩阵按键的值函数。在对应的.h文件中声明函数

#endif
