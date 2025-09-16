#include "ShapeManager.h"
#include "Qudrangle.h"
#include "Circle.h"
#include "Triangle.h"
#include <functional>
#include <math.h>


ShapeManager::ShapeManager(HWND _hWnd)
{
	m_hWnd = _hWnd;
	m_hdc = GetDC(m_hWnd);

	m_mouseLButtonStatus.m_bDown = false;
	m_mouseLButtonStatus.m_bPress = false;
	m_mouseLButtonStatus.m_bUp = false;

	m_SelectedColor = COLOR::BLACK;
	m_btnColorButtons[(int)COLOR::BLACK].SetActivate();

	m_SelectedShape = SHAPE::QUADRANGLE;
	m_btnShapeButtons[(int)SHAPE::QUADRANGLE].SetActivate();

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
	static POINT down_pt;
	static bool bDragging = false;
	
	POINT pt;

	GetCursorPos(&pt);
	ScreenToClient(m_hWnd, &pt);

	KeyUpdate();

	if (m_mouseLButtonStatus.m_bDown == true)
		down_pt = pt;

	if (m_mouseLButtonStatus.m_bPress == true)
	{
		if (bDragging)
		{
			if (m_curShape == nullptr)
				m_curShape = CreateShape(pt);
			else if (*m_curShape != pt)
				InvalidateRect(m_hWnd, nullptr, true);
			Draw();
			m_curShape->SetRect(pt);
			m_curShape->DrawWithColor();
		}
		else
		{
			double dCursorMove = Dist(down_pt, pt);
			if (dCursorMove > 5)
				bDragging = true;
		}
	}

	if (m_mouseLButtonStatus.m_bUp == true)
	{
		if (bDragging)
		{
			m_vecShapes.push_back(std::move(m_curShape));
			Draw();
			DrawButtons();
			bDragging = false;
		}
		else
		{
			if(CheckButtons(pt))
				DrawButtons();
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
		m_btnShapeButtons[i].Draw();

	// 색상 선택 버튼
	for (int i = 0; i < COLOR::COUNT_COLOR; ++i)
		m_btnColorButtons[i].Draw();
}

double ShapeManager::Dist(POINT prev_pt, POINT cur_pt)
{
	double dist = sqrt((prev_pt.x - cur_pt.x) * (prev_pt.x - cur_pt.x) + (prev_pt.y - cur_pt.y) * (prev_pt.y - cur_pt.y));
	return dist; // 5 pixel 미만인 경우 클릭으로 간주
}

bool ShapeManager::CheckButtons(POINT _pt)
{
	// 모양 선택 버튼
	for (int i = 0; i < SHAPE::COUNT_SHAPE; ++i)
	{
		if (m_btnShapeButtons[i].IsClicked(_pt))
			return true;
	}

	// 색상 선택 버튼
	for (int i = 0; i < COLOR::COUNT_COLOR; ++i)
	{
		if (m_btnColorButtons[i].IsClicked(_pt))
			return true;
	}

	return false;
}

void ShapeManager::SetShape(SHAPE _shape)
{
	m_btnShapeButtons[(int)m_SelectedShape].SetActivate();
	m_SelectedShape = _shape;
	m_btnShapeButtons[(int)m_SelectedShape].SetActivate();
}

void ShapeManager::SetColor(COLOR _color)
{
	m_btnColorButtons[(int)m_SelectedColor].SetActivate();
	m_SelectedColor = _color;
	m_btnColorButtons[(int)m_SelectedColor].SetActivate();
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
