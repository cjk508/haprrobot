#include "mouse.h"
#include "math.h"
#include "debug_frmwrk.h"
#include "uart.h"

const int r = 10;
int32_t x_move;
int32_t y_move;
int theta;

void cb(uint8_t buttons, int8_t x, int8_t t) {
	//if there is a change in the t value only then the robot is spinning;
	if(t != 0 && x == 0) {
		_DBG_("The Mouse has moved Left/right by: ");
		_DBC(t);
		_DBG_("\n");
		theta += spin(t, r);
		_DBG_("Value of theta is: ");
		_DBC(theta);
		_DBG_("\n");
	}
	
	//If there is a change in the x value only then the robot is moving forward;
	if(x != 0 && t == 0) {
		_DBG_("The Mouse has moved Forward/Backward by: ");
		_DBC(x);
		_DBG_("\n");
		add_to_x(x);
		add_to_y(x);
		_DBG_("Value of x_move is: ");
		_DBC(x_move);
		_DBG_("\n");
	}

	if(t != 0 && x != 0) {
	_DBG_("Moving in a curve");
	_DBG_("\n");
	curve(x);
	_DBG_("Value of x_move is: ");
	_DBC(x_move);
	_DBG_("\n");
  _DBG_("Value of y_move is: ");
	_DBC(y_move);
	_DBG_("\n");
	}

}

void curve(int x) {
	int t = spin(x, r);
	int hyp_y = sin(t) * r;
	int hyp_z = cos(t) * r;
	int y2 = hyp_y * sin(t);
	int x2 = hyp_y * cos(t);
	int hyp_x = r - hyp_z;
	int x1 = hyp_x * sin(t);
	int y1 = hyp_x * cos(t);
	theta += t;
	add_to_x(x1 + x2);
	add_to_y(y2 - y1);
}

int spin(int l, int r) {
	int th = l/r;
	return th;
}

void attach() {
	x_move = 0;
	y_move = 0;
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
	x_move += x * cos(theta);
}

void add_to_y(int8_t y) {
	y_move += y * sin(theta);
}

int distanceMoved(int x, int y) {
	int d;
	d = ((x^2) + (y^2));
	d = sqrt(d);
	_DBG_("the Distance moved by the Polulu robot is: ");
	_DBC(d); _DBG_("");
	return d;
}

void printToLCD() {
	int x = get_x_move();
	int y = get_y_move();
 	int	distance = distanceMoved(x, y);
	char buf[8];
//	itoa(distance, buf, 10);
//	cmdLcdPrint(buf);
}

