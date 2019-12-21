#pragma once
#include <thread>
#include <time.h>
#include <functional>
using Task = std::function<void(void)>;
using TimeSpec = struct timespec;
class Timerfd
{
public:
	virtual int start_timer(Task task, TimeSpec* once_time, TimeSpec* period_time, int times = 0);
	virtual void stop_timer();
	Timerfd();
	~Timerfd();
private:
	int timer_thread();

	int fd;
	std::thread timer_task;
	Task task;
	TimeSpec once_time = {0,0};
	TimeSpec period_time = {0,0};
	int times = 0;
};
