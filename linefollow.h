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
typedef enum {LEFT, RIGHT, LEFT_STRAIGHT, RIGHT_STRAIGHT, CROSSROAD, LEFT_RIGHT, DEAD_END, NONE} intersection_enum;

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
* @param sensorPattern This method returns the current values that the raw sensors are transmitting
*/
void getRawSensors(uint16_t* sensorPattern);
//----------------------------------------------------------------
/**
*	returns the Calibrated sensor values of the line sensors
*
* @author Christopher King
* @param sensorPattern This method retruns the current values that the calibrated sensors believe.
*/
void getCalibratedSensors(uint16_t* sensorPattern);
//----------------------------------------------------------------
/**
*	moves forward by a very small amount to test if the intersection
* is a turn only or a turn and straight on
*
* @author Christopher King
* @param junctionType This is the type of junction which needs to be analysed
*/
void inchForward(intersection_enum junctionType,uint16_t* sensorPattern);
//----------------------------------------------------------------
/**
 * For a given input it will check it against the desired pattern to whether they are equivalent
 *
 * @author Christopher King
 * @param	sensorPattern	this is the pattern that the needs to be normalised to 1s and 0s.
 */
void patternNormaliser(uint16_t* sensorPattern);
//----------------------------------------------------------------
/**
*	This should return the junction type
*
* @author Christopher King
* @param  sensorPattern current sensor readings
* @return will return which intersection we have come across
*/
intersection_enum analyseJunction(uint16_t* sensorPattern);
//----------------------------------------------------------------
/**
*	Main function which follows the line and analyses what it finds
*
* @author Christopher King
*/
void lineMotors();
//----------------------------------------------------------------
/**
*	Spins left until sensorPattern[2] == 1 which should mean its spun until it's centred on a new line
*
* @author Christopher King
* @param  sensorPattern current sensor readings
*/
void lineSpinLeft(uint16_t* sensorPattern);
//----------------------------------------------------------------
/**
*	Spins right until sensorPattern[2] == 1 which should mean its spun until it's centred on a new line
*
* @author Christopher King
* @param  sensorPattern current sensor readings
*/
void lineSpinRight(uint16_t* sensorPattern);
//----------------------------------------------------------------
/**
*	Should correct forward movement if it goes astray
*
* @author Christopher King
* @param  sensorPattern current sensor readings
*/
void lineFollowForward(uint16_t* sensorPattern);
#endif


