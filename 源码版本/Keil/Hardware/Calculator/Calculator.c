/* Includes包含头文件*/
#include "Calculator.h"
#include "lcd1602.h"
#include "key.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "math.h"

/* Global Variable全局变量*/
u8 Key_Value_Temp=0;//获取的按键值临时存储变量
int32_t Operate_Number1 = 0;//参与计算的第1个操作数是整型
int32_t Operate_Number2 = 0;//参与计算的第2个操作数是整型
u8 Operate_Symbol  = 0;//参与计算的操作符
char Save_Operate_Number1[11] = {0};//保存操作数1
char Save_Operate_Number2[11] = {0};//保存操作数2
u8 Save_Operate_Number2_Position=0;//记录保存第2个操作数在Save_Operate_Number2数组中的下标位置
int32_t Calculate_Result  = 0;//计算的结果是整型
char Result[12]={0};//保存计算的结果
u8 Input_Number=0;//输入的字符个数，用来记录应该显示在LCD1602的哪一列的
u8 Operate_Symbol_Flag=0;//参与计算的操作符标志位，只有输入了操作符以后，才能获取第二个操作数。因为按键输入顺序是第一个操作数、操作符、第二个操作数
u8 Operate_Number2_Flag=0;//参与计算的第2个操作数标志位，只有第二个操作数输入完毕，再按等于号'='才有效
u8 Calculate_Complete_Flag=0;//计算完成标志位

float Operate_Number1_Float = 0;//参与计算的第1个操作数是浮点型
float Operate_Number2_Float = 0;//参与计算的第2个操作数是浮点型
float Calculate_Result_Float  = 0;//计算的结果是浮点型

/*
获取按键输入的操作数和操作符，以及进行四则和科学运算
*/
void Get_Operate_Number_And_Operate_Symbol_And_Calculate(void)
{
	u8 i=0;//自增变量
	
	Key_Value_Temp = Get_Key_Value();//获取按键值
	if(((Key_Value_Temp >= '0') && (Key_Value_Temp <= '9')) || (Key_Value_Temp == '.'))//获取操作数，输入的是0到9或者小数点
	{
		if((Operate_Symbol_Flag == 1) && (Operate_Number2_Flag == 1) && (Operate_Symbol == 0))//用来支持连续计算，计算完一次后不用按on/c按键清零，直接输入就能进行下一次计算
		{
			LCD1602_Clear_Screen();//LCD1602清屏
			Input_Number = 0;//输入的字符个数清零
			Operate_Number1 = 0;//参与计算的第1个操作数清零
			Operate_Number2 = 0;//参与计算的第2个操作数清零
			Operate_Symbol = 0;//参与计算的操作符清零
			Save_Operate_Number2_Position=0;//记录保存第2个操作数在Save_Operate_Number2数组中的下标位置清零
			Operate_Symbol_Flag = 0;//参与计算的操作符标志位清零
			Calculate_Result = 0;//计算结果清零
			Operate_Number2_Flag = 0;//参与计算的第2个操作数标志位清零
			Calculate_Complete_Flag=0;//计算完成标志位清零
			Operate_Number1_Float = 0;//参与计算的第1个操作数是浮点型清零
			Operate_Number2_Float = 0;//参与计算的第2个操作数是浮点型清零
			Calculate_Result_Float  = 0;//计算的结果是浮点型清零
			for(i=0; i<11; i++)//数组清零
			{
				Save_Operate_Number1[i] = 0;//清零
			}
			for(i=0; i<11; i++)//数组清零
			{
				Save_Operate_Number2[i] = 0;//清零
			}
			for(i=0; i<12; i++)//数组清零
			{
				Result[i] = 0;//清零
			}			
		}

		if(Operate_Symbol_Flag == 0)//获取输入的第一个操作数
		{
			Save_Operate_Number1[Input_Number] = Key_Value_Temp;//将获取的字符按键值保存到Save_Operate_Number1数组中
			Input_Number++;//按键输入一个字符，则自增一次，用来记录应该显示在LCD1602的哪一列的
			LCD1602_Display_Character(1, Input_Number, Key_Value_Temp);//从LCD1602第1行，第Input_Number列的位置开始依次显示输入的对应的字符
		}
		else if(Operate_Symbol_Flag == 1)//获取输入的第二个操作数。只有在输入了+、-、*和/四则运算符后，才能输入第二个操作数
		{
			Save_Operate_Number2[Save_Operate_Number2_Position++] = Key_Value_Temp;//将获取的字符按键值保存到Save_Operate_Number2数组中
			Input_Number++;//按键输入一个字符，则自增一次，用来记录应该显示在LCD1602的哪一列的
			LCD1602_Display_Character(1, Input_Number, Key_Value_Temp);//从LCD1602第1行，第Input_Number列的位置开始依次显示输入的对应的字符
			Operate_Number2_Flag = 1;//参与计算的第2个操作数标志位置1，说明可以按下等于号'='进行相关运算了
		}
	}
	else if((Key_Value_Temp == '+') || (Key_Value_Temp == '-') || (Key_Value_Temp == '*') || (Key_Value_Temp == '/')  || (Key_Value_Temp == '^') )//获取的是+、-、*和/四则运算符及x^y幂运算
	{
		Input_Number++;//按键输入一个字符，则自增一次，用来记录应该显示在LCD1602的哪一列的
		Operate_Symbol = Key_Value_Temp;//记录输入的操作符，后面根据操作符才能进行对应的四则运算
		LCD1602_Display_Character(1, Input_Number, Key_Value_Temp);//从LCD1602第1行，第Input_Number列的位置开始依次显示输入的对应的字符
		Operate_Symbol_Flag = 1;//参与计算的操作符标志位置1。只有在输入了+、-、*和/四则运算符后，才能输入第二个操作数
	}
	else if((Key_Value_Temp == 'A') || (Key_Value_Temp == 'B') || (Key_Value_Temp == 'C') || (Key_Value_Temp == 'D') || \
	        (Key_Value_Temp == 'E') || (Key_Value_Temp == 'G') || (Key_Value_Temp == 'H') || (Key_Value_Temp == 'I') || \
			(Key_Value_Temp == 'J') || (Key_Value_Temp == 'K') || (Key_Value_Temp == 'L') || (Key_Value_Temp == 'N') || \
			(Key_Value_Temp == 'P') || (Key_Value_Temp == 'Q'))//获取ln、tanh、acos、sin、log10、atan、cos、√￣根号、e^x、sinh、tan、n!、cosh、asin
	{
		if(Input_Number != 0)//有操作数输入时才能进行运算
		{
			switch(Key_Value_Temp)
			{
				case 'A': //ln按键被按下
						if((strchr(Save_Operate_Number1, '.') != NULL))//第1个操作数有小数点
						{
							Operate_Number1_Float = atof(Save_Operate_Number1);//获取第一个操作数。将获取的字符按键值转成浮点型存储到Operate_Number1_Float
							Calculate_Result_Float = log(Operate_Number1_Float);//进行ln计算
						}
						else//第1个操作数是整数
						{
							Operate_Number1 = atol(Save_Operate_Number1);//获取第1个操作数。将获取的字符按键值转成长整型存储到Operate_Number1
							Calculate_Result_Float = log(Operate_Number1);//进行ln计算
						}
						LCD1602_Display_String(1, 1, "ln(");//在LCD1602的第1行第1列开始进行字符串显示
						LCD1602_Display_String(1, 4, Save_Operate_Number1);//在LCD1602的第1行第4列开始进行字符串显示
						LCD1602_Display_String(1, Input_Number+4, ")");//在LCD1602的第1行第Input_Number+4列开始进行字符串显示
						sprintf((char *)Result, "=%g", Calculate_Result_Float);//将Calculate_Result_Float以指定格式变成字符串保存到Result中
						LCD1602_Display_String(2, 1, Result);//在LCD1602的第二行第一列开始进行字符串显示
					break;
				case 'B': //tanh按键被按下
						if((strchr(Save_Operate_Number1, '.') != NULL))//第1个操作数有小数点
						{
							Operate_Number1_Float = atof(Save_Operate_Number1);//获取第一个操作数。将获取的字符按键值转成浮点型存储到Operate_Number1_Float
							Calculate_Result_Float = tanh(Operate_Number1_Float);//进行tanh计算(弧度)
						}
						else//第1个操作数是整数
						{
							Operate_Number1 = atol(Save_Operate_Number1);//获取第1个操作数。将获取的字符按键值转成长整型存储到Operate_Number1
							Calculate_Result_Float = tanh(Operate_Number1);//进行tanh计算(弧度)
						}
						LCD1602_Display_String(1, 1, "tanh(");//在LCD1602的第1行第1列开始进行字符串显示
						LCD1602_Display_String(1, 6, Save_Operate_Number1);//在LCD1602的第1行第6列开始进行字符串显示
						LCD1602_Display_String(1, Input_Number+6, ")");//在LCD1602的第1行第Input_Number+6列开始进行字符串显示
						sprintf((char *)Result, "=%g", Calculate_Result_Float);//将Calculate_Result_Float以指定格式变成字符串保存到Result中
						LCD1602_Display_String(2, 1, Result);//在LCD1602的第二行第一列开始进行字符串显示
					break;
				case 'C': //acos按键被按下
						if((strchr(Save_Operate_Number1, '.') != NULL))//第1个操作数有小数点
						{
							Operate_Number1_Float = atof(Save_Operate_Number1);//获取第一个操作数。将获取的字符按键值转成浮点型存储到Operate_Number1_Float
							Calculate_Result_Float = acos(Operate_Number1_Float);//进行acos计算(弧度)
						}
						else//第1个操作数是整数
						{
							Operate_Number1 = atol(Save_Operate_Number1);//获取第1个操作数。将获取的字符按键值转成长整型存储到Operate_Number1
							Calculate_Result_Float = acos(Operate_Number1);//进行acos计算(弧度)
						}
						LCD1602_Display_String(1, 1, "acos(");//在LCD1602的第1行第1列开始进行字符串显示
						LCD1602_Display_String(1, 6, Save_Operate_Number1);//在LCD1602的第1行第6列开始进行字符串显示
						LCD1602_Display_String(1, Input_Number+6, ")");//在LCD1602的第1行第Input_Number+6列开始进行字符串显示
						sprintf((char *)Result, "=%g", Calculate_Result_Float);//将Calculate_Result_Float以指定格式变成字符串保存到Result中
						LCD1602_Display_String(2, 1, Result);//在LCD1602的第二行第一列开始进行字符串显示
					break;
				case 'D': //sin按键被按下
						if((strchr(Save_Operate_Number1, '.') != NULL))//第1个操作数有小数点
						{
							Operate_Number1_Float = atof(Save_Operate_Number1);//获取第一个操作数。将获取的字符按键值转成浮点型存储到Operate_Number1_Float
							Calculate_Result_Float = sin(Operate_Number1_Float);//进行sin计算(弧度)
						}
						else//第1个操作数是整数
						{
							Operate_Number1 = atol(Save_Operate_Number1);//获取第1个操作数。将获取的字符按键值转成长整型存储到Operate_Number1
							Calculate_Result_Float = sin(Operate_Number1);//进行sin计算(弧度)
						}
						LCD1602_Display_String(1, 1, "sin(");//在LCD1602的第1行第1列开始进行字符串显示
						LCD1602_Display_String(1, 5, Save_Operate_Number1);//在LCD1602的第1行第5列开始进行字符串显示
						LCD1602_Display_String(1, Input_Number+5, ")");//在LCD1602的第1行第Input_Number+5列开始进行字符串显示
						sprintf((char *)Result, "=%g", Calculate_Result_Float);//将Calculate_Result_Float以指定格式变成字符串保存到Result中
						LCD1602_Display_String(2, 1, Result);//在LCD1602的第二行第一列开始进行字符串显示
					break;
				case 'E': //log10按键被按下
						if((strchr(Save_Operate_Number1, '.') != NULL))//第1个操作数有小数点
						{
							Operate_Number1_Float = atof(Save_Operate_Number1);//获取第一个操作数。将获取的字符按键值转成浮点型存储到Operate_Number1_Float
							Calculate_Result_Float = log10(Operate_Number1_Float);//进行log10计算
						}
						else//第1个操作数是整数
						{
							Operate_Number1 = atol(Save_Operate_Number1);//获取第1个操作数。将获取的字符按键值转成长整型存储到Operate_Number1
							Calculate_Result_Float = log10(Operate_Number1);//进行log10计算
						}
						LCD1602_Display_String(1, 1, "log10(");//在LCD1602的第1行第1列开始进行字符串显示
						LCD1602_Display_String(1, 7, Save_Operate_Number1);//在LCD1602的第1行第7列开始进行字符串显示
						LCD1602_Display_String(1, Input_Number+7, ")");//在LCD1602的第1行第Input_Number+7列开始进行字符串显示
						sprintf((char *)Result, "=%g", Calculate_Result_Float);//将Calculate_Result_Float以指定格式变成字符串保存到Result中
						LCD1602_Display_String(2, 1, Result);//在LCD1602的第二行第一列开始进行字符串显示
					break;
				case 'G': //atan按键被按下
						if((strchr(Save_Operate_Number1, '.') != NULL))//第1个操作数有小数点
						{
							Operate_Number1_Float = atof(Save_Operate_Number1);//获取第一个操作数。将获取的字符按键值转成浮点型存储到Operate_Number1_Float
							Calculate_Result_Float = atan(Operate_Number1_Float);//进行atan计算(弧度)
						}
						else//第1个操作数是整数
						{
							Operate_Number1 = atol(Save_Operate_Number1);//获取第1个操作数。将获取的字符按键值转成长整型存储到Operate_Number1
							Calculate_Result_Float = atan(Operate_Number1);//进行atan计算(弧度)
						}
						LCD1602_Display_String(1, 1, "atan(");//在LCD1602的第1行第1列开始进行字符串显示
						LCD1602_Display_String(1, 6, Save_Operate_Number1);//在LCD1602的第1行第6列开始进行字符串显示
						LCD1602_Display_String(1, Input_Number+6, ")");//在LCD1602的第1行第Input_Number+6列开始进行字符串显示
						sprintf((char *)Result, "=%g", Calculate_Result_Float);//将Calculate_Result_Float以指定格式变成字符串保存到Result中
						LCD1602_Display_String(2, 1, Result);//在LCD1602的第二行第一列开始进行字符串显示
					break;
				case 'H': //cos按键被按下
						if((strchr(Save_Operate_Number1, '.') != NULL))//第1个操作数有小数点
						{
							Operate_Number1_Float = atof(Save_Operate_Number1);//获取第一个操作数。将获取的字符按键值转成浮点型存储到Operate_Number1_Float
							Calculate_Result_Float = cos(Operate_Number1_Float);//进行cos计算(弧度)
						}
						else//第1个操作数是整数
						{
							Operate_Number1 = atol(Save_Operate_Number1);//获取第1个操作数。将获取的字符按键值转成长整型存储到Operate_Number1
							Calculate_Result_Float = cos(Operate_Number1);//进行cos计算(弧度)
						}
						LCD1602_Display_String(1, 1, "cos(");//在LCD1602的第1行第1列开始进行字符串显示
						LCD1602_Display_String(1, 5, Save_Operate_Number1);//在LCD1602的第1行第5列开始进行字符串显示
						LCD1602_Display_String(1, Input_Number+5, ")");//在LCD1602的第1行第Input_Number+5列开始进行字符串显示
						sprintf((char *)Result, "=%g", Calculate_Result_Float);//将Calculate_Result_Float以指定格式变成字符串保存到Result中
						LCD1602_Display_String(2, 1, Result);//在LCD1602的第二行第一列开始进行字符串显示
					break;
				case 'I': //根号√￣按键被按下
						if((strchr(Save_Operate_Number1, '.') != NULL))//第1个操作数有小数点
						{
							Operate_Number1_Float = atof(Save_Operate_Number1);//获取第一个操作数。将获取的字符按键值转成浮点型存储到Operate_Number1_Float
							Calculate_Result_Float = sqrt(Operate_Number1_Float);//进行sqrt计算
						}
						else//第1个操作数是整数
						{
							Operate_Number1 = atol(Save_Operate_Number1);//获取第1个操作数。将获取的字符按键值转成长整型存储到Operate_Number1
							Calculate_Result_Float = sqrt(Operate_Number1);//进行sqrt计算
						}
						LCD1602_Display_String(1, 1, "Sqrt(");//在LCD1602的第1行第1列开始进行字符串显示
						LCD1602_Display_String(1, 6, Save_Operate_Number1);//在LCD1602的第1行第6列开始进行字符串显示
						LCD1602_Display_String(1, Input_Number+6, ")");//在LCD1602的第1行第Input_Number+6列开始进行字符串显示
						sprintf((char *)Result, "=%g", Calculate_Result_Float);//将Calculate_Result_Float以指定格式变成字符串保存到Result中
						LCD1602_Display_String(2, 1, Result);//在LCD1602的第二行第一列开始进行字符串显示
					break;
	 			case 'J': //e^x按键被按下
						if((strchr(Save_Operate_Number1, '.') != NULL))//第1个操作数有小数点
						{
							Operate_Number1_Float = atof(Save_Operate_Number1);//获取第一个操作数。将获取的字符按键值转成浮点型存储到Operate_Number1_Float
							Calculate_Result_Float = exp(Operate_Number1_Float);//进行exp计算
						}
						else//第1个操作数是整数
						{
							Operate_Number1 = atol(Save_Operate_Number1);//获取第1个操作数。将获取的字符按键值转成长整型存储到Operate_Number1
							Calculate_Result_Float = exp(Operate_Number1);//进行exp计算
						}
						LCD1602_Display_String(1, 1, "e^(");//在LCD1602的第1行第1列开始进行字符串显示
						LCD1602_Display_String(1, 4, Save_Operate_Number1);//在LCD1602的第1行第4列开始进行字符串显示
						LCD1602_Display_String(1, Input_Number+4, ")");//在LCD1602的第1行第Input_Number+4列开始进行字符串显示
						sprintf((char *)Result, "=%g", Calculate_Result_Float);//将Calculate_Result_Float以指定格式变成字符串保存到Result中
						LCD1602_Display_String(2, 1, Result);//在LCD1602的第二行第一列开始进行字符串显示				
	 				break;
				case 'K': //sinh按键被按下
						if((strchr(Save_Operate_Number1, '.') != NULL))//第1个操作数有小数点
						{
							Operate_Number1_Float = atof(Save_Operate_Number1);//获取第一个操作数。将获取的字符按键值转成浮点型存储到Operate_Number1_Float
							Calculate_Result_Float = sinh(Operate_Number1_Float);//进行sinh计算(弧度)
						}
						else//第1个操作数是整数
						{
							Operate_Number1 = atol(Save_Operate_Number1);//获取第1个操作数。将获取的字符按键值转成长整型存储到Operate_Number1
							Calculate_Result_Float = sinh(Operate_Number1);//进行sinh计算(弧度)
						}
						LCD1602_Display_String(1, 1, "sinh(");//在LCD1602的第1行第1列开始进行字符串显示
						LCD1602_Display_String(1, 6, Save_Operate_Number1);//在LCD1602的第1行第6列开始进行字符串显示
						LCD1602_Display_String(1, Input_Number+6, ")");//在LCD1602的第1行第Input_Number+6列开始进行字符串显示
						sprintf((char *)Result, "=%g", Calculate_Result_Float);//将Calculate_Result_Float以指定格式变成字符串保存到Result中
						LCD1602_Display_String(2, 1, Result);//在LCD1602的第二行第一列开始进行字符串显示
					break;
				case 'L': //tan按键被按下
						if((strchr(Save_Operate_Number1, '.') != NULL))//第1个操作数有小数点
						{
							Operate_Number1_Float = atof(Save_Operate_Number1);//获取第一个操作数。将获取的字符按键值转成浮点型存储到Operate_Number1_Float
							Calculate_Result_Float = tan(Operate_Number1_Float);//进行tan计算(弧度)
						}
						else//第1个操作数是整数
						{
							Operate_Number1 = atol(Save_Operate_Number1);//获取第1个操作数。将获取的字符按键值转成长整型存储到Operate_Number1
							Calculate_Result_Float = tan(Operate_Number1);//进行tan计算(弧度)
						}
						LCD1602_Display_String(1, 1, "tan(");//在LCD1602的第1行第1列开始进行字符串显示
						LCD1602_Display_String(1, 5, Save_Operate_Number1);//在LCD1602的第1行第5列开始进行字符串显示
						LCD1602_Display_String(1, Input_Number+5, ")");//在LCD1602的第1行第Input_Number+5列开始进行字符串显示
						sprintf((char *)Result, "=%g", Calculate_Result_Float);//将Calculate_Result_Float以指定格式变成字符串保存到Result中
						LCD1602_Display_String(2, 1, Result);//在LCD1602的第二行第一列开始进行字符串显示
					break;
				case 'N': //n！按键被按下求n的阶乘(小数会强制转换为整数)
						Calculate_Result_Float = 1;//阶乘从1开始
						if((strchr(Save_Operate_Number1, '.') != NULL))//第1个操作数有小数点
						{
							Operate_Number1_Float = atof(Save_Operate_Number1);//获取第一个操作数。将获取的字符按键值转成浮点型存储到Operate_Number1_Float
							Operate_Number1 = (int32_t)Operate_Number1_Float;//小数转换成整数
							for (i=1; i<=Operate_Number1; i++)
							{
								Calculate_Result_Float = Calculate_Result_Float * i;//计算n!的阶乘
							}
						}
						else//第1个操作数是整数
						{
							Operate_Number1 = atol(Save_Operate_Number1);//获取第1个操作数。将获取的字符按键值转成长整型存储到Operate_Number1
							for (i=1; i<=Operate_Number1; i++)
							{
								Calculate_Result_Float = Calculate_Result_Float * i;//计算n!的阶乘
							}
						}
						LCD1602_Display_String(1, 1, "fact(");//在LCD1602的第1行第1列开始进行字符串显示
						LCD1602_Display_String(1, 6, Save_Operate_Number1);//在LCD1602的第1行第6列开始进行字符串显示
						LCD1602_Display_String(1, Input_Number+6, ")");//在LCD1602的第1行第Input_Number+6列开始进行字符串显示
						sprintf((char *)Result, "=%g", Calculate_Result_Float);//将Calculate_Result_Float以指定格式变成字符串保存到Result中
						LCD1602_Display_String(2, 1, Result);//在LCD1602的第二行第一列开始进行字符串显示
					break;
				case 'P': //cosh按键被按下
						if((strchr(Save_Operate_Number1, '.') != NULL))//第1个操作数有小数点
						{
							Operate_Number1_Float = atof(Save_Operate_Number1);//获取第一个操作数。将获取的字符按键值转成浮点型存储到Operate_Number1_Float
							Calculate_Result_Float = cosh(Operate_Number1_Float);//进行cosh计算(弧度)
						}
						else//第1个操作数是整数
						{
							Operate_Number1 = atol(Save_Operate_Number1);//获取第1个操作数。将获取的字符按键值转成长整型存储到Operate_Number1
							Calculate_Result_Float = cosh(Operate_Number1);//进行cosh计算(弧度)
						}
						LCD1602_Display_String(1, 1, "cosh(");//在LCD1602的第1行第1列开始进行字符串显示
						LCD1602_Display_String(1, 6, Save_Operate_Number1);//在LCD1602的第1行第6列开始进行字符串显示
						LCD1602_Display_String(1, Input_Number+6, ")");//在LCD1602的第1行第Input_Number+6列开始进行字符串显示
						sprintf((char *)Result, "=%g", Calculate_Result_Float);//将Calculate_Result_Float以指定格式变成字符串保存到Result中
						LCD1602_Display_String(2, 1, Result);//在LCD1602的第二行第一列开始进行字符串显示
					break;
				case 'Q': //asin按键被按下
						if((strchr(Save_Operate_Number1, '.') != NULL))//第1个操作数有小数点
						{
							Operate_Number1_Float = atof(Save_Operate_Number1);//获取第一个操作数。将获取的字符按键值转成浮点型存储到Operate_Number1_Float
							Calculate_Result_Float = asin(Operate_Number1_Float);//进行asin计算(弧度)
						}
						else//第1个操作数是整数
						{
							Operate_Number1 = atol(Save_Operate_Number1);//获取第1个操作数。将获取的字符按键值转成长整型存储到Operate_Number1
							Calculate_Result_Float = asin(Operate_Number1);//进行asin计算(弧度)
						}
						LCD1602_Display_String(1, 1, "asin(");//在LCD1602的第1行第1列开始进行字符串显示
						LCD1602_Display_String(1, 6, Save_Operate_Number1);//在LCD1602的第1行第6列开始进行字符串显示
						LCD1602_Display_String(1, Input_Number+6, ")");//在LCD1602的第1行第Input_Number+6列开始进行字符串显示
						sprintf((char *)Result, "=%g", Calculate_Result_Float);//将Calculate_Result_Float以指定格式变成字符串保存到Result中
						LCD1602_Display_String(2, 1, Result);//在LCD1602的第二行第一列开始进行字符串显示
					break;
				default:
					break;
			}			
		}
	}
	else if(Key_Value_Temp == '=')//如果等于号'='被按下，则对输入的操作数进行对应的+、-、*和/四则运算及幂运算
	{
		if((Operate_Symbol == 0) || (Calculate_Complete_Flag == 1))//没有输入操作符之前或者计算完成之后通过'='按键对系统清屏清零。否则进行正常的系统计算
		{
			LCD1602_Clear_Screen();//LCD1602清屏
			Input_Number = 0;//输入的字符个数清零
			Operate_Number1 = 0;//参与计算的第1个操作数清零
			Operate_Number2 = 0;//参与计算的第2个操作数清零
			Operate_Symbol = 0;//参与计算的操作符清零
			Save_Operate_Number2_Position=0;//记录保存第2个操作数在Save_Operate_Number2数组中的下标位置清零
			Operate_Symbol_Flag = 0;//参与计算的操作符标志位清零
			Calculate_Result = 0;//计算结果清零
			Operate_Number2_Flag = 0;//参与计算的第2个操作数标志位清零
			Calculate_Complete_Flag=0;//计算完成标志位清零
			Operate_Number1_Float = 0;//参与计算的第1个操作数是浮点型清零
			Operate_Number2_Float = 0;//参与计算的第2个操作数是浮点型清零
			Calculate_Result_Float  = 0;//计算的结果是浮点型清零
			for(i=0; i<11; i++)//数组清零
			{
				Save_Operate_Number1[i] = 0;//清零
			}
			for(i=0; i<11; i++)//数组清零
			{
				Save_Operate_Number2[i] = 0;//清零
			}
			for(i=0; i<12; i++)//数组清零
			{
				Result[i] = 0;//清零
			}
		}
		else if(Operate_Number2_Flag == 1)//正常进行四则运算。参与计算的第2个操作数标志位置1，只有在输入完第二个操作数以后才能再按等于号'='进行四则远算及幂运算
		{
			if((strchr(Save_Operate_Number1, '.') != NULL) || (strchr(Save_Operate_Number2, '.') != NULL))//第1操作数或者第2个操作数有小数点
			{
				Operate_Number1_Float = atof(Save_Operate_Number1);//获取第一个操作数。将获取的字符按键值转成浮点型存储到Operate_Number1_Float
				Operate_Number2_Float = atof(Save_Operate_Number2);//获取第二个操作数。将获取的字符按键值转成浮点型存储到Operate_Number2_Float
				
				switch(Operate_Symbol)//根据操作符进行匹配对应的四则运算
				{
					case '+':	//加法
							Calculate_Result_Float = (Operate_Number1_Float + Operate_Number2_Float);//加法运算，注意这三个参数在定义时数据类型“必须”一致，否则运算结果会溢出出错
							sprintf((char *)Result, "=%g", Calculate_Result_Float);//将Calculate_Result_Float以指定格式变成字符串保存到Result中
						break;
					case '-':	//减法
							Calculate_Result_Float = (Operate_Number1_Float - Operate_Number2_Float);//减法运算，注意这三个参数在定义时数据类型“必须”一致，否则运算结果会溢出出错
							sprintf((char *)Result, "=%g", Calculate_Result_Float);//将Calculate_Result_Float以指定格式变成字符串保存到Result中
						break;
					case '*':	//乘法
							Calculate_Result_Float = (Operate_Number1_Float * Operate_Number2_Float);//乘法运算，注意这三个参数在定义时数据类型“必须”一致，否则运算结果会溢出出错
							sprintf((char *)Result, "=%g", Calculate_Result_Float);//将Calculate_Result_Float以指定格式变成字符串保存到Result中
						break;
					case '/':	//除法
							if(Operate_Number2_Float == 0)//输入的第二个操作数为0，除数为0
							{
								sprintf((char *)Result, "=%s", "Error");//除数为0会报错显示Error
							}
							else//除法运算
							{
								sprintf((char *)Result, "=%g", (Operate_Number1_Float / Operate_Number2_Float));//将Calculate_Result以指定格式变成字符串保存到Result中							
							}
						break;
					case '^':	//幂运算
							Calculate_Result_Float = pow(Operate_Number1_Float, Operate_Number2_Float);//幂运算
							sprintf((char *)Result, "=%g", Calculate_Result_Float);//将Calculate_Result_Float以指定格式变成字符串保存到Result中
						break;
					default:
						break;
				}
			}
			else //第1操作数或者第2个操作数都没有小数
			{
				Operate_Number1 = atol(Save_Operate_Number1);//获取第一个操作数。将获取的字符按键值转成长整型存储到Operate_Number1
				Operate_Number2 = atol(Save_Operate_Number2);//获取第二个操作数。将获取的字符按键值转成长整型存储到Operate_Number2

				switch(Operate_Symbol)//根据操作符进行匹配对应的四则运算
				{
					case '+':	//加法
							Calculate_Result = (Operate_Number1 + Operate_Number2);//加法运算，注意这三个参数在定义时数据类型“必须”一致，否则运算结果会溢出出错
							sprintf((char *)Result, "=%d", Calculate_Result);//将Calculate_Result以ld(必须必须是长整型格式)格式变成字符串保存到Result中
						break;
					case '-':	//减法
							Calculate_Result = (Operate_Number1 - Operate_Number2);//减法运算，注意这三个参数在定义时数据类型“必须”一致，否则运算结果会溢出出错
							sprintf((char *)Result, "=%d", Calculate_Result);//将Calculate_Result以ld(必须必须是长整型格式)格式变成字符串保存到Result中
						break;
					case '*':	//乘法
							Calculate_Result = (Operate_Number1 * Operate_Number2);//乘法运算，注意这三个参数在定义时数据类型“必须”一致，否则运算结果会溢出出错
							sprintf((char *)Result, "=%d", Calculate_Result);//将Calculate_Result以ld(必须必须是长整型格式)格式变成字符串保存到Result中
						break;
					case '/':	//除法
							if(Operate_Number2 == 0)//输入的第二个操作数为0，除数为0
							{
								sprintf((char *)Result, "=%s", "Error");//除数为0会报错显示Error
							}
							else if(Operate_Number1%Operate_Number2 == 0)//能够整除
							{
								Calculate_Result = (Operate_Number1 / Operate_Number2);//除法运算，注意这三个参数在定义时数据类型“必须”一致，否则运算结果会溢出出错	
								sprintf((char *)Result, "=%d", Calculate_Result);//将Calculate_Result以ld(必须必须是长整型格式)格式变成字符串保存到Result中						
							}
							else//不能整除，除不尽有小数
							{
								sprintf((char *)Result, "=%g", (Operate_Number1 / (float)Operate_Number2));//将Calculate_Result以ld(必须必须是长整型格式)格式变成字符串保存到Result中
							}
						break;
					case '^':	//幂运算
							Calculate_Result_Float = pow(Operate_Number1, Operate_Number2);//幂运算
							sprintf((char *)Result, "=%g", Calculate_Result_Float);//将Calculate_Result_Float以指定格式变成字符串保存到Result中
						break;
					default:
						break;
				}
			}
			
			LCD1602_Display_String(2, 1, Result);//在LCD1602的第二行第一列开始进行字符串显示
			Operate_Symbol = 0;//参与计算的操作符清零
			Calculate_Complete_Flag=1;//计算完成标志位置1
		}
	}
	else if(Key_Value_Temp == 'M')//如果Clear按键被按下，则清屏
	{
			LCD1602_Clear_Screen();//LCD1602清屏
			Input_Number = 0;//输入的字符个数清零
			Operate_Number1 = 0;//参与计算的第1个操作数清零
			Operate_Number2 = 0;//参与计算的第2个操作数清零
			Operate_Symbol = 0;//参与计算的操作符清零
			Save_Operate_Number2_Position=0;//记录保存第2个操作数在Save_Operate_Number2数组中的下标位置清零
			Operate_Symbol_Flag = 0;//参与计算的操作符标志位清零
			Calculate_Result = 0;//计算结果清零
			Operate_Number2_Flag = 0;//参与计算的第2个操作数标志位清零
			Calculate_Complete_Flag=0;//计算完成标志位清零
			Operate_Number1_Float = 0;//参与计算的第1个操作数是浮点型清零
			Operate_Number2_Float = 0;//参与计算的第2个操作数是浮点型清零
			Calculate_Result_Float  = 0;//计算的结果是浮点型清零
			for(i=0; i<11; i++)//数组清零
			{
				Save_Operate_Number1[i] = 0;//清零
			}
			for(i=0; i<11; i++)//数组清零
			{
				Save_Operate_Number2[i] = 0;//清零
			}
			for(i=0; i<12; i++)//数组清零
			{
				Result[i] = 0;//清零
			}	
	}
}
