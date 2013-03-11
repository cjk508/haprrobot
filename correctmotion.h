/***********************************************************//**
*	@file	correctmotion.h
*	@brief	Enables self-correction of movement when the 
*		robot should move parallel to an object
*
*	@author	Lloyd Wallis
* @author Christopher King
*	@version: V0.8
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
* @author Christopher King (changed to work with WALL_DISTANCE also debug)
* @author Lloyd Wallis (initial code & debug)
* @author Andrew Durant (debugger)
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
* Reads in side sensor values, and will automatically adjust with the intention
* of eventually moving parallel to the nearest object.
* Will adjust speed one unit left or right per invokation - repeated use over
* a period of a few seconds is best.
*
* @author Lloyd Wallis <lpw503@york.ac.uk> (initial coding)
* @author Christopher King (removed duplicated code and put it into wallfollow rather than checking for left and then right)
*/
void correctForwardMotion();
#endif

