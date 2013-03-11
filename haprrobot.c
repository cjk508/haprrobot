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
#include "environment.h"

// This is a file for your test functions
#include "tests.c"
/**
* @brief 0 short course goes straight on to dock 
*        1 is long course, bears right after left wall to find the right wall.
*/
int courseType;
/**
 * Runs all the initialisations that are needed
 * Please put them in here.
 */
void initialise() {
  debug_frmwrk_init();
  trackingState = 0;
  courseType = 0;
  initSerial();
  serialTest();
  initSensors();
  // Even tho this is a test it needs to run so that the serial is set up properly
  //initTimers();
  __enable_irq();
  //mouseinitial();  
	_DBG_("I've completed"); 

}

void doATest() {
  //cmdDoPlay("abcdefg>a");
 // forwards(25);
 //followLine();
 /* while(1) {
    sensorsTest();
  }*/
 
//  linefollowTest();    

  motorCorrectTest();

//  _DBG_("init mouse");
 // mouseinitial();
}

int doTheDemo() { 
  /**
   * @todo create checks for the current environment setup. This should include line and wall checks	
   * @todo create state machine that will set the state based on the priority of the input.
   * @todo make sure that the front sensor always interrupts
  */
  int currentState = -1;
  
  if(checkForLine()) {
    if (checkForWall() == 2) {
      currentState = 3;
    }
    else
      currentState = 0;
  }
  else if(checkForWall() == 1 || checkForWall() == 2) {
    currentState = 1;
  }
  else if(checkForWall() == 3 && courseType) {
    currentState = 4;
  }    
  else {
    currentState = 2;
  }
  
  if (currentState > -1) { // should never be -1 but if it is we have some problems
    switch (currentState) {
      
      case 0: { // Woop I've found a line
        followLine(); ///@todo how do I know when to stop... where all the line gone?
        break;
      }
      case 1: { //Wall found... follow it
        correctForwardMotion(); //looped by state machine
        break;
      }
      case 2: {// No Wall found track movement with mouse
        trackByMouse();
        break;
      }
      case 3: {// Walls and lines on both sides
        dockBySensorsAndLine();
        break;
      }
      case 4: { // left wall ended, bear right
        turnRight();
        delay(20); ///@todo need to add something in case we never reach the wall
        forwards(15);
      }      
      default: {  // should never reach but if it does then track movement with mouse
        currentState = 2;
      }  
    }
    return 1;
  }
  else {
    if(DBG_LEVEL == 1) {
      _DBG_("ARGH WE HAVE NO ENVIRONMENT");
    }
    return 0;
  }
}

void main(void) {
  initialise();
  _DBG_("Magic!");
  
  doATest();
  
  _DBG_("Done");
}





  /*
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
  
  trackMovement(100); /// @todo check this value
  
  findALine();
  
  followToDock();

void trackMovement(int distance) {
  /// @todo Take current value
  
  // Start moving
  forwards(20);
  
  /// @todo Take value & check against distance
  
}

void findAWall() {
  /// @todo needs to be able to deal with not being near the wall
  /// @todo needs to recognise that the wall might be directly in front.
}

void followWall() {
  /// @todo correct motion allong wall until no more wall then get out! 
}

void updateMouse() {
  /// @todo should take in location values
  /// @todo move into mouse.c
  /// @todo set location values because we know where we are
}

void findALine() {
  /// @todo move to line follow
  /// @todo implement this
}

void followToDock() {
  /// @todo use functions from line following, lineFollow() until dock.
}*/








