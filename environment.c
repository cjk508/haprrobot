#include "environment.h"

#include "correctmotion.h"
#include "sensors.h"
#include "linefollow.h"

int checkForLine() {
  uint16_t sensorPattern[5] = {0};
  getRawSensors(sensorPattern);
  int i;
  int isThereALine = 0;
  
  for (i = 0; i<5; i++) {
    if (sensorPattern[i] == 2000)
      isThereALine = 1;
  }
  if (isThereALine) {
    return 1;
  }
  else
    return 0;
}


int checkForWall() {
  SensorPair leftSensors = calibratedValuesLeft(getLeftSensorValues());
  SensorPair rightSensors = calibratedValuesRight(getRightSensorValues());  
  if (leftSensors.FrontSensor < 40 || leftSensors.RearSensor < 40) {
    setSensorSide(1);
    return 1;
  }
  else if (rightSensors.FrontSensor < 40 || rightSensors.RearSensor < 40) {
    setSensorSide(0);  
    return 1;
  }
  return 0;
}

void trackByMouse() {
}
