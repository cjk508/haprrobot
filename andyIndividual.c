#include "andyIndividual.h"

#include "uart.h"


#include "string.h"
#include "debug_frmwrk.h"


// cmdDoPlay(note[28]);

SensorPair noteValuesLeft(SensorPair sensorValue) {
  uint16_t tempF = 0;
  uint16_t tempR = 0;
  // Front
  if      (sensorValue.FrontSensor < 150)  { tempF = 0; }
  else if (sensorValue.FrontSensor < 200)  { tempF = 1; }
  else if (sensorValue.FrontSensor < 250)  { tempF = 2; }  
  else if (sensorValue.FrontSensor < 300)  { tempF = 3; }     
  else if (sensorValue.FrontSensor < 350)  { tempF = 4; }  
  else if (sensorValue.FrontSensor < 400)  { tempF = 5; }
  else if (sensorValue.FrontSensor < 450)  { tempF = 6; }      
  else if (sensorValue.FrontSensor < 500)  { tempF = 7; }
  else if (sensorValue.FrontSensor < 550)  { tempF = 8; }
  else if (sensorValue.FrontSensor < 600)  { tempF = 9; }
  else if (sensorValue.FrontSensor < 650)  { tempF = 10; }
  else if (sensorValue.FrontSensor < 700)  { tempF = 11; }  
  else if (sensorValue.FrontSensor < 750)  { tempF = 12; }     
  else if (sensorValue.FrontSensor < 800)  { tempF = 13; }  
  else if (sensorValue.FrontSensor < 850)  { tempF = 14; }
  else if (sensorValue.FrontSensor < 900)  { tempF = 15; }      
  else if (sensorValue.FrontSensor < 950)  { tempF = 16; }
  else if (sensorValue.FrontSensor < 1000) { tempF = 17; }
  else if (sensorValue.FrontSensor < 1050) { tempF = 18; }
  else if (sensorValue.FrontSensor < 1100) { tempF = 19; }
  else if (sensorValue.FrontSensor < 1150) { tempF = 20; }  
  else if (sensorValue.FrontSensor < 1200) { tempF = 21; }  
  else if (sensorValue.FrontSensor < 1250) { tempF = 22; }
  else if (sensorValue.FrontSensor < 1300) { tempF = 23; }
  else if (sensorValue.FrontSensor < 1350) { tempF = 24; }
  else if (sensorValue.FrontSensor < 1400) { tempF = 25; }
  else if (sensorValue.FrontSensor < 1450) { tempF = 26; }
  else if (sensorValue.FrontSensor < 1500) { tempF = 27; }
  else if (sensorValue.FrontSensor < 1550) { tempF = 28; }
  else if (sensorValue.FrontSensor < 1600) { tempF = 29; }
  else if (sensorValue.FrontSensor < 1650) { tempF = 30; }
  else if (sensorValue.FrontSensor < 1700) { tempF = 31; }
  else if (sensorValue.FrontSensor < 1750) { tempF = 32; }
  else if (sensorValue.FrontSensor < 1800) { tempF = 33; }
  else if (sensorValue.FrontSensor < 1850) { tempF = 34; }
  else if (sensorValue.FrontSensor < 1900) { tempF = 35; }
  else if (sensorValue.FrontSensor < 1950) { tempF = 36; }
  else if (sensorValue.FrontSensor < 2000) { tempF = 37; }  
  else if (sensorValue.FrontSensor < 2050) { tempF = 38; }     
  else if (sensorValue.FrontSensor < 2100) { tempF = 39; }  
  else if (sensorValue.FrontSensor < 2150) { tempF = 40; }
  else if (sensorValue.FrontSensor < 2200) { tempF = 41; }      
  else if (sensorValue.FrontSensor < 2250) { tempF = 42; }
  else if (sensorValue.FrontSensor < 2300) { tempF = 43; }
  else if (sensorValue.FrontSensor < 2350) { tempF = 44; }
  else if (sensorValue.FrontSensor < 2400) { tempF = 45; }
  else if (sensorValue.FrontSensor < 2450) { tempF = 46; }  
  else if (sensorValue.FrontSensor < 2500) { tempF = 47; }  
  else if (sensorValue.FrontSensor < 2550) { tempF = 48; }
  else if (sensorValue.FrontSensor < 2600) { tempF = 49; }
  else if (sensorValue.FrontSensor < 2650) { tempF = 50; }
  else if (sensorValue.FrontSensor < 2700) { tempF = 51; }
  else if (sensorValue.FrontSensor < 2750) { tempF = 52; }
  else if (sensorValue.FrontSensor < 2800) { tempF = 53; }
  else if (sensorValue.FrontSensor < 2850) { tempF = 54; }
  else if (sensorValue.FrontSensor < 2900) { tempF = 55; }
  else if (sensorValue.FrontSensor < 2950) { tempF = 56; }
  else if (sensorValue.FrontSensor < 3000) { tempF = 57; }
  else if (sensorValue.FrontSensor < 3050) { tempF = 58; }
  else if (sensorValue.FrontSensor < 3100) { tempF = 59; }
  else if (sensorValue.FrontSensor < 3150) { tempF = 60; }
  else if (sensorValue.FrontSensor < 3200) { tempF = 61; }
  else                                     { tempF = 62; }
  
  sensorValue.RearSensor = tempR;
  sensorValue.FrontSensor = tempF;
  return sensorValue;
}

SensorPair volumeValuesRight(SensorPair sensorValue) {
  uint16_t tempF = 0;
  uint16_t tempR = 0;
  // Front
  if      (sensorValue.FrontSensor < 1400) { tempF = 16; }
  else if (sensorValue.FrontSensor < 1560) { tempF = 15; }
  else if (sensorValue.FrontSensor < 1670) { tempF = 14; }  
  else if (sensorValue.FrontSensor < 1725) { tempF = 13; }     
  else if (sensorValue.FrontSensor < 1800) { tempF = 12; }  
  else if (sensorValue.FrontSensor < 1900) { tempF = 11; }
  else if (sensorValue.FrontSensor < 2000) { tempF = 10; }      
  else if (sensorValue.FrontSensor < 2150) { tempF = 9; }
  else if (sensorValue.FrontSensor < 2280) { tempF = 8; }
  else if (sensorValue.FrontSensor < 2400) { tempF = 7; }
  else if (sensorValue.FrontSensor < 2600) { tempF = 6; }
  else if (sensorValue.FrontSensor < 2810) { tempF = 5; }  
  else if (sensorValue.FrontSensor < 2900) { tempF = 4; }     
  else if (sensorValue.FrontSensor < 3000) { tempF = 3; }  
  else if (sensorValue.FrontSensor < 3100) { tempF = 2; }
  else if (sensorValue.FrontSensor < 3250) { tempF = 1; }      
  else                                     { tempF = 0; }

  sensorValue.RearSensor = tempR;
  sensorValue.FrontSensor = tempF;
  return sensorValue;
}

void setNote() {
  SensorPair noteSensor = getLeftSensorValues();
  noteSensor = noteValuesLeft(noteSensor);
  cmdDoPlay((char*)note[noteSensor.FrontSensor]);
}

void setVolume() {
  SensorPair volumeSensor = getRightSensorValues();
  volumeSensor = volumeValuesRight(volumeSensor);
  cmdDoPlay((char*)volume[volumeSensor.FrontSensor]);
}


