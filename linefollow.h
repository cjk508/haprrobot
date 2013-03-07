/**************************************************************************//**
 * @file     linefollow.h
 * @brief    Should allow the robot to follow a line. Currently all it does is analyse 
 *           an intersection
 * @version: V0.6
 * @date:    03 March 2013
 ******************************************************************************/
#ifndef LINE_INC
#define LINE_INC
//----------------------------------------------------------------
/**
 *  This function should calibrate the line following sensors.
 *
 *  @author Christopher King <cjk508@york.ac.uk>
 */
uint32_t calibrateSensors(void);
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
*	Main function which follows the line
*
* @author Christopher King <cjk508@york.ac.uk>
*/
void followLine();

#endif


