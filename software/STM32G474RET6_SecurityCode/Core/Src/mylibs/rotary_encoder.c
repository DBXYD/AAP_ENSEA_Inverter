/*
 * rotary_encoder.c
 *
 *  Created on: Jul 29, 2023
 *      Author: nicolas
 */
#include "mylibs/rotary_encoder.h"
#include "FreeRTOS.h"
#include "semphr.h"

extern SemaphoreHandle_t xUartMutex;

uint8_t value;
uint32_t last_Tick = 0;

void vTask_RotaryEnc(void *pvParameters){
	TIM_HandleTypeDef* htim = (TIM_HandleTypeDef*) pvParameters;
	uint32_t RotaryEnc_Previous_Value = 0;
	uint32_t RotaryEnc_Value = 0;
	printf("Init Rotary Encoder...");
	RotaryEnc_Init(htim);
	printf(" Done\r\n");
	for(;;){
		RotaryEnc_Value = __HAL_TIM_GET_COUNTER(htim);

		if(RotaryEnc_Previous_Value != RotaryEnc_Value){
			if(xSemaphoreTake(xUartMutex, portMAX_DELAY) == pdTRUE){
				printf("Rot_Enc : %6d\r\n", RotaryEnc_Value);
				xSemaphoreGive(xUartMutex);
			}
			RotaryEnc_Previous_Value = RotaryEnc_Value;
		}
		vTaskDelay(100);
	}
}

void RotaryEnc_Init(TIM_HandleTypeDef* htim){
	HAL_TIM_Encoder_Start(htim, TIM_CHANNEL_1);
}
