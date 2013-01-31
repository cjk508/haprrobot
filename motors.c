#include "motors.h"

// uint32_t cmdLeftMFw(int speed); 0xC1 - M1 forward
// uint32_t cmdLeftMBw(int speed); 0xC2 - M1 backward
// uint32_t cmdRightMFw(int speed); 0xC5 - M2 forward
// uint32_t cmdRightMBw(int speed); 0xC6 - M2 backward

int current_motor_speed_left;
int current_motor_speed_right;


int speedCheck(int speed) {
	if(speed > MAX_SPEED) speed = MAX_SPEED;
	return speed;
}

void setLeftMotor(int left) {
	current_motor_speed_left = left;
	if(left < 0 ) {
		left *= -1;
		cmdLeftMBw(speedCheck(left));
		cmdLeftMFw(0);
	}
	else {
		cmdLeftMFw(speedCheck(left));
		cmdLeftMBw(0);
	}
}

void setRightMotor(int right) {
	current_motor_speed_right = right;
	if(right < 0 ) {
		right *= -1;
		cmdRightMBw(speedCheck(left));
		cmdRightMFw(0);
	}
	else {
		speedCheck(right);
		cmdRightMFw(speedCheck(left));
		cmdRightMBw(0);
	}
}

void setMotors(int lm, int rm) {
	setLeftMotor(lm);
	setRightMotor(rm);
}

void forwards(int s) {
	setMotors(s, s);
}

void backwards(int s) {
  s = s * (-1);
	setMotors(s, s);
}

void right() {
	setMotors(15, 0);
}

void left() {
	setMotors(0, 15);
}

void freewheel() {
	setMotors(0, 0);
}

void brake() {
  int brakeSpeed = speedCheck(127);
	cmdLeftMFw(brakeSpeed);
	cmdRightMFw(brakeSpeed);
	cmdLeftMBw(brakeSpeed);
	cmdRightMBw(brakeSpeed);
}

void spinLeft() {
	setMotors(-25, 25);
}

void spinRight() {
	setMotors(25, -25);
}


