#include "correctmotion.h"
#include "motors.h"
#include "sensors.h"

void correctForwardMotion() {
  //Get an initial value
  SensorPair left = getLeftSensorValues();
  SensorPair right = getRightSensorValues();
  //Other variables used
  SensorPair x;
  int use_left; //1 = left, 0 = right
  /**
  * Wait for a little while
  * @todo Better way of doing this (e.g. interrupt/other sleep method)?
  */
  int i;
  for (i = 0; i < 1000000; i++);

  /**
  * Comparing the sets of values, choose either left or right
  * as a calibration pair - the closest one preferably
  * A higher sensor value means closer to an object
  */
  if ((left.FrontSensor + left.RearSensor) / 2 >=
       (right.FrontSensor + right.RearSensor) /2 && 0) {
    //The Left is closer to something, use that from now on
    x = getLeftSensorValues();
    use_left = 1;
  } else {
    //The Right is closer to something, use that from now on
    x = getRightSensorValues();
    use_left = 0;
  }

  /**
  * Compare the two sets of values, and decide
  * whether an adjustment left or right is needed
  */
  if (
      //If using left and moving toward object, turn right (move away a bit)
      (use_left
      && (left.FrontSensor + left.RearSensor)/2 - (x.FrontSensor + x.RearSensor)/2 > 1000)
      //If using right and moving away, turn right
      || (!use_left
      && (right.FrontSensor + right.RearSensor)/2 - (x.FrontSensor + x.RearSensor) /2 < -1000)) {
     
       //Adjust right a bit, decide whether to speed up left or slow down right
       if (current_motor_speed_left > current_motor_speed_right) {
         //Speed up right
         setRightMotor(current_motor_speed_right+1);
       } else {
         //Slow Down left
         setLeftMotor(current_motor_speed_left-1);
       }
       
       
     } else if (
      //If using left and moving away from object, turn left (move toward a bit)
      (use_left
      && (left.FrontSensor + left.RearSensor)/2 - (x.FrontSensor + x.RearSensor)/2 < -1000)
      //If using right and moving toward, turn left
      || (!use_left
      && (right.FrontSensor + right.RearSensor)/2 - (x.FrontSensor + x.RearSensor) /2 > 1000)
     ) {
       
       //Adjust right a bit, decide whether to speed up right or slow down left
       if (current_motor_speed_left > current_motor_speed_right) {
         //Speed up left
         setLeftMotor(current_motor_speed_left-1);
       } else {
         //Slow Down right
         setRightMotor(current_motor_speed_right+1);
       }
       
     }
        
}
