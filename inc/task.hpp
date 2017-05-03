/******************************************************************************
 * Author: Nicholas Pelham
 * Date  : 4/27/2017
 *****************************************************************************/

#ifndef TASK_HPP
#define TASK_HPP

#include <vector>

using namespace std;

class Task {
	public:
		Task(int);
		int tick(int);
		int get_period_ms() {return period_ms;};

	protected:
		enum States { INIT } state;
		int period_ms;
		int elapsed_time;

	private:
		virtual int tick_function() = 0;
};

class TaskList {
	public:
		vector<Task*> add_task(Task *);
		int get_period_ms(void) { return period_ms; };
		int init();
		void tick();

	private:
		vector<Task*> tasks;
		int period_ms;

		void set_period_ms(int ms) { period_ms = ms; };
		int findGCD(int);
};

#endif
