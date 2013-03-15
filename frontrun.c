#include "environment.h"
#include "motors.h"
#include "debug_frmwrk.h"
#include "sensors.h"
#include "timer.h"
#include "uart.h"
#include "correctmotion.h"
#include "frontrun.h"

/// previous sensor side, how to run away
int previousSensorSide =0;
int delayCounter;


void runAway(void) {
	sensorSide = 3;
	backwards(15);
	delay(75);
	while (sensorSide == 3) {
		spinLeft();
		checkForWall();
	}
	previousSensorSide = sensorSide;
	delayCounter = 0;
	// turn and follow the nearest wall for delay 50
	while(delayCounter < 50 ) {
		if (sensorSide) {
		  	SensorPair temp = getLeftSensorValues();
			SensorPair distanceMeasured = calibratedValuesLeft(temp);
			if (distanceMeasured.FrontSensor >=35 && distanceMeasured.RearSensor >=35) {
				break;
			}
			else {
				correctForwardMotion();
			}
		}
		else {
  			SensorPair temp = getRightSensorValues();
			SensorPair distanceMeasured = calibratedValuesRight(temp);
			if (distanceMeasured.FrontSensor >=35 && distanceMeasured.RearSensor >= 35) {
				break;
			}
			else {
				correctForwardMotion();
			}
		}
		waitForAWhile();
	}
	// Oh no the wall goes on for ages or there isn't a wall! turn and follow a different wall
	delayCounter = 0 - delayCounter;
	while (previousSensorSide != sensorSide) {
		spinRight();
	}
	while(delayCounter < 0 ) {
		forwards(15);
		waitForAWhile();
	}
	while(delayCounter < 50 ) {
		if (sensorSide) {
		  SensorPair temp = getLeftSensorValues();
			SensorPair distanceMeasured = calibratedValuesLeft(temp);
			if (distanceMeasured.FrontSensor >=35 && distanceMeasured.RearSensor >= 35) {
				break;
			}
			else {
				correctForwardMotion();
			}
	  }
		else {
  		SensorPair temp = getRightSensorValues();
			SensorPair distanceMeasured = calibratedValuesRight(temp);
			if (distanceMeasured.FrontSensor >=35 && distanceMeasured.RearSensor >= 35) {
				break;
			}
			else {
				correctForwardMotion();
			}
		}
		waitForAWhile();
	}
	brake();
	cmdDoPlay("abc");
	_DBG_("Wall goes on for a very long way I'm not going to follow it!");
}

void waitForAWhile(void){
	delay(10);
	delayCounter +=1;
}
