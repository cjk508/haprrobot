#include "timer.h"
#include "KeyboardHost.h"

int motorState = 0;

void initTimer(LPC_TIM_TypeDef *TIMx, IRQn_Type IRQn, int time) {
	TIM_TIMERCFG_Type TimerConf = {
	.PrescaleOption = TIM_PRESCALE_USVAL, 
	.PrescaleValue = time};

	TIM_Init(TIMx, TIM_TIMER_MODE, &TimerConf);

	TIM_MATCHCFG_Type MatchConf = {
	.MatchChannel = 0,
	.IntOnMatch = ENABLE,
	.ResetOnMatch = ENABLE,
	.MatchValue = 1};
	TIM_ConfigMatch(TIMx,&MatchConf);
	NVIC_EnableIRQ(IRQn);
	TIM_Cmd(TIMx, ENABLE);
}

void initTimers() {
	initTimer(LPC_TIM0, TIMER0_IRQn, 10000);
	initTimer(LPC_TIM2, TIMER2_IRQn, 50);
}


void TIMER0_IRQHandler() {
	motorStateMachine(motorState);
	motorState++;
	TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
	NVIC_ClearPendingIRQ(TIMER0_IRQn);
}

//interrupt handler for mouse sensor, interrupts every 50ms to see change in values on the robot
void TIMER2_IRQHandler() {
	if(TIM_GetIntStatus(LPC_TIM2, TIM_MR2_INT) == SET)
    {
	    mouse_poll();
    }
    TIM_ClearIntPending(LPC_TIM2, TIM_MR2_INT);
}




