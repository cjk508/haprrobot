int analogSensorPins[] = {23, 24, 25, 30};
const unsigned long frontSensor = 0<<17;
uint16_t currentReadings[] = {0,0,0,0,0};
/**
* This method initialises the Sensors by setting 
* up the pins on the MBED board
*
* @author Christopher King
* @param p_Portnum		The port number of the Pin (between 0 and 4)
* @param p_Pinnum 		The pin number of the Pin
* @param p_Funcnum		The function of the pin (between 0 and 3)
* @param p_Pinmode 		The mode of the pin (PULLUP, Tristate or pulldown)
* @param p_OpenDrain	Whether the pin is in open drain mode or not
*/
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

/**
* This method initialises the Sensors by setting 
* up the pins on the MBED board
*
* @author Christopher King
*/
void initialiseSensors()
{
	// configures the analogue pins
	pinConfSetup(PINSEL_PORT_0, analogSensorPins[0], PINSEL_FUNC_1, PINSEL_PINMODE_PULLUP,PINSEL_PINMODE_NORMAL);
	pinConfSetup(PINSEL_PORT_0, analogSensorPins[1], PINSEL_FUNC_1, PINSEL_PINMODE_PULLUP,PINSEL_PINMODE_NORMAL);	
	pinConfSetup(PINSEL_PORT_0, analogSensorPins[2], PINSEL_FUNC_1, PINSEL_PINMODE_PULLUP,PINSEL_PINMODE_NORMAL);	
	pinConfSetup(PINSEL_PORT_0, analogSensorPins[3], PINSEL_FUNC_3, PINSEL_PINMODE_PULLUP,PINSEL_PINMODE_NORMAL);	

	GPIO_SetDir(0, frontSensor, 0);
	GPIO_ClearValue(1, frontSensor);

	// Set up the ADC sampling at 200kHz (maximum rate).
	ADC_Init(LPC_ADC, 200000);

	// Enable ADC channel 1.
	ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_1, ENABLE);

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
	int changed = 0;
	if(currentReadings[0] != ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_0))
	{
		currentReadings[0] = ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_0);
		changed = 1;
	}
	
	if(currentReadings[1] != ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_3))
	{
		currentReadings[1] = ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_3);
		changed = 1;
	}
	
	if(currentReadings[2] != ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_1))
	{
		currentReadings[2] = ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_1);
		changed = 1;
	}
	
	if(currentReadings[3] != ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_2))
	{
		currentReadings[3] = ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_2);
		changed = 1;
	}				
	if (currentReadings[4] != GPIO_ReadValue(frontSensor))
	{
		currentReadings[4] = GPIO_ReadValue(frontSensor);
		changed = 1;
	}	
	
	if(changed == 1)
	{
		_DBG_("#################");
		_DBG("FL:");	_DBD16(currentReadings[0]); _DBG_("");
		_DBG("BL:");	_DBD16(currentReadings[2]); _DBG_("");
		_DBG("FR:");	_DBD16(currentReadings[1]); _DBG_("");
		_DBG("BR:");	_DBD16(currentReadings[3]); _DBG_("");			
		_DBG("F:");	_DBD16(currentReadings[4]);_DBG_("");	
		_DBG_("#################");	
	}
	GPIO_ClearValue(1, frontSensor);			
}
