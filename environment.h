/*********************************************************************//**
*	@file environment.h
*	@brief	 Checks the robots surrounding environment and informs the "state machine"
*          Also includes environment based sub-functions that are necessary for ensuring
*          stable results.
*
*	@author	Andrew Durant
* @author Christopher King
* @author Lloyd Wallis
*	@version: V1.0
*	@date:	10 March 2013
************************************************************************/

#ifndef ENVIRO_INC
#define ENVIRO_INC
/**
* contains the current X postion, starts at 0
*/
int trackingPositionX;
/**
* contains the current Y postion, starts at 0
*/
int trackingPositionY;
/**
* where in the course the robot is
*/
int trackingState;
/**
* Checks to see if there is a line underneath the robot using the raw sensors
*
* @author Andrew Durant (Initial Coding)
* @author Christopher King (Initial Coding)
*
* @return true or false
*/
int checkForLine();
/**
* Checks to see if there is not a line underneath the robot using the raw sensors
*
* @author Andrew Durant (Debug)
* @author Christopher King (Initial Coding)
*
* @return true or false
*/
int checkForNoLine();
/**
* Checks to see if there is a wall next to the robot using the IR sensors
*
* @author Andrew Durant (Initial Coding)
* @author Christopher King (Initial Coding)
*
* @return true or false
*/
int checkForWall();
/**
* if there is a wall next to the robot using the IR sensors and t
* a line underneath. If so you have entered a dock and therefore should stop
*
* @author Christopher King (Initial Coding)
*/
void dockBySensorsAndLine();
/**
* Sets the tracking position to a given x and y value
*
* @author Christopher King (Initial Coding)
* @author Lloyd Wallis (Debug)
*
* @param x the new X coordinate
* @param y the new Y coordinate
*/
void setTrackingPosition(int x, int y);
/**
* Checks to see if the coord is valid by ensuring that the sensors are stable
* If there is a blip in the sensor readings then the reading will not be passed
*
* @author Christopher King (Initial Coding)
* @author Lloyd Wallis (Debug)
*
* @param wallPosition  where should the wall be? 0 = wall infront of FS, 1 = wall infront of RS, anything else = no wall
* @return 1 or 0 depending on whether Sensors are stable (1) or they aren't (0)
*/
int checkForStableSensors(int wallPosition);
/**
* State machine that contains the next set coordinates. This then checks that the
* sensors are stable and continues to the next state
*
* @author Christopher King (Initial Coding)
* @author Lloyd Wallis (Debug)
*/
void setCoords() ;
/**
* Checks the difference between the mouse and the real position. If it differs
* by more than 10cm it will give us a pleasant beep to warn us
*
* @author Christopher King (Initial Coding)
* @author Lloyd Wallis (Debug)
*
* @param x the X coordinate that is being checked
* @param y the Y coordinate that is being checked
*/
void differenceBetweenMouseAndPosition(int x, int y) ;
/**
* enables tracking by mouse, should beep every 50 cm or so
*
* @author Andrew Durant (initial)
* @author Christopher King (revision - changed entire code with Lloyd Wallis)
* @author Lloyd Wallis (revision - changed entire code with Christopher King)
*/
void trackByMouse();

#endif
