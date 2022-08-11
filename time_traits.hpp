#pragma once
#include <chrono>

namespace state
{
	namespace detail
	{
		using namespace std::chrono_literals;

		template<typename T>
		struct time_traits {};

		template<>
		struct time_traits<std::chrono::milliseconds>
		{
			static void increament(std::chrono::milliseconds& time, const std::chrono::milliseconds diff)
			{
				time += diff;
			}

			static bool passed(const std::chrono::microseconds& time)
			{
				return time <= 0ms;
			}

			static void assignment(std::chrono::microseconds& time, const std::chrono::microseconds& diff)
			{
				time = diff;
			}
		};

		template<>
		struct time_traits<std::chrono::seconds>
		{
			static void increament(std::chrono::seconds& time, const std::chrono::seconds diff)
			{
				time += diff;
			}

			static bool passed(const std::chrono::seconds& time)
			{
				return time <= 0s;
			}

			static void assignment(std::chrono::seconds& time, const std::chrono::seconds& diff)
			{
				time = diff;
			}
		};
	}

	
}