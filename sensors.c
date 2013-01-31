#include "sensors.h"
//----------------------------------------------------------------
//constants
const unsigned long frontSensor = 0<<17;

//Variables
int analogSensorPins[] = {23, 24, 25, 30}; // FL, BL, BR, FR
uint16_t currentReadings[] = {0,0,0,0,0}; // initialised readings
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

SensorPair getLeftSensorValues()
{
	
	struct SensorPair returnValue;
	//assigns the FL and BL to the SensorPair
	returnValue.FrontSensor = ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_0);
	returnValue.RearSensor = ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_1);	

	// returns the SensorPair
	return returnValue;
}

SensorPair getRightSensorValues()
{
	// creates the return value
	struct SensorPair returnValue;
	
	//assigns the FL and BL to the SensorPair
	returnValue.FrontSensor = ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_4);
	returnValue.RearSensor = ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_2);

	// returns the SensorPair	
	return returnValue;
}
// Test routine

void delay(void)
{
	int i = 0;
	while(i<1000000)
	{
		i=i+1;
	}
	_DBG_("");
	_DBD16(GPIO_ReadValue(0));
	_DBG_("");
	delay();
}
uint16_t getFrontSensorValue()
{
	//returns the front sensor reading
	return GPIO_ReadValue(0);
}

void initialiseSensors()
{
	// configures the analogue pins
	pinConfSetup(PINSEL_PORT_0, analogSensorPins[0], PINSEL_FUNC_1, PINSEL_PINMODE_PULLUP,PINSEL_PINMODE_NORMAL);
	pinConfSetup(PINSEL_PORT_0, analogSensorPins[1], PINSEL_FUNC_1, PINSEL_PINMODE_PULLUP,PINSEL_PINMODE_NORMAL);	
	pinConfSetup(PINSEL_PORT_0, analogSensorPins[2], PINSEL_FUNC_1, PINSEL_PINMODE_PULLUP,PINSEL_PINMODE_NORMAL);	
	pinConfSetup(PINSEL_PORT_1, analogSensorPins[3], PINSEL_FUNC_3, PINSEL_PINMODE_PULLUP,PINSEL_PINMODE_NORMAL);	
	// sets the direction of the GPIO pin and clears the value.
	GPIO_SetDir(0, frontSensor, 0);
	//GPIO_IntCmd(0, frontSensor, 0);
	// Set up the ADC sampling at 200kHz (maximum rate).
	ADC_Init(LPC_ADC, 200000);
	
	//Allows the channels to communicate
	ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_0, ENABLE);
	ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_1, ENABLE);
	ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_2, ENABLE);
	ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_4, ENABLE);

	// Set ADC to continuously sample.
	ADC_StartCmd (LPC_ADC, ADC_START_CONTINUOUS);

	// Set ADC to start converting.
	ADC_BurstCmd (LPC_ADC, ENABLE);
	_DBG_("dlkgnsdl");
	// Enable interrupts for ADC conversion completing.
  NVIC_EnableIRQ(ADC_IRQn);

  _DBG_("Waiting for Interrupt 1");
  // Enable interrupts globally.
  __enable_irq();
  _DBG_("Waiting for Interrupt 2");
}

void ADC_IRQHandler(void)
{
	// counter made to refresh the readings.
	int counter = 0;
	// captures the readings at the point the interrupt is called
	uint16_t newReadings[] = {ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_0),ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_4),ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_1),ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_2),GPIO_ReadValue(frontSensor)};

	// refreshes the old readings
	while(counter < 5)
	{
		currentReadings[counter] = newReadings[counter];
		counter = counter+1;
	}
	_DBG_("#################");
	_DBG("FL:");	_DBD16(currentReadings[0]); _DBG_("");
	_DBG("BL:");	_DBD16(currentReadings[2]); _DBG_("");
	_DBG("FR:");	_DBD16(currentReadings[1]); _DBG_("");
	_DBG("BR:");	_DBD16(currentReadings[3]); _DBG_("");			
	_DBG("F:");	_DBD16(currentReadings[4]);_DBG_("");		
}

// Not Working!
/*void EINT3_IRQHandler(void)
{
	currentReadings[4]=GPIO_ReadValue(0);
	//outputs the readings to a dummy terminal
	_DBG_("#################");
	_DBG("FL:");	_DBD16(currentReadings[0]); _DBG_("");
	_DBG("BL:");	_DBD16(currentReadings[2]); _DBG_("");
	_DBG("FR:");	_DBD16(currentReadings[1]); _DBG_("");
	_DBG("BR:");	_DBD16(currentReadings[3]); _DBG_("");			
	_DBG("F:");	_DBD16(currentReadings[4]);_DBG_("");	
	GPIO_ClearInt(0, frontSensor);
}*/

