/************************************************************//**
 *	@file	motors.h
 *	@brief	contains all the motor controls for the m3pi robot. It keeps track of the direction and the speed of each motor
 *		it will also allow each motor to be set usin easily readible commands and allow the speeds to be read by other functions
 *		within haprrobot.
 *	@author	Jed Warwick-Mooney
 *	@author	Andrew Durant
 *	@author Christopher King
 *
 *	@version:	 V0.9
 *	@date:	01 March 2013
 */
/* Motor library for m3pi
 * Jed Warwick-Mooney
 * Andrew Durant
 * 
 * Provides basic functions for each serial command that can be sent to the m3pi
 *
 */

#ifndef MOTOR_INC
#define MOTOR_INC

#define MAX_SPEED 30

int current_motor_speed_left;
int current_motor_speed_right;

int current_motor_dir_left;
int current_motor_dir_right;

int getSpeedLeft();
int getSpeedRight();

/**
 * Restricts the max speed to the constant MAX_SPEED
 *
 * @author Jed Warwick-Mooney
 * @author Andrew Durant
 * @param speed input speed
 * @return restricted speed
 */
int speedCheck(int speed);
/**
* Sets the left motor forward speed  
*
* @author Andrew Durant
* @param speed input speed for left motor

*/
void setLeftMotorFw(int speed);
/**
* Sets the left motor backward speed  
*
* @author Andrew Durant
* @param speed input speed for left motor

*/
void setLeftMotorBw(int speed);
/**
* Sets the right motor forward speed  
*
* @author Andrew Durant
* @param speed input speed for right motor

*/
void setRightMotorFw(int speed);
/**
* Sets the right motor backward speed  
*
* @author Andrew Durant
* @param speed input speed for right motor

*/
void setRightMotorBw(int speed);

/**
* Allows the setting of the left and right motors in one call
*
* @author Jed Warwick-Mooney
* @param lm speed to set left motor at
* @param rm speed to set right motor at

*/

void setMotorsFw(int lm, int rm);
/**
* Allows the setting of the left and right motors in one call
*
* @author Jed Warwick-Mooney
* @param lm speed to set left motor at
* @param rm speed to set right motor at

*/

void setMotorsBw(int lm, int rm);

/**
* Sets the speed the motors will go in the forwards direction
*
* @author Jed Warwick-Mooney
* @param s speed to set motors forwards
*/

void forwards(int s);

/**
* Sets speed of motors in the backwards direction
*
* @author Jed Warwick-Mooney
* @param s speed to set motors backwards
*/

void backwards(int s);

/**
* Sets right motor low and left motor high to turn right
*
* @author Jed Warwick-Mooney
*/

void right();

/**
* Sets left motor low and right motor high to turn left
*
* @author Jed Warwick-Mooney
*/

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

/**
* Sets the left motor to backwards and right forwards in order to spin left
* git checkout 40f2acb65a235f8d74033d073451f6b8145f1660^1 doxy.doxyfile
*
* @author Jed Warwick-Mooney
*/

void spinLeft();

/**
* Sets the right motor to backwards and left forwards in order to spin right
*
* @author Jed Warwick-Mooney
*/

void spinRight();
/** removed as found new way of doing this
* Spins Left for x seconds till it faces 90 degrees to its Left
* Needed for line following
*
* @author Christopher King
*
*void Turn90Left();
**
* Spins Right for x seconds till it faces 90 degrees to its right
* Needed for line following
*
* @author Christopher King
*
void Turn90Right();
**
* Spins 180 degrees so it is facing the way it came
* Needed for line following
*
* @author Christopher King
*
void Turn180();
*/

void motorStateMachine(int state);

#endif
