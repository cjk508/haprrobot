#include "environment.h"

#include "correctmotion.h"
#include "sensors.h"
#include "linefollow.h"
#include "timer.h"
#include "mouse.h"
#include "uart.h"
#include "debug_frmwrk.h"

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
  int noLine = 0;
  
  for (i = 0; i<5; i++) {
//    _DBG("Sensor ");_DBD(i);_DBG(" ");_DBD16(sensorPattern[i]);_DBG_("");
    if (sensorPattern[i] <= 1500) {
      noLine += 1;
    }
  }
  if (noLine == 5) {
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
 /* SensorPair temp1;
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
*/
return 2; 
}

void setCoords() {
/*
  switch(trackingState) {
    case 1: {
      if (checkForStableSensors(0)) {
        differenceBetweenMouseAndPosition(200, 0);
        trackingState = 2;
        _DBG_("200,0");
      }
      break;
    }
    case 2: {
      if (checkForStableSensors(1)) {
        differenceBetweenMouseAndPosition(400, 0);
        trackingState = 3;
        _DBG_("400,0");        
      }    
      break;
    }
    case 3: {
      if (checkForStableSensors(0)) {
        differenceBetweenMouseAndPosition(600, 200);
        trackingState = 4;
        _DBG_("600,200"); 
      }    
      break;
    }
    case 4: {
      if (checkForStableSensors(1)) {
        differenceBetweenMouseAndPosition(800, 200);
        trackingState = 5;
        _DBG_("800,200"); 
      }    
      break;
    }  
    default: {
      trackingState = 1;
      _DBG_("State 1"); 
    }              
  }
*/
}

void differenceBetweenMouseAndPosition(int x, int y) {
 /* int diffX = x - trackingPositionX;
  int diffY = y - trackingPositionY;  
  
  if (diffY<0)
    diffY = diffY * (-1);  
  if (diffX<0)
    diffX = diffX * (-1);      
    
  if ((diffX > 10) || (diffY > 10)){
    cmdDoPlay("aa");  //There's been a large difference in the tracking distance. 
  }
  trackingPositionX = x;
  trackingPositionY = y;*/
}

void trackDistance(int y, int x) {
  int initialX = get_coord_x();
  int initialY = get_coord_y();  
  
  while ((get_coord_x() < initialX + x) && (get_coord_y() < initialY + y)) {
    
  }
  motorPair LM = getSpeedLeft();
  motorPair RM = getSpeedRight();  
  brake();
  cmdDoPlay("gg");
  resume(LM, RM);
}

void trackByMouse() {
  int trackingPosition = 0;
  switch (trackingPosition) {
    case 0: {
      trackDistance(200,0);
      break;
    }
    case 1: {
      trackDistance(100,00);
      break;
    }    
    case 2: {
      trackDistance(500,-1000);
      break;
    }    
  }


  trackingPositionX = get_coord_x();
  trackingPositionY = get_coord_y();  
  setCoords();
}











