

#ifndef TIMER
#define TIMER

/**
* Initialises the timer interrupt for the robot setting the
* prescale value to the integer timer
*
* @author Jed Warwick-Mooney
* @param int timer
*/
void init_TIMER(int timer);
/**
* The interrupt handler for the robot
*
* @author Jed Warwick-Mooney
*/
void TIMER0_IRQHandler();

#endif
