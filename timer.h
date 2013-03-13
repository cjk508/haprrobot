/***********************************************************//**
*	@file	timer.h
*	@brief	Allows easy set up of timers for use in the mouse and motion.	
*
*	@author Andrew Durant
*	@author Jed Warwick-Mooney
*	@version: V2.0
*	@date 20 February 2013
**************************************************************/

#ifndef TIMER
#define TIMER

#include "lpc17xx_timer.h"
#include "lpc17xx_clkpwr.h"

#include "motors.h"
#include "mouse.h"
/**
 * Initially was used as a counter to state when the line following
 * realised there was a blob of black tape. However as this became unnecessary
 * it has remained as 'lotsOfBlackTape' purely because we have't renamedit.
 *
 * It now is used as a counter for the delay function to count how many times
 * Timer0 has ticked.
 */
int timerCounter;
/**
* Timer interrupt initialisation abstraction.
* Sets up a timer interupt from the given parameters
* Allows multiple timers to be created easily, however timer1 
* throws an error and timer2 doesn't work...
*
* @author Andrew Durant (Initial Coding)
* @author Jed Warwick-Mooney (Revision - removed timer 2)
* @param TIMx the timer to setup
* @param IRQn the interupt to fire
* @param time the time in ms the interupt fires at
*/
void initTimer(LPC_TIM_TypeDef *TIMx, IRQn_Type IRQn, int time);

/**
* Initialises the timers for the robot Timer1
* @author Jed Warwick-Mooney (Initial Coding)
*/
void initTimers();
/**
* The timer over multiple interrupts
*
* @author Andrew Durant (Initial Coding)
* @author Christopher King (Debug and revision changed to actually work)
* @param time The length of time you wish to delay by
*/
void delay(int time);
/**
* Interrrupt handler for the mouse sensor. Should interrupt every 10ms
* and runs method myspecialpoll()
* @author Jed Warwick-Mooney (Initial Coding)
* @author Christopher King (added the timerCounter for a delay function to work)
*
*/
void TIMER0_IRQHandler();

#endif
