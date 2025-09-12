#include "Triangle.h"

void Triangle::DrawLine(HDC hdc, POINT p1, POINT p2)
{
	MoveToEx(hdc, p1.x, p1.y, NULL);
	LineTo(hdc, p2.x, p2.y);

}

Triangle::Triangle(HDC _hdc, POINT _pt, COLOR _color)
	:Shape(_hdc, _pt, _color)
{
}

void Triangle::Draw()
{
	POINT vertices[3] = { {m_initialPoint.x, m_rect.top},{m_rect.left, m_rect.bottom},{m_rect.right, m_rect.bottom} };
	for (int i = 0; i < 3; ++i)
	{
		DrawLine(m_hdc, vertices[i], vertices[(i+1)%3]);
	}
}