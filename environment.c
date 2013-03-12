#include "environment.h"

#include "correctmotion.h"
#include "sensors.h"
#include "linefollow.h"
#include "timer.h"
#include "mouse.h"
#include "uart.h"

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
int checkForNoLine() {
  uint16_t sensorPattern[5] = {0};
  getRawSensors(sensorPattern);
  int i;
  int isThereALine = 0;
  
  for (i = 0; i<5; i++) {
    if (sensorPattern[i] <= 1500)
      isThereALine = 1;
  }
  if (isThereALine == 5) {
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
  if (leftSensors.FrontSensor < 100 || leftSensors.RearSensor < 100) {
    setSensorSide(1);
    sensorSideFound++;
  }
  if (rightSensors.FrontSensor < 100 || rightSensors.RearSensor < 100) {
    setSensorSide(0);  
    sensorSideFound++;
  }
  if (leftSensors.FrontSensor == 100 && leftSensors.RearSensor < 100) {
    setSensorSide(1);  
    sensorSideFound = 3;
  }   
  if (rightSensors.FrontSensor == 100 && rightSensors.RearSensor < 100) {
    setSensorSide(0);  
    sensorSideFound = 4;
  }       
  return sensorSideFound;
}

void setTrackingPosition(int x, int y) {
  trackingPositionX = x;
  trackingPositionY = y;
}

int checkForStableSensors(int wallPosition) {
  SensorPair temp1;
  SensorPair temp2;
  
  if (getSensorSide()) {
    temp1 = calibratedValuesLeft(getLeftSensorValues());
  }
  else {
    temp1 = calibratedValuesRight(getRightSensorValues()); 
  }
  
  if (wallPosition == 0) { // robot just found wall
    if (temp1.RearSensor != 100) {
      return 0; // Wall is not in the right position don't write the new tracking position
    }
  }
  else if (wallPosition == 1) { // robot just leaving wall
    if (temp1.FrontSensor != 100) {
      return 0; // Wall is not in the right position don't write the new tracking position
    }  
  }
  else { // No wall
    if ((temp1.RearSensor < 100) || (temp1.FrontSensor < 100)) 
      return 0; // Wall is not in the right position don't write the new tracking position
  }
  
  delay(2);
  	
  if (getSensorSide()) {
    temp2 = calibratedValuesLeft(getLeftSensorValues());
  }
  else {
    temp2 = calibratedValuesRight(getRightSensorValues()); 
  } 
  
  if (wallPosition == 0) { // robot just found wall
    if (temp2.RearSensor != 100) {
      return 0; // Wall is not in the right position don't write the new tracking position
    }
  }
  else if (wallPosition == 1) { // robot just leaving wall
    if (temp2.FrontSensor != 100) {
      return 0; // Wall is not in the right position don't write the new tracking position
    }  
  }
  else { // No wall
    if ((temp2.RearSensor < 100) || (temp2.FrontSensor < 100)) 
      return 0; // Wall is not in the right position don't write the new tracking position
  }  
  
  if ((temp1.FrontSensor == temp2.FrontSensor) && (temp1.FrontSensor == temp2.FrontSensor)) {
    return 1;
  }
  else {
      return 0; // Sensors were not stable don't write the new tracking position
  }
}

void setCoords() {

  switch(trackingState) {
    case 1: {
      if (checkForStableSensors(0)) {
        differenceBetweenMouseAndPosition(2000, 0);
        trackingState = 2;
      }
      break;
    }
    case 2: {
      if (checkForStableSensors(1)) {
        differenceBetweenMouseAndPosition(4000, 0);
        trackingState = 3;
      }    
      break;
    }
    case 3: {
      if (checkForStableSensors(0)) {
        differenceBetweenMouseAndPosition(6000, 2000);
        trackingState = 4;
      }    
      break;
    }
    case 4: {
      if (checkForStableSensors(1)) {
        differenceBetweenMouseAndPosition(8000, 2000);
        trackingState = 5;
      }    
      break;
    }  
    default: {
      trackingState = 1;
    }              
  }

}

void differenceBetweenMouseAndPosition(int x, int y) {
  int diffX = x - trackingPositionX;
  int diffY = y - trackingPositionY;  
  
  if (diffY<0)
    diffY = diffY * (-1);  
  if (diffX<0)
    diffX = diffX * (-1);      
    
  if ((diffX > 10) || (diffY > 10)){
    cmdDoPlay("aa");  //There's been a large difference in the tracking distance. 
  }
  trackingPositionX = x;
  trackingPositionY = y;
}

void trackByMouse() {
  
/*  switch (trackingPosition) {
    case 0: {
//      trackDistance(2000,0);
      break;
    }
    case 1: {
//      trackDistance(2000,2000);
      break;
    }    
    case 2: {
//      trackDistance(500,-1000);
      break;
    }    
  }
*/

  trackingPositionX = get_coord_x();
  trackingPositionY = get_coord_y();  
  setCoords();
}











