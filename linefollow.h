/**************************************************************************//**
 * @file     linefollow.h
 * @brief    Should allow the robot to follow a line. Currently all it does is analyse 
 *           an intersection
 * @version: V0.6
 * @date:    03 March 2013
 ******************************************************************************/
#ifndef LINE_FOLLOW
#define LINE_FOLLOW
//----------------------------------------------------------------
/**
 *  This function should calibrate the line following sensors.
 *
 *  @author Christopher King <cjk508@york.ac.uk>
 */
uint32_t calibrateSensors(void)
//----------------------------------------------------------------
/**
*	Main function which follows the line and analyses what it finds
*
* @author Christopher King <cjk508@york.ac.uk>
*/
void lineMotors();

#endif


