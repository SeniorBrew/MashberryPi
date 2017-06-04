/******************************************************************************
 * Author: Nicholas Pelham
 * Date  : 6/4/2017
 *****************************************************************************/

#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "task.hpp"
#include "timer.hpp"
#include "thermometer.hpp"
#include "volume.hpp"
#include "heater.hpp"
#include <wiringPi.h>

class Control : public Task {
	public:
		Control(int, Timer &, Thermometer &, Thermometer &, 
			Volume &, Volume &, Heater &);
	private:
		enum States { START, INIT, PRE_MASH, TRANSFER, MASH, 
			PRE_SPARGE, SPARGE, END } state;

		Timer * time;
		Thermometer * hlt_therm;
		Thermometer * mash_therm;
		Volume * hlt_vol;
		Volume * mash_vol;
		Heater * hlt_heat;

		virtual int tick_function();
};

#endif
