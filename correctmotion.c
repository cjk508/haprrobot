#include "correctmotion.h"
#include "motors.h"
#include "sensors.h"

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
  
  int use_left; //1 = left, 0 = right

  /**
  * Comparing the sets of values, choose either left or right
  * as a calibration pair - the closest one preferably
  * A higher sensor value means closer to an object
  */
  if (left.FrontSensor + left.RearSensor >=
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
  * Remember that a higher value means it's closer to the sensor.
  */
  if (
      //If using left and moving away from object, turn left (move away a bit)
      (use_left && left.FrontSensor < left.RearSensor)
      //If using right and moving toward, turn left
      || (!use_left && right.FrontSensor > right.RearSensor)
     ) {
       //Adjust right a bit, decide whether to speed up left or slow down right
       // @todo this is where it could check if the motor is going backwards or forwards
       if (current_motor_speed_left > current_motor_speed_right) {
         //Speed up right
         setRightMotor(current_motor_speed_right+1);
       } 
       else {
         //Slow Down left
         setLeftMotor(current_motor_speed_left-1);
       }
     }
  else if (
      //If using left and moving toward an object, turn right (move toward a bit)
      (use_left && left.FrontSensor > left.RearSensor)
      //If using right and moving away, turn right
      || (!use_left && right.FrontSensor < right.RearSensor)
       ) {
         //Adjust right a bit, decide whether to speed up right or slow down left
         // @todo this is where it could check if the motor is going backwards or forwards
         if (current_motor_speed_left > current_motor_speed_right) {
           //Speed up left
           setLeftMotor(current_motor_speed_left+1);
         } 
         else {
           //Slow Down right
           setRightMotor(current_motor_speed_right-1);
         }
     }
        
}
