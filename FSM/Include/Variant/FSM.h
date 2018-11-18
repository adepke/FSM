#include <variant>
#include <optional>
#include <utility>

namespace Variant
{
	template <typename DerivedType, typename StateVariant>
	class FSM
	{
	protected:
		using OnEventReturnType = std::optional<StateVariant>;

	private:
		StateVariant ActiveState;

	public:
		template <typename T>
		FSM(T&& InitialState) : ActiveState(std::move(InitialState))
		{
			std::visit([](auto& VariantState) { VariantState.OnEnter(); }, ActiveState);
		}

		template <typename EventType>
		void Dispatch(EventType&& e)
		{
			auto NewState = std::visit(
				[this, &e](auto& VariantState) -> std::optional<StateVariant> { return static_cast<DerivedType* const>(this)->OnEvent(VariantState, std::forward<EventType>(e)); },
				ActiveState
			);

			if (NewState)
			{
				// New state, begin a transition.

				std::visit([](auto& VariantState) { VariantState.OnExit(); }, ActiveState);

				ActiveState = std::move(*NewState);

				std::visit([](auto& VariantState) { VariantState.OnEnter(); }, ActiveState);
			}
		}
	};
}  // namespace Variant