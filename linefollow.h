/**************************************************************************//**
 * @file     linefollow.h
 * @brief    Should allow the robot to follow a line. Currently all it does is analyse 
 *           an intersection
 * @version: V0.2
 * @date:    21. February 2013
 ******************************************************************************/
#ifndef LINE_FOLLOW
#define LINE_FOLLOW
/**
* @brief enum for intersection analysis
*
* Will be able help the code be more readable for intersection names
*
* @author Christopher King
*/
typedef enum {LEFT, RIGHT, LEFT_STRAIGHT, RIGHT_STRAIGHT, CROSSROAD, LEFT_RIGHT, DEAD_END} intersection_enum;
//----------------------------------------------------------------
/**
 *  This function should calibrate the line following sensors.
 *
 *  @author Christopher King
 */
void calibrateSensors(void);
//----------------------------------------------------------------
/**
*	returns the raw sensor values of the line sensors
*
* @author Christopher King
* @return This method returns the current values that the raw sensors are transmitting
*/
char[] getRawSensors(void);
//----------------------------------------------------------------
/**
*	returns the Calibrated sensor values of the line sensors
*
* @author Christopher King
* @return This method retruns the current values that the calibrated sensors believe.
*/
char[] getCalibratedSensors(void);
//----------------------------------------------------------------
/**
*	moves forward by a very small amount to test if the intersection
* is a turn only or a turn and straight on
*
* @author Christopher King
*/
void inchForward();
//----------------------------------------------------------------
/**
*	checks to see whether an end to the line is a dead end or a left/right
* T-junction. 
*
* @author Christopher King
* @return DEAD_END or turn type 
*/
intersection_enum scanForDeadEnd()
//----------------------------------------------------------------
/**
*	This should return whether the 
*
* @author Christopher King
* @return will return which intersection we have come across
*/
intersection_enum intersectionAnalysis();
#endif
