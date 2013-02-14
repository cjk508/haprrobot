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

void motorCorrectTest() {
  forwards(10);
  while (1) {correctForwardMotion();}
}
