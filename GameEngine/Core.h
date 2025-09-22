#pragma once
#include "pch.h"
#include "Card.h"
class Card;
class Core
{
	SINGLETON(Core)
private:
	HWND	m_hWnd;
	Vector2 m_WindowSize;
	Vector2 m_ScreenCenterPosition;
	HDC		m_hDC;
	Card*	m_parrBoard[(int)BOARD_SIZE::HEIGHT][(int)BOARD_SIZE::WIDTH];
public:
	void Init(HWND _hWnd, Vector2 _size);
	void GameLoop();
	HWND GethWnd() { return m_hWnd; }
	HDC GetMainDC() { return m_hDC; }
	Vector2 GewWindowSize() { return m_WindowSize; }

private:
	POINT GetMousePosition();
	void Update();
	void Render();
};

