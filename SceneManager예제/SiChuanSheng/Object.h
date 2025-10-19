#pragma once
#include"ResourceManager.h"

class Object
{
private:
	Vector2 m_vec2Position;
	Vector2 m_vec2Scale;
public:
	Object();
	virtual ~Object();

	virtual void Update() = 0;
	virtual void Render(HDC _memDC) = 0;
	virtual void Init(Vector2 _vec2Position, TEXTURE_TYPE _eTexture_Type) = 0;

	void AddPosition_x(int _x) { m_vec2Position.m_ix += _x; }
	void AddPosition_y(int _y) { m_vec2Position.m_iy += _y; }
	void SetPosition(Vector2 _vec2Position) { m_vec2Position = _vec2Position; }
	void SetScale(Vector2 _vec2Scale) { m_vec2Scale = _vec2Scale; }
	Vector2 GetPosition() { return m_vec2Position; }
	Vector2 GetScale() { return m_vec2Scale; }
};

