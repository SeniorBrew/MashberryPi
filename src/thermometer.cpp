/******************************************************************************
 * Author: Nicholas Pelham
 * Date  : 5/4/2017
 *
 *****************************************************************************/

#include "task.hpp"
#include "thermometer.hpp"
#include <iostream>
#include <wiringPi.h>
#include <ads1115.h>

Thermometer::Thermometer(int ms, int chan) : Task(ms) {

	std::cout << "Initializing Thermometer " << chan << "..." << std::endl;

	channel = chan;
	state = START;
}

int Thermometer::tick_function() {

	std::cout << "Thermometer " << channel << " Tick" << std::endl;

	/* State transitions */
	switch(state) {
		case INIT:
			state = POLL_TEMP;
			break;
		case POLL_TEMP:
			state = POLL_TEMP;
			break;
		default: 
			state = INIT;
			break;
	}

	/* State actions */
	switch(state) {
		case INIT:
			break;
		case POLL_TEMP:
			temperature = poll_temp();
			std::cout << "Temp " << channel << ": " << temperature << std::endl;
			break;
		default:
			break;
	}
	return 0;
}

double Thermometer::poll_temp(void) {
	int read = analogRead(2222 + channel);
	double volts = read * 4.096;
	volts /= 32767.0;
	double tempC = (volts - 0.5) * 100;
	double tempF = (tempC * 9.0 / 5.0) + 32.0;
	return tempF;
}
