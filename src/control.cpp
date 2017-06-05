/******************************************************************************
 * Author: Nicholas Pelham
 * Date  : 6/4/2017
 *****************************************************************************/

#include "testconstants.h"

#include "task.hpp"
#include "thermometer.hpp"
#include "volume.hpp"
#include "heater.hpp"
#include "control.hpp"
#include <wiringPi.h>
#include <iostream>

Control::Control(int ms, Timer &timer, Thermometer & hlt, Thermometer & mash, 
		Volume &hlt_volume, Volume &mash_volume) : Task(ms) {

	pin = p;
	time = &timer;
	hlt_therm = &hlt;
	mash_therm = &mash;
	hlt_vol = &hlt_volume;
	mash_vol = &mash_volume;
	state = START;
}

int Control::tick_function() {

	/* State transitions */
	switch(state) {
		case INIT:
			std::cout << std::endl << "PRE_MASH" << std::endl 
				<< std::endl;
			state = PRE_MASH;
			break;
		case PRE_MASH:
			if (hlt_therm->get_temp() >= MASH_TEMP) {
				std::cout << std::endl << "TRANSFER" 
					<< std::endl << std::endl;
				state = TRANSFER;
			} else {
				state = PRE_MASH;
			}
			break;
		case TRANSFER:
			if (hlt_vol->is_empty()) {
				time->start_timer();
				std::cout << std::endl << "MASH" << std::endl 
					<< std::endl;
				state = MASH;
			} else {
				state = TRANSFER;
			}
			break;
		case MASH:
			if (time->get_minutes() >= MASH_TIME) {
				std::cout << std::endl << "PRE_SPARGE" 
					<< std::endl << std::endl;
				state = PRE_SPARGE;
			} else {
				state = MASH;
			}
			break;
		case PRE_SPARGE:
			if (hlt_therm->get_temp() >= SPARGE_TEMP) {
				std::cout << std::endl << "SPARGE" 
					<< std::endl << std::endl;
				state = SPARGE;
			} else {
				state = PRE_SPARGE;
			}
			break;
		case SPARGE:
			if (hlt_vol->is_empty() && mash_vol->is_empty()) {
				std::cout << std::endl << "END" << std::endl 
					<< std::endl;
				state = END;
			} else {
				state = SPARGE;
			}
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
			std::cout << "Initializing Control Task..." 
				<< std::endl;

			break;
		case PRE_MASH:
			hlt_heat->on();
			break;
		case TRANSFER:
			hlt_heat->off();
			hlt_pump->on();
			break;
		case MASH:
			if (hlt_therm->get_temp() >= MASH_TEMP + 10) {
				hlt_heat->off();
			} else {
				hlt_heat->on();
			}
			if ((mash_therm->get_temp() < MASH_TEMP)
					&& (hlt_therm->get_temp() >= MASH_TEMP 
						+10)) {
				mash_pump->on();
			} else {
				mash_pump->off();
			}
			break;
		case PRE_SPARGE:
			mash_pump->off();
			hlt_heat->on();
			break;
		case SPARGE:
			hlt_heat->off();
			hlt_pump->on();
			mash_pump->on();
			break;
		case END:
			hlt_heat->off();
			hlt_pump->off();
			hlt_pump->off();
			break;
		default:
			break;
	}
	
	return 0;
}

int Control::print_status(void) {
	/* HLT            MASH
	 * Heat: On/Off   Time: xxx:xx m:s
	 * Vol: x Gal     Vol: x Gal
	 * Temp: xxx F    Temp: xxx F
	*/
	std::cout << "HLT            MASH" << std::endl
		<< "Heat: On/Off   Time: xxx:xx m:s" << std::endl
		<< "Vol: x Gal     Vol: x Gal" << std::endl
		<< "Temp: xxx F    Temp: xxx F" << std::endl;
}
