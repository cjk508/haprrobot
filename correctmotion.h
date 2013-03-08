/***********************************************************//**
*	@file	correctmotion.h
*	@brief	Enables self-correction of movement when the 
*		robot should move parallel to an object
*
*	@author	Lloyd Wallis
*	@version: V0.6
*	@date:	27 February 2013
*
***************************************************************/		
#ifndef CORRECT_INC
#define CORRECT_INC					      
#include "sensors.h"
/**
* Gets the side that the sensor should use
*
* @author Christopher King
* @author Andrew Durant
* @return returns the sensor side
*/
int getSensorSide();
/**
* Sets the side that the sensor should use
*
* @author Christopher King
* @author Andrew Durant
* @param setSide The sensor side to set
*/
void setSensorSide(int setSide);
/**
* Uses the sensor that is passed to follow the wall.
* If the front sensor reads over 40 then it will move towards the wall
* If the rear sensor reads over 40 then nothing will happen.
* If the front sensor > rear sensor and both are below WALL_DISTANCE then turn towards wall
* If the front sensor < rear sensor and both are below WALL_DISTANCE then turn away from wall
*
* @author Christopher King
* @author Lloyd Wallis
* @param sensor sensor that will be used for wall following
*/
void wallFollow(SensorPair sensor);
/**
* Outputs the values of the sensor that is passed
*
* @author Christopher King
* @param sensor The sensor that will be debugged
*/
void debug_output(SensorPair sensor);

/**
* Gets the sensor values and then passes then on to
* wall follow if the front sensor is lower than 100
* @todo should then move away from it when front sensor 100 rear sensor 40
*
* @author Lloyd Wallis
* @author Christopher King
*/
void correctForwardMotion();
#endif

