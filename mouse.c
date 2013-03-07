#include "mouse.h"
#include "math.h"
#include "debug_frmwrk.h"
#include "uart.h"
#include "timer.h"
#include "KeyboardHost.h"
#include <stdlib.h>
#include "motors.h"

const int r = 1;
int32_t x_move;
int32_t y_move;
int32_t theta;
int coord_x;
int coord_y;
// when the mouse moves slow enough it can detect 1000 points per 10cm, so 10000 = 1m
void mouseinitial()
{
  _DBG_("I'm starting");
  mouse_init(cb, attach, detach);
  _DBG_("I've set up the mouse");
}
void myspecialpoll() {
 /*this has been moved in case there was an issue reaching the cb function when it was
 called from timer.c. This shouldn't be an issue however it has been very slow to react 
therefore we thought it best to remove it and place it here. This may not be the best way
of debugging but it seems to have worked,*/
  mouse_poll();
}

void overflowProtection(int8_t x, int8_t t)
{
	if( x > 125 || x < -125 || -125 > t || t > 125) {
		_DBG_("OVERFLOW");
	}
}
void cb(uint8_t buttons, int8_t x, int8_t t) {
/**
* @todo put some form of overflow protection to make sure that we are getting fairly accurate results.
*/
	overflowProtection(x, t);
	//if there is a change in the t value only then the robot is spinning;
	if(t != 0 && x == 0) {
		_DBG_("Theta has changed by: ");
		_DBD32(t);
		_DBG_("");
		//int32_t spinVal = spin(t, r);
		theta = theta + t; 
		_DBG_("Value of theta is: ");
		_DBD32(theta);
		_DBG_("\n");
		turnRightTill90(theta);
	}
	
	//If there is a change in the x value only then the robot is moving forward;
	if(x != 0 && t == 0) {
		//_DBG_("The Mouse has moved Forward/Backward by: ");
		//_DBD32(x);
		//add_to_x(x);
		//add_to_y(x);
		//_DBG_("Value of x_move is: ");
		//_DBD32(x_move);
		//_DBG_("\n");
	}

	if(t != 0 && x != 0) {
		//_DBG_("Moving in a curve");
		//curve(x);
		//_DBG_("Value of x_move is: ");
		//_DBD32(x_move);
  	//_DBG_("Value of y_move is: ");
		//_DBD32(y_move);
		//_DBG_("\n");
	}
}

void turnRightTill90(int t) {
	if(t < 300){
	spinRight();
	}
	brake();
}

void converter() {
	coord_x = x_move/100;
	coord_y = y_move/100;
}

void curve(int x) {
/**
The Idea of this method is to work out how far the robot has moved with respect to the x and y axis coordinates.
*/
	int t = spin(x, r); // gives us an angle theta, from the length of the arc traversed, x, and the constant, r, wKolkatahere r is the radius of a circle.
	int hyp_2 = sin(t) * r; // gets sin(t) and multiplies it by r to get the hypotenuse, hyp_2, of the upper triangle 
	int x2 = hyp_2 * cos(t); // multiplies hyp_2 by the cosine of theta, to get an x value parrallel to the x axis of the overall coordinates
	int y2 = hyp_2 * sin(t); // multiplies hyp_2 by the sine of theta, to get an y value parrallel to the y axis of the overall coordinates
	int hyp_1 = r - (cos(t) * r); // gets cos(t) multplies it by r, then minusing r from the result of the multiplication to get the hypotenuse, hyp_1, of the lower triangle 
	int x1 = hyp_1 * sin(t);// multiplies hyp_1 by the cosine of theta, to get an x value parrallel to the x axis of the overall coordinates
	int y1 = hyp_1 * cos(t);// multiplies hyp_1 by the cosine of theta, to get an y value parrallel to the y axis of the overall coordinates
	theta += t;// add t to theta so the angle the robot now faces is known
	x_move += (x1 + x2);// add the values of x1 and x2 together so the overall parrallel movement with respect to the x axis is known
	y_move += (y2 - y1);// minus y1 (from the lower triangle) from y2( from the upper triangle) where the difference is how far left or right the robot has moved with respect to the y axis
}

int32_t spin(int l, int r) {
	int th = l/r;
	return th;
}

void attach() {
	x_move = 0;
	y_move = 0;
	theta = 0;
	_DBG_("I'm attached, YAY!");
}

void detach() {
	_DBG_("I'm detached, BOO!");
//	printToLCD();
}

int32_t get_x_move() {	
	//Returns the value of x_move
	return x_move;
}

int32_t get_y_move() {
	//Returns the value of y_move
	return y_move;
}

void add_to_x(int8_t x) {
	x_move += x * cos(theta); //x is multiplied by cos(theta) as direction the robot is facing can affect how far it actually moves along the x_axis
}

void add_to_y(int8_t y) {
	y_move += y * sin(theta);//y is multiplied by sin(theta) as direction the robot is facing can affect how far it actually moves along the y_axis
}

int distanceMoved(int x, int y) {
	int d;
	d = ((x^2) + (y^2)); //pythagarus theorem used to work out overall distance moved from orignal start point
	d = sqrt(d);
	_DBG_("the Distance moved by the Polulu robot is: ");
	_DBD(d); _DBG_("");
	return d;
}
/* Code taken from http://code.google.com/p/my-itoa/, for ease of use and lack of time*/
int my_itoa(int val, char* buf)
{
    const unsigned int radix = 10; // sets the base of the output

    char* p;
    unsigned int a;        //every digit
    int len;
    char* b;            //start of the digit char
    char temp;
    unsigned int u;
    p = buf;
    if (val < 0)
    {
        *p++ = '-';
        val = 0 - val;
    }
    u = (unsigned int)val;
    b = p;
    while (u > 0)
    {
        a = u % radix;
        u /= radix;
        *p++ = a + '0';
    } 
    len = (int)(p - buf);
    *p-- = 0;
    //swap
    while (b < p)
    {
        temp = *p;
        *p = *b;
        *b = temp;
        --p;
        ++b;
    }
    return len;
}

void printToLCD() {
 	int x = get_x_move();
	int y = get_y_move();
 	int	distance = distanceMoved(x, y);
	char buf[8];
	my_itoa(distance, buf);
	cmdLcdPrint(buf);
}

