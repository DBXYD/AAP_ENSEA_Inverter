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
BREAK_HandleTypeDef hbreak1;

void vTask_Break(void *pvParameters){
	uint16_t VBus_raw;
	float Vin, VBus;
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
		HAL_ADC_Start(&hadc4);
		HAL_ADC_PollForConversion(&hadc4, HAL_MAX_DELAY);
		VBus_raw = HAL_ADC_GetValue(&hadc4);
		Vin = ((float)VBus_raw)*3.3/4096;
		VBus = (Vin-2.56)/4*471;
		if(hbreak1.VBus_max_configured){
			if(VBus > hbreak1.VBus_max){
				__HAL_TIM_SET_COMPARE(hbreak1.htim, TIM_CHANNEL_1, 256);
			}
			else{
				__HAL_TIM_SET_COMPARE(hbreak1.htim, TIM_CHANNEL_1, 0);
			}
			//						break_state = 1 - break_state;
			//						if(break_state){
			//							__HAL_TIM_SET_COMPARE(&htim17, TIM_CHANNEL_1, 256);
			//						}
			//						else{
			//							__HAL_TIM_SET_COMPARE(&htim17, TIM_CHANNEL_1, 0);

			if(xSemaphoreTake(xUartMutex, portMAX_DELAY) == pdTRUE){
				printf("Vbus 0x%4d; Vin %1.3f V; VBus = %2.2f V; Vref = %2.2f V; Vmax = %2.2f V\r\n", VBus_raw, Vin, VBus, hbreak1.VBus_ref, hbreak1.VBus_max);
				xSemaphoreGive(xUartMutex);
			}
		}
		else{
			__HAL_TIM_SET_COMPARE(hbreak1.htim, TIM_CHANNEL_1, 0);

		}
		vTaskDelay(10);
	}
}

void Break_Init(BREAK_HandleTypeDef* hbreak, TIM_HandleTypeDef* htim){
	hbreak->htim = htim;
	hbreak->Max_Pwm = __HAL_TIM_GET_AUTORELOAD(htim);
	hbreak->Pwm = 0;
	hbreak->Channel = BREAK_CHANNEL;
	hbreak->VBus_max_configured = 0;
	Break_Set_DutyCycle(hbreak, 0);
	HAL_TIM_PWM_Start(hbreak->htim, hbreak->Channel);
}

void Break_Set_DutyCycle(BREAK_HandleTypeDef* hbreak, float dutyCycle){
	hbreak->Pwm = (uint16_t)(dutyCycle*((float)hbreak->Max_Pwm));
	__HAL_TIM_SET_COMPARE(hbreak->htim, hbreak->Channel, hbreak->Pwm);
}

void Break_Set_VBus_ref(BREAK_HandleTypeDef* hbreak, float Vbus_ref){
	hbreak1.VBus_ref = Vbus_ref;
}
