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
	while (sensorSide == 3) {
		spinLeft();
	}
	previousSensorSide = sensorSide;
	delayCounter = 0;
	// turn and follow the nearest wall for delay 50
	while(waitForAWhile() < 50 ) {
		if (sensorSide) {
		  SensorPair temp = getLeftSensorValues();
			SensorPair distanceMeasured = calibratedValuesLeft(temp);
			if (distanceMeasured.FrontSensor >=100 && distanceMeasured.RearSensor >= 100) {
				break;
			}
			else {
				correctForwardMotion();
			}
		}
		else {
  		SensorPair temp = getRightSensorValues();
			SensorPair distanceMeasured = calibratedValuesRight(temp);
			if (distanceMeasured.FrontSensor >=100 && distanceMeasured.RearSensor >= 100) {
				break;
			}
			else {
				correctForwardMotion();
			}
		}
	}
	// Oh no the wall goes on for ages or there isn't a wall! turn and follow a different wall
	delayCounter = 0 - delayCounter;
	while (previousSensorSide != sensorSide) {
		spinRight();
	}
	while(delayCounter < 0 ) {
		forwards(15);
	}
	while(waitForAWhile() < 50 ) {
		if (sensorSide) {
		  SensorPair temp = getLeftSensorValues();
			SensorPair distanceMeasured = calibratedValuesLeft(temp);
			if (distanceMeasured.FrontSensor >=100 && distanceMeasured.RearSensor >= 100) {
				break;
			}
			else {
				correctForwardMotion();
			}
	  }
		else {
  		SensorPair temp = getRightSensorValues();
			SensorPair distanceMeasured = calibratedValuesRight(temp);
			if (distanceMeasured.FrontSensor >=100 && distanceMeasured.RearSensor >= 100) {
				break;
			}
			else {
				correctForwardMotion();
			}
		}
	}
	brake();
	cmdDoPlay("abc");
	_DBG_("Wall goes on for a very long way I'm not going to follow it!");
}

int waitForAWhile(void){
	delay(10);
	delayCounter +=1;
}
