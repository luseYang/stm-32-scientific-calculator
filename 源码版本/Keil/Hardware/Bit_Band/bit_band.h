/**
  *************************** 字节智控 *************************************
  * @author  LWen   
  * @version V1.0
  * @date    2020-08-01
  * @brief   Firmware Library V3.5.0。
  * @copyright  版权所有 ,盗版必究
  * @attention  本程序只供学习使用，未经作者许可，不得用于其它任何用途
  *             Copyright(C) LWen 2023-2033   All rights reserved
  *
  ************************** ST单片机系列 ************************************
  * @淘宝店铺: 字节智控
  * @淘宝网址: https://zijiezhikong.taobao.com/
  * @邮箱地址: zijiezhikong@foxmail.com
  ******************************************************************************
**/ 

/*-----------------------------------------------------------------------------------------------------------------------*/	
#ifndef __BIT_BAND_H
#define __BIT_BAND_H	
#include "stm32f10x.h"
	 
//bit_band实现类似51单片机IO操作方式

//公式根据<Cortex-M3权威指南>的第87-92页
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define REGx_Bit_Band(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 


/**
 * @brief  实现指针操作相应GPIOx(A..G)的ODR和IDR寄存器
 * @param  Pin:where Pin can be (0..15).
**/
#define OUTPUTA(Pin) REGx_Bit_Band((uint32_t)(&(GPIOA->ODR)), Pin)//GPIOA的引脚Pin(0..15)输出
#define  INPUTA(Pin) REGx_Bit_Band((uint32_t)(&(GPIOA->IDR)), Pin)//GPIOA的引脚Pin(0..15)输入

#define OUTPUTB(Pin) REGx_Bit_Band((uint32_t)(&(GPIOB->ODR)), Pin)//GPIOB的引脚Pin(0..15)输出
#define  INPUTB(Pin) REGx_Bit_Band((uint32_t)(&(GPIOB->IDR)), Pin)//GPIOB的引脚Pin(0..15)输入

#define OUTPUTC(Pin) REGx_Bit_Band((uint32_t)(&(GPIOC->ODR)), Pin)//GPIOC的引脚Pin(0..15)输出
#define  INPUTC(Pin) REGx_Bit_Band((uint32_t)(&(GPIOC->IDR)), Pin)//GPIOC的引脚Pin(0..15)输入

#define OUTPUTD(Pin) REGx_Bit_Band((uint32_t)(&(GPIOD->ODR)), Pin)//GPIOD的引脚Pin(0..15)输出
#define  INPUTD(Pin) REGx_Bit_Band((uint32_t)(&(GPIOD->IDR)), Pin)//GPIOD的引脚Pin(0..15)输入

#define OUTPUTE(Pin) REGx_Bit_Band((uint32_t)(&(GPIOE->ODR)), Pin)//GPIOE的引脚Pin(0..15)输出
#define  INPUTE(Pin) REGx_Bit_Band((uint32_t)(&(GPIOE->IDR)), Pin)//GPIOE的引脚Pin(0..15)输入

#define OUTPUTF(Pin) REGx_Bit_Band((uint32_t)(&(GPIOF->ODR)), Pin)//GPIOF的引脚Pin(0..15)输出
#define  INPUTF(Pin) REGx_Bit_Band((uint32_t)(&(GPIOF->IDR)), Pin)//GPIOF的引脚Pin(0..15)输入

#define OUTPUTG(Pin) REGx_Bit_Band((uint32_t)(&(GPIOG->ODR)), Pin)//GPIOG的引脚Pin(0..15)输出
#define  INPUTG(Pin) REGx_Bit_Band((uint32_t)(&(GPIOG->IDR)), Pin)//GPIOG的引脚Pin(0..15)输入

#endif

/*------------------------------------------*** 淘宝店铺: 字节智控 ***--------------------------------------------------*/	
/*---------------End Of File---------Copyright(C) LWen 2023-2033   All rights reserved---------End Of File---------------*/	


