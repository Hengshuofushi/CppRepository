/**
 * @file ring_buffer.hpp
 * @author your name (you@domain.com)
 * @brief 通用循环队列
 * @version 0.1
 * @date 2022-05-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <memory>
#include <iostream>
#include <vector>

template<class T>
class RingBuffer
{
public:
    explicit RingBuffer(size_t capacity) : queue(capacity) {}
    ~RingBuffer() { queue.clear(); }

    bool Push(std::shared_ptr<T> obj)
    {
        if (IsFull()) return false;

        queue[rear] = obj;

        rear = (rear + 1) % Capacity();

        ++count;
    }
    std::shared_ptr<T> Pop()
    {
        if (IsEmpty()) return nullptr;

        std::shared_ptr<T> tmp = queue.at(front);
        queue[front] = nullptr;

        front = (front + 1) % Capacity();

        --count;
        return tmp;
    }
    size_t Count() const { return count; }
    size_t Capacity() const { return queue.capacity(); }
    size_t IsEmpty() const { return rear == front; }
    size_t IsFull() const { return (rear + 1) % Capacity() == front; }

    void Print()        // for test only
    {
        std::cout << "=====================" << std::endl;
        for (size_t i = 0; i < Capacity(); i++)
        {
            if (queue[i] != nullptr)
            {
                std::cout << *queue[i] << ", cur rear = " << rear << ", cur front = " << front << std::endl;
            }
        }
    }

private:
    std::vector<std::shared_ptr<T>> queue;
    size_t rear  { 0 };         // queue tail indicator (no obj)
    size_t front { 0 };         // queue head indicator (had obj)
    size_t count { 0 };
};