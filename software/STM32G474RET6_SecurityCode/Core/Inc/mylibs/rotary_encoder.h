/*
 * rotary_encoder.h
 *
 *  Created on: Jul 29, 2023
 *      Author: nicolas
 */

#ifndef INC_MYLIBS_ROTARY_ENCODER_H_
#define INC_MYLIBS_ROTARY_ENCODER_H_

#include "main.h"

void vTask_RotaryEnc(void *pvParameters);
void RotaryEnc_Init(TIM_HandleTypeDef* htim);
void ENC_Button_Update(GPIO_PinState ENC_Button_Value);
#endif /* INC_MYLIBS_ROTARY_ENCODER_H_ */
