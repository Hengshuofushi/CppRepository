#pragma once
#include <string>

class Module;
class MsgServer
{
public:
	~MsgServer();
	static MsgServer* GetInstance();
	void Notify(Module* mod, const std::string& msg);
private:
	MsgServer();
	static MsgServer* instance;
};