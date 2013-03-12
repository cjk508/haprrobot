/*********************************************************************//**
*	@file JedInduvidual.h
*	@brief	 Induvidual part for Jed Warwick-Mooney
*
*	@author	Jed Warwick-Mooney
*	@version: V0.1
*	@date:	12 March 2013
************************************************************************/

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
* character array with the new string of the number 
*
* @author Jed Warwick-Mooney
* @param toPrint integer double we want to transform to a string
* @return *bufToPrint a char* that holds the new string
*/
char* integerToAscii(double toPrint);
/**
* Takes an integer value associsated with the motion of the robot and sets
* it to the integer robotMotion
* 
* @author Jed Warwick-Mooney
* @param i integer representing the current motion of the robot
*
*/
void recordMotion(int i);
/**
* Uses the values of the mouse and robotMotion to see if the 
* robot is moving in the correct motion and corrects if otherwise
* 
* @author Jed Warwick-Mooney
*	@param y mouse y value
*	@param t mouse t value
*/
void checkMotion(int y, int t);
