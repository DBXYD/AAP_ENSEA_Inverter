/*
 * motor.c
 *
 *  Created on: Oct 2, 2023
 *      Author: nicolas
 */

#include "mylibs/motor.h"
#include "tim.h"
#include <stdio.h>
#include <string.h>

extern TIM_HandleTypeDef htim1;

#define PWM_MAX 1023

void Motor_Init(void){
	HAL_TIMEx_ConfigBreakDeadTime(&htim1, 100);
	Motor_Set_Speed_Instant(512);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
}

void Motor_DeInit(void){
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
	HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2);
	Motor_Set_Speed(512);
}

void Motor_Set_Speed_Instant(int speed){
	int alpha, nalpha;
	alpha = speed;
	nalpha = PWM_MAX - speed;
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, alpha);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, nalpha);
}

void Motor_Set_Speed(int target){
	int speed = __HAL_TIM_GET_COMPARE(&htim1, TIM_CHANNEL_1);
	int alpha, nalpha;
	while(target != speed){
		if(speed < target) speed++;
		if(speed > target) speed--;
		alpha = speed;
		nalpha = PWM_MAX - speed;
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, alpha);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, nalpha);
		HAL_Delay(10);
	}
}
