#pragma once

#define SINGLETON(Type) public:		\
	static Type* GetInstance()		\
	{								\
		static Type instance;		\
		return &instance;			\
	}								\
									\
	private:						\
		Type();						\
		~Type();

enum class OBJECT_GROUP
{
	MONSTER,
	PLAYABLE,
	BULLET,
	END
};

enum class COLLIDER_GROUP
{
	MONSTER,
	PLAYABLE,
	BULLET,
	END
};