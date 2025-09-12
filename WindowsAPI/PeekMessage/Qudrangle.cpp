#include "Qudrangle.h"

Qudrangle::Qudrangle(HDC _hdc, POINT _pt, COLOR _color)
	:Shape(_hdc,_pt,_color)
{
}

void Qudrangle::Draw()
{
	Rectangle(m_hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
}

