#pragma once
#include"SkillObject.h"
#include "Animation.h"

class Actor;
class CircleCollider;
class CircleDamageZone : public SkillObject
{
private:
	std::list<Actor*> m_TargetList;
	CircleCollider* m_pAttackCollider;
	Animation m_Animation;
	bool m_bEnable;
public:
	CircleDamageZone();
	~CircleDamageZone();
	void Init(int _iIndex, Object* _pTarget = nullptr);
	void Update() override;
	void Render(HDC _memDC) override;
	void SetEnable(bool _bEnabled);
	const std::list<Actor*>& GetTargetList() { return m_TargetList; }
};

