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


void Motor_Init(void){
	HAL_TIMEx_ConfigBreakDeadTime(&htim1, 100);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
}

void Motor_Loop(int alpha){
	int pwm_max = 1023;
	int nalpha = pwm_max - alpha;
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, alpha);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, nalpha);
}
