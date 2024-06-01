#ifndef __SYSTICK_DELAY_H
#define __SYSTICK_DELAY_H 

			   
#include "bit_band.h"   

#define IS_SYSTICK_DELAY_US_VAULE(PERIPH) (((PERIPH) > 0) && ((PERIPH) < 0xFFFF))
#define IS_SYSTICK_DELAY_MS_VAULE(PERIPH) (((PERIPH) > 0) && ((PERIPH) < 0xFFFF))
	 
void Systick_Delay_Init(void);//systick��ʱ������ʼ��
void Systick_Delay_us(u16 us);//systick��ʱ΢�뺯��
void Systick_Delay_ms(u16 ms);//systick��ʱ���뺯��

void Delay_us(uint16_t us);//��ͨ΢����ʱ����
void Delay_ms(uint16_t ms);//��ͨ������ʱ����

void Systick_Interrupt_5ms_Init(void);//systick��ʼ�������жϺ���,ÿ5ms����һ���ж�.

#endif

























