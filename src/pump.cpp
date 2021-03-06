/******************************************************************************
 * Author: Nicholas Pelham
 * Date  : 5/30/2017
 *****************************************************************************/

#include "task.hpp"
#include "pump.hpp"
#include "volume.hpp"
#include <wiringPi.h>
#include <iostream>

Pump::Pump(int ms, Volume & s, Volume & d, int p) : Task(ms) {
	pin = p;
	source = &s;
	destination = &d;
	state = START;
	power_flag = 0;
}

Pump::Pump(int ms, Volume & s, int p) : Task(ms) {
	pin = p;
	source = &s;
	destination = NULL;
	state = START;
	power_flag = 0;
}

int Pump::tick_function() {

	/* State transitions */
	switch(state) {
		case INIT:
			state = OFF;
			break;
		case ON:
			if (!power_flag) {
				state = OFF;
			} else if (destination != NULL 
					&& destination->is_full()) {
				power_flag = 0;
				state = OFF;	
			} else if (source->is_empty()) {
				power_flag = 0;
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
			std::cout << "Initializing pump on pin " << pin
				<< "..." << std::endl;

			pinMode(pin, OUTPUT);
			digitalWrite(pin, HIGH);
			break;
		case ON:
			digitalWrite(pin, LOW);
			break;
		case OFF:
			digitalWrite(pin, HIGH);
			break;
		default:
			break;
	}

	return 0;
}

int Pump::on() {
	power_flag = 1;
}

int Pump::off() {
	power_flag = 0;
}
