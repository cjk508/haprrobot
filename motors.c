#include "motors.h"

// uint32_t cmdLeftMFw(int speed); 0xC1 - M1 forward
// uint32_t cmdLeftMBw(int speed); 0xC2 - M1 backward
// uint32_t cmdRightMFw(int speed); 0xC5 - M2 forward
// uint32_t cmdRightMBw(int speed); 0xC6 - M2 backward

int current_motor_speed_left;
int current_motor_speed_right;


int speedCheck(int speed) {
	return (speed > MAX_SPEED) ? MAX_SPEED : speed;
}

void setLeftMotor(int left) {
	current_motor_speed_left = left;
	if(left < 0 ) {
		left *= -1;
		cmdLeftMBw(speedCheck(left));
	}
	else {
		cmdLeftMFw(speedCheck(left));
	}
}

void setRightMotor(int right) {
	current_motor_speed_right = right;
	if(right < 0 ) {
		right *= -1;
		cmdRightMBw(speedCheck(right));
	}
	else {
		speedCheck(right);
		cmdRightMFw(speedCheck(right));
	}
}

void setMotors(int lm, int rm) {
	setLeftMotor(lm);
	setRightMotor(rm);
}

void forwards(int s) {
	setMotors(s+2, s);
}

void backwards(int s) {
  s = s * (-1);
	setMotors(s, s+2);
}

void right() {
	setMotors(25, 0);
}

void left() {
	setMotors(0, 25);
}

void freewheel() {
	setMotors(0, 0);
}

void brake() {
  freewheel();
}

void spinLeft() {
	setMotors(-25, 25);
}

void spinRight() {
	setMotors(25, -25);
}

void motorStateMachine(int state) {
switch(state) {
	case 0 :
		forwards(25);
		break;
	case 1 :
		right();
		break;
	case 2 :
  	left();
  	break;
  case 3:
    spinLeft();
    break;
  case 4 :
     spinRight();
     break;
	case 5 :
		brake();
		break;
	default	:
    break;
	}
}
