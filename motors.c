#include "motors.h"
#include "sensors.h"
#include "timer.h"
#include "uart.h"
#include "debug_frmwrk.h"

/*! \def DBG_LEVEL
*  \brief Sets level of debuging ouput.
*  Makes everything easier to switch on and off what is output for debuging
*  1- Verbose
*  2- No Movement
*/
#define DBG_LEVEL 1

motorPair getSpeedLeft() {
	struct motorPair motorValues;
	motorValues.motor_speed = current_motor_speed_left;
	motorValues.motor_dir = current_motor_dir_left;

	return motorValues;
}

motorPair getSpeedRight() {
	struct motorPair motorValues;
	motorValues.motor_speed = current_motor_speed_right;
	motorValues.motor_dir = current_motor_dir_right;

	return motorValues;
}

int isMovingForward() {
	return (current_motor_dir_left && current_motor_dir_right)
	&& (current_motor_speed_left != 0 && current_motor_speed_right != 0);
}

int speedCheck(int speed) {
	speed = (speed < 0) ? 0 : speed;
	return (speed > MAX_SPEED) ? MAX_SPEED : speed;
}

void setLeftMotorFw(int speed) {
	if (frontIRQ_triggered) return;
	current_motor_dir_left = 1;
	current_motor_speed_left = speedCheck(speed);
	/*if (DBG_LEVEL >= 1) {
	_DBG("Left MotorF: ");_DBD32(current_motor_speed_left);_DBG_("");
}*/
cmdLeftMFw(current_motor_speed_left);
}
void setLeftMotorBw(int speed) {
	if (frontIRQ_triggered) return;
	current_motor_dir_left = 0;
	current_motor_speed_left = speedCheck(speed);
	/*	if (DBG_LEVEL >= 1) {
	_DBG("Left MotorB: ");_DBD32(current_motor_speed_left);_DBG_("");
}*/
cmdLeftMBw(current_motor_speed_left);
}

void setRightMotorFw(int speed) {
	if (frontIRQ_triggered) return;
	current_motor_dir_right = 1;
	current_motor_speed_right = speedCheck(speed);
	/*if (DBG_LEVEL >= 1) {
	_DBG("Right MotorF: ");_DBD32(current_motor_speed_right);_DBG_("");
}*/
cmdRightMFw(current_motor_speed_right);
}
void setRightMotorBw(int speed) {
	if (frontIRQ_triggered) return;
	current_motor_dir_right = 0;
	current_motor_speed_right = speedCheck(speed);
	/*if (DBG_LEVEL >= 1) {
	_DBG("Right MotorB: ");_DBD32(current_motor_speed_right);_DBG_("");
}*/
cmdRightMBw(current_motor_speed_right);
}

void setMotorsFw(int lm, int rm) {
	setLeftMotorFw(lm);
	setRightMotorFw(rm);
}
void setMotorsBw(int lm, int rm) {
	setLeftMotorBw(lm);
	setRightMotorBw(rm);
}

void forwards(int s) {
	setMotorsFw(s+2, s);
}

void backwards(int s) {
	s = s * (-1);
	setMotorsBw(s, s+2);
}

void right() {
	setLeftMotorFw(25);
	setRightMotorFw(15);
}

void left() {
	setLeftMotorFw(15);
	setRightMotorFw(25);
}

void brake() {
	setMotorsFw(0, 0);
}

void spinLeft() {
	setLeftMotorFw(25);
	setRightMotorBw(25);
}

void spinRight() {
	setLeftMotorBw(25);
	setRightMotorFw(25);
}

void resume(motorPair lm, motorPair rm) {
	if(lm.motor_dir == 1 ) {
		setLeftMotorFw(lm.motor_speed);
	} else {
		setLeftMotorBw(lm.motor_speed);
	}

	if(rm.motor_dir == 1 ) {
		setRightMotorFw(rm.motor_speed);
	} else {
		setRightMotorBw(rm.motor_speed);
	}
}
