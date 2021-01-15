#ifndef COREFUNCTIONS_H
#define COREFUNCTIONS_H

//core thermostat functions: schedule, reports

#define LOGADDRESS              0x3000 //start address for logging ON/OFF times for each day; 4 bytes: day, month and 2 bytes for minutes
#define PROGRAMADDRESS 			0x1000


#include "main.h"
#include <RTCFunctions.h>
#include "spi_flash.h"


typedef struct{ //to keep things a bit simpler
  uint8_t hour, minute, temperature;
}Program;

typedef struct{
	Program programArray[7];
	uint8_t numberOfActivePrograms;
}DaySchedule;

typedef struct Schedule_t{
	DaySchedule daySchedule[8];
}Schedule;

Schedule schedule;
uint8_t lastp, lastd;
uint8_t scheduleUpdated;

/*
 * Programs in a day handlers
 * */


uint8_t programCount(uint8_t day);

float getScheduleTemperature(uint8_t hour, uint8_t minute, uint8_t dow);


/* Schedule management */
void loadSchedule();

void sortProgramsForDay(uint8_t day);

void saveSchedule();

void updateProgram(DaySchedule p, uint8_t dow);

DaySchedule getDaySchedule(uint8_t dow);


/*                      FLAME RELAY CONTROL                     */

void relay(uint8_t state);

/*                      IP TO STRING DISPLAY FUNCTION           */
/*
void displayPassword();

void clearDisplayPassword();

void printIP();
*/



/*                      DATA LOGGING FUNCTIONS                  */

/*
 * Data is structured in a sequence of 2 bytes for each day logged
 * The address is given by the formula "sectorAddress = (month * 31 + day) * 2", and the global address is "address = LOGADDRESS + yearsLogged * 4096 + sectorAddress
 * start address = 2*(31+1)     = 2 * 32  =  64
 * stop  address = 2*(12*31+31) = 2 * 403 = 806
 * sector byte 4095 marks wether the sector is full or not (a year is or not logged)
 * sector byte 0 stores the last 2 digits of the year being logged, 0xFF means not yet initialized
 *
 * */

/*

uint32_t logStop;
class logObject{
  bool logExists = 0;
  logComponent currentYear[404], lastYear[404];
  uint32_t logStartAddress = LOGADDRESS, lastLogAddress;
  int recordedYears = 0;
  uint8_t crty;
  
  uint32_t flashAddress(uint8_t d, uint8_t m, uint8_t y){
    if(crty - y < recordedYears)
      return 0;
    return LOGADDRESS + 4096 * (crty - y) + 2 * (31 * m + d);
  }
  
  uint32_t flashAddress(uint8_t d, uint8_t m){
    return LOGADDRESS + 4096 * recordedYears + 2 * (31 * m + d);
  }
  
  uint32_t flashAddress(int index){
    return LOGADDRESS + 4096 * recordedYears + 2 * index;
  }
  
  uint32_t flashAddress(){
    return LOGADDRESS + 4096 * recordedYears;
  }
  
  void scanForLogs(){
    if(flash.readByte(LOGADDRESS) != 0xFF)
      logExists = 1;
    while(flash.readByte(flashAddress() + 4095) != 0xFF)
      recordedYears++;
    //check if the thermostat is powered the year after the last log; if so, mark the last year as full, and record on a new sector
    if(flash.readByte(flashAddress() + 4095) != 0xFF && flash.readByte(flashAddress()) < tempDate.Year){
      flash.writeByte(flashAddress() + 4095, 0x01);
      recordedYears++;
    }
  }
  
  bool readComponent(uint32_t address, logComponent* ret){
    ret->m0 =      flash.readByte(address);
    ret->m1 =      flash.readByte(address+1);
    return 1;
  }
  
  void fill(){
    if(recordedYears > 0){
      for(int i=32;i<=403;i++){
        readComponent(LOGADDRESS + (recordedYears-1)*4096 + i * 2, &lastYear[i]);
      }
    }
    for(int i=32;i<=403;i++)
        readComponent(LOGADDRESS + recordedYears*4096 + i * 2, &currentYear[i]);
  }
  
public:
  
  void init(){ //initialization of the log data structure; also does corrections to the flash memory resulted from long times of being unpowered
    //set all the bytes in the log to 0xFF to prepare for writing to flash (unflashed memory is 0xFF)
    for(int i=0;i<=403;i++){
      currentYear[i].m0 = 0xFF;
      currentYear[i].m1 = 0xFF;
      lastYear[i].m0    = 0xFF;
      lastYear[i].m1    = 0xFF;
    }
    //scan the memory for existing logs
    scanForLogs();
    fill();
    if(flash.readByte(flashAddress()) == 0xFF)
      flash.writeByte(flashAddress(), tempDate.Year);
    crty = tempDate.Year;
  }
  
  void log(uint16_t minutes){
    uint8_t day = tempDate.Date;
    uint8_t month = tempDate.Month;
    uint8_t year = tempDate.Year;
    if(year > crty){
      init();
    }
    int index = month * 31 + day;
    currentYear[index].m0 = minutes>>8;
    currentYear[index].m1 = minutes & 0xFF;
    flash.writeByte(flashAddress(index), currentYear[index].m0);
    flash.writeByte(flashAddress(index)+1, currentYear[index].m1);
  }
  
  uint32_t getLoggedDay(uint8_t day, uint8_t month, uint8_t year){
    if(flashAddress(day, month, year) == 0) //data does not exist
      return 0;
    logComponent returnDay;
    readComponent(flashAddress(day, month, year), &returnDay);
    if(returnDay.m0 == 0xFF && returnDay.m1 == 0xFF)
      return 0;
    return returnDay.m0<<8 | returnDay.m1;
  }
  
  uint32_t getLoggedMonth(uint8_t month, uint8_t year){
    uint32_t ret = 0;
    for(uint8_t i=1;i<=31;i++)
      ret += getLoggedDay(i, month, year);
    return ret;
  }
  
  uint32_t getLoggedYear(uint8_t year){
    uint32_t ret = 0;
    for(uint8_t m = 1; m <= 12; m++)
      for(uint8_t d = 1; d <= 31; d++)
        ret += getLoggedDay(d,m,year);
    return ret;
  }
};

logObject Log;
*/

#endif
