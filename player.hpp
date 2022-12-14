#pragma once
#include <iostream>
#include "detail.hpp"
#include "state_machine.hpp"

namespace statemachine
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

	template<MoveFlag f>
	class player_action : public default_state_action<MoveFlag, f>
	{
	public:
		template<typename Func>
		player_action(Func&& func, ActionFlag flag = ActionFlag::Action_Flag_None)
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
		Regist_Begin(MoveFlag);
			Regist_Content(MoveFlag::walk, &walk);
			Regist_Content(MoveFlag::run, &run);
			Regist_Content(MoveFlag::jump, &jump);
			Regist_Content(MoveFlag::climb, &climb);
		Regist_End(player_action);

	private:
		bool walk(int task)
		{
			ignore(task);
			std::cout << "player is walking" << std::endl;
			return true;
		}

		bool run(int task)
		{
			ignore(task);
			std::cout << "player is running" << std::endl;
			return true;
		}

		bool jump(int task)
		{
			ignore(task);
			std::cout << "player is jumping" << std::endl;
			return true;
		}

		bool climb(int task)
		{
			ignore(task);
			std::cout << "player is climbing" << std::endl;
			return true;
		}
	};
}