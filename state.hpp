#pragma once
#include <type_traits>

namespace fsm
{
	template<typename _T, typename _R>
		requires(std::is_integral_v<_T>&& std::is_enum_v<_R>)
	class basic_state
	{
	public:
		basic_state()
			: flag_()
		{
		}

	public:
		void add(_R f)
		{
			flag_ = flag_ & ~static_cast<_T>(f) | static_cast<_T>(f);
		}

		void remove(_R f)
		{
			flag_ = flag_ & ~static_cast<_T>(f);
		}

		bool has(_R f)
		{
			return (flag_ & static_cast<_T>(f)) != 0;
		}

	private:
		_T flag_;
	};
}