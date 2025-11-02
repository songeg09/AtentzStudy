#pragma once
#include "Actor.h"
#include "ResourceManager.h"
#include "Skill.h"

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
	std::vector<Skill*> m_Skills;
	
public:
	Player();
	~Player();
	virtual void Init(Vector2 _vec2Position);
	virtual void Update() override;
	virtual void Render(HDC _memDC) override;
	virtual void Attack(Collider* _pOther) override;
	void Input();
};