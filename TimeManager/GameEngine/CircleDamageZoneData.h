#pragma once
#include "Data.h"
class CircleDamageZoneData : public Data
{
private:
	float m_fRadius;
	int m_iAnimationStart;
	int m_iAnimationEnd;
public:
	// Data을(를) 통해 상속됨
	void Load(std::wifstream& _loadFile) override;
	float GetRadius() { return m_fRadius; }
	int GetAnimationStart() { return m_iAnimationStart; }
	int GetAnimationEnd() { return m_iAnimationEnd; }
};

