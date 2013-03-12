// Jed Individual

#include "math.h"
#include "mouse.h"
#include <string.h>
#include "uart.h"
#include "motors.h"
#include "debug_frmwrk.h"
#include "timer.h"

int robotMotion;



char* integerToAscii(double toPrint) {
	char* bufForPrint = "0";
	char numbers[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	int32_t intToPrint = toPrint;
	if(intToPrint > 0) {
		*bufForPrint++ = '-';
    intToPrint *= (-1);
	}
	while(intToPrint > 0) {
		int i = intToPrint % 10;
		intToPrint /= 10;
		*bufForPrint++ = numbers[i];
	}
	return strdup(bufForPrint);
} 

void totalDistanceMoved(int32_t x, int32_t y) {
	double d = ((x^2) + (y^2)); //pythagarus theorem used to work out overall distance moved from orignal start point
	d = sqrt(d);
	_DBG_("The total distance moved by the Pololu robot is: ");
	_DBD(d); _DBG_("");
	cmdLcdPrint(integerToAscii(d));
}

void recordMotion(motorPair RMV, motorPair LMV) {
	if(((RMV.motor_speed == (LMV.motor_speed+2||LMV.motor_speed-2)) != 0) && (RMV.motor_dir == LMV.motor_dir)){
		robotMotion = 1; // The robot is moving forwards or backwards
	}
	else if((RMV.motor_speed > LMV.motor_speed) && (RMV.motor_dir == LMV.motor_dir)) {
		robotMotion = 2; // The robot is turning left
	}
	else if((RMV.motor_speed < LMV.motor_speed) && (RMV.motor_dir == LMV.motor_dir)) {
		robotMotion = 3; // The robot is turning right
	}
	else if((RMV.motor_speed == LMV.motor_speed) && (RMV.motor_dir > LMV.motor_dir)) {
		robotMotion = 4; // spinning left
	}
	else if((RMV.motor_speed == LMV.motor_speed) && (RMV.motor_dir < LMV.motor_dir)) {
		robotMotion = 5; // spinning right
	}
	else if(RMV.motor_speed == 0 && LMV.motor_speed == 0) {
		robotMotion = 6; // braking
	}
}

void checkMotion(int y, int t) {
	motorPair rightMotorValue = getSpeedRight();
	motorPair leftMotorValue = getSpeedLeft();
	recordMotion(rightMotorValue, leftMotorValue);
	if(((y != 0 && t != 0) || y == 0)  && robotMotion == (1)) {
		brake();
		delay(100000);
		if(t > 0) {
			cmdDoPlay("abab>a");
			
			right();
			delay(100000);
		}
		else if(t < 0) {
		  cmdDoPlay("abba>a");
			
			left();
			delay(100000);
		}
		if(y==0) {
			cmdDoPlay("aaaaa>a");//the robot is not moving when it sould be
		}
		resume(rightMotorValue, leftMotorValue);
	}
	else if(robotMotion == (2) && (t < 0)) {
		cmdDoPlay("abcd>b");//Should be turning left but isn't
		left();
	}

	else if(robotMotion == (3) && (t > 0)) {
		cmdDoPlay("abef>b");//Should be turning right but isn't
		right();
	}

	else if(robotMotion == (4) && t < 0) {
		cmdDoPlay("bacd>c");//Should be spinning left but isn't
	}

	else if(robotMotion == (5) && t > 0) {
		cmdDoPlay("baef>c");//Should be spinning right but isn't
	}

	else if(y != 0 && t!=0 && robotMotion == (6)) {
		cmdDoPlay("abababa>d"); //Should be braking but isn't
	} 
}

