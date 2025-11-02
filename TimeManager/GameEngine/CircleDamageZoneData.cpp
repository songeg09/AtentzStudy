#include "pch.h"
#include "CircleDamageZoneData.h"

void CircleDamageZoneData::Load(std::wifstream& _loadFile)
{
	int tmp;
	_loadFile >> tmp;
	_loadFile >> m_fRadius;
	_loadFile >> m_iAnimationStart;
	_loadFile >> m_iAnimationEnd;
}
