#include "debug_frmwrk.h"

const int analogSensorPins = {15, 16, 17, 19};
const unsigned long frontSensor = 1<<12;

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
	int i;
	for(i=0;i<5;i++)
	{
		PinCfg.Funcnum   = PINSEL_FUNC_1;
		PinCfg.OpenDrain = PINSEL_PINMODE_NORMAL;
		PinCfg.Pinmode   = PINSEL_PINMODE_PULLUP;
		PinCfg.Portnum   = PINSEL_PORT_0;
		PinCf.Pinnum = analogSensorPins[i];
		PINSEL_ConfigPin(&PinCfg);
	}
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
	GPIO_SetDir(1, frontSensor, 1);
	GPIO_ClearValue(1, frontSensor);
}

void ADC_IRQHandler(void)
{
	int FL = ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_0);
	int FR = ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_3);		
	int BL = ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_1);
	int BR = ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_2);		
	int F = GPIO_ReadValue(frontSensor);	
	_DBG("FL:");	_DBD(FL);_DBG_();
	_DBG("BL:");	_DBD(BL);_DBG_();
	_DBG("FR:");	_DBD(FR);_DBG_();
	_DBG("BR:");	_DBD(BR);_DBG_();			
	_DBG("F:");	_DBD(F);_DBG_();	
	GPIO_ClearValue(1, frontSensor);			
}
/**
* Main function that controls the initialisation
*
* @author Christopher King
*/
void main(void)
{
	debug_frmwrk_init();
	initialiseSensors();
	_DBG_("Sensors Initialised");
	
}
