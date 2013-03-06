/*********************************************************//**
*	@file haprrobot.c
*	@brief	Main file that intialises the sensors and uart. Then allows testing and the main files to run
*
*	@version V1.0
*	@author Andrew Durant
*	@author Christopher King
*	@author Jed Warwick-Mooney
*	@author Lloyd Wallis
*
*	@date 03 March 2013
*
*/							     

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
  debug_frmwrk_init();
  initSerial();
//  initSensors();
  // Even tho this is a test it needs to run so that the serial is set up properly
  serialTest();
  initTimers();  
}

void main(void) {
  initialise();
  _DBG_("Magic!");
  //cmdDoPlay("abcdefg>a");
  linefollowTest();    
//  while(1) {
//    sensorsTest();
//  }
//  motorCorrectTest();

//  _DBG_("init mouse");
 // mouseinitial(); 

  _DBG_("Done");
}
