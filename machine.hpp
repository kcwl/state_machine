#pragma once
#include <deque>
#include <vector>
#include <memory>
#include <functional>
#include "action.hpp"
#include "state.hpp"
#include "time_tracker.hpp"
#include "regist.hpp"
#include "flag_def.hpp"

namespace fsm
{
	template<typename _State, template<typename>typename _Action, typename _Timer = micro_timer>
	class machine
	{
		using drive_flag = basic_state<uint8_t, DriveFlag>;

		using state_t = _State;

		using time_type = typename _Timer::value_type;

	public:
		machine()
			: diff_()
			, timer_(_Timer::zero)
		{

		}

		machine(time_type diff)
			: diff_(diff)
			, timer_(diff)
		{
		}

		virtual ~machine() = default;

	public:
		void add(std::shared_ptr<_Action<_State>> action_ptr)
		{
			if (!action_ptr)
				return;

			actions_.push_back(action_ptr);
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
		}

		void update(time_type diff = _Timer::zero)
		{
			if (actions_.empty())
				return;

			timer_.update(diff);

			if (!timer_.passed())
				return;

			drive_flag_.add(DriveFlag::Drive_Flag_Update);

			auto top = actions_.begin();

			current_state_ = (*top)->state();

			if ((*top)->invoke())
			{
				remove();
			}

			drive_flag_.remove(DriveFlag::Drive_Flag_Update);

			timer_.reset(diff_);
		}

	private:
		drive_flag drive_flag_;

		std::vector<std::shared_ptr<_Action<_State>>> actions_;

		time_type diff_;

		state_t current_state_;

		_Timer timer_;
	};
}