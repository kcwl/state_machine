#pragma once
#include <functional>
#include "task_base.hpp"
#include "flag_base.hpp"

namespace state
{
	enum class ActionFlag : uint16_t
	{
		Action_Flag_None = 0x000,
		Action_Flag_Initialize = 0x001,
		Action_Flag_Finalize = 0x002,
		Action_Flag_Deactivate = 0x004,
		Action_Flag_Pending = 0x008
	};

	using action_flag = flag_base<uint16_t, ActionFlag>;

	template<typename Enum, Enum state>
	class basic_state_action
	{
	public:
		constexpr static Enum value = state;

	public:
		virtual ~basic_state_action() = default;

		virtual bool invoke_action() const = 0;
	};

	template<typename Enum, Enum state>
	class default_state_action : public basic_state_action<Enum,state>
	{
	public:
		void invoke_action() override final
		{
			if (flag_.has(ActionFlag::Action_Flag_Finalize))
				return;

			if (flag_.has(ActionFlag::Action_Flag_Initialize))
			{
				flag_.remove(ActionFlag::Action_Flag_Initialize);

				initialize();
			}

			if (flag_.has(ActionFlag::Action_Flag_Deactivate))
			{
				flag_.remove(ActionFlag::Action_Flag_Deactivate);

				reset();
			}

			return update();
		}

	public:
		virtual void initialize() {};

		virtual void finalize() {}

		virtual void reset() {};

		virtual void deactivate() {};

		virtual bool update(const task_base* task) = 0;

	public:
		action_flag flag_;
	};



	template<typename Enum, Enum value>
	class state_action : public default_state_action<Enum, value>
	{
	public:
		template<typename Func>
		state_action(Func&& f)
			: func_(std::forward<Func>(f))
		{

		}

	public:
		bool update(const task_base* task) override final
		{
			return func_(task);
		}

	private:
		std::function<bool(const task_base*)> func_;
	};
}