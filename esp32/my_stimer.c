#include "my_stimer.h"

#define FREQ 1000

volatile uint8_t timer_cnt = 0; // for counting interrupt
bool timer_flag = 0;
hw_timer_t *timer = NULL; // H/W timer defining (Pointer to the Structure)
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

static void IRAM_ATTR timer_run(void);
void timer_set(uint16_t time)
{
    timer_cnt = time * FREQ / 1000;
    timer_flag = 1;
}
void timer_init1(void)
{
    timer_set(10);
    timer = timerBegin(0, 80, true);               // timer 0, prescalar: 80, UP counting
    timerAttachInterrupt(timer, &timer_run, true); // Attach interrupt
    timerAlarmWrite(timer, 1000, true);            // Match value= 1000000 for 1 sec. delay.
    timerAlarmEnable(timer);                       // Enable Timer with interrupt (Alarm Enable)
}

static void IRAM_ATTR timer_run(void)
{ // Defining Inerrupt function with IRAM_ATTR for faster access
    portENTER_CRITICAL_ISR(&timerMux);
    if (timer_cnt > 0)
    {
        timer_cnt--;
        if (timer_cnt == 0)
        {
            timer_flag = 0;
        }
    }
    portEXIT_CRITICAL_ISR(&timerMux);
}
