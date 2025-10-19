#include "pch.h"
#include "Button.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "InputManager.h"
#include "Core.h"

Button::Button()
{
	m_pButtonTexture = nullptr;
	m_CallBackFunction = nullptr;
}

Button::~Button()
{
}

void Button::Update()
{
	if (InputManager::GetInstance()->GetKeyState(VK_LBUTTON) == KEY_STATE::DOWN)
	{
		POINT ptMouse;
		GetCursorPos(&ptMouse);
		ScreenToClient(Core::GetInstance()->GethWnd(), &ptMouse);
		if (m_CallBackFunction != nullptr && PtInRect(&m_rect, ptMouse) == true)
			m_CallBackFunction();
	}
}

void Button::Render(HDC _memDC)
{
	TransparentBlt(_memDC, m_rect.left, m_rect.top, m_pButtonTexture->GetWidth(), m_pButtonTexture->GetHeight(), m_pButtonTexture->GetDC(),
		0, 0, m_pButtonTexture->GetWidth(), m_pButtonTexture->GetHeight(), RGB(255, 0, 255));
}

void Button::Init(Vector2 _vec2Position, TEXTURE_TYPE _eTexture_Type)
{
	m_pButtonTexture = ResourceManager::GetInstance()->LoadTexture(_eTexture_Type);

	Object::SetPosition(_vec2Position);
	Object::SetScale(Vector2{ m_pButtonTexture->GetWidth(),m_pButtonTexture->GetHeight() });
	m_rect.left = _vec2Position.m_ix;
	m_rect.top = _vec2Position.m_iy;
	m_rect.right = _vec2Position.m_ix + m_pButtonTexture->GetWidth();
	m_rect.bottom = _vec2Position.m_iy + m_pButtonTexture->GetHeight();
}

void Button::Init(Vector2 _vec2Position, TEXTURE_TYPE _eTexture_Type, std::function<void()> _CallBackFunction)
{
	Init(_vec2Position, _eTexture_Type);
	m_CallBackFunction = _CallBackFunction;
}
