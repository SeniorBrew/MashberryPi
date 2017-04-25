#include "task.hpp"
#include "ping.hpp"
#include <iostream>

Ping::Ping(int ms) : Task(ms) {
	o_num = 0;
}

int Ping::tick_function() {
	std::cout << o_num++ << std::endl;
	return 0;
}
