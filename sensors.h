//----------------------------------------------------------------
#ifndef Sensors
#define Sensors
//----------------------------------------------------------------
/**
* This struct is the return value of the get sensor function
* it will contain values for the sensor pair that are called.
* If only the fron sensor is needed then it'll return the value 
* in the frontsensor variable.
*
* @author Christopher King
*/
typedef struct SensorPair {
	uint16_t FrontSensor;
	uint16_t RearSensor;
}SensorPair;
//----------------------------------------------------------------
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
void pinConfSetup(uint8_t p_Portnum, uint8_t p_Pinnum, uint8_t p_Funcnum, uint8_t p_Pinmode, uint8_t p_OpenDrain);
//----------------------------------------------------------------
/**
*	returns the value of the left sensors, both front and rear
*
* @author Christopher King
* @return returns a SensorPair which contains .FrontSensor and .RearSensor 
*/ 
struct SensorPair getLeftSensorValues();
//----------------------------------------------------------------
/**
*	returns the value of the Right sensors, both front and rear
*
* @author Christopher King
* @return returns a SensorPair which contains .FrontSensor and .RearSensor 
*/ 
struct SensorPair getRightSensorValues();
//----------------------------------------------------------------
/**
*	returns the value of the from sensor
*
* @author Christopher King
* @return returns the current value of the front sensor
*/
uint16_t getFrontSensorValue();
//----------------------------------------------------------------
/**
* This method initialises the Sensors by setting 
* up the pins on the MBED board
*
* @author Christopher King
*/ 
void initialiseSensors();
//----------------------------------------------------------------
/**
* This method is called whenever there is a change in the ADC values
* it is then converted and sent to a dummy USB terminal. This is here purely for testing,
* it will not be part of the final program.
*
* @author Christopher King.
*/
void ADC_IRQHandler();

void GPIO_IRQHandler();
//----------------------------------------------------------------
#endif
//----------------------------------------------------------------
