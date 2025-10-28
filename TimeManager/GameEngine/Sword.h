#pragma once
#include "Object.h"

class Sword : public Object
{
private:
	Object* m_Owner;

public:
	Sword();
	~Sword();

	virtual void SetPosition(DIRECTION _eDriection);

	virtual void Init(Vector2 _vec2Position, Object* _Owner);
	virtual void Render(HDC _memDC) override;
	virtual void Update() override;

};

