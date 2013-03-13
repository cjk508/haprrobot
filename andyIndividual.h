/**********************************************************************//**
 *	@file andyIndividual.h
 *	@brief Header file for Andy's individual project
 *
 *	@author	Andrew Durant
 *	@version: V1.0
 *	@date: 12 March 2013
 */

#ifndef ANDY_INC
#define ANDY_INC

#include "sensors.h"

/**
 * Converts sensor readings into note values
 *
 * @author Andrew Durant
 * @param sensorValue takes in raw sensor values 
 * @return SensorPair a reference for a play command
 */
SensorPair noteValuesLeft(SensorPair sensorValue);

/**
 * Converts sensor readings into volume values
 *
 * @author Andrew Durant
 * @param sensorValue takes in raw sensor values 
 * @return SensorPair a reference for a play command
 */
SensorPair volumeValuesRight(SensorPair sensorValue);

/**
 * Read sensor values, convert and send play command for notes
 *
 * @author Andrew Durant
 */
void setNote();

/**
 * Read sensor values, convert and send play command for volume
 *
 * @author Andrew Durant
 */
void setVolume();

#endif
