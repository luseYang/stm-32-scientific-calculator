#include "systick_delay.h"
#include "key.h"
#include "lcd1602.h"
#include "stdio.h"


void Systick_Delay_Init(void)
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK); //AHBʱ����Ϊsystick clock source����systickʱ��Ƶ��Ϊ8M
}						    
/*
systick��ʱus����.
us:Maximum value 65535.
*/		    								   
void Systick_Delay_us(u16 us)
{		
	/* Check the parameters */
	assert_param(IS_SYSTICK_DELAY_US_VAULE(us));
	
	SysTick->VAL = 0x00;  //���systick������	
	SysTick->LOAD = us*8; //��װ��ֵ��systickʱ��Ƶ��Ϊ8M�����������8������ʱ1us��Ҫ��ʱʱ�����8���Ǽ�����װ�ص�ֵ
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; //systick����������ʹ��	  
	while(!((SysTick->CTRL)&(1<<16))); //systick��CTRL�Ĵ�����16λ��Ϊ1���򵹼�����0   
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; //�ر�systick������ 
	
}

/*
systick��ʱms����.
ms:Maximum value 65535.
*/	
void Systick_Delay_ms(u16 ms)
{	
	/* Check the parameters */
	assert_param(IS_SYSTICK_DELAY_MS_VAULE(ms));

	while(ms--)
	{
		Systick_Delay_us(1000);//����΢����ʱ����ʵ�ֺ�����ʱ
	}
}

/*
��ͨ΢����ʱ������ʱ��Ƶ��8MHzʱ�������48MHz����ʱ��ʱ���ٳ���6����us*6������ʱ1us
us:��ʱʱ�䣬���ֵ65535
*/
void Delay_us(uint16_t us)
{
    while(us--);
}

/*
��ͨ������ʱ������ʱ��Ƶ��8MHzʱ�������48MHz����ʱ��ʱ���ٳ���6����1333*6������ʱ1ms
ms:��ʱʱ�䣬���ֵ65535
*/
void Delay_ms(uint16_t ms)
{
	uint16_t x=0, y=0;//�ֲ�����������ʱ
	
	for(x=ms; x>0; x--)//ѭ����x�Լ�һֱ����0����ѭ��
	{
		for(y=1333; y>0; y--)//ѭ����y�Լ�һֱ����0����ѭ��
		{
		}
	}
}

/*
systick��ʼ�������жϺ���,ÿ5ms����һ���ж�.
*/	
void Systick_Interrupt_5ms_Init(void)
{	
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK); //AHBʱ����Ϊsystick clock source����systickʱ��Ƶ��Ϊ8M
	SysTick->VAL = 0x00;  //���systick������	
	SysTick->LOAD = 5000*8; //��װ��ֵ��systickʱ��Ƶ��Ϊ8M�����������8������ʱ1us��Ҫ��ʱʱ�����8���Ǽ�����װ�ص�ֵ,Ϊ5ms
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;//systick�ж�ʹ��
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; //systick����������ʹ��
}

/*
systick�жϷ�����,ÿ5ms����һ�δ��жϷ�����.
*/	
void SysTick_Handler(void)
{	

}



































