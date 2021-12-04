#pragma once

#include "RequestQueue.h"
#include <functional>
#include <vector>
#include <thread>
#include <memory>

const int MAX_TASK_NUMBER = 100;

class HshaThreadPool;
using P_HshaThreadPool_T = std::shared_ptr<HshaThreadPool>;

class HshaThreadPool
{
public:
	HshaThreadPool(int numThreads = std::thread::hardware_concurrency()) : m_queue(MAX_TASK_NUMBER), numThreads(numThreads), isStop(false) {}
	virtual ~HshaThreadPool();

	void Start();

	virtual void Run();

	virtual bool AddTask(const Task& task);

	void Stop();

protected:

	RequestQueue m_queue;
	std::vector<std::shared_ptr<std::thread>> m_threads;
	std::atomic_bool isStop;
	int numThreads;
	std::once_flag m_stopOnceFlag;
};


