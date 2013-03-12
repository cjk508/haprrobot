#include "motors.h"
#include "uart.h"
#include "debug_frmwrk.h" 
#include "linefollow.h"
#include "environment.h"
/**
* @brief enum for intersection analysis
*
* Will be able help the code be more readable for intersection names
*
* @author Christopher King <cjk508@york.ac.uk>
*/
typedef enum {LEFT, RIGHT, LEFT_STRAIGHT, RIGHT_STRAIGHT, CROSSROAD, LEFT_RIGHT, DEAD_END, NONE} intersection_enum;
;
//----------------------------------------------------------------
/**
*	returns the raw sensor values of the line sensors
*
* @author Christopher King <cjk508@york.ac.uk>
* @param sensorPattern This method returns the current values that the raw sensors are transmitting
*/
void getRawSensors(uint16_t* sensorPattern);
//----------------------------------------------------------------
/**
*	returns the Calibrated sensor values of the line sensors
*
* @author Christopher King <cjk508@york.ac.uk>
* @param sensorPattern This method retruns the current values that the calibrated sensors believe.
*/
void getCalibratedSensors(uint16_t* sensorPattern);
//----------------------------------------------------------------
/**
*	moves forward by a very small amount to test if the intersection
* is a turn only or a turn and straight on
*
* @author Christopher King <cjk508@york.ac.uk>
* @param junctionType This is the type of junction which needs to be analysed
* @param  sensorPattern current sensor readings
*/
void inchForward(intersection_enum junctionType ,uint16_t* sensorPattern);
//----------------------------------------------------------------
/**
 * For a given input it will check it against the desired pattern to whether they are equivalent
 *
 * @author Christopher King <cjk508@york.ac.uk>
 * @param	sensorPattern	this is the pattern that the needs to be normalised to 1s and 0s.
 */
void patternNormaliser(uint16_t* sensorPattern);
//----------------------------------------------------------------
/**
*	This should return the junction type
*
* @author Christopher King <cjk508@york.ac.uk>
* @param  sensorPattern current sensor readings
* @return will return which intersection we have come across
*/
intersection_enum analyseJunction(uint16_t* sensorPattern);
//----------------------------------------------------------------
/**
*	Spins left until sensorPattern[2] == 1 which should mean its spun until it's centred on a new line
*
* @author Christopher King <cjk508@york.ac.uk>
* @param  sensorPattern current sensor readings
*/
void lineSpinLeft(uint16_t* sensorPattern);
//----------------------------------------------------------------
/**
*	Spins right until sensorPattern[2] == 1 which should mean its spun until it's centred on a new line
*
* @author Christopher King <cjk508@york.ac.uk>
* @param  sensorPattern current sensor readings
*/
void lineSpinRight(uint16_t* sensorPattern);
//----------------------------------------------------------------
/**
*	Should correct forward movement if it goes astray
*
* @author Christopher King <cjk508@york.ac.uk>
* @param  sensorPattern current sensor readings
*/
void mazeFollow();
