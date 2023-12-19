/*
 * my_fingerprintAS608.h
 *
 *  Created on: Dec 12, 2023
 *      Author: HP
 */

#ifndef INC_MY_FINGERPRINTAS608_H_
#define INC_MY_FINGERPRINTAS608_H_

#include"my_define.h"
#include "my_uart.h"
#ifdef TEST_FINGERPRINT
void fp_test(void);
#endif
void fp_init(void);
void fp_receive_data(uint8_t data);
void fp_run_timer(void);
bool fp_enroll(void);
bool fp_search(void);
uint16_t fg_get_id(void);
#endif /* INC_MY_FINGERPRINTAS608_H_ */
