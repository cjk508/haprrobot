#include "motors.h"
#include "sensors.h"
#include "timer.h"

/// previous sensor side, how to run away
int previousSensorSide;
int delayCounter;
void runAway(void) {
	sensorSide = 3;
	while (sensorSide == 3) {
		spinLeft();
	}
	previousSensorSide = sensorsSide
	delayCounter = 0;
	sensorSide distanceMeasured;
	while(waitForAWhile < 50 ) {
		if (sensorSide) {
		}
			distanceMeasured = calibrateLeftValues(getLeftSensors());
			if (distanceMeasured.FrontSensor >=100 && distanceMeasured.RearSensor >= 100) {
				break;
			}
			else {
				correctForwardMotion;
			}
		else {
			distanceMeasured = calibrateRightValues(getLeftSensors());
			if (distanceMeasured.FrontSensor >=100 && distanceMeasured.RearSensor >= 100) {
				break;
			}
			else {
				correctForwardMotion;
			}
		}
	}
	delayCounter = 0 - delayCounter;
	while (previousSensorSide != sensorSide) {
		spinRight();
	}
	while(delayCounter < 0 ) {
		forwards(15);
	}
	while(waitForAWhile < 50 ) {
		if (sensorSide) {
		}
			distanceMeasured = calibrateLeftValues(getLeftSensors());
			if (distanceMeasured.FrontSensor >=100 && distanceMeasured.RearSensor >= 100) {
				break;
			}
			else {
				correctForwardMotion;
			}
		else {
			distanceMeasured = calibrateRightValues(getLeftSensors());
			if (distanceMeasured.FrontSensor >=100 && distanceMeasured.RearSensor >= 100) {
				break;
			}
			else {
				correctForwardMotion;
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
