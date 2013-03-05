/*********************************************************************//**
*	@file mouse.h
*	@brief	 Records mouse sensor data in order to find out how far it has moved form the original start point
*
*	@author	Jed Warwick-Mooney
*	@version: V0.8
*	@date:	28 February 2013
************************************************************************/
#ifndef MOUSE
#define MOUSE

#include "KeyboardHost.h"

void mouseinitial();

void myspecialpoll();

/**
* Records what movement has occured in the robot on every interrupt.
* A change in the t value only means the robot is spinning, the angle
* the robot faces is worked out usnig the spin() method and returned to
* added to theta.
* A change in the x value only means the robot is moving either forwards
* or backwards and the value is added to x_move or y_move depending on
* direction the robot is facing.
* A change in both t and x values at the same time means the robot is
* moving in an arc like shape. The method curve() is called to manipulate
* the recieved values and add the results to x_move and y_move 
*
* @author Jed Warwick-Mooney
* @param buttons unsigned int button pressed(not used), int movement in the 
* forward
* @param x int movement in the forward or backward direction
* @param t int movement in the left or right direction
* 
*/
void cb(uint8_t buttons, int8_t x, int8_t t);

/**
* Manipulates integers t and x using trigonometry, to work out the actual
* distance travelled by the robot when it moves in an arc like way. 
*
* @author Jed Warwick-Mooney
* @param  x integer indicating the forward/backward movement distance 
* of the robot
*/
void curve(int x);

/**
* Returns an angle in radiens, after dividing the length l travelled by the constant r
*
* @author Jed Warwick-Mooney
* @param l integer being the value of the arc length
* @param r integer being the radius of the circle
* @return th angle which the robot is facing
*/
int32_t spin(int l, int r);

/**
* When USB mouse is attached to the integers 
* x_move and y_move are set to 0
*
* @author Jed Warwick-Mooney
* 
*/
void attach();

/**
* When the USB is detahced form the Polulu 
* robot the x_move nd y_move ints are sent to 
* the method printLCD()
*
* @author Jed Warwick-Mooney
* 
*/
void detach();

/**
* Returns the value of x_move
*
* @author Jed Warwick-Mooney
* @return x_move
* 
*/
int32_t give_x_move();

/**
* Returns the value of y_move
*
* @author Jed Warwick-Mooney
* @return y_move
* 
*/
int32_t give_y_move();

/**
* Sets the value of x_move to the value of the param x
*
* @author Jed Warwick-Mooney
* @param x 8 bit int
* 
*/
void add_to_x(int8_t x);

/**
* Sets the value of x_move to the value of the param y
* 
* @author Jed Warwick-Mooney
* @param y 8 bit int
* 
*/
void add_to_y(int8_t y);

/**
* Works out the distance the robot has moved 
* from it's orignal starting position 
* and prints the value to the debug screen.
*
* @author Jed Warwick-Mooney
* @param x int
* @param y int
* @return d - interger indicating the distance moved
*/
int distanceMoved(int x, int y);

/**
* Translates an integer value to an ascii value 
* 
* @author Jed Warwick-Mooney(not original author)
* @param val - value we want in ascii 
* @param buf - stores ascii value
*/
int my_itoa(int val, char* buf) ;

/**
* Prints the distance the robot has moved from its start point
* by calling distanceMoved(x, y) and sending the result to the LCD.
* 
* @author Jed Warwick-Mooney
*/
void printToLCD();


#endif
