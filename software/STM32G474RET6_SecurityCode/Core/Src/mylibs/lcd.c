/*
 * lcd.c
 *
 *  Created on: Jul 26, 2023
 *      Author: nicolas
 */

#include "mylibs/lcd.h"
#include "FreeRTOS.h"
#include "semphr.h"

extern SemaphoreHandle_t xUartMutex;
extern SemaphoreHandle_t xI2CMutex;
LCD_HandleTypeDef hlcd1;
uint8_t LCD_Text_Buffer[_LCD_MAX_CHAR];
const uint8_t _ROW_16[] = {0x80, 0xC0};

// Task
void vTask_LCD(void *pvParameters){
	int time = 0;
	I2C_HandleTypeDef* hi2c = (I2C_HandleTypeDef*) pvParameters;
	if(xSemaphoreTake(xUartMutex, portMAX_DELAY) == pdTRUE){
		printf("Init Task LCD...      ");
		xSemaphoreGive(xUartMutex);
	}
	LCD_Init(&hlcd1, hi2c);
	if(xSemaphoreTake(xUartMutex, portMAX_DELAY) == pdTRUE){
		printf(" Done\r\n");
		xSemaphoreGive(xUartMutex);
	}
	for(;;){
		snprintf((char*)(&hlcd1)->LCD_Text_Buffer, _LCD_MAX_CHAR, "Time : %4d sec", time);
		LCD_Print(&hlcd1, (&hlcd1)->LCD_Text_Buffer, _LCD_1ST_LINE);
		vTaskDelay(1000);
		time++;
		HAL_GPIO_TogglePin(USR_LED_1_GPIO_Port, USR_LED_1_Pin);
	}
}

// Fonction d'écriture d'une commande sur l'écran LCD
HAL_StatusTypeDef LCD_Send_Command(LCD_HandleTypeDef *hlcd, uint8_t command) {
	uint8_t data[2] = {hlcd->LCD_Command, command};
	HAL_StatusTypeDef ret;
	if(xSemaphoreTake(xI2CMutex, portMAX_DELAY)==pdTRUE){
		ret = HAL_I2C_Master_Transmit(hlcd->LCD_hi2c, hlcd->LCD_I2C_addr<<1, data, sizeof(data), HAL_MAX_DELAY);
		xSemaphoreGive(xI2CMutex);
	}
	return ret;
}

// Fonction d'écriture d'une donnée (caractère) sur l'écran LCD
HAL_StatusTypeDef LCD_Send_Data(LCD_HandleTypeDef *hlcd, uint8_t data) {
	uint8_t data_array[2] = {hlcd->LCD_Data, data};
	HAL_StatusTypeDef ret;
	if(xSemaphoreTake(xI2CMutex, portMAX_DELAY)==pdTRUE){
		ret = HAL_I2C_Master_Transmit(hlcd->LCD_hi2c, hlcd->LCD_I2C_addr<<1, data_array, sizeof(data_array), HAL_MAX_DELAY);
		xSemaphoreGive(xI2CMutex);
	}
	return ret;
}

// Fonction d'initialisation de l'écran LCD
void LCD_Init(LCD_HandleTypeDef *hlcd, I2C_HandleTypeDef *hi2c) {
	//	int debug;
	//	uint8_t data[2];
	hlcd->LCD_hi2c = hi2c;
	hlcd->LCD_I2C_addr = _LCD_I2C_TXT_ADDR;
	hlcd->LCD_Command = _LCD_COMMAND;
	hlcd->LCD_Data = _LCD_DATA;
	hlcd->LCD_Background_Color[0] = 0;
	hlcd->LCD_Background_Color[1] = 255;
	hlcd->LCD_Background_Color[2] = 128;
	sprintf((char*)hlcd->LCD_Text_Buffer,"");

	HAL_Delay(50);
	LCD_Send_Command(hlcd, _LCD_FUNCTIONSET | _LCD_4BITMODE | _LCD_1LINE | _LCD_5x8DOTS);
	//	LCD_Send_Command(hlcd, 0x28);
	HAL_Delay(5);
	LCD_Send_Command(hlcd, _LCD_FUNCTIONSET | _LCD_4BITMODE | _LCD_1LINE | _LCD_5x8DOTS);
	//	LCD_Send_Command(hlcd, 0x28);
	HAL_Delay(1);
	LCD_Send_Command(hlcd, _LCD_FUNCTIONSET | _LCD_4BITMODE | _LCD_1LINE | _LCD_5x8DOTS);
	//	LCD_Send_Command(hlcd, 0x28);
	HAL_Delay(1);
	LCD_Send_Command(hlcd, _LCD_FUNCTIONSET | _LCD_4BITMODE | _LCD_1LINE | _LCD_5x8DOTS);
	//	LCD_Send_Command(hlcd, 0x28);

	LCD_Send_Command(hlcd, _LCD_DISPLAYCONTROL | _LCD_DISPLAYON | _LCD_CURSORON | _LCD_BLINKON);
	LCD_Send_Command(hlcd, _LCD_CLEARDISPLAY);
	HAL_Delay(2);
	LCD_Send_Command(hlcd, _LCD_ENTRYMODESET | _LCD_ENTRYLEFT | _LCD_ENTRYSHIFTDECREMENT);

	//	from https://github.com/4ilo/HD44780-Stm32HAL/blob/master/lcd_lib/lcd.c
	//	LCD_Send_Command(hlcd, 0x33);
	//	LCD_Send_Command(hlcd, 0x32);
	//	LCD_Send_Command(hlcd, 0x28);
	//	LCD_Send_Command(hlcd, 0x01);
	//	LCD_Send_Command(hlcd, 0x0C);
	//	LCD_Send_Command(hlcd, 0x06);

	LCD_Background_Init(hlcd);
	LCD_Set_Background_Color(hlcd, hlcd->LCD_Background_Color, _DIMMING_HALF);
}

void LCD_Clear(LCD_HandleTypeDef *hlcd) {
	LCD_Send_Command(hlcd, _LCD_CLEARDISPLAY);
}

void LCD_Print(LCD_HandleTypeDef *hlcd, uint8_t *message, uint8_t line){
	LCD_Send_Command(hlcd, _ROW_16[line]);
	uint8_t i = 0;
	while (message[i] != '\0') {
		LCD_Send_Data(hlcd, message[i]);
		i++;
	}
}

void LCD_Background_Init(LCD_HandleTypeDef *hlcd){
	uint8_t data[2];
	if(xSemaphoreTake(xI2CMutex, portMAX_DELAY)==pdTRUE){
		data[0] = _REG_MODE1;
		data[1] = 0x00;
		HAL_I2C_Master_Transmit(hlcd->LCD_hi2c, _LCD_I2C_RGB_ADDR<<1, data, 2, HAL_MAX_DELAY);
		data[0] = _REG_OUTPUT;
		data[1] = 0xFF;
		HAL_I2C_Master_Transmit(hlcd->LCD_hi2c, _LCD_I2C_RGB_ADDR<<1, data, 2, HAL_MAX_DELAY);
		data[0] = _REG_MODE2;
		data[1] = 0x20;
		HAL_I2C_Master_Transmit(hlcd->LCD_hi2c, _LCD_I2C_RGB_ADDR<<1, data, 2, HAL_MAX_DELAY);
		xSemaphoreGive(xI2CMutex);
	}
	for(int blink_idx = 0; blink_idx<10; blink_idx++){
		LCD_Set_Background_Color_White(hlcd);
		HAL_Delay(50);
		LCD_Set_Background_Color_Red(hlcd);
		HAL_Delay(50);
	}
}

void LCD_Set_Background_Color(LCD_HandleTypeDef *hlcd, uint8_t rgb[3], uint8_t dimming){
	uint8_t data[2];
	if(xSemaphoreTake(xI2CMutex, portMAX_DELAY)==pdTRUE){
		data[0] = 0x04;
		data[1] = rgb[0]>>dimming;
		HAL_I2C_Master_Transmit(hlcd->LCD_hi2c, _LCD_I2C_RGB_ADDR<<1, data, 2, HAL_MAX_DELAY);

		data[0] = 0x03;
		data[1] = rgb[1]>>dimming;
		HAL_I2C_Master_Transmit(hlcd->LCD_hi2c, _LCD_I2C_RGB_ADDR<<1, data, 2, HAL_MAX_DELAY);

		data[0] = 0x02;
		data[1] = rgb[2]>>dimming;
		HAL_I2C_Master_Transmit(hlcd->LCD_hi2c, _LCD_I2C_RGB_ADDR<<1, data, 2, HAL_MAX_DELAY);
		xSemaphoreGive(xI2CMutex);
	}
}

void LCD_Set_Background_Color_White(LCD_HandleTypeDef *hlcd){
	uint8_t rgb[3] = _COLOR_WHITE;
	LCD_Set_Background_Color(hlcd, rgb, _DIMMING_NO);
}

void LCD_Set_Background_Color_Red(LCD_HandleTypeDef *hlcd){
	uint8_t rgb[3] = _COLOR_RED;
	LCD_Set_Background_Color(hlcd, rgb, _DIMMING_NO);
}

void LCD_Set_Background_Color_Green(LCD_HandleTypeDef *hlcd){
	uint8_t rgb[3] = _COLOR_GREEN;
	LCD_Set_Background_Color(hlcd, rgb, _DIMMING_NO);
}

void LCD_Set_Background_Color_Blue(LCD_HandleTypeDef *hlcd){
	uint8_t rgb[3] = _COLOR_BLUE;
	LCD_Set_Background_Color(hlcd, rgb, _DIMMING_NO);
}
