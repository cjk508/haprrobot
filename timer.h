

#ifndef TIMER
#define TIMER

#include "lpc17xx_timer.h"
#include "lpc17xx_clkpwr.h"

#include "motors.h"
#include "mouse.h"


/**
* Timer interupt initialisation abstraction.
* Sets up a timer interupt from the given parameters
*
* @param TIMx the timer to setup
* @param IRQn the interupt to fire
* @param time the time in ms the interupt fires at
*/
void initTimer(LPC_TIM_TypeDef *TIMx, IRQn_Type IRQn, int time);

/**
* Initialises the timers for the robot.
* Timer1 and Timer2
*/
void initTimers();

/**
* The interrupt handler for the robot
*
* @author Jed Warwick-Mooney
*/
void TIMER0_IRQHandler();

/**
* Interrrupt handler for the mouse sensor.
* Helps with tracking of the robots movement
* from its original position
*
*/
void TIMER2_IRQHandler();

#endif
