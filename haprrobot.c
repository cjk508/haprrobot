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
  //initSensors();
  // Even tho this is a test it needs to run so that the serial is set up properly
  serialTest(); 
  //initTimers();
  //mouseinitial();  
	_DBG_("I've completed"); 

}

void delay(int time) {
  int i = getLotsOfBlackTape();
  while (i - getLotsOfBlackTape() == time) {
  }
}


void doATest() {
  cmdDoPlay("abcdefg>a");
  
//  lineMotors();
//  while(1) {
//    sensorsTest();
//  }
  
//  linefollowTest();    

//  motorCorrectTest();

//  _DBG_("init mouse");
 // mouseinitial();
}



void trackMovement(int distance) {
  // @todo Take current value
  
  // Start moving
  forwards(20);
  
  // @todo Take value & check against distance
  
}

void findAWall() {
  // @todo needs to be able to deal with not being near the wall
  // @todo needs to recognise that the wall might be directly in front.
}

void followWall() {
  // @todo correct motion allong wall until no more wall then get out! 
}

void updateMouse() {
  // @todo should take in location values
  // @todo move into mouse.c
  // @todo set location values because we know where we are
}

void findALine() {
  // @todo move to line follow
  // @todo implement this
}

void followToDock() {
  // @todo use functions from line following, lineFollow() until dock.
}

void doTheDemo() {
  // wait for initialisation
  delay(100);
  
  // Track distance
  trackMovement(200);
  
  findAWall();
  
  updateMouse();
  
  followWall();
  
  updateMouse();
  
  int dist = 0;
  
  // dist is based on where we are from the wall, and how far we need to go to the next wall. total is 2m dist should be less.
  trackMovement(dist);
  
  findAWall();
  
  followWall();
  
  updateMouse();
  
  trackMovement(100); // @todo check this value
  
  findALine();
  
  followToDock();
}

void main(void) {
  initialise();
  _DBG_("Magic!");
  
  doATest();
  
  _DBG_("Done");
}














