#include "pch.h"
#include "Core.h"
#include "Card.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "PathManager.h"

Core::Core()
{
	m_hDC = nullptr;
	m_hWnd = nullptr;
	m_ScreenCenterPosition = {};
	m_WindowSize = {};
}

Core::~Core()
{
	ReleaseDC(m_hWnd, m_hDC);
	for (int y = 0; y < (int)BOARD_SIZE::HEIGHT; ++y)
	{
		for (int x = 0; x < (int)BOARD_SIZE::WIDTH; ++x)
		{
			delete m_parrBoard[y][x];
		}
	}
}

void Core::Init(HWND _hWnd, Vector2 _size)
{
	m_hWnd = _hWnd;
	m_WindowSize = _size;

	m_ScreenCenterPosition = Vector2{ (GetSystemMetrics(SM_CXSCREEN) / 2) - (m_WindowSize.x / 2),
		(GetSystemMetrics(SM_CYSCREEN) / 2) - (m_WindowSize.y / 2) };

	SetWindowPos(m_hWnd, nullptr, m_ScreenCenterPosition.x, m_ScreenCenterPosition.y,
		m_WindowSize.x, m_WindowSize.y, SWP_SHOWWINDOW);
	m_hDC = GetDC(m_hWnd);

	Texture* parrTexture[(int)BOARD_SIZE::HEIGHT * (int)BOARD_SIZE::WIDTH];
	parrTexture[0] = ResourceManager::GetInstance()->LoadTexture(L"루피", L"luffy.bmp");
	parrTexture[1] = ResourceManager::GetInstance()->LoadTexture(L"조로", L"zoro.bmp");
	parrTexture[2] = ResourceManager::GetInstance()->LoadTexture(L"나미", L"nami.bmp");
	parrTexture[3] = ResourceManager::GetInstance()->LoadTexture(L"우솝", L"usopp.bmp");
	parrTexture[4] = ResourceManager::GetInstance()->LoadTexture(L"상디", L"sanji.bmp");
	parrTexture[5] = ResourceManager::GetInstance()->LoadTexture(L"니코로빈", L"nico_robin.bmp");
	parrTexture[6] = ResourceManager::GetInstance()->LoadTexture(L"비비", L"vivi.bmp");
	parrTexture[7] = ResourceManager::GetInstance()->LoadTexture(L"샹크스", L"shanks.bmp");
	parrTexture[8] = ResourceManager::GetInstance()->LoadTexture(L"에이스", L"ace.bmp");
	parrTexture[9] = ResourceManager::GetInstance()->LoadTexture(L"버기", L"buggy.bmp");
	parrTexture[10] = ResourceManager::GetInstance()->LoadTexture(L"골드로저", L"gold_roger.bmp");
	parrTexture[11] = ResourceManager::GetInstance()->LoadTexture(L"쵸파", L"chopper.bmp");

	int iTextureIndex = 0;
	for (int y = 0; y < (int)BOARD_SIZE::HEIGHT; ++y)
	{
		for (int x = 0; x < (int)BOARD_SIZE::WIDTH; ++x)
		{
			Card* card = new Card;
			Vector2 position;
			position.x = CARD_START_POSITION.x + (x * parrTexture[iTextureIndex]->GetWidth()) + (x * CARD_MARGIN.x);
			position.y = CARD_START_POSITION.y + (y * parrTexture[iTextureIndex]->GetHeight()) + (y * CARD_MARGIN.y);
			card->Init(position, parrTexture[iTextureIndex++]);
			m_parrBoard[y][x] = card;
		}
	}
}

void Core::GameLoop()
{
	Update();
	Render();
}

POINT Core::GetMousePosition()
{
	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(m_hWnd, &ptMouse);
	return ptMouse;
}

void Core::Update()
{
	for (int y = 0; y < (int)BOARD_SIZE::HEIGHT; ++y)
	{
		for (int x = 0; x < (int)BOARD_SIZE::WIDTH; ++x)
			m_parrBoard[y][x]->Update();
	}
}

void Core::Render()
{
	for (int y = 0; y < (int)BOARD_SIZE::HEIGHT; ++y)
	{
		for (int x = 0; x < (int)BOARD_SIZE::WIDTH; ++x)
			m_parrBoard[y][x]->Render(m_hDC);
	}
}