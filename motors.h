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

#ifndef MOTOR_INC
#define MOTOR_INC

/*! \def MAX_SPEED
 *  \brief Sets the speed limit that speedCheck() uses
*/
#define MAX_SPEED 25

int current_motor_speed_left;
int current_motor_speed_right;

int current_motor_dir_left;
int current_motor_dir_right;

/**
* @brief Motor return type, contains 2 integers motor_speed and motor_dir
*
* This struct will return the speed and direction of the motors at the time.
* It will allow easy access to all information that the motors need 
* this includes the direction of the motor as speed is always positive.
*
* @author Christopher King <cjk508@york.ac.uk>
* @author Jed Warwick-Mooney 
*/
typedef struct motorPair{
	int motor_speed;
	int motor_dir;
}motorPair;

/**
* Allows access to the left motor speed and direction
*
* @author Andrew Durant (Initial Coding & debug)
* @author Christopher King (Revision regarding motor pair)
* @author Jed Warwick-Mooney (Initial Coding)
* @return the speed and direction of the left motors
*/
motorPair getSpeedLeft();
/**
* Allows access to the right motor speed and direction
*
* @author Andrew Durant (Initial Coding & debug)
* @author Christopher King (Revision regarding motor pair)
* @author Jed Warwick-Mooney (Initial Coding)
* @return the speed and direction of the right motors
*/
motorPair getSpeedRight();

/**
* Returns 1 if the robot is moving forwards, 0 otherwise
*
* @author Lloyd Wallis <lpw503@york.ac.uk> (Initial Coding)
* @return If the robot is doing a forward
*/
int isMovingForward();
/**
 * Restricts the max speed to the constant MAX_SPEED
 *
 * @author Jed Warwick-Mooney
 * @author Andrew Durant @todo who wrote this?
 * @param speed input speed
 * @return restricted speed
 */
int speedCheck(int speed);
/**
* Sets the left motor forward speed  
*
* @author Andrew Durant (Initial Coding)
* @param speed input speed for left motor
*
*/
void setLeftMotorFw(int speed);
/**
* Sets the left motor backward speed  
*
* @author Andrew Durant (Initial Coding)
* @param speed input speed for left motor
*
*/
void setLeftMotorBw(int speed);
/**
* Sets the right motor forward speed  
*
* @author Andrew Durant (Initial Coding)
* @param speed input speed for right motor
*
*/
void setRightMotorFw(int speed);
/**
* Sets the right motor backward speed  
*
* @author Andrew Durant (Initial Coding)
* @param speed input speed for right motor
*
*/
void setRightMotorBw(int speed);

/**
* Allows the setting of the left and right motors in one call
*
* @author Jed Warwick-Mooney (Initial Coding)
* @param lm speed to set left motor at
* @param rm speed to set right motor at
*
*/

void setMotorsFw(int lm, int rm);
/**
* Allows the setting of the left and right motors in one call
*
* @author Jed Warwick-Mooney (Initial Coding)
* @param lm speed to set left motor at
* @param rm speed to set right motor at
*
*/

void setMotorsBw(int lm, int rm);

/**
* Sets the speed the motors will go in the forwards direction
*
* @author Jed Warwick-Mooney (Initial Coding)
* @param s speed to set motors forwards
*/

void forwards(int s);

/**
* Sets speed of motors in the backwards direction
*
* @author Jed Warwick-Mooney (Initial Coding)
* @param s speed to set motors backwards
*/

void backwards(int s);

/**
* Sets right motor low and left motor high to turn right
*
* @author Jed Warwick-Mooney (Initial Coding)
* @author Christopher King  (revision regarding new set motor functions)
*/

void right();

/**
* Sets left motor low and right motor high to turn left
*
* @author Jed Warwick-Mooney (Initial Coding)
* @author Christopher King  (revision regarding new set motor functions)
*/

void left();

/**
 * Sets all motors to high (forwards and backwards)
 * This stops it from freewheeling at all
 *
 * @author Andrew Durant (Initial Coding)
 */
void brake();

/**
* Sets the left motor to backwards and right forwards in order to spin left
*
* @author Jed Warwick-Mooney (Initial Coding)
*/

void spinLeft();

/**
* Sets the right motor to backwards and left forwards in order to spin right
* 
* @author Jed Warwick-Mooney (Initial Coding)
*/

void spinRight();
/**
* Sets the robot to its previous state after being interrupted by the overflowProtection() method in mouse.c 
*
* @author Chris King (Initial Coding)
*	@author Jed Warwick-Mooney (Initial Coding)
* @param lm The value for the direction and speed of the left motor
* @param rm The value for the direction and speed of the right motor
*/
void resume(motorPair lm, motorPair rm);
#endif
