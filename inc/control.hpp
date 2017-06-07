/******************************************************************************
 * Author: Nicholas Pelham
 * Date  : 6/4/2017
 *****************************************************************************/

#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "task.hpp"
#include "timer.hpp"
#include "thermometer.hpp"
#include "pump.hpp"
#include "volume.hpp"
#include "heater.hpp"
#include <wiringPi.h>

class Control : public Task {
	public:
		Control(int, Timer &, Thermometer &, Thermometer &, 
			Pump &, Pump &, Volume &, Volume &, Heater &,
			double, double, int);
		Control(int, Timer &, Thermometer &, Thermometer &, 
			Pump &, Pump &, Pump &, Volume &, Volume &, 
			Heater &, double, double, int);
	private:
		enum States { START, INIT, PRE_MASH, TRANSFER, MASH, 
			PRE_SPARGE, SPARGE, END } state;
		int state_flag;
		int sparge_timer;

		Timer * time;
		Thermometer * hlt_therm;
		Thermometer * mash_therm;
		Pump * hlt_pump;
		Pump * mash_pump;
		Pump * boil_pump;
		Volume * hlt_vol;
		Volume * mash_vol;
		Heater * hlt_heat;

		double MASH_TEMP;
		double MASH_TIME;
		int SPARGE_TEMP;

		virtual int tick_function();
		int print_status(void);
};

#endif
