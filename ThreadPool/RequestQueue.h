#pragma once
/**
 * 请求队列，同步线程的请求都放入队列
 */
#include <queue>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <iostream>
#include <atomic>

using std::cout;
using std::endl;

template <typename T>
class RequestQueue
{
public:
	RequestQueue(size_t size)
	{
		this->m_maxSize = size;
		this->m_isStop = false;
	};
	~RequestQueue() 
	{
		//std::call_once(m_stopOnceFlag, [this] {Stop(); });
	};

	void AddTask(T&& task)//同步任务加入队列，如果队列满了就等待，会阻塞请求的线程
	{
		std::unique_lock<std::mutex> lck(m_mutex);
		m_notFullCv.wait(lck, [this] {return m_isStop || !IsFull(); });
		if (m_isStop)
		{
			cout << "AddTask stop" << endl;
			return;
		}
		m_queue.emplace(std::forward<T>(task));
		m_notEmptyCv.notify_one();
	};

	void TakeTask(T& task)
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

	size_t GetSize() const
	{
		std::lock_guard<std::mutex> lck(m_mutex);
		return m_queue.size();
	};

	void Stop()
	{
		{
			std::lock_guard<std::mutex> lck(m_mutex);    //等待锁释放后这里才会获取到锁，设置停止标志位
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

	std::queue<T> m_queue;

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
