#ifndef LINE_FOLLOW
#define LINE_FOLLOW
/**
* @brief enum for intersection analysis
*
* Will be able help the code be more readable for intersection names
*
* @author Christopher King
*/
typedef enum {LEFT, RIGHT, LEFT_STRAIGHT, RIGHT_STRAIGHT, CROSS, LEFT_RIGHT} intersection_enum;
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
//----------------------------------------------------------------
/**
*	This should return whether the 
*
* @author Christopher King
* @return will return which intersection we have come across
*/
intersection_enum intersectionAnalysis();
#endif
