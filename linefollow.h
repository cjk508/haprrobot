/**************************************************************************//**
 * @file     linefollow.h
 * @brief    Should allow the robot to follow a line. Currently all it does is analyse 
 *           an intersection
 * @version: V0.6
 * @date:    03 March 2013
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
void getRawSensors(uint16_t* sens);
//----------------------------------------------------------------
/**
*	returns the Calibrated sensor values of the line sensors
*
* @author Christopher King
* @return This method retruns the current values that the calibrated sensors believe.
*/
void getCalibratedSensors(uint16_t* sens);
//----------------------------------------------------------------
/**
*	moves forward by a very small amount to test if the intersection
* is a turn only or a turn and straight on
*
* @author Christopher King
*/
void inchForward(void);
//----------------------------------------------------------------
/**
*	checks to see whether an end to the line is a dead end or a left/right
* T-junction. 
*
* @author Christopher King
* @return DEAD_END or turn type 
*/
//intersection_enum scanForDeadEnd(void)
//----------------------------------------------------------------
/**
 * For a given input it will check it against the desired pattern to whether they are equivalent
 *
 * @author Christopher King
 * @param	sensorPattern	this is the pattern that the if statements want to check.
 * @param	desiredPattern	this is the pattern that the if statement wants to check against
 * @return returns either a 1 or a 0 depending on whether the input pattern matches the desired pattern.
 */
int sensorPatternChecker(uint16_t sensorPattern[], uint16_t desiredPattern[]);
//----------------------------------------------------------------
/**
*	This should return whether the 
*
* @author Christopher King
* @return will return which intersection we have come across
*/
intersection_enum intersectionAnalysis(void);
#endif
