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
//  initSensors();
}

//void mouseTest() {
//	mouse_init(cb, attach, detach);
//}

void motorTest() {
  /*_DBG_("State 0");
  motorStateMachine(0);
  waitMotor();
  _DBG_("State 1");
  motorStateMachine(1);
  waitMotor();
  _DBG_("State 2");  
  motorStateMachine(2);
  waitMotor();  
  _DBG_("State 3");    
  motorStateMachine(3);
  waitMotor();  
  _DBG_("State 4");    
  motorStateMachine(4);
  waitMotor();    
  _DBG_("State 5");    
  motorStateMachine(5);
  waitMotor();      */
// motorStateMachine(0);
  /*while(getFrontSensorValue() == 1)
  {
    _DBD(getFrontSensorValue());
    _DBG_("");
   }
   motorStateMachine(5);*/
}

void linefollowTest(){
  uint16_t *sens[5] = {0};  
  while(1)
  {
  /**
  * @todo Need to work out why the sensors aren't changing
  */
    cmdRawSens(*sens); 
    _DBG_("##################");
    _DBG("Sensor 1:");_DBD16(*sens[0]);_DBG_("");
    _DBG("Sensor 2:");_DBD16(*sens[1]);_DBG_("");
    _DBG("Sensor 3:");_DBD16(*sens[2]);_DBG_("");
//    _DBG("Sensor 4:");_DBD16(*sens[3]);_DBG_("");        
    _DBG("Sensor 5:");_DBD16(*sens[4]);_DBG_("");      
  }
}

void motorCorrectTest() {
  forwards(10);
  while (1) {correctForwardMotion();}
}
