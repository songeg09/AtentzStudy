#pragma once
#include"ResourceManager.h"
#include "Animation.h"

class Collider;
class Object
{
protected:
	enum ANIMATION
	{
		IDLE,
		RUN,
		ATTACK,
		END,
	};

	Animation				m_AnimationList[DIRECTION::END][ANIMATION::END];
	ANIMATION				m_eCurAnimation;
	Vector2					m_vec2Position;
	Vector2					m_vec2Scale;
	Vector2					m_vec2ExternalForce;
	DIRECTION				m_eDirection;

	const float				m_fMoveSpeed;

	std::list<Collider*>	m_pColliders;

public:
	Object(float _fMoveSpeed);
	virtual ~Object();

	virtual void Update();
	virtual void LateUpdate() final; // 자식 Class에서 Override하지 못하게 막는 용도
	virtual void Render(HDC _memDC);
	virtual void Init(Vector2 _vec2Position);
	
	virtual void Action() = 0;
	virtual void KnockBack();

	inline std::list<Collider*>& GetColliders() { return m_pColliders; }
	void AddPosition(Vector2 _vec2Add) { m_vec2Position += _vec2Add; }
	void SetPosition(Vector2 _vec2Position) { m_vec2Position = _vec2Position; }
	void SetScale(Vector2 _vec2Scale) { m_vec2Scale = _vec2Scale; }
	Vector2 GetPosition() { return m_vec2Position; }
	Vector2 GetScale() { return m_vec2Scale; }

	void SetExternalForce(Vector2 _vec2MoveForce);
	Vector2 GetExternalForce() { return m_vec2ExternalForce; }

	void SetAnimation(ANIMATION _eAnimation){m_eCurAnimation = _eAnimation;}
	ANIMATION GetAnimation() { return m_eCurAnimation; }

	virtual void HitBy(Vector2 _vec2MoveForce, Collider* _other);
};

