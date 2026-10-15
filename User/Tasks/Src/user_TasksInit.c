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
//#include "user_KeyTask.h"
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

/* Message queues ------------------------------------------------------------*/
osEventFlagsId_t HardIntEventHandle;

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
    if (HardIntEventHandle == NULL)
    {
        Error_Handler();
    }
	
	/* add threads, ... */
	HardwareInitTaskHandle  = osThreadNew(HardwareInitTask, NULL, &HardwareInitTask_attributes);
    if (HardwareInitTaskHandle == NULL)
    {
        Error_Handler();
    }
	
	/* add events, ... */


	/* add  others ... */
	
}
