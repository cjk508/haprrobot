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


const char *note[] = {
                    "<<<<C",
                    "<<<<D",
                    "<<<<E",
                    "<<<<F",
                    "<<<<G",
                    "<<<<A",
                    "<<<<B",
                    "<<<C",
                    "<<<D",
                    "<<<E",
                    "<<<F",
                    "<<<G",
                    "<<<A",
                    "<<<B",
                    "<<C",
                    "<<D",
                    "<<E",
                    "<<F",
                    "<<G",
                    "<<A",
                    "<<B",
                    "<C",
                    "<D",
                    "<E",
                    "<F",
                    "<G",
                    "<A",
                    "<B",
                    "C",
                    "D",
                    "E",
                    "F",
                    "G",
                    "A",
                    "B",
                    ">C",
                    ">D",
                    ">E",
                    ">F",
                    ">G",
                    ">A",
                    ">B",
                    ">>C",
                    ">>D",
                    ">>E",
                    ">>F",
                    ">>G",
                    ">>A",
                    ">>B",
                    ">>>C",
                    ">>>D",
                    ">>>E",
                    ">>>F",
                    ">>>G",
                    ">>>A",
                    ">>>B",
                    ">>>>C",
                    ">>>>D",
                    ">>>>E",
                    ">>>>F",
                    ">>>>G",
                    ">>>>A",
                    ">>>>B"};

const char *volume[] = {
                        "V0",
                        "V1",
                        "V2",
                        "V3",
                        "V4",
                        "V5",
                        "V6",
                        "V7",
                        "V8",
                        "V9",
                        "V10",
                        "V11",
                        "V12",
                        "V13",
                        "V14",
                        "V15"};


SensorPair noteValuesLeft(SensorPair sensorValue);

SensorPair volumeValuesRight(SensorPair sensorValue);

void setNote();

void setVolume();

#endif
