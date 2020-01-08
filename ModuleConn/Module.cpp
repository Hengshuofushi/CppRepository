#include "Module.h"
#include <iostream>
Module::Module(const std::string& name):name(name)
{

}

Module::~Module()
{
}

std::string Module::GetName()
{
	return name;
}

void Module::SendMessage(const std::string& modTo, const std::string& msg)
{
	if (msgServer && !modTo.empty())
	{
		msgServer->Notify(modTo, msg);
	}
}

void Module::RecvMessage(const std::string& msg)
{
	std::cout << msg << std::endl;
}

void Module::RegMsgService(MsgServer* msgServer)
{
	this->msgServer = msgServer;
	if (msgServer)
	{
		msgServer->RegsterClient(this);
	}
}

void Module::UnregMsgService()
{
	if (msgServer)
	{
		msgServer->UnregsterClient(this);
	}
	msgServer = nullptr;
}
