/*
 * DHT11.h
 *
 *  Created on: Feb 27, 2024
 *      Author: Burak
 */

#ifndef INC_DHT11_H_
#define INC_DHT11_H_

#include "stm32f1xx.h"

extern TIM_HandleTypeDef htim2;

extern float durum,Humidity,Temperature;
extern uint16_t tempVal,humVal;
extern uint8_t dhtVal[2];
extern uint8_t mData[40];
extern uint16_t mTime1, mTime2;
extern uint16_t mbit;
extern uint8_t  parityVal, genParity;

#define DHT11_PORT  DHT11_SENS_GPIO_Port
#define DHT11_PIN	DHT11_SENS_Pin

void usDelay(uint16_t time);
void SetInput(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void SetOutput(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
uint8_t DHT11_Read(void);

#endif /* INC_DHT11_H_ */
