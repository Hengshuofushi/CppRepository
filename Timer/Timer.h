#pragma once
#include <chrono>
#include <functional>
#include <condition_variable>
#include <mutex>

using PeriodMilliSecond = std::chrono::milliseconds;

class Timer
{
public:
	
	Timer();
	~Timer();

	void AddTask(std::function<void()> task, PeriodMilliSecond time); //void()表示operator()的方式，此地需要传入bind对象，以毫秒为单位;
	void Start();
	void Stop();
private:
	std::thread timerThread;
	std::function<void()> task;
	PeriodMilliSecond periodMilliSecond;
	std::condition_variable cv_timer;
	std::mutex m_mutex;
	bool isStop;
};


