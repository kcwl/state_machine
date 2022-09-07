#pragma once
#include <functional>

namespace fsm
{
	template<typename _State>
	class state_action
	{
	public:
		virtual ~state_action() = default;

	public:
		virtual void initialize() = 0;

		virtual void finalize() = 0;

		virtual void reset() = 0;

		virtual void deactivate() = 0;

		virtual bool invoke() = 0;

		virtual _State state() = 0;
	};

	template<typename _State, _State st>
	class action : public state_action<_State>
	{
	public:
		using state_t = _State;

	public:
		action() = default;

		virtual ~action() = default;

	public:
		state_t state()
		{
			return st;
		}
	};
}