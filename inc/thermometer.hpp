/******************************************************************************
 * Author: Nicholas Pelham
 * Date  : 4/27/2017
 *****************************************************************************/

#ifndef THERMOMETER_HPP
#define THERMOMETER_HPP

#include "task.hpp"

#define BASE 2222
#define ADDRESS 0x48

class Thermometer : public Task {
	public:
		Thermometer(int, int);

		double get_temp(void) { return temperature; }
	private:
		enum States { START, INIT, POLL_TEMP } state;

		int channel;
		double temperature;

		double poll_temp(void);
		double v_to_c(double);
		double c_to_f(double);
		virtual int tick_function();
};

#endif
