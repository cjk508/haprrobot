#include <KeyboardHost.h>
#include <Math.h>

int32_t x_move;
int32_t y_move;
int y_direction_change = 1;

void cb(uint8_t buttons, int8_t X, int8_t Y) {
	//if there is a change in the Y value it is added to the integer y_move;
	if(Y != 0) {
		_DBG_("The Mouse has moved Left/right by: ");
		_DBC(Y);
		_DBG_("\n");
		y_move += Y;
		_DBG_("Value of y_move is: ");
		_DBC(y_move);
		_DBG_("\n");
		y_direction_change = cos(y_move);
	}
	
	//If there is a change in the X value it is added to the integer x_move;
	if(X != 0) {
		_DBG_("The Mouse has moved Forward/Backward by: ");
		_DBC(X);
		_DBG_("\n");
		x_move += X;
		_DBG_("Value of x_move is: ");
		_DBC(x_move);
		_DBG_("\n");
	}

}

void attach() {
	set_x_move(0);
	set_y_move(0);
}

void detach() {
	distanceMoved(x_move, y _move);
}

int32_t give_x_move() {	
	//Returns the value of x_move
	return x_move;
}

int32_t give_y_move() {
	//Returns the value of y_move
	return y_move;
}

void set_x_move(int8_t x) {
	x_move = x;
}

void set_y_move(int8_t y) {
	y_move = y;
}

int distanceMoved(int x, int y) {
	int d;
	d = ((x^2) + (y^2));
	d = sqrt(d);
	_DBG_("the Distance moved by the Polulu robot is: ");
	_DBC(d);
	return d;
}

//interrupt handler for mouse sensor, interrupts every 50ms to see change in values on the robot
void TIMER0_IRQHandler() {
	if(TIM_GetIntStatus(LPC_TIM0, TIM_MR0_INT) == SET)
    {
        mouse_poll();
    }
    TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
}

int main() {
	//Initialises mouse and runs the cb
	mouse_init(cb, attach, detach);
}
