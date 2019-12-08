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

	void AddTask(std::function<void()> task, PeriodMilliSecond time); //void()��ʾoperator()�ķ�ʽ���˵���Ҫ����bind�����Ժ���Ϊ��λ;
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


