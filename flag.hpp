#pragma once
#include "flag_def.hpp"
#include "detail/flag_base.hpp"

namespace statemachine
{
	using action_flag = detail::flag_base<uint16_t, ActionFlag>;
}