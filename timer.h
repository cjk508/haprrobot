#ifndef TIMER
#define TIMER

#include "lpc17xx_timer.h"
#include "lpc17xx_clkpwr.h"

#include "motors.h"
#include "mouse.h"
/**
*	Initialises a timer according to the inputs
*
* @author Jed Warwick-Mooney
* @param *TIMx 
* @param *IRQn sets the mode the timer is in according to the timer number
* @param time the length of time 
*
*/

void initTimer(LPC_TIM_TypeDef *TIMx, IRQn_Type IRQn, int time);
/**
* Initialises the timer interrupts for the robot setting the
* prescale values to the integer timers
*
* @author Jed Warwick-Mooney
* 
*/

void initTimers();

/**
* The interrupt handler for the robots state machine
*
* @author Jed Warwick-Mooney
*
*/
void TIMER0_IRQHandler();
/**
* Interrrupt handler for the tracking of the robots movement
* from its original position
*
* @author Jed Warwick-Mooney
*
*/
void TIMER2_IRQHandler();

#endif
