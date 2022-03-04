// Compute.h

#pragma once

#ifndef _COMPUTE_h
#define _COMPUTE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif


#endif


class Compute {

public:
	Compute(int placeholder);
	int compTimeOn(int plntWaterUsage, int pumpWaterOutput, int timesOn);
	int compTimeOff(int plntWaterUsage, int pumpWaterOutput, int timesOn);
	bool compTimer(int time, int timeToWait);
};
