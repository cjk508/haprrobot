

#ifndef TIMER
#define TIMER

#include "lpc17xx_timer.h"
#include "lpc17xx_clkpwr.h"

#include "motors.h"
#include "mouse.h"

void initTimer(LPC_TIM_TypeDef *TIMx, IRQn_Type IRQn, int time);

void initTimers();

/**
* Initialises the timer interrupt for the robot setting the
* prescale value to the integer timer
*
* @author Jed Warwick-Mooney
* @param int timer
*/
/**
* The interrupt handler for the robot
*
* @author Jed Warwick-Mooney
*/
void TIMER0_IRQHandler();
/**
* Interrrupt handler for the tracking of the robots movement
* from its original position
*
*/
void TIMER2_IRQHandler();

#endif
