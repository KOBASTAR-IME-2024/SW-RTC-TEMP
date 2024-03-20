/*
 * nokia5110_Text.h
 *
 *  Created on: Feb 27, 2024
 *      Author: Burak
 */

#ifndef INC_NOKIA5110_TEXT_H_
#define INC_NOKIA5110_TEXT_H_

#include "stm32f1xx.h"
#include "Nokia5110.h"
#include "ds1307.h"

char writeString[20]={0};
extern DS1307_TIME_t time_tr;

void Nokia5110_Text(){

	 	  Nokia5110_Clear();
		  Nokia5110_setStr("TIME", 0, 0, BLACK);
		  Nokia5110_setStr(":", 42, 0, BLACK);
		  Nokia5110_setStr(":", 60, 0, BLACK);
		  Nokia5110_setStr("DATE", 0, 10, BLACK);
		  Nokia5110_setStr("/", 42, 10, BLACK);
		  Nokia5110_setStr("/", 56, 10, BLACK);
		  Nokia5110_setStr("20", 60, 10, BLACK);
		  Nokia5110_setStr("TEMP", 0, 20, BLACK);
		  Nokia5110_setStr(" C", 70, 20, BLACK);
		  Nokia5110_setStr("HMDTY", 0, 30, BLACK);
		  Nokia5110_setStr(" %", 70, 30, BLACK);
		  Nokia5110_setStr("KOBASTAR", 18, 40, WHITE);


		  sprintf(writeString,"%d",time_tr.Seconds);
		  Nokia5110_setStr(writeString , 68, 0, BLACK);

		  sprintf(writeString,"%d",time_tr.Minutes);
		  Nokia5110_setStr(writeString , 48, 0, BLACK);

		  sprintf(writeString,"%d",time_tr.Hours);
		  Nokia5110_setStr(writeString , 30, 0, BLACK);

		  sprintf(writeString,"%d",time_tr.Year);
		  Nokia5110_setStr(writeString, 72, 10, BLACK);

		  sprintf(writeString,"%d",time_tr.Month);
		  Nokia5110_setStr(writeString, 48, 10, BLACK);

		  sprintf(writeString,"%d",time_tr.DayOfMonth);
		  Nokia5110_setStr(writeString, 30, 10, BLACK);

		  sprintf(writeString,"%0.2f",Temperature);
		  Nokia5110_setStr(writeString, 40, 20, BLACK);

		  sprintf(writeString,"%0.2f",Humidity);
		  Nokia5110_setStr(writeString, 40, 30, BLACK);

		  Nokia5110_Update();

}

#endif /* INC_NOKIA5110_TEXT_H_ */
