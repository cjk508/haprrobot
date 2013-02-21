#include "motors.h"
#include "uart.h"
#include "linefollow.h"

void useRawSensors(void)
{
  unsigned char *buf[10];
  uint32_t status = cmdRawSens(*buf);
  /**
  *@todo need to work out whether 0 is black or 1000
  *      once this have been sussed out then it will 
         attempt to look for a black floor. It will
         then calibrate and use the line follow command
         It will keep searching for the "barcode" throughout     
  */
}

void useCalibratedSensors(void)
{
  unsigned char *buf[10];
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

intersection_enum intersectionAnalysis();
{
}
