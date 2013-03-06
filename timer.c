#include "debug_frmwrk.h"
#include "timer.h"
#include "mouse.h"

int motorState = 0;
int lotsOfBlackTape = 0;

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
  NVIC_SetPriority(TIMER0_IRQn, ((0x01<<3)|0x01));
	NVIC_EnableIRQ(IRQn);
	TIM_Cmd(TIMx, ENABLE);
}

void initTimers() {
	initTimer(LPC_TIM0, TIMER0_IRQn, 1000);
	_DBG_("TIMER SETUP");
}

int getLotsOfBlackTape()
{
  return lotsOfBlackTape;
}

void TIMER0_IRQHandler() {
  //DBG_("Timer called");
	 if(TIM_GetIntStatus(LPC_TIM0, TIM_MR0_INT) == SET)
    {
    //  _DBG_("MOUSE POLL should occur now");
	    myspecialpoll();
	    if(lotsOfBlackTape <350)
  	    lotsOfBlackTape +=1;
  	  else
  	    lotsOfBlackTape = 0;
	  //  _DBG_("mouse polled");
    }
    TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
}



