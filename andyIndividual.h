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

SensorPair noteValuesLeft(SensorPair sensorValue);

SensorPair volumeValuesRight(SensorPair sensorValue);

void setNote();

void setVolume();

#endif
