#include "motors.h"
#include "timer.h"
#include "uart.h"
#include "debug_frmwrk.h" 
#include "linefollow.h"
uint16_t const jNone[]     = {0,0,1,0,0};
uint16_t const jCrossOrT[] = {1,1,1,1,1};
uint16_t const jLeft[]     = {1,1,1,0,0};
uint16_t const jRight[]    = {0,0,1,1,1};
int junctionFound = 0;

void calibrateSensors(void)
{
 /*this automatically calibrates the line following sensors. It scans left and 
  right in an attempt to find the line. This should be called when the raw sensors
  indicate that a line is present under the robot.*/
  _DBG_("send command");  
  uint32_t status = cmdAutoCal();
  
  if (status == 1) 
    _DBG_("Calibrated");
  else
    _DBG_("Failed Calibration :(");
}

void getRawSensors(uint16_t*  sensorPattern)
{
  uint32_t status = cmdRawSens(sensorPattern);
}
void getCalibratedSensors(uint16_t* sensorPattern)
{
  uint32_t status = cmdCalSens(sensorPattern);
/*  if(buffer arrays are white)
  {
    //try to find the line
  }
  else
  {
    //follow the line
    cmdLinePosition(); //nneds to implemented in uart.c
  if the read in i between 0-1000 then we are to the right of the line
    if it is between 1000 and 3000 then we are approx centre 
    if it is between 3000 and 4000 then it is to the far left of the robot

  } 	
  return *buf;*/
}

void lineMotors()
{
  uint16_t sensorPattern[5] = {0};
  _DBG_("CALIB LINE");
  calibrateSensors();  
  _DBG_("START LINE FOLLOWING");
  uint8_t sequence[] = {35, 45 , 35, 35 ,45}; 
  cmdPIDstart(sequence);	
  _DBG_("START MOVING"); 
}

void patternNormaliser(uint16_t* sensorPattern)
{
  int arraySize = sizeof(sensorPattern);
  int i = 0;
  for(i=0;i<=arraySize;i+=1)
  {
    if(sensorPattern[i]>=1600)
      sensorPattern[i] = 1;
    else
      sensorPattern[i] = 0; 
  };
}


intersection_enum analyseJunction(uint16_t* sensorPattern)
{
  if((sensorPattern[0] = 1) && (sensorPattern[1] = 1) && // Left Junction
     (sensorPattern[2] = 1) && (sensorPattern[3] = 0) && (sensorPattern[4] = 0)) 
     {
        inchForward(LEFT, sensorPattern);
        if((sensorPattern[1] = 0) && (sensorPattern[2] = 0) && (sensorPattern[3] = 0)) //No straight Line
        {
          return LEFT;
        }  
        else
        {
          return LEFT_STRAIGHT;
        }
     }     
  else if((sensorPattern[0] = 0) && (sensorPattern[1] = 0) && // Right Junction
          (sensorPattern[2] = 1) && (sensorPattern[3] = 1) && (sensorPattern[4] = 1)) 
     {
        inchForward(RIGHT, sensorPattern); 
        if((sensorPattern[1] = 0) && (sensorPattern[2] = 0) && (sensorPattern[3] = 0)) //No straight Line
        {
          return RIGHT;
        }  
        else
        {
          return RIGHT_STRAIGHT;
        }          
     }     
  else if((sensorPattern[0] = 1) && (sensorPattern[1] = 1) && // CrossRoad or T Junction
          (sensorPattern[2] = 1) && (sensorPattern[3] = 1) && (sensorPattern[4] = 1)) 
     {
        inchForward(CROSSROAD, sensorPattern);   
        if((sensorPattern[1] = 0) && (sensorPattern[2] = 0) && (sensorPattern[3] = 0) &&
           (sensorPattern[0] = 1) && (sensorPattern[4] = 1)) //No straight Line hence T junction
        {
          return LEFT_RIGHT;
        }  
        else if((sensorPattern[0] = 0) && (sensorPattern[4] = 0))
        {
          return DEAD_END;
        }  
        else
        {
          return CROSSROAD;
        }           
     }
} 




void lineSpinLeft(uint16_t* sensorPattern)
{
  spinLeft();
  while(sensorPattern[2] == 0)
  {
    getRawSensors(sensorPattern);
  }
  brake();
}

void lineSpinRight(uint16_t* sensorPattern)
{
  spinRight();
  while(sensorPattern[2] == 0)
  {
    getRawSensors(sensorPattern);
  }
  brake();
}

void lineFollowForward(uint16_t* sensorPattern)
{
  getRawSensors(sensorPattern);
  if((sensorPattern[1] == 1) && (sensorPattern[3] == 1) && (sensorPattern[2] == 1))
  {
    if (getSpeedLeft().motor_speed != getSpeedRight().motor_speed) //if speed is not equal then change otherwise carry on
    {
      forwards(25);
    }
  }  
  else if ((sensorPattern[1] == 0) && (sensorPattern[3] == 1))
  {
    setLeftMotorFw(getSpeedLeft().motor_speed+1);
  }
  else if((sensorPattern[1] == 1) && (sensorPattern[3] == 0))
  {
    setRightMotorFw(getSpeedRight().motor_speed+1);
  }
}


void inchForward(intersection_enum junctionType, uint16_t* sensorPattern)
{
  switch(junctionType)
  {
    case LEFT:{
        forwards(25);
        while(sensorPattern[0]==1)
        {
          getRawSensors(sensorPattern);
        }
        brake();
        break;
      }
    case RIGHT:{
        forwards(25);
        while(sensorPattern[4]==1)
        {
          getRawSensors(sensorPattern);
        }
        brake();
        break;
      }
    default:{ //Crossroads
        int initialCrossRoadTime = getLotsOfBlackTape();
        forwards(25);
        while(((sensorPattern[0]==1) && (sensorPattern[4]==1))/*side sensors detect line*/ &&
              ((sensorPattern[1]==1) && (sensorPattern[2]==1)&&(sensorPattern[3]==1))/*front sensors detect line*/ &&
              (initialCrossRoadTime <= (getLotsOfBlackTape() - 10 ) /*block of tape isn't found*/)
             )
        {
          getRawSensors(sensorPattern);
        }
        brake();
        break;
      }
  }
}    
