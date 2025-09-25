#pragma once

#define SINGLETON(Type) public:\
	static Type* GetInstance()\
	{\
		static Type instance;\
		return &instance;\
	}\
\
	private:\
		Type();\
		~Type();

enum class BOARD_SIZE
{
	WIDTH = 6,
	HEIGHT = 4,
};
