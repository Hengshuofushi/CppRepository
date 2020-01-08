#pragma once
#include "MsgServer.h"
#include <string>

class Module
{
public:
	Module(const std::string& name);
	virtual ~Module();
	std::string GetName();
	void SendMessage(const std::string& modTo, const std::string& msg);
	void RecvMessage(const std::string& msg);
	void RegMsgService(MsgServer* msgServer);
	void UnregMsgService();
private:
	std::string name;
	MsgServer* msgServer = nullptr;
};

