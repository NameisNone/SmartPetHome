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
* 1��Serial drive for Module communication,��1��Interrupt receive data to write to the ring buffer ;2��ʵ��uartWrite() Serial send function��
* 2��Serial print function , printf()
* 3��MS timer��gizTimerMs() maintain system time
* 4��MCU Reset function. The module can request MCU reset
* 5��Configure network function,use gizwitsSetMode() , realization module distribution network function
* 6��userHandle() , data acquisition��Uplink logic��
* 7��gizwitsEventProcess() , Specific execution of control commands (Downlink logic)
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
//ȫ�ֱ�������
volatile u8 wifi_flag = 0;
volatile u8 wifi_sta = 0; //wifi����״̬ 0��δ���ӣ�1��������
volatile u8 music_flag = 0;
volatile u8 door_flag = 0;
volatile u8 door_S_flag = 0;

u8 TimerFlag = 0;
u8  temperature = 0, humidity = 0; //DHT11��ȡ����ʪ��ֵ
u8 arrayStart[] = {0x7E, 0xFF, 0x06, 0x0D, 0x00, 0x00, 0x00, 0xFE, 0xEE, 0xEF};
u8 arrayStop[] = {0x7E, 0xFF, 0x06, 0x0E, 0x00, 0x00, 0x00, 0xFE, 0xED, 0xEF};
//Ӳ����ʼ������
void HardWareInit(void)
{
    delay_init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�жϷ�������Ϊ2
    LED_Init();//LED��ʼ��
    KEY_Init();//������ʼ��
    RELAY_Init();//�̵����˿ڳ�ʼ��
    Motor_PWM_Init(7199, 0); //���PWM��ʼ��
    uart2_init();//������115200
    uart_init(9600);//����1��ʼ��9600
    OLED_Init();//��ʼ��OLED��ʾ
    OLED_ShowString(8, 0, "Smart Pet Home", 16);
    while(DHT11_Init())//����1:������; ����0:����
    {
        printf("DHT11��ʼ��ʧ�ܣ�\r\n");
    }
    printf("Ӳ����ʼ���ɹ�����\r\n");
}

//�����Ƴ�ʼ��
void Gizwits_Init(void)
{
    TIM3_Int_Init();//��ʱ����ʼ��
    uart3_init();//wifi���ڳ�ʼ��������������Ϊ9600
    memset((uint8_t *)&currentDataPoint, 0, sizeof(dataPoint_t));
    gizwitsInit();
}

//������������
void WIFI_SetMode(void)
{
    u8 key_temp = 0;
    key_temp = KEY_Scan(0); //��������
    if(key_temp == KEY1_PRES)
    {
        GIZWITS_LOG("Go to SetMode\r\n");
        printf("��ʼ��������\r\n");
        gizwitsSetMode(WIFI_SOFTAP_MODE);//SOFTAPģʽ����
        printf("WIFI_SOFTAP_MODE OK��\r\n");
        key_temp = 0;
    }
    else if(key_temp == 2)
    {
        RELAY3 = !RELAY3;
    }

}
//���ݵ��ϱ�����
void userHandle(void)
{
    if(wifi_sta == 1) //������������ݵ�
    {
        //printf()
        currentDataPoint.valueTemperature = temperature;//Add Sensor Data Collection
        currentDataPoint.valueHumidity = humidity;//Add Sensor Data Collection
//		printf("�ϴ�����ʪ������Ϊ:%d------%d\r\n",currentDataPoint.valueTemperature,currentDataPoint.valueHumidity);
        if((time_HH == NTP_HH) && (time_MM == NTP_MM) && (time_SS == NTP_SS) && (TimerFlag == 0) ) //���ʱ�䵽��
        {
            RELAY3 = 1; //�������ߵ�
            music_flag = 1;
            door_flag = 1;
            door_S_flag = 1;
            time_MM = time_MM + 1;
            TimerFlag = 1;
            if(time_MM >= 60) //����60���д���
            {
                time_MM = time_MM - 60;
                time_HH++;
            }
        }
        else if((time_HH == NTP_HH) && (time_MM == NTP_MM) && (time_SS == NTP_SS) && (TimerFlag == 1) ) //1���Ӻ�ر������ߵ�
        {
            RELAY3 = 0; //�ر������ߵ�
            TimerFlag = 0;
						if(time_MM==0)
						{
							time_MM=59;
							time_HH--;
						}
						else time_MM = time_MM - 1;
										
        }

        //��������״̬
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
//������
int main(void)
{
    u16 t;
    HardWareInit();
    Gizwits_Init();//����gizwitsInit();
    userInit();
    while(1)
    {
        if(wifi_sta == 1) 	//wifi������
        {
            LED = 0;
            OLED_ShowString(4, 4, "Wifi Connected!", 16);
        }
        else 			//wifiδ����
        {
            LED = 1;
            OLED_ShowString(4, 4, "Wifi Connecting", 16);
        }
        WIFI_SetMode();
        if(music_flag == 1)			//������������
            Usart_SendArray(USART1, arrayStart, sizeof(arrayStart));	//����
        else
            Usart_SendArray(USART1, arrayStop, sizeof(arrayStart)); //��ͣ

        if(door_S_flag == 1 && door_flag == 1) //����ſ����߼�����ʱδ������Ϊ����ָ��ʱ�����ת
        {
            MotorTurn(1);
        }
        else if(door_S_flag == 1 && door_flag == 0) //��ʱδ������Ϊ����ָ��ʱ�����ת
        {
            MotorTurn(0);
        }
        else //��ʱ���������ת
        {
            MotorTurn(2);
        }

        userHandle();   //���ݵ��ϱ�
        gizwitsHandle((dataPoint_t *)&currentDataPoint); //Э�鴦��

        if(t % 100 == 0) //100ms����һ����ʾ
        {
            DHT11_Read_Data(&temperature, &humidity); //��ȡ��ʪ��
            OLED_ShowString(0, 2, "Temp:", 16);
            OLED_ShowNum(40, 2, temperature, 2, 16);
            OLED_ShowString(68, 2, "Humi:", 16);
            OLED_ShowNum(110, 2, humidity, 2, 16);
        }
        if(t % 1000 == 0)t = 0;
        delay_ms(1);//��ʱ1ms
        t++;
    }
}

