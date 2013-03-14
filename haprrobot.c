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
*	@date 13 March 2013
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

#include "andyIndividual.h"

// This is a file for your test functions
#include "tests.c"
/**
* @brief 0 short course goes straight on to dock 
*        1 is long course, bears right after left wall to find the right wall.
*/

int courseType = 0;
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

void doTheDemo() {

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
  
  if (courseType == 0) {
    cmdDoPlay(">aa");
    _DBG_("State 5");
    while(!checkForLine()) {
      
    }
    followLine();
    while(!checkForNoLine()) {
      
    }
    brake();
  }
  else {
    //Bear right to head for other wall
    cmdDoPlay(">ff");
    _DBG_("State 3");
    right();
    delay(1000);
    _DBG_("State 3.1");
    forwards(20);
    
    //Wait until right wall is trackable
    while (sensorSide != 2) {
      checkForWall();
      _DBD(sensorSide);_DBG_(" sens");
    }
    
    //Track right wall
    cmdDoPlay(">gg");
    _DBG_("State 4");
    wallState = -1;
    while (wallState != 4 && wallState != 0) {
      wallState = checkForWall();
      correctForwardMotion();
    }
    
    //Find the line
    cmdDoPlay(">aa");
    _DBG_("State 5");
    forwards(20);
    while(!checkForLine()) {
      
    }
    followLine();
    while(!checkForNoLine()) {
      
    }
    brake();
  }
}

void theremin() {
  setVolume();
  setNote();
}

void main(void) {
  initialise();
  _DBG_("Magic!");
  
  while(1) {
    if (getMode() == 0) {
      cmdDoPlay("ML");
      cmdDoPlay("T80");
      cmdDoPlay("L1");
      
      while(getMode() == 0) {
        theremin();
        int i = 0;
        while (i < 500000) {i++;}
      }
    }
    else if (getMode() == 1) {
      playPopcorn();
      int i = 0;
      while (i < 30000000) {i++;}
    }
  }
  
  _DBG_("Done");
}

void fullDemo() {
	int robotState = 0;
	uint16_t sensorPattern[5] = {0};	
	while(robotState != 6) {
		switch(robotState) {
			case 0:
				while(get_coord_x() < 200) {
					forwards(20);
				}
				robotState = 1;
				break;
			case 1:
				setSensorSide(1);
				while(get_coord_x() < 400) {
					correctForwardMotion();
				}
				robotState = 2;
				break;
			case 2:
				while(convertToDeg(get_theta()) > -90) {
					spinLeft();
				}
				while(get_coord_y() < 120) {
					forwards(20);
				}
				while(convertToDeg(get_theta()) < 0) {
					spinRight();
				}
				while(get_coord_x() < 600) {
					forwards(20);
				}
				robotState = 3;
				break;
			case 3:
				setSensorSide(2);
				while(get_coord_x() < 800) {
					correctForwardMotion();
				}
				robotState = 4;
				break;
			case 4:
				forwards(20);		
				while(sensorPattern[3]<2000){
					getRawSensors(sensorPattern);
				}
				robotState = 5;
				break;
			case 5:
				followLine();
				robotState = 6;
				break;
		}
	}
}
