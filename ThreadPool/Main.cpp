#include "ThreadPool.cpp"
using std::cout;
using std::endl;
int main()
{
	ThreadPool pool;
	std::thread t1([&pool] {    //创建任务的线程1
		{
			for (int i = 0; i < 5; i++)
			{
				auto id = std::this_thread::get_id();
				pool.AddTask([id]
					{
						cout << "[" << id << "]:" << std::this_thread::get_id() << endl;
					});
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
		}
		});
	std::thread t2([&pool] {    //创建任务的线程2
		{
			for (int i = 0; i < 5; i++)
			{
				auto id = std::this_thread::get_id();
				pool.AddTask([id]
					{
						cout << "[" << id << "]:" << std::this_thread::get_id() << endl;
					});
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
		}
		});
	getchar();
	pool.Stop();
	t1.join();
	t2.join();
}