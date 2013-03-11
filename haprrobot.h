/*********************************************************//**
*	@file haprrobot.h
*	@brief	Main file that intialises the sensors and uart. Then allows testing and the main files to run
*
*	@version V1.0
*	@author Andrew Durant
*	@author Christopher King
*	@author Jed Warwick-Mooney
*	@author Lloyd Wallis
*
*	@date 03 March 2013
*
*/
/**
* @brief 0 short course goes straight on to dock 
*        1 is long course, bears right after left wall to find the right wall.
*/
int courseType;
/**
* Enables tools to override the next state
*/
int stateOverride;
/**
* Enables interrupts to request the state machine to abort current operation
* and reevaluate transitions
*/
int abortMode;
/**
 * Runs all the initialisations that are needed
 * Please put them in here.
 */
void initialise();

void doATest();

int doTheDemo();

void main(void);







