#include "task.hpp"
//#include "tasklist.hpp"
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <vector>

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
}

vector<Task> TaskList::addTask(Task & T) {
	tasks.push_back(T);
	set_period_ms(findGCD(T.get_period_ms()));
}

int TaskList::findGCD(int b) {
	int c;
    int a = period_ms;
	while(1) {
		c = a%b;
		if (c == 0) { return b; }
		a = b;
		b = c;
	}
	return 0;
}

int TaskList::init(void) {
	set_timer_ms(period_ms);
	signal(SIGALRM, Task::list.tick);
}

void TaskList::tick(int i) {
	for (vector<Task>::iterator T = tasks.begin(); T != tasks.end(); ++T) {
		T->tick(period_ms);
	}
}

void TaskList::set_timer_s(long int s) {
	struct itimerval timer;

											// Interval for periodic timer
	timer.it_interval.tv_usec = 0;			// microseconds
	timer.it_interval.tv_sec = s;			// seconds
											// Time until next expiration
	timer.it_value.tv_usec = 0;				// microseconds
	timer.it_value.tv_sec = s;				// seconds

	setitimer(ITIMER_REAL, &timer, NULL);
}

void TaskList::set_timer_ms(long int ms) {
	struct itimerval timer;

											// Interval for periodic timer
	timer.it_interval.tv_usec = ms * 1000;	// microseconds
	timer.it_interval.tv_sec = 0;			// seconds
											// Time until next expiration
	timer.it_value.tv_usec = ms * 1000;		// microseconds
	timer.it_value.tv_sec = 0;				// seconds

	setitimer(ITIMER_REAL, &timer, NULL);
}

void TaskList::set_timer_us(long int us) {
	struct itimerval timer;

											// Interval for periodic timer
	timer.it_interval.tv_usec = us;			// microseconds
	timer.it_interval.tv_sec = 0;			// seconds
											// Time until next expiration
	timer.it_value.tv_usec = us;			// microseconds
	timer.it_value.tv_sec = 0;				// seconds

	setitimer(ITIMER_REAL, &timer, NULL);
}
