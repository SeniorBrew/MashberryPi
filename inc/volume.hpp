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
		double get_vol(void) {return volume;};
	private:
		enum States { START, INIT, POLL } state;
		int trigger;
		int echo;

		double volume;
		double diameter;
		double depth;
		double capacity;

		virtual int tick_function();

		double poll_distance();
		double circle_area(double);
		double cylinder_volume(double, double);
		double cm_to_gal(double);
};

#endif
