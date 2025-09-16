#include "Shape.h"
#include "GDIManager.h"

Shape::Shape()
{
}

Shape::Shape(HDC _hdc, POINT _pt, COLOR _color)
	:m_hdc(_hdc), m_initialPoint(_pt), m_color(_color)
{
}

void Shape::DrawWithColor()
{
	GDIManager::GetInstance().SetColor(m_hdc,m_color);
	Draw();
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