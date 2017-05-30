/******************************************************************************
 * Author: Nicholas Pelham
 * Date  : 4/26/2017
 *
 *   Timer is a simple task that prints an incrementing number to console. It 
 * is provided here to demonstrate how to create a new task.
 *  To see inherited functionality, check task.cpp.
 *****************************************************************************/

#include "task.hpp"
#include "timer.hpp"
#include <iostream>

Timer::Timer(int ms) : Task(1000) {

	std::cout << "Initializing Timer..." << std::endl;

	state = START;
	hours = 0;
	minutes = 0;
	seconds = -1;
}

int Timer::tick_function() {

	/* State transitions */
	switch(state) {
		case INIT:
			state = OFF;
			break;
		case ON:
			if (seconds == -1) {
				state = OFF;
			} else {
				state = ON;
			}
			break;
		case OFF:
			if (seconds != -1) {
				state = ON;
			} else {
				state = OFF;
			}
			break;
		default: 
			state = INIT;
			break;
	}

	/* State actions */
	switch(state) {
		case INIT:
			hours = 0;
			minutes = 0;
			seconds = -1;
			break;
		case ON:
			//std::cout << seconds++ << std::endl;
			seconds++;
			if ((seconds % 60) == 0) {
				minutes++;
			}
			if ((minutes % 60) == 0) {
				hours++;
			}
			break;
		case OFF:
			break;
		default:
			break;
	}
	return 0;
}
