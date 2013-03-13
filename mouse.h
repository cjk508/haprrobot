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
* The disance between the robots pivot point and the mouse sensor in centimeters
*/
const int r;
/**
* The angle the robot is facing in radiens
*/
double theta;
/**
* The coordinate value of x along the x axis
*/
int32_t coord_x;
/**
* The coordinate value of y along the y axis
*/
int32_t coord_y;
/**
* Intialiases the mouse by linking the cb, attach, detach methods together and calling mouse_init
*
* @author Jed Warwick-Mooney (Initial Coding)
*
*/
void mouseinitial();
/**
*	Called by timer.h to call mouse_poll() in mouse to save timer.c calling it as this caused problems
*
*	@author Chris King (Initial Coding)
* @author Jed Warwick-Mooney (Initial Coding)
*/

void myspecialpoll();
/**
* Takes the two integers and checks if they are larger than 125 or less than -125, 
* if either is the case then a debug message is sent stating there is an overflow
* A motorPair are then intialised for the left and right motors to allow us to save
* the values of the motors, the brakes are applied to slow the robot down, delay is
*	called, resume() is then called with the 2 motorPair values being passed with it
*	to return the robot to its previous state.

* @author Jed Warwick-Mooney(Intial Coding)
*	@param y the y value of the mouse
*	@param t the t value of the mouse
*/
void overflowProtection(int8_t y, int8_t t);
/**
* Returns an angle in radiens, after dividing the length l travelled by the constant r
*
* @author Jed Warwick-Mooney (Initial Coding)
* @param l integer being the value of the arc length
* @param r integer being the radius of the circle
* @return th angle which the robot is facing
*/
double thetaOfArc(int32_t l, int32_t r);
/**
* Takes an integer value and convertes it into centimeters 
* 
* @author Jed Warwick-Mooney (Initial Coding)
* @param x integer to be converted
* @return temp the resulting centimeter value
*/
int32_t converterForCm(int32_t x);
/**
* Takes an angle in radiens and returns the degrees conversion
* of the angle
* 
* @author Jed Warwick-Mooney (Initial Coding)
* @param t the radiens angle we want to convert to degrees
* @return temp the angle in degrees
*/
int32_t convertToDeg(int32_t t);

/**
* Called by mouse_poll() containd in myspecialpoll() according to the time the 
* interrrupt is set to. When called, the parameter buttons is ignored and y and 
* t are tested to see if they match one of three conditions,
* 1 - only t is changing, meaning the robot is moving on the spot i.e. spinning
* 2 - only y in changing, meaning the robot is moving in forwards/backwards direction
* 3 - both y and t are changing, meaning the robot is moving in curve
* Once the conditon the integers match to, is determined, the static int "state" is set to
* the corresponding integer of the state, with prevState being set to state before state
* is set. overflowProtection() is called to make sure overflows are flagged/controlled.
* depending on the state the mehtod has entered y and t are added to their respected static temp
* variables. prevState is then checked to see if the previous state is different to the
* current state the robot is in, if so operate on it's values as these can affect how the
* values we just recieved are changed. Temp variables that have been added to within the state
* are then checked to see if they are above a certain value - if so they can be operated on. 
*
* @author Jed Warwick-Mooney (Initial Coding)
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
* @author Jed Warwick-Mooney (Initial Coding)
* @param  y integer indicating the forward/backward movement distance 
* of the robot
* @param  t integer indicating the left/right motion of the robot 
*/
void curve(int y, int t);

/**
* When USB mouse is attached to the integers 
* x_coords and y_coords are set to 0
* 
* @author Jed Warwick-Mooney (Initial Coding)
* 
*/
void attach();

/**
* Detaching the USB mouse causes the x_coord and y_coord values to be sent 
* to the debug screen via the printCoords() method
*
* @author Jed Warwick-Mooney (Initial Coding)
* 
*/
void detach();

/**
* Returns the value of coord_y
*
* @author Jed Warwick-Mooney (Initial Coding)
* @return coord_y
* 
*/
int32_t get_coord_y();

/**
* Returns the value of coord_x
*
* @author Jed Warwick-Mooney (Initial Coding)
* @return coord_x
* 
*/
int32_t get_coord_x();
/**
* Returns the value of theta
*
* @author Jed Warwick-Mooney (Initial Coding)
* @return the Theta value
*/
int32_t get_theta();

/**
* Adds the value of x to the x_coords integer whilst multipling
* the value of x by sin(theta) as the actual value of x can be 
* different in relation to where the robot is facing
*
* @author Jed Warwick-Mooney (Initial Coding)
* @param x 8 bit int
* 
*/
void add_to_x(int8_t x);

/**
* Adds the value of y to the y_coords integer whilst multipling
* the value of y by cos(theta) as the actual value of y can be 
* different in relation to where the robot is facing
* 
* @author Jed Warwick-Mooney (Initial Coding)
* @param y 8 bit int
* 
*/
void add_to_y(int8_t y);
/**
*	Prints the coordinates of the robot to the debug screen
*
* @author Jed Warwick-Mooney (Initial Coding)
* @param x integer of the x coordinate
* @param y integer of the y coordinate
* @param theta integer value representing the angle the robot faces, in degrees

*/
void printCoords(int32_t x, int32_t y, int32_t theta);

#endif
