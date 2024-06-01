/* Includes����ͷ�ļ�*/
#include "Calculator.h"
#include "lcd1602.h"
#include "key.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "math.h"

/* Global Variableȫ�ֱ���*/
u8 Key_Value_Temp=0;//��ȡ�İ���ֵ��ʱ�洢����
int32_t Operate_Number1 = 0;//�������ĵ�1��������������
int32_t Operate_Number2 = 0;//�������ĵ�2��������������
u8 Operate_Symbol  = 0;//�������Ĳ�����
char Save_Operate_Number1[11] = {0};//���������1
char Save_Operate_Number2[11] = {0};//���������2
u8 Save_Operate_Number2_Position=0;//��¼�����2����������Save_Operate_Number2�����е��±�λ��
int32_t Calculate_Result  = 0;//����Ľ��������
char Result[12]={0};//�������Ľ��
u8 Input_Number=0;//������ַ�������������¼Ӧ����ʾ��LCD1602����һ�е�
u8 Operate_Symbol_Flag=0;//�������Ĳ�������־λ��ֻ�������˲������Ժ󣬲��ܻ�ȡ�ڶ�������������Ϊ��������˳���ǵ�һ�������������������ڶ���������
u8 Operate_Number2_Flag=0;//�������ĵ�2����������־λ��ֻ�еڶ���������������ϣ��ٰ����ں�'='����Ч
u8 Calculate_Complete_Flag=0;//������ɱ�־λ

float Operate_Number1_Float = 0;//�������ĵ�1���������Ǹ�����
float Operate_Number2_Float = 0;//�������ĵ�2���������Ǹ�����
float Calculate_Result_Float  = 0;//����Ľ���Ǹ�����

/*
��ȡ��������Ĳ������Ͳ��������Լ���������Ϳ�ѧ����
*/
void Get_Operate_Number_And_Operate_Symbol_And_Calculate(void)
{
	u8 i=0;//��������
	
	Key_Value_Temp = Get_Key_Value();//��ȡ����ֵ
	if(((Key_Value_Temp >= '0') && (Key_Value_Temp <= '9')) || (Key_Value_Temp == '.'))//��ȡ���������������0��9����С����
	{
		if((Operate_Symbol_Flag == 1) && (Operate_Number2_Flag == 1) && (Operate_Symbol == 0))//����֧���������㣬������һ�κ��ð�on/c�������㣬ֱ��������ܽ�����һ�μ���
		{
			LCD1602_Clear_Screen();//LCD1602����
			Input_Number = 0;//������ַ���������
			Operate_Number1 = 0;//�������ĵ�1������������
			Operate_Number2 = 0;//�������ĵ�2������������
			Operate_Symbol = 0;//�������Ĳ���������
			Save_Operate_Number2_Position=0;//��¼�����2����������Save_Operate_Number2�����е��±�λ������
			Operate_Symbol_Flag = 0;//�������Ĳ�������־λ����
			Calculate_Result = 0;//����������
			Operate_Number2_Flag = 0;//�������ĵ�2����������־λ����
			Calculate_Complete_Flag=0;//������ɱ�־λ����
			Operate_Number1_Float = 0;//�������ĵ�1���������Ǹ���������
			Operate_Number2_Float = 0;//�������ĵ�2���������Ǹ���������
			Calculate_Result_Float  = 0;//����Ľ���Ǹ���������
			for(i=0; i<11; i++)//��������
			{
				Save_Operate_Number1[i] = 0;//����
			}
			for(i=0; i<11; i++)//��������
			{
				Save_Operate_Number2[i] = 0;//����
			}
			for(i=0; i<12; i++)//��������
			{
				Result[i] = 0;//����
			}			
		}

		if(Operate_Symbol_Flag == 0)//��ȡ����ĵ�һ��������
		{
			Save_Operate_Number1[Input_Number] = Key_Value_Temp;//����ȡ���ַ�����ֵ���浽Save_Operate_Number1������
			Input_Number++;//��������һ���ַ���������һ�Σ�������¼Ӧ����ʾ��LCD1602����һ�е�
			LCD1602_Display_Character(1, Input_Number, Key_Value_Temp);//��LCD1602��1�У���Input_Number�е�λ�ÿ�ʼ������ʾ����Ķ�Ӧ���ַ�
		}
		else if(Operate_Symbol_Flag == 1)//��ȡ����ĵڶ�����������ֻ����������+��-��*��/����������󣬲�������ڶ���������
		{
			Save_Operate_Number2[Save_Operate_Number2_Position++] = Key_Value_Temp;//����ȡ���ַ�����ֵ���浽Save_Operate_Number2������
			Input_Number++;//��������һ���ַ���������һ�Σ�������¼Ӧ����ʾ��LCD1602����һ�е�
			LCD1602_Display_Character(1, Input_Number, Key_Value_Temp);//��LCD1602��1�У���Input_Number�е�λ�ÿ�ʼ������ʾ����Ķ�Ӧ���ַ�
			Operate_Number2_Flag = 1;//�������ĵ�2����������־λ��1��˵�����԰��µ��ں�'='�������������
		}
	}
	else if((Key_Value_Temp == '+') || (Key_Value_Temp == '-') || (Key_Value_Temp == '*') || (Key_Value_Temp == '/')  || (Key_Value_Temp == '^') )//��ȡ����+��-��*��/�����������x^y������
	{
		Input_Number++;//��������һ���ַ���������һ�Σ�������¼Ӧ����ʾ��LCD1602����һ�е�
		Operate_Symbol = Key_Value_Temp;//��¼����Ĳ�������������ݲ��������ܽ��ж�Ӧ����������
		LCD1602_Display_Character(1, Input_Number, Key_Value_Temp);//��LCD1602��1�У���Input_Number�е�λ�ÿ�ʼ������ʾ����Ķ�Ӧ���ַ�
		Operate_Symbol_Flag = 1;//�������Ĳ�������־λ��1��ֻ����������+��-��*��/����������󣬲�������ڶ���������
	}
	else if((Key_Value_Temp == 'A') || (Key_Value_Temp == 'B') || (Key_Value_Temp == 'C') || (Key_Value_Temp == 'D') || \
	        (Key_Value_Temp == 'E') || (Key_Value_Temp == 'G') || (Key_Value_Temp == 'H') || (Key_Value_Temp == 'I') || \
			(Key_Value_Temp == 'J') || (Key_Value_Temp == 'K') || (Key_Value_Temp == 'L') || (Key_Value_Temp == 'N') || \
			(Key_Value_Temp == 'P') || (Key_Value_Temp == 'Q'))//��ȡln��tanh��acos��sin��log10��atan��cos���̣����š�e^x��sinh��tan��n!��cosh��asin
	{
		if(Input_Number != 0)//�в���������ʱ���ܽ�������
		{
			switch(Key_Value_Temp)
			{
				case 'A': //ln����������
						if((strchr(Save_Operate_Number1, '.') != NULL))//��1����������С����
						{
							Operate_Number1_Float = atof(Save_Operate_Number1);//��ȡ��һ��������������ȡ���ַ�����ֵת�ɸ����ʹ洢��Operate_Number1_Float
							Calculate_Result_Float = log(Operate_Number1_Float);//����ln����
						}
						else//��1��������������
						{
							Operate_Number1 = atol(Save_Operate_Number1);//��ȡ��1��������������ȡ���ַ�����ֵת�ɳ����ʹ洢��Operate_Number1
							Calculate_Result_Float = log(Operate_Number1);//����ln����
						}
						LCD1602_Display_String(1, 1, "ln(");//��LCD1602�ĵ�1�е�1�п�ʼ�����ַ�����ʾ
						LCD1602_Display_String(1, 4, Save_Operate_Number1);//��LCD1602�ĵ�1�е�4�п�ʼ�����ַ�����ʾ
						LCD1602_Display_String(1, Input_Number+4, ")");//��LCD1602�ĵ�1�е�Input_Number+4�п�ʼ�����ַ�����ʾ
						sprintf((char *)Result, "=%g", Calculate_Result_Float);//��Calculate_Result_Float��ָ����ʽ����ַ������浽Result��
						LCD1602_Display_String(2, 1, Result);//��LCD1602�ĵڶ��е�һ�п�ʼ�����ַ�����ʾ
					break;
				case 'B': //tanh����������
						if((strchr(Save_Operate_Number1, '.') != NULL))//��1����������С����
						{
							Operate_Number1_Float = atof(Save_Operate_Number1);//��ȡ��һ��������������ȡ���ַ�����ֵת�ɸ����ʹ洢��Operate_Number1_Float
							Calculate_Result_Float = tanh(Operate_Number1_Float);//����tanh����(����)
						}
						else//��1��������������
						{
							Operate_Number1 = atol(Save_Operate_Number1);//��ȡ��1��������������ȡ���ַ�����ֵת�ɳ����ʹ洢��Operate_Number1
							Calculate_Result_Float = tanh(Operate_Number1);//����tanh����(����)
						}
						LCD1602_Display_String(1, 1, "tanh(");//��LCD1602�ĵ�1�е�1�п�ʼ�����ַ�����ʾ
						LCD1602_Display_String(1, 6, Save_Operate_Number1);//��LCD1602�ĵ�1�е�6�п�ʼ�����ַ�����ʾ
						LCD1602_Display_String(1, Input_Number+6, ")");//��LCD1602�ĵ�1�е�Input_Number+6�п�ʼ�����ַ�����ʾ
						sprintf((char *)Result, "=%g", Calculate_Result_Float);//��Calculate_Result_Float��ָ����ʽ����ַ������浽Result��
						LCD1602_Display_String(2, 1, Result);//��LCD1602�ĵڶ��е�һ�п�ʼ�����ַ�����ʾ
					break;
				case 'C': //acos����������
						if((strchr(Save_Operate_Number1, '.') != NULL))//��1����������С����
						{
							Operate_Number1_Float = atof(Save_Operate_Number1);//��ȡ��һ��������������ȡ���ַ�����ֵת�ɸ����ʹ洢��Operate_Number1_Float
							Calculate_Result_Float = acos(Operate_Number1_Float);//����acos����(����)
						}
						else//��1��������������
						{
							Operate_Number1 = atol(Save_Operate_Number1);//��ȡ��1��������������ȡ���ַ�����ֵת�ɳ����ʹ洢��Operate_Number1
							Calculate_Result_Float = acos(Operate_Number1);//����acos����(����)
						}
						LCD1602_Display_String(1, 1, "acos(");//��LCD1602�ĵ�1�е�1�п�ʼ�����ַ�����ʾ
						LCD1602_Display_String(1, 6, Save_Operate_Number1);//��LCD1602�ĵ�1�е�6�п�ʼ�����ַ�����ʾ
						LCD1602_Display_String(1, Input_Number+6, ")");//��LCD1602�ĵ�1�е�Input_Number+6�п�ʼ�����ַ�����ʾ
						sprintf((char *)Result, "=%g", Calculate_Result_Float);//��Calculate_Result_Float��ָ����ʽ����ַ������浽Result��
						LCD1602_Display_String(2, 1, Result);//��LCD1602�ĵڶ��е�һ�п�ʼ�����ַ�����ʾ
					break;
				case 'D': //sin����������
						if((strchr(Save_Operate_Number1, '.') != NULL))//��1����������С����
						{
							Operate_Number1_Float = atof(Save_Operate_Number1);//��ȡ��һ��������������ȡ���ַ�����ֵת�ɸ����ʹ洢��Operate_Number1_Float
							Calculate_Result_Float = sin(Operate_Number1_Float);//����sin����(����)
						}
						else//��1��������������
						{
							Operate_Number1 = atol(Save_Operate_Number1);//��ȡ��1��������������ȡ���ַ�����ֵת�ɳ����ʹ洢��Operate_Number1
							Calculate_Result_Float = sin(Operate_Number1);//����sin����(����)
						}
						LCD1602_Display_String(1, 1, "sin(");//��LCD1602�ĵ�1�е�1�п�ʼ�����ַ�����ʾ
						LCD1602_Display_String(1, 5, Save_Operate_Number1);//��LCD1602�ĵ�1�е�5�п�ʼ�����ַ�����ʾ
						LCD1602_Display_String(1, Input_Number+5, ")");//��LCD1602�ĵ�1�е�Input_Number+5�п�ʼ�����ַ�����ʾ
						sprintf((char *)Result, "=%g", Calculate_Result_Float);//��Calculate_Result_Float��ָ����ʽ����ַ������浽Result��
						LCD1602_Display_String(2, 1, Result);//��LCD1602�ĵڶ��е�һ�п�ʼ�����ַ�����ʾ
					break;
				case 'E': //log10����������
						if((strchr(Save_Operate_Number1, '.') != NULL))//��1����������С����
						{
							Operate_Number1_Float = atof(Save_Operate_Number1);//��ȡ��һ��������������ȡ���ַ�����ֵת�ɸ����ʹ洢��Operate_Number1_Float
							Calculate_Result_Float = log10(Operate_Number1_Float);//����log10����
						}
						else//��1��������������
						{
							Operate_Number1 = atol(Save_Operate_Number1);//��ȡ��1��������������ȡ���ַ�����ֵת�ɳ����ʹ洢��Operate_Number1
							Calculate_Result_Float = log10(Operate_Number1);//����log10����
						}
						LCD1602_Display_String(1, 1, "log10(");//��LCD1602�ĵ�1�е�1�п�ʼ�����ַ�����ʾ
						LCD1602_Display_String(1, 7, Save_Operate_Number1);//��LCD1602�ĵ�1�е�7�п�ʼ�����ַ�����ʾ
						LCD1602_Display_String(1, Input_Number+7, ")");//��LCD1602�ĵ�1�е�Input_Number+7�п�ʼ�����ַ�����ʾ
						sprintf((char *)Result, "=%g", Calculate_Result_Float);//��Calculate_Result_Float��ָ����ʽ����ַ������浽Result��
						LCD1602_Display_String(2, 1, Result);//��LCD1602�ĵڶ��е�һ�п�ʼ�����ַ�����ʾ
					break;
				case 'G': //atan����������
						if((strchr(Save_Operate_Number1, '.') != NULL))//��1����������С����
						{
							Operate_Number1_Float = atof(Save_Operate_Number1);//��ȡ��һ��������������ȡ���ַ�����ֵת�ɸ����ʹ洢��Operate_Number1_Float
							Calculate_Result_Float = atan(Operate_Number1_Float);//����atan����(����)
						}
						else//��1��������������
						{
							Operate_Number1 = atol(Save_Operate_Number1);//��ȡ��1��������������ȡ���ַ�����ֵת�ɳ����ʹ洢��Operate_Number1
							Calculate_Result_Float = atan(Operate_Number1);//����atan����(����)
						}
						LCD1602_Display_String(1, 1, "atan(");//��LCD1602�ĵ�1�е�1�п�ʼ�����ַ�����ʾ
						LCD1602_Display_String(1, 6, Save_Operate_Number1);//��LCD1602�ĵ�1�е�6�п�ʼ�����ַ�����ʾ
						LCD1602_Display_String(1, Input_Number+6, ")");//��LCD1602�ĵ�1�е�Input_Number+6�п�ʼ�����ַ�����ʾ
						sprintf((char *)Result, "=%g", Calculate_Result_Float);//��Calculate_Result_Float��ָ����ʽ����ַ������浽Result��
						LCD1602_Display_String(2, 1, Result);//��LCD1602�ĵڶ��е�һ�п�ʼ�����ַ�����ʾ
					break;
				case 'H': //cos����������
						if((strchr(Save_Operate_Number1, '.') != NULL))//��1����������С����
						{
							Operate_Number1_Float = atof(Save_Operate_Number1);//��ȡ��һ��������������ȡ���ַ�����ֵת�ɸ����ʹ洢��Operate_Number1_Float
							Calculate_Result_Float = cos(Operate_Number1_Float);//����cos����(����)
						}
						else//��1��������������
						{
							Operate_Number1 = atol(Save_Operate_Number1);//��ȡ��1��������������ȡ���ַ�����ֵת�ɳ����ʹ洢��Operate_Number1
							Calculate_Result_Float = cos(Operate_Number1);//����cos����(����)
						}
						LCD1602_Display_String(1, 1, "cos(");//��LCD1602�ĵ�1�е�1�п�ʼ�����ַ�����ʾ
						LCD1602_Display_String(1, 5, Save_Operate_Number1);//��LCD1602�ĵ�1�е�5�п�ʼ�����ַ�����ʾ
						LCD1602_Display_String(1, Input_Number+5, ")");//��LCD1602�ĵ�1�е�Input_Number+5�п�ʼ�����ַ�����ʾ
						sprintf((char *)Result, "=%g", Calculate_Result_Float);//��Calculate_Result_Float��ָ����ʽ����ַ������浽Result��
						LCD1602_Display_String(2, 1, Result);//��LCD1602�ĵڶ��е�һ�п�ʼ�����ַ�����ʾ
					break;
				case 'I': //���ṣ̌�����������
						if((strchr(Save_Operate_Number1, '.') != NULL))//��1����������С����
						{
							Operate_Number1_Float = atof(Save_Operate_Number1);//��ȡ��һ��������������ȡ���ַ�����ֵת�ɸ����ʹ洢��Operate_Number1_Float
							Calculate_Result_Float = sqrt(Operate_Number1_Float);//����sqrt����
						}
						else//��1��������������
						{
							Operate_Number1 = atol(Save_Operate_Number1);//��ȡ��1��������������ȡ���ַ�����ֵת�ɳ����ʹ洢��Operate_Number1
							Calculate_Result_Float = sqrt(Operate_Number1);//����sqrt����
						}
						LCD1602_Display_String(1, 1, "Sqrt(");//��LCD1602�ĵ�1�е�1�п�ʼ�����ַ�����ʾ
						LCD1602_Display_String(1, 6, Save_Operate_Number1);//��LCD1602�ĵ�1�е�6�п�ʼ�����ַ�����ʾ
						LCD1602_Display_String(1, Input_Number+6, ")");//��LCD1602�ĵ�1�е�Input_Number+6�п�ʼ�����ַ�����ʾ
						sprintf((char *)Result, "=%g", Calculate_Result_Float);//��Calculate_Result_Float��ָ����ʽ����ַ������浽Result��
						LCD1602_Display_String(2, 1, Result);//��LCD1602�ĵڶ��е�һ�п�ʼ�����ַ�����ʾ
					break;
	 			case 'J': //e^x����������
						if((strchr(Save_Operate_Number1, '.') != NULL))//��1����������С����
						{
							Operate_Number1_Float = atof(Save_Operate_Number1);//��ȡ��һ��������������ȡ���ַ�����ֵת�ɸ����ʹ洢��Operate_Number1_Float
							Calculate_Result_Float = exp(Operate_Number1_Float);//����exp����
						}
						else//��1��������������
						{
							Operate_Number1 = atol(Save_Operate_Number1);//��ȡ��1��������������ȡ���ַ�����ֵת�ɳ����ʹ洢��Operate_Number1
							Calculate_Result_Float = exp(Operate_Number1);//����exp����
						}
						LCD1602_Display_String(1, 1, "e^(");//��LCD1602�ĵ�1�е�1�п�ʼ�����ַ�����ʾ
						LCD1602_Display_String(1, 4, Save_Operate_Number1);//��LCD1602�ĵ�1�е�4�п�ʼ�����ַ�����ʾ
						LCD1602_Display_String(1, Input_Number+4, ")");//��LCD1602�ĵ�1�е�Input_Number+4�п�ʼ�����ַ�����ʾ
						sprintf((char *)Result, "=%g", Calculate_Result_Float);//��Calculate_Result_Float��ָ����ʽ����ַ������浽Result��
						LCD1602_Display_String(2, 1, Result);//��LCD1602�ĵڶ��е�һ�п�ʼ�����ַ�����ʾ				
	 				break;
				case 'K': //sinh����������
						if((strchr(Save_Operate_Number1, '.') != NULL))//��1����������С����
						{
							Operate_Number1_Float = atof(Save_Operate_Number1);//��ȡ��һ��������������ȡ���ַ�����ֵת�ɸ����ʹ洢��Operate_Number1_Float
							Calculate_Result_Float = sinh(Operate_Number1_Float);//����sinh����(����)
						}
						else//��1��������������
						{
							Operate_Number1 = atol(Save_Operate_Number1);//��ȡ��1��������������ȡ���ַ�����ֵת�ɳ����ʹ洢��Operate_Number1
							Calculate_Result_Float = sinh(Operate_Number1);//����sinh����(����)
						}
						LCD1602_Display_String(1, 1, "sinh(");//��LCD1602�ĵ�1�е�1�п�ʼ�����ַ�����ʾ
						LCD1602_Display_String(1, 6, Save_Operate_Number1);//��LCD1602�ĵ�1�е�6�п�ʼ�����ַ�����ʾ
						LCD1602_Display_String(1, Input_Number+6, ")");//��LCD1602�ĵ�1�е�Input_Number+6�п�ʼ�����ַ�����ʾ
						sprintf((char *)Result, "=%g", Calculate_Result_Float);//��Calculate_Result_Float��ָ����ʽ����ַ������浽Result��
						LCD1602_Display_String(2, 1, Result);//��LCD1602�ĵڶ��е�һ�п�ʼ�����ַ�����ʾ
					break;
				case 'L': //tan����������
						if((strchr(Save_Operate_Number1, '.') != NULL))//��1����������С����
						{
							Operate_Number1_Float = atof(Save_Operate_Number1);//��ȡ��һ��������������ȡ���ַ�����ֵת�ɸ����ʹ洢��Operate_Number1_Float
							Calculate_Result_Float = tan(Operate_Number1_Float);//����tan����(����)
						}
						else//��1��������������
						{
							Operate_Number1 = atol(Save_Operate_Number1);//��ȡ��1��������������ȡ���ַ�����ֵת�ɳ����ʹ洢��Operate_Number1
							Calculate_Result_Float = tan(Operate_Number1);//����tan����(����)
						}
						LCD1602_Display_String(1, 1, "tan(");//��LCD1602�ĵ�1�е�1�п�ʼ�����ַ�����ʾ
						LCD1602_Display_String(1, 5, Save_Operate_Number1);//��LCD1602�ĵ�1�е�5�п�ʼ�����ַ�����ʾ
						LCD1602_Display_String(1, Input_Number+5, ")");//��LCD1602�ĵ�1�е�Input_Number+5�п�ʼ�����ַ�����ʾ
						sprintf((char *)Result, "=%g", Calculate_Result_Float);//��Calculate_Result_Float��ָ����ʽ����ַ������浽Result��
						LCD1602_Display_String(2, 1, Result);//��LCD1602�ĵڶ��е�һ�п�ʼ�����ַ�����ʾ
					break;
				case 'N': //n��������������n�Ľ׳�(С����ǿ��ת��Ϊ����)
						Calculate_Result_Float = 1;//�׳˴�1��ʼ
						if((strchr(Save_Operate_Number1, '.') != NULL))//��1����������С����
						{
							Operate_Number1_Float = atof(Save_Operate_Number1);//��ȡ��һ��������������ȡ���ַ�����ֵת�ɸ����ʹ洢��Operate_Number1_Float
							Operate_Number1 = (int32_t)Operate_Number1_Float;//С��ת��������
							for (i=1; i<=Operate_Number1; i++)
							{
								Calculate_Result_Float = Calculate_Result_Float * i;//����n!�Ľ׳�
							}
						}
						else//��1��������������
						{
							Operate_Number1 = atol(Save_Operate_Number1);//��ȡ��1��������������ȡ���ַ�����ֵת�ɳ����ʹ洢��Operate_Number1
							for (i=1; i<=Operate_Number1; i++)
							{
								Calculate_Result_Float = Calculate_Result_Float * i;//����n!�Ľ׳�
							}
						}
						LCD1602_Display_String(1, 1, "fact(");//��LCD1602�ĵ�1�е�1�п�ʼ�����ַ�����ʾ
						LCD1602_Display_String(1, 6, Save_Operate_Number1);//��LCD1602�ĵ�1�е�6�п�ʼ�����ַ�����ʾ
						LCD1602_Display_String(1, Input_Number+6, ")");//��LCD1602�ĵ�1�е�Input_Number+6�п�ʼ�����ַ�����ʾ
						sprintf((char *)Result, "=%g", Calculate_Result_Float);//��Calculate_Result_Float��ָ����ʽ����ַ������浽Result��
						LCD1602_Display_String(2, 1, Result);//��LCD1602�ĵڶ��е�һ�п�ʼ�����ַ�����ʾ
					break;
				case 'P': //cosh����������
						if((strchr(Save_Operate_Number1, '.') != NULL))//��1����������С����
						{
							Operate_Number1_Float = atof(Save_Operate_Number1);//��ȡ��һ��������������ȡ���ַ�����ֵת�ɸ����ʹ洢��Operate_Number1_Float
							Calculate_Result_Float = cosh(Operate_Number1_Float);//����cosh����(����)
						}
						else//��1��������������
						{
							Operate_Number1 = atol(Save_Operate_Number1);//��ȡ��1��������������ȡ���ַ�����ֵת�ɳ����ʹ洢��Operate_Number1
							Calculate_Result_Float = cosh(Operate_Number1);//����cosh����(����)
						}
						LCD1602_Display_String(1, 1, "cosh(");//��LCD1602�ĵ�1�е�1�п�ʼ�����ַ�����ʾ
						LCD1602_Display_String(1, 6, Save_Operate_Number1);//��LCD1602�ĵ�1�е�6�п�ʼ�����ַ�����ʾ
						LCD1602_Display_String(1, Input_Number+6, ")");//��LCD1602�ĵ�1�е�Input_Number+6�п�ʼ�����ַ�����ʾ
						sprintf((char *)Result, "=%g", Calculate_Result_Float);//��Calculate_Result_Float��ָ����ʽ����ַ������浽Result��
						LCD1602_Display_String(2, 1, Result);//��LCD1602�ĵڶ��е�һ�п�ʼ�����ַ�����ʾ
					break;
				case 'Q': //asin����������
						if((strchr(Save_Operate_Number1, '.') != NULL))//��1����������С����
						{
							Operate_Number1_Float = atof(Save_Operate_Number1);//��ȡ��һ��������������ȡ���ַ�����ֵת�ɸ����ʹ洢��Operate_Number1_Float
							Calculate_Result_Float = asin(Operate_Number1_Float);//����asin����(����)
						}
						else//��1��������������
						{
							Operate_Number1 = atol(Save_Operate_Number1);//��ȡ��1��������������ȡ���ַ�����ֵת�ɳ����ʹ洢��Operate_Number1
							Calculate_Result_Float = asin(Operate_Number1);//����asin����(����)
						}
						LCD1602_Display_String(1, 1, "asin(");//��LCD1602�ĵ�1�е�1�п�ʼ�����ַ�����ʾ
						LCD1602_Display_String(1, 6, Save_Operate_Number1);//��LCD1602�ĵ�1�е�6�п�ʼ�����ַ�����ʾ
						LCD1602_Display_String(1, Input_Number+6, ")");//��LCD1602�ĵ�1�е�Input_Number+6�п�ʼ�����ַ�����ʾ
						sprintf((char *)Result, "=%g", Calculate_Result_Float);//��Calculate_Result_Float��ָ����ʽ����ַ������浽Result��
						LCD1602_Display_String(2, 1, Result);//��LCD1602�ĵڶ��е�һ�п�ʼ�����ַ�����ʾ
					break;
				default:
					break;
			}			
		}
	}
	else if(Key_Value_Temp == '=')//������ں�'='�����£��������Ĳ��������ж�Ӧ��+��-��*��/�������㼰������
	{
		if((Operate_Symbol == 0) || (Calculate_Complete_Flag == 1))//û�����������֮ǰ���߼������֮��ͨ��'='������ϵͳ�������㡣�������������ϵͳ����
		{
			LCD1602_Clear_Screen();//LCD1602����
			Input_Number = 0;//������ַ���������
			Operate_Number1 = 0;//�������ĵ�1������������
			Operate_Number2 = 0;//�������ĵ�2������������
			Operate_Symbol = 0;//�������Ĳ���������
			Save_Operate_Number2_Position=0;//��¼�����2����������Save_Operate_Number2�����е��±�λ������
			Operate_Symbol_Flag = 0;//�������Ĳ�������־λ����
			Calculate_Result = 0;//����������
			Operate_Number2_Flag = 0;//�������ĵ�2����������־λ����
			Calculate_Complete_Flag=0;//������ɱ�־λ����
			Operate_Number1_Float = 0;//�������ĵ�1���������Ǹ���������
			Operate_Number2_Float = 0;//�������ĵ�2���������Ǹ���������
			Calculate_Result_Float  = 0;//����Ľ���Ǹ���������
			for(i=0; i<11; i++)//��������
			{
				Save_Operate_Number1[i] = 0;//����
			}
			for(i=0; i<11; i++)//��������
			{
				Save_Operate_Number2[i] = 0;//����
			}
			for(i=0; i<12; i++)//��������
			{
				Result[i] = 0;//����
			}
		}
		else if(Operate_Number2_Flag == 1)//���������������㡣�������ĵ�2����������־λ��1��ֻ����������ڶ����������Ժ�����ٰ����ں�'='��������Զ�㼰������
		{
			if((strchr(Save_Operate_Number1, '.') != NULL) || (strchr(Save_Operate_Number2, '.') != NULL))//��1���������ߵ�2����������С����
			{
				Operate_Number1_Float = atof(Save_Operate_Number1);//��ȡ��һ��������������ȡ���ַ�����ֵת�ɸ����ʹ洢��Operate_Number1_Float
				Operate_Number2_Float = atof(Save_Operate_Number2);//��ȡ�ڶ���������������ȡ���ַ�����ֵת�ɸ����ʹ洢��Operate_Number2_Float
				
				switch(Operate_Symbol)//���ݲ���������ƥ���Ӧ����������
				{
					case '+':	//�ӷ�
							Calculate_Result_Float = (Operate_Number1_Float + Operate_Number2_Float);//�ӷ����㣬ע�������������ڶ���ʱ�������͡����롱һ�£��������������������
							sprintf((char *)Result, "=%g", Calculate_Result_Float);//��Calculate_Result_Float��ָ����ʽ����ַ������浽Result��
						break;
					case '-':	//����
							Calculate_Result_Float = (Operate_Number1_Float - Operate_Number2_Float);//�������㣬ע�������������ڶ���ʱ�������͡����롱һ�£��������������������
							sprintf((char *)Result, "=%g", Calculate_Result_Float);//��Calculate_Result_Float��ָ����ʽ����ַ������浽Result��
						break;
					case '*':	//�˷�
							Calculate_Result_Float = (Operate_Number1_Float * Operate_Number2_Float);//�˷����㣬ע�������������ڶ���ʱ�������͡����롱һ�£��������������������
							sprintf((char *)Result, "=%g", Calculate_Result_Float);//��Calculate_Result_Float��ָ����ʽ����ַ������浽Result��
						break;
					case '/':	//����
							if(Operate_Number2_Float == 0)//����ĵڶ���������Ϊ0������Ϊ0
							{
								sprintf((char *)Result, "=%s", "Error");//����Ϊ0�ᱨ����ʾError
							}
							else//��������
							{
								sprintf((char *)Result, "=%g", (Operate_Number1_Float / Operate_Number2_Float));//��Calculate_Result��ָ����ʽ����ַ������浽Result��							
							}
						break;
					case '^':	//������
							Calculate_Result_Float = pow(Operate_Number1_Float, Operate_Number2_Float);//������
							sprintf((char *)Result, "=%g", Calculate_Result_Float);//��Calculate_Result_Float��ָ����ʽ����ַ������浽Result��
						break;
					default:
						break;
				}
			}
			else //��1���������ߵ�2����������û��С��
			{
				Operate_Number1 = atol(Save_Operate_Number1);//��ȡ��һ��������������ȡ���ַ�����ֵת�ɳ����ʹ洢��Operate_Number1
				Operate_Number2 = atol(Save_Operate_Number2);//��ȡ�ڶ���������������ȡ���ַ�����ֵת�ɳ����ʹ洢��Operate_Number2

				switch(Operate_Symbol)//���ݲ���������ƥ���Ӧ����������
				{
					case '+':	//�ӷ�
							Calculate_Result = (Operate_Number1 + Operate_Number2);//�ӷ����㣬ע�������������ڶ���ʱ�������͡����롱һ�£��������������������
							sprintf((char *)Result, "=%d", Calculate_Result);//��Calculate_Result��ld(��������ǳ����͸�ʽ)��ʽ����ַ������浽Result��
						break;
					case '-':	//����
							Calculate_Result = (Operate_Number1 - Operate_Number2);//�������㣬ע�������������ڶ���ʱ�������͡����롱һ�£��������������������
							sprintf((char *)Result, "=%d", Calculate_Result);//��Calculate_Result��ld(��������ǳ����͸�ʽ)��ʽ����ַ������浽Result��
						break;
					case '*':	//�˷�
							Calculate_Result = (Operate_Number1 * Operate_Number2);//�˷����㣬ע�������������ڶ���ʱ�������͡����롱һ�£��������������������
							sprintf((char *)Result, "=%d", Calculate_Result);//��Calculate_Result��ld(��������ǳ����͸�ʽ)��ʽ����ַ������浽Result��
						break;
					case '/':	//����
							if(Operate_Number2 == 0)//����ĵڶ���������Ϊ0������Ϊ0
							{
								sprintf((char *)Result, "=%s", "Error");//����Ϊ0�ᱨ����ʾError
							}
							else if(Operate_Number1%Operate_Number2 == 0)//�ܹ�����
							{
								Calculate_Result = (Operate_Number1 / Operate_Number2);//�������㣬ע�������������ڶ���ʱ�������͡����롱һ�£��������������������	
								sprintf((char *)Result, "=%d", Calculate_Result);//��Calculate_Result��ld(��������ǳ����͸�ʽ)��ʽ����ַ������浽Result��						
							}
							else//������������������С��
							{
								sprintf((char *)Result, "=%g", (Operate_Number1 / (float)Operate_Number2));//��Calculate_Result��ld(��������ǳ����͸�ʽ)��ʽ����ַ������浽Result��
							}
						break;
					case '^':	//������
							Calculate_Result_Float = pow(Operate_Number1, Operate_Number2);//������
							sprintf((char *)Result, "=%g", Calculate_Result_Float);//��Calculate_Result_Float��ָ����ʽ����ַ������浽Result��
						break;
					default:
						break;
				}
			}
			
			LCD1602_Display_String(2, 1, Result);//��LCD1602�ĵڶ��е�һ�п�ʼ�����ַ�����ʾ
			Operate_Symbol = 0;//�������Ĳ���������
			Calculate_Complete_Flag=1;//������ɱ�־λ��1
		}
	}
	else if(Key_Value_Temp == 'M')//���Clear���������£�������
	{
			LCD1602_Clear_Screen();//LCD1602����
			Input_Number = 0;//������ַ���������
			Operate_Number1 = 0;//�������ĵ�1������������
			Operate_Number2 = 0;//�������ĵ�2������������
			Operate_Symbol = 0;//�������Ĳ���������
			Save_Operate_Number2_Position=0;//��¼�����2����������Save_Operate_Number2�����е��±�λ������
			Operate_Symbol_Flag = 0;//�������Ĳ�������־λ����
			Calculate_Result = 0;//����������
			Operate_Number2_Flag = 0;//�������ĵ�2����������־λ����
			Calculate_Complete_Flag=0;//������ɱ�־λ����
			Operate_Number1_Float = 0;//�������ĵ�1���������Ǹ���������
			Operate_Number2_Float = 0;//�������ĵ�2���������Ǹ���������
			Calculate_Result_Float  = 0;//����Ľ���Ǹ���������
			for(i=0; i<11; i++)//��������
			{
				Save_Operate_Number1[i] = 0;//����
			}
			for(i=0; i<11; i++)//��������
			{
				Save_Operate_Number2[i] = 0;//����
			}
			for(i=0; i<12; i++)//��������
			{
				Result[i] = 0;//����
			}	
	}
}
