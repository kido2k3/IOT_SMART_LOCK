/*
 * my_fingerprintAS608.c
 *
 *  Created on: Dec 12, 2023
 *      Author: HP
 */

#include "my_fingerprintAS608.h"

#define CMD_HEADER		0xEF, 0x01, 0xff, 0xff, 0xff, 0xff
#define	INS_PACKET_FLAG	0x01
//----------instruction code----------
#define	INS_GET_IMAGE	0x01
#define INS_GEN_CHAR	0x02
#define INS_SEARCH		0x04
#define INS_REG_MODEL	0x05
#define INS_STORE_CHAR	0x06

#define	INS_VFY_PWD		0x13

//------------------------------------
#define	INS_LEN_NO_DATA	12
#define ACK_HEADER		{ 0xEF, 0x01, 0xff, 0xff, 0xff, 0xff,0x07, 0x00,0x03}
#define	ACK_PACKET_FLAG	0x07
#define	ACK_PACKET_LEN	0x03
#define	ACK_OK			0x00
#define ACK_LEN_12		12
#define ACK_LEN_16		16

#define IDX_INS_START	10
#define FINGER_TIMER	10 //10s

extern UART_HandleTypeDef huart1;
static bool receive_flag = 0;
static bool ins_search_flag = 0;
static uint8_t ins[20];
static uint8_t ins_len = 0;
static uint8_t from_sensor[20];
static uint8_t idx = 0;
static uint16_t idx_page = 0;
static uint16_t page_id = 0;
static uint16_t score = 0;
static uint8_t finger_timer = FINGER_TIMER;

static bool check_respone(void);
static bool check_respone_search(void);
static void build_ins(uint8_t code, uint8_t data_len, uint8_t *data);
static void send_ins(void);
static void get_finger(uint8_t time);
static bool merge_finger(void);
static void fp_reset_timer(void);
static bool store_finger(void);
static bool search_finger(void);

void fp_init(void) {
	uart_fp_init();
}

bool fp_search(void) {
	fp_reset_timer();
	get_finger(2);
	if (merge_finger()) {
		if (search_finger()) {
			return 1;
		}
	}
	return 0;
}
bool fp_enroll(void) {
	fp_reset_timer();
	get_finger(2);
	if (merge_finger()) {
		if (store_finger()) {
			return 1;
		}
	}
	return 0;
}
void fp_run_timer(void) {
	if (finger_timer > 0) {
		finger_timer--;
	}
}
static bool search_finger(void) {
	ins_search_flag = 1;
	uint8_t data[5] = { 0x01, 0x00, 0x00, 0x00, 0x63 };
	build_ins(INS_SEARCH, 5, data);
	send_ins();
	if (check_respone_search()) {
		ins_search_flag = 0;
		return 1;
	}
	ins_search_flag = 0;
	return 0;
}
static bool store_finger(void) {
	uint8_t data[3] = { 0x01, (uint8_t) (idx_page >> 8), (uint8_t) (idx_page) };
	build_ins(INS_STORE_CHAR, 3, data);
	send_ins();
	if (check_respone()) {
		idx_page++;
		return 1;
	}
	return 0;
}
static void fp_reset_timer(void) {
	finger_timer = FINGER_TIMER;
}
static bool merge_finger(void) {
	build_ins(INS_REG_MODEL, 0, 0);
	send_ins();
	if (check_respone()) {
		return 1;
	}
	return 0;
}
static void get_finger(uint8_t time) {
	for (uint8_t i = 0; i < time; i++) {
		fp_reset_timer();
		while (1) {
			build_ins(INS_GET_IMAGE, 0, 0);
			send_ins();
			if (check_respone()) {
				uint8_t data = i + 1;
				build_ins(INS_GEN_CHAR, 1, &data);
				send_ins();
				if (check_respone()) {
					break;
				}
			}
		}
	}
}

static bool check_respone_search(void) {
	while (!receive_flag) {
		if (finger_timer == 0) {
			idx = 0;
			return 0;
		}
	}
	receive_flag = !receive_flag;
	uint8_t header[9] = ACK_HEADER;
	header[8] = 0x07;
	if (memcmp(header, from_sensor, 9)) {
		idx = 0;
		return 0;
	}
	if (from_sensor[9] == 0x00) {
		idx = 0;
		page_id = (uint16_t) (from_sensor[10]) << 8 | from_sensor[11];
		score = (uint16_t) (from_sensor[12]) << 8 | from_sensor[13];
		return 1;
	}
	if (idx >= ACK_LEN_16) {
		idx = 0;
	}
	return 0;
}
static bool check_respone(void) {
	while (!receive_flag) {
		if (finger_timer == 0) {
			idx = 0;
			return 0;
		}
	}
	receive_flag = !receive_flag;
	uint8_t header[9] = ACK_HEADER;
	if (memcmp(header, from_sensor, 9)) {
		idx = 0;
		return 0;
	}
	if (from_sensor[9] == 0x00) {
		idx = 0;
		return 1;
	}
	if (idx >= ACK_LEN_12) {
		idx = 0;
	}
	return 0;
}
static void build_ins(uint8_t code, uint8_t data_len, uint8_t *data) {
	ins_len = INS_LEN_NO_DATA + data_len;
	uint16_t packet_len = data_len + 3;
	uint16_t sum = INS_PACKET_FLAG + code + packet_len;
	uint8_t header[IDX_INS_START] = { CMD_HEADER, INS_PACKET_FLAG,
			(uint8_t) (packet_len >> 8), (uint8_t) (packet_len), code };
	memcpy(ins, header, IDX_INS_START);
	uint8_t i = IDX_INS_START;
	for (; i < IDX_INS_START + data_len; i++) {
		ins[i] = data[i - IDX_INS_START];
		sum += data[i - IDX_INS_START];
	}
	ins[IDX_INS_START + data_len] = (uint8_t) (sum >> 8);
	ins[IDX_INS_START + data_len + 1] = (uint8_t) sum;
}

static void send_ins(void) {
	for (uint8_t i = 0; i < ins_len; i++) {
		HAL_UART_Transmit(&huart1, ins + i, 1, 100);
	}
}

void fp_receive_data(uint8_t data) {
	from_sensor[idx++] = data;
	uint8_t ack_len;
	if (ins_search_flag) {
		ack_len = ACK_LEN_16;
	} else {
		ack_len = ACK_LEN_12;
	}
	if (idx >= ack_len) {
		receive_flag = 1;
	}
}
#ifdef TEST_FINGERPRINT
extern UART_HandleTypeDef huart2;
char str[30];

void fp_test(void) {
	uint16_t len = sprintf((void*) str, "lay van tay\n");
	HAL_UART_Transmit(&huart2, (void*) str, len, 100);
	get_finger(5);
	len = sprintf((void*) str, "xong lay van tay\n");
	HAL_UART_Transmit(&huart2, (void*) str, len, 100);
	if (merge_finger()) {
		len = sprintf((void*) str, "van tay chuan\n");
		HAL_UART_Transmit(&huart2, (void*) str, len, 100);
//		if (search_finger()) {
//			len = sprintf((void*) str, "page id: %d; score: %d\n", page_id,
//					score);
//			HAL_UART_Transmit(&huart2, (void*) str, len, 100);
//		} else {
//			len = sprintf((void*) str, "cut, \n");
//			HAL_UART_Transmit(&huart2, (void*) str, len, 100);
//		}
		if (store_finger()) {
			len = sprintf((void*) str, "da luu\n");
			HAL_UART_Transmit(&huart2, (void*) str, len, 100);
		}
	}
	HAL_Delay(10);
}
#endif
