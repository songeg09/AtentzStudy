#pragma once
#include "Object.h"
#include "ResourceManager.h"

class Arrow : public Object
{
private:
	int m_iMaxPosition_x;
	float m_fSpeed;
	Vector2 m_vecDirection;

public:
	Arrow();
	~Arrow();
	virtual void Update() override;
	virtual void Init(Vector2 _vec2Position, TEXTURE_TYPE _eTexture_Type) override;
	void Init(Vector2 _vec2Position, TEXTURE_TYPE _eTexture_Type, float _fSpeed, Vector2 _vecDirection);
};

