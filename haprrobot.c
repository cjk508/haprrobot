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
#include "correctmotion.h"
#include "timer.h"

// This is a file for your test functions
#include "tests.c"


/**
 * Runs all the initialisations that are needed
 * Please put them in here.
 */
void initialise() {
  initSerial();
  initSensors();
  
}



void main(void) {
  debug_frmwrk_init();
  _DBG_("Magic!");
  initialise();
  
	serialTest();

  //motorCorrectTest();


  
  _DBG_("Done");
}
