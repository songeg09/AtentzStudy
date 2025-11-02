#pragma once

class RectZone;
class RectDamageSkill : public Skill
{
private:
	RectZone* m_pSkillObject;
public:
	RectDamageSkill(int _iIndex, Actor* _pCaster, int _iKey);

	void Create() override;
	void Cast() override;
	void Fire() override;
};
