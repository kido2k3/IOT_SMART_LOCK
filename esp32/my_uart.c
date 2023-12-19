

#include "my_uart.h"
#define BUFFER_MAX_SIZE 20
#define LED_ON_CMD      "LED:1"
#define LED_OFF_CMD     "LED:0"
#define LOCK_CMD        "LOCK:"
#define SLEEP_CMD       "SLP:"
#define PEOPLE_CMD      "PEO:"
#define FP_ID_CMD       "ID:"
uint8_t buf_uart[BUFFER_MAX_SIZE];
uint8_t idx = 0;
bool done_receive = 0;
void get_data(uint8_t msg) {
  buf_uart[idx++] = msg;
  if(buf_uart[idx - 1] == '#'){
    done_receive = 1;
    idx = 0;
  }
  if (idx > BUFFER_MAX_SIZE - 1) {
    idx = 0;
  }
}
/*0: bad cmd
  1: turn led on
  2: turn led off
  3: send the state of lock to server
  4: send the amount of sleep period to server
  5: send the number of people to server
  6: send the fingerprint id that has just entered to server
*/


uint8_t compile_cmd(uint32_t *cmd_data) {
  if (done_receive) {
    done_receive = 0;
    if(strstr((char*)buf_uart, LED_ON_CMD)){
      return 1;
    }
    else if(strstr((char*)buf_uart, LED_OFF_CMD)){
      return 2;
    }
    else if(strstr((char*)buf_uart, LOCK_CMD)){
      *cmd_data = buf_uart[5]-'0';
      return 3;
    }
    else if(strstr((char*)buf_uart, SLEEP_CMD)){
      *cmd_data = strtoul(buf_uart + strlen(SLEEP_CMD),0,10);
      return 4;
    }
    else if(strstr((char*)buf_uart, PEOPLE_CMD)){
      *cmd_data = strtoul(buf_uart + strlen(PEOPLE_CMD),0,10);
      return 5;
    }
    else if(strstr((char*)buf_uart, FP_ID_CMD)){
      *cmd_data = strtoul(buf_uart + strlen(FP_ID_CMD),0,10);
      return 6;
    }
  }
  return 0;
}
