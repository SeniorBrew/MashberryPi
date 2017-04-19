#include "task.hpp"

Class Ping : public Task {
	Public:
		Ping(int ms) : Task(ms);
		tick_function();
	Private:
		enum States { INIT };
		int o_num;
};

virtual int Ping::Ping(int ms) : Task(ms) {

	o_num = 0;
}

virtual int Ping::tick_function() {
	std::cout << o_num << std::endl;
}
