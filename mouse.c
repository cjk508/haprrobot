#include <KeyboardHost.h>

int32_t x_move;
int32_t y_move;

void cb(uint8_t buttons, int8_t X, int8_t Y) {
	if(X != 0) {
		x_move += X;
	}
	if(Y != 0) {
		y_move += Y;
	}
	
}

void attach() {
	
}

void detach() {
	
}

int32_t give_x_move() {	
	return x_move;
}

int32_t give_y_move() {
	return y_move;
}

void TIMER0_IRQHandler() {
	if(TIM_GetIntStatus(LPC_TIM0, TIM_MR0_INT) == SET)
    {
        mouse_poll();
    }
    TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
}

int main() {
	mouse_init(cb, attach, detach);
}
