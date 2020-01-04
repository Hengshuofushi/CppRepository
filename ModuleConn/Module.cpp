#include "Module.h"
#include <iostream>
Module::Module()
{

}

Module::~Module()
{
}

void Module::SendMessage(Module* modTo, const std::string& msg)
{
	if (msgServer && modTo)
	{
		msgServer->Notify(modTo, msg);
	}
}

void Module::RecvMessage(Module* modFrom, const std::string& msg)
{
	std::cout << msg << std::endl;
}

void Module::RegMsgService(MsgServer* msgServer)
{
	this->msgServer = msgServer;
}

void Module::UnregMsgService()
{
	msgServer = nullptr;
}
