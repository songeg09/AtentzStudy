#include "pch.h"
#include "Core.h"
#include "InputManager.h"
#include "PathManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"

Core::Core()
{
	m_hBackBoardBitmap = nullptr;
	m_hBackDC = nullptr;
	m_hDC = nullptr;
	m_hWnd = nullptr;
}
Core::~Core()
{
	if (m_hBackBoardBitmap != nullptr)
		DeleteObject(m_hBackBoardBitmap);
	if (m_hBackDC != nullptr)
		DeleteDC(m_hBackDC);
	if (m_hWnd != nullptr && m_hDC != nullptr)
		ReleaseDC(m_hWnd,m_hDC);
}
void Core::Init(HWND _hWnd)
{
	srand(time(NULL));

	m_hWnd = _hWnd;
	m_hDC = GetDC(m_hWnd);
	InputManager::GetInstance()->Init();
	InputManager::GetInstance()->RegistKey(VK_LBUTTON);
	InputManager::GetInstance()->RegistKey(VK_RBUTTON);
	InputManager::GetInstance()->RegistKey(VK_ESCAPE);

	PathManager::GetInstance()->Init();

	SceneManager::GetInstance()->Init();

	CreateBackDC();
}

void Core::GameLoop()
{
	Update();
	Render();
}

void Core::CreateBackDC()
{
	if (m_hBackBoardBitmap != nullptr)
		DeleteObject(m_hBackBoardBitmap);
	if (m_hBackDC != nullptr)
		DeleteDC(m_hBackDC);
	Vector2 WindowSize = SceneManager::GetInstance()->GetCurScene()->GetWindowSize();
	m_hBackBoardBitmap = CreateCompatibleBitmap(m_hDC, WindowSize.m_ix, WindowSize.m_iy);
	m_hBackDC = CreateCompatibleDC(m_hDC);
	HBITMAP hOldBitMap = (HBITMAP)SelectObject(m_hBackDC, m_hBackBoardBitmap);
	DeleteObject(hOldBitMap);
}

void Core::Update()
{
	InputManager::GetInstance()->Update();
	SceneManager::GetInstance()->Update();
}

void Core::Render()
{
	Vector2 WindowSize = SceneManager::GetInstance()->GetCurScene()->GetWindowSize();
	SceneManager::GetInstance()->GetCurScene()->Render(m_hBackDC);
	BitBlt(m_hDC, 0, 0, WindowSize.m_ix, WindowSize.m_iy, m_hBackDC, 0, 0, SRCCOPY);
}
