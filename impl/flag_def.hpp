#pragma once
#include "stdint.hpp"

namespace state
{
	namespace impl
	{
		enum class ActionFlag : uint16_t
		{
			Action_Flag_None = 0x000,
			Action_Flag_Initialize = 0x001,
			Action_Flag_Finalize = 0x002,
			Action_Flag_Deactivate = 0x004,
			Action_Flag_Pending = 0x008
		};
	}
}