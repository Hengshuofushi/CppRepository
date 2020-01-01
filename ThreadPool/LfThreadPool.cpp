/**
 * �쵼�߸������̳߳�
 * 1. �쵼�߼��������Ƿ񵽴���������
 *		a. ���Լ�����Ϊ������
 *		b. ��������������ѡ��һ���쵼��
 *      c. ��ʼ�Լ���������
 *		d. ������ɺ��Լ�����Ϊ������
 * 2. ά���쵼�ߡ������ߡ�������״̬
 * 3. ͬʱ���ֻ��һ���쵼�ߣ�����ֻ�����쵼����ָ���̳е��쵼�ߣ������ھ���
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

	void Start() // Ϊ�̳߳ش����߳�
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

	void Run()  // �����������ȡ��������ص��̳߳��е��߳�ִ��
	{
		while (!isStop.load())
		{
			Task task;
			m_queue.TakeTask(task);
			if (task)
			{
				//1.�����leader���Լ�����Ϊprocessing����������
				cout << std::this_thread::get_id()<<" isLeader=" << queryThreadStatus(Leader) << endl;
				if (queryThreadStatus(Leader))
				{
					setThreadStatus(Processing);
					//2.�Ӹ�����ѡ���µ��쵼�ߣ����û�и�����������
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
					//3.��������
					task();
					//4.������ɺ������Լ�״̬ΪFollower
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

	void Stop()  // ���̳߳��е�ÿ���̶߳�ֹͣ
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
	std::condition_variable cv_follower; //����и�������֪ͨ�쵼�߿���ѡ�µ��쵼����
	std::mutex m_follower;
};