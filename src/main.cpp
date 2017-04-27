/******************************************************************************
 * Author: Nicholas Pelham
 * Date  : 4/26/2017
 *
 *   This main file is meant to be as minimal as possible. All state machine 
 * definitions can be found in their appropriate header and source files. 
 * Initialization of a state machine is handled within the constructor of 
 * each class.
 *****************************************************************************/

#include "task.hpp"
#include "tasklist.hpp"
#include "ping.hpp"
#include "heater.hpp"
#include "pump.hpp"
#include "timer.h"

int main(void) {
	extern int timer_flag;
	TaskList * T = new TaskList();

	if(wiringPiSetup())
		return 1;

	/* Add new tasks here */
	/* T->add_task(new Task(period_ms)); */
	T->add_task(new Ping(1000));
	T->add_task(new Heater(500));
	//T->add_task(new Pump(3000));

	if(timer_init(T->get_period_ms()))
		return 1;

	for(;;) {
		T->tick();
		while(!timer_flag)
			;
		timer_flag = 0;
	}

	return 1;
}
