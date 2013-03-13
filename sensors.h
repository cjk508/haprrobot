/**************************************************************************//**
 * @file     sensors.h
 * @brief    Sets up and returns the IR sensor values
 * @version: V1
 * @date:    25. February 2013
 * @author   Christopher King <cjk508@york.ac.uk>
******************************************************************************/
//----------------------------------------------------------------
#ifndef SENSORS_INC
#define SENSORS_INC
//----------------------------------------------------------------
//CMSIS Includes
#include "lpc17xx_nvic.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_pinsel.h"
//Project Includes
//----------------------------------------------------------------
/**
* Stores whether the frontIRQ has stopped the robot
*/
int frontIRQ_triggered;
/**
* @brief Sensor return type, contains 2 integers FrontSensor and RearSensor
*
* This struct is the return value of the get sensor function
* it will contain values for the sensor pair that are called.
* If only the fron sensor is needed then it'll return the value
* in the frontsensor variable.
*
* @author Christopher King <cjk508@york.ac.uk> (Initial Coding)
*/
typedef struct SensorPair {
  /**
   * contains the value of the front sensor. Normally this will now be given in cm
   */
  uint16_t FrontSensor;
  /**
   * contains the value of the rear sensor, normally this will now be given in cm.
   */
  uint16_t RearSensor;
  }SensorPair;
//----------------------------------------------------------------
/**
* returns the rounded value of the sensor.
*
* @author Christopher King <cjk508@york.ac.uk> (Initial Coding)
* @author Andrew Durant (Debug)
* @param  sensorValue The value that should be rounded
* @return returns the rounded value
*/
SensorPair roundingValues(SensorPair sensorValue);
//----------------------------------------------------------------
/**
* Returns calibrated values in cm for the left sensors
*
* @author Andrew Durant (Initial Coding)
* @param  sensorValue The raw value from the sensors
* @return value in cm for the left side
*/
SensorPair calibratedValuesLeft(SensorPair sensorValue);
//----------------------------------------------------------------
/**
* Returns calibrated values in cm for the right sensors
*
* @author Andrew Durant (Initial Coding)
* @param  sensorValue The raw value from the sensors
* @return value in cm for the right side
*/
SensorPair calibratedValuesRight(SensorPair sensorValue);
//----------------------------------------------------------------
/**
* This method initialises the Sensors by setting up the pins on the MBED board
*
* @author Christopher King <cjk508@york.ac.uk> (Initial Coding)
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
* @author Christopher King <cjk508@york.ac.uk> (Initial Coding)
* @return returns a SensorPair which contains .FrontSensor and .RearSensor
*/
SensorPair getLeftSensorValues();
//----------------------------------------------------------------
 /**
*	returns the value of the Right sensors, both front and rear
*
* @author Christopher King <cjk508@york.ac.uk> (Initial Coding)
* @return returns a SensorPair which contains .FrontSensor and .RearSensor
*/
SensorPair getRightSensorValues();
//----------------------------------------------------------------
/**
*	returns the value of the from sensor
*
* @author Christopher King <cjk508@york.ac.uk> (Initial Coding)
* @return returns 0 unless it sees something, then returns one.
*/
int getFrontSensorValue();
//----------------------------------------------------------------
/**
* This method initialises the Sensors by setting up the pins on the MBED board
* 
* @author Christopher King <cjk508@york.ac.uk> (Initial Coding)
*/
void initSensors();
//----------------------------------------------------------------
/**
* This interrupt is called whenever the value of the front sensor
* changes. The front sensor reports either "nothing there" or "something there"
* This will slow down and stop the robot if something is in the way
* Or start moving again if previously stopped
*
* @author Lloyd Wallis <lpw503@york.ac.uk> (Initial Coding)
* @author Christopher King (revision - added resume on brake so motors will have same values)
*/
void EINT0_IRQHandler();
#endif
