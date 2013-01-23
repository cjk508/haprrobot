int analogSensorPins[] = {23, 24, 25, 30};
const unsigned long frontSensor = 0<<17;

/**
* This method initialises the Sensors by setting 
* up the pins on the MBED board
*
* @author Christopher King
*/
void initialiseSensors()
{
	// Sets up the counter and the pin config so that the analogue pins can be sete
	PINSEL_CFG_Type PinCfg;
	PinCfg.Funcnum   = PINSEL_FUNC_1;
	PinCfg.OpenDrain = PINSEL_PINMODE_NORMAL;
	PinCfg.Pinmode   = PINSEL_PINMODE_PULLUP;
	PinCfg.Portnum   = PINSEL_PORT_0;	
	int i;
	for(i=0;i<3;i++)
	{
		PinCfg.Pinnum = analogSensorPins[i];
		PINSEL_ConfigPin(&PinCfg);
	}
	PinCfg.Funcnum   = PINSEL_FUNC_3;
	PinCfg.Pinnum = analogSensorPins[3];
	PINSEL_ConfigPin(&PinCfg);	
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
	GPIO_SetDir(0, frontSensor, 0);
	GPIO_ClearValue(1, frontSensor);
}

void ADC_IRQHandler(void)
{
	uint16_t FL = ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_0);
	uint16_t FR = ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_3);		
	uint16_t BL = ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_1);
	uint16_t BR = ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_2);		
	uint16_t F = GPIO_ReadValue(frontSensor);	
	_DBG_("#################");
	_DBG("FL:");	_DBD16(FL); _DBG_("");
	_DBG("BL:");	_DBD16(BL); _DBG_("");
	_DBG("FR:");	_DBD16(FR); _DBG_("");
	_DBG("BR:");	_DBD16(BR); _DBG_("");			
	_DBG("F:");	_DBD16(F);_DBG_("");	
	_DBG_("#################");	
	GPIO_ClearValue(1, frontSensor);			
}
