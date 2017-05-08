/******************************************************************************
 * Author: Nicholas Pelham
 * Date  : 4/27/2017
 *****************************************************************************/

#ifndef HEATER_HPP
#define HEATER_HPP

#include "task.hpp"
#include "timer.hpp"
#include "thermometer.hpp"
#include <wiringPi.h>

class Heater : public Task {
	public:
		Heater(int, Timer &, Thermometer &, Thermometer &, int);
	private:
		enum States { START, INIT, PRE_MASH, TRANSFER, MASH, 
			PRE_SPARGE, SPARGE, END } state;

		int pin;
		Timer * time;
		Thermometer * hlt_therm;
		Thermometer * mash_therm;

		virtual int tick_function();
};

#endif
