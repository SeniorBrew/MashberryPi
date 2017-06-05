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
		Heater(int, int);

		int on(void);
		int off(void);
	private:
		enum States { START, INIT, ON, OFF } state;

		int pin;
		int power_flag;

		virtual int tick_function();
};

#endif
