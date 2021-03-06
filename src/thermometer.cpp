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

	channel = chan;
	state = START;
}

int Thermometer::tick_function() {

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
			std::cout << "Initializing Thermometer on A" 
				<< channel << "..." << std::endl;

			break;
		case POLL_TEMP:
			temperature = poll_temp();
			//std::cout << "Temp " << channel << ": " 
				//<< temperature << std::endl;
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
	double tempC = v_to_c(volts);
	double tempF = c_to_f(tempC);
	return tempF;
}

double Thermometer::v_to_c(double v) {
	return (v - 0.5) * 100;
}

double Thermometer::c_to_f(double c) {
	return (c * 9.0 / 5.0) + 32;
}
