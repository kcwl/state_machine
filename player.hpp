#pragma once
#include <iostream>
#include "detail.hpp"
#include "machine.hpp"

namespace fsm
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


	class walk_action : public action<MoveFlag, MoveFlag::walk>
	{
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

		bool invoke() override
		{
			std::cout << "player walk ....." << std::endl;
			return true;
		}
	};

	class run_action : public action<MoveFlag, MoveFlag::run>
	{
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

		bool invoke() override
		{
			std::cout << "player run ....." << std::endl;
			return true;
		}
	};

	class jump_action : public action<MoveFlag, MoveFlag::jump>
	{
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

		bool invoke() override
		{
			std::cout << "player jump ....." << std::endl;
			return true;
		}
	};

	class climb_action : public action<MoveFlag, MoveFlag::climb>
	{
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

		bool invoke() override
		{
			std::cout << "player climb ....." << std::endl;
			return true;
		}
	};

	class player : public machine<MoveFlag, state_action>
	{
	public:
		Regist_Begin(MoveFlag);
			Regist_Content(walk, walk_action);
			Regist_Content(run, run_action);
			Regist_Content(jump, jump_action);
			Regist_Content(climb, climb_action);
		Regist_End();
	};
}