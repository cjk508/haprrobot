#include "motors.h"
#include "uart.h"
#include "linefollow.h"

void calibrateSensors(void)
{
 /*this automatically calibrates the line following sensors. It scans left and 
  right in an attempt to find the line. This should be called when the raw sensors
  indicate that a line is present under the robot.*/
  cmdAutoCal();
}

char[] getRawSensors(void)
{
  char *buf[10];
  uint32_t status = cmdRawSens(*buf);
  return *buf;
  /**
  *@todo need to work out whether 0 is black or 1000
  *      once this have been sussed out then it will 
         attempt to look for a black floor. It will
         then calibrate and use the line follow command
         It will keep searching for the "barcode" throughout     
  */
}

char[] getCalibratedSensors(void)
{
  char *buf[10];
  uint32_t status = cmdCalSens(*buf);
  if(/*buffer arrays are white*/)
  {
    //try to find the line
  }
  else
  {
    //follow the line
    cmdLinePosition(); //nneds to implemented in uart.c
  /*if the read in i between 0-1000 then we are to the right of the line
    if it is between 1000 and 3000 then we are approx centre 
    if it is between 3000 and 4000 then it is to the far left of the robot
  */
  }
  /**
  *@todo need to work out whether 0 is black or 2000
  *      once this have been sussed out then it will 
         attempt to look for a black floor. It will
         then calibrate and use the line follow command
         It will keep searching for the "barcode" throughout     
  */  
  return *buf;
}
void inchForward()
{
  int i = 0;
  forward(25);
  while (i < 10000)
  {  
    i = i+1;
  }
  brake(); 
}

intersection_enum scanForDeadEnd()
{
 /**@todo need to check the sensor patterns when going over a line. I highly doubt it'll be as simple as 1 for a line and 0 for no line, although that is what 
the documentation suggests in the pololu how to follow a line thingy.*/
  char *sensorPattern = useRawSensors();
  bool left = true;
  bool right = true;
  int i = 0;
  spinLeft();
  while (i<400)
  {
    i = i + 1;
  }
  brake();
  if sensorPattern != {1,1,1,0,0}
    left = false;
  i = 0;    
  spinRight();
  while (i<400)
  {
    i = i + 1;
  }
  brake();
  if sensorPattern != {0,0,1,1,1}
    right = false;
    
  if (!left && !right)
    return DEAD_END;
  else if (!left)
    return RIGHT;
  else if (!right)
    return LEFT;
  else
    return LEFT_RIGHT;    
}

intersection_enum intersectionAnalysis();
{
  brake();
  intersection_enum intersectionType;
  if sensorPattern == {0,0,0,0,0} //Nothing in front or to the side of the robot
    intersectionType = scanForDeadEnd();
  else if sensorPattern == {1,1,1,0,0} //Line to the left and infront of the robot
  {
    inchForward();
    intersection_enum futureTurn = intersectionAnalysis();
    if futureTurn == DEAD_END
      intersectionType = LEFT;
    else
      intersectionType = LEFT_STRAIGHT;
  }
  else if sensorPattern == {0,0,1,1,1}//Line to the right and infront of the robot
  {
    inchForward();
    intersection_enum futureTurn = intersectionAnalysis();
    if futureTurn == DEAD_END
      intersectionType = RIGHT;
    else
      intersectionType = RIGHT_STRAIGHT;
  }  
  else if sensorPattern = {1,1,1,1,1} //Line to the left, right and in front of the robot.
     intersectionType = CROSSROAD;
}
