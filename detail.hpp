#pragma once

namespace state
{
	template<typename T>
	void release(const T&){}

	template<typename T>
	void release(const T*){}
}