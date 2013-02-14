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
  /**
  *@todo need to work out whether 0 is black or 2000
  *      once this have been sussed out then it will 
         attempt to look for a black floor. It will
         then calibrate and use the line follow command
         It will keep searching for the "barcode" throughout     
  */  
}
