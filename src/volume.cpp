/******************************************************************************
 * Author: Nicholas Pelham
 * Date  : 5/30/2017
 *****************************************************************************/

#include "task.hpp"
#include "volume.hpp"
#include <iostream>

Volume::Volume(int ms, double dia, double dep, double c, int t, int e) : Task(ms) {
	diameter = dia;
	depth = dep;
	capacity = c;
	trigger = t;
	echo = e;
	state = START;
	pinMode(trigger, OUTPUT);
	digitalWrite(trigger, LOW);
	pinMode(echo, INPUT);
}

int Volume::tick_function() {

	/* State transitions */
	switch(state) {
		case INIT:
			state = POLL;
			break;
		case POLL:
			state = POLL;
			break;
		default: 
			state = INIT;
			break;
	}

	/* State actions */
	switch(state) {
		case INIT:
			std::cout << "Initializing Volumeter on pins " 
				<< trigger << " and " << echo << "..." 
				<< std::endl;

			pinMode(trigger, OUTPUT);
			digitalWrite(trigger, LOW);
			pinMode(echo, INPUT);
			break;
		case POLL:
			volume = cylinder_volume(diameter, (depth - poll_distance()));
			std::cout << "Volume " << echo << ": " 
				<< cm_to_gal(volume) << std::endl;
			break;
		default:
			break;
	}
	return 0;
}

double Volume::poll_distance() {
	digitalWrite(trigger, LOW);
	delayMicroseconds(2);
	digitalWrite(trigger, HIGH);
	delayMicroseconds(15);
	digitalWrite(trigger, LOW);

	/* Expects an initial high value, which will be ignored */
	int timeout = 100000;
	int fail = 0;
	int start_timeout = micros();
	/*while (digitalRead(echo) == HIGH) {
		if ((micros() - start_timeout) < timeout) {
			fail = 1;
			break;
		}
	}*/

	while (digitalRead(echo) == LOW) {
		if ((micros() - start_timeout) > timeout) {
			fail = 1;
			break;
		}
	}

	int start_measured = micros();
	while (digitalRead(echo) == HIGH) {
		if ((micros() - start_timeout) > timeout) {
			fail = 1;
			break;
		}
	}
	int end_measured = micros();

	if (fail) {
		return depth;
	}
	double distance = (double)(end_measured - start_measured) * 0.0343 / 2.0;
	
	return distance;
}

int Volume::is_full() {
	if (cm_to_gal(volume) >= capacity) {
		return 1;
	} else {
		return 0;
	}
}

int Volume::is_empty() {
	if (cm_to_gal(volume) <= 0) {
		return 1;
	} else {
		return 0;
	}
}

double Volume::circle_area(double diameter) {
	return (3.14159 * diameter * diameter / 4.0);
}

double Volume::cylinder_volume(double diameter, double height) {
	return (circle_area(diameter) * height);
}

double Volume::cm_to_gal(double volume_in_cm) {
	return (volume_in_cm * 0.000264172);
}
