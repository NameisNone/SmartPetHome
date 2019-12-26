#ifndef __KEY_H
#define __KEY_H	 
#include "stm32f10x.h"

//#define KEY_WKUP    GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) //读取按键WKUP
#define KEY1    		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)//读取按键0
#define KEY2    		GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)//读取按键1
//#define KEY4    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8) //读取按键4
//#define KEY5    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3) //读取按键5

#define KEY1_PRES 	1	//KEY0按下
#define KEY2_PRES	2	//KEY1按下
//#define KEY2_PRES	3	//KEY2按下
//#define WKUP_PRES   4	//KEY_UP按下(即WK_UP/KEY_UP)

void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8 mode);
#endif

