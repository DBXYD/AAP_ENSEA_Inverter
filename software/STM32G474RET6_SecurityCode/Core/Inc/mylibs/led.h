/*
 * led.h
 *
 *  Created on: Aug 1, 2023
 *      Author: nicolas
 */

#ifndef INC_MYLIBS_LED_H_
#define INC_MYLIBS_LED_H_

#include "main.h"

void vTask_LED(void *pvParameters);
void LED_Init(void);
void LED_Write(uint8_t leds);


#endif /* INC_MYLIBS_LED_H_ */
