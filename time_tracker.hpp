#pragma once
#include "detail/time_traits.hpp"

namespace state
{
	template<typename Time, typename Traits = detail::time_traits<Time>>
	class baisc_time_tracker
	{
	public:
		constexpr static auto zero = Traits::zero;

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
	using micro_time_tracker = baisc_time_tracker<T, detail::time_traits<detail::milliseconds<T>>>;

	template<typename T>
	using second_time_tracker = baisc_time_tracker<T, detail::time_traits<detail::seconds<T>>>;
}