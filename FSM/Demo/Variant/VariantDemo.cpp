/*
	Copyright (c) 2018 Andrew Depke
*/
#include "../../Include/Variant/FSM.h"

#include <iostream>

using namespace Variant;

struct DemoEventA
{
	int Data;

	DemoEventA(int InData) : Data(InData) {}
};

struct DemoEventB
{
	float Data;

	DemoEventB(float InData) : Data(InData) {}
};

class DemoStateA
{
	template <typename, typename>
	friend class FSM;

protected:
	void OnEnter() { std::cout << "DemoStateA OnEnter\n"; }
	void OnExit() { std::cout << "DemoStateA OnExit\n"; }
};

class DemoStateB
{
	template <typename, typename>
	friend class FSM;

protected:
	void OnEnter() { std::cout << "DemoStateB OnEnter\n"; }
	void OnExit() { std::cout << "DemoStateB OnExit\n"; }
};

class DemoFSM : public FSM<DemoFSM, std::variant<DemoStateA, DemoStateB>>
{
public:
	template <typename T>
	DemoFSM(T&& InitialState) : FSM(std::forward<T>(InitialState)) {}

	OnEventReturnType OnEvent(DemoStateA& s, const DemoEventA& e);
	OnEventReturnType OnEvent(DemoStateA& s, const DemoEventB& e);
	OnEventReturnType OnEvent(DemoStateB& s, const DemoEventA& e);
	OnEventReturnType OnEvent(DemoStateB& s, const DemoEventB& e);

	// Catch all case.
	template <typename StateType, typename EventType>
	OnEventReturnType OnEvent(StateType&, const EventType&);
};

DemoFSM::OnEventReturnType DemoFSM::OnEvent(DemoStateA& s, const DemoEventA& e)
{
	std::cout << "DemoStateA OnEvent DemoEventA(Data: " << e.Data << "): Switching to DemoStateB\n";

	return DemoStateB{};
}

DemoFSM::OnEventReturnType DemoFSM::OnEvent(DemoStateA& s, const DemoEventB& e)
{
	std::cout << "DemoStateA OnEvent DemoEventB(Data: " << e.Data << "): Ignoring\n";

	return std::nullopt;
}

DemoFSM::OnEventReturnType DemoFSM::OnEvent(DemoStateB& s, const DemoEventA& e)
{
	std::cout << "DemoStateB OnEvent DemoEventA(Data: " << e.Data << "): Ignoring\n";

	return std::nullopt;
}

DemoFSM::OnEventReturnType DemoFSM::OnEvent(DemoStateB& s, const DemoEventB& e)
{
	std::cout << "DemoStateB OnEvent DemoEventB(Data: " << e.Data << "): Switching to DemoStateA\n";

	return DemoStateA{};
}

template <typename StateType, typename EventType>
DemoFSM::OnEventReturnType DemoFSM::OnEvent(StateType&, const EventType&)
{
	std::cout << "Catch All Case Invoked\n";

	return std::nullopt;
}

int main()
{
	DemoFSM Engine(DemoStateA{});

	std::cout << "=== Dispatching DemoEventB ===\n";

	Engine.Dispatch(DemoEventB{ 5.2f });

	std::cout << "=== Dispatching DemoEventA ===\n";

	Engine.Dispatch(DemoEventA{ 3 });

	std::cout << "=== Dispatching DemoEventB ===\n";

	Engine.Dispatch(DemoEventB{ 8.9f });

	std::cout << "=== Dispatching DemoEventB ===\n";

	Engine.Dispatch(DemoEventB{ 0.4f });

	std::cout << "=== Dispatching DemoEventA ===\n";

	Engine.Dispatch(DemoEventA{ 62 });

	system("pause");

	return 0;
}