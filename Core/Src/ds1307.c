/*
 * ds1307.c
 *
 *  Created on: Feb 20, 2024
 *      Author: Burak Özsoy
 */

#include "ds1307.h"

uint8_t DecToBCD(int dec){

	return (uint8_t) ((dec/10 * 16) + (dec % 10));
}

int BCDToDec(uint8_t bdc){

	return (int) ((bdc/16 * 10 ) + (bdc % 16));
}

void getTime(DS1307_TIME_t* time){

	uint8_t currentTime[7];
	HAL_I2C_Mem_Read(&hi2c1, DS1307_ADDRESS, 0x00, 1, currentTime, sizeof(currentTime), 10);


	time->Seconds 		= BCDToDec(currentTime[0]);
	time->Minutes 		= BCDToDec(currentTime[1]);
	time->Hours 		= BCDToDec(currentTime[2]);
	time->DayOfWeek 	= BCDToDec(currentTime[3]);
	time->DayOfMonth	= BCDToDec(currentTime[4]);
	time->Month			= BCDToDec(currentTime[5]);
	time->Year 			= BCDToDec(currentTime[6]);

	}

void setTime(
		uint8_t Seconds,
		uint8_t Minutes,
		uint8_t Hours,
		uint8_t DayOfWeek,  //DAY
		uint8_t DayOfMonth, //DATE
		uint8_t Month,
		uint8_t Year
){
	uint8_t TimeAdjusting[7];

	TimeAdjusting[0]= DecToBCD(Seconds);
	TimeAdjusting[1]= DecToBCD(Minutes);
	TimeAdjusting[2]= DecToBCD(Hours);
	TimeAdjusting[3]= DecToBCD(DayOfWeek);
	TimeAdjusting[4]= DecToBCD(DayOfMonth);
	TimeAdjusting[5]= DecToBCD(Month);
	TimeAdjusting[6]= DecToBCD(Year);
	HAL_I2C_Mem_Write(&hi2c1, DS1307_ADDRESS, 0x00, 1, TimeAdjusting, sizeof(TimeAdjusting), 10);
}
