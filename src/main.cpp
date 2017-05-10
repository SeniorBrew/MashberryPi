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
#include "ping.hpp"
#include "heater.hpp"
#include "pump.hpp"
#include "timer.hpp"
#include "timer.h"
#include "thermometer.hpp"
#include <wiringPi.h>
#include <ads1115.h>

int main(void) {
	extern int timer_flag;
	TaskList * T = new TaskList();

	if(wiringPiSetup())
		return 1;
	if(!ads1115Setup(2222, 0x48))
		return 1;

	/* Add new tasks here */
	Thermometer hlt_therm(500, 0);
	Thermometer mash_therm(500, 2);
	Timer timer(1000);
	Heater hlt_heat(1000, timer, hlt_therm, mash_therm, 0);

	T->add_task(&hlt_therm);
	T->add_task(&mash_therm);
	T->add_task(&timer);
	T->add_task(&hlt_heat);

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
