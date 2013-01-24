#include "lpc17xx_uart.h"		// Central include files
#include "debug_frmwrk.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_nvic.h"
#include "lpc17xx_timer.h"
#include "lpc_types.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_i2c.h"
#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_dac.h"

#include "lpc17xx.h"

#include "uart.c"
#include "sensors.c"

uint8_t sig = 0x81;

void serialTest() {
  initSerial();
  char buf[6];
  _DBG_(buf);

  serialSend(&sig,4);
  serialRecv(&buf,6);

  _DBG_(buf);
}

void sensorsTest() {
  initialiseSensors();
}

void main(void) {
  debug_frmwrk_init();
  _DBG_("Magic!");
  
  serialTest();
 // sensorsTest();
}
