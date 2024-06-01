/* Includes包含头文件 ------------------------------------------------------------------*/
#include "systick_delay.h"
#include "key.h"
#include "lcd1602.h"
#include "Calculator.h"

/* Global Variable全局变量 -----------------------------------------------------------*/
//4个字节32位支持计算范围是-2147483648 to 2147483647 
//区分有小数时和没小数时分别进行四则运算
 
int main(void)
 {	 
	KEY_Init();//按键初始化函数
    LCD1602_Init();//LCD1602初始化
	while(1)
	{	
		Get_Operate_Number_And_Operate_Symbol_And_Calculate();//获取按键输入的操作数和操作符，以及进行四则运算。
	}	 
}

