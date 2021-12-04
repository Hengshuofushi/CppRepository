#include "promise_thread_pool.hpp"

void PromiseTask::Run()
{
    if (Action())
    {
        promise.set_value(true);
    }
    else
    {
        promise.set_value(false);
    }
}

bool PromiseTask::Validate()
{
    bool ret = promise.get_future().get();
    return ret;
}

bool PromiseThreadPool::AddTaskBatch(const std::vector<Task>& taskVec)
{
    if (processing.load())
    {
        return false;
    }
    taskPromise.clear();
    for (auto task : taskVec)
    {
        if (task == nullptr)
        {
            return false;
        }
        if (!AddTask(task))
        {
            return false;
        }
        taskPromise.push_back(task);
    }
    return true;
}
bool PromiseThreadPool::Validate()
{
    for (auto task : taskPromise)
    {
        if (task == nullptr)
        {
            return false;
        }
        if (!task->Validate())
        {
            return false;
        }
    }
    return true;
}
