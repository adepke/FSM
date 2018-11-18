#pragma once

#include <utility>

#include "State.h"
#include "Event.h"

namespace SingleDispatch
{
	template <typename StateType = State<Event>>
	class FSM
	{
	private:
		std::unique_ptr<StateType> ActiveState;

	public:
		template <typename T>
		FSM(T&& InitialState) : ActiveState(std::make_unique<std::remove_reference_t<T>>(std::move(InitialState)))
		{
			ActiveState->OnEnter();
		}

		template <typename EventType>
		void Dispatch(EventType e)
		{
			auto NewState = ActiveState->OnEvent(e);
			if (NewState)
			{
				// New state, begin a transition.

				ActiveState->OnExit();

				ActiveState = std::move(*NewState);

				ActiveState->OnEnter();
			}
		}

		auto& GetState() const
		{
			return *ActiveState;
		}
	};
}  // namespace SingleDispatch