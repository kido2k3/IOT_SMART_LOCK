#ifndef MY_UART
#define MY_UART

#include "my_define.h"

#ifdef __cplusplus
extern "C"
{
#endif
void get_data(uint8_t msg);
uint8_t compile_cmd(uint32_t *cmd_data);
#ifdef __cplusplus
} // extern "C"
#endif
#endif
