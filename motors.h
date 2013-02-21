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

#define MAX_SPEED 40

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
/**
* Sets the left motor speed  
*
* @author Jed Warwick-Mooney
* @author Andrew Durant
* @param int input speed for left motor
*/
void setLeftMotor(int left);
/**
* Sets the right motor speed  
*
* @author Jed Warwick-Mooney
* @author Andrew Durant
* @param int input speed for right motor
*/

void setRightMotor(int right);

/**
* Allows the setting of the left and right motors in one call
*
* @author Jed Warwick-Mooney
* @param int speed to set left motor at, int speed to set right motor at
*/

void setMotors(int lm, int rm);

/**
* Sets the speed the motors will go in the forwards direction
*
* @author Jed Warwick-Mooney
* @param int speed
*/

void forwards(int s);

/**
* Sets speed of motors in the backwards direction
*
* @author Jed Warwick-Mooney
* @param int speed
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
*git checkout 40f2acb65a235f8d74033d073451f6b8145f1660^1 doxy.doxyfile
*
* @author Jed Warwick-Mooney
*/

void spinLeft();

/**
* Sets the right motor to backwards and left forwards in order to spin right
*
*
* @author Jed Warwick-Mooney
*/

void spinRight();
/**
* Spins Left for x seconds till it faces 90 degrees to its Left
* Needed for line following
*
* @author Christopher King
*/
void Turn90Left();
/**
* Spins Right for x seconds till it faces 90 degrees to its right
* Needed for line following
*
* @author Christopher King
*/
void Turn90Right();
/**
* Spins 180 degrees so it is facing the way it came
* Needed for line following
*
* @author Christopher King
*/
void Turn180();


void motorStateMachine(int state);

#endif
