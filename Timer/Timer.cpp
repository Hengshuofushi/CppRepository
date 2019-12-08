#include "Timer.h"
#include <iostream>
Timer::Timer() : isStop(true), periodMilliSecond(1000) {};

Timer::~Timer() 
{
	Stop();
	if (timerThread.joinable())
	{
		timerThread.join();
	}
};

void Timer::AddTask(std::function<void()> task, PeriodMilliSecond time)
{
	this->task = task;
	periodMilliSecond = time;
	isStop = false;
}

void Timer::Start()
{
	std::thread t([this] 
		{
			while (!isStop)
			{
				if (task)
				{
					task();
				}
				std::unique_lock<std::mutex> lck(m_mutex);
				cv_timer.wait_for(lck, std::chrono::milliseconds(periodMilliSecond));
			}
		});
	timerThread = std::move(t);
	
};

void Timer::Stop()
{
	isStop = true;
	cv_timer.notify_all();
};


