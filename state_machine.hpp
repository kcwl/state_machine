#pragma once
#include <deque>
#include <vector>
#include <memory>
#include <functional>
#include "state_action.hpp"
#include "time_tracker.hpp"
#include "state_machine_regist.hpp"

namespace statemachine
{
	class delay_action
	{
	public:
		using delay_action_func = std::function<void()>;
		using delay_filter = std::function<bool()>;

		delay_action(delay_action_func&& func, delay_filter&& filter)
			: action_(func)
			, filter_(filter)
		{}

		void resolve()
		{
			if (!filter_())
				return;

			action_();
		}

		delay_action_func action_;

		delay_filter filter_;
	};

	template<typename Timer, typename Enum>
	class state_machine
	{
		using drive_flag = detail::flag_base<uint8_t, DriveFlag>;

	public:
		state_machine()
			: diff_()
			, timer_(micro_time_tracker<Timer>::zero)
		{

		}

		state_machine(Timer diff)
			: diff_(diff)
			, timer_(diff)
		{
		}

		virtual ~state_machine() = default;

	public:
		void add(std::shared_ptr<basic_state_action<Enum>> action_ptr)
		{
			if (!action_ptr)
				return;

			if (drive_flag_.has(DriveFlag::Drive_Flag_Delay))
			{
				delay_action::delay_action_func action = [this, action_ptr]()
				{
					add(action_ptr);
				};

				delay_actions_.push_back({ std::move(action), [] {return true; } });
			}
			else
			{
				actions_.push_back(std::move(action_ptr));
			}
		}

		void remove()
		{
			if (actions_.empty())
				return;

			actions_.erase(actions_.begin());
		}

		void clear()
		{
			if (actions_.empty())
				return;

			actions_.clear();

			delay_actions_.clear();
		}

		void delay()
		{
			drive_flag_.remove(DriveFlag::Drive_Flag_Delay);
		}

		void update(Timer diff = micro_time_tracker<Timer>::zero)
		{
			timer_.update(diff);

			if (!timer_.passed())
				return;

			if (actions_.empty())
				return;

			drive_flag_.add(DriveFlag::Drive_Flag_Update);

			auto top = actions_.begin();

			current_state_ = (*top)->get_enum();

			if ((*top)->invoke_action())
			{
				remove();
			}

			resolve_delay_action();

			drive_flag_.remove(DriveFlag::Drive_Flag_Update);

			timer_.reset(diff_);
		}

		void set_action_flag(ActionFlag flag)
		{
			action_flag_.add(flag);
		}

	private:
		void resolve_delay_action()
		{
			while (!delay_actions_.empty())
			{
				delay_actions_.front().resolve();

				delay_actions_.pop_front();
			}
		}

	protected:
		ActionFlag action_flag_;

	private:
		drive_flag drive_flag_;

		std::vector<std::shared_ptr<basic_state_action<Enum>>> actions_;

		std::deque<delay_action> delay_actions_;

		Timer diff_;

		Enum current_state_;

		micro_time_tracker<Timer> timer_;
	};
}