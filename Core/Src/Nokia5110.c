/*
 * Nokia5110.c
 *
 *  Created on: Feb 16, 2024
 *      Author: Burak Özsoy
 */

#include "Nokia5110.h"

uint8_t frameBuff[504];
bool Nokia5110_Init(void) {

	Nokia5110_Reset();

	if(!Nokia5110_Write(0x21, 0))  //the Command Set in addition mode
		return false;

	if(!Nokia5110_Write(0xBA, 0))  //To send Command Set Voltage VOP ,ORIJINALI 0xC0
		return false;

	if(!Nokia5110_Write(0x07, 0))  //To send Command for setting value of Temp Control
		return false;

	if(!Nokia5110_Write(0x13, 0))  //To send Command to set value of Voltage Bias System
		return false;

	if(!Nokia5110_Write(0x20, 0)) //the Command Set in basic mode
		return false;

	if(!Nokia5110_Write(0x0C, 0))  //setting LCD to display results in Normal Mode
		return false;

	return true;

}

bool Nokia5110_Update(void){

	if(!Nokia5110_Write(0x80, 0))
		return false;

	if(!Nokia5110_Write(0x40, 0))
		return false;

	Nokia5110_BufferWrite(frameBuff, 504);

	return true;

}


void Nokia5110_Reset() {

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);	  //RST Pin is Low
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET); 	  //RST Pin is High
}


void Nokia5110_Clear(void){

	for(int i = 0; i<504; i++)		//LCD_WIDTH * LCD_HEIGHT / 8
		frameBuff[i] = 0x00;		//X-Address and Y-Address has been cleaned

}

void Nokia5110_SetPixel(uint8_t x, uint8_t y, bool bw){

	uint8_t Bi;
	uint16_t By;

	if(x < 0 || x >= LCD_WIDTH || y < 0 || y >= LCD_HEIGHT)
		return;

	By = (y / 8) * 84 + x;
	Bi = y % 8;

	if(bw){

		frameBuff[By] |= (1<<Bi);
	}
	else{

		frameBuff[By] &= ~(1<<Bi);
	}
}



void setPixel(int x, int y)
{
	Nokia5110_SetPixel(x, y, BLACK); // Call setPixel with bw set to Black
}



void clearPixel(int x, int y)
{
	Nokia5110_SetPixel(x, y, WHITE); // call setPixel with bw set to white
}


void setChar(char character, int x, int y, bool bw)
{
  int column; // temp byte to store character's column bitmap
  for (int i=0; i<5; i++) // 5 columns (x) per character
  {
    column = ASCII[character - 0x20][i];
    for (int j=0; j<8; j++) // 8 rows (y) per character
    {
      if (column & (0x01 << j)) // test bits to set pixels
    	  Nokia5110_SetPixel(x+i, y+j, bw);
      else
    	  Nokia5110_SetPixel(x+i, y+j, !bw);
    }
  }
}


void Nokia5110_setStr(char  *dString, int x, int y, bool bw)
{
  while (*dString != 0x00) // loop until null terminator
  {
    setChar(*dString++, x, y, bw);
    x+=5;
    for (int i=y; i<y+8; i++)
    {
    	Nokia5110_SetPixel(x, i, !bw);
    }
    x++;
    if (x > (LCD_WIDTH - 5)) // Enables wrap around
    {
      x = 0;
      y += 8;
    }
  }
}


bool Nokia5110_Write (uint8_t data, uint8_t mode)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8 , GPIO_PIN_RESET);    //CE Pin is Low

	if(mode == 0)
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET); //DC Pin is Low for data send

	else if(mode == 1)
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);	  //DC Pin is High for command send

	else{

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8 , GPIO_PIN_SET);  //CE Pin is High
		return false;
	}
	HAL_SPI_Transmit_DMA(&hspi2, &data, 1);

	return true;
}

 void Nokia5110_BufferWrite(uint8_t* data, uint16_t length){

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8 , GPIO_PIN_RESET);    //CE Pin is Low
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);	  	  //DC Pin is High for command send

	HAL_SPI_Transmit_DMA(&hspi2, data, length);
}

