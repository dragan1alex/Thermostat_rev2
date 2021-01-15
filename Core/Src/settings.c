/*
 * settings.c
 *
 *  Created on: Dec 21, 2020
 *      Author: Andrei
 */

#include "settings.h"
#include "programFunctions.h"

Settings settings;

void initializeSettings()
{
	settings.memoryInitialized = MEMORY_INITIALIZED_VALUE;
	settings.hysteresis = DEFAULT_HYSTERESIS;
	settings.operatingMode = MODE_MANUAL;
	settings.manualTemp = 22;
	sprintf(settings.ssid, "ssid");
	sprintf(settings.pass, "pass");
	settings.storedSettingsSize = sizeof(settings);
	saveSettings();
}

void loadSettings()
{
	readBytesFlash(SETTINGSADDRESS, (void*)&settings, sizeof(settings));
	/* Check if the memory has been initialized; if not, initialize it */
	if(settings.memoryInitialized != MEMORY_INITIALIZED_VALUE)
	{
		initializeSettings();
		saveSchedule();
	}
	/* If the settings structure has been updated re-initialize it */
	if(settings.storedSettingsSize != sizeof(settings))
	{
		initializeSettings();
	}
}

void saveSettings()
{
	sectorErase4KFlash(SETTINGSADDRESS);
	writeBytesFlash(SETTINGSADDRESS, &settings, sizeof(settings));
}

void setMode(MODES m);


void setSSID(uint8_t len, uint8_t* s){
	for(uint8_t i=0;i<len;i++)
		settings.ssid[i] = s[i];
	settings.ssidLen = len;
}
void setPass(uint8_t len, uint8_t* p){
	for(uint8_t i=0;i<len;i++)
		settings.pass[i] = p[i];
	settings.passLen = len;
}


