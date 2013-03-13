#include "correctmotion.h"
#include "motors.h"
#include "sensors.h"
#include "uart.h"
#include "debug_frmwrk.h"

/*! \def DBG_LEVEL
 *  \brief Sets level of debuging ouput.
 *  Makes everything easier to switch on and off what is output for debuging
 *  1- Basic
 *  2- Verbose
*/
#define DBG_LEVEL 1

#define WALL_DISTANCE 15

int getSensorSide() {
  return sensorSide;
}

void setSensorSide(int setSide) {
  sensorSide = setSide;
}

void debug_output(SensorPair sensor) {
  if (DBG_LEVEL >= 2) {
    _DBG_("##################");
    if(sensorSide) {
        _DBG("Left Front:");_DBD16(sensor.FrontSensor);_DBG_("");
        _DBG("Left Rear:");_DBD16(sensor.RearSensor);_DBG_("");
     }
     else {
      _DBG("Right Front:");_DBD16(sensor.FrontSensor);_DBG_("");
      _DBG("Right Rear:");_DBD16(sensor.RearSensor);_DBG_("");
    }
  }
}

void wallFollow(SensorPair sensor) { 
  
  if ((sensor.FrontSensor > WALL_DISTANCE) && (sensor.RearSensor > WALL_DISTANCE)) { // both sensors are over the desired distance
    if(sensor.RearSensor > sensor.FrontSensor) {
      forwards(20); //keep on going straight until one of the sensors is at the desired distance.
//      debug_output(sensor);
    }
    else { //if we are either parallel or facing away from the wall
      if(sensorSide){
        setRightMotorFw(20 + (sensor.FrontSensor - WALL_DISTANCE));
        setLeftMotorFw(20);            
      }
      else {
        setLeftMotorFw(20 + (sensor.FrontSensor - WALL_DISTANCE));    
        setRightMotorFw(20);        
      }    
    }
  }
  else if ((sensor.FrontSensor < WALL_DISTANCE) && (sensor.RearSensor < WALL_DISTANCE)) { // both sensors less closer to the wall than required
    if (sensor.RearSensor > sensor.FrontSensor) { //Front sensor is closest to the wall and under the desired distance
      
      if(sensorSide){
        motorPair motorInfo = getSpeedLeft();
        setLeftMotorFw(motorInfo.motor_speed + (WALL_DISTANCE - sensor.FrontSensor));
      }
      else {
        motorPair motorInfo = getSpeedRight();
        setRightMotorFw(motorInfo.motor_speed + (WALL_DISTANCE - sensor.FrontSensor));      
      } 
//      debug_output(sensor);  
       
    }
    else if(sensor.RearSensor < sensor.FrontSensor) {//Rear sensor is closest to the wall and under the desired distance
      forwards(20);   
//      debug_output(sensor);
      
    }
  }
  else if ((sensor.FrontSensor <= WALL_DISTANCE) && (sensor.RearSensor > WALL_DISTANCE)) { // both sensors less closer to the wall than required
      if(sensorSide){
        motorPair motorInfo = getSpeedLeft();
        setLeftMotorFw(motorInfo.motor_speed + (WALL_DISTANCE - sensor.FrontSensor));
      }
      else {
        motorPair motorInfo = getSpeedRight();
        setRightMotorFw(motorInfo.motor_speed + (WALL_DISTANCE - sensor.FrontSensor));      
      } 
//      debug_output(sensor);        
  }  
  else if ((sensor.FrontSensor > WALL_DISTANCE) && (sensor.RearSensor <= WALL_DISTANCE)) { // both sensors less closer to the wall than required
      if(sensorSide){
        motorPair motorInfo = getSpeedRight();
        setRightMotorFw(motorInfo.motor_speed + (sensor.FrontSensor - WALL_DISTANCE));   
      }
      else {
        motorPair motorInfo = getSpeedLeft();
        setLeftMotorFw(motorInfo.motor_speed + (sensor.FrontSensor - WALL_DISTANCE ));    
      } 
//      debug_output(sensor);        
  }     
  else if(sensor.RearSensor < sensor.FrontSensor) {//Rear sensor is closest to the wall and under the desired distance
      forwards(20);   
//      debug_output(sensor);  
  }     
  else if ((sensor.FrontSensor == WALL_DISTANCE) && (sensor.RearSensor == WALL_DISTANCE)) {//if at the required distance carry on all is well
    forwards(20);   
  }
  else {
    cmdDoPlay("a"); //error beep
    forwards(20);
    debug_output(sensor);
  }
}

void correctForwardMotion() {
  //Get an initial value
  SensorPair left = getLeftSensorValues();
  SensorPair right = getRightSensorValues();
  left = calibratedValuesLeft(left);
  right = calibratedValuesRight(right);
  
  /**
  * Compare the two sets of values, and decide
  * whether an adjustment left or right is needed
  *
  * Now measured in cm meaning that larger value is, as per normal, further away
  */
  if (sensorSide) {
    if (left.FrontSensor < 100) { //if i can see a wall then follow it
      wallFollow(left);
      cmdDoPlay("bb");
    }
  }
  else {
    if (right.FrontSensor < 100) {
      wallFollow(right);
      cmdDoPlay("dd");
    }
  }  
}
