#include "motors.h"
#include "timer.h"
#include "uart.h"
#include "debug_frmwrk.h" 
#include "linefollow.h"

void calibrateSensors(void)
{
  _DBG_("send command");  
  uint32_t status = cmdAutoCal();
  
  if (status == 1) 
    _DBG_("Calibrated");
  else
    _DBG_("Failed Calibration :(");
}

void lineMotors()
{
  uint16_t sensorPattern[5] = {0};
  _DBG_("CALIB LINE");
  calibrateSensors();  
  _DBG_("START LINE FOLLOWING");
  uint8_t sequence[] = {35, 45 , 35, 35 ,45}; 
  cmdPIDstart(sequence);	
  _DBG_("START MOVING"); 
}

