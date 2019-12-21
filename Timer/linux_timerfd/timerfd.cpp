#include "timerfd.h"
#include <sys/timerfd.h>
#include <unistd.h>
#include <fcntl.h>
using ITimerSpec= struct itimerspec;
Timerfd::Timerfd() {};
Timerfd::~Timerfd()
{
	stop_timer();
	timer_task.join();
}

int Timerfd::start_timer(Task task, TimeSpec* once_time, 
	TimeSpec* period_time, int times)
{
	if (task)
	{
		this->task = task;
	}
	if (once_time)
	{
		this->once_time = *once_time;
	}
	if (period_time)
	{
		this->period_time = *period_time;
	}
	this->times = times;
	std::thread t(&Timerfd::timer_thread, this);
	timer_task = std::move(t);
}
int Timerfd::timer_thread()
{
	int cnt = 0, ret = 0;
	uint64_t exp;

	fd = timerfd_create(CLOCK_MONOTONIC, TFD_CLOEXEC);  //TFD_CLOEXEC, TFD_NONBLOCK 
	if (fd < 0)
	{
		printf("timerfd_create failed, fd=%d\n", fd);
		return -1;
	}
	ITimerSpec val = { {0,0},{0,0} };
	val.it_interval = std::move(period_time);
	val.it_value = std::move(once_time);
	timerfd_settime(fd, 0, &val, NULL); //0, TFD_TIMER_ABSTIME

	while (1)
	{
		cnt++;
		task();
		ret = read(fd, &exp, sizeof(uint64_t));
		if (ret != sizeof(uint64_t) || ret < 0)
		{
			printf("read error, ret=%d\n", ret);
			if (fd)
			{
				close(fd);
			}
			break;
		}
		if (times && cnt >= times)
		{
			printf("task run max timers, return\n");
			break;
		}
		printf("task run times cnt=%d\n", cnt);
	}
	if (fd)
	{
		close(fd);
		fd = -1;
	}
	return ret;
}
void Timerfd::stop_timer()
{

	//ITimerSpec val = { {0,0}, {0,0} };  //暂停定时器，read一直阻塞。it_value=0则会阻塞，it_interval=0则只执行一次
	//timerfd_settime(fd, 0, &val, NULL);
	int flag = fcntl(fd, F_GETFL, 0);  //退出定时器
	flag |= TFD_NONBLOCK;
	int ret = fcntl(fd, F_SETFL, flag);
	
	printf("timerfd stop ret=%d\n",ret);
}
