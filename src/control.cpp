/******************************************************************************
 * Author: Nicholas Pelham
 * Date  : 6/4/2017
 *****************************************************************************/

//#include "testconstants.h"

#include "task.hpp"
#include "thermometer.hpp"
#include "volume.hpp"
#include "pump.hpp"
#include "heater.hpp"
#include "control.hpp"
#include <wiringPi.h>
#include <iostream>

Control::Control(int ms, Timer &timer, Thermometer & hlt_thermometer, 
		Thermometer & mash_thermometer, Pump & hlt_pump_, 
		Pump & mash_pump_, Volume &hlt_volume, Volume &mash_volume, 
		Heater &hlt_heater, double mash_temp, double sparge_temp, 
		int mash_time) 
		: Task(ms) {

	time = &timer;
	hlt_therm = &hlt_thermometer;
	mash_therm = &mash_thermometer;
	hlt_vol = &hlt_volume;
	mash_vol = &mash_volume;
	hlt_pump = &hlt_pump_;
	mash_pump = &mash_pump_;
	hlt_heat = &hlt_heater;
	boil_pump = NULL;

	MASH_TEMP = mash_temp;
	MASH_TIME = mash_time;
	SPARGE_TEMP = sparge_temp;
	
	sparge_timer = 0;
	state_flag = 0;
	state = START;
}

Control::Control(int ms, Timer &timer, Thermometer & hlt_thermometer, 
		Thermometer & mash_thermometer, Pump & hlt_pump_, 
		Pump & mash_pump_, Pump & boil_pump_, Volume &hlt_volume, 
		Volume &mash_volume, Heater &hlt_heater, double mash_temp, 
		double sparge_temp, int mash_time) : Task(ms) {

	time = &timer;
	hlt_therm = &hlt_thermometer;
	mash_therm = &mash_thermometer;
	hlt_vol = &hlt_volume;
	mash_vol = &mash_volume;
	hlt_pump = &hlt_pump_;
	mash_pump = &mash_pump_;
	boil_pump = &boil_pump_;
	hlt_heat = &hlt_heater;

	MASH_TEMP = mash_temp;
	MASH_TIME = mash_time;
	SPARGE_TEMP = sparge_temp;
	
	sparge_timer = 0;
	state_flag = 0;
	state = START;
}

int Control::tick_function() {

	/* State transitions */
	switch(state) {
		case INIT:
			//time->start_timer(); // ONLY FOR TESTING
			//state = MASH; // TESTING
			state = PRE_MASH;
			break;
		case PRE_MASH:
			if (hlt_therm->get_temp() >= MASH_TEMP) {
				state_flag++;
				if (state_flag >= 3) {
					state_flag == 0;
					state = TRANSFER;
				}
			} else {
				state_flag == 0;
				state = PRE_MASH;
			}
			break;
		case TRANSFER:
			if (hlt_vol->is_empty() || mash_vol->is_full()) {
				state_flag++;
				if (state_flag >= 3) {
					state_flag == 0;
					time->start_timer();
					state = MASH;
				}
			} else {
				state_flag == 0;
				state = TRANSFER;
			}
			break;
		case MASH:
			if (time->get_minutes() >= MASH_TIME) {
				time->stop_timer();
				state = PRE_SPARGE;
			} else {
				state = MASH;
			}
			break;
		case PRE_SPARGE:
			if (hlt_therm->get_temp() >= SPARGE_TEMP) {
				state_flag++;
				if (state_flag >= 3) {
					state_flag == 0;
					state = SPARGE;
				}
			} else {
				state_flag == 0;
				state = PRE_SPARGE;
			}
			break;
		case SPARGE:
			if (hlt_vol->is_empty() && mash_vol->is_empty()) {
				state_flag++;
				if (state_flag >= 3) {
					state_flag == 0;
					state = END;
				}
			} else {
				state_flag == 0;
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
			std::cout << std::endl << "PRE_MASH" << std::endl 
				<< std::endl;
			hlt_heat->on();
			break;
		case TRANSFER:
			std::cout << std::endl << "TRANSFER" 
				<< std::endl << std::endl;
			hlt_heat->off();
			hlt_pump->on();
			break;
		case MASH:
			std::cout << std::endl << "MASH" 
				<< std::endl << std::endl;
			if (hlt_therm->get_temp() >= MASH_TEMP + 10) {
				hlt_heat->off();
			} else {
				hlt_heat->on();
			}
			if ((mash_therm->get_temp() < MASH_TEMP)
					&& (hlt_therm->get_temp() >= MASH_TEMP 
						+ 10)) {
				mash_pump->on();
			} else {
				mash_pump->off();
			}
			break;
		case PRE_SPARGE:
			std::cout << std::endl << "PRE_SPARGE" 
				<< std::endl << std::endl;
			mash_pump->off();
			hlt_heat->on();
			break;
		case SPARGE:
			std::cout << std::endl << "SPARGE" 
				<< std::endl << std::endl;
			hlt_heat->off();
			if (sparge_timer < 30) {
				sparge_timer++;
				mash_pump->on();
			} else if (boil_pump != NULL) {
				if (hlt_vol->is_empty()) {
					hlt_pump->off();
				} else {
					hlt_pump->on();
				}
				if (mash_vol->is_empty()) {
					boil_pump->off();
				} else {
					boil_pump->on();
				}
			}
			break;
		case END:
			std::cout << std::endl << "END" 
				<< std::endl << std::endl;
			hlt_heat->off();
			hlt_pump->off();
			mash_pump->off();
			boil_pump->off();
			//exit(0);
			break;
		default:
			break;
	}

	print_status();
	
	return 0;
}

int Control::print_status(void) {
	/* HLT            MASH
	 * Heat: On/Off   Time: xxx:xx m:s
	 * Vol: x Gal     Vol: x Gal
	 * Temp: xxx F    Temp: xxx F
	*/
	std::cout << "HLT            MASH" << std::endl
		<< "               Time: " << (MASH_TIME-1 - time->get_minutes()) 
		<< ":" << (59 - (time->get_seconds() % 60)) << " m:s" << std::endl
		<< "Vol: " << hlt_vol->get_vol() << " Gal     Vol: "
		<< mash_vol->get_vol() << " Gal" << std::endl
		<< "Temp: " << hlt_therm->get_temp() << " F    Temp: "
		<< mash_therm->get_temp() << " F" << std::endl;
}
