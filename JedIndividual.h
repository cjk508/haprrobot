/*********************************************************************//**
*	@file JedIndividual.h
*	@brief Individual part for Jed Warwick-Mooney
*
*	@author	Jed Warwick-Mooney
*	@version: V0.1
*	@date:	12 March 2013
************************************************************************/
#ifndef JEDINDIVIDUAL
#define JEDINDIVIDUAL
/**
* Works out the distance the robot has moved 
* from it's orignal starting position 
* and prints the value to the debug screen as well as the
* Lcd screen on the robot
*
* @author Jed Warwick-Mooney
* @param x int
* @param y int
* @return d - interger indicating the distance moved
*/
void distanceMoved(int x, int y);

/**
* Takes an integer double as an input and outputs a 
* character pointer(created by strdup()), pointing to 
* the new string of the number.
*
* @author Jed Warwick-Mooney
* @param toPrint integer double we want to transform to a string
* @return *bufToPrint a char* that holds the new string
*/
char* integerToAscii(double toPrint);
/**
* Takes an integer value associsated with the motion of the robot and sets
* it to the integer robotMotion which is between 0-6. This is set using values
* taken from the motors of the robot.
* 0 - indicates the robot is moving in a forwards motion
*	1 - indicates the robot is moving in a backwards motion
*	2 - indicates the robot is turning towards the left
*	3 - indicates the robot is turning towards the right
*	4 - indicates the robot is spinning in a clockwise direction
*	5 - indicates the robot is spinnign in a anti-clockwise direction
*	6 - indicates the robot is braking
* 
* @author Jed Warwick-Mooney
* @param i integer representing the current motion of the robot
*
*/
void recordMotion(motorPair RMV, motorPair LMV);
/**
* Uses the values of the mouse and robotMotion to see if the 
* robot is moving in the correct motion it thinks it's moving in
* and notifies the user using sound if something is not right.
* 
* @author Jed Warwick-Mooney
*	@param y mouse y value
*	@param t mouse t value
*/
void checkMotion(int y, int t);

#endif JEDINDIVIDUAL
