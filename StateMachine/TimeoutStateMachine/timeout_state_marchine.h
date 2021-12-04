//#ifndef TIMEOUT_STATE_MARCHINE_HPP_
//#define TIMEOUT_STATE_MARCHINE_HPP_

namespace tools
{

	/**
	 * 超时状态机，每个状态有超时参数
	 * 触发条件、当前状态、响应动作、下一个状态
	 * 触发条件和当前状态共同决定响应动作和下一个状态，而不只是触发条件和当前状态某一个
	 */
	#include <memory>
	#include <map>
	class TransferAction
	{
	public:
		TransferAction();
		virtual ~TransferAction();
		virtual int Action();
	protected:
	private:
	};
	using P_TransferAction_T = std::shared_ptr<TransferAction>;

	class StateLinker
	{
	public:
		StateLinker(int triggerEvent,
					int currentState, 
					P_TransferAction_T action,
					int nextState);
		~StateLinker();
		int triggerEvent;
		int currentState;
		P_TransferAction_T transferAction;
		int nextState;
	protected:
	private:
	};
	using P_StateLinker_T = std::shared_ptr<StateLinker>;

	class TimeoutStateMarchine
	{
	public:
		TimeoutStateMarchine();
		~TimeoutStateMarchine();
		void AddStateLinker(P_StateLinker_T statLinker);
		void Run(int triggerEvent);

	protected:
	private:
		static long long CalKey(int triggerEvent, int currentState);

		int currentState;
		bool isStop;
		std::map<long long, P_StateLinker_T> stateLinkerMap;		// <key,linker>, key = triggerEvent<<8 | currentState
	};
}


//#endif // !TIMEOUT_STATE_MARCHINE_HPP_

