#include "Core.h"
#include "Block.h"
#include "InputManager.h"
#include "PathManager.h"
#include "ResourceManager.h"
#include "Texture.h"


Core::Core()
{
	m_hDC = nullptr;
	m_hWnd = nullptr;
	m_WindowStartPosition = {};
	m_WindowSize = {};
	m_pBackGroundTexture = nullptr;
	m_hBackBoardBitMap = nullptr;
	m_hBackDC = nullptr;
}

Core::~Core()
{
	ReleaseDC(m_hWnd, m_hDC);
}

void Core::Init(HWND _hWnd)
{
	srand(time(NULL));
	m_hWnd = _hWnd;
	m_hDC = GetDC(m_hWnd);

	InputManager::GetInstance()->Init();
	PathManager::GetInstance()->Init();

	InputManager::GetInstance()->RegistKey(VK_LBUTTON);
	InputManager::GetInstance()->RegistKey(VK_RBUTTON);
	m_pBackGroundTexture = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::BACK_GROUND);
	m_WindowSize = Vector2{ m_pBackGroundTexture->GetWidth(),m_pBackGroundTexture->GetHeight() };
	m_WindowStartPosition = Vector2{ (GetSystemMetrics(SM_CXSCREEN) / 2) - (m_WindowSize.x / 2),
												(GetSystemMetrics(SM_CYSCREEN) / 2) - (m_WindowSize.y / 2) };
	SetWindowPos(m_hWnd, nullptr, m_WindowStartPosition.x, m_WindowStartPosition.y,
		m_WindowSize.x + 15, m_WindowSize.y + 60, SWP_SHOWWINDOW);

	m_hBackBoardBitMap = CreateCompatibleBitmap(m_hDC, m_WindowSize.x, m_WindowSize.y);
	m_hBackDC = CreateCompatibleDC(m_hDC);
	HBITMAP hOldBitMap = (HBITMAP)SelectObject(m_hBackDC, m_hBackBoardBitMap);
	DeleteObject(hOldBitMap);

	
	// Blocks ¼¼ÆÃ
	const int BLOCK_HEIGHT = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::BLOCK_CLOSE)->GetHeight();
	const int BLOCK_WIDTH = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::BLOCK_CLOSE)->GetHeight();
	
	int numOfBombs = 0;
	for (int  y= 0; y < BOARD_HEIGHT; ++y)
	{
		for (int x = 0; x < BOARD_WIDTH; ++x)
		{
			if (numOfBombs < NUM_OF_BOMBS)
			{
				m_blockBoard[y][x] = std::make_shared<Block>(true, Vector2(BOARD_START_X + x* BLOCK_WIDTH, BOARD_START_Y + y * BLOCK_HEIGHT));
				numOfBombs++;
			}
			else
				m_blockBoard[y][x] = std::make_shared<Block>(false, Vector2(BOARD_START_X + x * BLOCK_WIDTH, BOARD_START_Y + y * BLOCK_HEIGHT));
		}
	}

	m_GameState = GAMESTATE::PREGAME;
}

void Core::GameLoop()
{
	Update();
	Render();
}


void Core::UpdateBlocks()
{
	for (int  y = 0; y < BOARD_HEIGHT; ++y)
	{
		for (int x = 0; x < BOARD_WIDTH; ++x)
		{
			m_blockBoard[y][x]->Update(InputManager::GetInstance()->GetCursorPosition());
		}
	}
}

void Core::ChangeGameState(GAMESTATE _gameState)
{
	m_GameState = _gameState;
}

void Core::Shuffle()
{
	int x1, y1;
	int x2, y2;
	for (int i = 0; i < 480; ++i)
	{
		x1 = rand() % BOARD_WIDTH;
		y1 = rand() % BOARD_HEIGHT;

		x2 = rand() % BOARD_WIDTH;
		y2 = rand() % BOARD_HEIGHT;

		
		std::shared_ptr<Block> temp = m_blockBoard[y1][x1];
		m_blockBoard[y1][x1] = m_blockBoard[y2][x2];
		m_blockBoard[y2][x2] = temp;

		Vector2 tempVec2 = m_blockBoard[y1][x1]->GetPosition();
		m_blockBoard[y1][x1]->SetPosition(m_blockBoard[y2][x2]->GetPosition());
		m_blockBoard[y2][x2]->SetPosition(tempVec2);
	}
}

void Core::SetBlocks()
{
	for (int y = 0; y < BOARD_HEIGHT; ++y)
	{
		for (int x = 0; x < BOARD_WIDTH; ++x)
		{
			m_blockBoard[y][x]->Close();

			if (m_blockBoard[y][x]->IsBomb()) continue;
			m_blockBoard[y][x]->SetupBlock(GetAdjBombs(Vector2(x,y)));
		}
	}
}

int Core::GetAdjBombs(Vector2 _pos)
{
	int Result = 0;
	
	Vector2 AdjPos;
	for (const Vector2& Dir : Directions8)
	{
		AdjPos = _pos + Dir;
		if (PositionOutOfBounds(AdjPos)) continue;
		if (m_blockBoard[AdjPos.y][AdjPos.x]->IsBomb())
			Result++;
	}

	return Result;
}

bool Core::PositionOutOfBounds(const Vector2& _pos)
{
	return !(0 <= _pos.x && _pos.x < BOARD_WIDTH && 0 <= _pos.y && _pos.y < BOARD_HEIGHT);
}

void Core::Update()
{
	switch (m_GameState)
	{
	case GAMESTATE::PREGAME:
		Shuffle();
		SetBlocks();
		ChangeGameState(GAMESTATE::PLAY);
		break;
	case GAMESTATE::PLAY:
		InputManager::GetInstance()->Update();
		UpdateBlocks();
		break;
	case GAMESTATE::WIN:
		break;
	case GAMESTATE::LOSE:
		break;
	}

}

void Core::Render()
{
	BitBlt(m_hBackDC, 0, 0, m_pBackGroundTexture->GetWidth(), m_pBackGroundTexture->GetHeight(), m_pBackGroundTexture->GetDC(), 0, 0, SRCCOPY);
	
	for (int y = 0; y < BOARD_HEIGHT; ++y)
	{
		for (int x = 0; x < BOARD_WIDTH; ++x)
		{
			m_blockBoard[y][x]->Render(m_hBackDC);
		}
	}

	BitBlt(m_hDC, 0, 0, m_WindowSize.x, m_WindowSize.y, m_hBackDC, 0, 0, SRCCOPY);
}
