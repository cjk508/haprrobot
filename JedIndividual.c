#include "math.h"
#include "mouse.h"
#include <string.h>
#include "uart.c"

int robotMotion;

void totalDistanceMoved() {
	double d = ((x^2) + (y^2)); //pythagarus theorem used to work out overall distance moved from orignal start point
	d = sqrt(d);
	_DBG_("The total distance moved by the Pololu robot is: ");
	_DBD(d); _DBG_("");
	cmdLcdPrint(integerToAscii(d));
}

char* integerToAscii(double toPrint) {
	char* bufForPrint;
	char[] numbers = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	toPrint >= 0 ? (int32_t)(toPrint+0.5) : (int32_t)(toPrint-0.5);
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

void converterForTheta() {
	if(theta>0){
		while(theta>4){
			theta = theta - 4;
			actTheta+=1;
		}
	}
	else {
		while(theta<(-4)){
			theta = theta + 4;
			actTheta-=1;
		}
	}
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
	else if((RMV.motor_speed == LMV.motor_speed == 0) {
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
			cmdDoPlay*"aaaaa>a");
		}
		resume(rightMotorValue, leftMotorValue);
	}
	else if(y != 0 && robotMotion == (2)) {
		if(t < 0) {
		cmdDoPlay("abcd>b");//Should be turning left but isn't
		brake();
		delay(100000);
		left();
		}
	}

	else if(y != 0 && robotMotion == (3)) {
		if(t > 0) {
		cmdDoPlay("abef>b");//Should be turning right but isn't
		brake();
		delay(100000);
		right();
		}
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

