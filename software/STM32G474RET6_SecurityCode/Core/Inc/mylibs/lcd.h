/*
 * lcd.h
 *
 *  Created on: Jul 26, 2023
 *      Author: nicolas
 */

#ifndef INC_MYLIBS_LCD_H_
#define INC_MYLIBS_LCD_H_

#ifdef __cplusplus
extern "C" {
#endif

#define _LCD_I2C_TXT_ADDR 	0x3E
#define _LCD_I2C_RGB_ADDR 	0x62
#define _LCD_COMMAND 		0x80
#define _LCD_DATA 			0x40
#define _DIMMING_NO 		0
#define _DIMMING_HALF 		1
#define _DIMMING_QUARTER 	2


// Line define
#define _LCD_1ST_LINE 		0
#define _LCD_2ND_LINE		1
#define _LCD_MAX_CHAR		32+1 // for \0
// color define
#define _WHITE           	0
#define _RED             	1
#define _GREEN           	2
#define _BLUE            	3
#define _COLOR_WHITE 		{255, 255, 255}
#define _COLOR_RED 			{255, 0, 0}
#define _COLOR_GREEN 		{0, 255, 0}
#define _COLOR_BLUE 		{0, 0, 255}

#define _REG_MODE1       	0x00
#define _REG_MODE2       	0x01
#define _REG_OUTPUT     	0x08

// Commands
// Clear Display
#define _LCD_CLEARDISPLAY 0x01

// Return Home
#define _LCD_RETURNHOME 0x02

// Entry Mode Set
#define _LCD_ENTRYMODESET 0x04
	// Flags
#define _LCD_ENTRYRIGHT 0x00
#define _LCD_ENTRYLEFT 0x02
#define _LCD_ENTRYSHIFTDECREMENT 0x00
#define _LCD_ENTRYSHIFTINCREMENT 0x01

// Display on/off control
#define _LCD_DISPLAYCONTROL 0x08
	// Flags
#define _LCD_BLINKOFF 0x00
#define _LCD_BLINKON 0x01
#define _LCD_CURSOROFF 0x00
#define _LCD_CURSORON 0x02
#define _LCD_DISPLAYOFF 0x00
#define _LCD_DISPLAYON 0x04

// Cursor or display shift
#define _LCD_CURSORSHIFT 0x10
	// Flags
#define _LCD_MOVELEFT 0x00
#define _LCD_MOVERIGHT 0x04
#define _LCD_CURSORMOVE 0x00
#define _LCD_DISPLAYMOVE 0x08

// Function Set
#define _LCD_FUNCTIONSET 0x20
	// Flags
#define _LCD_5x8DOTS 0x00
#define _LCD_5x10DOTS 0x04
#define _LCD_1LINE 0x00
#define _LCD_2LINE 0x08
#define _LCD_4BITMODE 0x00
#define _LCD_8BITMODE 0x10

// Set CGRAM address
#define _LCD_SETCGRAMADDR 0x40

// Set DDRAM address
#define _LCD_SETDDRAMADDR 0x80

#include "main.h"

typedef struct {
	I2C_HandleTypeDef *LCD_hi2c;
	uint8_t LCD_I2C_addr;
	uint8_t LCD_Command;
	uint8_t LCD_Data;
	uint8_t LCD_Background_Color[3];
	uint8_t LCD_Text_Buffer[_LCD_MAX_CHAR];
} LCD_HandleTypeDef;

extern LCD_HandleTypeDef hlcd1;

void vTask_LCD(void *pvParameters);
HAL_StatusTypeDef LCD_Send_Command(LCD_HandleTypeDef *hlcd, uint8_t command);
HAL_StatusTypeDef LCD_Send_Data(LCD_HandleTypeDef *hlcd, uint8_t data);
void LCD_Init(LCD_HandleTypeDef *hlcd, I2C_HandleTypeDef *hi2c);
void LCD_Clear(LCD_HandleTypeDef *hlcd);
void LCD_Print(LCD_HandleTypeDef *hlcd, uint8_t *message, uint8_t line);
void LCD_Background_Init(LCD_HandleTypeDef *hlcd);
void LCD_Set_Background_Color(LCD_HandleTypeDef *hlcd, uint8_t rgb[3], uint8_t dimming);
void LCD_Set_Background_Color_White(LCD_HandleTypeDef *hlcd);
void LCD_Set_Background_Color_Red(LCD_HandleTypeDef *hlcd);
void LCD_Set_Background_Color_Green(LCD_HandleTypeDef *hlcd);
void LCD_Set_Background_Color_Blue(LCD_HandleTypeDef *hlcd);
// void LCD_Set_Mode(LCD_HandleTypeDef *hlcd, LCD_ModeDef mode);
// LCD_ModeDef LCD_Get_Mode(LCD_HandleTypeDef *hlcd);
// LCD_StateTypeDef LCD_Get_State(LCD_HandleTypeDef *hlcd);

#endif /* INC_MYLIBS_LCD_H_ */
