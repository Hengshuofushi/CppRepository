#include "HshaThreadPool.hpp"
#include "promise_thread_pool.hpp"
#include <iostream>

using std::cout;
using std::endl;

class TestTask : public BaseTask
{
public:
	TestTask() = default;
	virtual ~TestTask() = default;
	virtual void Run() override
	{
		cout << std::this_thread::get_id() << endl;
		std::this_thread::sleep_for(std::chrono::seconds(3));
	}
};

class TestPromiseTask : public PromiseTask
{
public:
	TestPromiseTask() = default;
	virtual ~TestPromiseTask() = default;
	virtual bool Action() override
	{
		cout << "[" << std::this_thread::get_id() << "] xxxx 0" << endl;
		std::this_thread::sleep_for(std::chrono::seconds(3));
		cout << "[" << std::this_thread::get_id() << "] xxxx 1" << endl;
		return true;
	}
};
class TestPromiseTask2 : public PromiseTask
{
public:
	TestPromiseTask2() = default;
	virtual ~TestPromiseTask2() = default;
	virtual bool Action() override
	{
		cout << "[" << std::this_thread::get_id() << "] yyyyyy 0" << endl;
		std::this_thread::sleep_for(std::chrono::seconds(5));
		cout << "[" << std::this_thread::get_id() << "] yyyyyy 1" << endl;
		return true;
	}
};

int main1()
{
	HshaThreadPool pool;
	pool.Start();
	std::thread t1([&pool] {
		{
			for (int i = 0; i < 10; i++)
			{
				pool.AddTask(std::make_shared<TestTask>());
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
		}
		});
	std::thread t2([&pool] {
		for (int i = 0; i < 5; i++)
		{
			pool.AddTask(std::make_shared<TestTask>());
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		});
	getchar();
	pool.Stop();
	t1.join();
	t2.join();
	return 0;
}


int main()
{
	PromiseThreadPool pool;
	pool.Start();
	std::vector<Task> vec1, vec2;
	for (size_t i = 0; i < 10; i++)
	{
		Task task = std::make_shared<TestPromiseTask>();
		vec1.push_back(task);
		Task task2 = std::make_shared<TestPromiseTask2>();
		vec2.push_back(task2);
	}
	cout << std::this_thread::get_id() << endl;
	cout << "---------------" << endl;
	pool.AddTaskBatch(vec1);
	pool.Validate();
	pool.Clear();
	cout << "---------------" << endl;
	pool.AddTaskBatch(vec2);
	pool.Validate();
	getchar();
	return 0;
}


int main2()
{
	TestPromiseTask task;
	std::thread th(&TestPromiseTask::Run, &task);
	cout << task.Validate() << endl;
	cout << "---------------" << endl;
	th.join();
	return 0;
}