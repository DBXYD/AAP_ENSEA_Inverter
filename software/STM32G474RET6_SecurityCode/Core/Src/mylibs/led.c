/*
 * led.c
 *
 *  Created on: Aug 1, 2023
 *      Author: nicolas
 */
#include "mylibs/led.h"

void vTask_LED(void *pvParameters){
	uint8_t led = 0;
	uint8_t dir = 1;
	printf("Init LED...           ");
	LED_Init();
	printf(" Done\r\n");
	for(;;){
		LED_Write(led);
		if(dir){
			led = 2*led+1;
			if(led==0x0F) dir = 0;
		}
		else{
			led = (led-1)/2;
			if(led==0x00) dir = 1;
		}
		vTaskDelay(1000);
	}
}

void LED_Init(){

}

void LED_Write(uint8_t leds){
	HAL_GPIO_WritePin(USR_LED_1_GPIO_Port, USR_LED_1_Pin, (leds>>0)&1);
	HAL_GPIO_WritePin(USR_LED_2_GPIO_Port, USR_LED_2_Pin, (leds>>1)&1);
	HAL_GPIO_WritePin(USR_LED_3_GPIO_Port, USR_LED_3_Pin, (leds>>2)&1);
	HAL_GPIO_WritePin(USR_LED_4_GPIO_Port, USR_LED_4_Pin, (leds>>3)&1);
}
