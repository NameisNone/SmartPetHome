/**
************************************************************
* @file         gizwits_product.c
* @brief        Gizwits control protocol processing, and platform-related hardware initialization 
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
#include <stdio.h>
#include <string.h>
#include "gizwits_product.h"

static uint32_t timerMsCount;

/** Current datapoint */
dataPoint_t currentDataPoint;

/**@} */
/**@name Gizwits User Interface
* @{
*/

/**
* @brief Event handling interface

* Description:

* 1. Users can customize the changes in WiFi module status

* 2. Users can add data points in the function of event processing logic, such as calling the relevant hardware peripherals operating interface

* @param [in] info: event queue
* @param [in] data: protocol data
* @param [in] len: protocol data length
* @return NULL
* @ref gizwits_protocol.h
*/
int8_t gizwitsEventProcess(eventInfo_t *info, uint8_t *gizdata, uint32_t len)
{
  uint8_t i = 0;
  dataPoint_t *dataPointPtr = (dataPoint_t *)gizdata;
  moduleStatusInfo_t *wifiData = (moduleStatusInfo_t *)gizdata;
  protocolTime_t *ptime = (protocolTime_t *)gizdata;
  
#if MODULE_TYPE
  gprsInfo_t *gprsInfoData = (gprsInfo_t *)gizdata;
#else
  moduleInfo_t *ptModuleInfo = (moduleInfo_t *)gizdata;
#endif

  if((NULL == info) || (NULL == gizdata))
  {
    return -1;
  }

  for(i=0; i<info->num; i++)
  {
    switch(info->event[i])
    {
      case EVENT_ultraviolet_LED:
        currentDataPoint.valueultraviolet_LED = dataPointPtr->valueultraviolet_LED;
        GIZWITS_LOG("Evt: EVENT_ultraviolet_LED %d \n", currentDataPoint.valueultraviolet_LED);
        if(0x01 == currentDataPoint.valueultraviolet_LED)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_Light_LED:
        currentDataPoint.valueLight_LED = dataPointPtr->valueLight_LED;
        GIZWITS_LOG("Evt: EVENT_Light_LED %d \n", currentDataPoint.valueLight_LED);
        if(0x01 == currentDataPoint.valueLight_LED)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_MusicSwitch:
        currentDataPoint.valueMusicSwitch = dataPointPtr->valueMusicSwitch;
        GIZWITS_LOG("Evt: EVENT_MusicSwitch %d \n", currentDataPoint.valueMusicSwitch);
        if(0x01 == currentDataPoint.valueMusicSwitch)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_WhiteLight:
        currentDataPoint.valueWhiteLight = dataPointPtr->valueWhiteLight;
        GIZWITS_LOG("Evt: EVENT_WhiteLight %d \n", currentDataPoint.valueWhiteLight);
        if(0x01 == currentDataPoint.valueWhiteLight)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_DoorMotor:
        currentDataPoint.valueDoorMotor = dataPointPtr->valueDoorMotor;
        GIZWITS_LOG("Evt: EVENT_DoorMotor %d \n", currentDataPoint.valueDoorMotor);
        if(0x01 == currentDataPoint.valueDoorMotor)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;

      case EVENT_HH:
        currentDataPoint.valueHH = dataPointPtr->valueHH;
        GIZWITS_LOG("Evt: EVENT_HH %d\n", currentDataPoint.valueHH);
        switch(currentDataPoint.valueHH)
        {
          case HH_VALUE0:
            //user handle
            break;
          case HH_VALUE1:
            //user handle
            break;
          case HH_VALUE2:
            //user handle
            break;
          case HH_VALUE3:
            //user handle
            break;
          case HH_VALUE4:
            //user handle
            break;
          case HH_VALUE5:
            //user handle
            break;
          case HH_VALUE6:
            //user handle
            break;
          case HH_VALUE7:
            //user handle
            break;
          case HH_VALUE8:
            //user handle
            break;
          case HH_VALUE9:
            //user handle
            break;
          case HH_VALUE10:
            //user handle
            break;
          case HH_VALUE11:
            //user handle
            break;
          case HH_VALUE12:
            //user handle
            break;
          case HH_VALUE13:
            //user handle
            break;
          case HH_VALUE14:
            //user handle
            break;
          case HH_VALUE15:
            //user handle
            break;
          case HH_VALUE16:
            //user handle
            break;
          case HH_VALUE17:
            //user handle
            break;
          case HH_VALUE18:
            //user handle
            break;
          case HH_VALUE19:
            //user handle
            break;
          case HH_VALUE20:
            //user handle
            break;
          case HH_VALUE21:
            //user handle
            break;
          case HH_VALUE22:
            //user handle
            break;
          case HH_VALUE23:
            //user handle
            break;
          default:
            break;
        }
        break;
      case EVENT_MM:
        currentDataPoint.valueMM = dataPointPtr->valueMM;
        GIZWITS_LOG("Evt: EVENT_MM %d\n", currentDataPoint.valueMM);
        switch(currentDataPoint.valueMM)
        {
          case MM_VALUE0:
            //user handle
            break;
          case MM_VALUE1:
            //user handle
            break;
          case MM_VALUE2:
            //user handle
            break;
          case MM_VALUE3:
            //user handle
            break;
          case MM_VALUE4:
            //user handle
            break;
          case MM_VALUE5:
            //user handle
            break;
          case MM_VALUE6:
            //user handle
            break;
          case MM_VALUE7:
            //user handle
            break;
          case MM_VALUE8:
            //user handle
            break;
          case MM_VALUE9:
            //user handle
            break;
          case MM_VALUE10:
            //user handle
            break;
          case MM_VALUE11:
            //user handle
            break;
          case MM_VALUE12:
            //user handle
            break;
          case MM_VALUE13:
            //user handle
            break;
          case MM_VALUE14:
            //user handle
            break;
          case MM_VALUE15:
            //user handle
            break;
          case MM_VALUE16:
            //user handle
            break;
          case MM_VALUE17:
            //user handle
            break;
          case MM_VALUE18:
            //user handle
            break;
          case MM_VALUE19:
            //user handle
            break;
          case MM_VALUE20:
            //user handle
            break;
          case MM_VALUE21:
            //user handle
            break;
          case MM_VALUE22:
            //user handle
            break;
          case MM_VALUE23:
            //user handle
            break;
          case MM_VALUE24:
            //user handle
            break;
          case MM_VALUE25:
            //user handle
            break;
          case MM_VALUE26:
            //user handle
            break;
          case MM_VALUE27:
            //user handle
            break;
          case MM_VALUE28:
            //user handle
            break;
          case MM_VALUE29:
            //user handle
            break;
          case MM_VALUE30:
            //user handle
            break;
          case MM_VALUE31:
            //user handle
            break;
          case MM_VALUE32:
            //user handle
            break;
          case MM_VALUE33:
            //user handle
            break;
          case MM_VALUE34:
            //user handle
            break;
          case MM_VALUE35:
            //user handle
            break;
          case MM_VALUE36:
            //user handle
            break;
          case MM_VALUE37:
            //user handle
            break;
          case MM_VALUE38:
            //user handle
            break;
          case MM_VALUE39:
            //user handle
            break;
          case MM_VALUE40:
            //user handle
            break;
          case MM_VALUE41:
            //user handle
            break;
          case MM_VALUE42:
            //user handle
            break;
          case MM_VALUE43:
            //user handle
            break;
          case MM_VALUE44:
            //user handle
            break;
          case MM_VALUE45:
            //user handle
            break;
          case MM_VALUE46:
            //user handle
            break;
          case MM_VALUE47:
            //user handle
            break;
          case MM_VALUE48:
            //user handle
            break;
          case MM_VALUE49:
            //user handle
            break;
          case MM_VALUE50:
            //user handle
            break;
          case MM_VALUE51:
            //user handle
            break;
          case MM_VALUE52:
            //user handle
            break;
          case MM_VALUE53:
            //user handle
            break;
          case MM_VALUE54:
            //user handle
            break;
          case MM_VALUE55:
            //user handle
            break;
          case MM_VALUE56:
            //user handle
            break;
          case MM_VALUE57:
            //user handle
            break;
          case MM_VALUE58:
            //user handle
            break;
          case MM_VALUE59:
            //user handle
            break;
          default:
            break;
        }
        break;



      case WIFI_SOFTAP:
        break;
      case WIFI_AIRLINK:
        break;
      case WIFI_STATION:
        break;
      case WIFI_CON_ROUTER:
 
        break;
      case WIFI_DISCON_ROUTER:
 
        break;
      case WIFI_CON_M2M:
 
        break;
      case WIFI_DISCON_M2M:
        break;
      case WIFI_RSSI:
        GIZWITS_LOG("RSSI %d\n", wifiData->rssi);
        break;
      case TRANSPARENT_DATA:
        GIZWITS_LOG("TRANSPARENT_DATA \n");
        //user handle , Fetch data from [data] , size is [len]
        break;
      case WIFI_NTP:
        GIZWITS_LOG("WIFI_NTP : [%d-%d-%d %02d:%02d:%02d][%d] \n",ptime->year,ptime->month,ptime->day,ptime->hour,ptime->minute,ptime->second,ptime->ntp);
        break;
      case MODULE_INFO:
            GIZWITS_LOG("MODULE INFO ...\n");
      #if MODULE_TYPE
            GIZWITS_LOG("GPRS MODULE ...\n");
            //Format By gprsInfo_t
      #else
            GIZWITS_LOG("WIF MODULE ...\n");
            //Format By moduleInfo_t
            GIZWITS_LOG("moduleType : [%d] \n",ptModuleInfo->moduleType);
      #endif
    break;
      default:
        break;
    }
  }

  return 0;
}

/**
* User data acquisition

* Here users need to achieve in addition to data points other than the collection of data collection, can be self-defined acquisition frequency and design data filtering algorithm

* @param none
* @return none
*/
void userHandle(void)
{
 /*
    currentDataPoint.valueTemperature = ;//Add Sensor Data Collection
    currentDataPoint.valueHumidity = ;//Add Sensor Data Collection

    */
    
}

/**
* Data point initialization function

* In the function to complete the initial user-related data
* @param none
* @return none
* @note The developer can add a data point state initialization value within this function
*/
void userInit(void)
{
    memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));
    
    /** Warning !!! DataPoint Variables Init , Must Within The Data Range **/ 
    /*
      currentDataPoint.valueultraviolet_LED = ;
      currentDataPoint.valueLight_LED = ;
      currentDataPoint.valueMusicSwitch = ;
      currentDataPoint.valueWhiteLight = ;
      currentDataPoint.valueDoorMotor = ;
      currentDataPoint.valueHH = ;
      currentDataPoint.valueMM = ;
      currentDataPoint.valueTemperature = ;
      currentDataPoint.valueHumidity = ;
    */

}


/**
* @brief  gizTimerMs

* millisecond timer maintenance function ,Millisecond increment , Overflow to zero

* @param none
* @return none
*/
void gizTimerMs(void)
{
    timerMsCount++;
}

/**
* @brief gizGetTimerCount

* Read system time, millisecond timer

* @param none
* @return System time millisecond
*/
uint32_t gizGetTimerCount(void)
{
    return timerMsCount;
}

/**
* @brief mcuRestart

* MCU Reset function

* @param none
* @return none
*/
void mcuRestart(void)
{

}
/**@} */

/**
* @brief TIMER_IRQ_FUN

* Timer Interrupt handler function

* @param none
* @return none
*/
void TIMER_IRQ_FUN(void)
{
  gizTimerMs();
}

/**
* @brief UART_IRQ_FUN

* UART Serial interrupt function ，For Module communication

* Used to receive serial port protocol data between WiFi module

* @param none
* @return none
*/
void UART_IRQ_FUN(void)
{
  uint8_t value = 0;
  //value = USART_ReceiveData(USART2);//STM32 test demo
  gizPutData(&value, 1);
}


/**
* @brief uartWrite

* Serial write operation, send data to the WiFi module

* @param buf      : Data address
* @param len       : Data length
*
* @return : Not 0,Serial send success;
*           -1，Input Param Illegal
*/
int32_t uartWrite(uint8_t *buf, uint32_t len)
{
    uint32_t i = 0;
    
    if(NULL == buf)
    {
        return -1;
    }
    
    #ifdef PROTOCOL_DEBUG
    GIZWITS_LOG("MCU2WiFi[%4d:%4d]: ", gizGetTimerCount(), len);
    for(i=0; i<len; i++)
    {
        GIZWITS_LOG("%02x ", buf[i]);
    }
    GIZWITS_LOG("\n");
    #endif

    for(i=0; i<len; i++)
    {
        //USART_SendData(UART, buf[i]);//STM32 test demo
        //Serial port to achieve the function, the buf[i] sent to the module
        if(i >=2 && buf[i] == 0xFF)
        {
          //Serial port to achieve the function, the 0x55 sent to the module
          //USART_SendData(UART, 0x55);//STM32 test demo
        }
    }


    
    return len;
}


