/*
	Copyright (c) 2018 Andrew Depke
*/
#pragma once

#include <optional>
#include <memory>

#include "Event.h"

namespace SingleDispatch
{
	template <typename>
	class FSM;

	// Base Class for States
	template <typename EventType_>
	class State
	{
		friend class FSM<State<EventType_>>;

	protected:
		using EventType = EventType_;
		using OnEventReturnType = std::optional<std::unique_ptr<State>>;

	public:
		State() = default;
		State(const State&) = delete;
		State(State&&) noexcept = default;
		virtual ~State() = default;

		State& operator=(const State&) = delete;
		State& operator=(State&&) = default;

		virtual OnEventReturnType OnEvent(EventType e) { return std::nullopt; }

	protected:
		virtual void OnEnter() {}
		virtual void OnExit() {}
	};
}  // namespace SingleDispatch