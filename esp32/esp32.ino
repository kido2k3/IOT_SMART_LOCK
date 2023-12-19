#include "my_define.h"
#include "my_led.h"
#include"my_stimer.h"
#include"my_uart.h"
/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"
//
AdafruitIO_Feed *lock = io.feed("lock");
AdafruitIO_Feed *sleep_period = io.feed("sleep-period");
AdafruitIO_Feed *people = io.feed("people");
AdafruitIO_Feed *fingerprint_id = io.feed("fingerprint-id");
int LED_STATE = LOW;
uint8_t counter = 100;


void setup() {
  // put your setup code here, to run once:
  led_init();
  //timer_init1();

  led_off();
  //--------------START CONNECTION------------------------------
  led_flash_on();
  Serial.begin (115200);
  // connect to io.adafruit.com
  io.connect();
  // set up a message handler for the count feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  lock->onMessage(handleMessage);
  // wait for a connection
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  lock->get();
  led_flash_off();
  //--------------END CONNECTION------------------------------
}



void loop() {
  // put your main code here, to run repeatedly:
  // to do
  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  if (Serial.available()) {
    uint8_t msg = Serial.read();
    Serial.println((char)msg);
    get_data(msg);
  }
  uint32_t cmd_data;
  uint8_t cmd =  compile_cmd(&cmd_data);
  //  portENTER_CRITICAL_ISR(&timerMux);
  //  if (!timer_flag) {
  //    //todo
  //    handle_cmd( cmd,  cmd_data);
  //
  //    if (counter > 0) {
  //      counter--;
  //    }
  //    timer_set(10);
  //  }
  //  portEXIT_CRITICAL_ISR(&timerMux);
  handle_cmd( cmd,  cmd_data);
  if (!counter) {
    LED_STATE = !LED_STATE;
    if (LED_STATE) {
      led_on();
    } else {
      led_off();
    }
    counter = 100;
  }
  if (counter > 0) {
    counter--;
  }
  delay(10);
}
/*0: bad cmd
  1: turn led flash on
  2: turn led flash off
  3: send the state of lock to server
  4: send the amount of sleep period to server
  5: send the number of people to server
  6: send the fingerprint id that has just entered to server
*/
void handle_cmd(uint8_t cmd, uint8_t cmd_data) {
  switch (cmd) {
    case 1:
      led_flash_on();
      break;
    case 2:
      led_flash_off();
      break;
    case 3:
      lock->save(cmd_data);
      break;
    case 4:
      sleep_period->save(cmd_data);
      break;
    case 5:
      people->save(cmd_data);
      break;
    case 6:
      fingerprint_id->save(cmd_data);
      break;

    default:
      break;
  }
}
void handleMessage(AdafruitIO_Data *data) {
  if (data->toPinLevel() == 0) {
    if (Serial.availableForWrite())
      Serial.write("LOCK:0#");
  }
}
