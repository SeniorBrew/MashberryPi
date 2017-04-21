#ifndef TASKLIST_HPP
#define TASKLIST_HPP

#include "task.hpp"
#include <vector>

using namespace std;

class TaskList {
	public:
		vector<Task> addTask(Task &);
		int get_period_s(void) { return period_ms / 1000; };
		int get_period_ms(void) { return period_ms; };
		int get_period_us(void) { return period_ms * 1000; };

		int init();
		void tick();

	private:
		vector<Task> tasks;
		int period_ms;

		void set_period_s(int s) { period_ms = s * 1000; };
		void set_period_ms(int ms) { period_ms = ms; };
		void set_period_us(int us) { period_ms = us * 1000; };
        void set_timer_s(long int);
        void set_timer_ms(long int);
        void set_timer_us(long int);
		int findGCD(int);
};

#endif
