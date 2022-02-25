/*
 Name:		Arduino_Water.ino
 Created:	2/21/2022 5:25:19 PM
 Author:	Vitas Ruhland
*/

//local dependencies
#include "Compute.h"
#include "Plant.h"
#include "Plant.h"
#include "Compute.h"

//important constants for the system
constexpr uint8_t RELAIS_PIN = 2;
constexpr uint8_t WATERSENSOR_PIN = A0;
constexpr uint8_t ROTARYENCODER_PIN = A1;

//important values for program start
bool ONSTARTWATER = true;
static constexpr uint8_t plantArrSize = 5;// check if used

constexpr uint8_t PUMPWATEROUTPUT = 50; //unit in ml/min
constexpr uint8_t TIMESON = 3; //unit in 1/d


//main objects for system
Plant plant[plantArrSize];
Compute cmp(1);


void setup()
{
	Serial.begin(9600);

	Serial.println("Initializing plant configuration");
	uint8_t waterUsageTemp = 100;
	for (int i = 0; i < plantArrSize; i++)
	{
		plant[i].setWaterUsage(waterUsageTemp);
		waterUsageTemp += 50;
	}
	Serial.println("Plant initialized successfully");

	//set all pins for modules
	Serial.println("Initializing PIN allocation");
	pinMode(RELAIS_PIN, OUTPUT);
	pinMode(WATERSENSOR_PIN, INPUT);
	Serial.println("Everything successfully initialized");
}


int getRotaryIND()
{
	//add code for rot-enc pos
	return 0;
}


void loop()
{
	if (ONSTARTWATER) {
		digitalWrite(RELAIS_PIN, HIGH);
		delay(cmp.compTimeOn(plant[getRotaryIND()].getWaterUsage(), PUMPWATEROUTPUT, TIMESON));
		digitalWrite(RELAIS_PIN, LOW);
		ONSTARTWATER = false;
	}
	else
	{
		delay(cmp.compTimeOff(plant[getRotaryIND()].getWaterUsage(), PUMPWATEROUTPUT, TIMESON));
		digitalWrite(RELAIS_PIN, HIGH);
		delay(cmp.compTimeOn(plant[getRotaryIND()].getWaterUsage(), PUMPWATEROUTPUT, TIMESON));
		digitalWrite(RELAIS_PIN, LOW);
	}
}