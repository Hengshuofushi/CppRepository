#pragma once
#include "MsgServer.h"
#include <string>

class Module
{
public:
	Module();
	~Module();
	void SendMessage(Module* modTo, const std::string& msg);
	void RecvMessage(Module* modFrom, const std::string& msg);
	void RegMsgService(MsgServer* msgServer);
	void UnregMsgService();
private:
	MsgServer* msgServer = nullptr;
};

