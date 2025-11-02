#pragma once
#include "Data.h"
class CircleDamageSkillData : public Data
{
private:
	int m_iCircleDamageZoneIndex;
	bool m_bUseTarget;
public:
	// Data을(를) 통해 상속됨
	void Load(std::wifstream& _loadFile) override;
	int GetCircleDamageZoneIndex() { return m_iCircleDamageZoneIndex; }
	bool GetUseTarget() { return m_bUseTarget; }
};

