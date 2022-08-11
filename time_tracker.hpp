#pragma once
#include "time_traits.hpp"

namespace state
{
	template<typename Time, typename Traits>
	class baisc_time_tracker
	{
	public:
		baisc_time_tracker(Time t)
			: expiry_time_(t)
		{

		}

	public:
		void update(Time diff)
		{
			Traits::increament(expiry_time_, diff);
		}

		bool passed()
		{
			return Traits::passed(expiry_time_);
		}

		void reset(Time diff)
		{
			Traits::assignment(expiry_time_, diff);
		}

	private:
		Time expiry_time_;
	};

	template<typename T>
	using time_tracker = baisc_time_tracker<T, detail::time_traits<T>>;
}