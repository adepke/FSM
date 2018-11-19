/*
	Copyright (c) 2018 Andrew Depke
*/
#pragma once

#include "Event.h"

namespace DoubleDispatch
{
	template <typename>
	class FSM;

	// Base Class for States
	template <typename Derived>
	class State
	{
		friend class FSM<State>;

	protected:
		using OnEventReturnType = std::optional<std::unique_ptr<Derived>>;

	public:
		State() = default;
		State(const State&) = delete;
		State(State&&) noexcept = default;
		virtual ~State() = default;

		State& operator=(const State&) = delete;
		State& operator=(State&&) = default;

		// State interface class needs to provide a virtual function OnEvent with an overload for all Event types.
		//virtual OnEventReturnType OnEvent(const EventType& e) { return std::nullopt; }

	protected:
		virtual void OnEnter() {}
		virtual void OnExit() {}
	};
}  // namespace DoubleDispatch