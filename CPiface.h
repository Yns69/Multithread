#pragma once
#include <stdio.h>
#include <wiringPi.h>
#include <piFace.h>
// Use 200 as the pin-base for the PiFace board, and pick a pin
// for the LED that's not connected to a relay
#define PIFACE 200
#define LED (PIFACE+2)
class CPiface
{
private: 
	void init(unsigned int AdrBase);
public:
	CPiface();
	CPiface(unsigned int AdrBase);
	~CPiface();
	void AllumerLed(unsigned int);
	void EteindreLed(unsigned int);
	void RazLed();
	void AllLed();
	void InitPullUp();
	int TestBouton();
};

