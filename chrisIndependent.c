#include "chrisIndependent.h"
#include "motors.h"
#include "uart.h"
#include "debug_frmwrk.h" 
#include "linefollow.h"
#include "environment.h"
#include "timer.h"

#define DBG_LEVEL 1
//-------------------------------------------------------------------------
void mazeFollow() {
  if (DBG_LEVEL == 1)
    _DBG_("CALIB LINE");

  calibrateSensors();  
  uint16_t sensorPattern[5] = {0};
  if (DBG_LEVEL == 1)
    _DBG_("START LINE FOLLOWING");

  uint8_t sequence[] = {35, 45 , 35, 35 ,45}; 
  cmdPIDstart(sequence);	

  if (DBG_LEVEL == 1)  
    _DBG_("START MOVING");
  
  int junctionFound = 0; 
  uint8_t linePos = 0;
  while(!junctionFound) {
    linePos = cmdLinePos(&linePos);
    if(!((linePos > 500) && (linePos < 3500)))
      junctionFound = 1;  
  }
  cmdPIDstop();
  
  intersection_enum junctionType = analyseJunction(sensorPattern);
  
  switch(junctionType)
  {
    case LEFT:{
        _DBG_("LEFT");
        lineSpinLeft(sensorPattern);
        break;
      }
    case RIGHT:{
        _DBG_("RIGHT");
        lineSpinRight(sensorPattern);
        break;
      }
    case LEFT_STRAIGHT:{
        _DBG_("LEFT_STRAIGHT");
        lineSpinLeft(sensorPattern); // or forwards depending on previous moves
        break;
      }
    case RIGHT_STRAIGHT:{
        _DBG_("RIGHT_STRAIGHT");
        lineSpinRight(sensorPattern); // or forwards depending on previous moves
        break;
      }
    case CROSSROAD:{
        _DBG_("CROSSROAD");
        lineSpinLeft(sensorPattern); // or right or forwards depending on previous moves
        break;
      }
    case LEFT_RIGHT:{
        _DBG_("LEFT_RIGHT");
        lineSpinLeft(sensorPattern); // or right depending on previous moves
        break;
      }
    case DEAD_END:{
        _DBG_("DEAD_END");
        lineSpinLeft(sensorPattern);
        break;
      }
    case NONE: break;
  }   
}
//-------------------------------------------------------------------------
intersection_enum analyseJunction(uint16_t* sensorPattern)
{
  int linePos = cmdLinePos(&linePos);
  if(linePos < 2000) 
     {
        inchForward(LEFT, sensorPattern);
        if((sensorPattern[1] == 0) && (sensorPattern[2]== 0) && (sensorPattern[3] == 0)) //No straight Line
        {
          return LEFT;
        }  
        else
        {
          return LEFT_STRAIGHT;
        }
     }     
  else if(linePos > 2000) 
     {
        inchForward(RIGHT, sensorPattern); 
        if((sensorPattern[1] == 0) && (sensorPattern[2] == 0) && (sensorPattern[3] == 0)) //No straight Line
        {
          return RIGHT;
        }  
        else
        {
          return RIGHT_STRAIGHT;
        }          
     }     
  else if(linePos < 3000 && linePos > 1000) 
     {
        inchForward(CROSSROAD, sensorPattern);   
        if((sensorPattern[1] == 0) && (sensorPattern[2] == 0) && (sensorPattern[3] == 0) &&
           (sensorPattern[0] == 1) && (sensorPattern[4] == 1)) //No straight Line hence T junction
        {
          return LEFT_RIGHT;
        }  
        else if((sensorPattern[0] == 0) && (sensorPattern[4] == 0))
        {
          return DEAD_END;
        }  
        else
        {
          return CROSSROAD;
        }           
     }
} 
//-------------------------------------------------------------------------
void lineSpinLeft(uint16_t* sensorPattern)
{
  spinLeft();
  while(sensorPattern[2] == 0)
  {
    getRawSensors(sensorPattern);
  }
  brake();
}
//-------------------------------------------------------------------------
void lineSpinRight(uint16_t* sensorPattern)
{
  spinRight();
  while(sensorPattern[2] == 0)
  {
    getRawSensors(sensorPattern);
  }
  brake();
}
//-------------------------------------------------------------------------
void inchForward(intersection_enum junctionType, uint16_t* sensorPattern)
{
  switch(junctionType)
  {
    case LEFT:{
        forwards(25);
        while(sensorPattern[0]==1)
        {
          getRawSensors(sensorPattern);
           patternNormaliser(sensorPattern);
        }
        brake();
        break;
      }
    case RIGHT:{
        forwards(25);
        while(sensorPattern[4]==1)
        {
          getRawSensors(sensorPattern);
          patternNormaliser(sensorPattern);
        }
        brake();
        break;
    }
    default:{ //Crossroads
        int initialCrossRoadTime = lotsOfBlackTape;
        forwards(25);
        while(((sensorPattern[0]==1) && (sensorPattern[4]==1))/*side sensors detect line*/ &&
              ((sensorPattern[1]==1) && (sensorPattern[2]==1)&&(sensorPattern[3]==1))/*front sensors detect line*/ &&
              (initialCrossRoadTime <= (lotsOfBlackTape - 100 ) /*block of tape isn't found*/)
             )
        {
          getRawSensors(sensorPattern);
          patternNormaliser(sensorPattern);
        }
        brake();
        break;
      }
  }
}   

//-------------------------------------------------------------------------
void patternNormaliser(uint16_t* sensorPattern)
{
  int arraySize = sizeof(sensorPattern);
  int i = 0;
  for(i=0;i<=arraySize;i+=1)
  {
    if(sensorPattern[i]==2000)
      sensorPattern[i] = 1;
    else
      sensorPattern[i] = 0; 
  };
} 
//-------------------------------------------------------------------------
void getCalibratedSensors(uint16_t* sensorPattern)
{
  cmdCalSens(sensorPattern);
}  
//-------------------------------------------------------------------------
