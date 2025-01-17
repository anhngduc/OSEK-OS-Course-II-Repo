/**
 * @file AlarmManagementCodingExerciseStarter.c
 * @author Sarea Alhariri (Sarea.h95@outlook.com)
 * @brief  Alarm Managment coding exercise starter file
 * @version 0.1
 * @date 2020-10-23
 *
 * @copyright Sarea Alhariri - All rights reserved
 *
 */

#include "os.h"
#include "switch.h"

volatile static bool g_PwmSignal = 0u;

static uint8_t PwmWidth = 0U;
static int8_t temp = 1;

DeclareTask(AppTask_PulseWidthUpdate)
DeclareTask(AppTask_PwmOn)

void SystemInit(void) {}
int main(void)
{
  StartOS();
  while (1)
    ; /* Should not be executed */
  return 0;
}

TASK(AppTask_PulseWidthUpdate)
{
  if (PwmWidth + temp >= 10)
  {
    temp = -1;
  }
  else if (PwmWidth + temp <= 0)
  {
    temp = 1;
  }
  PwmWidth += temp;
  TerminateTask();
}

TASK(AppTask_PwmOn)
{
  g_PwmSignal = 1u;
	SetRelAlarm(Alrm_PwmOff, PwmWidth, 0); 
  TerminateTask();
}

ALARMCALLBACK(PwmOff)
{
  g_PwmSignal = 0u;
}
