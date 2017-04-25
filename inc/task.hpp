#ifndef TASK_HPP
#define TASK_HPP

#include <vector>

using namespace std;

class Task {
	public:
		Task(int);
		int tick(int);
		int get_period_s() {return period_ms / 1000;};
		int get_period_ms() {return period_ms;};
		int get_period_us() {return period_ms * 1000;};

	protected:
		int state;
		int period_ms;
		int elapsed_time;

	private:
		virtual int tick_function() = 0;
};

#endif
