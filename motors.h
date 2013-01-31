/* Motor library for m3pi
 * Jed Warwick-Mooney
 * Andrew Durant
 * 
 * Provides basic functions for each serial command that can be sent to the m3pi
 *
 */

#ifndef MOTOR_INC
#define MOTOR_INC

#include "uart.h"

#define MAX_SPEED 25

int current_motor_speed_left;
int current_motor_speed_right;

/**
 * Restricts the max speed to the constant MAX_SPEED
 *
 * @author Jed Warwick-Mooney
 * @author Andrew Durant
 * @param int input speed
 * @return int restricted speed
 */
int speedCheck(int speed);

void setLeftMotor(int left);

void setRightMotor(int right);

void setMotors(int lm, int rm);

void forwards(int s);

void backwards(int s);

void right();

void left();

/**
 * Sets all motors to low (forwards and backwards)
 * This allows the robot to freewheel
 *
 * @author Andrew Durant
 */
void freewheel();

/**
 * Sets all motors to high (forwards and backwards)
 * This stops it from freewheeling at all
 *
 * @author Andrew Durant
 */
void brake();

void spinLeft();

void spinRight();

#endif
