/*
	Copyright (c) 2018 Andrew Depke
*/
#include "../../Include/SingleDispatch/FSM.h"

#include <iostream>

using namespace SingleDispatch;

enum class DemoEvent
{
	Demo1,
	Demo2
};

class DemoStateA : public State<DemoEvent>
{
	template <typename>
	friend class FSM;

public:
	virtual OnEventReturnType OnEvent(EventType e) override;

protected:
	virtual void OnEnter() override { std::cout << "DemoStateA OnEnter\n"; }
	virtual void OnExit() override { std::cout << "DemoStateA OnExit\n"; }
};

class DemoStateB : public State<DemoEvent>
{
	template <typename>
	friend class FSM;

public:
	virtual OnEventReturnType OnEvent(EventType e) override;

protected:
	virtual void OnEnter() override { std::cout << "DemoStateB OnEnter\n"; }
	virtual void OnExit() override { std::cout << "DemoStateB OnExit\n"; }
};

State<DemoEvent>::OnEventReturnType DemoStateA::OnEvent(EventType e)
{
	switch (e)
	{
	case EventType::Demo1:
		std::cout << "DemoStateA OnEvent Demo1: Switching to DemoStateB\n";
		return std::make_unique<DemoStateB>();
	case EventType::Demo2:
		std::cout << "DemoStateA OnEvent Demo2: Ignoring\n";
		break;
	}

	return std::nullopt;
}

State<DemoEvent>::OnEventReturnType DemoStateB::OnEvent(EventType e)
{
	switch (e)
	{
	case EventType::Demo1:
		std::cout << "DemoStateB OnEvent Demo1: Ignoring\n";
		break;
	case EventType::Demo2:
		std::cout << "DemoStateB OnEvent Demo2: Switching to DemoStateA\n";
		return std::make_unique<DemoStateA>();
	}

	return std::nullopt;
}

int main()
{
	{
		FSM<State<DemoEvent>> Engine(DemoStateA{});

		std::cout << "=== Dispatching Demo2 ===\n";

		Engine.Dispatch(DemoEvent::Demo2);

		std::cout << "=== Dispatching Demo1 ===\n";

		Engine.Dispatch(DemoEvent::Demo1);

		std::cout << "=== Dispatching Demo2 ===\n";

		Engine.Dispatch(DemoEvent::Demo2);

		std::cout << "=== Dispatching Demo2 ===\n";

		Engine.Dispatch(DemoEvent::Demo2);

		std::cout << "=== Dispatching Demo1 ===\n";

		Engine.Dispatch(DemoEvent::Demo1);
	}

	system("pause");

	return 0;
}