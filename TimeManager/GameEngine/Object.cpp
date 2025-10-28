#include "pch.h"
#include "Object.h"
#include "Texture.h"
#include "Collider.h"
#include "TimerManager.h"

Object::Object(float _fMoveSpeed)
	:m_fMoveSpeed(_fMoveSpeed)
{
	m_eDirection = DIRECTION::DOWN;
	m_eCurAnimation = ANIMATION::IDLE;
	m_vec2Position = {};
	m_vec2Scale = {};
	m_vec2ExternalForce = {0.f,0.f};
	m_pColliders = {};
}

Object::~Object()
{
	if (!m_pColliders.empty())
	{
		for (std::list<Collider*>::iterator it = m_pColliders.begin(); it != m_pColliders.end();)
		{
			delete *it;
			it = m_pColliders.erase(it);
		}
	}
}

void Object::LateUpdate()
{
	for (std::list<Collider*>::iterator it = m_pColliders.begin(); it != m_pColliders.end(); ++it)
	{
		(*it)->FinalUpdate();
	}
}

void Object::Render(HDC _memDC)
{
	m_AnimationList[m_eDirection][m_eCurAnimation].Render(_memDC, Object::GetPosition());
	for (std::list<Collider*>::iterator it = m_pColliders.begin(); it != m_pColliders.end(); ++it)
	{
		(*it)->Render(_memDC);
	}
}

void Object::Init(Vector2 _vec2Position)
{
	SetPosition(_vec2Position);
}

void Object::Update()
{
	if (m_vec2ExternalForce.Length() == 0.0f)
	{
		if (m_eCurAnimation != ANIMATION::ATTACK)
			Action();
	}
	else
	{
		KnockBack();
	}

	m_AnimationList[m_eDirection][m_eCurAnimation].Update();
}

void Object::KnockBack()
{
	m_eCurAnimation = ANIMATION::RUN;;
	Vector2 vec2MoveForce;

	vec2MoveForce = GetExternalForce() * TimerManager::GetInstance()->GetfDeltaTime();

	SetPosition(GetPosition() + vec2MoveForce);

	Vector2 vec2Friction = GetExternalForce();
	vec2Friction.Normalize();
	vec2Friction = vec2Friction * ConstValue::FRICTION * TimerManager::GetInstance()->GetfDeltaTime() * (-1.f);
	m_vec2ExternalForce = m_vec2ExternalForce + vec2Friction;

	if (GetExternalForce().Length() <= 0.2f)
	{
		m_vec2ExternalForce = { 0.f,0.f };
	}
}

void Object::SetExternalForce(Vector2 _vec2MoveForce)
{
	if (m_vec2ExternalForce.Length() > 0.2f)
		return;
	if(m_eCurAnimation != ANIMATION::ATTACK)
		m_vec2ExternalForce = _vec2MoveForce;
}

void Object::HitBy(Vector2 _vec2MoveForce, Collider* _Other)
{
	if (m_vec2ExternalForce.Length() > 0.2f)
		return;
	if (m_eCurAnimation == ANIMATION::ATTACK)
		return;

	m_vec2ExternalForce = _vec2MoveForce;
}
