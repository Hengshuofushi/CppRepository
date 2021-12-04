#pragma once

#include <queue>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <iostream>
#include <atomic>

using std::cout;
using std::endl;

class BaseTask
{
public:
	BaseTask() = default;
	virtual ~BaseTask() = default;
	virtual void Run() = 0;
	virtual bool Validate() { return true; }
};
using Task = std::shared_ptr<BaseTask>;

class RequestQueue
{
public:
	RequestQueue(size_t size)
	{
		this->m_maxSize = size;
		this->m_isStop = false;
		this->isSync = false;
	};
	~RequestQueue() 
	{
		std::call_once(m_stopOnceFlag, [this] {Stop(); });
	};

	bool AddTask(const Task& task)
	{
		std::unique_lock<std::mutex> lck(m_mutex);
		if (isSync.load())
		{
			m_notFullCv.wait(lck, [this] {return m_isStop || !IsFull(); });
		}
		if (m_isStop)
		{
			cout << "AddTask stop" << endl;
			return false;
		}
		if (IsFull())
		{
			return false;
		}
		m_queue.push(task);
		m_notEmptyCv.notify_one();
		return true;
	};

	void TakeTask(Task& task)
	{
		std::unique_lock<std::mutex> lck(m_mutex);
		m_notEmptyCv.wait(lck, [this] {return m_isStop || !IsEmpty(); });
		if (m_isStop)
		{
			cout << "TakeTask stop" << endl;
			return;
		}
		task = m_queue.front();
		m_queue.pop();
		m_notFullCv.notify_one();
	};

	void Clear()
	{
		std::queue<Task> q;
		m_queue.swap(q);
	}

	size_t GetSize()
	{
		std::lock_guard<std::mutex> lck(m_mutex);
		return m_queue.size();
	};

	void Stop()
	{
		{
			std::lock_guard<std::mutex> lck(m_mutex);    //�ȴ����ͷź�����Ż��ȡ����������ֹͣ��־λ
			m_isStop = true;
		}
		m_notFullCv.notify_all();
		m_notEmptyCv.notify_all();
	};
private:
	int m_maxSize;
	std::atomic_bool m_isStop;

	std::condition_variable m_notEmptyCv;
	std::condition_variable m_notFullCv;
	std::mutex m_mutex;
	std::atomic_bool isSync;

	std::queue<Task> m_queue;

	bool IsEmpty() const
	{
		bool isEmpty = m_queue.size() == 0;
		if (isEmpty)
		{
			cout << "request queue is empty" << endl;
		}
		return isEmpty;
	};

	bool IsFull() const
	{
		bool isFull = m_queue.size() >= m_maxSize;
		if (isFull)
		{
			cout << "request queue is full" << endl;
		}
		return isFull;
	};
	std::once_flag m_stopOnceFlag;
};
