#include "mouse.h"
#include "math.h"
#include "debug_frmwrk.h"
#include "uart.h"
#include "timer.h"
#include "KeyboardHost.h"
#include <stdlib.h>
#include "motors.h"
#include "JedIndividual.h"

const int r = 7;
double theta;
int32_t coord_x;
int32_t coord_y;
// when the mouse moves slow enough it can detect 1000 points per 10cm, so 10000 = 1m
void mouseinitial()
{
  _DBG_("I'm starting");
  coord_x =0;
	coord_y =0;
	theta =0;
  mouse_init(cb, attach, detach);
	coord_x =0;
	coord_y =0;
	theta =0;
  _DBG_("I've set up the mouse");
}
void myspecialpoll() {
 /*this has been moved in case there was an issue reaching the cb function when it was
 called from timer.c. This shouldn't be an issue however it has been very slow to react 
therefore we thought it best to remove it and place it here. This may not be the best way
of debugging but it seems to have worked,*/
  mouse_poll();
}

void overflowProtection(int8_t y, int8_t t)
{
	if( y > 125 || y < -125) {
		_DBG_("y has OVERFLOW");
		motorPair YrightMotorValues = getSpeedRight();
		motorPair YleftMotorValues = getSpeedLeft();
		brake();
		delay(1000000);
		resume(YrightMotorValues, YleftMotorValues);
	}
	if( -125 > t || t > 125) {
		_DBG_("t has OVERFLOW");
		motorPair TrightMotorValues = getSpeedRight();
		motorPair TleftMotorValues = getSpeedLeft();
		brake();
		delay(1000000);
		resume(TrightMotorValues, TleftMotorValues);
	}
}

double thetaOfArc(int32_t l, int32_t r) {
	double th = (l/r);
	return th;
}

int32_t converterForCm(int32_t x) {
	int32_t temp = 0;
	if(x%100 > 49){
		temp += 1;
		int i = x%100;
		x = x-i;
	}
	temp += (x/100);
	return temp;
}

int32_t convertToDeg(int32_t t) {
	int32_t temp = t * (180/M_PI);
	return temp;
}

void cb(uint8_t buttons, int8_t y, int8_t t) {

	static int32_t tempt;
	static int32_t tempy;
	static int32_t tempYCurve;
	static int32_t tempTCurve;
	static int state;
	static int prevState;
	printCoords(coord_x, coord_y, theta);
	checkMotion(y, t);
	//if there is a change in the t value only then the robot is spinning
	if(t != 0 && y == 0) {
		prevState = state;
		state = 1;
		overflowProtection(0, t);
		tempt += t;
		
		if (prevState == 2){
		  int32_t tempy2 = converterForCm(tempy);
		  add_to_x(tempy2);
		  add_to_y(tempy2);
		  tempy = 0;
		}
		else if (prevState == 3){
		  curve(converterForCm(tempYCurve), converterForCm(tempTCurve));
		  tempYCurve = 0;
		}
		
		if (tempt > 99){
		  double spinVal = thetaOfArc(converterForCm(tempt), r); 
		  theta = theta + spinVal; tempt = 0;
		}
	}
	
	//If there is a change in the y value only then the robot is moving forward
	if(y != 0 && t == 0) {
		prevState = state;
		state = 2;
		overflowProtection(y, 0);
		tempy += y;
		
		if (prevState == 1){
		  double spinVal = thetaOfArc(converterForCm(tempt), r);
		  theta = theta + spinVal; tempt = 0;
		}
		else if (prevState == 3){
		  curve(converterForCm(tempYCurve), converterForCm(tempTCurve));
		  tempYCurve = 0;
		}
		
		if (tempy > 99){
		  int32_t tempy2 = converterForCm(tempy);
		  add_to_x(tempy2);
		  add_to_y(tempy2);
		  tempy = 0;
		}
	}
	//If y and t are changing then the robot is moving in a curve
	if(t != 0 && y != 0) {
		prevState = state;
		state = 3;
		overflowProtection(y, t);
		tempYCurve += y;
		tempTCurve += t;
		if (prevState == 1){
		  double spinVal = thetaOfArc(converterForCm(tempt), r);
		  theta = theta + spinVal; tempt = 0;
		}
		else if (prevState == 2){
		  int32_t tempy2 = converterForCm(tempy);
		  add_to_x(tempy2);
		  add_to_y(tempy2);
		  tempy = 0;
		}
		if (tempYCurve > 99 && tempTCurve > 99){
		  curve(converterForCm(tempYCurve), converterForCm(tempTCurve));
		  tempYCurve = 0;
			tempTCurve = 0;
		}
	}
}


void curve(int y, int t) {
/**
The Idea of this method is to work out how far the robot has moved with respect to the x and y axis coordinates.
*/double th = (t/y); // gives us an angle theta, from the length of the arc traversed, y, and the constant, r, where r is the radius of a circle.
	double rad = (y/th);	//divides y by theta to get the radius of the circle that the arc is part of.
	double hyp_2 = sin(th) * rad; // gets sin(th) and multiplies it by r to get the hypotenuse, hyp_2, of the upper triangle 
	double y2 = hyp_2 * cos(th); // multiplies hyp_2 by the cosine of theta, to get an x value parrallel to the x axis of the overall coordinates
	double x2 = hyp_2 * sin(th); // multiplies hyp_2 by the sine of theta, to get an y value parrallel to the y axis of the overall coordinates
	double hyp_1 = rad - (cos(th) * rad); // gets cos(th) multplies it by r, then minusing r from the result of the multiplication to get the hypotenuse, hyp_1, of the lower triangle 
	double y1 = hyp_1 * sin(th);// multiplies hyp_1 by the cosine of theta, to get an x value parrallel to the x axis of the overall coordinates
	double x1 = hyp_1 * cos(th);// multiplies hyp_1 by the cosine of theta, to get an y value parrallel to the y axis of the overall coordinates
	theta += th;// add t to theta so the angle the robot now faces is known
	coord_x += (x2 - x1);// minus the value x1 (from the lower triangle) from x2 (from the upper triangle) together so the overall parrallel movement with respect to the x axis is known
	coord_y += (y2 + y1);// add y1 and y2 together where the total is how far forward or backward the robot has moved with respect to the y axis
}

void attach() {
	_DBG_("I'm attached, YAY!");
}

void detach() {
	_DBG_("I'm detached, BOO!");
	printCoords(coord_x, coord_y, convertToDeg(theta));
}

int32_t get_coord_x() {	
	return coord_x;
}

int32_t get_coord_y() {
	return coord_y;
}

int32_t get_theta() {
	return theta;
}

void forwardsfor50(){
	while (coord_y<50){
		forwards(15);
	}
	int32_t temp = get_coord_x();
	int32_t temp2 = get_coord_y();
	int32_t temp3 = convertToDeg(get_theta());
	printCoords(temp, temp2, temp3); 
	_DBG_("I've went 50");	
	brake();
}

void add_to_x(int8_t x) {
	coord_x += x * sin(theta); //x is multiplied by sin(theta) as direction the robot is facing can affect how far it actually moves along the x_axis
  if ((((int)coord_x % 50) >= 48) && (((int)coord_x %50) <= 2)) { ///@todo change to just % 50 if it works well
    cmdDoPlay(">>c");
  } 
}

void add_to_y(int8_t y) {
	coord_y += y * cos(theta);//y is multiplied by cos(theta) as direction the robot is facing can affect how far it actually moves along the y_axis

  if ((((int)coord_y % 50) >= 48) && (((int)coord_y %50) <= 2)) { ///@todo change to just % 50 if it works well
    cmdDoPlay(">>c");
  } 	
}

void printCoords(int32_t x, int32_t y, int32_t t) {
	distanceMoved(x, y);
	_DBG_("The coordinate position of the Pololu robot is: ( ");_DBD32(x);_DBG_(" , ");_DBD32(y);_DBG_(" , ");_DBD32(t);_DBG_(" )");

}

