#pragma once


#define Regist_Begin(Action) \
private: \
using action_type = Action; \
template<action_type f>\
struct state_traits;

#define Regist_Content(Flag, Action) \
template<>\
struct state_traits<action_type::Flag>\
{\
	template<typename... _Args>\
	static auto delivery(_Args&&... args)\
	{\
		return std::make_shared<Action>();\
	}\
};

#define Regist_End() \
public: \
template<action_type f, typename... Args> \
void pass(Args&&... args) \
{ \
	add(state_traits<f>::template delivery(std::forward<Args>(args)...)); \
}