#ifndef __KEY_H
#define __KEY_H
#include "bit_band.h"
#include "systick_delay.h"

#define  PB0 	OUTPUTB(0) //PB0ʹ��bit_bandλ���궨�巽��
#define  PB1 	OUTPUTB(1) //PB1ʹ��bit_bandλ���궨�巽��
#define  PB2 	OUTPUTB(2) //PB2ʹ��bit_bandλ���궨�巽��
#define  PB3 	OUTPUTB(3) //PB3ʹ��bit_bandλ���궨�巽��
#define  PB4 	OUTPUTB(4) //PB4ʹ��bit_bandλ���궨�巽��
#define  PB5 	OUTPUTB(5) //PB5ʹ��bit_bandλ���궨�巽��
#define  PB6 	OUTPUTB(6) //PB6ʹ��bit_bandλ���궨�巽��
#define  PB7 	OUTPUTB(7) //PB7ʹ��bit_bandλ���궨�巽��

#define  PB8 	INPUTB(8)  //PB8ʹ��bit_bandλ���궨�巽��
#define  PB9 	INPUTB(9)  //PB9ʹ��bit_bandλ���궨�巽��
#define  PB10 	INPUTB(10) //PB10ʹ��bit_bandλ���궨�巽��
#define  PB11 	INPUTB(11) //PB11ʹ��bit_bandλ���궨�巽��

void KEY_Init(void);//������ʼ��
u8 Get_Key_Value(void);//��ȡ���󰴼���ֵ�������ڶ�Ӧ��.h�ļ�����������

#endif
