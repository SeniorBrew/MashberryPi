#ifndef PUMP_HPP
#define PUMP_HPP 

#include "task.hpp"
#include <wiringPi.h>

class Pump : public Task {
	public:
		Pump(int ms);
	private:
		enum States { INIT, ON, OFF } state;

		virtual int tick_function();
};

#endif
