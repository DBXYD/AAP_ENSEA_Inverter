/*
 * TCN75A.c
 *
 *  Created on: Aug 1, 2023
 *      Author: nicolas
 */
#include "mylibs/TCN75A.h"
#include "FreeRTOS.h"
#include "semphr.h"

extern SemaphoreHandle_t xUartMutex;
extern SemaphoreHandle_t xI2CMutex;
extern QueueHandle_t xTemperatureQueue;
TCN75A_HandleTypeDef hTCN75A1;


void vTask_TCN75A(void *pvParameters){
	I2C_HandleTypeDef* hi2c = (I2C_HandleTypeDef*) pvParameters;
	if(xSemaphoreTake(xUartMutex, portMAX_DELAY) == pdTRUE){
		printf("Init Task TCN75A...   ");
		xSemaphoreGive(xUartMutex);
	}
	TCN75A_Init(&hTCN75A1, hi2c);
	if(xSemaphoreTake(xUartMutex, portMAX_DELAY) == pdTRUE){
		printf(" Done\r\n");
		xSemaphoreGive(xUartMutex);
	}
	vTaskDelay(1000);
	for(;;){
		TCN75A_Read_Temperature(&hTCN75A1);
		if(xSemaphoreTake(xUartMutex, portMAX_DELAY) == pdTRUE){
			printf("Temperature %2.2f°C\r\n",hTCN75A1.temperature);
			xSemaphoreGive(xUartMutex);
			if(pdPASS == xQueueSend(xTemperatureQueue, &hTCN75A1.temperature, portMAX_DELAY)){
				printf("Temperature transmit to fan controller\r\n");
			}

		}
		vTaskDelay(1000);
		HAL_GPIO_TogglePin(USR_LED_3_GPIO_Port, USR_LED_3_Pin);
	}
}

void TCN75A_Init(TCN75A_HandleTypeDef* hTCN75A, I2C_HandleTypeDef* hi2c){
	hTCN75A->hi2c = hi2c;
	hTCN75A->I2C_addr = _TCN75A_I2C_ADDR;

	uint8_t config[2] = {_TCN75A_RP_CONFIG, _TCN75A_12BITS};
	HAL_I2C_Master_Transmit(hTCN75A->hi2c, hTCN75A->I2C_addr<<1, config, 2, HAL_MAX_DELAY);
}

void TCN75A_Read_Temperature(TCN75A_HandleTypeDef* hTCN75A){
	uint8_t data[2] = {0x00, 0x00};
	if(xSemaphoreTake(xI2CMutex, portMAX_DELAY)==pdTRUE){
		//HAL_I2C_Master_Transmit(hTCN75A->hi2c, hTCN75A->I2C_addr<<1, data, 1, HAL_MAX_DELAY);
		//HAL_I2C_Master_Receive(hTCN75A->hi2c, hTCN75A->I2C_addr<<1, data, 2, HAL_MAX_DELAY);
		HAL_I2C_Mem_Read(hTCN75A->hi2c, hTCN75A->I2C_addr<<1, _TCN75A_RP_TA, 1, data, 2, HAL_MAX_DELAY);
		xSemaphoreGive(xI2CMutex);
	}
		hTCN75A->temperature_raw = (data[0]<<4)|(data[1]>>4);
		hTCN75A->temperature = (float)hTCN75A->temperature_raw / 16.0;
}
