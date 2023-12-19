
#ifndef MY_LED
#define MY_LED
#include"my_define.h"

#ifdef __cplusplus
extern "C" {
#endif
void led_init(void);
void led_on(void);
void led_off(void); 
void led_flash_on(void); 
void led_flash_off(void);
#ifdef __cplusplus
} // extern "C"
#endif


#endif
