#ifndef PING_HPP
#define PING_HPP

#include "task.hpp"

class Ping : public Task {
	public:
		Ping(int ms);
	private:
		enum States { INIT };
		int o_num;

		virtual int tick_function();
};

#endif
