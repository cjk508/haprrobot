//#include "lpc17xx_uart.h"		// Central include files
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

#include "uart.h"
#include "sensors.h"
#include "motors.h"

uint8_t sig;

void serialTest() {
  _DBG_("Init Serial");
  initSerial(); 
  char buf[6];
  cmdSig(buf);
  _DBG_((char*)buf);
}

void sensorsTest() {
  initialiseSensors();
}

void motorTest() {
  cmdLeftMFw(25);
}

void main(void) {
  debug_frmwrk_init();
  _DBG_("Magic!");

  motorTest();

  _DBG_("Done");

 // serialTest();
  
 // sensorsTest();
}
