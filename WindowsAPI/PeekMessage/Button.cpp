#include "Button.h"

Button::Button()
{
}

Button::~Button()
{
}

void Button::Init(HDC _hdc, POINT _pt, std::function<void()> _callBackFunc, std::wstring _Text)
{
	m_hdc = _hdc;
	m_rect = { _pt.x - WIDTH / 2, _pt.y - HEIGHT / 2, _pt.x + WIDTH / 2, _pt.y + HEIGHT / 2 };
	m_callBackFunc = _callBackFunc;
	m_strText = _Text;
}

void Button::OnButtonClick()
{
	m_callBackFunc();
}

bool Button::isClicked(POINT pt)
{
	return PtInRect(&m_rect, pt);
}

void Button::Draw()
{
	Rectangle(m_hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
	SetTextAlign(m_hdc, TA_CENTER);
	TextOut(m_hdc, (m_rect.left + m_rect.right) / 2, (m_rect.top + m_rect.bottom) / 2, m_strText.c_str(), m_strText.length());
}
