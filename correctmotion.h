/***********************************************************//**
*	@file	correctmotion.c
*	@brief	Enables self-correction of movement when the 
*		robot should move parallel to an object
*
*	@author	Lloyd Wallis
*	@version: V0.6
*	@date:	27 February 2013
*
***************************************************************/							      

/**
* Compares the current motor speeds and sensor values
* It will adjust the motor speeds depending if necessary
* The aim is to keep the robot in a straight line
*
* @author Lloyd Wallis
*/
void correctForwardMotion();

