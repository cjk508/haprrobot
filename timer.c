#include "debug_frmwrk.h"
#include "timer.h"
#include "mouse.h"

int motorState = 0;

void initTimer(LPC_TIM_TypeDef *TIMx, IRQn_Type IRQn, int time) {
	_DBG_("1");
	TIM_TIMERCFG_Type TimerConf = {
	.PrescaleOption = TIM_PRESCALE_USVAL, 
	.PrescaleValue = time};
	_DBG_("4");
	TIM_Init(TIMx, TIM_TIMER_MODE, &TimerConf);
	_DBG_("5");
	TIM_MATCHCFG_Type MatchConf = {
	.MatchChannel = 0,
	.IntOnMatch = ENABLE,
	.ResetOnMatch = ENABLE,
	.MatchValue = 1};
		_DBG_("10");
	TIM_ConfigMatch(TIMx,&MatchConf);
			_DBG_("11");
  NVIC_SetPriority(TIMER0_IRQn, ((0x01<<3)|0x01));
	NVIC_EnableIRQ(IRQn);
			_DBG_("12");
	TIM_Cmd(TIMx, ENABLE);
			_DBG_("13");
}

void initTimers() {
	//initTimer(LPC_TIM0, TIMER0_IRQn, 50);
	initTimer(LPC_TIM0, TIMER0_IRQn, 5000);
	_DBG_("TIMER SETUP");
}


void TIMER0_IRQHandler() {
  //DBG_("Timer called");
	 if(TIM_GetIntStatus(LPC_TIM0, TIM_MR0_INT) == SET)
    {
    //  _DBG_("MOUSE POLL should occur now");
	    myspecialpoll();
	  //  _DBG_("mouse polled");
    }
    TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
}


