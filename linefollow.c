#include "motors.h"
#include "uart.h"
#include "linefollow.h"

char[] useRawSensors(void)
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

char[] useCalibratedSensors(void)
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
  if sensorPattern == {0,0,0,0,0}
    intersectionType = scanForDeadEnd();
  else if sensorPattern == {1,1,1,0,0}
  {
    inchForward();
    intersection_enum futureTurn = intersectionAnalysis();
    if futureTurn == DEAD_END
      intersectionType = LEFT;
    else
      intersectionType = LEFT_STRAIGHT;
  }
  else if sensorPattern == {0,0,1,1,1}
  {
    inchForward();
    intersection_enum futureTurn = intersectionAnalysis();
    if futureTurn == DEAD_END
      intersectionType = RIGHT;
    else
      intersectionType = RIGHT_STRAIGHT;
  }  
  else if sensorPattern = {1,1,1,1,1}
     intersectionType = CROSSROAD;
}
