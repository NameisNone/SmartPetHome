#ifndef __KEY_H
#define __KEY_H	 
#include "stm32f10x.h"

//#define KEY_WKUP    GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) //��ȡ����WKUP
#define KEY1    		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)//��ȡ����0
#define KEY2    		GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)//��ȡ����1
//#define KEY4    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8) //��ȡ����4
//#define KEY5    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3) //��ȡ����5

#define KEY1_PRES 	1	//KEY0����
#define KEY2_PRES	2	//KEY1����
//#define KEY2_PRES	3	//KEY2����
//#define WKUP_PRES   4	//KEY_UP����(��WK_UP/KEY_UP)

void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8 mode);
#endif

