#include "zmq.h"
#include <thread>
#include <iostream>
#include <atomic>
/**
 * socket连接方式：tcp,ipc,inproc,pgm,epgm
 * C风格接口调用
 */
class ZmqClient
{
public:
	ZmqClient() 
	{
		isStop.store(false);
	};
	~ZmqClient()
	{
		zmq_close(socket);
		zmq_close(context);
		isStop.store(true);
		handlerThread.join();
	};
	
	void Start()
	{
		InitZmq();
		std::thread t(&ZmqClient::Run, this);
		handlerThread = std::move(t);
	};
	void SendRequest(const char* msg)
	{
		zmq_msg_t request;
		zmq_msg_init_size(&request, ZMQ_MSG_T_SIZE);
		memcpy(zmq_msg_data(&request), msg, ZMQ_MSG_T_SIZE);
		zmq_send(socket, &request, ZMQ_MSG_T_SIZE, 0);
		zmq_close(&request);
	};
private:
	void InitZmq()
	{
		context = zmq_init(1);
		socket = zmq_socket(context, ZMQ_REQ);
		//zmq_bind(socket, "tcp://localhost:5051");
		zmq_connect(socket, "tcp://localhost:5050");

	};
	void Run()
	{
		while (!isStop.load())
		{
			zmq_msg_t reply; //MAX_LEN=64
			zmq_msg_init(&reply);
			zmq_recv(socket, &reply, ZMQ_MSG_T_SIZE, 0);
			HandleMessage((const char*)&reply);
			zmq_close(&reply);
		}
	};
	void HandleMessage(const char* msg)
	{
		std::cout << msg << std::endl;
	};
	void* context = nullptr;
	void* socket = nullptr;
	std::thread handlerThread;
	std::atomic_bool isStop;
};
int main()
{
	ZmqClient client;
	client.Start();
	client.SendRequest("hello");
}

