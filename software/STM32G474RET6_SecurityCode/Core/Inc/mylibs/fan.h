/*
 * fan.h
 *
 *  Created on: Aug 1, 2023
 *      Author: nicolas
 */

#ifndef INC_MYLIBS_FAN_H_
#define INC_MYLIBS_FAN_H_

#define FAN_CHANNEL TIM_CHANNEL_1
#include "main.h"

typedef struct {
	TIM_HandleTypeDef *htim;
	uint16_t Max_Pwm;
	uint16_t Pwm;
	uint8_t Channel;
} FAN_HandleTypeDef;

void vTask_Fan(void *pvParameters);
void Fan_Init(FAN_HandleTypeDef* hfan, TIM_HandleTypeDef* htim);
void Fan_Set_Speed(FAN_HandleTypeDef* hfan, float speed);



#endif /* INC_MYLIBS_FAN_H_ */
