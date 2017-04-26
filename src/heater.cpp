#include "task.hpp"
#include "heater.hpp"
#include <wiringPi.h>
#include <iostream>

Heater::Heater(int ms) : Task(ms) {
	pinMode(0, OUTPUT);
	digitalWrite(0, LOW);
	i = 0;
}

int Heater::tick_function() {
	i++;
	switch(i%2) {
		case 1: digitalWrite(0, HIGH);
			break;
		case 0: digitalWrite(0, LOW);
			break;
		default:
			break;
	}
	return 0;
}
