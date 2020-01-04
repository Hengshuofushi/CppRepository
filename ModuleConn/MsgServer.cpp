#include "MsgServer.h"
#include "Module.h"
MsgServer* MsgServer::instance = nullptr;
MsgServer::MsgServer()
{
}

MsgServer::~MsgServer()
{
}

MsgServer* MsgServer::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new MsgServer;
	}
	return instance;
}

void MsgServer::Notify(Module* mod, const std::string& msg)
{
	if (mod)
	{
		mod->RecvMessage(mod, msg);
	}
}
