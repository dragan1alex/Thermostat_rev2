/*
 * tasks.c
 *
 *  Created on: Jan 15, 2021
 *      Author: Andrei
 */

#include "tasks.h"

/* The name is self-explanatory */
void ThermostatTask(void *argument)
{
	while(1)
	{
		getAirData();
		getCurrentTime();
		if(airSensor.temp < getScheduleTemperature(vars.currentTime.hours, vars.currentTime.minutes, vars.currentTime.dow) - (settings.hysteresis/2)
				&& vars.relayState == RELAY_OFF)
			relay(RELAY_ON);
		else if(airSensor.temp > getScheduleTemperature(vars.currentTime.hours, vars.currentTime.minutes, vars.currentTime.dow) + (settings.hysteresis/2)
				&& vars.relayState == RELAY_ON)
			relay(RELAY_OFF);
		osDelay(1000);
	}
}
