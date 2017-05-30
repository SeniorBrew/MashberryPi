/******************************************************************************
 * Author: Nicholas Pelham
 * Date  : 5/30/2017
 *****************************************************************************/

#include "task.hpp"
#include "volume.hpp"
#include <iostream>

Volume::Volume(int ms, double a, double d, double c, int t, int e) : Task(ms) {
	area = a;
	depth = d;
	capacity = c;
	trigger = t;
	echo = e;
	state = START;
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
			pinMode(trigger, OUTPUT);
			digitalWrite(pin, LOW);
			pinMode(echo, INPUT);
			break;
		case POLL:
			volume = area * ( depth - poll_distance() );
			break;
		default:
			break;
	}
	return 0;
}

int poll_distance() {
	digitalwrite(pin,LOW);
	delaymicroseconds(2);
	digitalwrite(pin,HIGH);
	delaymicroseconds(15);
	digitalwrite(pin,LOW);

	/* Expects an initial high value, which will be ignored */
	while (digitalRead(echo) == HIGH)
		;

	while (digitalRead(echo) == LOW)
		;

	int start = micros();
	while (digitalRead(echo) == HIGH)
		;
	int end = micros();

	double distance = (end - start) * /*speedofsoundinusec*/ / 2;
}

int is_full() {
	if (volume >= capacity) {
		return 1;
	} else {
		return 0;
	}
}

int is_empty() {
	if (volume <= 0) {
		return 1;
	} else {
		return 0;
	}
}
