#pragma once
#include "Object.h"
class SkillObject abstract : public Object
{
private:
	Object* m_pTarget;
public:
	SkillObject();
	virtual ~SkillObject();
	void Init(Object* _pTarget);
	// Object을(를) 통해 상속됨
	virtual void Update() override;
};

