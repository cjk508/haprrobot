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
	PINSEL_CFG_Type PinCfg;
	int i = 0;
	for(i=0;i<5;i++)
	{
		PinCfg.FuncNum = 2;
		PinCfg.OpenDrain = 0;				
		PinCfg.PinMode = 0
		PinCf.Pinnum = analogSensorPins[i];
		PINSEL_ConfigPin(&PinCfg);
	}
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
	initialiseSensors();
}
