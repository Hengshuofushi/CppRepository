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

void MsgServer::RegsterClient(Module* mod)
{
	if (mod)
	{
		modMap[mod->GetName()] = mod;
	}
}

void MsgServer::UnregsterClient(Module* mod)
{
	if (mod)
	{
		if (modMap[mod->GetName()])
		{
			modMap.erase(mod->GetName());
		}
	}
}

void MsgServer::Notify(const std::string& mod, const std::string& msg)
{
	if (!mod.empty() && modMap[mod])
	{
		modMap[mod]->RecvMessage(msg);
	}
}
