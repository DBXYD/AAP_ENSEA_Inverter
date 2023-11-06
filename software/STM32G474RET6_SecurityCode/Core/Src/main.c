/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "adc.h"
#include "cordic.h"
#include "fmac.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "mylibs/button.h"
#include "mylibs/break.h"
#include "mylibs/lcd.h"
#include "mylibs/rotary_encoder.h"
#include "mylibs/led.h"
#include "mylibs/TCN75A.h"
#include "mylibs/fan.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define UART_TX_BUFFER_SIZE 32
#define UART_RX_BUFFER_SIZE 32
#define STACK_SIZE 256
#define Break_Task_Priority 6
#define Button_Task_Priority 5
#define RotaryEnc_Task_Priority 4
#define LCD_Task_Priority 3
#define TCN75A_Task_Priority 2
#define LED_Task_Priority 1
#define Fan_Task_Priority 0
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t uartTxBuffer[UART_TX_BUFFER_SIZE];
uint8_t uartRxBuffer[UART_RX_BUFFER_SIZE];

SemaphoreHandle_t xUartMutex;
SemaphoreHandle_t xI2CMutex;
QueueHandle_t xTemperatureQueue, xExtIQueue;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
TaskHandle_t xHandle_Break, xHandle_Button, xHandle_LCD, xHandle_Rotary, xHandle_LED, xHandle_TCN75A, xHandle_Fan = NULL;

//void vTask_1(void *pvParameters){
//
//	printf("Task 1 is starting\r\n");
//
//	for(;;){
//		printf("Hello from Task 1\r\n");
//		vTaskDelay(1);
//	}
//}
//
//void vTask_2(void *pvParameters){
//
//	printf("Task 2 is starting\r\n");
//
//	for(;;){
//		vTaskDelay(5);
//		printf("Hello from Task 2\r\n");
//	}
//}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	//	int led = 1;
	//	int PwmBreak = 0;
	//	int uartTxSize = 0;
	//	uint16_t bus_voltage_raw;
	//	float bus_voltage;
	//	int time = 0;
	//	BaseType_t xReturned;


  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_ADC3_Init();
  MX_ADC4_Init();
  MX_CORDIC_Init();
  MX_FMAC_Init();
//  MX_I2C2_Init();
  MX_TIM8_Init();
  MX_TIM15_Init();
  MX_TIM17_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  MX_TIM16_Init();
  MX_TIM1_Init();
  MX_USB_Device_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */

	printf(	"*****************************************\r\n"
			"* ENSEA INVERTER PROJECT                *\r\n"
			"* Firmware revision 1.1                 *\r\n"
			"* By Nicolas Papazoglou & Alexis Martin *\r\n"
			"*****************************************\r\n");
	I2C_Scan(&hi2c2);
	xUartMutex = xSemaphoreCreateMutex();
	xI2CMutex = xSemaphoreCreateMutex();
	xTemperatureQueue = xQueueCreate(1, sizeof(float));
	xExtIQueue = xQueueCreate(1, sizeof(Button_HandleTypeDef));

	HAL_GPIO_WritePin(Pwr_Enable_U_GPIO_Port, Pwr_Enable_U_Pin, RESET);
	HAL_GPIO_WritePin(Pwr_Enable_V_GPIO_Port, Pwr_Enable_V_Pin, RESET);
	HAL_GPIO_WritePin(Pwr_Enable_W_GPIO_Port, Pwr_Enable_W_Pin, RESET);

	if(pdPASS==xTaskCreate(vTask_Break, "Break_Task", STACK_SIZE, (void *) &htim17, Break_Task_Priority, &xHandle_Break)){
		printf("Break_Task successfully created\r\n");
	}
	else{
		printf("Break_Task creation error\r\n");
	}

	if(pdPASS==xTaskCreate(vTask_Button, "Button_Task", STACK_SIZE, (void *) NULL, Button_Task_Priority, &xHandle_Button)){
		printf("Button_Task successfully created\r\n");
	}
	else{
		printf("Button_Task creation error\r\n");
	}

//	if(pdPASS==xTaskCreate(vTask_LCD, "LCD_Task", STACK_SIZE, (void *) &hi2c2, LCD_Task_Priority, &xHandle_LCD)){
//		printf("LCD_Task successfully created\r\n");
//	}
//	else{
//		printf("LCD_Task creation error\r\n");
//	}

	if(pdPASS==xTaskCreate(vTask_RotaryEnc, "RotEncorder_Task", STACK_SIZE, (void *) &htim3, RotaryEnc_Task_Priority, &xHandle_Rotary)){
		printf("RotEncorder_Task successfully created\r\n");
	}
	else{
		printf("RotEncorder_Task creation error\r\n");
	}

	if(pdPASS==xTaskCreate(vTask_LED, "LED_Task", STACK_SIZE, (void *) NULL, LED_Task_Priority, &xHandle_LED)){
		printf("LED_Task successfully created\r\n");
	}
	else{
		printf("LED_Task creation error\r\n");
	}

	if(pdPASS==xTaskCreate(vTask_TCN75A, "TCN75A_Task", STACK_SIZE, (void *) &hi2c2, TCN75A_Task_Priority, &xHandle_TCN75A)){
		printf("TCN75A_Task successfully created\r\n");
	}
	else{
		printf("TCN75A_Task creation error\r\n");
	}

	if(pdPASS==xTaskCreate(vTask_Fan, "Fan_Task", STACK_SIZE, (void *) &htim16, Fan_Task_Priority, &xHandle_Fan)){
		printf("Fan_Task successfully created\r\n");
	}
	else{
		printf("Fan_Task creation error\r\n");
	}



	printf("Starting Scheduler... \r\n");
	vTaskStartScheduler();
  /* USER CODE END 2 */

  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

	while (1)
	{

		//		LED_Write(led);
		//		led = (led*2)%15;
		//		HAL_Delay(100);
		//
		//		PwmBreak = (PwmBreak+8)%256;
		//		__HAL_TIM_SET_COMPARE(&htim17, TIM_CHANNEL_1, (PwmBreak>245) ? 255 : 0);
		//
		//
		//		HAL_ADC_Start(&hadc4);
		//		HAL_ADC_PollForConversion(&hadc4, HAL_MAX_DELAY);
		//		bus_voltage_raw = HAL_ADC_GetValue(&hadc4);
		//		bus_voltage = (bus_voltage_raw*(3.3*161)/(8*4096)-51)*2;
		//
		//		uartTxSize = snprintf(uartTxBuffer, UART_TX_BUFFER_SIZE, "Bus Voltage : 0x%4x, %2.2f V\r\n", bus_voltage_raw, bus_voltage);
		//		HAL_UART_Transmit(&huart3, uartTxBuffer, uartTxSize, HAL_MAX_DELAY);
		//		CDC_Transmit_FS(uartTxBuffer, uartTxSize);



    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV4;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
PUTCHAR_PROTOTYPE
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART1 and Loop until the end of transmission */
	HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xFFFF);

	return ch;
}
/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
