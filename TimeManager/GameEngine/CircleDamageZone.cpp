#include "pch.h"
#include "CircleDamageZone.h"
#include "ResourceManager.h"
#include "CircleDamageZoneData.h"
#include "Collider.h"
#include "Actor.h"

CircleDamageZone::CircleDamageZone()
{
	m_pAttackCollider = nullptr;
}

CircleDamageZone::~CircleDamageZone()
{
}

void CircleDamageZone::Init(int _iIndex, Object* _pTarget)
{
	SkillObject::Init(_pTarget);

	CircleDamageZoneData* data = static_cast<CircleDamageZoneData*>(ResourceManager::GetInstance()->GetData(L"CircleDamageZone.txt", _iIndex));

	if (m_pAttackCollider == nullptr)
	{
		m_pAttackCollider = static_cast<CircleCollider*>(CreateCircleCollider(true, data->GetRadius()));
		m_pAttackCollider->SetBeginCollisionCallBack(
			[this](Collider* _pOther)
			{
				Actor* actor = dynamic_cast<Actor*>(_pOther->GetTarget());
				if (actor != nullptr)
					m_TargetList.push_back(actor);
			}
		);
		m_pAttackCollider->SetEndCollisionCallBack(
			[this](Collider* _pOther)
			{
				Actor* actor = dynamic_cast<Actor*>(_pOther->GetTarget());
				if (actor != nullptr)
					m_TargetList.remove(actor);
			}
		);
		m_Animation.Init(data->GetAnimationStart(), data->GetAnimationEnd(), ANIMATION_TYPE::LOOP, 0.3f, ANCHOR::CENTER);
	}
	else
	{
		m_pAttackCollider->SetEnable(true);
		m_pAttackCollider->SetSize(data->GetRadius());
		m_Animation.Reset();
	}
	SetEnable(true);
}

void CircleDamageZone::Update()
{
	if (m_bEnable == false)
		return;
	SkillObject::Update();
	m_Animation.Update();
}

void CircleDamageZone::Render(HDC _memDC)
{
	if (m_bEnable == false)
		return;
	Object::Render(_memDC);
	m_Animation.Render(_memDC, Object::GetPosition());
}

void CircleDamageZone::SetEnable(bool _bEnabled)
{
	m_bEnable = _bEnabled;
	if (m_pAttackCollider != nullptr)
	{
		m_pAttackCollider->SetEnable(m_bEnable);
	}
}
