#ifndef RCTFX_H
#define RCTFX_H

#include "main.h"
#include "stdio.h"
#include "globalVariables.h"

RTC_TimeTypeDef Time;
RTC_DateTypeDef Date;
uint8_t dayOfWeek;
RTC_DateTypeDef tempDate;


void getTime();

void setTime(int h, int m, int s);

void timeToString(char* buffer);

void printTime();

void setDate(int d, int m, int y);

uint8_t RTC_WeekDayNum(uint32_t nYear, uint8_t nMonth, uint8_t nDay);

void getDOW();

uint8_t dayOfTheWeek();

void getCurrentTime();

#endif
