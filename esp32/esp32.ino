#include "my_define.h"
#include "my_led.h"
#include"my_stimer.h"
/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

AdafruitIO_Feed *digital = io.feed("test");
int LED_STATE = LOW;
uint8_t counter = 100;


void setup() {
  // put your setup code here, to run once:
  pinMode(DEBUG_LED, OUTPUT);
  pinMode(FLASH_LED, OUTPUT);
  timer_init1();

  led_off();
  led_flash_on();
  Serial.begin (115200);
  // connect to io.adafruit.com
  io.connect();
  // set up a message handler for the count feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  digital->onMessage(handleMessage);
  // wait for a connection
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  digital->get();
  led_flash_off();
}

uint8_t buf_uart[20];
uint8_t idx = 0;
void get_data(uint8_t msg) {
  buf_uart[idx++] = msg;
}
float handle_data() {
  if (idx > 19) {
    idx = 0;
    return 0;
  }
  if (buf_uart[idx - 1] == '#' && strstr((char*)buf_uart, "!TEMP:")) {
    idx = 0;
    return atof((char*)(buf_uart + 6));
  }
  return 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  // to do
    // io.run(); is required for all sketches.
    // it should always be present at the top of your loop
    // function. it keeps the client connected to
    // io.adafruit.com, and processes any incoming data.
    io.run();
  portENTER_CRITICAL_ISR(&timerMux);
  if (!timer_flag) {
    if (counter > 0) {
      counter--;
    }
    timer_set(10);
  }
  portEXIT_CRITICAL_ISR(&timerMux);
  if (!counter) {
    LED_STATE = !LED_STATE;
    if (LED_STATE) {
      led_on();
    } else {
      led_off();
    }
    counter = 100;
  }
}
void handleMessage(AdafruitIO_Data *data) {
  
}
