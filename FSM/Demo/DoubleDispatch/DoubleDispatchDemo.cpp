/*
	Copyright (c) 2018 Andrew Depke
*/
#include "../../Include/DoubleDispatch/FSM.h"

#include <iostream>

using namespace DoubleDispatch;

struct DemoEventA : public Event<DemoEventA>
{
	int Data;

	DemoEventA(int InData) : Data(InData) {}
};

struct DemoEventB : public Event<DemoEventB>
{
	float Data;

	DemoEventB(float InData) : Data(InData) {}
};

// This class is used as the State interface for this demo.
class DemoStateBase : public State<DemoStateBase>
{
	template <typename>
	friend class FSM;

public:
	virtual OnEventReturnType OnEvent(const DemoEventA& e) { return std::nullopt; }
	virtual OnEventReturnType OnEvent(const DemoEventB& e) { return std::nullopt; }
};

class DemoStateA : public DemoStateBase
{
public:
	OnEventReturnType OnEvent(const DemoEventA& e);
	OnEventReturnType OnEvent(const DemoEventB& e);

protected:
	virtual void OnEnter() override { std::cout << "DemoStateA OnEnter\n"; }
	virtual void OnExit() override { std::cout << "DemoStateA OnExit\n"; }
};

class DemoStateB : public DemoStateBase
{
public:
	OnEventReturnType OnEvent(const DemoEventA& e);
	OnEventReturnType OnEvent(const DemoEventB& e);

protected:
	virtual void OnEnter() override { std::cout << "DemoStateB OnEnter\n"; }
	virtual void OnExit() override { std::cout << "DemoStateB OnExit\n"; }
};

DemoStateBase::OnEventReturnType DemoStateA::OnEvent(const DemoEventA& e)
{
	std::cout << "DemoStateA OnEvent DemoEventA(Data: " << e.Data << "): Switching to DemoStateB\n";

	return std::make_unique<DemoStateB>();
}

DemoStateBase::OnEventReturnType DemoStateA::OnEvent(const DemoEventB& e)
{
	std::cout << "DemoStateA OnEvent DemoEventB(Data: " << e.Data << "): Ignoring\n";

	return std::nullopt;
}

DemoStateBase::OnEventReturnType DemoStateB::OnEvent(const DemoEventA& e)
{
	std::cout << "DemoStateB OnEvent DemoEventA(Data: " << e.Data << "): Ignoring\n";

	return std::nullopt;
}

DemoStateBase::OnEventReturnType DemoStateB::OnEvent(const DemoEventB& e)
{
	std::cout << "DemoStateB OnEvent DemoEventB(Data: " << e.Data << "): Switching to DemoStateA\n";

	return std::make_unique<DemoStateA>();
}

int main()
{
	FSM<DemoStateBase> Engine(DemoStateA{});

	std::cout << "=== Dispatching DemoEventB ===\n";

	Engine.Dispatch(DemoEventB{5.2f});

	std::cout << "=== Dispatching DemoEventA ===\n";

	Engine.Dispatch(DemoEventA{3});

	std::cout << "=== Dispatching DemoEventB ===\n";

	Engine.Dispatch(DemoEventB{8.9f});

	std::cout << "=== Dispatching DemoEventB ===\n";

	Engine.Dispatch(DemoEventB{0.4f});

	std::cout << "=== Dispatching DemoEventA ===\n";

	Engine.Dispatch(DemoEventA{62});

	system("pause");

	return 0;
}