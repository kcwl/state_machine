#pragma once
#include <chrono>

namespace fsm
{
	using namespace std::chrono_literals;

	template<typename _T>
	struct milliseconds
	{
		using type = _T;
	};

	template<typename _T>
	struct seconds
	{
		using type = _T;
	};

	template<typename _T>
	struct time_traits;

	template<typename _T>
	struct time_traits<milliseconds<_T>>
	{
		using value_type = typename milliseconds<_T>::type;
		static void increament(value_type& time, const value_type& diff)
		{
			time += diff;
		}

		static bool passed(const value_type& time)
		{
			return time <= 0ms;
		}

		static void assignment(value_type& time, const value_type& diff)
		{
			time = diff;
		}

		constexpr static auto zero = value_type(0ms);
	};

	template<typename _T>
	struct time_traits<seconds<_T>>
	{
		using value_type = typename seconds<_T>::type;

		static void increament(value_type& time, const value_type& diff)
		{
			time += diff;
		}

		static bool passed(const value_type& time)
		{
			return time <= 0s;
		}

		static void assignment(value_type& time, const value_type& diff)
		{
			time = diff;
		}

		constexpr static auto zero = std::chrono::seconds(0s);
	};
}