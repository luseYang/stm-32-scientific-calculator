/* Includes����ͷ�ļ� ------------------------------------------------------------------*/
#include "systick_delay.h"
#include "key.h"
#include "lcd1602.h"
#include "Calculator.h"

/* Global Variableȫ�ֱ��� -----------------------------------------------------------*/
//4���ֽ�32λ֧�ּ��㷶Χ��-2147483648 to 2147483647 
//������С��ʱ��ûС��ʱ�ֱ������������
 
int main(void)
 {	 
	KEY_Init();//������ʼ������
    LCD1602_Init();//LCD1602��ʼ��
	while(1)
	{	
		Get_Operate_Number_And_Operate_Symbol_And_Calculate();//��ȡ��������Ĳ������Ͳ��������Լ������������㡣
	}	 
}

