#include "ShapeManager.h"
#include "Qudrangle.h"
#include "Circle.h"
#include "Triangle.h"
#include <functional>


ShapeManager::ShapeManager(HWND _hWnd)
{
	m_hWnd = _hWnd;
	m_hdc = GetDC(m_hWnd);

	m_mouseLButtonStatus.m_bDown = false;
	m_mouseLButtonStatus.m_bPress = false;
	m_mouseLButtonStatus.m_bUp = false;

	m_SelectedColor = COLOR::BLACK;
	m_btnColorButtons[(int)COLOR::BLACK].SetColor(COLOR::RED);

	m_SelectedShape = SHAPE::QUADRANGLE;
	m_btnShapeButtons[(int)SHAPE::QUADRANGLE].SetColor(COLOR::RED);

	int y;
	for (int i = 0; i < SHAPE::COUNT_SHAPE; ++i)
	{
		y = BASEPOINT.y + Button::HEIGHT * i + MARGIN * i;
		m_btnShapeButtons[i].Init(m_hdc, { BASEPOINT.x,  y }, std::bind(&ShapeManager::SetShape, this, (SHAPE)i), ShapeToText((SHAPE)i));
	}

	for (int i = 0; i < COLOR::COUNT_COLOR; ++i)
	{
		y = BASEPOINT.y + Button::HEIGHT * i + MARGIN * i;
		m_btnColorButtons[i].Init(m_hdc, { BASEPOINT.x + Button::WIDTH + MARGIN, y }, std::bind(&ShapeManager::SetColor, this, (COLOR)i), ColorToText((COLOR)i));
	}
	DrawButtons();
}

ShapeManager::~ShapeManager()
{
	ReleaseDC(m_hWnd, m_hdc);
}

std::unique_ptr<Shape> ShapeManager::CreateShape(POINT _pt)
{
	std::unique_ptr<Shape> NewShape;
	switch (m_SelectedShape)
	{
	case SHAPE::QUADRANGLE:
		NewShape = std::make_unique<Qudrangle>(m_hdc, _pt, m_SelectedColor);
		break;
	case SHAPE::CIRCLE:
		NewShape = std::make_unique<Circle>(m_hdc, _pt, m_SelectedColor);
		break;
	case SHAPE::TRIANGLE:
		NewShape = std::make_unique<Triangle>(m_hdc, _pt, m_SelectedColor);
		break;
	}
	return std::move(NewShape);
}

void ShapeManager::Update()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(m_hWnd, &pt);

	KeyUpdate();

	// Click 발생
	if (m_mouseLButtonStatus.m_bDown == true)
	{
		// 버튼을 클릭 했을 경우
		if (CheckButtons(pt))
		{
			Draw();
			DrawButtons();
		}
		else
			m_curShape = CreateShape(pt);
	}

	if (m_curShape != nullptr)
	{
		if (m_mouseLButtonStatus.m_bUp == true)
		{
			m_vecShapes.push_back(std::move(m_curShape));
			Draw();
			DrawButtons();
		}
		if (m_mouseLButtonStatus.m_bPress == true)
		{
			if (*m_curShape != pt)
				InvalidateRect(m_hWnd, nullptr, true);
			Draw();
			m_curShape->SetRect(pt);
			m_curShape->DrawWithColor();
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
	// 이전에 그렸던 모양들
	for (const std::unique_ptr<Shape>& shapePtr: m_vecShapes)
	{
		shapePtr->DrawWithColor();
	}
}

void ShapeManager::DrawButtons()
{
	// 모양 선택 버튼
	for (int i = 0; i < SHAPE::COUNT_SHAPE; ++i)
		m_btnShapeButtons[i].DrawWithColor();

	// 색상 선택 버튼
	for (int i = 0; i < COLOR::COUNT_COLOR; ++i)
		m_btnColorButtons[i].DrawWithColor();
}

bool ShapeManager::CheckButtons(POINT _pt)
{
	// 모양 선택 버튼
	for (int i = 0; i < SHAPE::COUNT_SHAPE; ++i)
	{
		if (m_btnShapeButtons[i].isClicked(_pt))
		{
			m_btnShapeButtons[i].OnButtonClick();
			return true;
		}
	}

	// 색상 선택 버튼
	for (int i = 0; i < COLOR::COUNT_COLOR; ++i)
	{
		if (m_btnColorButtons[i].isClicked(_pt))
		{
			m_btnColorButtons[i].OnButtonClick();
			return true;
		}
	}

	return false;
}

void ShapeManager::SetShape(SHAPE _shape)
{
	m_btnShapeButtons[(int)m_SelectedShape].SetColor(COLOR::BLACK);
	m_SelectedShape = _shape;
	m_btnShapeButtons[(int)m_SelectedShape].SetColor(COLOR::RED);
}

void ShapeManager::SetColor(COLOR _color)
{
	m_btnColorButtons[(int)m_SelectedColor].SetColor(COLOR::BLACK);
	m_SelectedColor = _color;
	m_btnColorButtons[(int)m_SelectedColor].SetColor(COLOR::RED);
}

std::wstring ShapeManager::ShapeToText(SHAPE _shape)
{
	switch(_shape)
	{
	case SHAPE::QUADRANGLE:
		return L"Qudrangle";
	case SHAPE::CIRCLE:
		return L"Circle";
	case SHAPE::TRIANGLE:
		return L"Triangle";
	}
}

std::wstring ShapeManager::ColorToText(COLOR _color)
{
	switch (_color)
	{
	case COLOR::BLACK:
		return L"Black";
	case COLOR::RED:
		return L"Red";
	case COLOR::BLUE:
		return L"Blue";
	case COLOR::GREEN:
		return L"Green";
	case COLOR::WHITE:
		return L"White";
	}
}
