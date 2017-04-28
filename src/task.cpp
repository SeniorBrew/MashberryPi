/******************************************************************************
 * Author: Nicholas Pelham
 * Date  : 4/26/2017
 *
 *   This file contains both Task and TaskList definitions.
 *
 * Task: 
 *   Handles the common functionality required by all tasks.
 *
 * TaskList:
 *   Wrapper for all Tasks. Runs through all Tasks on a global timer that it
 *   maintains.
 *****************************************************************************/

#include "task.hpp"
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <vector>

#include <iostream>

using namespace std;

/* 
 * Initialize variables that are neccessary for all tasks
 */
Task::Task(int ms) {
	state = INIT;
	period_ms = ms;
	elapsed_time = ms;
}

/* 
 * Handle calling tick_function when appropriate time has passed
 *
 * TODO: Thread tick_function for non-blocking operation
 */
int Task::tick(int ms) {
	if (elapsed_time >= period_ms) {
		this->tick_function();
		elapsed_time = 0;
	}
	elapsed_time += ms;

	return 0;
}

/*
 * One of the few function calls made in the main program
 */
vector<Task*> TaskList::add_task(Task * T) {
	tasks.push_back(T);
	set_period_ms(findGCD(T->get_period_ms()));

	return tasks;
}

/* 
 * Used to find the global tick period
 */
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

/*
 * Calls each individuals tasks tick at each global period.
 * Individual periods are handled by the respective task.
 */
void TaskList::tick(void) {
	for (vector<Task*>::iterator T = tasks.begin(); T != tasks.end(); ++T) {
		(*T)->tick(period_ms);
	}
}

