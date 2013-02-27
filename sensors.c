//----------------------------------------------------------------
#include "sensors.h"
#include "debug_frmwrk.h"
//----------------------------------------------------------------
//constants
const uint16_t DESIRED_DISTANCE = 1500;
const uint16_t VERY_CLOSE = 2700;
const uint16_t NO_WALL = 2500;
const unsigned long frontSensor = 1<<17; //this was 17 on robot 5
//Variables
int analogSensorPins[] = {23, 24, 25, 30}; // FL, BL, BR, FR
//int analogSensorPins[] = {25, 26, 23, 24}; // FL, BL, BR, FR
uint32_t currentReadings[] = {0,0,0,0,0}; // initialised readings
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

  if ((returnValue.FrontSensor > NO_WALL) && (returnValue.RearSensor > NO_WALL))
    // returns the SensorPair
	  return roundingValues(returnValue);
	else if (returnValue.FrontSensor < NO_WALL)
	  returnValue.FrontSensor = 0;
	else if (returnValue.RearSensor < NO_WALL)
	  returnValue.FrontSensor = 0;
	return roundingValues(returnValue);
}
//----------------------------------------------------------------
SensorPair getRightSensorValues()
{
	// creates the return value
	struct SensorPair returnValue;

	//assigns the FL and BL to the SensorPair
	returnValue.FrontSensor = ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_4);
	returnValue.RearSensor = ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_2);

  if ((returnValue.FrontSensor > NO_WALL) && (returnValue.RearSensor > NO_WALL))
    // returns the SensorPair
	  return roundingValues(returnValue);
	else if (returnValue.FrontSensor < NO_WALL)
	  returnValue.FrontSensor = 0;
	else if (returnValue.RearSensor < NO_WALL)
	  returnValue.FrontSensor = 0;

	return roundingValues(returnValue);
}
//----------------------------------------------------------------
int getFrontSensorValue()
{
  unsigned temp = GPIO_ReadValue(0);
  int temp17 =  (temp >> 17) & 1;
  currentReadings[4] = temp17 ;
  if (currentReadings[4] > 0)
  	return 1;
  else
    return 0;
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
	GPIO_SetDir(0, frontSensor, 0); /**@todo check that this initialisation is correct. If it is then get help*/
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
