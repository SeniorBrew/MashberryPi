/******************************************************************************
 * Author: Nicholas Pelham
 * Date  : 4/27/2017
 *****************************************************************************/

#ifndef PING_HPP
#define PING_HPP

#include "task.hpp"

class Ping : public Task {
	public:
		Ping(int ms);
	private:
		enum States { START, INIT, ON, OFF } state;
		int o_num;

		virtual int tick_function();
};

#endif
