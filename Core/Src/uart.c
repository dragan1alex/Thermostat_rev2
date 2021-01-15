/*
 * comms.c
 *
 * This file includes all the functions used to communicate with the ESP32 WiFi module
 *
 *  Created on: May 11, 2020
 *      Author: Andrei
 */
#include "uart.h"
#include "main.h"
#include "programFunctions.h"
#include "SHT30.h"
#include "settings.h"
#include "RTCFunctions.h"
#include "globalVariables.h"

uint8_t command;


void resetComms(){
	//command = 0;
	HAL_UART_Receive_IT(WIFI_UART, &command, 1);
}


void sendPong(){
	uint8_t pong = PONG;
	HAL_UART_Transmit(WIFI_UART, &pong, 1, 10);
}

void handleIP(){
	HAL_UART_Receive(WIFI_UART, (uint8_t*)vars.ip, 15, 100);
	for(int i=6;i<=14;i++)
		if(vars.ip[i] == ' '){
			vars.ip[i] = 0;
			break;
		}
	IPUpdated = 1;
}

void handleWLAN(){
	vars.wifiMode = WIFI_STATION;
}

void handleSETAP(){
	vars.wifiMode = WIFI_AP;
}


void handleGETTEMP(){
	uint8_t tempuart[2];
	tempuart[1] = (uint8_t)((uint32_t)(airSensor.temp * 100) % 100);
	tempuart[0] = (uint8_t)airSensor.temp % 100;
	HAL_UART_Transmit(WIFI_UART, tempuart, 2, 100);
}

void handleGETSETTEMP(){
	getCurrentTime();
	uint8_t tempuart[2];
	tempuart[1] = (uint8_t)((uint32_t)(getScheduleTemperature(vars.currentTime.hours, vars.currentTime.minutes, vars.currentTime.dow) * 100) % 100);
	tempuart[0] = (uint8_t)getScheduleTemperature(vars.currentTime.hours, vars.currentTime.minutes, vars.currentTime.dow) % 100;
	HAL_UART_Transmit(WIFI_UART, tempuart, 2, 100);
}

void handleGETSCHEDULE(){
	uint8_t day, nrProg;
	uint8_t txbuffer[18];
	uint8_t j = 0;
	DaySchedule tempDaySchedule;
	HAL_UART_Receive(WIFI_UART, &day, 1, 200);
	if(day<1 || day>7){
		return;
	}

	nrProg = programCount(day);
	if(nrProg==0){
		HAL_UART_Transmit(WIFI_UART, &nrProg, 1, 10);
		return;
	}
	tempDaySchedule = getDaySchedule(day);
	for(int i=1;i<=nrProg;i++){
		txbuffer[j++] = tempDaySchedule.programArray[i].hour;
		txbuffer[j++] = tempDaySchedule.programArray[i].minute;
		txbuffer[j++] = tempDaySchedule.programArray[i].temperature;
	}
	HAL_UART_Transmit(WIFI_UART, &nrProg, 1, 10);
	HAL_UART_Transmit(WIFI_UART, txbuffer, nrProg*3, 100);
}

void handleRESET(){
	uint8_t r = 0;
	HAL_UART_Receive(WIFI_UART, &r, 1, 200);
	if(r == RESET)
		HAL_NVIC_SystemReset();
}


void handleWRITESCHEDULE(){
	uint8_t h[7],m[7],t[7],d, nrProg = 0;
	HAL_UART_Receive(WIFI_UART, &d, 1, 200);
	HAL_UART_Receive(WIFI_UART, &nrProg, 1, 200);
	for(uint8_t i=1;i<=nrProg;i++)
		HAL_UART_Receive(WIFI_UART, &h[i], 1, 100);
	for(uint8_t i=1;i<=nrProg;i++)
		HAL_UART_Receive(WIFI_UART, &m[i], 1, 100);
	for(uint8_t i=1;i<=nrProg;i++)
		HAL_UART_Receive(WIFI_UART, &t[i], 1, 100);
	uint8_t error = 0;
	for(uint8_t i=1;i<=nrProg;i++){
		if(h[i] >23 || m[i] > 59)
			error = 1;
	}
	if(!error){
		DaySchedule updatedSchedule;
		updatedSchedule.numberOfActivePrograms = nrProg;
		for(uint8_t i=1;i<=nrProg;i++){
			updatedSchedule.programArray[i].hour = h[i];
			updatedSchedule.programArray[i].minute = m[i];
			updatedSchedule.programArray[i].temperature = t[i];
		}
		updateProgram(updatedSchedule, d);
	}
}

void handleSETDATE(){
	uint8_t day, month, year;
	HAL_UART_Receive(WIFI_UART, &day, 1, 100);
	HAL_UART_Receive(WIFI_UART, &month, 1, 100);
	HAL_UART_Receive(WIFI_UART, &year, 1, 100);
	setDate(day, month, year);
	scheduleUpdated = 1;
}

void handleSETTIME(){
	uint8_t time[3];
	HAL_UART_Receive(WIFI_UART, time, 3, 100);
	setTime(time[0], time[1], time[2]);
}

void handleGETFLAME(){
	HAL_UART_Transmit(WIFI_UART, (uint8_t*)&vars.relayState, 1, 10);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	switch(command){
	case PING:            sendPong();break;
	case SETIP:           handleIP();break;
	case SETWLAN:         handleWLAN();break;
	case SETAP:           handleSETAP();break;
	case GETTEMP:         handleGETTEMP();break;
	case GETSETTEMP:      handleGETSETTEMP();break;
	case GETSCHEDULE:     handleGETSCHEDULE();break;
	case RESET_CMD:       handleRESET();break;
	case WRITESCHEDULE:   handleWRITESCHEDULE();break;
	case SETDATE:         handleSETDATE();break;
	case SETTIME:         handleSETTIME();break;
	case GETFLAME:        handleGETFLAME();break;
	default:              break;
	}
	resetComms();
}
