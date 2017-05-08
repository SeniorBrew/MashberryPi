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

Heater::Heater(int ms, Timer &timer, Thermometer & hlt, Thermometer & mash, 
		int p) : Task(ms) {
	pin = p;
	time = &timer;
	hlt_therm = &hlt;
	mash_therm = &mash;
	state = START;
}

int Heater::tick_function() {

	/* State transitions */
	switch(state) {
		case INIT:
			std::cout << "PRE_MASH" << std::endl;
			state = PRE_MASH;
			break;
		case PRE_MASH:
			if (hlt_therm->get_temp() >= MASH_TEMP) {
				std::cout << "TRANSFER" << std::endl;
				state = TRANSFER;
			} else {
				state = PRE_MASH;
			}
			break;
		case TRANSFER:
			/* TODO: Pump/Vol logic */
			time->start_timer();
			std::cout << "MASH" << std::endl;
			state = MASH;
			break;
		case MASH:
			if (time->get_minutes() >= MASH_TIME) {
				std::cout << "PRE_SPARGE" << std::endl;
				state = PRE_SPARGE;
			} else {
				state = MASH;
			}
			break;
		case PRE_SPARGE:
			if (hlt_therm->get_temp() >= SPARGE_TEMP) {
				std::cout << "SPARGE" << std::endl;
				state = SPARGE;
			} else {
				state = PRE_SPARGE;
			}
			break;
		case SPARGE:
			/* TODO: Pump/Vol logic */
			std::cout << "END" << std::endl;
			state = END;
			break;
		case END:
			state = END;
			break;
		default: 
			state = INIT;
			break;
	}

	/* State actions */
	switch(state) {
		case INIT:
			pinMode(pin, OUTPUT);
			digitalWrite(pin, LOW);
			break;
		case PRE_MASH:
			//std::cout << "HEATER ON" << std::endl;
			digitalWrite(pin, HIGH);
			break;
		case TRANSFER:
			//std::cout << "HEATER OFF" << std::endl;
			digitalWrite(pin, LOW);
			break;
		case MASH:
			if (hlt_therm->get_temp() >= MASH_TEMP + 10) {
				//std::cout << "HEATER OFF" << std::endl;
				digitalWrite(pin, LOW);
			} else {
				//std::cout << "HEATER ON" << std::endl;
				digitalWrite(pin, HIGH);
			}
			break;
		case PRE_SPARGE:
			//std::cout << "HEATER ON" << std::endl;
			digitalWrite(pin, HIGH);
			break;
		case SPARGE:
			//std::cout << "HEATER OFF" << std::endl;
			digitalWrite(pin, LOW);
			break;
		case END:
			//std::cout << "HEATER OFF" << std::endl;
			digitalWrite(pin, LOW);
			break;
		default:
			break;
	}

	return 0;
}
