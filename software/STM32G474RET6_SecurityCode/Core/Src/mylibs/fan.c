/*
 * fan.c
 *
 *  Created on: Aug 1, 2023
 *      Author: nicolas
 */

#include "mylibs/fan.h"
#include "FreeRTOS.h"
#include "semphr.h"

extern SemaphoreHandle_t xUartMutex;
extern QueueHandle_t xTemperatureQueue;

void vTask_Fan(void *pvParameters){
	FAN_HandleTypeDef hfan1;
	float temperature;
	float speed = 0;
	if(xSemaphoreTake(xUartMutex, portMAX_DELAY) == pdTRUE){
		printf("Init Fan...           ");
		xSemaphoreGive(xUartMutex);
	}
	Fan_Init(&hfan1, (TIM_HandleTypeDef*)pvParameters);
	if(xSemaphoreTake(xUartMutex, portMAX_DELAY) == pdTRUE){
		printf(" Done\r\n");
		xSemaphoreGive(xUartMutex);
	}

	for(;;){
		if(pdPASS == xQueueReceive(xTemperatureQueue, &temperature, portMAX_DELAY)){
			speed = (temperature > 30) ? 1 : ((temperature < 29) ? 0 : speed);
			Fan_Set_Speed(&hfan1, speed);
		}
		vTaskDelay(1000);
	}
}

void Fan_Init(FAN_HandleTypeDef* hfan, TIM_HandleTypeDef* htim){
	hfan->htim = htim;
	hfan->Max_Pwm = __HAL_TIM_GET_AUTORELOAD(htim);
	hfan->Pwm = 0;
	hfan->Channel = FAN_CHANNEL;
	Fan_Set_Speed(hfan, 0);
	HAL_TIM_PWM_Start(hfan->htim, hfan->Channel);
}

void Fan_Set_Speed(FAN_HandleTypeDef* hfan, float speed){
	hfan->Pwm = (uint16_t)(speed*((float)hfan->Max_Pwm));
	__HAL_TIM_SET_COMPARE(hfan->htim, hfan->Channel, hfan->Pwm);
}
