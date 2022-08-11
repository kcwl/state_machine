#pragma once
#include <type_traits>

namespace state
{
	template<typename T, typename R>
		requires(std::is_integral_v<T>&& std::is_enum_v<R>)
	class flag_base
	{
	public:
		flag_base()
			: flag_()
		{

		}

		flag_base(T all_flags)
			: flag_(all_flags)
		{

		}

	public:
		T operator|(R rhs)
		{
			return flag_ | static_cast<T>(rhs);
		}

		void operator|=(R rhs)
		{
			return flag_ |= rhs;
		}

		T operator&(R rhs)
		{
			return flag_ & static_cast<T>(rhs);
		}

		void operator&=(R rhs)
		{
			return flag_ &= rhs;
		}

	public:
		void add(R f)
		{
			flag_ = flag_ &= ~(f | 1) | f;
		}

		void remove(R f)
		{
			flag_ = flag_ &= ~(f | 1);
		}

		bool has(R f)
		{
			return (flag_ & f) != 0;
		}

	private:
		T flag_;
	};
}