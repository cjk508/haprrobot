#include "debug_frmwrk.h"
#include "linefollow.h"
#include "uart.h"
#include "sensors.h"
#include "motors.h"
#include "correctmotion.h"
#include "timer.h"

#define DBG_LEVEL 1

// Here be test functions!


void serialTest() {
  if (DBG_LEVEL >= 1) _DBG_("Init Serial");
//  initSerial(); 
  unsigned char buf[6];
  cmdSig(buf);
  _DBG_((char*)buf);
}

void sensorsTest() {
  SensorPair left = getLeftSensorValues();
  SensorPair right = getRightSensorValues();
  _DBG_("##################");
  _DBG("Left Front:");_DBD16(left.FrontSensor);_DBG_("");
  _DBG("Left Rear:");_DBD16(left.RearSensor);_DBG_("");
  _DBG("Right Front:");_DBD16(right.FrontSensor);_DBG_("");
  _DBG("Right Rear:");_DBD16(right.RearSensor);_DBG_("");
  int i;
  for (i = 0; i < 10000; i++);
}




void linefollowTest(){
  _DBG_("LINE FOLLOW TEST");
  uint16_t *sens[10] = {0};  
  /**
  * @todo Need to work out why the sensors aren't changing
  */
/*
    _DBG_("##################");
     getRawSensors(*sens); 
    _DBG_("##################");
    _DBG("Sensor 1:");_DBD16(*sens[0]);_DBG_("");
    _DBG("Sensor 2:");_DBD16(*sens[1]);_DBG_("");
    _DBG("Sensor 3:");_DBD16(*sens[2]);_DBG_("");
    _DBG("Sensor 4:");_DBD16(*sens[3]);_DBG_("");        
    _DBG("Sensor 5:");_DBD16(*sens[4]);_DBG_("");
    */
  cmdAutoCal();
  //getCalibratedSensors(*sens); error stating undefined reference for both this function and getRawSensors(*sens);
}

void motorCorrectTest() {
  forwards(15);
  while (1) 
  {
//   while (getFrontSensorValue() == 1)    {
//     brake();
//   }    
    correctForwardMotion();
  }
}
