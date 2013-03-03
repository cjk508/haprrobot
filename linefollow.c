#include "motors.h"
#include "uart.h"
#include "debug_frmwrk.h" 
#include "linefollow.h"

void calibrateSensors(void)
{
 /*this automatically calibrates the line following sensors. It scans left and 
  right in an attempt to find the line. This should be called when the raw sensors
  indicate that a line is present under the robot.*/
  cmdAutoCal();
}

void getRawSensors(uint16_t*  sens)
{
  _DBG_("attempt to get sensor values");
  uint32_t status = cmdRawSens(sens);
  _DBG_("Got sensor values");  
  /**
  *@todo need to work out whether 0 is black or 1000
  *      once this have been sussed out then it will 
         attempt to look for a black floor. It will
         then calibrate and use the line follow command
         It will keep searching for the "barcode" throughout     
  */
}
void getCalibratedSensors(uint16_t *sens)
{
  uint32_t status = cmdCalSens(sens);
/**  if(buffer arrays are white)
  {
    //try to find the line
  }
  else
  {
    //follow the line
    cmdLinePosition(); //nneds to implemented in uart.c
  if the read in i between 0-1000 then we are to the right of the line
    if it is between 1000 and 3000 then we are approx centre 
    if it is between 3000 and 4000 then it is to the far left of the robot

  }
  *@todo need to work out whether 0 is black or 2000
  *      once this have been sussed out then it will 
         attempt to look for a black floor. It will
         then calibrate and use the line follow command
         It will keep searching for the "barcode" throughout     

  return *buf;*/
}
void inchForward()
{
 /**
  * @todo not sure if this should be in motor.c rather than in here as it is technically to do with the motors.
  */
  int i = 0;
  forwards(25);
  while (i < 10000)
  {  
    i = i+1;
  }
  brake(); 
}

intersection_enum scanForDeadEnd()
{
 /**@todo need to check the sensor patterns when going over a line. I highly doubt it'll be as simple as 1 for a line and 0 for no line, although that is what the documentation suggests in the pololu how to follow a line thingy.*/
  uint16_t* sensorPattern = {0};
  getRawSensors(sensorPattern);
  char left = '1';
  char right = '1';
  int i = 0;
  spinLeft();
  while (i<400)
  {
    i = i + 1;
  }
  brake();
  
  //uint16_t desiredPattern[5] = {1,1,1,0,0};
  if (!sensorPatternChecker(sensorPattern, (uint16_t*){1,1,1,0,0}))
    left = '0';
  i = 0;    
  spinRight();
  while (i<400)
  {
    i = i + 1;
  }
  brake();
  if (!sensorPatternChecker(sensorPattern, (uint16_t* ){0,0,1,1,1}))
    right = '0';
    
  if (!left && !right)
    return DEAD_END;
  else if (!left)
    return RIGHT;
  else if (!right)
    return LEFT;
  else
    return LEFT_RIGHT; 
}

int sensorPatternChecker(uint16_t sensorPattern[], uint16_t desiredPattern[])
{
	// This is to try and get round the sensor checking if statement problems, failing to analyse {0,0,0,0,0} properly
	int lengthSensors = sizeof(sensorPattern);
	int lengthDesired = sizeof(desiredPattern);
	int returnChecker = 0; //this will be incremented with each correct value. If it = 5 by the end then it will return 1
	if (lengthSensors == lengthDesired)
	{
		int i = 0;
		while (i<=lengthSensors)
		{
			if (sensorPattern[i] == desiredPattern[i])
				returnChecker += 1;			
		}
		if (returnChecker == lengthDesired)
			return 1;
		else
			return 0;
	}
	else
		return 0;
}

intersection_enum intersectionAnalysis()
{
  /**
   * @todo try and find a decent way of passing the desired pattern rather than using casting
   */
  uint16_t sensorPattern[5] = {0};
  brake();
  intersection_enum intersectionType;
  if (sensorPatternChecker(sensorPattern,(uint16_t*){0,0,0,0,0})) //Nothing in front or to the side of the robot
    intersectionType = scanForDeadEnd();
  else if (sensorPatternChecker(sensorPattern,(uint16_t*){1,1,1,0,0} ))//Line to the left and infront of the robot
  {
    inchForward();
    intersection_enum futureTurn = intersectionAnalysis();
    if (futureTurn == DEAD_END)
      intersectionType = LEFT;
    else
      intersectionType = LEFT_STRAIGHT;
  }
  else if (sensorPatternChecker(sensorPattern, (uint16_t*){0,0,1,1,1}))//Line to the right and infront of the robot
  {
    inchForward();
    intersection_enum futureTurn = intersectionAnalysis();
    if( futureTurn == DEAD_END)
      intersectionType = RIGHT;
    else
      intersectionType = RIGHT_STRAIGHT;
  }  
  else if (sensorPatternChecker(sensorPattern,(uint16_t*) {1,1,1,1,1})) //Line to the left, right and in front of the robot.
     intersectionType = CROSSROAD;
   return CROSSROAD;
}
