

#include "my_led.h"

void led_on(void)
{
    digitalWrite(DEBUG_LED, 0);
}
void led_off(void)
{
    digitalWrite(DEBUG_LED, 1);
}

void led_flash_on(void){
  digitalWrite(FLASH_LED, 1);
}
void led_flash_off(void){
  digitalWrite(FLASH_LED, 0);
}
