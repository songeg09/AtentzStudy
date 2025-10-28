#include "pch.h"
#include "Collider.h"
#include "Object.h"
#include "GDIManager.h"

unsigned int Collider::s_uID = 0;



Collider::Collider()
	:m_uID(++s_uID)
{
	m_vecOffset = {};
	m_vecPosition = {};
	m_pTarget = nullptr;
	m_iCollisionCount = 0;
	m_bActive = true;
}

Collider::~Collider()
{
}

void Collider::Hit(Collider* _pOther)
{
	Vector2 KnockBackForce = m_vecPosition - _pOther->GetPosition();
	KnockBackForce.Normalize();
	KnockBackForce = KnockBackForce * ConstValue::KNOCKBACK_SPEED;

	m_pTarget->HitBy(KnockBackForce, _pOther);
}

void Collider::OnCollision(Collider* _pOther)
{
	Hit(_pOther);
}

void Collider::BeginCollision(Collider* _pOther)
{
	Hit(_pOther);
	m_iCollisionCount += 1;
}

void Collider::EndCollision(Collider* _pOther)
{
	m_iCollisionCount -= 1;
	assert(m_iCollisionCount >= 0);
}

void Collider::FinalUpdate()
{
	Vector2 vecObjectPosition = m_pTarget->GetPosition();

	m_vecPosition = vecObjectPosition + m_vecOffset;
}

void Collider::Render(HDC _memDC)
{
	if (m_bActive == false)
		return;
	GDIManager::GetInstance()->SetBrush(_memDC, BRUSH_TYPE::HOLLOW);
	if (m_iCollisionCount > 0)
		GDIManager::GetInstance()->SetPen(_memDC, PEN_TYPE::RED);
	else
		GDIManager::GetInstance()->SetPen(_memDC, PEN_TYPE::BLUE);

	Rectangle(_memDC,
		m_vecPosition.m_fx - m_vecSize.m_fx / 2.0f,
		m_vecPosition.m_fy - m_vecSize.m_fy / 2.0f,
		m_vecPosition.m_fx + m_vecSize.m_fx / 2.0f,
		m_vecPosition.m_fy + m_vecSize.m_fy / 2.0f
	);

	GDIManager::GetInstance()->ResetBrush(_memDC);
	GDIManager::GetInstance()->ResetPen(_memDC);
}
