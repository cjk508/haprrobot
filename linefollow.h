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
*	returns the raw sensor values of the line sensors
*
* @author Christopher King
*/
char[] useRawSensors(void);
//----------------------------------------------------------------
/**
*	returns the Calibrated sensor values of the line sensors
*
* @author Christopher King
*/
char[] useCalibratedSensors(void);
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
