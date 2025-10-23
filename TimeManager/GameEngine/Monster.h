#pragma once
#include"Object.h"
#include"ResourceManager.h"
#include"Animation.h"
class Monster: public Object
{
	enum ANIMATION
	{
		IDLE,
		END
	};
private:
	Animation m_AnimationList[DIRECTION::END][ANIMATION::END];
	ANIMATION m_eCurAnimation;
	DIRECTION m_eDirection;
	const float m_fMoveSpeed;
public:
	Monster();
	~Monster();
	virtual void Init(Vector2 _vec2Position);
	virtual void Update() override;
	virtual void Render(HDC _memDC) override;
};

