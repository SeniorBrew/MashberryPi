#ifndef HEATER_HPP
#define HEATER_HPP

#include "task.hpp"
#include <wiringPi.h>

class Heater : public Task {
	public:
		Heater(int ms);
	private:
		enum States { INIT };
		int i;

		virtual int tick_function();
};

#endif
