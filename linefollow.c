#include "motors.h"
#include "uart.h"
#include "debug_frmwrk.h" 
#include "linefollow.h"
#include "environment.h"
#include "timer.h"

/*! \def DBG_LEVEL
 *  \brief Sets level of debuging ouput.
 *  Makes everything easier to switch on and off what is output for debuging
 *  1- Basic
 *  2- Verbose
*/
#define DBG_LEVEL 1
//----------------------------------------------------------------
uint32_t calibrateSensors()
{
   if (DBG_LEVEL == 1)
    _DBG_("send command");  
 
  uint32_t status = cmdAutoCal();
  
  if (DBG_LEVEL == 1) {
    if (status == 1) 
      _DBG_("Calibrated");
    else
      _DBG_("Failed Calibration :(");
  }
  
  return status;
}
//----------------------------------------------------------------
void getRawSensors(uint16_t*  sensorPattern)
{
  cmdRawSens(sensorPattern);
}
//----------------------------------------------------------------
void followLine(){

 if (DBG_LEVEL == 1)
    _DBG_("CALIB LINE");
  
  calibrateSensors();  
  
  if (DBG_LEVEL == 1)
    _DBG_("START LINE FOLLOWING");
  
  uint8_t sequence[] = {35, 45 , 35, 35 ,45}; 
  cmdPIDstart(sequence);	
  delay(100);
  
  if (DBG_LEVEL == 1)  
    _DBG_("START MOVING"); 
  
  while(!checkForNoLine()) {
    delay(10);
  }
  
  if (DBG_LEVEL == 1)
    _DBG_("STOP MOVING"); 
  
  cmdPIDstop();
 
  if (DBG_LEVEL == 1)
    _DBG_("STOPPED MOVING"); 
}
//----------------------------------------------------------------
