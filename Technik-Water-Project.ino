/*
 Name:		Arduino_Water.ino
 Created:	2/21/2022 5:25:19 PM
 Author:	Vitas Ruhland
*/

#include <arduino-timer.h>

//#include "Compute.h"
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
void* voidptr;
int timeToWater;
int timeToWait;
int RotaryState;


//main objects for system
Plant plant[plantArrSize];
//Compute cmp(1);
auto timer = timer_create_default();


int compTimeOn(int plntWaterUsage, int pumpWaterOutput, int timesOn)
{
	return int(plntWaterUsage / (pumpWaterOutput * timesOn) * 60000);
}

int compTimeOff(int plntWaterUsage, int pumpWaterOutput, int timesOn)
{
	return int((1440 - (compTimeOn(plntWaterUsage, pumpWaterOutput, timesOn) * timesOn)) * 60000);
}

//refresh timer imortant


bool toggleRelay(void *) 
{
	digitalWrite(RELAIS_PIN, !digitalRead(RELAIS_PIN));
	return true;
}


bool relayhandler(void *)
{
	toggleRelay(voidptr);
	timer.in(timeToWater, toggleRelay);
	return true;
}


void setup()
{
	Serial.begin(9600);

	Serial.println("Initialize time constants");

	int timeToWater = compTimeOn(plant[getRotaryIND()].getWaterUsage(), PUMPWATEROUTPUT, TIMESON);
	int timeToWait = int((1440 - (compTimeOn(plant[getRotaryIND()].getWaterUsage(), PUMPWATEROUTPUT, TIMESON) * TIMESON)) * 60000);



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



	Serial.println("Initializing timer");
	timer.every(timeToWait + timeToWater, relayhandler);
	timer.every(timeToWater, relayhandler);
}




int getRotaryIND()
{
	//add code for rot-enc pos
	return 0;
}


void getStatus() 
{
	
}

/*bool mainCompute()
{
	if (cmp.compTimer(time, timeToWait)) 
	{
		time = millis();
		return true;
	}
	else 
	{
		return false;
	}
}*/

void loop()
{
	

	//getStatus();
	
	timer.tick();
}