#include "RequestQueue.h"
#include "HshaThreadPool.hpp"
#include <functional>
#include <vector>
#include <thread>

HshaThreadPool::~HshaThreadPool() 
{
	std::call_once(m_stopOnceFlag, [this] { Stop(); });
};

void HshaThreadPool::Start()
{
	for (int i=0; i < numThreads; i++)
	{
		m_threads.push_back(std::make_shared<std::thread>(
			&HshaThreadPool::Run,this));
	}
}

void HshaThreadPool::Run()
{
	while (!isStop.load())
	{
		Task task;
		m_queue.TakeTask(task);
		if (task)
		{
			task->Run();
		}
	}
};

bool HshaThreadPool::AddTask(const Task& task)
{
	return m_queue.AddTask(task);
};

void HshaThreadPool::Stop()
{
	m_queue.Stop();
	isStop = true;
	for (auto& thread : m_threads)
	{
		if (thread)
		{
			thread->join();
		}
	}
	m_threads.clear();
};


