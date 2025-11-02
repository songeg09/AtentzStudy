#include "pch.h"
#include "SkillObject.h"

SkillObject::SkillObject()
{
	m_pTarget = nullptr;
}

SkillObject::~SkillObject()
{
}

void SkillObject::Init(Object* _pTarget)
{
	m_pTarget = _pTarget;
}

void SkillObject::Update()
{
	if (m_pTarget != nullptr)
	{
		SetPosition(m_pTarget->GetPosition());
	}
}
