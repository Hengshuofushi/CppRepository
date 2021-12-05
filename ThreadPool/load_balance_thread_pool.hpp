/**
 * @file load_balance_thread_pool.hpp
 * @author your name (you@domain.com)
 * @brief 负载均衡线程池，每个线程自己维护一个队列，队列中的任务具有权重属性，分配任务时保证每个线程的当前全任务权重相对均衡
 * @version 0.1
 * @date 2021-12-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include "RequestQueue.h"
#include <thread>
#include <memory>
#include <queue>
#include <mutex>
#include <atomic>
#include <map>

enum class TaskType
{
    TASK_TYPE_A,
    TASK_TYPE_B,
    TASK_TYPE_C,
    TASK_TYPE_D,
};

class BaseWeightTask : public BaseTask
{
public:
    BaseWeightTask(TaskType type_) : type(type_) {}
    virtual ~BaseWeightTask()= default;
    TaskType GetTaskType() { return type; }
    void SetWeight(unsigned int val) { weight = val; }
    unsigned int GetWeight() { return weight; }
private:
    TaskType type;
    unsigned int weight { 0 };
};

class LoadBalancePolicy
{
public:
    LoadBalancePolicy() = default;
    virtual ~LoadBalancePolicy() = default;
    virtual unsigned int CalWeight(const Task& task);
private:
    std::map<TaskType, unsigned int> typeWeigthMap;
};
using LoadBalancePolicyPtr = std::shared_ptr<LoadBalancePolicy>;

class Woker
{
public:
    Woker();
    ~Woker();
    bool AddTask(const Task& task);
    void Run();
    unsigned int GetWeight() { return weight; }
private:
    void TakeTask(Task& task);

    std::atomic_bool isStop { false };
    std::thread thread;
    RequestQueue taskQueue { 16 };
    std::atomic_uint weight { 0 };
};
using WokerPtr = std::shared_ptr<Woker>;

class LoadBalanceThreadPool
{
public:
    LoadBalanceThreadPool() = default;
    ~LoadBalanceThreadPool() = default;

    bool Start(unsigned int poolSize);
    bool AddTask(const Task& task);
private:
    std::vector<WokerPtr> wokerVec;
    LoadBalancePolicyPtr policy;
};