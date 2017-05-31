/******************************************************************************
 * Author: Nicholas Pelham
 * Date  : 5/30/2017
 *****************************************************************************/

#ifndef VOLUME_HPP
#define VOLUME_HPP 

#include "task.hpp"
#include <wiringPi.h>

class Volume : public Task {
	public:
		Volume(int, double, double, double, int, int);

		int is_full(void);
		int is_empty(void);
	private:
		enum States { START, INIT, POLL } state;
		int trigger;
		int echo;

		double volume;
		double area;
		double depth;
		double capacity;

		virtual int tick_function();

		double poll_distance();
};

#endif
