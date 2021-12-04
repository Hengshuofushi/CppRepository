#include "zmq.h"
#include <thread>
#include <iostream>
/**
 * socket连接方式：tcp,ipc,inproc,pgm,epgm
 * C风格接口调用
 */
class ZmqServer
{
public:
	ZmqServer() {};
	~ZmqServer()
	{
		zmq_close(socket);
		zmq_close(context);
		handlerThread.join();
	};
	void InitZmq()
	{
		context = zmq_init(1);
		socket = zmq_socket(context, ZMQ_REP);
		zmq_bind(socket, "tcp://localhost:5050");
	};
	void Start()
	{
		std::thread t(&ZmqServer::Run,this);
		handlerThread = std::move(t);
	};
	
private:
	void Run()
	{
		while (1)
		{
			zmq_msg_t request; //MAX_LEN=64
			zmq_msg_init(&request);
			zmq_recv(socket, &request, ZMQ_MSG_T_SIZE, 0);
			HandleMessage((const char*)&request);
			zmq_close(&request);
		}
	};
	void SendReply(const char* msg)
	{
		zmq_msg_t reply;
		zmq_msg_init_size(&reply, ZMQ_MSG_T_SIZE);
		memcpy(zmq_msg_data(&reply), msg, ZMQ_MSG_T_SIZE);
		zmq_send(socket, &reply, ZMQ_MSG_T_SIZE, 0);
		zmq_close(&reply);
	};
	void HandleMessage(const char* msg)
	{
		std::cout << "recv msg: " << msg << std::endl;
		SendReply("world");
	};
	void* context = nullptr;
	void* socket = nullptr;
	std::thread handlerThread;
};
int main()
{
	ZmqServer server;
	server.Start();
}
