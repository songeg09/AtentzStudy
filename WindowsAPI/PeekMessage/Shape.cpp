#include "Shape.h"

Shape::Shape()
{
}

Shape::Shape(HDC _hdc, POINT _pt, COLOR _color)
	:m_hdc(_hdc), m_initialPoint(_pt), m_color(_color)
{
}

void Shape::DrawWithColor()
{

	HPEN hColorPen;
	
	switch (m_color)
	{
	case COLOR::RED:
		hColorPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		break;
	case COLOR::BLUE:
		hColorPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
		break;
	case COLOR::GREEN:
		hColorPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
		break;
	case COLOR::WHITE:
		hColorPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
		break;
	default:
		hColorPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	}
	HPEN hPrevPen = (HPEN)SelectObject(m_hdc, hColorPen);
	
	Draw();

	SelectObject(m_hdc, hPrevPen);
	DeleteObject(hColorPen);
}

void Shape::SetRect(POINT _pt)
{
	int offset_x = _pt.x - m_initialPoint.x;
	int offset_y = _pt.y - m_initialPoint.y;
	
	m_rect.left = m_initialPoint.x - offset_x;
	m_rect.top = m_initialPoint.y - offset_y;

	m_rect.right = _pt.x;
	m_rect.bottom = _pt.y;
}