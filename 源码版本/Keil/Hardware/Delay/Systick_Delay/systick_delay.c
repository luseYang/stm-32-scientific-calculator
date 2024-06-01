#include "systick_delay.h"
#include "key.h"
#include "lcd1602.h"
#include "stdio.h"


void Systick_Delay_Init(void)
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK); //AHB时钟作为systick clock source，则systick时钟频率为8M
}						    
/*
systick延时us函数.
us:Maximum value 65535.
*/		    								   
void Systick_Delay_us(u16 us)
{		
	/* Check the parameters */
	assert_param(IS_SYSTICK_DELAY_US_VAULE(us));
	
	SysTick->VAL = 0x00;  //清空systick计数器	
	SysTick->LOAD = us*8; //重装载值，systick时钟频率为8M，则计数器计8个数用时1us，要延时时间乘以8才是计数器装载的值
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; //systick计数器计数使能	  
	while(!((SysTick->CTRL)&(1<<16))); //systick的CTRL寄存器第16位变为1，则倒计数到0   
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; //关闭systick计数器 
	
}

/*
systick延时ms函数.
ms:Maximum value 65535.
*/	
void Systick_Delay_ms(u16 ms)
{	
	/* Check the parameters */
	assert_param(IS_SYSTICK_DELAY_MS_VAULE(ms));

	while(ms--)
	{
		Systick_Delay_us(1000);//调用微秒延时函数实现毫秒延时
	}
}

/*
普通微秒延时函数在时钟频率8MHz时，如果是48MHz则延时的时间再乘以6，即us*6才是延时1us
us:延时时间，最大值65535
*/
void Delay_us(uint16_t us)
{
    while(us--);
}

/*
普通毫秒延时函数在时钟频率8MHz时，如果是48MHz则延时的时间再乘以6，即1333*6才是延时1ms
ms:延时时间，最大值65535
*/
void Delay_ms(uint16_t ms)
{
	uint16_t x=0, y=0;//局部变量用于延时
	
	for(x=ms; x>0; x--)//循环让x自减一直减到0结束循环
	{
		for(y=1333; y>0; y--)//循环让y自减一直减到0结束循环
		{
		}
	}
}

/*
systick初始化并开中断函数,每5ms进入一次中断.
*/	
void Systick_Interrupt_5ms_Init(void)
{	
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK); //AHB时钟作为systick clock source，则systick时钟频率为8M
	SysTick->VAL = 0x00;  //清空systick计数器	
	SysTick->LOAD = 5000*8; //重装载值，systick时钟频率为8M，则计数器计8个数用时1us，要延时时间乘以8才是计数器装载的值,为5ms
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;//systick中断使能
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; //systick计数器计数使能
}

/*
systick中断服务函数,每5ms进入一次此中断服务函数.
*/	
void SysTick_Handler(void)
{	

}



































