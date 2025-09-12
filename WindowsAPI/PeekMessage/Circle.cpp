#include "Circle.h"

Circle::Circle(HDC _hdc, POINT _pt, COLOR _color)
	:Shape(_hdc, _pt, _color)
{
}

void Circle::Draw()
{
	Ellipse(m_hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
}