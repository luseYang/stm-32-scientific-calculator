/**
  *************************** �ֽ��ǿ� *************************************
  * @author  LWen   
  * @version V1.0
  * @date    2020-08-01
  * @brief   Firmware Library V3.5.0��
  * @copyright  ��Ȩ���� ,����ؾ�
  * @attention  ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
  *             Copyright(C) LWen 2023-2033   All rights reserved
  *
  ************************** ST��Ƭ��ϵ�� ************************************
  * @�Ա�����: �ֽ��ǿ�
  * @�Ա���ַ: https://zijiezhikong.taobao.com/
  * @�����ַ: zijiezhikong@foxmail.com
  ******************************************************************************
**/ 

/*-----------------------------------------------------------------------------------------------------------------------*/	
#ifndef __BIT_BAND_H
#define __BIT_BAND_H	
#include "stm32f10x.h"
	 
//bit_bandʵ������51��Ƭ��IO������ʽ

//��ʽ����<Cortex-M3Ȩ��ָ��>�ĵ�87-92ҳ
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define REGx_Bit_Band(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 


/**
 * @brief  ʵ��ָ�������ӦGPIOx(A..G)��ODR��IDR�Ĵ���
 * @param  Pin:where Pin can be (0..15).
**/
#define OUTPUTA(Pin) REGx_Bit_Band((uint32_t)(&(GPIOA->ODR)), Pin)//GPIOA������Pin(0..15)���
#define  INPUTA(Pin) REGx_Bit_Band((uint32_t)(&(GPIOA->IDR)), Pin)//GPIOA������Pin(0..15)����

#define OUTPUTB(Pin) REGx_Bit_Band((uint32_t)(&(GPIOB->ODR)), Pin)//GPIOB������Pin(0..15)���
#define  INPUTB(Pin) REGx_Bit_Band((uint32_t)(&(GPIOB->IDR)), Pin)//GPIOB������Pin(0..15)����

#define OUTPUTC(Pin) REGx_Bit_Band((uint32_t)(&(GPIOC->ODR)), Pin)//GPIOC������Pin(0..15)���
#define  INPUTC(Pin) REGx_Bit_Band((uint32_t)(&(GPIOC->IDR)), Pin)//GPIOC������Pin(0..15)����

#define OUTPUTD(Pin) REGx_Bit_Band((uint32_t)(&(GPIOD->ODR)), Pin)//GPIOD������Pin(0..15)���
#define  INPUTD(Pin) REGx_Bit_Band((uint32_t)(&(GPIOD->IDR)), Pin)//GPIOD������Pin(0..15)����

#define OUTPUTE(Pin) REGx_Bit_Band((uint32_t)(&(GPIOE->ODR)), Pin)//GPIOE������Pin(0..15)���
#define  INPUTE(Pin) REGx_Bit_Band((uint32_t)(&(GPIOE->IDR)), Pin)//GPIOE������Pin(0..15)����

#define OUTPUTF(Pin) REGx_Bit_Band((uint32_t)(&(GPIOF->ODR)), Pin)//GPIOF������Pin(0..15)���
#define  INPUTF(Pin) REGx_Bit_Band((uint32_t)(&(GPIOF->IDR)), Pin)//GPIOF������Pin(0..15)����

#define OUTPUTG(Pin) REGx_Bit_Band((uint32_t)(&(GPIOG->ODR)), Pin)//GPIOG������Pin(0..15)���
#define  INPUTG(Pin) REGx_Bit_Band((uint32_t)(&(GPIOG->IDR)), Pin)//GPIOG������Pin(0..15)����

#endif

/*------------------------------------------*** �Ա�����: �ֽ��ǿ� ***--------------------------------------------------*/	
/*---------------End Of File---------Copyright(C) LWen 2023-2033   All rights reserved---------End Of File---------------*/	


