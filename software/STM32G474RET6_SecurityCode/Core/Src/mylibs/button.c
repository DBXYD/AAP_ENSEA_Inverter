/*
 * button.c
 *
 *  Created on: Sep 30, 2023
 *      Author: nicolas
 */

#include "mylibs/button.h"
#include "FreeRTOS.h"
#include "semphr.h"


void vTask_Button(void *pvParameters){
	uint8_t led = 0;
	uint8_t dir = 1;
	printf("Init BUTTON...        ");
	Button_Init();
	printf("Done\r\n");
	for(;;){
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		HAL_GPIO_TogglePin(Pwr_Enable_U_GPIO_Port, Pwr_Enable_U_Pin);
		vTaskDelay(100);
	}
}

void Button_Init(){

}

