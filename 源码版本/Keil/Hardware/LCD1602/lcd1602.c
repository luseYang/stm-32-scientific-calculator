#include "lcd1602.h"
#include "key.h"
char Temp_Strings[16]={0};//����ת������ַ���

/**LCD1602��ʼ��.
*/
void LCD1602_Init(void)
{
	GPIO_InitTypeDef GPIO_Init_Structure;//GPIO��ʼ���ṹ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//��GPIOA��ʱ��
	
	GPIO_Init_Structure.GPIO_Pin = (GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5|
                                    GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13);//����ΪPA0/PA1/PA2/PA3/PA4/PA5/PA6/PA7/PA11/PA12/PA13
	
    GPIO_Init_Structure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
	GPIO_Init_Structure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
	GPIO_Init(GPIOA, &GPIO_Init_Structure);//GPIOA���ݽṹ�������ʼ��
	
	LCD1602_Write_Command(0x38);//��LCD1602��ʾ��5X7����8λ���ݽӿ�
	LCD1602_Write_Command(0x0C);//����ʾ������ʾ��꣬��겻��˸
	LCD1602_Write_Command(0x06);//дһ���ַ����ַָ���һ�ҹ���һ
}

/*
LCD1602д����
data��Ҫд�������
*/
void LCD1602_Write_Data(u16 data)
{
//	Delay_ms(1);//��ʱ1ms�����������漸���Ӻ�LCD1602�Ჿ��λ����ʾ����
	RS = 1;//RS�ߵ�ƽ
	RW = 0;//RW�͵�ƽ
	E = 0;//δ��������ǰEΪ�͵�ƽ
	GPIOA->BSRR = (data & 0x00FF);//��data�ߵ�ƽ���ͳ�ȥ
	GPIOA->BRR  = ((~data) & 0x00FF );//��data�͵�ƽ���ͳ�ȥ
	E = 1;//��EΪ�ߵ�ƽ�ڼ佫���ݷ��ͳ�ȥ
	Delay_ms(1);//��ʱ1ms
	E = 0;//EΪ�͵�ƽ
}

/*
LCD1602д����
command: Ҫд�������
*/
void LCD1602_Write_Command(u16 command)
{
//	Delay_ms(1);//��ʱ1ms�����������漸���Ӻ�LCD1602�Ჿ��λ����ʾ����
	RS = 0;//RS�͵�ƽ
	RW = 0;//RW�͵�ƽ
	E = 0;//δ��������ǰEΪ�͵�ƽ
	GPIOA->BSRR = (command & 0x00FF);//��command�ߵ�ƽ���ͳ�ȥ
	GPIOA->BRR  = ((~command) & 0x00FF );//��command�͵�ƽ���ͳ�ȥ
	E = 1;//��EΪ�ߵ�ƽ�ڼ佫���ݷ��ͳ�ȥ
	Delay_ms(1);//��ʱ1ms
	E = 0;//EΪ�͵�ƽ
}

/*
LCD1602����.

*/
void LCD1602_Clear_Screen(void)
{	
	LCD1602_Write_Command(0x01);//������ʾ����
}

/*
LCD1602����ڼ�����.
row_x: �ڼ��У�ȡֵ��Χ1-2
*/
void LCD1602_Clear_Row(u8 row_x)
{	
	u8 i=0;//��������
	
	if(row_x == 1)//�����һ��
	{
		LCD1602_Write_Command(0x80);//�ӵ�һ�еĵ�1λ�ÿ�ʼ��ʾ��
		for(i=0; i<16; i++)
		{
			LCD1602_Write_Data(' ');//д��Ҫ��ʾ�ַ����������ȫ����ʾ�ո�' '
		}
	}
	else if(row_x == 2)//����ڶ���
	{
		LCD1602_Write_Command(0x80+0x40);//�ӵڶ��еĵ�1λ��ʼ��ʾ
		for(i=0; i<16; i++)
		{
			LCD1602_Write_Data(' ');//д��Ҫ��ʾ�ַ����������ȫ����ʾ�ո�' '
		}
	}
}

/*
LCD1602ָ���ӵڼ��С��ڼ��п�ʼ������������
row_x: �ڼ��У�ȡֵ��Χ1-2
column_y: �ڼ��У�ȡֵ��Χ1-16
length: Ҫ����ĸ�����ȡֵ��Χ1-16
*/
void LCD1602_Clear_Row_Column_Length(u8 row_x, u8 column_y, u8 length)
{	
	u8 i=0;//��������
	
	if(length>16)//LCD1602һ�������ʾ16���ַ������Ȳ��ܳ���
	{
		length = 16;//ǿ������
	}
	
	if((column_y + length) > 16)//����ӵ�5�п�ʼ�������15������ͳ�����LCD��һ�����16����ʾ������ǿ���������ֻ�����LCD1602һ�е�16���ַ�
	{
		length = 17 - column_y;//�����Ǵӵ�5�п�ʼ�������15������ɼ����lengthΪ12��ʵ�����Ǵӵ�5�п�ʼ��һ����ʣ12����һֱ���������ĩβ��16���ַ�
	}
	
	if(row_x == 1)//�����һ��
	{
		LCD1602_Write_Command(0x80+column_y-1);//�ӵ�һ�еĵ�column_y-1λ�ÿ�ʼ��ʾ�������һ��Ŀ����Ҫ�ӵ�0��λ�ÿ�ʼ��ʾ����ʶ���˻���Ϊ��һ��λ����1����0
		for(i=0; i<length; i++)
		{
			LCD1602_Write_Data(' ');//д��Ҫ��ʾ�ַ����������ȫ����ʾ�ո�' '
		}
	}
	else if(row_x == 2)//����ڶ���
	{
		LCD1602_Write_Command(0x80+0x40+column_y-1);//�ӵڶ��еĵ�column_y-1λ��ʼ��ʾ�������һ��Ŀ����Ҫ�ӵ�0��λ�ÿ�ʼ��ʾ����ʶ���˻���Ϊ��һ��λ����1����0
		for(i=0; i<length; i++)
		{
			LCD1602_Write_Data(' ');//д��Ҫ��ʾ�ַ����������ȫ����ʾ�ո�' '
		}
	}
}

/*
LCD1602��ʾ�����ַ�.
row_x: �ڼ��У�ȡֵ��Χ1-2
column_y: �ڼ��У�ȡֵ��Χ1-16
character: Ҫ��ʾ�ĵ����ַ�
*/
void LCD1602_Display_Character(u8 row_x, u8 column_y, u8 character)
{	
	if(row_x == 1)//�ӵ�һ�п�ʼ��ʾ
	{
		LCD1602_Write_Command(0x80+column_y-1);//�ӵ�һ�еĵ�column_y-1λ�ÿ�ʼ��ʾ�������һ��Ŀ����Ҫ�ӵ�0��λ�ÿ�ʼ��ʾ����ʶ���˻���Ϊ��һ��λ����1����0
		LCD1602_Write_Data(character);//д��Ҫ��ʾ�ַ�
	}
	else if(row_x == 2)//�ӵڶ��п�ʼ��ʾ
	{
		LCD1602_Write_Command(0x80+0x40+column_y-1);//�ӵڶ��еĵ�column_y-1λ��ʼ��ʾ�������һ��Ŀ����Ҫ�ӵ�0��λ�ÿ�ʼ��ʾ����ʶ���˻���Ϊ��һ��λ����1����0
		LCD1602_Write_Data(character);//д��Ҫ��ʾ�ַ�
	}
}

/*
LCD1602��ʾ�ַ���.
row_x: �ڼ��У�ȡֵ��Χ1-2
column_y: �ڼ��У�ȡֵ��Χ1-16
string: Ҫ��ʾ���ַ���
*/
void LCD1602_Display_String(u8 row_x, u8 column_y, char *string)
{	
	u8 i=0;//��������
	
	if(row_x == 1)//�ӵ�һ�п�ʼ��ʾ
	{
		LCD1602_Write_Command(0x80+column_y-1);//�ӵ�һ�еĵ�column_yλ�ÿ�ʼ��ʾ�������һ��Ŀ����Ҫ�ӵ�0��λ�ÿ�ʼ��ʾ����ʶ���˻���Ϊ��һ��λ����1����0
		for(i=0; string[i]!='\0'; i++)//�ַ�����'\0'��β
		{
			LCD1602_Write_Data(string[i]);//д��Ҫ��ʾ�ַ�
		}
	}
	else if(row_x == 2)//�ӵڶ��п�ʼ��ʾ
	{
		LCD1602_Write_Command(0x80+0x40+column_y-1);//�ӵڶ��еĵ�column_yλ��ʼ��ʾ�������һ��Ŀ����Ҫ�ӵ�0��λ�ÿ�ʼ��ʾ����ʶ���˻���Ϊ��һ��λ����1����0
		for(i=0; string[i]!='\0'; i++)//�ַ�����'\0'��β
		{
			LCD1602_Write_Data(string[i]);//д��Ҫ��ʾ�ַ�
		}
	}
}