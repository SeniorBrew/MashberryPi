/******************************************************************************
 * Author: Nicholas Pelham
 * Date  : 4/27/2017
 *****************************************************************************/

#include "task.hpp"
#include "pump.hpp"
#include <wiringPi.h>
#include <iostream>

Pump::Pump(int ms) : Task(ms) {
	pinMode(3, OUTPUT);
	digitalWrite(3, LOW);
	state = INIT;
}

int Pump::tick_function() {

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
			digitalWrite(3, LOW);
			break;
		case ON:
			digitalWrite(3, HIGH);
			break;
		case OFF:
			digitalWrite(3, LOW);
			break;
		default:
			break;
	}

	return 0;
}
