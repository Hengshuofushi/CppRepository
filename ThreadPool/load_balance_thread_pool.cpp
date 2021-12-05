#include "load_balance_thread_pool.hpp"
#include <algorithm>

unsigned int LoadBalancePolicy::CalWeight(const Task& task)
{
    if (task == nullptr) return 0;
    
    auto subtask = std::dynamic_pointer_cast<BaseWeightTask>(task);
    if (subtask == nullptr) return 0;

    auto it = typeWeigthMap.find(subtask->GetTaskType());
    if (it == typeWeigthMap.end()) return 0;
    
    return it->second;
}

Woker::Woker()
{
    thread = std::thread(&Woker::Run, this);
}

Woker::~Woker()
{
    if (thread.joinable())
    {
        thread.join();
    }
}

bool Woker::AddTask(const Task& task)
{
    if (task == nullptr) return false;


    auto subtask = std::dynamic_pointer_cast<BaseWeightTask>(task);
    if (subtask == nullptr) return false;

    taskQueue.AddTask(task);
    weight += subtask->GetWeight();

    return true;
}

void Woker::TakeTask(Task& task)
{
    auto subtask = std::dynamic_pointer_cast<BaseWeightTask>(task);
    if (subtask == nullptr) return;

    taskQueue.TakeTask(task);
    weight -= subtask->GetWeight();
}

void Woker::Run()
{
    while (!isStop.load())
    {
        Task task;
        taskQueue.TakeTask(task);
        if (task != nullptr)
        {
            task->Run();
        }
    }
}

bool LoadBalanceThreadPool::Start(unsigned int poolSize)
{
    for (size_t i = 0; i < poolSize; i++)
    {
        wokerVec.push_back(std::make_shared<Woker>());
    }
}
bool LoadBalanceThreadPool::AddTask(const Task& task)
{
    auto it = std::min_element(wokerVec.begin(), wokerVec.end(),
        [this] (const WokerPtr& worker1, const WokerPtr& worker2)
        {
            return worker1->GetWeight() > worker2->GetWeight();
        });
    if (it == wokerVec.end())
    {
        return false;
    }
    return (*it)->AddTask(task);
}