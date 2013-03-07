#include "mouse.h"
#include "math.h"
#include "debug_frmwrk.h"
#include "uart.h"
#include "timer.h"
#include "KeyboardHost.h"
#include <stdlib.h>
#include "motors.h"

const int r = 7;
int32_t theta;
int32_t coord_x;
int32_t coord_y;
int actTheta;
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
	if( x > 125 || x < -125) {
		_DBG_("x has OVERFLOW");
		struct motorPair XrightMotorValues = getSpeedRight();
		struct motorPair XleftMotorValues = getSpeedLeft();
		brake();
		delay();
		resume(XrightMotorValues, XleftMotorValues);
	}
	if( -125 > t || t > 125) {
		_DBG_("t has OVERFLOW");
		struct motorPair TrightMotorValues = getSpeedRight();
		struct motorPair TleftMotorValues = getSpeedLeft();
		brake();
		delay();
		resume(TrightMotorValues, TleftMotorValues);
	}
}

int32_t thetaOfArc(int32_t l, int32_t r) {
	int32_t th = l/r;
	return th;
}

void converterForTheta() {
	if(theta>0){
		while(theta>4){
			theta = theta - 4;
			actTheta+=1;
		}
	}
	else {
		while(theta<(-4)){
			theta = theta + 4;
			actTheta-=1;
		}	
	}
}

int32_t converterForCm(int32_t x) {
	int32_t temp = x/100;
	if(x%100 > 49) temp += 1;
	return temp;
}

void cb(uint8_t buttons, int8_t x, int8_t t) {
/**
* @todo put some form of overflow protection to make sure that we are getting fairly accurate results.
*/
	
	//if there is a change in the t value only then the robot is spinning;
	if(t != 0 && x == 0) {
	int32_t tempt = 0;
		while(t != 0 && x == 0) {
			overflowProtection(x, 0);
			tempt += t;
		}
		int32_t spinVal = thetaOfArc(converterForCm(tempt), r);
		theta = theta + spinVal; 
	}
	
	//If there is a change in the x value only then the robot is moving forward;
	if(x != 0 && t == 0) {
	int32_t tempx = 0;
		while(t == 0 && x != 0) {
			overflowProtection(x, 0);
			tempx += x;
		}
		x = converterForCm(tempx);
		add_to_x(x);
		add_to_y(x);
	}

	if(t != 0 && x != 0) {
	int32_t tempx = 0;
		while(t != 0 && x != 0) {
			overflowProtection(x, t);
			tempx += x;
		}
		curve(tempx);
	}
}

void curve(int x) {
/**
The Idea of this method is to work out how far the robot has moved with respect to the x and y axis coordinates.
*/
	int32_t th = thetaOfArc(converterForCm(x), r); // gives us an angle theta, from the length of the arc traversed, x, and the constant, r, where r is the radius of a circle.
	int hyp_2 = sin(th) * r; // gets sin(th) and multiplies it by r to get the hypotenuse, hyp_2, of the upper triangle 
	int x2 = hyp_2 * cos(th); // multiplies hyp_2 by the cosine of theta, to get an x value parrallel to the x axis of the overall coordinates
	int y2 = hyp_2 * sin(th); // multiplies hyp_2 by the sine of theta, to get an y value parrallel to the y axis of the overall coordinates
	int hyp_1 = r - (cos(th) * r); // gets cos(th) multplies it by r, then minusing r from the result of the multiplication to get the hypotenuse, hyp_1, of the lower triangle 
	int x1 = hyp_1 * sin(th);// multiplies hyp_1 by the cosine of theta, to get an x value parrallel to the x axis of the overall coordinates
	int y1 = hyp_1 * cos(th);// multiplies hyp_1 by the cosine of theta, to get an y value parrallel to the y axis of the overall coordinates
	theta += th;// add t to theta so the angle the robot now faces is known
	coord_x += (x1 + x2);// add the values of x1 and x2 together so the overall parrallel movement with respect to the x axis is known
	coord_y += (y2 - y1);// minus y1 (from the lower triangle) from y2( from the upper triangle) where the difference is how far left or right the robot has moved with respect to the y axis
}

void attach() {
	coord_x = 0;
	coord_y = 0;
	theta = 0;
	_DBG_("I'm attached, YAY!");
}

void detach() {
	_DBG_("I'm detached, BOO!");
	distanceMoved(coord_x, coord_y);
}

int32_t get_coord_x() {	
	//Returns the value of x_move
	return coord_x;
}

int32_t get_coord_y() {
	//Returns the value of y_move
	return coord_y;
}

void add_to_x(int8_t x) {
	coord_x += x * cos(theta); //x is multiplied by cos(theta) as direction the robot is facing can affect how far it actually moves along the x_axis
}

void add_to_y(int8_t y) {
	coord_y += y * sin(theta);//y is multiplied by sin(theta) as direction the robot is facing can affect how far it actually moves along the y_axis
}

/** @todo Is this alright? Code taken from http://code.google.com/p/my-itoa/, for ease of use and lack of time
*   @todo If not using in group project remove. Pop in indivual side if you want to use it.
*/
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

void distanceMoved(int x, int y) {
	int d;
	d = ((x^2) + (y^2)); //pythagarus theorem used to work out overall distance moved from orignal start point
	d = sqrt(d);
	_DBG_("The coordiante position of the Polulo robot is: ( ";_DBD(x);_DBG_" , ";_DBD(y);_DBG_" )";
	_DBG_("The total distance moved by the Polulu robot is: ");
	_DBD(d); _DBG_("");
}

