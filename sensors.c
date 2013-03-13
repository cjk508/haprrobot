//----------------------------------------------------------------
#include "sensors.h"
#include "motors.h"
#include "debug_frmwrk.h"
#include "uart.h"
#include "frontrun.h"
//----------------------------------------------------------------
//constants
const uint16_t DESIRED_DISTANCE = 1500;
const uint16_t VERY_CLOSE = 2700;
const uint16_t NO_WALL = 0; // 2500;
const unsigned long frontSensor = 1<<17; //this was 17 on robot 5
//Variables
int analogSensorPins[] = {23, 24, 25, 30}; // FL, BL, BR, FR
//int analogSensorPins[] = {25, 26, 23, 24}; // FL, BL, BR, FR
uint32_t currentReadings[] = {0,0,0,0,0}; // initialised readings
int frontIRQ_triggered = 0;
//----------------------------------------------------------------
SensorPair roundingValues(SensorPair sensorValue)
{
  uint16_t tempF = 0;
  uint16_t tempR = 0;
  tempF = ((sensorValue.FrontSensor + 50) / 100) * 100;
  tempR = ((sensorValue.RearSensor + 50) / 100) * 100;
  sensorValue.RearSensor = tempR;
  sensorValue.FrontSensor = tempF;
  return sensorValue;
}
//----------------------------------------------------------------
SensorPair calibratedValuesLeft(SensorPair sensorValue) {
  uint16_t tempF = 0;
  uint16_t tempR = 0;
  // Front
  if (sensorValue.FrontSensor < 400) { tempF = 100; }
  else if (sensorValue.FrontSensor < 470) { tempF = 60; }
  else if (sensorValue.FrontSensor < 560) { tempF = 50; }  
  else if (sensorValue.FrontSensor < 640) { tempF = 45; }     
  else if (sensorValue.FrontSensor < 710) { tempF = 43; }  
  else if (sensorValue.FrontSensor < 800) { tempF = 40; }
  else if (sensorValue.FrontSensor < 880) { tempF = 37; }      
  else if (sensorValue.FrontSensor < 920) { tempF = 35; }
  else if (sensorValue.FrontSensor < 980) { tempF = 33; }
  else if (sensorValue.FrontSensor < 1100) { tempF = 30; }
  else if (sensorValue.FrontSensor < 1350) { tempF = 25; }
  else if (sensorValue.FrontSensor < 1480) { tempF = 24; }  
  else if (sensorValue.FrontSensor < 1480) { tempF = 23; }  
  else if (sensorValue.FrontSensor < 1520) { tempF = 22; }   //? said 10 dunno why
  else if (sensorValue.FrontSensor < 1560) { tempF = 21; }
  else if (sensorValue.FrontSensor < 1580) { tempF = 20; }
  else if (sensorValue.FrontSensor < 1680) { tempF = 19; }
  else if (sensorValue.FrontSensor < 1770) { tempF = 18; }
  else if (sensorValue.FrontSensor < 1850) { tempF = 17; }
  else if (sensorValue.FrontSensor < 1950) { tempF = 16; }
  else if (sensorValue.FrontSensor < 2010) { tempF = 15; }
  else if (sensorValue.FrontSensor < 2200) { tempF = 14; }
  else if (sensorValue.FrontSensor < 2350) { tempF = 13; }
  else if (sensorValue.FrontSensor < 2430) { tempF = 12; }
  else if (sensorValue.FrontSensor < 2610) { tempF = 11; }
  else if (sensorValue.FrontSensor < 2720) { tempF = 10; }
  else if (sensorValue.FrontSensor < 3200) { tempF = 5; }
  
  // Rear
  if (sensorValue.RearSensor < 400) { tempR = 100; }  
  else if (sensorValue.RearSensor < 810) { tempR = 40; }
  else if (sensorValue.RearSensor < 940) { tempR = 35; }
  else if (sensorValue.RearSensor < 1100) { tempR = 30; }
  else if (sensorValue.RearSensor < 1350) { tempR = 25; }
  else if (sensorValue.RearSensor < 1600) { tempR = 20; }
  else if (sensorValue.RearSensor < 1700) { tempR = 19; }
  else if (sensorValue.RearSensor < 1800) { tempR = 18; }
  else if (sensorValue.RearSensor < 1870) { tempR = 17; }
  else if (sensorValue.RearSensor < 1950) { tempR = 16; }
  else if (sensorValue.RearSensor < 2050) { tempR = 15; }
  else if (sensorValue.RearSensor < 2150) { tempR = 14; }
  else if (sensorValue.RearSensor < 2280) { tempR = 13; }
  else if (sensorValue.RearSensor < 2400) { tempR = 12; }
  else if (sensorValue.RearSensor < 2600) { tempR = 11; }
  else if (sensorValue.RearSensor < 2810) { tempR = 10; }
  else if (sensorValue.RearSensor < 3250) { tempR = 5; }
  
  sensorValue.RearSensor = tempR;
  sensorValue.FrontSensor = tempF;
  return sensorValue;
}
//----------------------------------------------------------------
SensorPair calibratedValuesRight(SensorPair sensorValue) {
  uint16_t tempF = 0;
  uint16_t tempR = 0;
  // Front
  if (sensorValue.FrontSensor < 400) { tempF = 100; } 
  else if (sensorValue.FrontSensor < 930) { tempF = 40; }
  else if (sensorValue.FrontSensor < 1030) { tempF = 35; }
  else if (sensorValue.FrontSensor < 1170) { tempF = 30; }
  else if (sensorValue.FrontSensor < 1350) { tempF = 25; }
  else if (sensorValue.FrontSensor < 1590) { tempF = 20; }
  else if (sensorValue.FrontSensor < 1715) { tempF = 19; }
  else if (sensorValue.FrontSensor < 1780) { tempF = 18; }
  else if (sensorValue.FrontSensor < 1850) { tempF = 17; }
  else if (sensorValue.FrontSensor < 1980) { tempF = 16; }
  else if (sensorValue.FrontSensor < 2040) { tempF = 15; }
  else if (sensorValue.FrontSensor < 2100) { tempF = 14; }
  else if (sensorValue.FrontSensor < 2300) { tempF = 13; }
  else if (sensorValue.FrontSensor < 2400) { tempF = 12; }
  else if (sensorValue.FrontSensor < 2610) { tempF = 11; }
  else if (sensorValue.FrontSensor < 2720) { tempF = 10; }
  else if (sensorValue.FrontSensor < 3250) { tempF = 5; }
  
  // Rear
  if (sensorValue.RearSensor < 400) { tempR = 100; } 
  else if (sensorValue.RearSensor < 700) { tempR = 40; }
  else if (sensorValue.RearSensor < 825) { tempR = 35; }
  else if (sensorValue.RearSensor < 1100) { tempR = 30; }
  else if (sensorValue.RearSensor < 1300) { tempR = 25; }
  else if (sensorValue.RearSensor < 1560) { tempR = 20; }
  else if (sensorValue.RearSensor < 1670) { tempR = 19; }
  else if (sensorValue.RearSensor < 1725) { tempR = 18; }
  else if (sensorValue.RearSensor < 1800) { tempR = 17; }
  else if (sensorValue.RearSensor < 1900) { tempR = 16; }
  else if (sensorValue.RearSensor < 2000) { tempR = 15; }
  else if (sensorValue.RearSensor < 2150) { tempR = 14; }
  else if (sensorValue.RearSensor < 2280) { tempR = 13; }
  else if (sensorValue.RearSensor < 2400) { tempR = 12; }
  else if (sensorValue.RearSensor < 2600) { tempR = 11; }
  else if (sensorValue.RearSensor < 2810) { tempR = 10; }
  else if (sensorValue.RearSensor < 3250) { tempR = 5; }
  
  sensorValue.RearSensor = tempR;
  sensorValue.FrontSensor = tempF;
  return sensorValue;
}
//----------------------------------------------------------------
void pinConfSetup(uint8_t p_Portnum, uint8_t p_Pinnum, uint8_t p_Funcnum, uint8_t p_Pinmode, uint8_t p_OpenDrain)
{
	//Sets up the pin to the spec that has been passed to it
	PINSEL_CFG_Type PinCfg;
	PinCfg.Funcnum   = p_Funcnum;
	PinCfg.OpenDrain = p_OpenDrain;
	PinCfg.Pinmode   = p_Pinmode;
	PinCfg.Portnum   = p_Portnum;
	PinCfg.Pinnum 	 = p_Pinnum;
	PINSEL_ConfigPin(&PinCfg);
}
//----------------------------------------------------------------
SensorPair getLeftSensorValues()
{

	struct SensorPair returnValue;
	//assigns the FL and BL to the SensorPair
	returnValue.FrontSensor = ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_0);
	returnValue.RearSensor = ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_1);

  if ((returnValue.FrontSensor > NO_WALL) && (returnValue.RearSensor > NO_WALL)) {
    // returns the SensorPair
	  return returnValue; // roundingValues(returnValue);
	}
	if (returnValue.FrontSensor < NO_WALL) {
	  returnValue.FrontSensor = 0;
	}
	if (returnValue.RearSensor < NO_WALL) {
	  returnValue.RearSensor = 0;
	}
	return returnValue; // roundingValues(returnValue);
}
//----------------------------------------------------------------
SensorPair getRightSensorValues()
{
	// creates the return value
	struct SensorPair returnValue;

	//assigns the FL and BL to the SensorPair
	returnValue.FrontSensor = ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_4);
	returnValue.RearSensor = ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_2);

  if ((returnValue.FrontSensor > NO_WALL) && (returnValue.RearSensor > NO_WALL)) {
    // returns the SensorPair
	  return returnValue; // roundingValues(returnValue);
	}
	if (returnValue.FrontSensor < NO_WALL) {
	  returnValue.FrontSensor = 0;
	}
	if (returnValue.RearSensor < NO_WALL) {
	  returnValue.RearSensor = 0;
  }
	return returnValue; // roundingValues(returnValue);
}
//----------------------------------------------------------------
int getFrontSensorValue()
{
  unsigned temp = GPIO_ReadValue(0);
  int temp17 =  (temp >> 17) & 1;
  currentReadings[4] = temp17 ;
  if (currentReadings[4] > 0)
  	return 0;
  else
    return 1;
}
//----------------------------------------------------------------
void initSensors()
{
	// configures the analogue pins
	pinConfSetup(PINSEL_PORT_0, analogSensorPins[0], PINSEL_FUNC_1, PINSEL_PINMODE_PULLUP,PINSEL_PINMODE_NORMAL); //FL - 23
	pinConfSetup(PINSEL_PORT_0, analogSensorPins[1], PINSEL_FUNC_1, PINSEL_PINMODE_PULLUP,PINSEL_PINMODE_NORMAL);	//BL - 24
	pinConfSetup(PINSEL_PORT_0, analogSensorPins[2], PINSEL_FUNC_1, PINSEL_PINMODE_PULLUP,PINSEL_PINMODE_NORMAL);	//BR - 25
	pinConfSetup(PINSEL_PORT_1, analogSensorPins[3], PINSEL_FUNC_3, PINSEL_PINMODE_PULLUP,PINSEL_PINMODE_NORMAL); //FR - 30
	// sets the direction of the GPIO pin and clears the value.
	GPIO_SetDir(0, frontSensor, 0);
	GPIO_IntCmd(0, frontSensor, 1);
	NVIC_EnableIRQ(EINT3_IRQn);
	// Set up the ADC sampling at 200kHz (maximum rate).
	ADC_Init(LPC_ADC, 200000);

	//Allows the channels to communicate
	ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_0, ENABLE);
	ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_1, ENABLE);
	ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_2, ENABLE);
	ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_4, ENABLE); // enable this you fool

	// Set ADC to continuously sample.
	ADC_StartCmd (LPC_ADC, ADC_START_CONTINUOUS);

	// Set ADC to start converting.
	ADC_BurstCmd (LPC_ADC, ENABLE);
	//Interrupts not needed as sensor readings are provided when requested.
}
//----------------------------------------------------------------
void EINT3_IRQHandler() {
  //Check if this is "something in the way" or "nothing in the way, actually"
  if (getFrontSensorValue() && isMovingForward()) {
    //Something in the way
    brake();
    frontIRQ_triggered = 1;
    runAway();
  } else if (getFrontSensorValue() == 0 && frontIRQ_triggered) {
    //Nothing in the way, actually
    frontIRQ_triggered = 0;
  }
}
