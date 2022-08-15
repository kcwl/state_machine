#pragma once
#include "impl/flag_def.hpp"
#include "impl/flag_base.hpp"

namespace state
{
	using action_flag = impl::flag_base<uint16_t, impl::ActionFlag>;
}