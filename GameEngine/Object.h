#pragma once
#include "pch.h"

class Object
{
private:
	Vector2 m_vec2Position;
	Vector2 m_vec2Scale;
public:
	Object();
	~Object();
	virtual void Init(Vector2 _vec2Position, Vector2 _vec2Scale);
	virtual void Update() = 0;
	virtual void Render(HDC _hDC) = 0;
	Vector2 GetPosition() { return m_vec2Position; }
	Vector2 GetScale() { return m_vec2Scale; }
	void SetPosition(Vector2 _vec2Position) { m_vec2Position = _vec2Position; }
	void SetScale(Vector2 _vec2Scale) { m_vec2Scale = _vec2Scale; }
};

