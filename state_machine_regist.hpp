#pragma once


#define Regist_Begin(Action) \
private: \
using action_type = Action; \
template<Action f, template<Action> typename PlayerAction> \
struct state_traits;

#define Regist_Content(Flag, Action) \
template<template<decltype(Flag)> typename PlayerAction>\
struct state_traits<Flag,PlayerAction> \
{ \
	template<typename... Args> \
	static std::shared_ptr<basic_state_action<decltype(Flag)>> delivery(ActionFlag flag, Args&&... args) \
	{ \
		return std::make_shared<PlayerAction<Flag>>(std::bind(Action, std::forward<Args>(args)...), flag);\
	}\
}

#define Regist_End(PlayerAction) \
public: \
template<action_type f, typename... Args> \
void pass(Args&&... args) \
{ \
	add(state_traits<f,PlayerAction>::template delivery(action_flag_, this, std::forward<Args>(args)...)); \
}