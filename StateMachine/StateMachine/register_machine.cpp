#include "register_machine.h"

RegState Session::GetState()
{
	return state;
}
void Session::SetState(RegState state)
{
	this->state = state;
}

std::shared_ptr<RegisterMarchine> RegisterMarchine::instance;
void RegisterMarchine::RegisterStateLinker(StateLinker&& linker)
{
	stateMap.insert(std::make_pair(linker.event, std::forward<StateLinker>(linker)));
}

void RegisterMarchine::TransferState(Event event, Session& session)
{
	int a = (int)stateMap[event].current;
	int b = (int)session.GetState();
	if (stateMap.count(event) > 0 && (int)stateMap[event].current == (int)session.GetState())
	{
		auto func = stateMap[event].func;
		func(session);
		session.SetState(stateMap[event].next);
	}
}

