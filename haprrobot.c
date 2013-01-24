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

uint8_t sig;

void serialTest() {
  initSerial();
  char buf[6];
//  _DBG_(buf);
  sig = 0x81;
  serialSend(&sig,1);
  serialRecv(&buf,6);
  _DBG_(buf);
}

void music() {
  sig = 0xB3;
  serialSend(&sig,1);
  _DBG_("Sent Play");
  /*
  uint8_t buf[16] = {'c','d','e','f','g','a','b','>','c','b','a','g','f','e','d','c'};
  sig = sizeof(buf);
  serialSend(&sig,4);
  _DBG_("Sent Length");
  serialSend(&buf,sizeof(buf));
  _DBG_("Sent Music");
  */
  sig = 4;
  serialSend(&sig,1);
  _DBG_("Sent Length");
  sig = 'c';
  serialSend(&sig,1);
  _DBG_("Sent C");
}

void moveStop() {
  sig = 0xC1;
  serialSend(&sig,1);
  sig = 0x0A;
  serialSend(&sig,1);
}

void sensorsTest() {
  initialiseSensors();
	_DBG_("Sensors Initialised");
}

void main(void) {
  debug_frmwrk_init();
  _DBG_("Magic!");
  serialTest();
//  _DBG_("Music Start");
//  music();
//  _DBG_("Music Stop");
  moveStop();
  
}
