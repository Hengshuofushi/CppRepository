#include "timeout_state_marchine.h"
using namespace tools;

TransferAction::TransferAction() {}
TransferAction::~TransferAction() {}
int TransferAction::Action()
{
	return 0;
}


StateLinker::StateLinker(int triggerEvent_, int currentState_, P_TransferAction_T transferAction_, int nextState_)
	: triggerEvent(triggerEvent_), currentState(currentState_), nextState(nextState_)
{
	transferAction.swap(transferAction_);
}
StateLinker::~StateLinker() {}

TimeoutStateMarchine::TimeoutStateMarchine() : currentState(-1)
{
	stateLinkerMap.clear();
}
TimeoutStateMarchine::~TimeoutStateMarchine()
{
	stateLinkerMap.clear();
}

void TimeoutStateMarchine::AddStateLinker(P_StateLinker_T statLinker)
{
	if (statLinker == nullptr)
	{
		return;
	}
	if (statLinker->transferAction == nullptr)
	{
		return;
	}
	if (stateLinkerMap.count(statLinker->triggerEvent) == 0)
	{
		auto key = TimeoutStateMarchine::CalKey(statLinker->triggerEvent, statLinker->triggerEvent);
		stateLinkerMap.insert(std::make_pair(key, statLinker));
	}
}
void TimeoutStateMarchine::Run(int triggerEvent)
{
	long long key = TimeoutStateMarchine::CalKey(triggerEvent, currentState);
	if (stateLinkerMap.count(key) > 0)
	{
		stateLinkerMap[triggerEvent]->transferAction->Action();
	}
}

long long TimeoutStateMarchine::CalKey(int triggerEvent, int currentState)
{
	return triggerEvent << 8 | currentState;
}
