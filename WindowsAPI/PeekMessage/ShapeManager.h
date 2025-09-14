#pragma once
#include <list>
#include <memory>
#include "Shape.h"
#include "Button.h"

enum SHAPE
{
	QUADRANGLE = 0,
	CIRCLE,
	TRIANGLE,
	COUNT_SHAPE
};

struct KeyStatus
{
	bool m_bDown;
	bool m_bPress;
	bool m_bUp;
};

class ShapeManager
{
private:
	static constexpr POINT BASEPOINT = { 1300, 100 };
	static constexpr int MARGIN = 10;

	std::list<std::unique_ptr<Shape>> m_vecShapes;
	HWND m_hWnd;
	HDC m_hdc;
	KeyStatus m_mouseLButtonStatus;

	Button m_btnShapeButtons[SHAPE::COUNT_SHAPE];
	Button m_btnColorButtons[COLOR::COUNT_COLOR];

	std::unique_ptr<Shape> m_curShape;
	COLOR m_SelectedColor;
	SHAPE m_SelectedShape;

	std::unique_ptr<Shape> CreateShape(POINT _pt);

public:
	ShapeManager(HWND _hWnd);
	~ShapeManager();
	void Update();
	void KeyUpdate();
	void Draw();
	void DrawButtons();
	bool CheckButtons(POINT _pt);

	void SetShape(SHAPE _shape);
	void SetColor(COLOR _color);

	std::wstring ShapeToText(SHAPE _shape);
	std::wstring ColorToText(COLOR _color);
};

