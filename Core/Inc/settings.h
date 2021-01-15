/*
 * settings.h
 *
 *  Created on: Dec 20, 2020
 *      Author: Andrei
 */

#ifndef INC_SETTINGS_H_
#define INC_SETTINGS_H_

#include "spi_flash.h"

#define SETTINGSADDRESS         0x0000 //for saving the thermostat state in case of a power outage (standby/running/fault) and fault codes

#define MEMORY_INITIALIZED_VALUE 	0xAF
#define DEFAULT_HYSTERESIS 			0.25

typedef enum
{
	MODE_SCHEDULE,
	MODE_MANUAL,
	MODE_OFF
}MODES;

typedef struct
{
	uint8_t memoryInitialized;
	float hysteresis;
	float manualTemp;
	char ssid[30];
	char pass[30];
	uint8_t ssidLen, passLen;
	uint8_t operatingMode;
	uint16_t storedSettingsSize; /*Used for settings re-initialization if the structure changed between updates*/

}Settings;

Settings settings;

void loadSettings();
void saveSettings();
void setMode(MODES m);
void setSSID(uint8_t len, uint8_t* s);
void setPass(uint8_t len, uint8_t* p);



#endif /* INC_SETTINGS_H_ */
