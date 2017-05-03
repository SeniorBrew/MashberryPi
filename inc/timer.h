/******************************************************************************
 * Author: Nicholas Pelham
 * Date  : 4/27/2017
 *
 *   This file contains the C functionality for using a hardware timer. It is 
 * required for real-time operation of tasks.
 *
 * There were problems compiling the program with timer_flag with the 
 * definitions and declarations seperated. So The definitions have been moved 
 * to this single header file. Because it is small, and only included in a 
 * single source file, this created negligible bloat.
 *****************************************************************************/

#ifndef TIMER_H
#define TIMER_H

#include <sys/time.h>
#include <signal.h>
#include <unistd.h>

int timer_flag;

void timer_set_flag(int i) {
	timer_flag = 1;
}

void timer_set_ms(long int ms) {
	struct itimerval timer;

	// Interval for periodic timer
	timer.it_interval.tv_usec = ((ms % 1000) * 1000);	// microseconds
	timer.it_interval.tv_sec = (ms / 1000);			// seconds

	// Time until next expiration
	timer.it_value.tv_usec = ((ms % 1000) * 1000);		// microseconds
	timer.it_value.tv_sec = (ms / 1000);			// seconds

	setitimer(ITIMER_REAL, &timer, NULL);
}

int timer_init(int ms) {
	timer_flag = 0;
	timer_set_ms(ms);
	signal(SIGALRM, timer_set_flag);

	return 0;
}
#endif
