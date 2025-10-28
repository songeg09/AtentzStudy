#pragma once
#include "Object.h"
#include "ResourceManager.h"
#include "Animation.h"
class Player : public Object
{
	
private:
	Collider* m_Sword;

public:
	Player();
	~Player();
	// Object을(를) 통해 상속됨
	
	virtual void Init(Vector2 _vec2Position);

	virtual void Action() override;

	void BeginAttack();
	void EndAttack();

	Collider* GetSword() { return m_Sword; }
};