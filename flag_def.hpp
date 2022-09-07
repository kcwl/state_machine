#pragma once
#include <cstdint>

namespace fsm
{
	enum class DriveFlag : uint8_t
	{
		Drive_Flag_None = 0x0,
		Drive_Flag_Update = 0x1,
		Drive_Flag_Initialize = 0x2,
		Drive_Flag_Deactivate = 0x4,
		Drive_Flag_Finalize = 0x8
	};
}