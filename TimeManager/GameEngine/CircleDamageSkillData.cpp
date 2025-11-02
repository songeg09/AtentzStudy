#include "pch.h"
#include "CircleDamageSkillData.h"

void CircleDamageSkillData::Load(std::wifstream& _loadFile)
{
	int tmp;
	_loadFile >> tmp;
	_loadFile >> m_iCircleDamageZoneIndex;
	int UseTarget;
	_loadFile >> UseTarget;
	if (UseTarget == 1)
		m_bUseTarget = true;
	else
		m_bUseTarget = false;
}
