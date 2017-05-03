/******************************************************************************
 * Author: Nicholas Pelham
 * Date  : 4/26/2017
 *
 *   Ping is a simple task that prints an incrementing number to console. It 
 * is provided here to demonstrate how to create a new task.
 *  To see inherited functionality, check task.cpp.
 *****************************************************************************/

#include "task.hpp"
#include "ping.hpp"
#include <iostream>

Ping::Ping(int ms) : Task(ms) {
	state = INIT;
	o_num = 0;
}

int Ping::tick_function() {

	/* State transitions */
	switch(state) {
		case INIT:
			state = ON;
			break;
		case ON:
			state = ON;
			break;
		case OFF:
			state = INIT;
			break;
		default: 
			state = INIT;
			break;
	}

	/* State actions */
	switch(state) {
		case INIT:
			break;
		case ON:
			std::cout << " " << o_num++ << std::endl;
			break;
		case OFF:
			break;
		default:
			break;
	}
	return 0;
}
