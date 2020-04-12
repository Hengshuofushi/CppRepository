/**
 * ×´Ì¬»úÑ§Ï°
 * ´¥·¢ÊÂ¼þ -> ×´Ì¬1 -> ×´Ì¬×ª»» -> ×´Ì¬2 -> ×´Ì¬ÊÂ¼þ
 */
#include "register_machine.h"
#include <iostream>

int main()
{
	StateLinker linker1 = {
		Event::REGISTER_REQUEST,
		RegState::UNREGISTER_AUTH,
		[](Session& session) {std::cout << (int)session.GetState() << std::endl; },
		RegState::REGISTER_UNAUTH
	};
	RegisterMarchine::GetInstance()->RegisterStateLinker(std::move(linker1));
	StateLinker linker2 = {
		Event::REGISTER_AUTH,
		RegState::REGISTER_UNAUTH,
		[](Session& session) {std::cout << (int)session.GetState() << std::endl; },
		RegState::REGISTER_AUTH
	};
	RegisterMarchine::GetInstance()->RegisterStateLinker(std::move(linker2));
	StateLinker linker3 = {
		Event::UNREGISTER_REQUEST,
		RegState::REGISTER_AUTH,
		[](Session& session) {std::cout << (int)session.GetState() << std::endl; },
		RegState::UNREGISTER_UNAUTH
	};
	RegisterMarchine::GetInstance()->RegisterStateLinker(std::move(linker3));
	StateLinker linker4 = {
		Event::UNREGISTER_AUTH,
		RegState::UNREGISTER_UNAUTH,
		[](Session& session) {std::cout << (int)session.GetState() << std::endl; },
		RegState::UNREGISTER_AUTH
	};
	RegisterMarchine::GetInstance()->RegisterStateLinker(std::move(linker4));

	Session session;
	session.SetState(RegState::UNREGISTER_AUTH);
	RegisterMarchine::GetInstance()->TransferState(Event::REGISTER_REQUEST, session);
}