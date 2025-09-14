#pragma once
#include <functional>
#include "Shape.h"
#include <string>

class Button : public Shape
{
private:
	std::function<void()> m_callBackFunc;
	std::wstring m_strText;

public:
	static constexpr int WIDTH = 300;
	static constexpr int HEIGHT = 100;

	Button();
	~Button();
	void Init(HDC _hdc, POINT _pt, std::function<void()> _callBackFunc, std::wstring _Text);
	void OnButtonClick();
	bool isClicked(POINT pt);
	void Draw() override;
};