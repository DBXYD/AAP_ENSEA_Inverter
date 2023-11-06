/*
 * button.c
 *
 *  Created on: Sep 30, 2023
 *      Author: nicolas
 */

#include "mylibs/button.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "queue.h"
#include "mylibs/button.h"
#include "mylibs/break.h"
#include "adc.h"

extern SemaphoreHandle_t xUartMutex;
extern TaskHandle_t xHandle_Button;
extern QueueHandle_t xExtIQueue;
extern TIM_HandleTypeDef htim17;
extern BREAK_HandleTypeDef hbreak1;
uint8_t break_state = 0;

void vTask_Button(void *pvParameters){
	Button_HandleTypeDef button;
	uint16_t VBus_raw;
	float Vin, VBus;

	if(xSemaphoreTake(xUartMutex, portMAX_DELAY) == pdTRUE){
		printf("Init Button...         ");
		xSemaphoreGive(xUartMutex);
	}
	Button_Init();
	if(xSemaphoreTake(xUartMutex, portMAX_DELAY) == pdTRUE){
		printf("Done\r\n");
		xSemaphoreGive(xUartMutex);
	}

	for(;;){
		if(pdPASS == xQueueReceive(xExtIQueue, &button, portMAX_DELAY)){
			switch(button.pin){
			case USR_BTN_1_Pin:	//0x0004 PD2

				HAL_GPIO_TogglePin(Pwr_Enable_U_GPIO_Port, Pwr_Enable_U_Pin);
				HAL_GPIO_TogglePin(Pwr_Enable_V_GPIO_Port, Pwr_Enable_V_Pin);
				//				HAL_GPIO_TogglePin(Pwr_Enable_W_GPIO_Port, Pwr_Enable_W_Pin);
				if(xSemaphoreTake(xUartMutex, portMAX_DELAY) == pdTRUE){
					printf("BTN1\r\n");
					xSemaphoreGive(xUartMutex);
				}
				break;
			case USR_BTN_2_Pin:	//0x0010 PA4
				__HAL_TIM_SET_COMPARE(hbreak1.htim, TIM_CHANNEL_1, 0);
				HAL_ADC_Start(&hadc4);
				HAL_ADC_PollForConversion(&hadc4, HAL_MAX_DELAY);
				VBus_raw = HAL_ADC_GetValue(&hadc4);
				Vin = ((float)VBus_raw)*3.3/4096;
				VBus = (Vin-2.56)/4*471;
				hbreak1.VBus_ref = VBus;
				hbreak1.VBus_max = VBus*BREAK_COEFF;
				hbreak1.VBus_max_configured = 1;
//				Break_Set_VBus_ref(&hbreak1, VBus);
				//				HAL_GPIO_TogglePin(Pwr_Enable_V_GPIO_Port, Pwr_Enable_V_Pin);
				//				break_state = 1 - break_state;
				//				if(break_state){
				//					__HAL_TIM_SET_COMPARE(&htim17, TIM_CHANNEL_1, 256);
				//				}
				//				else{
				//					__HAL_TIM_SET_COMPARE(&htim17, TIM_CHANNEL_1, 0);
				//				}
				if(xSemaphoreTake(xUartMutex, portMAX_DELAY) == pdTRUE){
					printf("BTN2\r\n");
					xSemaphoreGive(xUartMutex);
				}
				break;
			case USR_BTN_3_Pin:	//0x0040 PB6
				//				HAL_GPIO_TogglePin(Pwr_Enable_W_GPIO_Port, Pwr_Enable_W_Pin);
				if(xSemaphoreTake(xUartMutex, portMAX_DELAY) == pdTRUE){
					printf("BTN3\r\n");
					xSemaphoreGive(xUartMutex);
				}
				break;
			case Soft_NRST_Pin:	//0x0080 PB7
				if(xSemaphoreTake(xUartMutex, portMAX_DELAY) == pdTRUE){
					printf("BTN4\r\n");
					xSemaphoreGive(xUartMutex);
				}
				break;
			case ENC_BTN_Pin:	//0x0020 PA5
				if(xSemaphoreTake(xUartMutex, portMAX_DELAY) == pdTRUE){
					printf("BTN_ENC\r\n");
					xSemaphoreGive(xUartMutex);
				}
				break;
			default:
				break;
			}
		}

		vTaskDelay(1000);
	}
}

void Button_Init(){
	HAL_GPIO_WritePin(Pwr_Enable_U_GPIO_Port, Pwr_Enable_U_Pin, RESET);
	HAL_GPIO_WritePin(Pwr_Enable_V_GPIO_Port, Pwr_Enable_V_Pin, RESET);
	HAL_GPIO_WritePin(Pwr_Enable_W_GPIO_Port, Pwr_Enable_W_Pin, RESET);
}

