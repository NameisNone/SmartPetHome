#ifndef __MOTOR_H
#define __MOTOR_H
#include <sys.h>	 
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
#define PWMA   TIM2->CCR1  //PA8 ���� PWMB
#define AIN1   PAout(5)
#define AIN2   PAout(4)
//#define BIN1   PBout(13)
//#define BIN2   PBout(12)
//#define PWMB   TIM1->CCR4  //PA11 ���� PWMA
void Motor_PWM_Init(u16 arr,u16 psc);
void Motor_IO_Init(void);
void MotorTurn(u8 dir);
#endif
