#pragma once
#include <chrono>

namespace state
{
	namespace detail
	{
		using namespace std::chrono_literals;

		template<typename T>
		struct milliseconds
		{
			using type = T;
		};

		template<typename T>
		struct seconds
		{
			using type = T;
		};

		template<typename T>
		struct time_traits;

		template<typename T>
		struct time_traits<milliseconds<T>>
		{
			using value_type = typename milliseconds<T>::type;
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

		template<typename T>
		struct time_traits<seconds<T>>
		{
			using value_type = typename seconds<T>::type;

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

	
}