#pragma once
#include"Object.h"
#include"ResourceManager.h"
#include"Animation.h"
class Monster: public Object
{
public:
	Monster();
	~Monster();
	virtual void Init(Vector2 _vec2Position);
	virtual void Action() override;

	void EndAttack();

	virtual void HitBy(Vector2 _vec2MoveForce, Collider* _other) override;
};

