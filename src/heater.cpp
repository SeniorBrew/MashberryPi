/******************************************************************************
 * Author: Nicholas Pelham
 * Date  : 4/27/2017
 *****************************************************************************/

#include "testconstants.h"

#include "task.hpp"
#include "thermometer.hpp"
#include "heater.hpp"
#include <wiringPi.h>
#include <iostream>

Heater::Heater(int ms, int p) : Task(ms) {

	pin = p;
	power_flag = 0;
	state = START;
}

int Heater::tick_function() {

	/* State transitions */
	switch(state) {
		case INIT:
			state = OFF;
			break;
		case ON:
			if (!power_flag) {
				state = OFF;
			} else {
				state = ON;
			}
			break;
		case OFF:
			if (power_flag) {
				state = ON;
			} else {
				state = OFF;
			}
			break;
		default: 
			state = INIT;
			break;
	}

	/* State actions */
	switch(state) {
		case INIT:
			std::cout << "Initializing heater on pin " << pin
				<< "..." << std::endl;

			pinMode(pin, OUTPUT);
			digitalWrite(pin, LOW);
			break;
		case ON:
			digitalWrite(pin, HIGH);
			break;
		case OFF:
			digitalWrite(pin, LOW);
			break;
		default:
			break;
	}
	
	return 0;
}

int Heater::on() {
	power_flag = 1;
}

int Heater:off() {
	power_flag = 0;
}
