
// ADC 6通道采集实验

#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_adc.h"
#include "stdio.h"

// ADC1转换的电压值通过MDA方式传到SRAM
extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];

u8 start[]= {0xAA, 0X02, 0X00, 0XAC};
u8 stop[]={0XAA, 0X03, 0X00, 0XAD};
u8 next[]={0xAA, 0X06, 0X00, 0XAF};//0xAA, 0x08, 0x08, 0x01, 0x2F, 0xB4, 0xF2, 0xBB, 0xF7, 0x2A, 0x2F, 0x9B  /打击*/
																	//0xAA, 0x08, 0x08, 0x01, 0x2F, 0xC4, 0xC5, 0xBA, 0xB0, 0x2A, 0x2F, 0x36, /呐喊*/
u8 lujing[]={0XAA, 0X08};

u8 huran[]={0xAA, 0x08, 0x10, 0x01, 0x2F, 0xB4, 0xF2, 0xBB, 0xF7, 0x2A, 0x2F, 0xBA, 0xF6, 0xC8, 0xBB, 0x2A, 0x3F, 0x3F, 0x3F, 0xBD};
u8 kaishi[]={0X7E, 0XFF, 0X06, 0X0D, 0X00, 0X00, 0X00, 0XFE, 0XEE, 0XEF};
u8 next1[]={0X7E, 0XFF, 0X06, 0X01,0X00, 0X00, 0X00, 0XFE, 0XFA, 0XEF};
	
	// 局部变量，用于保存转换计算后的电压值 	 
float ADC_ConvertedValueLocal[NOFCHANEL];        

// 软件延时
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{		
	// 配置串口
	int i;
	USART1_Config();
	USART2_Config();
	// ADC 初始化
	//ADCx_Init();
	
//	printf("\r\n ----这是一个ADC多通道采集实验----\r\n");
	i = sizeof(kaishi);
	
	//Usart_SendArray(USART2,next1,10);
	Usart_SendArray(USART2,kaishi,10);
	//printf("%x", i);
	//Usart_SendArray(USART2,start,4);
	
//	Usart_SendArray(USART2,lujing,2);
//	Usart_SendByte(USART2,i);
//	Usart_SendByte(USART2,0X01);
//	Usart_SendString(USART2,"/打击*/忽然*???");
//	Usart_SendByte(USART2,0XBD);
	
	//Usart_SendArray(USART2,huran,i);
	//printf("/广告*/小米*???");//2F B9 E3 B8 E6 2A 2F D0 A1 C3 D7 2A 3F 3F 3F  
														//0xAA, 0x08, 0x10, 0x01, 0x2F, 0xB9, 0xE3, 0xB8, 0xE6, 0x2A, 0x2F, 0xD0, 0xA1, 0xC3, 0xD7, 0x2A, 0x3F, 0x3F, 0x3F, 0x77, 

	while (1)
	{	
    
//			ADC_ConvertedValueLocal[0] =(float) ADC_ConvertedValue[0]/4096*3.3;
//			ADC_ConvertedValueLocal[1] =(float) ADC_ConvertedValue[1]/4096*3.3;
//			ADC_ConvertedValueLocal[2] =(float) ADC_ConvertedValue[2]/4096*3.3;
//			ADC_ConvertedValueLocal[3] =(float) ADC_ConvertedValue[3]/4096*3.3;
//			ADC_ConvertedValueLocal[4] =(float) ADC_ConvertedValue[4]/4096*3.3;
//			ADC_ConvertedValueLocal[5] =(float) ADC_ConvertedValue[5]/4096*3.3;
//		
//			printf("\r\n CH0 value = %f V \r\n",ADC_ConvertedValueLocal[0]);
//			printf("\r\n CH1 value = %f V \r\n",ADC_ConvertedValueLocal[1]);
//			printf("\r\n CH2 value = %f V \r\n",ADC_ConvertedValueLocal[2]);
//			printf("\r\n CH3 value = %f V \r\n",ADC_ConvertedValueLocal[3]);
//			printf("\r\n CH4 value = %f V \r\n",ADC_ConvertedValueLocal[4]);
//			printf("\r\n CH5 value = %f V \r\n",ADC_ConvertedValueLocal[5]);
		
//			printf("\r\n\r\n");
//			Delay(0xffffee);	
//				Usart_SendArray(USART2,bofang,4);
//				Delay(0xffffee);
		
	}
}
/*********************************************END OF FILE**********************/

