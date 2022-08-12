#pragma once
#include <iostream>
#include "detail.hpp"
#include "state_machine.hpp"

namespace state
{
	enum class MoveFlag :uint8_t
	{
		none = 0x0,
		walk = 0x1,
		run = 0x2,
		jump = 0x4,
		climb = 0x8
	};

	using namespace std::chrono_literals;

	class player : public state_machine<std::chrono::microseconds, MoveFlag>
	{
	public:
		player() = default;

	public:
		template<MoveFlag f>
		void pass()
		{
			add(state_traits<f>::delivery(this));
		}

	private:
		bool walk(task_base* task)
		{
			release(task);
			std::cout << "player is walking" << std::endl;
			return true;
		}

		bool run(task_base* task)
		{
			release(task);
			std::cout << "player is running" << std::endl;
			return true;
		}

		bool jump(task_base* task)
		{
			release(task);
			std::cout << "player is jumping" << std::endl;
			return true;
		}

		bool climb(task_base* task)
		{
			release(task);
			std::cout << "player is climbing" << std::endl;
			return true;
		}

		template<MoveFlag f>
		struct state_traits{};

		template<>
		struct state_traits<MoveFlag::walk>
		{
			static std::shared_ptr<basic_state_action<MoveFlag>> delivery(player* player_ptr)
			{
				return std::make_shared<state_action<MoveFlag, MoveFlag::walk>>(std::bind(&player::walk, player_ptr, std::placeholders::_1));
			}
		};

		template<>
		struct state_traits<MoveFlag::run>
		{
			static std::shared_ptr<basic_state_action<MoveFlag>> delivery(player* player_ptr)
			{
				return std::make_shared<state_action<MoveFlag, MoveFlag::run>>(std::bind(&player::run, player_ptr, std::placeholders::_1));
			}
		};

		template<>
		struct state_traits<MoveFlag::jump>
		{
			static std::shared_ptr<basic_state_action<MoveFlag>> delivery(player* player_ptr)
			{
				return std::make_shared<state_action<MoveFlag, MoveFlag::jump>>(std::bind(&player::jump, player_ptr, std::placeholders::_1));
			}
		};

		template<>
		struct state_traits<MoveFlag::climb>
		{
			static std::shared_ptr<basic_state_action<MoveFlag>> delivery(player* player_ptr)
			{
				return std::make_shared<state_action<MoveFlag, MoveFlag::climb>>(std::bind(&player::climb, player_ptr, std::placeholders::_1));
			}
		};
	};
}