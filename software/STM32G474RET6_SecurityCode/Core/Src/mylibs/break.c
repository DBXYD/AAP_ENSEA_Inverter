/*
 * break.c
 *
 *  Created on: Sep 30, 2023
 *      Author: nicolas
 */

#include "mylibs/break.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "adc.h"

extern SemaphoreHandle_t xUartMutex;

void vTask_Break(void *pvParameters){
	BREAK_HandleTypeDef hbreak1;
	uint16_t VBus_raw;
	if(xSemaphoreTake(xUartMutex, portMAX_DELAY) == pdTRUE){
		printf("Init Break...         ");
		xSemaphoreGive(xUartMutex);
	}
	Break_Init(&hbreak1, (TIM_HandleTypeDef*)pvParameters);
	if(xSemaphoreTake(xUartMutex, portMAX_DELAY) == pdTRUE){
		printf(" Done\r\n");
		xSemaphoreGive(xUartMutex);
	}

	for(;;){
//		HAL_ADC_Start(&hadc4);
//		HAL_ADC_PollForConversion(&hadc4, HAL_MAX_DELAY);
//		VBus_raw = HAL_ADC_GetValue(&hadc4);
//		if(xSemaphoreTake(xUartMutex, portMAX_DELAY) == pdTRUE){
//			printf("Vbus 0x%4\r\n", VBus_raw);
//			xSemaphoreGive(xUartMutex);
//		}
		vTaskDelay(1000);
	}
}

void Break_Init(BREAK_HandleTypeDef* hbreak, TIM_HandleTypeDef* htim){
	hbreak->htim = htim;
	hbreak->Max_Pwm = __HAL_TIM_GET_AUTORELOAD(htim);
	hbreak->Pwm = 0;
	hbreak->Channel = BREAK_CHANNEL;
	Break_Set_DutyCycle(hbreak, 0);
	HAL_TIM_PWM_Start(hbreak->htim, hbreak->Channel);
}

void Break_Set_DutyCycle(BREAK_HandleTypeDef* hbreak, float dutyCycle){
	hbreak->Pwm = (uint16_t)(dutyCycle*((float)hbreak->Max_Pwm));
	__HAL_TIM_SET_COMPARE(hbreak->htim, hbreak->Channel, hbreak->Pwm);
}

