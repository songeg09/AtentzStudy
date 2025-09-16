#pragma once
#include <functional>
#include <string>
#include "framework.h"
#include "Mecro.h"

class Button
{
private:
	HDC m_hdc;
	RECT m_rect;
	bool m_bActivate;
	std::function<void()> m_callBackFunc;
	std::wstring m_strText;

public:
	static constexpr int WIDTH = 300;
	static constexpr int HEIGHT = 100;

	Button();
	~Button();
	void Init(HDC _hdc, POINT _pt, std::function<void()> _callBackFunc, std::wstring _Text);
	void SetActivate();
	void Draw();
	bool IsClicked(POINT pt);
};