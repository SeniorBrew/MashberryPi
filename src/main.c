#include "task.hpp"
#include "ping.hpp"

int main(void) {
	TaskList T = new TaskList();

	//T.add_task(new Task(   ));
	//...

    T.add_task(new Ping(500));

	T.init();

	for(;;)
		;

	return 1;
}
