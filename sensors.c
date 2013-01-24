#include "sensors.h"
//----------------------------------------------------------------
//constants
private const unsigned long frontSensor = 0<<17;

//Variables
private int analogSensorPins[] = {23, 24, 25, 30}; // FL, BL, BR, FR
private uint16_t currentReadings[] = {0,0,0,0,0}; // initialised readings
//----------------------------------------------------------------
void pinConfSetup(uint8_t p_Portnum, uint8_t p_Pinnum, uint8_t p_Funcnum, uint8_t p_Pinmode, uint8_t p_OpenDrain)
{
	PINSEL_CFG_Type PinCfg;
	PinCfg.Funcnum   = p_Funcnum;
	PinCfg.OpenDrain = p_OpenDrain;
	PinCfg.Pinmode   = p_Pinmode;
	PinCfg.Portnum   = p_Portnum;		
	PinCfg.Pinnum 	 = p_Pinnum;
	PINSEL_ConfigPin(&PinCfg);
}

struct SensorPair getLeftSensorValues()
{
	struct SensorPair returnValue;
	returnValue.FrontSensor = currentReadings[0];
	returnValue.RearSensor = currentReadings[2];	
	return returnValue;
}

struct SensorPair getRightSensorValues()
{
	struct SensorPair returnValue;
	returnValue.FrontSensor = currentReadings[1];
	returnValue.RearSensor = currentReadings[3];	
	return returnValue;
}

uint16_t getFrontSensorValue()
{
	return currentReadings[4];
}

void initialiseSensors()
{
	// configures the analogue pins
	pinConfSetup(PINSEL_PORT_0, analogSensorPins[0], PINSEL_FUNC_1, PINSEL_PINMODE_PULLUP,PINSEL_PINMODE_NORMAL);
	pinConfSetup(PINSEL_PORT_0, analogSensorPins[1], PINSEL_FUNC_1, PINSEL_PINMODE_PULLUP,PINSEL_PINMODE_NORMAL);	
	pinConfSetup(PINSEL_PORT_0, analogSensorPins[2], PINSEL_FUNC_1, PINSEL_PINMODE_PULLUP,PINSEL_PINMODE_NORMAL);	
	pinConfSetup(PINSEL_PORT_1, analogSensorPins[3], PINSEL_FUNC_3, PINSEL_PINMODE_PULLUP,PINSEL_PINMODE_NORMAL);	

	GPIO_SetDir(0, frontSensor, 0);
	GPIO_ClearValue(1, frontSensor);

	// Set up the ADC sampling at 200kHz (maximum rate).
	ADC_Init(LPC_ADC, 200000);
	
	ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_0, ENABLE);
	ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_1, ENABLE);
	ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_2, ENABLE);
	ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_4, ENABLE);

	// Set ADC to continuously sample.
	ADC_StartCmd (LPC_ADC, ADC_START_CONTINUOUS);

	// Set ADC to start converting.
	ADC_BurstCmd (LPC_ADC, ENABLE);

	// Enable interrupts for ADC conversion completing.
	NVIC_EnableIRQ(ADC_IRQn);

	// Enable interrupts globally.
	__enable_irq();
}

void ADC_IRQHandler(void)
{
	// changed value means that if anything has changed since the last reading then it'll print out the changes
	int counter = 0;
	uint16_t newReadings[] = {ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_0),ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_4),ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_1),ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_2),GPIO_ReadValue(frontSensor)};

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
	GPIO_ClearValue(1, frontSensor);			
}
