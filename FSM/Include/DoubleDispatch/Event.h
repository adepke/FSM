/*
	Copyright (c) 2018 Andrew Depke
*/
#pragma once

#include <optional>
#include <memory>

namespace DoubleDispatch
{
	// Base Class for Events
	template <typename DerivedType>
	struct Event
	{
		Event() = default;
		Event(const Event&) = delete;
		Event(Event&&) noexcept = default;
		virtual ~Event() = default;

		Event& operator=(const Event&) = delete;
		Event& operator=(Event&&) = default;

		template <typename StateType>
		auto Dispatch(StateType& s) const
		{
			return s.OnEvent(*static_cast<const DerivedType* const>(this));
		}
	};
}  // namespace DoubleDispatch