#pragma once
#include <list>
#include <memory>
#include "Shape.h"

struct KeyStatus
{
	bool m_bDown;
	bool m_bPress;
	bool m_bUp;
};

class ShapeManager
{
private:
	std::list<std::unique_ptr<Shape>> m_vecShapes;
	HWND m_hWnd;
	HDC m_hdc;
	std::unique_ptr<Shape> m_curShape;
	KeyStatus m_mouseLButtonStatus;

public:
	ShapeManager(HWND _hWnd);
	~ShapeManager();
	void Update();
	void KeyUpdate();
	void Draw();

};

