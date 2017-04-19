#include <std/vector>

class Task {
	public:
		virtual int Task() = 0;
		virtual int set_state(int) = 0;
		virtual int init() = 0;
		virtual int tick(int);

		int get_period_s() {return period_ms / 1000;};
		int get_period_ms() {return period_ms;};
		int get_period_us() {return period_ms * 1000;};

	protected:
		int state;
		int period_ms;
		int elapsed_time;
};

class TaskList {
	public:
		vector<Task> addTask(Task);
		int get_period_s(void) { return period_ms / 1000; };
		int get_period_ms(void) { return period_ms; };
		int get_period_us(void) { return period_ms * 1000; };

		int init();
		int tick();

	private:
		vector<Task> tasks;
		int period_ms;

		void set_period_s(int s) { period_ms = s * 1000; };
		void set_period_ms(int ms) { period_ms = ms; };
		void set_period_us(int us) { period_ms = us * 1000; };
		int findGCD(int);
};
