/* Records mouse sensor data in order to find out how far it has moved form the original start point
*  
* Jed Warwick-Mooney
*/
#ifndef MOUSE
#define MOUSE

#include "KeyboardHost.h"

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
* @param unsigned int button pressed(not used), int movement in the forward
* or backward direction, int movement in the left or right direction
* 
*/
void cb(uint8_t buttons, int8_t X, int8_t Y);

/**
* Manipulates integers t and x using trigonometry, to work out the actual
* distance travelled by the robot when it moves in an arc like way.
*
* @author Jed Warwick-Mooney
* @param integer x indicating the forward/backward movement distance 
* of the robot
*/
void curve( int x)

/**
* Works out the angle of direction the robot faces 
*
* @author Jed Warwick-Mooney
* @param integer l being the value of the arc length, and integer r 
* being the radius of the circle
*/
int spin(int l, int r)

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
void add_to_x(int8_t x);

/**
* Sets the value of x_move to the value of the param y
* 
* @author Jed Warwick-Mooney
* @param 8 bit int y
* 
*/
void add_to_y(int8_t y);

/**
* Works out the distance the robot has moved 
* from it's orignal starting position 
* and prints the value to the debug screen.
*
* @author Jed Warwick-Mooney
* @param int x, int y
*/
<<<<<<< HEAD
int distanceMoved(int x, int y);

=======
//void distanceMoved(int x, int y);
>>>>>>> 411f2b6330cb7100bcc85257fdf722c0eb04aa2a
/**
* Prints the distance the robot has moved from its start point
* by calling distanceMoved(x, y) and sending the result to the LCD.
* 
* @author Jed Warwick-Mooney
*/
//void printToLCD()


#endif
