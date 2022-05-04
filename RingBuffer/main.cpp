#include "ring_buffer.hpp"

int main()
{
    RingBuffer<std::string> queue(4);

    queue.Push(std::make_shared<std::string>("AAA"));
    queue.Push(std::make_shared<std::string>("BBB"));
    queue.Push(std::make_shared<std::string>("CCC"));
    queue.Push(std::make_shared<std::string>("DDD"));
    queue.Print();

    queue.Pop();
    queue.Print();
    queue.Pop();
    queue.Print();
    queue.Pop();
    queue.Print();
    queue.Pop();
    
    queue.Print();

    return 0;
}