#include "task.hpp"
#include "tasklist.hpp"
#include "ping.hpp"
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>

int timer_flag;
void tick_list(int);
int init(int);
void set_timer_s(long int);
void set_timer_ms(long int);
void set_timer_us(long int);

int main(void) {
	TaskList * T = new TaskList();

	/* Add new tasks here */
	/* T->add_task(new Task(period_ms)); */
	T->add_task(new Ping(1000));

	init(T->get_period_ms());

	for(;;) {
		T->tick();
		while(!timer_flag)
			;
		timer_flag = 0;
	}

	return 1;
}

void set_flag(int i) {
	timer_flag = 1;
}

int init(int ms) {
	timer_flag = 0;
	set_timer_ms(ms);
	signal(SIGALRM, set_flag);
}

void set_timer_ms(long int ms) {
	struct itimerval timer;

											// Interval for periodic timer
	timer.it_interval.tv_usec = (ms * 1000) % 1000;	// microseconds
	timer.it_interval.tv_sec = ms / 1000;		// seconds
											// Time until next expiration
	timer.it_value.tv_usec = (ms * 1000) % 1000;	// microseconds
	timer.it_value.tv_sec = ms / 1000;		// seconds

	setitimer(ITIMER_REAL, &timer, NULL);
}
