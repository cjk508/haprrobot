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
/**
* Intialiases the mouse by linking the cb, attach, detach methods together and calling mouse_init
*
* @author Jed Warwick-Mooney
*
*/
void mouseinitial();
/**
*	Called by timer.h to call mouse_poll() in mouse to save timer.c calling it as this caused problems
*
*	@author Chris King
* @author Jed Warwick-Mooney
*/

void myspecialpoll();

/**
* Returns an angle in radiens, after dividing the length l travelled by the constant r
*
* @author Jed Warwick-Mooney
* @param l integer being the value of the arc length
* @param r integer being the radius of the circle
* @return th angle which the robot is facing
*/
double thetaOfArc(int32_t l, int32_t r);
/**
* Takes an integer value and convertes it into centimeters 
* 
* @author Jed Warwick-Mooney
* @param x integer to be converted
* @return temp the resulting centimeter value
*/
int32_t converterForCm(int32_t x);

/**
* Clears the value of the integer given to it
* 
* @author Jed Warwick-Mooney
* @param x the integer to be cleared
*/
void clearVal(int x);

/**
* Records what movement has occured in the robot on every interrupt.
* A change in the t value only means the robot is spinning, the angle
* the robot faces is worked out usnig the spin() method and returned to
* added to theta.
* A change in the y value only means the robot is moving either forwards
* or backwards and the value is added to coord_x and/or coord_y depending on
* direction the robot is facing.
* A change in both t and y values at the same time means the robot is
* moving in an arc like shape. The method curve() is called to manipulate
* the recieved values and add the results to coord_x and coord_y 
*
* @author Jed Warwick-Mooney
* @param buttons unsigned int button pressed(not used), int movement in the 
* forward
* @param y int movement in the forward or backward direction
* @param t int movement in the left or right direction
* 
*/

void cb(uint8_t buttons, int8_t y, int8_t t);
/**
* Manipulates integers t and x using trigonometry, to work out the actual
* distance travelled by the robot when it moves in an arc like way. 
*
* @author Jed Warwick-Mooney
* @param  y integer indicating the forward/backward movement distance 
* of the robot
* @param  t ?
*/
void curve(int y, int t);

/**
* When USB mouse is attached to the integers 
* x_coords and y_coords are set to 0
*
* @author Jed Warwick-Mooney
* 
*/
void attach();

/**
* detaching the USB mouse causes the x_coord and y_coord values to be sent 
* to the debug screen via the printCoords() method
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
int32_t get_coord_y();

/**
* Returns the value of y_move
*
* @author Jed Warwick-Mooney
* @return y_move
* 
*/
int32_t get_coord_x();

int32_t get_theta();

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
* Translates an integer value to an ascii value 
* 
* @author Jed Warwick-Mooney(not original author)
* @param val - value we want in ascii 
* @param buf - stores ascii value
*/
int my_itoa(int val, char* buf) ;

/**
*	Prints the coordinates of the robot to the debug screen
*
* @author Jed Warwick-Mooney
* @param x integer of the x coordinate
* @param y integer of the y coordinate
* @param theta ?
*/
void printCoords(int32_t x, int32_t y, int32_t theta);

#endif
