/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "OLED.h"
#include "usart.h"
#include <string.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for LEDTask */
osThreadId_t LEDTaskHandle;
const osThreadAttr_t LEDTask_attributes = {
  .name = "LEDTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for UARTTask */
osThreadId_t UARTTaskHandle;
const osThreadAttr_t UARTTask_attributes = {
  .name = "UARTTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for OLEDTask */
osThreadId_t OLEDTaskHandle;
const osThreadAttr_t OLEDTask_attributes = {
  .name = "OLEDTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void EntryLEDTask(void *argument);
void EntryUARTTask(void *argument);
void EntryOLEDTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void configureTimerForRunTimeStats(void);
unsigned long getRunTimeCounterValue(void);

/* USER CODE BEGIN 1 */
/* Functions needed when configGENERATE_RUN_TIME_STATS is on */
void configureTimerForRunTimeStats(void) {
  /* 1. 使能 TRC (Trace) 模块 */
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  /* 2. 重置 DWT 周期计数器 */
  DWT->CYCCNT = 0;
  /* 3. 使能 DWT 周期计数器 */
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

unsigned long getRunTimeCounterValue(void) {
  return DWT->CYCCNT; 
}
/* USER CODE END 1 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of LEDTask */
  LEDTaskHandle = osThreadNew(EntryLEDTask, NULL, &LEDTask_attributes);

  /* creation of UARTTask */
  UARTTaskHandle = osThreadNew(EntryUARTTask, NULL, &UARTTask_attributes);

  /* creation of OLEDTask */
  OLEDTaskHandle = osThreadNew(EntryOLEDTask, NULL, &OLEDTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_EntryLEDTask */
/**
 * @brief  Function implementing the LEDTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_EntryLEDTask */
void EntryLEDTask(void *argument)
{
  /* USER CODE BEGIN EntryLEDTask */
  /* Infinite loop */
  for (;;) {
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
    osDelay(1000);
  }
  /* USER CODE END EntryLEDTask */
}

/* USER CODE BEGIN Header_EntryUARTTask */
/**
 * @brief Function implementing the UARTTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_EntryUARTTask */
void EntryUARTTask(void *argument)
{
  /* USER CODE BEGIN EntryUARTTask */
  char *str = "UART Sending...\r\n";
  /* Infinite loop */
  for (;;) {
    HAL_UART_Transmit(&huart1, (uint8_t *)str, strlen(str), HAL_MAX_DELAY);
    osDelay(2000);
  }
  /* USER CODE END EntryUARTTask */
}

/* USER CODE BEGIN Header_EntryOLEDTask */
/**
 * @brief Function implementing the OLEDTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_EntryOLEDTask */
void EntryOLEDTask(void *argument)
{
  /* USER CODE BEGIN EntryOLEDTask */
  uint16_t data = 0;
  OLED_Init();
  OLED_ShowString(1, 1, "data:");
  /* Infinite loop */
  for (;;) {
    OLED_ShowHexNum(1, 7, data, 4);
    OLED_ShowString(2, 1, "OLED Refreshing");
    osDelay(250);
    OLED_ShowString(2, 1, "                ");
    osDelay(250);
    data++;
  }
  /* USER CODE END EntryOLEDTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

