/* Straight-line correction library for m3pi
 * Lloyd Wallis
 * 
 * Enables self-correction of movement when the robot should move
 * parallel to an object
 *
 */

/**
* Compares the current motor speeds and sensor values
* It will adjust the motor speeds depending if necessary
* The aim is to keep the robot in a straight line
*
* @author Lloyd Wallis
*/
void correctForwardMotion();

