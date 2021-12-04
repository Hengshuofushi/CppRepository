#pragma once

#include "HshaThreadPool.hpp"
#include <future>

class PromiseTask : public BaseTask
{
public:
    PromiseTask() = default;
    virtual ~PromiseTask() = default;

    virtual void Run() override;
    virtual bool Action() = 0;
    virtual bool Validate() override;

private:
    std::promise<bool> promise;
};


class PromiseThreadPool final : public HshaThreadPool
{
public:
	PromiseThreadPool() = default;
    virtual ~PromiseThreadPool() = default;

    bool AddTaskBatch(const std::vector<Task>& taskVec);
    bool Validate();
    void Clear() { m_queue.Clear(); }
private:
    std::vector<Task> taskPromise;
    std::atomic_bool processing { false };
};