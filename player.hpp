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

	static int a = 1;

	using namespace std::chrono_literals;

	template<MoveFlag f>
	class player_action : public default_state_action<MoveFlag, f>
	{
	public:
		template<typename Func>
		player_action(Func&& func, detail::ActionFlag flag = detail::ActionFlag::Action_Flag_None)
			: default_state_action<MoveFlag, f>(std::forward<Func>(func), flag)
		{

		}

	public:
		void initialize() override
		{
			std::cout << "player action initialize" << std::endl;
		}

		void finalize() override
		{
			std::cout << "player action finalize" << std::endl;
		}

		void reset() override
		{
			std::cout << "player action reset" << std::endl;
		}

		void deactivate() override
		{
			std::cout << "player action dectivate" << std::endl;
		}
	};

	class player : public state_machine<std::chrono::microseconds, MoveFlag>
	{
	public:
		player() = default;

	public:
		template<MoveFlag f>
		void pass()
		{
			add(state_traits<f>::template delivery(this));
		}

	private:
		bool walk(int task)
		{
			release(task);
			std::cout << "player is walking" << std::endl;
			return true;
		}

		bool run(int task)
		{
			release(task);
			std::cout << "player is running" << std::endl;
			return true;
		}

		bool jump(int task)
		{
			release(task);
			std::cout << "player is jumping" << std::endl;
			return true;
		}

		bool climb(int task)
		{
			release(task);
			std::cout << "player is climbing" << std::endl;
			return true;
		}

		template<MoveFlag f>
		struct state_traits {};

		template<>
		struct state_traits<MoveFlag::walk>
		{
			static std::shared_ptr<basic_state_action<MoveFlag>> delivery(player* player_ptr)
			{
				return std::make_shared<player_action<MoveFlag::walk>>(std::bind(&player::walk, player_ptr, a), detail::ActionFlag::Action_Flag_Initialize);
			}
		};

		template<>
		struct state_traits<MoveFlag::run>
		{
			static std::shared_ptr<basic_state_action<MoveFlag>> delivery(player* player_ptr)
			{
				return std::make_shared<player_action<MoveFlag::run>>(std::bind(&player::run, player_ptr, a));
			}
		};

		template<>
		struct state_traits<MoveFlag::jump>
		{
			static std::shared_ptr<basic_state_action<MoveFlag>> delivery(player* player_ptr)
			{
				return std::make_shared<player_action<MoveFlag::jump>>(std::bind(&player::jump, player_ptr, a));
			}
		};

		template<>
		struct state_traits<MoveFlag::climb>
		{
			static std::shared_ptr<basic_state_action<MoveFlag>> delivery(player* player_ptr)
			{
				return std::make_shared<player_action<MoveFlag::climb>>(std::bind(&player::climb, player_ptr, a));
			}
		};
	};
}