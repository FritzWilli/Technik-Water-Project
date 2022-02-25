// Plant.h

#pragma once

#ifndef _PLANT_h
#define _PLANT_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif


#endif

class Plant {
private:
	int waterUsage; //unit in ml/d
public:
	//Plant(int waterUsage_);
	int getWaterUsage();
	void setWaterUsage(int waterUsage_);
};
