/*
 * rtcfx.c
 *
 *  Created on: May 12, 2020
 *      Author: Andrei
 */

#include <RTCFunctions.h>

RTC_TimeTypeDef Time = {0};
RTC_DateTypeDef Date = {0};
uint8_t dayOfWeek;
RTC_DateTypeDef tempDate;


void getTime()
{
	HAL_RTC_GetTime(&hrtc, &Time, RTC_FORMAT_BIN);
	vars.currentTime.hours = Time.Hours;
	vars.currentTime.minutes = Time.Minutes;
	vars.currentTime.seconds = Time.Seconds;
}

void setTime(int h, int m, int s){
	RTC_TimeTypeDef tempTime;
	tempTime.Hours = h;
	tempTime.Minutes = m;
	tempTime.Seconds = s;
	tempTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	tempTime.StoreOperation = RTC_STOREOPERATION_SET;
	HAL_RTC_SetTime(&hrtc, &tempTime, RTC_FORMAT_BIN);
}

void timeToString(char* buffer){
	buffer[0] = '\0';
	HAL_RTC_GetTime(&hrtc, &Time, RTC_FORMAT_BIN);
	sprintf(buffer, "%02d:%02d:%02d", Time.Hours, Time.Minutes, Time.Seconds);
	return;
}

void printTime(){
	//TODO
}

void setDate(int d, int m, int y){
	RTC_DateTypeDef tempDate;
	tempDate.Date = d;
	tempDate.Month = m;
	tempDate.Year = y;
	tempDate.WeekDay = RTC_WeekDayNum(tempDate.Year, tempDate.Month, tempDate.Date);
	HAL_RTC_SetDate(&hrtc, &tempDate, RTC_FORMAT_BIN);
}

uint8_t RTC_WeekDayNum(uint32_t nYear, uint8_t nMonth, uint8_t nDay)
{
	uint32_t year = 0U, weekday = 0U;

	year = 2000U + nYear;

	if(nMonth < 3U)
	{
		/*D = { [(23 x month)/9] + day + 4 + year + [(year-1)/4] - [(year-1)/100] + [(year-1)/400] } mod 7*/
		weekday = (((23U * nMonth)/9U) + nDay + 4U + year + ((year-1U)/4U) - ((year-1U)/100U) + ((year-1U)/400U)) % 7U;
	}
	else
	{
		/*D = { [(23 x month)/9] + day + 4 + year + [year/4] - [year/100] + [year/400] - 2 } mod 7*/
		weekday = (((23U * nMonth)/9U) + nDay + 4U + year + (year/4U) - (year/100U) + (year/400U) - 2U ) % 7U;
	}

	return (uint8_t)weekday;
}


void getDOW()
{
	char temp[5];
	HAL_RTC_GetDate(&hrtc, &tempDate, RTC_FORMAT_BIN);
	uint8_t dow = 0;
	dow = RTC_WeekDayNum(tempDate.Year, tempDate.Month, tempDate.Date);
	switch(dow){
	case RTC_WEEKDAY_MONDAY:   sprintf(temp, "MON");break;
	case RTC_WEEKDAY_TUESDAY:  sprintf(temp, "TUE");break;
	case RTC_WEEKDAY_WEDNESDAY:sprintf(temp, "WED");break;
	case RTC_WEEKDAY_THURSDAY: sprintf(temp, "THU");break;
	case RTC_WEEKDAY_FRIDAY:   sprintf(temp, "FRI");break;
	case RTC_WEEKDAY_SATURDAY: sprintf(temp, "SAT");break;
	case RTC_WEEKDAY_SUNDAY:   sprintf(temp, "SUN");break;
	}
}

uint8_t dayOfTheWeek()
{
	uint8_t dow = 0;
	HAL_RTC_GetDate(&hrtc, &tempDate, RTC_FORMAT_BIN);
	dow = RTC_WeekDayNum(tempDate.Year, tempDate.Month, tempDate.Date);
	if(dow == 0){
		dayOfWeek = 7;
		return 7;
	}
	dayOfWeek = dow;
	return dow;
}

void getCurrentTime()
{
	getTime();
	dayOfTheWeek();
	vars.currentTime.dow = dayOfWeek;
}
