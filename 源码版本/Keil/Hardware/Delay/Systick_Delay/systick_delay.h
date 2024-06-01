#ifndef __SYSTICK_DELAY_H
#define __SYSTICK_DELAY_H 

			   
#include "bit_band.h"   

#define IS_SYSTICK_DELAY_US_VAULE(PERIPH) (((PERIPH) > 0) && ((PERIPH) < 0xFFFF))
#define IS_SYSTICK_DELAY_MS_VAULE(PERIPH) (((PERIPH) > 0) && ((PERIPH) < 0xFFFF))
	 
void Systick_Delay_Init(void);//systick延时函数初始化
void Systick_Delay_us(u16 us);//systick延时微秒函数
void Systick_Delay_ms(u16 ms);//systick延时毫秒函数

void Delay_us(uint16_t us);//普通微秒延时函数
void Delay_ms(uint16_t ms);//普通毫秒延时函数

void Systick_Interrupt_5ms_Init(void);//systick初始化并开中断函数,每5ms进入一次中断.

#endif

























