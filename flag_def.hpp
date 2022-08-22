#pragma once
#include "detail/stdint.hpp"

namespace statemachine
{
	enum class ActionFlag : uint16_t
	{
		Action_Flag_None = 0x000,
		Action_Flag_Initialize = 0x001,
		Action_Flag_Finalize = 0x002,
		Action_Flag_Deactivate = 0x004,
		Action_Flag_Pending = 0x008
	};


	enum class DriveFlag : uint8_t
	{
		Drive_Flag_None = 0x0,
		Drive_Flag_Update = 0x1,
		Drive_Flag_Initialize = 0x2,
		Drive_Flag_Pending = 0x4,

		Drive_Flag_Delay = Drive_Flag_Update | Drive_Flag_Pending
	};

}