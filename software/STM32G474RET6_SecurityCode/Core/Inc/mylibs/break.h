/*
 * break.h
 *
 *  Created on: Sep 30, 2023
 *      Author: nicolas
 */

#ifndef INC_MYLIBS_BREAK_H_
#define INC_MYLIBS_BREAK_H_

#include "main.h"
// On PWM 17 CHANNEL 1
#define BREAK_CHANNEL TIM_CHANNEL_1
#define BREAK_COEFF 1.2

typedef struct {
	TIM_HandleTypeDef *htim;
	uint16_t Max_Pwm;
	uint16_t Pwm;
	uint8_t Channel;
	float VBus_ref;
	float VBus_max;
	uint8_t VBus_max_configured;
} BREAK_HandleTypeDef;


void vTask_Break(void *pvParameters);
void Break_Init(BREAK_HandleTypeDef* hbreak, TIM_HandleTypeDef* htim);
void Break_Set_DutyCycle(BREAK_HandleTypeDef* hbreak, float dutyCycle);

#endif /* INC_MYLIBS_BREAK_H_ */
