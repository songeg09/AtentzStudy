#pragma once
#include"Object.h"

class Texture;
class Button:public Object
{
private:
	std::function<void()> m_CallBackFunction;
	Texture*					m_pButtonTexture;
	RECT						m_rect;
public:
	Button();
	~Button();
	// Object을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render(HDC _memDC) override;
	virtual void Init(Vector2 _vec2Position, TEXTURE_TYPE _eTexture_Type) override;
	virtual void Init(Vector2 _vec2Position, TEXTURE_TYPE _eTexture_Type, std::function<void()> _CallBackFunction);
};

