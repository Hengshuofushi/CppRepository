#pragma once
#include <string>
#include <map>
class Module;
class MsgServer
{
public:
	~MsgServer();
	static MsgServer* GetInstance();
	void RegsterClient(Module* mod);
	void UnregsterClient(Module* mod);
	void Notify(const std::string& mod, const std::string& msg);
private:
	MsgServer();
	static MsgServer* instance;
	std::map<std::string, Module*> modMap;
};