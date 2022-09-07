#pragma once
#include "time_traits.hpp"

namespace fsm
{
	template<typename _Time, typename Traits = time_traits<_Time>>
	class baisc_time_tracker
	{
	public:
		constexpr static auto zero = Traits::zero;

		using value_type = _Time;

	public:
		baisc_time_tracker(_Time t)
			: expiry_time_(t)
		{

		}

	public:
		void update(_Time diff)
		{
			Traits::increament(expiry_time_, diff);
		}

		bool passed()
		{
			return Traits::passed(expiry_time_);
		}

		void reset(_Time diff)
		{
			Traits::assignment(expiry_time_, diff);
		}

	private:
		_Time expiry_time_;
	};

	using micro_timer = baisc_time_tracker<std::chrono::microseconds, time_traits<milliseconds<std::chrono::microseconds>>>;

	using second_timer = baisc_time_tracker<std::chrono::seconds, time_traits<seconds<std::chrono::seconds>>>;
}