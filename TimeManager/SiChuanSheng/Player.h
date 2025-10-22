#pragma once
#include "Object.h"
#include "ResourceManager.h"
#include "Animation.h"
class Player : public Object
{
	enum ANIMATION
	{
		IDLE,
		ATTACK_1,
		END,
	};
private:
	Animation m_AnimationList[ANIMATION::END];
	ANIMATION m_eCurAnimation;
public:
	Player();
	~Player();
	// Object을(를) 통해 상속됨
	void FireArrow();
	virtual void Init(Vector2 _vec2Position);
	virtual void Update() override;
	virtual void Render(HDC _memDC) override;
};