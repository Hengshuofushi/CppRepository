#pragma once
/**
 * 注册状态转换: 触发事件 -> 状态1 -> 处理事件 -> 状态2
 * UNREGISTER_AUTH -> REGISTER_UNAUTH -> REGISTER_AUTH -> UNREGISTER_UNAUTH -> UNREGISTER_AUTH
 * UNREGISTER_UNAUTH -> UNREGISTER_UNAUTH 已登陆再登出
 * REGISTER_AUTH -> REGISTER_UNAUTH -> REGISTER_AUTH  已登陆再登陆
 */

#include <mutex>
#include <string>
#include <functional>
#include <map>

enum class RegState
{
	UNREGISTER_UNAUTH,
	UNREGISTER_AUTH,
	REGISTER_UNAUTH,
	REGISTER_AUTH
};
enum class Event
{
	REGISTER_REQUEST,
	REGISTER_AUTH,
	UNREGISTER_REQUEST,
	UNREGISTER_AUTH
};
class Session
{
public:
	Session() { state = RegState::UNREGISTER_AUTH; };
	~Session() {};
	RegState GetState();
	void SetState(RegState state);

private:
	RegState state;
};

using StateLinker = struct StateLinker
{
	// trigger event
	Event event;
	// state start
	RegState current;
	// handler
	std::function<void(Session&)> func;
	// state end
	RegState next;
};
class RegisterMarchine
{
public:
	~RegisterMarchine() = default;
	void RegisterStateLinker(StateLinker&& linker);
	void TransferState(Event evnet, Session& session);
	static std::shared_ptr<RegisterMarchine> GetInstance()
	{
		static std::once_flag flag;
		std::call_once(flag, [] {instance.reset(new RegisterMarchine()); });
		return instance;
	};
private:
	RegisterMarchine() = default;
	static std::shared_ptr<RegisterMarchine> instance;
	
	
	std::map<Event, StateLinker> stateMap;
};
