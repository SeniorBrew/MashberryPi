#include <task.hpp>
#include <std/vector>

TaskList::TaskList() {
}

TaskList::~TaskList() {
}

vector<Task> TaskList::addTask(Task T) {
	tasks.add(T);
	set_period_ms(findGCD(T.get_period()));
}

int TaskList::init(void) {
	set_timer_ms(period_ms);
	signal(SIGALRM, tick);
}

int TaskList::tick(void) {
	for (iterator<Task> T = tasks.begin(); T != tasks.end(); ++T) {
		T.tick(period_ms);
	}
}

int Task::tick(int ms) {
	if (elapsed_time >= period_ms) {
		tick_function();
		elapsed_time = 0;
	}
	elapsed_time += ms;
}

int TaskList::findGCD(int) {
	int c;
	while(1) {
		c = a%b;
		if (c == 0) { return b; }
		a = b;
		b = c;
	}
	return 0;
}

void set_timer_seconds(long int s) {
	struct itimerval timer;

											// Interval for periodic timer
	timer.it_interval.tv_usec = 0;			// microseconds
	timer.it_interval.tv_sec = s;			// seconds
											// Time until next expiration
	timer.it_value.tv_usec = 0;				// microseconds
	timer.it_value.tv_sec = s;				// seconds

	setitimer(ITIMER_REAL, &timer, NULL);
}

void set_timer_milliseconds(int ms) {
	struct itimerval timer;

											// Interval for periodic timer
	timer.it_interval.tv_usec = ms * 1000;	// microseconds
	timer.it_interval.tv_sec = 0;			// seconds
											// Time until next expiration
	timer.it_value.tv_usec = ms * 1000;		// microseconds
	timer.it_value.tv_sec = 0;				// seconds

	setitimer(ITIMER_REAL, &timer, NULL);
}

void set_timer_microseconds(int us) {
	struct itimerval timer;

											// Interval for periodic timer
	timer.it_interval.tv_usec = us;			// microseconds
	timer.it_interval.tv_sec = 0;			// seconds
											// Time until next expiration
	timer.it_value.tv_usec = us;			// microseconds
	timer.it_value.tv_sec = 0;				// seconds

	setitimer(ITIMER_REAL, &timer, NULL);
}
