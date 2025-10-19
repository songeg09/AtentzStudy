#pragma once
#include"ResourceManager.h"
#include"Block.h"

class Core
{
	SINGLETON(Core)
private:
	HWND		m_hWnd;
	HDC			m_hDC;
	HBITMAP		m_hBackBoardBitmap;
	HDC			m_hBackDC;
public:
	void Init(HWND _hWnd);
	void GameLoop();
	HWND GethWnd() { return m_hWnd; }
	HDC GetMainDC() { return m_hDC; }
	void CreateBackDC();
private:
	void Update();
	void Render();
};

