// Central include files
#include "debug_frmwrk.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_nvic.h"
#include "lpc17xx_timer.h"
#include "lpc_types.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_i2c.h"
#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_dac.h"

#include "lpc17xx.h"

// DBG Levels
// 1 - Basic
// 2 - Verbose
#define DBG_LEVEL 1

#include "uart.h"
#include "sensors.h"
#include "motors.h"
#include "correctmotion.h"
#include "timer.h"

uint8_t sig;

void serialTest() {
  if (DBG_LEVEL >= 1) _DBG_("Init Serial");
  initSerial(); 
  unsigned char buf[6];
  cmdSig(buf);
  _DBG_((char*)buf);
}

void sensorsTest() {
  initSensors();
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
  motorStateMachine(0);
  /*while(getFrontSensorValue() == 1)
  {
    _DBD(getFrontSensorValue());
    _DBG_("");
   }
   motorStateMachine(5);*/
}

void motorCorrectTest() {
  motorTest();
  while (1) {correctForwardMotion();}
}

void main(void) {
  debug_frmwrk_init();
  _DBG_("Magic!");
	serialTest();

  sensorsTest();
  motorCorrectTest();


  
  _DBG_("Done");
}
