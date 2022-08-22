#pragma once
#include <functional>
#include "flag.hpp"

namespace statemachine
{
	template<typename Enum>
	class basic_state_action
	{
	public:
		virtual ~basic_state_action() = default;

		virtual bool invoke_action() = 0;

		virtual Enum get_enum() = 0;
	};

	template<typename Enum, Enum es>
	class default_state_action : public basic_state_action<Enum>
	{
	public:
		constexpr static Enum value = es;

	public:
		template<typename Func>
		default_state_action(Func&& f, detail::ActionFlag flag)
			: func_(std::forward<Func>(f))
		{
			flag_.add(flag);
		}

		virtual ~default_state_action() = default;

	public:
		bool invoke_action() override final
		{
			if (flag_.has(detail::ActionFlag::Action_Flag_Finalize))
				return false;

			if (flag_.has(detail::ActionFlag::Action_Flag_Initialize))
			{
				flag_.remove(detail::ActionFlag::Action_Flag_Initialize);

				initialize();
			}

			if (flag_.has(detail::ActionFlag::Action_Flag_Deactivate))
			{
				flag_.remove(detail::ActionFlag::Action_Flag_Deactivate);

				reset();
			}

			if (!update())
				return false;

			if (flag_.has(detail::ActionFlag::Action_Flag_Finalize))
				finalize();

			return true;
		}

		Enum get_enum() override
		{
			return value;
		}

	public:
		virtual void initialize() {};

		virtual void finalize() {}

		virtual void reset() {};

		virtual void deactivate() {};

	private:
		bool update()
		{
			return func_();
		}

	private:
		action_flag flag_;

		std::function<bool()> func_;
	};
}