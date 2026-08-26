#include "cmsis_os.h"
#include "main.h"
#include "cmsis_os2.h"
#include "FreeRTOS.h"

#include "task.h"
#include "OLED.h"
#include "tim.h"

#define SwTmr1Period 500
#define SwTmr2Period 1000
#define TIM1Period 2000
#define TIM2Period 5000

void StartTaskSwTmr1(void *argument)
{
    OLED_Init();
    osTimerStart(SwTmr1Handle, SwTmr1Period);
    for (;;)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        OLED_ShowString(1, 1, "SwTmr 1 running.");
        osDelay(SwTmr1Period/2);
        OLED_ShowString(1, 1, "                ");
    }
}
void SwTmr1Callback(void *argument)
{
    xTaskNotifyGive(TaskSwTmr1Handle);
    osTimerStart(SwTmr1Handle, SwTmr1Period);
}

void StartTaskSwTmr2(void *argument)
{
    osTimerStart(SwTmr2Handle, SwTmr2Period);
    for (;;)
    {
        uint8_t temp;
        osMessageQueueGet(SwTmr2QueueHandle, &temp, 0, osWaitForever);
        OLED_ShowString(2, 1, "SwTmr 2 running.");
        osDelay(SwTmr2Period/2);
        OLED_ShowString(2, 1, "                ");
    }
}
void SwTmr2Callback(void *argument)
{
    uint8_t temp = 1;
    osMessageQueuePut(SwTmr2QueueHandle, &temp, 0, 0);
}

void StartTaskTIM1(void *argument)
{
    HAL_TIM_Base_Start_IT(&htim1);
    for (;;)
    {
        osEventFlagsWait(TIM1EvtFlagHandle, 0x01, osFlagsWaitAll, osWaitForever);
        OLED_ShowString(3, 1, "TIM 1 running.");
        osDelay(TIM1Period/2);
        OLED_ShowString(3, 1, "                ");
    }
}

void StartTaskTIM2(void *argument)
{
    HAL_TIM_Base_Start_IT(&htim2);
    for (;;)
    {
        osSemaphoreAcquire(TIM2SmphHandle, osWaitForever);
        OLED_ShowString(4, 1, "TIM 2 running.");
        osDelay(TIM2Period/2);
        OLED_ShowString(4, 1, "                ");
    }
}