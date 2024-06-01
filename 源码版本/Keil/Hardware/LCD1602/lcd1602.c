#include "lcd1602.h"
#include "key.h"
char Temp_Strings[16]={0};//保存转换后的字符串

/**LCD1602初始化.
*/
void LCD1602_Init(void)
{
	GPIO_InitTypeDef GPIO_Init_Structure;//GPIO初始化结构体
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//打开GPIOA的时钟
	
	GPIO_Init_Structure.GPIO_Pin = (GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5|
                                    GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13);//引脚为PA0/PA1/PA2/PA3/PA4/PA5/PA6/PA7/PA11/PA12/PA13
	
    GPIO_Init_Structure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
	GPIO_Init_Structure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
	GPIO_Init(GPIOA, &GPIO_Init_Structure);//GPIOA根据结构体参数初始化
	
	LCD1602_Write_Command(0x38);//打开LCD1602显示，5X7点阵，8位数据接口
	LCD1602_Write_Command(0x0C);//打开显示，不显示光标，光标不闪烁
	LCD1602_Write_Command(0x06);//写一个字符后地址指针加一且光标加一
}

/*
LCD1602写数据
data：要写入的数据
*/
void LCD1602_Write_Data(u16 data)
{
//	Delay_ms(1);//延时1ms。不加这句仿真几分钟后LCD1602会部分位置显示错乱
	RS = 1;//RS高电平
	RW = 0;//RW低电平
	E = 0;//未发送数据前E为低电平
	GPIOA->BSRR = (data & 0x00FF);//把data高电平发送出去
	GPIOA->BRR  = ((~data) & 0x00FF );//把data低电平发送出去
	E = 1;//在E为高电平期间将数据发送出去
	Delay_ms(1);//延时1ms
	E = 0;//E为低电平
}

/*
LCD1602写命令
command: 要写入的命令
*/
void LCD1602_Write_Command(u16 command)
{
//	Delay_ms(1);//延时1ms。不加这句仿真几分钟后LCD1602会部分位置显示错乱
	RS = 0;//RS低电平
	RW = 0;//RW低电平
	E = 0;//未发送数据前E为低电平
	GPIOA->BSRR = (command & 0x00FF);//把command高电平发送出去
	GPIOA->BRR  = ((~command) & 0x00FF );//把command低电平发送出去
	E = 1;//在E为高电平期间将数据发送出去
	Delay_ms(1);//延时1ms
	E = 0;//E为低电平
}

/*
LCD1602清屏.

*/
void LCD1602_Clear_Screen(void)
{	
	LCD1602_Write_Command(0x01);//所有显示清屏
}

/*
LCD1602清除第几整行.
row_x: 第几行，取值范围1-2
*/
void LCD1602_Clear_Row(u8 row_x)
{	
	u8 i=0;//自增变量
	
	if(row_x == 1)//清除第一行
	{
		LCD1602_Write_Command(0x80);//从第一行的第1位置开始显示，
		for(i=0; i<16; i++)
		{
			LCD1602_Write_Data(' ');//写入要显示字符，清除就是全都显示空格' '
		}
	}
	else if(row_x == 2)//清除第二行
	{
		LCD1602_Write_Command(0x80+0x40);//从第二行的第1位置始显示
		for(i=0; i<16; i++)
		{
			LCD1602_Write_Data(' ');//写入要显示字符，清除就是全都显示空格' '
		}
	}
}

/*
LCD1602指定从第几行、第几列开始清除和清除个数
row_x: 第几行，取值范围1-2
column_y: 第几列，取值范围1-16
length: 要清除的个数，取值范围1-16
*/
void LCD1602_Clear_Row_Column_Length(u8 row_x, u8 column_y, u8 length)
{	
	u8 i=0;//自增变量
	
	if(length>16)//LCD1602一行最多显示16个字符，长度不能超了
	{
		length = 16;//强制置数
	}
	
	if((column_y + length) > 16)//假如从第5列开始，共清除15个，这就超过了LCD的一行最大16个显示，所以强制限制最大只能清除LCD1602一行的16个字符
	{
		length = 17 - column_y;//假如是从第5列开始，共清除15个，则可计算出length为12。实际上是从第5列开始，一共还剩12个，一直清除到本行末尾共16个字符
	}
	
	if(row_x == 1)//清除第一行
	{
		LCD1602_Write_Command(0x80+column_y-1);//从第一行的第column_y-1位置开始显示，这里减一的目的是要从第0个位置开始显示，常识上人会认为第一个位置是1不是0
		for(i=0; i<length; i++)
		{
			LCD1602_Write_Data(' ');//写入要显示字符，清除就是全都显示空格' '
		}
	}
	else if(row_x == 2)//清除第二行
	{
		LCD1602_Write_Command(0x80+0x40+column_y-1);//从第二行的第column_y-1位置始显示，这里减一的目的是要从第0个位置开始显示，常识上人会认为第一个位置是1不是0
		for(i=0; i<length; i++)
		{
			LCD1602_Write_Data(' ');//写入要显示字符，清除就是全都显示空格' '
		}
	}
}

/*
LCD1602显示单个字符.
row_x: 第几行，取值范围1-2
column_y: 第几列，取值范围1-16
character: 要显示的单个字符
*/
void LCD1602_Display_Character(u8 row_x, u8 column_y, u8 character)
{	
	if(row_x == 1)//从第一行开始显示
	{
		LCD1602_Write_Command(0x80+column_y-1);//从第一行的第column_y-1位置开始显示，这里减一的目的是要从第0个位置开始显示，常识上人会认为第一个位置是1不是0
		LCD1602_Write_Data(character);//写入要显示字符
	}
	else if(row_x == 2)//从第二行开始显示
	{
		LCD1602_Write_Command(0x80+0x40+column_y-1);//从第二行的第column_y-1位置始显示，这里减一的目的是要从第0个位置开始显示，常识上人会认为第一个位置是1不是0
		LCD1602_Write_Data(character);//写入要显示字符
	}
}

/*
LCD1602显示字符串.
row_x: 第几行，取值范围1-2
column_y: 第几列，取值范围1-16
string: 要显示的字符串
*/
void LCD1602_Display_String(u8 row_x, u8 column_y, char *string)
{	
	u8 i=0;//自增变量
	
	if(row_x == 1)//从第一行开始显示
	{
		LCD1602_Write_Command(0x80+column_y-1);//从第一行的第column_y位置开始显示，这里减一的目的是要从第0个位置开始显示，常识上人会认为第一个位置是1不是0
		for(i=0; string[i]!='\0'; i++)//字符串以'\0'结尾
		{
			LCD1602_Write_Data(string[i]);//写入要显示字符
		}
	}
	else if(row_x == 2)//从第二行开始显示
	{
		LCD1602_Write_Command(0x80+0x40+column_y-1);//从第二行的第column_y位置始显示，这里减一的目的是要从第0个位置开始显示，常识上人会认为第一个位置是1不是0
		for(i=0; string[i]!='\0'; i++)//字符串以'\0'结尾
		{
			LCD1602_Write_Data(string[i]);//写入要显示字符
		}
	}
}