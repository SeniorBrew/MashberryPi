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

#include <iostream>

int main(void) {
	extern int timer_flag;
	TaskList * T = new TaskList();

	std::cout << "Initializing wiringPi..." << std::endl;
	if(wiringPiSetup())
		return 1;

	std::cout << "Initializing ads1115..." << std::endl;
	if(!ads1115Setup(2222, 0x48))
		return 1;

	/* Add new tasks here */
	Thermometer hlt_therm(500, 0);
	Thermometer mash_therm(500, 2);
	Timer timer(1000);
	Volume hlt_vol(500, 3.14, 10.0, 1.0, 4, 5);
	Volume mash_vol(500, 3.14, 10.0, 1.0, 6, 7);
	Pump hlt_pump(100, hlt_vol, mash_vol, 2);
	Pump mash_pump(100, mash_vol, 3);
	Heater hlt_heat(100, 0);
	Control control(1000, timer, hlt_therm, mash_therm, hlt_vol, 
			mash_vol, hlt_heat);

	std::cout << "Compiling Task List..." << std::endl;

	T->add_task(&hlt_therm);
	T->add_task(&mash_therm);
	T->add_task(&timer);
	T->add_task(&hlt_vol);
	T->add_task(&mash_vol);
	T->add_task(&hlt_pump);
	T->add_task(&mash_pump);
	T->add_task(&hlt_heat);

	std::cout << "Initializing Timer Interrupts..." << std::endl;

	if(timer_init(T->get_period_ms()))
		return 1;

	std::cout << "Starting Tasks..." << std::endl;

	for(;;) {
		T->tick();
		while(!timer_flag)
			;
		timer_flag = 0;
	}

	return 1;
}
