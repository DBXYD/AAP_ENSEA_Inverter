/*
 * button.h
 *
 *  Created on: Sep 30, 2023
 *      Author: nicolas
 */

#ifndef INC_MYLIBS_BUTTON_H_
#define INC_MYLIBS_BUTTON_H_

#include "main.h"

typedef struct {
	GPIO_TypeDef * port;
	uint16_t pin;
} Button_HandleTypeDef;

void vTask_Button(void *pvParameters);
void Button_Init(void);

#endif /* INC_MYLIBS_BUTTON_H_ */
