/*
 * TCN75A.h
 *
 *  Created on: Aug 1, 2023
 *      Author: nicolas
 */

#ifndef INC_MYLIBS_TCN75A_H_
#define INC_MYLIBS_TCN75A_H_

#define _TCN75A_I2C_ADDR 			0x48

#define _TCN75A_RP_TA 				0x00
#define _TCN75A_RP_CONFIG			0x01
#define _TCN75A_RP_THYST 			0x02
#define _TCN75A_RP_TSET				0x03

#define _TCN75A_ONE_SHOT_DISABLE	0x00 //Default
#define _TCN75A_ONE_SHOT_ENABLE		0x80
#define _TCN75A_9BITS 				0x00 //Default
#define _TCN75A_10BITS 				0x20
#define _TCN75A_11BITS	 			0x40
#define _TCN75A_12BITS	 			0x60
#define _TCN75A_FAULT_Q1			0x00 //Default
#define _TCN75A_FAULT_Q2			0x08
#define _TCN75A_FAULT_Q4			0x10
#define _TCN75A_FAULT_Q6			0x18
#define _TCN75A_ALERT_POL_L			0x00 //Default
#define _TCN75A_ALERT_POL_H			0x04
#define _TCN75A_COMP_MODE			0x00 //Default
#define _TCN75A_INT_MODE			0x02
#define _TCN75A_SHUTDOWN_DISABLE 	0x00 //Default
#define _TCN75A_SHUTDOWN_ENABLE		0x01

#include "main.h"

typedef struct {
	I2C_HandleTypeDef *hi2c;
	uint8_t I2C_addr;
	uint8_t Command;
	uint8_t Data;
	uint16_t temperature_raw;
	float temperature;
} TCN75A_HandleTypeDef;

extern TCN75A_HandleTypeDef hTCN75A1;

void vTask_TCN75A(void *pvParameters);
void TCN75A_Init(TCN75A_HandleTypeDef* hTCN75A, I2C_HandleTypeDef* hi2c);

#endif /* INC_MYLIBS_TCN75A_H_ */
