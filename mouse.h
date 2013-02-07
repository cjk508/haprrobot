/* Records mouse sensor data in order to find out how far it has moved form the original start point
*  
* Jed Warwick-Mooney
*/
#ifndef MOUSE
#define MOUSE

#include <KeyboardHost.h>
#include "math.h"



/**
* Records what movement has occured in the robot on every interrupt
*
* @author Jed Warwick-Mooney
* @param unsigned int button pressed(not used), int movement in the forward
* or backward direction, int movement in the left or right direction
* 
*/
void cb(uint8_t buttons, int8_t X, int8_t Y);
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
* the method distanceMoved()
*
* @author Jed Warwick-Mooney
* 
*/
void detach();
/**
* Returns the value of x_move
*
* @author Jed Warwick-Mooney
* 
*/
int32_t give_x_move();
/**
* Returns the value of y_move
*
* @author Jed Warwick-Mooney
* 
*/
int32_t give_y_move();
/**
* Sets the value of x_move to the value of the param x
*
* @author Jed Warwick-Mooney
* @param 8 bit int x
* 
*/
void set_x_move(int8_t x);
/**
* Sets the value of x_move to the value of the param y
* 
* @author Jed Warwick-Mooney
* @param 8 bit int y
* 
*/
void set_y_move(int8_t y);
/**
* Works out the distance the robot has moved 
* from it's orignal starting position 
* and prints the value to the debug screen
*
* @author Jed Warwick-Mooney
* @param int x, int y
*/
void distanceMoved(int x, int y);
/**
* Interrupts the USB mouse every 50ms to take X and Y values
*
* @author Jed Warwick-Mooney
* 
*/
void TIMER0_IRQHandler();
/**
* Runs the mouse_init which sets up the mouse
*
* @author Jed Warwick-Mooney
* 
*/

#endif
