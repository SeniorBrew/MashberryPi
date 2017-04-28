/******************************************************************************
 * Author: Nicholas Pelham
 * Date  : 4/27/2017
 *****************************************************************************/

#include "task.hpp"
#include "heater.hpp"
#include <wiringPi.h>
#include <iostream>

Heater::Heater(int ms) : Task(ms) {
	pinMode(0, OUTPUT);
	digitalWrite(0, LOW);
	state = INIT;
}

int Heater::tick_function() {

	/* State transitions */
	switch(state) {
		case INIT:
			state = ON;
			break;
		case ON:
			state = OFF;
			break;
		case OFF:
			state = ON;
			break;
		default: 
			state = INIT;
			break;
	}

	/* State actions */
	switch(state) {
		case INIT:
			digitalWrite(0, LOW);
			break;
		case ON:
			digitalWrite(0, HIGH);
			break;
		case OFF:
			digitalWrite(0, LOW);
			break;
		default:
			break;
	}

	return 0;
}
