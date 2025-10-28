#pragma once
#include "Object.h"
#include "ResourceManager.h"
#include "Animation.h"
class Sword;
class Player : public Object
{
	enum ANIMATION
	{
		IDLE,
		RUN,
		ATTACK,
		END,
	};
private:
	Animation m_AnimationList[DIRECTION::END][ANIMATION::END];
	ANIMATION m_eCurAnimation;
	DIRECTION m_eDirection;
	const float m_fMoveSpeed;

	Sword* m_Sword;

public:
	Player();
	~Player();
	// Object을(를) 통해 상속됨
	void SetAnimation(ANIMATION _eAnimation)
	{
		m_eCurAnimation = _eAnimation;
	}
	virtual void Init(Vector2 _vec2Position);
	virtual void Update() override;
	virtual void Render(HDC _memDC) override;

	void BeginAttack();
	void EndAttack();
};