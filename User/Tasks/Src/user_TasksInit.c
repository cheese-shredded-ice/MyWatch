/* Private includes -----------------------------------------------------------*/
//includes
#include "user_TasksInit.h"
//sys
#include "sys.h"
#include "main.h"
#include "stdio.h"
#include "lcd.h"
//#include "WDOG.h"
//gui
//#include "lvgl.h"
//#include "ui_TimerPage.h"
//tasks
#include "user_HardwareInitTask.h"
//#include "user_RunModeTasks.h"
#include "user_KeyTask.h"
#include "user_DisplayTask.h"
//#include "user_ScrRenewTask.h"
//#include "user_SensUpdateTask.h"
//#include "user_ChargCheckTask.h"
//#include "user_MessageSendTask.h"
//#include "user_DataSaveTask.h"

/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/


/* Tasks ---------------------------------------------------------------------*/
//Hardwars initialization
osThreadId_t HardwareInitTaskHandle;
const osThreadAttr_t HardwareInitTask_attributes = {
  .name = "HardwareInitTask",
  .stack_size = 128 * 10,
  .priority = (osPriority_t) osPriorityHigh3,
};

//Key task
osThreadId_t KeyTaskHandle;
const osThreadAttr_t KeyTask_attributes = {
  .name = "KeyTask",
  .stack_size = 128 * 1,
  .priority = (osPriority_t) osPriorityNormal,
};

//Display task
osThreadId_t DisplayTaskHandle;
const osThreadAttr_t DisplayTask_attributes = {
    .name = "DisplayTask",
    .stack_size = 128 * 2,
    .priority = (osPriority_t)osPriorityNormal1,
};

/* Message queues ------------------------------------------------------------*/
osEventFlagsId_t HardIntEventHandle;
osMessageQueueId_t Key_MessageQueue;

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void User_Tasks_Init(void)
{
	/* add mutexes, ... */

	/* add semaphores, ... */

	/* start timers, add new ones, ... */

	/* add queues, ... */
	HardIntEventHandle = osEventFlagsNew(NULL);
	Key_MessageQueue = osMessageQueueNew(4, sizeof(uint8_t), NULL);
    if (HardIntEventHandle == NULL)
    {
        Error_Handler();
    }
	
	/* add threads, ... */
	HardwareInitTaskHandle  = 	osThreadNew(HardwareInitTask, NULL, &HardwareInitTask_attributes);
	KeyTaskHandle 			= 	osThreadNew(KeyTask, NULL, &KeyTask_attributes);
	DisplayTaskHandle		=	osThreadNew(DisplayTask, NULL, &DisplayTask_attributes);
    if (HardwareInitTaskHandle == NULL)
    {
        Error_Handler();
    }
	
	/* add events, ... */


	/* add  others ... */
	
}
