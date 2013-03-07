#include "correctmotion.h"
#include "motors.h"
#include "sensors.h"

#include "debug_frmwrk.h"
// DBG Levels
// 1 - Basic
// 2 - Verbose
#define DBG_LEVEL 2

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
  SensorPair left = calibratedValuesLeft(getLeftSensorValues());
  SensorPair right = calibratedValuesRight(getRightSensorValues());
  
  int use_left; //1 = left, 0 = right

  /**
  * Comparing the sets of values, choose either left or right
  * as a calibration pair - the closest one preferably
  * A higher sensor value means closer to an object
  */
  if (left.FrontSensor + left.RearSensor <=
        right.FrontSensor + right.RearSensor) {
    //The Left is closer to something, use that
    use_left = 1;
  } else {
    //The Right is closer to something, use that
    use_left = 0;
  }

  /**
  * Compare the two sets of values, and decide
  * whether an adjustment left or right is needed
  *
  * Now measured in cm meaning that larger value is, as per normal, further away
  */
  if (use_left) {
    if (left.FrontSensor > left.RearSensor) {
    //If using left and moving away from an object, turn left (move closer a bit)
      //Slow down left
      setLeftMotorFw(getSpeedLeft().motor_speed-1);
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
      setLeftMotorFw(getSpeedLeft().motor_speed+1);
      if (DBG_LEVEL >= 2) { _DBG_("Turning Right"); _DBG("Set left dn: "); _DBD32(getSpeedLeft().motor_speed); _DBG_(""); 
        _DBG_("##################");
        _DBG("Left Front:");_DBD16(left.FrontSensor);_DBG_("");
        _DBG("Left Rear:");_DBD16(left.RearSensor);_DBG_("");
        _DBG("Right Front:");_DBD16(right.FrontSensor);_DBG_("");
        _DBG("Right Rear:");_DBD16(right.RearSensor);_DBG_("");
      }
    }
  }
  else if (!use_left) {
    if (right.FrontSensor < right.RearSensor) {
    //If using right and moving toward an object, turn left (move away a bit)
      //Speed up right
      setRightMotorFw(getSpeedRight().motor_speed+1);
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
      setRightMotorFw(getSpeedRight().motor_speed-1);
      if (DBG_LEVEL >= 2) { _DBG_("Turning Right"); _DBG("Set right dn: "); _DBD32(getSpeedRight().motor_speed); _DBG_(""); 
        _DBG_("##################");
        _DBG("Left Front:");_DBD16(left.FrontSensor);_DBG_("");
        _DBG("Left Rear:");_DBD16(left.RearSensor);_DBG_("");
        _DBG("Right Front:");_DBD16(right.FrontSensor);_DBG_("");
        _DBG("Right Rear:");_DBD16(right.RearSensor);_DBG_("");
      }
    }
  }
}
