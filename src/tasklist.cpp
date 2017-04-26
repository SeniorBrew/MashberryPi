#include "task.hpp"
#include "tasklist.hpp"
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <vector>

#include <iostream>

using namespace std;

Task::Task(int ms) {
	state = -1;
	period_ms = ms;
	elapsed_time = ms;
}

int Task::tick(int ms) {
	if (elapsed_time >= period_ms) {
		this->tick_function();
		elapsed_time = 0;
	}
	elapsed_time += ms;

	return 0;
}

vector<Task*> TaskList::add_task(Task * T) {
	tasks.push_back(T);
	set_period_ms(findGCD(T->get_period_ms()));

	return tasks;
}

int TaskList::findGCD(int b) {
	int c;
	int a = period_ms;
	if (!period_ms)
		return b;
	while(1) {
		c = a%b;
		if (c == 0) { return b; }
		a = b;
		b = c;
	}
	return 0;
}

void TaskList::tick(void) {
	for (vector<Task*>::iterator T = tasks.begin(); T != tasks.end(); ++T) {
		(*T)->tick(period_ms);
	}
}

