#include "ModuleA.h"
#include "ModuleB.h"
#include <iostream>

int main()
{
	MsgServer* server = MsgServer::GetInstance();
	Module* a = new ModuleA("a");
	Module* b = new ModuleB("b");
	a->RegMsgService(server);
	b->RegMsgService(server);
	a->SendMessage("b", "ssss");
}


