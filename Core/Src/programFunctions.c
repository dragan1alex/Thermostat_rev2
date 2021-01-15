/*
 * coreFunctions.c
 *
 * Core functions used by the thermostat: schedule management, display elements, hardware drivers and WiFi configuration
 *
 *  Created on: May 12, 2020
 *      Author: Andrei
 */

#include "programFunctions.h"
#include "settings.h"

Schedule schedule;
uint8_t lastp, lastd;
uint8_t scheduleUpdated;

/*
 * Handlers for day programs
 * */

void sortProgramsForDay(uint8_t day){
	if(schedule.daySchedule[day].numberOfActivePrograms < 2) //sorting doesn't make sense with only 1 item
		return;
	Program temp;
	DaySchedule *p = &schedule.daySchedule[day];
	for(uint8_t i = 1; i < p->numberOfActivePrograms; i++)
		for(uint8_t j=i+1; j <= p->numberOfActivePrograms; j++)
			if( (p->programArray[i].hour > p->programArray[j].hour) || (p->programArray[i].hour == p->programArray[j].hour && p->programArray[i].minute > p->programArray[j].minute) ){
				temp = p->programArray[j];
				p->programArray[j] = p->programArray[i];
				p->programArray[i] = temp;
			}
}

uint8_t programCount(uint8_t day)
{
	return schedule.daySchedule[day].numberOfActivePrograms;
}

float getScheduleTemperature(uint8_t hour, uint8_t minute, uint8_t dow)
{
	uint8_t programIndex, dayIndex;
	Program *p;
	/*
	 * Temperature for the current time will be searched in the schedule in 3 steps:
	 * -search the current day schedule for an earlier program
	 * -search for the last program in the days dow-1 -> 1 for any program
	 * -search for the last program in the days 7 -> dow for any program
	 *
	 * */
	for(programIndex = schedule.daySchedule[dow].numberOfActivePrograms; programIndex >= 1; programIndex--)
	{
		p = &schedule.daySchedule[dow].programArray[programIndex];
		if(p->hour <= hour && p->minute <= minute)
			return (float)p->temperature * 0.5;
	}

	for(dayIndex = dow-1; dayIndex >= 1; dayIndex--)
	{
		if(schedule.daySchedule[dayIndex].numberOfActivePrograms > 0)
			return (float)schedule.daySchedule[dayIndex].programArray[schedule.daySchedule[dayIndex].numberOfActivePrograms].temperature * 0.5;
	}

	for(dayIndex = 7; dayIndex >=dow; dayIndex--)
	{
		if(schedule.daySchedule[dayIndex].numberOfActivePrograms > 0)
			return (float)schedule.daySchedule[dayIndex].programArray[schedule.daySchedule[dayIndex].numberOfActivePrograms].temperature * 0.5;
	}
	/* If there is no record in the schedule set the temperature to 10C to prevent freezing */
	return 10.0;
}

void saveSchedule()
{
	sectorErase4KFlash(PROGRAMADDRESS);
	writeBytesFlash(PROGRAMADDRESS, &schedule, sizeof(schedule));
}

void loadSchedule()
{
	readBytesFlash(PROGRAMADDRESS, (void*)&schedule, sizeof(schedule));
}

void updateProgram(DaySchedule p, uint8_t dow)
{
	schedule.daySchedule[dow] = p;
	saveSchedule();
	scheduleUpdated = 1;

}

DaySchedule getDaySchedule(uint8_t dow)
{
	return schedule.daySchedule[dow];
}

void relay(RELAY_STATE state)
{
	if(state == RELAY_ON)
	{
		HAL_GPIO_WritePin(RELAY_PORT, RELAY_PIN, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(RELAY_PORT, RELAY_PIN, GPIO_PIN_RESET);
	}
	vars.relayState = state;
}

//                      IP TO STRING DISPLAY FUNCTION           //

void displayPassword()
{
	//TODO
}

void clearDisplayPassword()
{
	//TODO
}

void printIP()
{
	//TODO
}

//                      WIFI SETTINGS STORAGE                   //
/////////////////////////////////////////////////////////////////


