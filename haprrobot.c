// Central include files
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

// DBG Levels
// 1 - Basic
// 2 - Verbose
#define DBG_LEVEL 1

#include "uart.h"
#include "sensors.h"
#include "motors.h"

uint8_t sig;

void serialTest() {
  if (DBG_LEVEL >= 1) _DBG_("Init Serial");
  initSerial(); 
  unsigned char buf[6];
  cmdSig(buf);
  _DBG_((char*)buf);
}

void sensorsTest() {
  initSensors();
}

void motorTest() {
  setMotors(25, -25);
}

void main(void) {
  debug_frmwrk_init();
  _DBG_("Magic!");

  //serialTest();

 // motorTest();

  //_DBG_("Done");

  
  sensorsTest();
}
