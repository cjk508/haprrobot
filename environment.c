#include "environment.h"

#include "correctmotion.h"
#include "sensors.h"
#include "linefollow.h"
#include "timer.h"

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

void dockBySensorsAndLine() {
  forwards(25);
  delay(20);
  brake();
}

int checkForWall() {
  SensorPair leftSensors = calibratedValuesLeft(getLeftSensorValues());
  SensorPair rightSensors = calibratedValuesRight(getRightSensorValues());  
  int sensorSideFound = 0;
  if (leftSensors.FrontSensor < 40 || leftSensors.RearSensor < 40) {
    setSensorSide(1);
    sensorSideFound++;
  }
  if (rightSensors.FrontSensor < 40 || rightSensors.RearSensor < 40) {
    setSensorSide(0);  
    sensorSideFound++;
  }
  
  switch (sensorSideFound) {
    case 0: {
      return 0;
      break;
    }
    case 1: {
      return 1;
      break;
    }    
    case 2: {
      return 2;
      break;
    }    
  }
}

void trackByMouse() {
}
