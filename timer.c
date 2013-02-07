#include "lpc17xx_timer.h"
#include "lpc17xx_clkpwr.h"

#include "motors.h"

int motorState = 0;
void init_TIMER(int timer)
{
	TIM_TIMERCFG_Type TimerConf = {
	.PrescaleOption = TIM_PRESCALE_USVAL, 
	.PrescaleValue = timer};
	
	TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &TimerConf);
	
	TIM_MATCHCFG_Type MatchConf = {
	.MatchChannel = 0,
	.IntOnMatch = ENABLE,
	.ResetOnMatch = ENABLE,
	.MatchValue = 1};
	TIM_ConfigMatch(LPC_TIM0,&MatchConf);
	NVIC_EnableIRQ(TIMER0_IRQn);
	__enable_irq();
	TIM_Cmd(LPC_TIM0, ENABLE);
}

void TIMER0_IRQHandler() {
	motorStateMachine(motorState);
	motorState++;
	TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
	NVIC_ClearPendingIRQ(TIMER0_IRQn);
}


