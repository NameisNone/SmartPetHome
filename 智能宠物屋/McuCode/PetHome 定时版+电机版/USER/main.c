/**
************************************************************
* @file         main.c
* @brief        MCU entry file
* @author       Gizwits
* @date         2017-07-19
* @version      V03030000
* @copyright    Gizwits
*
* @note         Gizwits is only for smart hardware
*               Gizwits Smart Cloud for Smart Products
*               Links | Value Added | Open | Neutral | Safety | Own | Free | Ecology
*               www.gizwits.com
*
***********************************************************/
/********************************************************
** Code migration instructions
*
* 1、Serial drive for Module communication,（1、Interrupt receive data to write to the ring buffer ;2、实现uartWrite() Serial send function）
* 2、Serial print function , printf()
* 3、MS timer，gizTimerMs() maintain system time
* 4、MCU Reset function. The module can request MCU reset
* 5、Configure network function,use gizwitsSetMode() , realization module distribution network function
* 6、userHandle() , data acquisition（Uplink logic）
* 7、gizwitsEventProcess() , Specific execution of control commands (Downlink logic)
*
*
*********************************************************/
#include <string.h>
#include "gizwits_product.h"
#include "common.h"
#include "sys.h"
#include "led.h"
#include "timer.h"
#include "key.h"
#include "relay.h"
#include "dht11.h"
#include "usart2.h"
#include "usart.h"
#include "delay.h"
#include "oled.h"
#include "motor.h"
/**
* @brief main

* In this function, the user - associated initialization and the main logical loop are completed

* @param none
* @return none
*/
u8 time_HH = 0;
u8 time_MM = 0;
u8 time_SS = 0;

u8 NTP_HH;
u8 NTP_MM;
u8 NTP_SS;
//全局变量定义
volatile u8 wifi_flag = 0;
volatile u8 wifi_sta = 0; //wifi连接状态 0：未连接，1：已连接
volatile u8 music_flag = 0;
volatile u8 door_flag = 0;
volatile u8 door_S_flag = 0;

u8 TimerFlag = 0;
u8  temperature = 0, humidity = 0; //DHT11读取的温湿度值
u8 arrayStart[] = {0x7E, 0xFF, 0x06, 0x0D, 0x00, 0x00, 0x00, 0xFE, 0xEE, 0xEF};
u8 arrayStop[] = {0x7E, 0xFF, 0x06, 0x0E, 0x00, 0x00, 0x00, 0xFE, 0xED, 0xEF};
//硬件初始化函数
void HardWareInit(void)
{
    delay_init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断分组设置为2
    LED_Init();//LED初始化
    KEY_Init();//按键初始化
    RELAY_Init();//继电器端口初始化
    Motor_PWM_Init(7199, 0); //电机PWM初始化
    uart2_init();//波特率115200
    uart_init(9600);//串口1初始化9600
    OLED_Init();//初始化OLED显示
    OLED_ShowString(8, 0, "Smart Pet Home", 16);
    while(DHT11_Init())//返回1:不存在; 返回0:存在
    {
        printf("DHT11初始化失败！\r\n");
    }
    printf("硬件初始化成功！！\r\n");
}

//机智云初始化
void Gizwits_Init(void)
{
    TIM3_Int_Init();//定时器初始化
    uart3_init();//wifi串口初始化，波特率设置为9600
    memset((uint8_t *)&currentDataPoint, 0, sizeof(dataPoint_t));
    gizwitsInit();
}

//按键配网函数
void WIFI_SetMode(void)
{
    u8 key_temp = 0;
    key_temp = KEY_Scan(0); //按键配网
    if(key_temp == KEY1_PRES)
    {
        GIZWITS_LOG("Go to SetMode\r\n");
        printf("开始配网！！\r\n");
        gizwitsSetMode(WIFI_SOFTAP_MODE);//SOFTAP模式配网
        printf("WIFI_SOFTAP_MODE OK！\r\n");
        key_temp = 0;
    }
    else if(key_temp == 2)
    {
        RELAY3 = !RELAY3;
    }

}
//数据点上报函数
void userHandle(void)
{
    if(wifi_sta == 1) //联网则更新数据点
    {
        //printf()
        currentDataPoint.valueTemperature = temperature;//Add Sensor Data Collection
        currentDataPoint.valueHumidity = humidity;//Add Sensor Data Collection
//		printf("上传的温湿度数据为:%d------%d\r\n",currentDataPoint.valueTemperature,currentDataPoint.valueHumidity);
        if((time_HH == NTP_HH) && (time_MM == NTP_MM) && (time_SS == NTP_SS) && (TimerFlag == 0) ) //如果时间到了
        {
            RELAY3 = 1; //打开紫外线灯
            music_flag = 1;
            door_flag = 1;
            door_S_flag = 1;
            time_MM = time_MM + 1;
            TimerFlag = 1;
            if(time_MM >= 60) //大于60进行处理
            {
                time_MM = time_MM - 60;
                time_HH++;
            }
        }
        else if((time_HH == NTP_HH) && (time_MM == NTP_MM) && (time_SS == NTP_SS) && (TimerFlag == 1) ) //1分钟后关闭紫外线灯
        {
            RELAY3 = 0; //关闭紫外线灯
            TimerFlag = 0;
						if(time_MM==0)
						{
							time_MM=59;
							time_HH--;
						}
						else time_MM = time_MM - 1;
										
        }

        //更新数据状态
        if(RELAY3 == 1)
            currentDataPoint.valueultraviolet_LED = 1;//
        else
            currentDataPoint.valueultraviolet_LED = 0;

        if(music_flag == 1)
            currentDataPoint.valueMusicSwitch = 1;//
        else
            currentDataPoint.valueMusicSwitch = 0;

        if(door_S_flag == 0 && door_flag == 1)
            currentDataPoint.valueDoorMotor = 1;//
        else if(door_S_flag == 0 && door_flag == 0)
            currentDataPoint.valueDoorMotor = 0;
    }
}
//主函数
int main(void)
{
    u16 t;
    HardWareInit();
    Gizwits_Init();//包含gizwitsInit();
    userInit();
    while(1)
    {
        if(wifi_sta == 1) 	//wifi已连接
        {
            LED = 0;
            OLED_ShowString(4, 4, "Wifi Connected!", 16);
        }
        else 			//wifi未连接
        {
            LED = 1;
            OLED_ShowString(4, 4, "Wifi Connecting", 16);
        }
        WIFI_SetMode();
        if(music_flag == 1)			//开启播放音乐
            Usart_SendArray(USART1, arrayStart, sizeof(arrayStart));	//播放
        else
            Usart_SendArray(USART1, arrayStop, sizeof(arrayStart)); //暂停

        if(door_S_flag == 1 && door_flag == 1) //电机门控制逻辑：计时未结束且为开门指令时电机正转
        {
            MotorTurn(1);
        }
        else if(door_S_flag == 1 && door_flag == 0) //计时未结束且为关门指令时电机反转
        {
            MotorTurn(0);
        }
        else //计时结束电机不转
        {
            MotorTurn(2);
        }

        userHandle();   //数据点上报
        gizwitsHandle((dataPoint_t *)&currentDataPoint); //协议处理

        if(t % 100 == 0) //100ms更新一次显示
        {
            DHT11_Read_Data(&temperature, &humidity); //读取温湿度
            OLED_ShowString(0, 2, "Temp:", 16);
            OLED_ShowNum(40, 2, temperature, 2, 16);
            OLED_ShowString(68, 2, "Humi:", 16);
            OLED_ShowNum(110, 2, humidity, 2, 16);
        }
        if(t % 1000 == 0)t = 0;
        delay_ms(1);//延时1ms
        t++;
    }
}

