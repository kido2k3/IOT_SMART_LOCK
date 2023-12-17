
#ifndef MY_S_TIMER
#define MY_S_TIMER
#include"my_define.h"

#ifdef __cplusplus
extern "C" {
#endif
extern bool timer_flag;
extern portMUX_TYPE timerMux;
void timer_set(uint16_t time);
void timer_init1(void);
#ifdef __cplusplus
} // extern "C"
#endif


#endif
