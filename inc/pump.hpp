/******************************************************************************
 * Author: Nicholas Pelham
 * Date  : 5/30/2017
 *****************************************************************************/

#ifndef PUMP_HPP
#define PUMP_HPP 

#include "task.hpp"
#include "volume.hpp"
#include <wiringPi.h>

class Pump : public Task {
	public:
		Pump(int, Volume &, Volume &, int);
		Pump(int, Volume &, int);

		int on(void);
		int off(void);
	private:
		enum States { START, INIT, ON, OFF } state;
		int pin;
		int power_flag;
		Volume * source;
		Volume * destination;

		virtual int tick_function();
};

#endif
