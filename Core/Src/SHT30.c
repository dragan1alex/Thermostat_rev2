/*
 * SHT30.c
 *
 *  Created on: Dec 18, 2020
 *      Author: Andrei
 */

#include "SHT30.h"

SHT30_Sensor airSensor;


ErrorStatus initAirSensor()
{
	airSensor.address = SHT30_ADDRESS;
	airSensor.i2cDev = SHT30_PERIPHERIAL;
	airSensor.temp = 0;
	airSensor.rh = 0;
	return SUCCESS;
}

ErrorStatus getAirData()
{
	uint8_t sensorData[6] = {0};
	uint16_t readCommand = SHT30_READ_COMMAND;
	if(HAL_I2C_IsDeviceReady(airSensor.i2cDev, airSensor.address, 3, 100) != HAL_OK)
		return ERROR;
#if FLASH_LEDS_ON_SENSOR_READ
	flashLed(COMMS_LED);
#endif
	if(HAL_I2C_Mem_Read(airSensor.i2cDev,
			airSensor.address,
			readCommand,
			SHT30_READ_COMMAND_SIZE,
			sensorData,
			SHT30_READ_DATA_SIZE,
			100) != HAL_OK)
		return ERROR;
	airSensor.temp  = convertToC((uint16_t)(sensorData[0] << 8) + sensorData[1]);
	airSensor.rh = convertToRH((uint16_t)(sensorData[3] << 8) + sensorData[4]);
	return SUCCESS;
}

float getTemperature()
{
	getAirData();
	return airSensor.temp;
}

