#ifndef LINE_FOLLOW
#define LINE_FOLLOW
//----------------------------------------------------------------
/**
*	returns the raw sensor values of the line sensors
*
* @author Christopher King
*/
void useRawSensors(void);
//----------------------------------------------------------------
/**
*	returns the Calibrated sensor values of the line sensors
*
* @author Christopher King
*/
void useCalibratedSensors(void);
//----------------------------------------------------------------
/**
*	moves forward by a very small amount to test if the intersection
* is a turn only or a turn and straight on
*
* @author Christopher King
*/
void inchForward();

#endif
