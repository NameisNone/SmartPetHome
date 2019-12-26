#ifndef __RELAY_H
#define __RELAY_H
#include "sys.h"

#define	RELAY1_ON() GPIO_SetBits(GPIOB,GPIO_Pin_12) //数据端口	PA0 
#define	RELAY2_ON() GPIO_SetBits(GPIOB,GPIO_Pin_13) //数据端口	PA0 
#define	RELAY3_ON() GPIO_SetBits(GPIOB,GPIO_Pin_14) //数据端口	PA0 
#define	RELAY4_ON() GPIO_SetBits(GPIOA,GPIO_Pin_11) //数据端口	PA0

#define	RELAY1_OFF() GPIO_ResetBits(GPIOB,GPIO_Pin_12) //数据端口	PA0 
#define	RELAY2_OFF() GPIO_ResetBits(GPIOB,GPIO_Pin_13) //数据端口	PA0 
#define	RELAY3_OFF() GPIO_ResetBits(GPIOB,GPIO_Pin_14) //数据端口	PA0 
#define	RELAY4_OFF() GPIO_ResetBits(GPIOA,GPIO_Pin_11) //数据端口	PA0

#define RELAY1 PBout(12)
#define RELAY2 PBout(13)
#define RELAY3 PBout(14)
#define RELAY4 PAout(11)

void RELAY_Init(void);
#endif






