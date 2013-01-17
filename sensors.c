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
	// Sets up the counter and the pin config so that the analogue pins can be set
	PINSEL_CFG_Type PinCfg;
	int i;
	for(i=0;i<5;i++)
	{
		PinCfg.FuncNum = 2;
		PinCfg.OpenDrain = 0;				
		PinCfg.PinMode = 0
		PinCf.Pinnum = analogSensorPins[i];
		PINSEL_ConfigPin(&PinCfg);
	}
	//Initialises the DAC so it can analyse the input
	DAC_Init(LPC_DAC);
	GPIO_SetDir(1, frontSensor, 1);
	GPIO_ClearValue(1, frontSensor);
}


/**
* Main function that controls the initialisation
*
* @author Christopher King
*/
void main()
{
	debug_frmwrk_init();
	initialiseSensors();
	_DBG_("Sensors Initialised");
	
}
