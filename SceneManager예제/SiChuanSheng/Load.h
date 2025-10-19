#pragma once
#include"Object.h"

class Texture;
class Load : public Object
{
private:
	TEXTURE_TYPE		m_eBlockType;
	Texture*				m_pBlockTexture;
public:
	// Object을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render(HDC _memDC) override;
	virtual void Init(Vector2 _vec2Position, TEXTURE_TYPE _eTexture_Type) override;
};

