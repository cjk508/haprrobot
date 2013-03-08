/***************************************************************//**
 *	@file tests.c
 *	@brief	contains all of the tests for each part of the robot
 *
 *	@author Andrew Durant
 *	@author Chistopher King
 *	@author Jed Warwick-Mooney
 *	@author Lloyd Wallis
 *
 *	@version V1.5
 *	@date 01 March 2013
 *
*/
#include "debug_frmwrk.h"
#include "linefollow.h"
#include "uart.h"
#include "sensors.h"
#include "motors.h"
#include "correctmotion.h"
#include "timer.h"
#include "environment.h"

#define DBG_LEVEL 1

// Here be test functions!

/**
 * Tests the uart connections between the MBED board and the m3pi
 *
 * @author Andrew Durant
 */
void serialTest() {
  if (DBG_LEVEL >= 1) _DBG_("Init Serial");
//  initSerial(); 
  unsigned char buf[6];
  cmdSig(buf);
  _DBG_((char*)buf);
}

/**
 * Tests the front and side sensors on the robot, prints out the values that correctmotion will recieve
 *
 * @author Christopher King <cjk508@york.ac.uk>
 */
void sensorsTest() {
  SensorPair left = getLeftSensorValues();
  SensorPair right = getRightSensorValues();
  SensorPair leftcal = calibratedValuesLeft(left);
  SensorPair rightcal = calibratedValuesRight(right);
  //_DBG_("##################");
  _DBG("Left Front:");_DBD16(left.FrontSensor);_DBG_("");
  //_DBG("Left Rear:");_DBD16(left.RearSensor);_DBG_("");
  //_DBG("Left FCal:");_DBD16(leftcal.FrontSensor);_DBG_("");
  //_DBG("Left RCal:");_DBD16(leftcal.RearSensor);_DBG_("");
  //_DBG("Right Front:");_DBD16(right.FrontSensor);_DBG_("");
  //_DBG("Right Rear:");_DBD16(right.RearSensor);_DBG_("");
  //_DBG("Right FCal:");_DBD16(rightcal.FrontSensor);_DBGm_("");
  //_DBG("Right RCal:");_DBD16(rightcal.RearSensor);_DBG_("");
  /*int i = 0;
  while (i < 3000000) {i++;}*/
}
/**
 * Tests line following. Very easy atm because the linefollowing code doesn't work
 *
 * @author Christopher King <cjk508@york.ac.uk>
 */

void linefollowTest(){
  _DBG_("LINE FOLLOW TEST");
}
/**
 * Tests the motion correction, should stop if there is an object infront of the robot, otherwise it should follow a wall
 *
 * @author Lloyd Wallis
 * @author Christoher King
 */
void motorCorrectTest() {
  forwards(15);
  _DBG_("Moving");
  setSensorSide(1);
  _DBG_("Using Left");
  //checkForWall();
  while (1) 
  {
    int i =0;
    while (i < 3000000) {i++;}
    correctForwardMotion();
  }
}
