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

extern SemaphoreHandle_t xUartMutex;
extern TaskHandle_t xHandle_Button;
extern QueueHandle_t xExtIQueue;
extern TIM_HandleTypeDef htim17;
uint8_t break_state = 0;

void vTask_Button(void *pvParameters){
	Button_HandleTypeDef button;

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
				break;
			case USR_BTN_2_Pin:	//0x0010 PA4
//				HAL_GPIO_TogglePin(Pwr_Enable_V_GPIO_Port, Pwr_Enable_V_Pin);
				break_state = 1 - break_state;
				if(break_state){
					__HAL_TIM_SET_COMPARE(&htim17, TIM_CHANNEL_1, 256);
				}
				else{
					__HAL_TIM_SET_COMPARE(&htim17, TIM_CHANNEL_1, 0);
				}
				break;
			case USR_BTN_3_Pin:	//0x0040 PB6
//				HAL_GPIO_TogglePin(Pwr_Enable_W_GPIO_Port, Pwr_Enable_W_Pin);
				break;
			case Soft_NRST_Pin:	//0x0080 PB7
				break;
			case ENC_BTN_Pin:	//0x0020 PA5
				break;
			default:
				break;
			}
		}
		vTaskDelay(500);
	}
}

void Button_Init(){
	HAL_GPIO_WritePin(Pwr_Enable_U_GPIO_Port, Pwr_Enable_U_Pin, RESET);
	HAL_GPIO_WritePin(Pwr_Enable_V_GPIO_Port, Pwr_Enable_V_Pin, RESET);
	HAL_GPIO_WritePin(Pwr_Enable_W_GPIO_Port, Pwr_Enable_W_Pin, RESET);
}

