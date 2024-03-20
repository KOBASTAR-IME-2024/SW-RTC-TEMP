/*
 * DHT11.c
 *
 *  Created on: Feb 27, 2024
 *      Author: Burak
 */

#include "DHT11.h"
#include "main.h"

void usDelay(uint16_t time){

	__HAL_TIM_SET_COUNTER(&htim2,0);

	while(__HAL_TIM_GET_COUNTER(&htim2)< time);

}

void SetInput(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){

	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  GPIO_InitStruct.Pin = DHT11_SENS_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	  HAL_GPIO_Init(DHT11_SENS_GPIO_Port, &GPIO_InitStruct);

}

void SetOutput(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){

	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  GPIO_InitStruct.Pin = DHT11_SENS_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	  HAL_GPIO_Init(DHT11_SENS_GPIO_Port, &GPIO_InitStruct);

}

uint8_t DHT11_Read(void){

		for (int a = 0; a < 40; a++) {
	        mData[a] = 0;
	    }
	    mTime1 = 0,
		mTime2 = 0,
		durum=0,
		tempVal=0,
		humVal=0,
		parityVal = 0,
		genParity = 0,
		mbit = 0;

	    SetOutput(DHT11_PORT,DHT11_PIN);
		HAL_GPIO_WritePin(DHT11_PORT,DHT11_PIN,GPIO_PIN_RESET);
	    usDelay(18000);
	    SetInput(DHT11_PORT,DHT11_PIN);

		 __HAL_TIM_SET_COUNTER(&htim2, 0);				//set timer counter to zero
		while(HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) == GPIO_PIN_SET)
		if((uint16_t)__HAL_TIM_GET_COUNTER(&htim2) > 500)
			return 0;

		__HAL_TIM_SET_COUNTER(&htim2, 0);
		while(HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) == GPIO_PIN_RESET)
		if((uint16_t)__HAL_TIM_GET_COUNTER(&htim2) > 500)
			return 0;


		mTime1 = (uint16_t)__HAL_TIM_GET_COUNTER(&htim2);

		__HAL_TIM_SET_COUNTER(&htim2, 0);
		while(HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) == GPIO_PIN_SET)

		if((uint16_t)__HAL_TIM_GET_COUNTER(&htim2) > 500)
		return 0;

	    mTime2 = (uint16_t)__HAL_TIM_GET_COUNTER(&htim2);


		if(mTime1 < 75 && mTime1 > 85 && mTime2 < 75 && mTime2 > 85)
			return 0;





		for(int j = 0; j < 40; j++)
		{
			__HAL_TIM_SET_COUNTER(&htim2, 0);
			while(HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) == GPIO_PIN_RESET) if((uint16_t)__HAL_TIM_GET_COUNTER(&htim2) > 500) return 0;
			__HAL_TIM_SET_COUNTER(&htim2, 0);
			while(HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) == GPIO_PIN_SET) if((uint16_t)__HAL_TIM_GET_COUNTER(&htim2) > 500) return 0;
			mTime1 = (uint16_t)__HAL_TIM_GET_COUNTER(&htim2);

			//check pass time in high state
			//if pass time 25uS set as LOW
			if(mTime1 > 20 && mTime1 < 30)
			{
				mbit = 0;
			}
			else if(mTime1 > 60 && mTime1 < 80) //if pass time 70 uS set as HIGH
			{
				 mbit = 1;
			}

			//set i th data in data buffer
			mData[j] = mbit;

		}

		//get hum value from data buffer
		for(int i = 0; i < 8; i++)
		{
			humVal += mData[i];
			humVal = humVal << 1;
		}

		//get temp value from data buffer
		for(int i = 16; i < 24; i++)
		{
			tempVal += mData[i];
			tempVal = tempVal << 1;
		}

		//get parity value from data buffer
		for(int i = 32; i < 40; i++)
		{
			parityVal += mData[i];
			parityVal = parityVal << 1;
		}

		parityVal = parityVal >> 1;
		humVal = humVal >> 1;
		tempVal = tempVal >> 1;

		genParity = humVal + tempVal;


		dhtVal[0]= tempVal;
		dhtVal[1] = humVal;

		return 1;

}

