#include "user_DisplayTask.h"
#include "user_TasksInit.h"
#include "cmsis_os.h"
#include "lcd.h"
#include "lcd_init.h"

void DisplayTask(void *argument)
{
    uint8_t key;
	(void)argument;
    for (;;)
    {
        if (osMessageQueueGet(Key_MessageQueue,
                              &key,
                              NULL,
                              osWaitForever) == osOK)
        {
            LCD_Fill(0, 0, LCD_W, LCD_H, RED);

            if (key == 1)
            {
                LCD_ShowString(72, 120,
                               (const uint8_t *)"KEY1",
                               WHITE, RED, 24, 0);
            }
            else if (key == 2)
            {
                LCD_ShowString(72, 120,
                               (const uint8_t *)"KEY2",
                               WHITE, RED, 24, 0);
            }
        }
    }
}