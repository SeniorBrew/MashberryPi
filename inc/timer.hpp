/******************************************************************************
 * Author: Nicholas Pelham
 * Date  : 4/27/2017
 *****************************************************************************/

#ifndef TIMER_HPP
#define TIMER_HPP

#include "task.hpp"

class Timer : public Task {
	public:
		Timer(int);

		void start_timer(void) { hours = 0; minutes = 0; seconds = 0; }
		void stop_timer(void) { seconds = -1; }

		int get_hours(void) { return hours; }
		int get_minutes(void) { return minutes; }
		int get_seconds(void) { return seconds; }
	private:
		enum States { START, INIT, ON, OFF } state;
		int hours;
		int minutes;
		int seconds;

		virtual int tick_function();
};

#endif
