#include <cstdio>
#include <iostream>
#include <unistd.h>
#include "timerfd.h"
using namespace std;

void func()
{
	cout << "1111" << endl;
}
int main()
{
	Task task = std::bind(func);
	Timerfd timer;
	TimeSpec once_time = { 1,0 };
	TimeSpec period_time = { 1,0 };
	timer.start_timer(task, &once_time, &period_time);
	sleep(5);
	timer.stop_timer();
    return 0;
}