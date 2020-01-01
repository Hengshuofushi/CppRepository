/**
 * 领导者跟随者线程池
 * 1. 领导者监听任务是否到达，如果到达则：
 *		a. 将自己设置为处理中
 *		b. 从其他跟随者中选出一名领导者
 *      c. 开始自己的任务处理
 *		d. 处理完成后将自己设置为跟随者
 * 2. 维护领导者、跟随者、处理中状态
 * 3. 同时最多只能一个领导者，并且只能由领导者来指定继承的领导者，不存在竞争
 */
#include "RequestQueue.h"
#include <functional>
#include <map>
#include <thread>
#include <condition_variable>
#include <mutex>

enum ThreadStatus
{
	Leader,
	Follower,
	Processing
};

const int MAX_TASK_NUMBER = 100;
using Task = std::function<void()>;
using ThreadPtr = std::shared_ptr<std::thread>;


class LfThreadPool
{
public:
	LfThreadPool(int numThreads = std::thread::hardware_concurrency()) :
		numThreads(numThreads),
		m_queue(MAX_TASK_NUMBER)
	{
		Start();
	};
	~LfThreadPool()
	{
		std::call_once(m_stopOnceFlag, [this] {Stop(); });
	};

	void Start() // 为线程池创建线程
	{
		for (int i = 0; i < numThreads-1; i++)
		{
			m_threads.insert(std::make_pair(
				std::make_shared<std::thread>(&LfThreadPool::Run, this),
				Follower));
		}
		m_threads.insert(std::make_pair(
			std::make_shared<std::thread>(&LfThreadPool::Run, this),
			Leader));
	};

	void Run()  // 从任务队列中取出任务加载到线程池中的线程执行
	{
		while (!isStop.load())
		{
			Task task;
			m_queue.TakeTask(task);
			if (task)
			{
				//1.如果是leader则将自己设置为processing，否则跳过
				cout << std::this_thread::get_id()<<" isLeader=" << queryThreadStatus(Leader) << endl;
				if (queryThreadStatus(Leader))
				{
					setThreadStatus(Processing);
					//2.从跟随者选出新的领导者，如果没有跟随者则阻塞
					while (!isStop.load())
					{
						if (!electNewLeader())
						{
							std::unique_lock<std::mutex> lck(m_follower);
							cv_follower.wait(lck, [this] {return isStop.load(); });
						}
						else
						{
							break;
						}
					}
					//3.处理任务
					task();
					//4.处理完成后设置自己状态为Follower
					setThreadStatus(Follower);
				}
				else if (queryThreadStatus(Follower))
				{
					cv_follower.notify_one();
				}
				else
				{

				}
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
		for (auto& t : m_threads)
		{
			if (t.first)
			{
				t.first->join();
			}
		}
		m_threads.clear();
	};
private:
	bool queryThreadStatus(ThreadStatus status)
	{
		for (auto& t : m_threads)
		{
			if (t.first->get_id() == std::this_thread::get_id() 
				&& t.second == status)
			{
				return true;
			}
		}
		return false;
	}
	void setThreadStatus(ThreadStatus status)
	{
		for (auto& t : m_threads)
		{
			if (t.first->get_id() == std::this_thread::get_id())
			{
				t.second = status;
			}
		}
	}
	bool electNewLeader()
	{
		for (auto& t : m_threads)
		{
			if (t.first->get_id() != std::this_thread::get_id() && t.second == Follower)
			{
				t.second = Leader;
				return true;
			}
		}
		return false;
	}

	RequestQueue<Task> m_queue;
	std::map<ThreadPtr, ThreadStatus> m_threads;
	std::atomic_bool isStop;
	int numThreads;
	std::once_flag m_stopOnceFlag;
	std::condition_variable cv_follower; //如果有跟随者则通知领导者可以选新的领导者了
	std::mutex m_follower;
};