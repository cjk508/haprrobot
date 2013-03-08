#include "correctmotion.h"
#include "motors.h"
#include "sensors.h"

#include "debug_frmwrk.h"
// DBG Levels
// 1 - Basic
// 2 - Verbose
#define DBG_LEVEL 2

#define WALL_DISTANCE 15

int sensorSide; //1 = left, 0 = right

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
      
      if(sensorSide){
        motorPair motorInfo = getSpeedLeft();
        setLeftMotorFw(motorInfo.motor_speed + 1);
      }
      else {
        motorPair motorInfo = getSpeedRight();
        setRightMotorFw(motorInfo.motor_speed + 1);      
      }
      debug_output(sensor);
    }
  }
  else if ((sensor.FrontSensor < WALL_DISTANCE) || (sensor.RearSensor < WALL_DISTANCE)) {
    if((sensor.FrontSensor < WALL_DISTANCE) && (sensor.RearSensor > sensor.FrontSensor)) { //Front sensor is closest to the wall and under the desired distance
      
      if(sensorSide){
        motorPair motorInfo = getSpeedLeft();
        setLeftMotorFw(motorInfo.motor_speed + 1);
      }
      else {
        motorPair motorInfo = getSpeedRight();
        setRightMotorFw(motorInfo.motor_speed + 1);      
      } 
      debug_output(sensor);   
    }
    else if((sensor.RearSensor < WALL_DISTANCE) && (sensor.RearSensor < sensor.FrontSensor)) {//Rear sensor is closest to the wall and under the desired distance
    
      if(sensorSide){ //if left then 
        motorPair motorInfo = getSpeedRight();
        setRightMotorFw(motorInfo.motor_speed + 1);
      }
      else {
        motorPair motorInfo = getSpeedLeft();
        setLeftMotorFw(motorInfo.motor_speed + 1);      
      }     
      debug_output(sensor);  
    }
  }
  else {
    forwards(15);
    debug_output(sensor);
  }
}

/**
* Reads in side sensor values, and will automatically adjust with the intention
* of eventually moving parallel to the nearest object.
* Will adjust speed one unit left or right per invokation - repeated use over
* a period of a few seconds is best.
*
* @author Lloyd Wallis <lpw503@york.ac.uk>
*/
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
    wallFollow(left);
  }
  else {
    wallFollow(right);
  }  
/*  if (sensorSide) {
    if (left.FrontSensor > left.RearSensor) {
    //If using left and moving away from an object, turn left (move closer a bit)
      //Slow down left
      setLeftMotorFw(getSpeedLeft().motor_speed-3);
      if (DBG_LEVEL >= 2) { _DBG_("Turning Left"); _DBG("Set left up: "); _DBD32(getSpeedLeft().motor_speed); _DBG_(""); 
        _DBG_("##################");
        _DBG("Left Front:");_DBD16(left.FrontSensor);_DBG_("");
        _DBG("Left Rear:");_DBD16(left.RearSensor);_DBG_("");
        _DBG("Right Front:");_DBD16(right.FrontSensor);_DBG_("");
        _DBG("Right Rear:");_DBD16(right.RearSensor);_DBG_("");
      }
    }
    else if (left.FrontSensor < left.RearSensor) {
    //If using left and moving toward an object, turn right (move away a bit)
      //Speed up left
      setLeftMotorFw(getSpeedLeft().motor_speed+3);
      if (DBG_LEVEL >= 2) { _DBG_("Turning Right"); _DBG("Set left dn: "); _DBD32(getSpeedLeft().motor_speed); _DBG_(""); 
        _DBG_("##################");
        _DBG("Left Front:");_DBD16(left.FrontSensor);_DBG_("");
        _DBG("Left Rear:");_DBD16(left.RearSensor);_DBG_("");
        _DBG("Right Front:");_DBD16(right.FrontSensor);_DBG_("");
        _DBG("Right Rear:");_DBD16(right.RearSensor);_DBG_("");
      }
    }
  }
  else if (!sensorSide) {
    if (right.FrontSensor < right.RearSensor) {
    //If using right and moving toward an object, turn left (move away a bit)
      //Speed up right
      setRightMotorFw(getSpeedRight().motor_speed+3);
      if (DBG_LEVEL >= 2) { _DBG_("Turning Left"); _DBG("Set right up: "); _DBD32(getSpeedRight().motor_speed); _DBG_(""); 
        _DBG_("##################");
        _DBG("Left Front:");_DBD16(left.FrontSensor);_DBG_("");
        _DBG("Left Rear:");_DBD16(left.RearSensor);_DBG_("");
        _DBG("Right Front:");_DBD16(right.FrontSensor);_DBG_("");
        _DBG("Right Rear:");_DBD16(right.RearSensor);_DBG_("");
      }
    }
    else if (right.FrontSensor > right.RearSensor) {
    //If using right and moving away from an object, turn right (move closer a bit)
      //Slow down right
      setRightMotorFw(getSpeedRight().motor_speed-3);
      if (DBG_LEVEL >= 2) { _DBG_("Turning Right"); _DBG("Set right dn: "); _DBD32(getSpeedRight().motor_speed); _DBG_(""); 
        _DBG_("##################");
        _DBG("Left Front:");_DBD16(left.FrontSensor);_DBG_("");
        _DBG("Left Rear:");_DBD16(left.RearSensor);_DBG_("");
        _DBG("Right Front:");_DBD16(right.FrontSensor);_DBG_("");
        _DBG("Right Rear:");_DBD16(right.RearSensor);_DBG_("");
      }
    }
  }*/
}
