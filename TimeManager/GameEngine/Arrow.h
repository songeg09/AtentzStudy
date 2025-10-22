#pragma once
#include "Object.h"
#include "ResourceManager.h"

class Arrow : public Object
{
private:
	int m_iMaxPosition_x;
	float m_fSpeed;

public:
	Arrow();
	~Arrow();
	void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
	virtual void Update() override;
	virtual void Init(Vector2 _vec2Position, TEXTURE_TYPE _eTexture_Type) override;
};

