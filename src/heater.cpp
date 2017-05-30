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

	std::cout << "Initializing Heater..." << std::endl;

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
			std::cout << std::endl << "PRE_MASH" << std::endl << std::endl;
			state = PRE_MASH;
			break;
		case PRE_MASH:
			if (hlt_therm->get_temp() >= MASH_TEMP) {
				std::cout << std::endl << "TRANSFER" << std::endl << std::endl;
				state = TRANSFER;
			} else {
				state = PRE_MASH;
			}
			break;
		case TRANSFER:
			/* TODO: Pump/Vol logic */
			time->start_timer();
			std::cout << std::endl << "MASH" << std::endl << std::endl;
			state = MASH;
			break;
		case MASH:
			if (time->get_minutes() >= MASH_TIME) {
				std::cout << std::endl << "PRE_SPARGE" << std::endl << std::endl;
				state = PRE_SPARGE;
			} else {
				state = MASH;
			}
			break;
		case PRE_SPARGE:
			if (hlt_therm->get_temp() >= SPARGE_TEMP) {
				std::cout << std::endl << "SPARGE" << std::endl << std::endl;
				state = SPARGE;
			} else {
				state = PRE_SPARGE;
			}
			break;
		case SPARGE:
			/* TODO: Pump/Vol logic */
			std::cout << std::endl << "END" << std::endl << std::endl;
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
			pinMode(3, OUTPUT);
			digitalWrite(3, LOW);
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
			if ((mash_therm->get_temp() < MASH_TEMP)
					&& (hlt_therm->get_temp() >= MASH_TEMP)) {// + 10)) {
				std::cout << "PUMP ON" << std::endl;
				digitalWrite(3, HIGH);
			} else {
				std::cout << "PUMP OFF" << std::endl;
				digitalWrite(3, LOW);
			}
			break;
		case PRE_SPARGE:
			//std::cout << "HEATER ON" << std::endl;
			digitalWrite(pin, HIGH);
			digitalWrite(3, LOW);
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
