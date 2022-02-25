// 
// 
// 

#include "Compute.h"

Compute::Compute(int placeholder)
{}

int Compute::compTimeOn(int plntWaterUsage, int pumpWaterOutput, int timesOn)
{
	return int(plntWaterUsage / (pumpWaterOutput * timesOn) * 60000);
}

int Compute::compTimeOff(int plntWaterUsage, int pumpWaterOutput, int timesOn)
{
	return int((1440 - (compTimeOn(plntWaterUsage, pumpWaterOutput, timesOn) * timesOn)) * 60000);
}
