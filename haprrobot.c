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

/*! \def DBG_LEVEL
 *  \brief Sets level of debuging ouput.
 *  Makes everything easier to switch on and off what is output for debuging
 *  1- Basic
 *  2- Verbose
*/
#define DBG_LEVEL 1

#include "uart.h"
#include "sensors.h"
#include "motors.h"
#include "correctmotion.h"
#include "timer.h"
#include "environment.h"


// This is a file for your test functions
#include "tests.c"
/**
* @brief 0 short course goes straight on to dock 
*        1 is long course, bears right after left wall to find the right wall.
*/
int courseType;
/**
* Enables tools to override the next state
*/
int stateOverride = -1;
/**
* Enables interrupts to request the state machine to abort current operation
* and reevaluate transitions
*/
int abortMode = 0;
/**
 * Runs all the initialisations that are needed
 * Please put them in here.
 */
void initialise() {
  debug_frmwrk_init();
  setSensorSide(-1);
  trackingState = 0;
  timerCounter = 0;
  courseType = 0;
  initSerial();
  serialTest();
  initSensors();
  // Even tho this is a test it needs to run so that the serial is set up properly
  initTimers();
  //__enable_irq();
  if (DBG_LEVEL >= 1) {
	  _DBG_("MOUSE");
  }
 	mouseinitial();  
  if (DBG_LEVEL >= 1) {
	  _DBG_("I've completed"); 
	}

}

void doATest() {
  cmdDoPlay("cdefgab>c");
 // forwards(25);
 //followLine();
 /* while(1) {
    sensorsTest();
  }*/
 
 while(1) {
   trackByMouse();
   /*int i = 0;
   while (i < 3000000) {i++;}*/
 }
 
//  linefollowTest();    

 //motorCorrectTest();

// _DBG_("init mouse");
 //mouseinitial();
// forwardsfor50();
}

int doTheDemo() {

  cmdDoPlay(">cc");
  _DBG_("State 0");
  forwards(20);
  
  cmdDoPlay(">dd");
  _DBG_("State 1");
  while (sensorSide != 1) {
    //Forwards until we find a left wall
    checkForWall();
    _DBD(sensorSide);_DBG_(" sens");
  }
  
  cmdDoPlay(">ee");
  _DBG_("State 2");
  //Follow wall until it's ended
  int wallState = -1;
  while (wallState != 3 && wallState != 0) {
    wallState = checkForWall();
    correctForwardMotion();
  }
  
  //Bear right to head for other wall
  cmdDoPlay(">ff");
  _DBG_("State 3");
  right();
  delay(2000);
  _DBG_("State 3.1");
  forwards(20);
  
  //Wait until right wall is trackable
  while (sensorSide != 0) {
    checkForWall();
  }
  
  //Track right wall
  cmdDoPlay(">gg");
  _DBG_("State 4");
  while (checkForWall() != 4) {
    correctForwardMotion();
    delay(10);
  }
}

void main(void) {
  initialise();
  _DBG_("Magic!");
  
  doTheDemo();
  
  _DBG_("Done");
}
