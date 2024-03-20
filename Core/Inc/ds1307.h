/*
 * ds1307.h
 *
 *  Created on: Feb 20, 2024
 *      Author: Burak
 */

#ifndef INC_DS1307_H_
#define INC_DS1307_H_

#include "stm32f103xb.h"
#include "stm32f1xx.h"

extern I2C_HandleTypeDef hi2c1;

#define DS1307_ADDRESS 0xD0


typedef struct{

	uint8_t Seconds;
	uint8_t Minutes;
	uint8_t Hours;
	uint8_t DayOfWeek;  //DAY
	uint8_t DayOfMonth; //DATE
	uint8_t Month;
	uint8_t Year;

}DS1307_TIME_t;

uint8_t DecToBCD(int dec);
int BCDToDec(uint8_t bdc);

void getTime(DS1307_TIME_t* time);
void setTime(
		uint8_t Seconds,
		uint8_t Minutes,
		uint8_t Hours,
		uint8_t DayOfWeek,  //DAY
		uint8_t DayOfMonth, //DATE
		uint8_t Month,
		uint8_t Year
);

#endif /* INC_DS1307_H_ */
