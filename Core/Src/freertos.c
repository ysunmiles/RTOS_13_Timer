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
/* Definitions for TaskSwTmr1 */
osThreadId_t TaskSwTmr1Handle;
const osThreadAttr_t TaskSwTmr1_attributes = {
  .name = "TaskSwTmr1",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityRealtime,
};
/* Definitions for TaskSwTmr2 */
osThreadId_t TaskSwTmr2Handle;
const osThreadAttr_t TaskSwTmr2_attributes = {
  .name = "TaskSwTmr2",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for TaskTIM1 */
osThreadId_t TaskTIM1Handle;
const osThreadAttr_t TaskTIM1_attributes = {
  .name = "TaskTIM1",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for TaskTIM2 */
osThreadId_t TaskTIM2Handle;
const osThreadAttr_t TaskTIM2_attributes = {
  .name = "TaskTIM2",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for SwTmr1 */
osTimerId_t SwTmr1Handle;
const osTimerAttr_t SwTmr1_attributes = {
  .name = "SwTmr1"
};
/* Definitions for SwTmr2 */
osTimerId_t SwTmr2Handle;
const osTimerAttr_t SwTmr2_attributes = {
  .name = "SwTmr2"
};
/* Definitions for SwTmr2Mutex */
osMutexId_t SwTmr2MutexHandle;
const osMutexAttr_t SwTmr2Mutex_attributes = {
  .name = "SwTmr2Mutex"
};
/* Definitions for TIM2Smph */
osSemaphoreId_t TIM2SmphHandle;
const osSemaphoreAttr_t TIM2Smph_attributes = {
  .name = "TIM2Smph"
};
/* Definitions for TIM1EvtFlag */
osEventFlagsId_t TIM1EvtFlagHandle;
const osEventFlagsAttr_t TIM1EvtFlag_attributes = {
  .name = "TIM1EvtFlag"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartTaskSwTmr1(void *argument);
void StartTaskSwTmr2(void *argument);
void StartTaskTIM1(void *argument);
void StartTaskTIM2(void *argument);
void SwTmr1Callback(void *argument);
void SwTmr2Callback(void *argument);

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
  /* Create the mutex(es) */
  /* creation of SwTmr2Mutex */
  SwTmr2MutexHandle = osMutexNew(&SwTmr2Mutex_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of TIM2Smph */
  TIM2SmphHandle = osSemaphoreNew(1, 0, &TIM2Smph_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* creation of SwTmr1 */
  SwTmr1Handle = osTimerNew(SwTmr1Callback, osTimerOnce, NULL, &SwTmr1_attributes);

  /* creation of SwTmr2 */
  SwTmr2Handle = osTimerNew(SwTmr2Callback, osTimerPeriodic, NULL, &SwTmr2_attributes);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of TaskSwTmr1 */
  TaskSwTmr1Handle = osThreadNew(StartTaskSwTmr1, NULL, &TaskSwTmr1_attributes);

  /* creation of TaskSwTmr2 */
  TaskSwTmr2Handle = osThreadNew(StartTaskSwTmr2, NULL, &TaskSwTmr2_attributes);

  /* creation of TaskTIM1 */
  TaskTIM1Handle = osThreadNew(StartTaskTIM1, NULL, &TaskTIM1_attributes);

  /* creation of TaskTIM2 */
  TaskTIM2Handle = osThreadNew(StartTaskTIM2, NULL, &TaskTIM2_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* creation of TIM1EvtFlag */
  TIM1EvtFlagHandle = osEventFlagsNew(&TIM1EvtFlag_attributes);

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartTaskSwTmr1 */
/**
  * @brief  Function implementing the TaskSwTmr1 thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartTaskSwTmr1 */
void StartTaskSwTmr1(void *argument)
{
  /* USER CODE BEGIN StartTaskSwTmr1 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartTaskSwTmr1 */
}

/* USER CODE BEGIN Header_StartTaskSwTmr2 */
/**
* @brief Function implementing the TaskSwTmr2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskSwTmr2 */
void StartTaskSwTmr2(void *argument)
{
  /* USER CODE BEGIN StartTaskSwTmr2 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartTaskSwTmr2 */
}

/* USER CODE BEGIN Header_StartTaskTIM1 */
/**
* @brief Function implementing the TaskTIM1 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskTIM1 */
void StartTaskTIM1(void *argument)
{
  /* USER CODE BEGIN StartTaskTIM1 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartTaskTIM1 */
}

/* USER CODE BEGIN Header_StartTaskTIM2 */
/**
* @brief Function implementing the TaskTIM2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskTIM2 */
void StartTaskTIM2(void *argument)
{
  /* USER CODE BEGIN StartTaskTIM2 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartTaskTIM2 */
}

/* SwTmr1Callback function */
void SwTmr1Callback(void *argument)
{
  /* USER CODE BEGIN SwTmr1Callback */

  /* USER CODE END SwTmr1Callback */
}

/* SwTmr2Callback function */
void SwTmr2Callback(void *argument)
{
  /* USER CODE BEGIN SwTmr2Callback */

  /* USER CODE END SwTmr2Callback */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

