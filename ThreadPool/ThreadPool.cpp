#include "RequestQueue.h"
#include <functional>
#include <vector>
#include <thread>

const int MAX_TASK_NUMBER = 100;
using Task = std::function<void()>;

class ThreadPool
{
public:
	ThreadPool(int numThreads = std::thread::hardware_concurrency()) : 
		numThreads(numThreads),
		m_queue(MAX_TASK_NUMBER)
	{
		Start();
	};
	~ThreadPool() 
	{
		std::call_once(m_stopOnceFlag, [this] {Stop(); });
	};

	void Start() // 为线程池创建线程
	{
		for (int i=0; i < numThreads; i++)
		{
			m_threads.push_back(std::make_shared<std::thread>(
				&ThreadPool::Run,this));
		}
	};

	void Run()  // 从任务队列中取出任务加载到线程池中的线程执行
	{
		while (!isStop.load())
		{
			Task task;
			m_queue.TakeTask(task);
			if (task)
			{
				task();
			}
			
		}
	};

	void AddTask(Task&& task)
	{
		m_queue.AddTask(std::forward<Task>(task));
	};

	void Stop()  // 将线程池中的每个线程都停止
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
private:
	RequestQueue<Task> m_queue;
	std::vector<std::shared_ptr<std::thread>> m_threads;
	std::atomic_bool isStop;
	int numThreads;
	std::once_flag m_stopOnceFlag;
};


