/* Private includes -----------------------------------------------------------*/

// includes
// sys
//#include "usart.h"
#include "tim.h"
#include "stm32f4xx_it.h"
#include "spi.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"

// user
#include "user_HardwareInitTask.h"
//#include "HWDataAccess.h"
//#include "version.h"

// bsp
#include "key.h"
#include "lcd.h"
#include "lcd_init.h"
//#include "CST816.h"
//include "DataSave.h"

// ui
//gui
//#include "lvgl.h"
//#include "lv_port_disp.h"
//#include "lv_port_indev.h"
//#include "ui.h"

// APP SYS setting
//#include "ui_DateTimeSetPage.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/**
  * @brief  hardwares init task
  * @param  argument: Not used
  * @retval None
  */
/* Debug watch: 0=not entered, 1=entered, 2=backlight started,
 * 3=SPI configured, 4=LCD initialized, 5=filled, 6=text sent.
 * Inspect this value with the program halted after allowing it to run.
 */
volatile uint32_t lcd_test_stage = 0;

void HardwareInitTask(void *argument)
{
    (void)argument;
    lcd_test_stage = 1;

    /* TIM3_CH3 drives PB0 (LCD backlight). The generated PWM pulse is 0,
       so set a non-zero compare value before starting the channel. */
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, PWM_PERIOD);
    if (HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3) != HAL_OK)
    {
        lcd_test_stage = 0xE1;
        Error_Handler();
    }
    lcd_test_stage = 2;

    /* Start with a conservative SPI clock while diagnosing the panel. */
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
    if (HAL_SPI_Init(&hspi1) != HAL_OK)
    {
        lcd_test_stage = 0xE2;
        Error_Handler();
    }
    lcd_test_stage = 3;

    LCD_Init();
	Key_Port_Init();
    lcd_test_stage = 4;

    LCD_Fill(0, 0, LCD_W, LCD_H, BLUE);
    lcd_test_stage = 5;

    LCD_ShowString(90, 120, (const uint8_t *)"Hello",
                   WHITE, BLUE, 24, 0);
    lcd_test_stage = 6;

    /* Set the intended brightness after the panel has been initialized. */
    LCD_Set_Light(50);
    lcd_test_stage = 7;

    osThreadExit();
}
