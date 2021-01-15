#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#include "main.h"
#include "cmsis_os2.h"

#define RELAY_PORT 	GPIOC
#define RELAY_PIN	GPIO_PIN_4

typedef struct{
  uint8_t m0, m1;
}logComponent;

typedef enum
{
	WIFI_STATION,
	WIFI_AP
}WIFI_MODE;

typedef enum
{
	RELAY_OFF,
	RELAY_ON
}RELAY_STATE;

ADC_HandleTypeDef hadc1;
I2C_HandleTypeDef hi2c3;
RTC_HandleTypeDef hrtc;
SPI_HandleTypeDef hspi1;
TIM_HandleTypeDef htim2;
UART_HandleTypeDef huart4;

/* RTOS variables */

typedef struct
{
	uint8_t hours;
	uint8_t minutes;
	uint8_t seconds;
	uint8_t dow;
}CurrentTime;

typedef struct
{
	char ip[16];
	RELAY_STATE relayState;
	uint8_t ipUpdated;
	uint8_t systemLoaded;
	WIFI_MODE wifiMode;
	CurrentTime currentTime;
}RuntimeVariables;

typedef struct
{
	float temperature;
	char ip[16];
	uint64_t lastUpdateTime;
}RemoteThermometer;

RuntimeVariables vars;

uint8_t relayState;
uint8_t IPUpdated;
RTC_TimeTypeDef nextTime;
uint8_t nextDow;
uint32_t dayBurnMillis, currentBurnMillis;
uint8_t lastLogDay;
uint8_t flashmem[100];
uint8_t checkbytes[4];


#endif
