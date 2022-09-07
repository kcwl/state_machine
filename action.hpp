#pragma once
#include <functional>

namespace fsm
{
	template<typename _State>
	class basic_action
	{
	public:
		template<typename _Func, typename... _Args>
		basic_action(_Func&& f, _Args&&... args)
		{
			auto func = std::bind(std::forward<_Func>(f), std::forward<_Args>(args)...);

			func_ = [func = std::move(func)]
			{
				func();
			};
		}

		virtual ~basic_action() = default;

	public:
		virtual void initialize() {};

		virtual void finalize() {}

		virtual void reset() {};

		virtual void deactivate() {};

		virtual _State state() { return{}; }

		bool invoke()
		{
			func_();

			return true;
		}

	private:
		std::function<void()> func_;
	};

	template<typename _State, _State act>
	class action : public basic_action<_State>
	{
	public:
		using state_t = _State;

	public:
		template<typename _Func, typename... _Args>
		action(_Func&& f, _Args&&... args)
			: basic_action<_State>(std::forward<_Func>(f), std::forward<_Args>(args)...)
		{

		}

		~action() = default;

	public:
		state_t state()
		{
			return act;
		}
	};
}