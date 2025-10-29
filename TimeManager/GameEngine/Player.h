#pragma once
#include "Actor.h"
#include "ResourceManager.h"
class Player : public Actor
{
	enum ANIMATION
	{
		IDLE,
		RUN,
		ATTACK,
		END,
	};
	
private:
	bool m_bInput;
	Collider* m_pAttackCollider;
public:
	Player();
	~Player();
	virtual void Init(Vector2 _vec2Position);
	virtual void Update() override;
	virtual void Render(HDC _memDC) override;
	virtual void Attack(Collider* _pOther) override;
	void Input();
};