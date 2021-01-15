/*
 * SHT30.h
 *
 *  Created on: Dec 18, 2020
 *      Author: Andrei
 */

#ifndef INC_SHT30_H_
#define INC_SHT30_H_

#include "globalVariables.h"

#define SHT30_PERIPHERIAL 			&hi2c3
#define SHT30_ADDRESS 				(0x44 << 1)
#define SHT30_READ_COMMAND 			0x2C06
#define SHT30_READ_COMMAND_SIZE 	2
#define SHT30_READ_DATA_SIZE 		6
#define convertToC(x) 				(-45.0 + 175.0 * (float)(x) / 65535.0)
#define convertToRH(x) 				(100.0 * (float)(x) / 65535.0)

typedef struct
{
	I2C_HandleTypeDef* i2cDev;
	uint16_t address;
	float temp;
	float rh;
}SHT30_Sensor;

SHT30_Sensor airSensor;

ErrorStatus initAirSensor();
ErrorStatus getAirData();
float getTemperature();





#endif /* INC_SHT30_H_ */
