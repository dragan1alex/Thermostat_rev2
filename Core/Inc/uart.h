#ifndef COMMS_H
#define COMMS_H

#define SETIP           0x01
#define SETAP           0x02
#define SETWLAN         0x03
#define GETSCHEDULE     0x04
#define WRITESCHEDULE   0x05
#define GETCONSUMPTION  0x06
#define GETTEMP         0x07
#define SETTIME         0x08
#define SETDATE         0x09
#define GETSETTEMP      0x0A
#define SETSSID         0x0D
#define SETPASS         0x0E
#define GETFLAME        0x0F
#define PING            0xFF
#define PONG            0xF1
#define STOP            0x00
#define RESET_CMD       0xEE


#define WIFI_UART &huart4

#include <stdio.h>
#include <string.h>
#include <main.h>
uint8_t command;


void resetComms();


void sendPong();

void handleIP();

void handleWLAN();

void handleSETAP();

void handleGETTEMP();

void handleGETSETTEMP();

void handleGETSCHEDULE();

void handleRESET();

void handleWRITESCHEDULE();

void handleSETDATE();

void handleSETTIME();

void handleGETSSID();

void handleGETPASS();

void handleSETSSID();

void handleSETPASS();

void handleGETFLAME();

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#endif
