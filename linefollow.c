#include "motors.h"
#include "uart.h"
#include "linefollow.h"

void calibrateSensors(void)
{
  /**
  * @todo this will need to calibrate the sensors. This will be called
  * when the robot reaches the line and the raw sensors pick up on this fact
  * Calibrate sensors should just have to call the calibrate function that I think pololu provides
  * if it in't provided then the robot will just scan left and right a few times until
  * it can deduce what the line looks like. 
  */
  cmdCalSens();
 //or
 spinRight();
 int i =0;
 while (i<1500)
 {
   i = i+1;
 }
 brake();
 char bufRight[] = getRawSensors();
 
 spinLeft();
 i = 0;
 while (i<3000)
 {
	 i = i+1;	
 }
 brake();
 char bufLeft[] = getRawSensors();

 /**
  * @todo insert clever calibration code here.
  */
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
