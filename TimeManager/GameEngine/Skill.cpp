#include "pch.h"
#include "Skill.h"
#include "ResourceManager.h"
#include "CircleDamageSkillData.h"
#include "CircleDamageZone.h"
#include "Actor.h"
#include "SceneManager.h"
#include "InputManager.h"

Skill::Skill(int _iIndex, Actor* _pCaster, int _iKey)
{
	m_iKey = _iKey;
	InputManager::GetInstance()->RegistKey(m_iKey);
	m_iIndex = _iIndex;
	m_pCaster = _pCaster;
	if (m_pCaster->GetActorType() == ACTOR_TYPE::PLAYER)
		m_eSkillGroup = OBJECT_GROUP::PLAYER_SKILL;
	else if (m_pCaster->GetActorType() == ACTOR_TYPE::MONSTER)
		m_eSkillGroup = OBJECT_GROUP::MONSTER_SKILL;
}

void Skill::Input()
{
	switch (InputManager::GetInstance()->GetKeyState('Q'))
	{
	case KEY_STATE::DOWN:
		Create();
		break;
	case KEY_STATE::PRESS:
		Cast();
		break;
	case KEY_STATE::UP:
		Fire();
		break;
	}
}

CircleDamageSkill::CircleDamageSkill(int _iIndex, Actor* _pCaster, int _iKey)
	: Skill(_iIndex, _pCaster, _iKey)
{
	m_pSkillObject = nullptr;
}

void CircleDamageSkill::Create()
{
	CircleDamageSkillData* data = static_cast<CircleDamageSkillData*>(ResourceManager::GetInstance()->GetData(L"CircleDamageSkill.txt", Skill::GetIndex()));
	if (data != nullptr)
	{
		if (m_pSkillObject == nullptr)
		{
			m_pSkillObject = new CircleDamageZone;
			SceneManager::GetInstance()->GetCurScene()->AddObject(m_pSkillObject, Skill::GetObjectGroup());
		}

		if (data->GetUseTarget() == true)
			m_pSkillObject->Init(data->GetCircleDamageZoneIndex(), Skill::GetCaster());
		else
		{

			m_pSkillObject->Init(data->GetCircleDamageZoneIndex());
			m_pSkillObject->SetPosition(Skill::GetCaster()->GetPosition());
		}
	}
}

void CircleDamageSkill::Cast()
{
	const std::list<Actor*>& targetList = m_pSkillObject->GetTargetList();
	for (Actor* actor : targetList)
	{
		Vector2 ForceDirection = m_pSkillObject->GetPosition() - actor->GetPosition();
		if (ForceDirection.Length() >= 30.0f)
		{
			ForceDirection.Normalize();
			actor->SetVelocity(ForceDirection * 30.0f);
		}
		else
			actor->SetVelocity({ 0.0f,0.0f });
	}
}

void CircleDamageSkill::Fire()
{
	const std::list<Actor*>& targetList = m_pSkillObject->GetTargetList();
	for (Actor* actor : targetList)
	{
		Vector2 ForceDirection = actor->GetPosition() - m_pSkillObject->GetPosition();
		ForceDirection.Normalize();
		actor->AddForce(ForceDirection * 500.0f);
	}
	m_pSkillObject->SetEnable(false);
}