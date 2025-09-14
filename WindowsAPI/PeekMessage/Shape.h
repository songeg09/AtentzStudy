#pragma once
#include "framework.h"

enum COLOR
{
	BLACK = 0,
	RED,
	BLUE,
	GREEN,
	WHITE,
	COUNT_COLOR
};

class Shape
{
protected:
	HDC m_hdc;
	RECT m_rect;
	POINT m_initialPoint;
	COLOR m_color;

public:
	Shape();
	Shape(HDC _hdc, POINT _pt, COLOR _color);

	virtual void Draw() = 0;
	void DrawWithColor();

	void SetRect(POINT pt);
	bool operator !=(POINT _pt)
	{
		return !(m_rect.right == _pt.x && m_rect.bottom == _pt.y);
	}
	bool operator ==(POINT _pt)
	{
		return m_rect.right == _pt.x && m_rect.bottom == _pt.y;
	}

	void SetColor(COLOR _color)
	{
		m_color = _color;
	}
};

