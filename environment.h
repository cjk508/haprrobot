#ifndef ENVIRO_INC
#define ENVIRO_INC

/**
* Checks to see if there is a line underneath the robot using the raw sensors
*
* @author Andrew Durant
* @author Christopher King
*
* @return true or false
*/
int checkForLine();
/**
* Checks to see if there is a wall next to the robot using the IR sensors
*
* @author Andrew Durant
* @author Christopher King
*
* @return true or false
*/
int checkForWall();

#endif
