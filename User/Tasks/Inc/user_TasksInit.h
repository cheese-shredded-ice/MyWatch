#ifndef __USER_TASKSINIT_H__
#define __USER_TASKSINIT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "FreeRTOS.h"
#include "cmsis_os.h"

#define SCRRENEW_DEPTH	5
#define HARDINT_EVENT_UART  (1U << 0)
#define HARDINT_EVENT_CHARG (1U << 1)
#define HARDINT_EVENT_MPU   (1U << 2)

extern osEventFlagsId_t HardIntEventHandle;
extern osMessageQueueId_t Key_MessageQueue;

void User_Tasks_Init(void);

#ifdef __cplusplus
}
#endif

#endif

