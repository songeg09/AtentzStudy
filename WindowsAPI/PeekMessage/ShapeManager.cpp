#include "ShapeManager.h"
#include "Qudrangle.h"
#include "Circle.h"
#include "Triangle.h"

ShapeManager::ShapeManager(HWND _hWnd)
{
	m_hWnd = _hWnd;
	m_hdc = GetDC(m_hWnd);

	m_mouseLButtonStatus.m_bDown = false;
	m_mouseLButtonStatus.m_bPress = false;
	m_mouseLButtonStatus.m_bUp = false;
}

ShapeManager::~ShapeManager()
{
	ReleaseDC(m_hWnd, m_hdc);
}

void ShapeManager::Update()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(m_hWnd, &pt);

	KeyUpdate();
	if (m_mouseLButtonStatus.m_bDown == true)
	{
		m_curShape = std::make_unique<Triangle>(m_hdc, pt, COLOR::BLACK);
	}

	if (m_curShape != nullptr)
	{
		if (m_mouseLButtonStatus.m_bUp == true)
		{
			m_vecShapes.push_back(std::move(m_curShape));
			Draw();
		}
		if (m_mouseLButtonStatus.m_bPress == true)
		{
			if (*m_curShape != pt)
				InvalidateRect(m_hWnd, nullptr, true);
			Draw();
			m_curShape->SetRect(pt);
			m_curShape->Draw();
		}
	}
}

void ShapeManager::KeyUpdate()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (m_mouseLButtonStatus.m_bPress == false)
			m_mouseLButtonStatus.m_bDown = true;
		else
			m_mouseLButtonStatus.m_bDown = false;
		m_mouseLButtonStatus.m_bUp = false;
		m_mouseLButtonStatus.m_bPress = true;
	}
	else
	{
		if (m_mouseLButtonStatus.m_bPress == true)
			m_mouseLButtonStatus.m_bUp = true;
		else
			m_mouseLButtonStatus.m_bUp = false;
		m_mouseLButtonStatus.m_bPress = false;
		m_mouseLButtonStatus.m_bDown = false;
	}
}

void ShapeManager::Draw()
{
	for (const std::unique_ptr<Shape>& shapePtr: m_vecShapes)
	{
		shapePtr->Draw();
	}
}
