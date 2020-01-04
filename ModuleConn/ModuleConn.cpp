#include "MsgServer.h"
#include "Module.h"
#include <iostream>

int main()
{
	MsgServer* server = MsgServer::GetInstance();
	Module* a = new Module;
	Module* b = new Module;
	a->RegMsgService(server);
	b->RegMsgService(server);
	a->SendMessage(b, "ssss");
}


