#include "key.h"
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitType_Structure;//GPIO初始化结构体
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//打开GPIOB的时钟
	
    GPIO_InitType_Structure.GPIO_Pin = (GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |
                                        GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);//引脚为PB0到PB7
    GPIO_InitType_Structure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
	GPIO_InitType_Structure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
	GPIO_Init(GPIOB, &GPIO_InitType_Structure);//GPIOB根据结构体参数初始化
    
	GPIO_InitType_Structure.GPIO_Pin = (GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11);//引脚为PB8到PB11
	GPIO_InitType_Structure.GPIO_Mode = GPIO_Mode_IPD;//下拉输入
	GPIO_Init(GPIOB, &GPIO_InitType_Structure);//GPIOB根据结构体参数初始化
    
    PB0 = 0;//PB0输出低电平
    PB1 = 0;//PB1输出低电平
    PB2 = 0;//PB2输出低电平
    PB3 = 0;//PB3输出低电平
    PB4 = 0;//PB4输出低电平
    PB5 = 0;//PB5输出低电平
    PB6 = 0;//PB6输出低电平
    PB7 = 0;//PB7输出低电平
}

/**
获取矩阵按键的值函数
**/
u8 Get_Key_Value(void)
{
	u8 key_value = 0;//按键的值
    u8 i = 0;//自增变量

	//扫描从上往下横着看第一行按键
	PB0 = 1;//扫描第一行按键ln、log10、√根号和Clear清屏，第一行对应的PB0引脚输出高电平1
	if((PB8 == 1) || (PB9 == 1) || (PB10 == 1) || (PB11 == 1))//如果有按键被按下，则值是1
	{
//		Delay_ms(1);//延时消抖
		if((PB8 == 1) || (PB9 == 1) || (PB10 == 1) || (PB11 == 1))//如果有按键被按下，则值是1
		{
			if(PB8 == 1)////按键'ln'被按下
            {
                key_value = 'A';//对应的字符'A'
            }
            else if(PB9 == 1)//按键'log10'被按下
            {
                key_value = 'E';//对应的字符'E'
            }
            else if(PB10 == 1) //按键'√'被按下，表示根号
            {
                key_value = 'I';//对应的字符'I'
            }
            else if(PB11 == 1)//按键'Clear'被按下，表示清除屏幕
            {
                key_value = 'M';//对应的字符'M'
            }
		}
        while((PB8 == 1) || (PB9 == 1) || (PB10 == 1) || (PB11 == 1));//等待按键松手
	}
    PB0 = 0;//PB0输出低电平，非扫描状态

	//扫描从上往下横着看第二行按键
	PB1 = 1;//扫描第二行按键tanh、x^y、e^x和n!，第二行对应的PB1引脚输出高电平1
	if((PB8 == 1) || (PB9 == 1) || (PB10 == 1) || (PB11 == 1))//如果有按键被按下，则值是1
	{
//		Delay_ms(1);//延时消抖
		if((PB8 == 1) || (PB9 == 1) || (PB10 == 1) || (PB11 == 1))//如果有按键被按下，则值是1
		{
			if(PB8 == 1)//按键'tanh'被按下
            {
                key_value = 'B';//对应的字符'B'
            }
            else if(PB9 == 1)//按键'x^y'被按下
            {
                key_value = '^';//对应的字符'^'
            }
            else if(PB10 == 1) //按键'e^x'被按下
            {
                key_value = 'J';//对应的字符'J'
            }
            else if(PB11 == 1)//按键'n!'被按下
            {
                key_value = 'N';//对应的字符'N'
            }
		}
        while((PB8 == 1) || (PB9 == 1) || (PB10 == 1) || (PB11 == 1));//等待按键松手
	}
    PB1 = 0;//PB1输出低电平，非扫描状态

	//扫描从上往下横着看第三行按键
	PB2 = 1;//扫描第三行按键acos、atan、sinh和cosh，第三行对应的PB2引脚输出高电平1
	if((PB8 == 1) || (PB9 == 1) || (PB10 == 1) || (PB11 == 1))//如果有按键被按下，则值是1
	{
//		Delay_ms(1);//延时消抖
		if((PB8 == 1) || (PB9 == 1) || (PB10 == 1) || (PB11 == 1))//如果有按键被按下，则值是1
		{
			if(PB8 == 1) //按键'acos'被按下
            {
                key_value = 'C';//对应的字符'C'
            }
            else if(PB9 == 1)//按键'atan'被按下
            {
                key_value = 'G';//对应的字符'G'
            }
            else if(PB10 == 1) //按键'sinh'被按下
            {
                key_value = 'K';//对应的字符'K'
            }
            else if(PB11 == 1)//按键'cosh'被按下
            {
                key_value = 'P';//对应的字符'P'
            }
		}
        while((PB8 == 1) || (PB9 == 1) || (PB10 == 1) || (PB11 == 1));//等待按键松手
	}
    PB2 = 0;//PB2输出低电平，非扫描状态

	//扫描从上往下横着看第四行按键
	PB3 = 1;//扫描第四行按键sin、cos、tan和asin，第四行对应的PB3引脚输出高电平1
	if((PB8 == 1) || (PB9 == 1) || (PB10 == 1) || (PB11 == 1))//如果有按键被按下，则值是1
	{
//		Delay_ms(1);//延时消抖
		if((PB8 == 1) || (PB9 == 1) || (PB10 == 1) || (PB11 == 1))//如果有按键被按下，则值是1
		{
			if(PB8 == 1) //按键'sin'被按下
            {
                key_value = 'D';//对应的字符'D'
            }
            else if(PB9 == 1)//按键'cos'被按下
            {
                key_value = 'H';//对应的字符'H'
            }
            else if(PB10 == 1) //按键'tan'被按下
            {
                key_value = 'L';//对应的字符'L'
            }
            else if(PB11 == 1)//按键'asin'被按下
            {
                key_value = 'Q';//对应的字符'Q'
            }
		}
        while((PB8 == 1) || (PB9 == 1) || (PB10 == 1) || (PB11 == 1));//等待按键松手
	}
    PB3 = 0;//PB3输出低电平，非扫描状态
	
	//扫描从上往下横着看第五行按键
	PB4 = 1;//扫描第五行按键7、8、9和/，第五行对应的PB4引脚输出高电平1
	if((PB8 == 1) || (PB9 == 1) || (PB10 == 1) || (PB11 == 1))//如果有按键被按下，则值是1
	{
//		Delay_ms(1);//延时消抖
		if((PB8 == 1) || (PB9 == 1) || (PB10 == 1) || (PB11 == 1))//如果有按键被按下，则值是1
		{
			if(PB8 == 1)//按键'7'被按下
            {
                key_value = '7';//对应的字符'7'
            }
            else if(PB9 == 1)//按键'8'被按下
            {
                key_value = '8';//对应的字符'8'
            }
            else if(PB10 == 1)//按键'9'被按下
            {
                key_value = '9';//对应的字符'9'
            }
            else if(PB11 == 1)//按键'/'被按下
            {
                key_value = '/';//对应的字符'/'
            }
		}
        while((PB8 == 1) || (PB9 == 1) || (PB10 == 1) || (PB11 == 1));//等待按键松手
	}
    PB4 = 0;//PB4输出低电平，非扫描状态
	
	//扫描从上往下横着看第六行按键
	PB5 = 1;//扫描第六行按键4、5、6和*，第六行对应的PB5引脚输出高电平1
	if((PB8 == 1) || (PB9 == 1) || (PB10 == 1) || (PB11 == 1))//如果有按键被按下，则值是1
	{
//		Delay_ms(1);//延时消抖
		if((PB8 == 1) || (PB9 == 1) || (PB10 == 1) || (PB11 == 1))//如果有按键被按下，则值是1
		{
			if(PB8 == 1)//按键'4'被按下
            {
                key_value = '4';//对应的字符'4'
            }
            else if(PB9 == 1)//按键'5'被按下
            {
                key_value = '5';//对应的字符'5'
            }
            else if(PB10 == 1)//按键'6'被按下
            {
                key_value = '6';//对应的字符'6'
            }
            else if(PB11 == 1)//按键'*'被按下
            {
                key_value = '*';//对应的字符'*'
            }
		}
        while((PB8 == 1) || (PB9 == 1) || (PB10 == 1) || (PB11 == 1));//等待按键松手
	}
    PB5 = 0;//PB5输出低电平，非扫描状态 
    
    
	//扫描从上往下横着看第七行按键
	PB6 = 1;//扫描第七行按键1、2、3和-，第七行对应的PB6引脚输出高电平1
	if((PB8 == 1) || (PB9 == 1) || (PB10 == 1) || (PB11 == 1))//如果有按键被按下，则值是1
	{
//		Delay_ms(1);//延时消抖
		if((PB8 == 1) || (PB9 == 1) || (PB10 == 1) || (PB11 == 1))//如果有按键被按下，则值是1
		{
			if(PB8 == 1)//按键'1'被按下
            {
                key_value = '1';//对应的字符'1'
            }
            else if(PB9 == 1)//按键'2'被按下
            {
                key_value = '2';//对应的字符'2'
            }
            else if(PB10 == 1)//按键'3'被按下
            {
                key_value = '3';//对应的字符'3'
            }
            else if(PB11 == 1)//按键'-'被按下
            {
                key_value = '-';//对应的字符'-'
            }
		}
        while((PB8 == 1) || (PB9 == 1) || (PB10 == 1) || (PB11 == 1));//等待按键松手
	}
    PB6 = 0;//PB6输出低电平，非扫描状态 
    
 
	//扫描从上往下横着看第八行按键
	PB7 = 1;////扫描第八行按键.、0、=和+，第八行对应的PB7引脚输出高电平1
	if((PB8 == 1) || (PB9 == 1) || (PB10 == 1) || (PB11 == 1))//如果有按键被按下，则值是1
	{
//		Delay_ms(1);//延时消抖
		if((PB8 == 1) || (PB9 == 1) || (PB10 == 1) || (PB11 == 1))//如果有按键被按下，则值是1
		{
			if(PB8 == 1)//按键'.'被按下，表示小数点
            {
                key_value = '.';//对应的字符'.'小数点
            }
            else if(PB9 == 1)//按键'0'被按下
            {
                key_value = '0';//对应的字符'0'
            }
            else if(PB10 == 1)//按键'='被按下
            {
                key_value = '=';//对应的字符'='
            }
            else if(PB11 == 1)//按键'+'被按下
            {
                key_value = '+';//对应的字符'+'
            }
		}
        while((PB8 == 1) || (PB9 == 1) || (PB10 == 1) || (PB11 == 1));//等待按键松手
	}  	
	PB7 = 0;//PB7输出低电平，非扫描状态
    
	return key_value;//返回按键被按下时，按键对应的字符
}