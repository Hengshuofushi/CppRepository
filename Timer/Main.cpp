#include "Timer.h"
#include <iostream>
using namespace std;

void func()
{
	cout << "func" << endl;
}

int main()
{
	Timer timer;
	timer.AddTask(func, std::chrono::milliseconds(10000));
	timer.Start();

	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	timer.Stop();

}