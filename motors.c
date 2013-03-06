#include "motors.h"
#include "uart.h"
#include "debug_frmwrk.h" 

// uint32_t cmdLeftMFw(int speed); 0xC1 - M1 forward
// uint32_t cmdLeftMBw(int speed); 0xC2 - M1 backward
// uint32_t cmdRightMFw(int speed); 0xC5 - M2 forward
// uint32_t cmdRightMBw(int speed); 0xC6 - M2 backward

int getSpeedLeft() {
  return current_motor_speed_left;
}
int getSpeedRight() {
  return current_motor_speed_right;
}

int speedCheck(int speed) {
  speed = (speed < 0) ? 0 : speed;
	return (speed > MAX_SPEED) ? MAX_SPEED : speed;
}

void setLeftMotorFw(int speed) {
  current_motor_dir_left = 1;
	current_motor_speed_left = speedCheck(speed);
	_DBD32(current_motor_speed_left);_DBG_("");
	cmdLeftMFw(current_motor_speed_left);
}
void setLeftMotorBw(int speed) {
  current_motor_dir_left = 0;
	current_motor_speed_left = speedCheck(speed);
	_DBD32(current_motor_speed_left);_DBG_("");
	cmdLeftMBw(current_motor_speed_left);
}

void setRightMotorFw(int speed) {
  current_motor_dir_right = 1;
	current_motor_speed_right = speedCheck(speed);
	_DBD32(current_motor_speed_right);_DBG_("");
	cmdRightMFw(current_motor_speed_right);
}
void setRightMotorBw(int speed) {
  current_motor_dir_right = 0;
	current_motor_speed_right = speedCheck(speed);
	_DBD32(current_motor_speed_right);_DBG_("");
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
	//setMotors(25, 0);
}

void left() {
	//setMotors(0, 25);
}

void freewheel() {
	setMotorsFw(0, 0);
}

void brake() {
  freewheel();
}

void spinLeft() {
	//setMotors(-25, 25);
}

void spinRight() {
	setMotors(25, -25);
}
/**
* @todo need to check the timings for turning 90/180 degrees probably should create a timer
*/
void Turn90Left() {
  int i= 0;
  spinLeft();
  while(i<10000)
  {   
    i = i+1;
  }
  forwards(25);
}
void Turn90Right(){
  int i= 0;
  spinRight();
  while(i<10000)
  {  
    i = i+1;
  }
  forwards(25);
}

void Turn180(){
  int i= 0;
  spinRight();
  while(i<50000)
  {    
    i = i+1;
  }
  forwards(25);

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
