#include "pch.h"
#include "MineSweeperScene.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Mine.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Core.h"

MineSweeperScene::MineSweeperScene(std::string _strName)
	: Scene(_strName),
	m_pBackBoard(nullptr),
	m_GameState(GAMESTATE::PREGAME),
	m_iNumOfFlags(NUM_OF_BOMBS)
{

}

MineSweeperScene::~MineSweeperScene()
{
}

void MineSweeperScene::Init()
{
	m_arrObjects.resize(OBJECT_GROUP::END);
	m_pBackBoard = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::BACK);
	Scene::SetWindowSize(m_pBackBoard->GetWidth() + 16, m_pBackBoard->GetHeight() + 60);
	InitBoard();
	m_GameState = GAMESTATE::PREGAME;
	m_iNumOfFlags = NUM_OF_BOMBS;
}

void MineSweeperScene::InitBoard()
{
	Scene::Release();
	int numOfBombs = 0;
	for (int y = 0; y < BOARD_HEIGHT; ++y)
	{
		for (int x = 0; x < BOARD_WIDTH; ++x)
		{
			if (numOfBombs < NUM_OF_BOMBS)
			{
				m_Board[y][x] = new Mine(
					true, 
					std::bind(&MineSweeperScene::HandleLeftClick, this, std::placeholders::_1),
					std::bind(&MineSweeperScene::HandleRightClick, this, std::placeholders::_1)
				);
				m_Board[y][x]->Init(Vector2(x,y), TEXTURE_TYPE::MINE);
				Scene::AddObject(m_Board[y][x], OBJECT_GROUP::MINE);
				numOfBombs++;
			}
			else
			{
				m_Board[y][x] = new Mine(
					false, 
					std::bind(&MineSweeperScene::HandleLeftClick, this, std::placeholders::_1),
					std::bind(&MineSweeperScene::HandleRightClick, this, std::placeholders::_1)
				);
				m_Board[y][x]->Init(Vector2(x, y), TEXTURE_TYPE::BLOCK_0);
				Scene::AddObject(m_Board[y][x], OBJECT_GROUP::MINE);
			}
		}
	}
}

void MineSweeperScene::Update()
{
	switch (m_GameState)
	{
	case GAMESTATE::PREGAME:
		m_iNumOfFlags = NUM_OF_BOMBS;
		ShuffleBoard();
		SetTextures();
		m_GameState = GAMESTATE::PLAY;
		break;
	case GAMESTATE::PLAY:
		if (InputManager::GetInstance()->GetKeyState(VK_ESCAPE) == KEY_STATE::DOWN)
			SceneManager::GetInstance()->SceneChange(SCENE_TYPE::MAIN);
		Scene::Update();
		break;
	case GAMESTATE::WIN:
		if (MessageBox(Core::GetInstance()->GethWnd(), "Play Again?", "You Win!", MB_YESNO) == IDYES)
		{
			m_GameState = GAMESTATE::PREGAME;
			break;
		}
		else
		{
			SceneManager::GetInstance()->SceneChange(SCENE_TYPE::MAIN);
		}
		break;
	case GAMESTATE::LOSE:
		if (MessageBox(Core::GetInstance()->GethWnd(), "Play Again?", "You Lose!", MB_YESNO) == IDYES)
		{
			m_GameState = GAMESTATE::PREGAME;
			break;
		}
		else
		{
			SceneManager::GetInstance()->SceneChange(SCENE_TYPE::MAIN);
		}
		break;
	}
}

void MineSweeperScene::Render(HDC _memDC)
{
	BitBlt(_memDC, 0, 0, m_pBackBoard->GetWidth(), m_pBackBoard->GetHeight(), m_pBackBoard->GetDC(), 0, 0, SRCCOPY);
	std::string msg = std::to_string(m_iNumOfFlags);
	TextOut(_memDC, FLAGLEFT_START_X, FLAGLEFT_START_Y, msg.c_str(), msg.length());
	Scene::Render(_memDC);
}

void MineSweeperScene::ShuffleBoard()
{
	int x1, y1;
	int x2, y2;
	for (int i = 0; i < NUM_OF_BOMBS * 10; ++i)
	{
		x1 = rand() % BOARD_WIDTH;
		y1 = rand() % BOARD_HEIGHT;

		x2 = rand() % BOARD_WIDTH;
		y2 = rand() % BOARD_HEIGHT;


		m_Board[y1][x1]->SetPosition({ x2,y2 });
		m_Board[y2][x2]->SetPosition({ x1,y1 });

		Mine* temp = m_Board[y1][x1];
		m_Board[y1][x1] = m_Board[y2][x2];
		m_Board[y2][x2] = temp;
	}
}

void MineSweeperScene::SetTextures()
{
	for (int y = 0; y < BOARD_HEIGHT; ++y)
	{
		for (int x = 0; x < BOARD_WIDTH; ++x)
		{
			m_Board[y][x]->SetState(MINE_STATE::CLOSE);

			// ÆøÅºÀÏ °æ¿ì ClickArea¸¸ ¼öÁ¤
			if (m_Board[y][x]->IsMine() == false)
				m_Board[y][x]->SetTexture(GetAdjMines(Vector2(x, y)));
		}
	}
}

int MineSweeperScene::GetAdjMines(const Vector2 _pos)
{
	int Result = 0;

	Vector2 AdjPos;
	for (const Vector2& Dir : Directions)
	{
		AdjPos = _pos + Dir;
		if (PositionOutOfBounds(AdjPos)) continue;
		if (m_Board[AdjPos.m_iy][AdjPos.m_ix]->IsMine())
			Result++;
	}

	return Result;
}

bool MineSweeperScene::PositionOutOfBounds(const Vector2& _pos)
{
	return !(0 <= _pos.m_ix && _pos.m_ix < BOARD_WIDTH && 0 <= _pos.m_iy && _pos.m_iy < BOARD_HEIGHT);
}

void MineSweeperScene::RevealMines()
{
	for (int y = 0; y < BOARD_HEIGHT; ++y)
	{
		for (int x = 0; x < BOARD_WIDTH; ++x)
		{
			if (m_Board[y][x]->IsMine())
				m_Board[y][x]->SetState(MINE_STATE::OPEN);
		}
	}
}

void MineSweeperScene::RevealAdj(const Vector2 _vec2)
{
	static std::queue<Vector2> adjBlocks;

	m_Board[_vec2.m_iy][_vec2.m_ix]->SetState(MINE_STATE::OPEN);
	adjBlocks.push(_vec2);

	Vector2 Current, Next;
	while (!adjBlocks.empty())
	{
		Current = adjBlocks.front();
		adjBlocks.pop();

		if (m_Board[Current.m_iy][Current.m_ix]->GetAdjMines() > 0) continue;

		for (int d = 0; d < 8; d += 2)
		{
			Next = Current + Directions[d];

			if (PositionOutOfBounds(Next)) continue;
			if (m_Board[Next.m_iy][Next.m_ix]->GetState() == MINE_STATE::OPEN) continue;
			if (m_Board[Next.m_iy][Next.m_ix]->IsMine()) continue;

			if (m_Board[Next.m_iy][Next.m_ix]->GetState() == MINE_STATE::FLAGGED)
				m_iNumOfFlags++;
			m_Board[Next.m_iy][Next.m_ix]->SetState(MINE_STATE::OPEN);

			if (m_Board[Next.m_iy][Next.m_ix]->GetAdjMines() == 0)
				adjBlocks.push(Next);
		}
	}
}

bool MineSweeperScene::WinCheck()
{
	static constexpr int Target = (BOARD_WIDTH * BOARD_HEIGHT) - NUM_OF_BOMBS;

	int Opened = 0;
	for (int y = 0; y < BOARD_HEIGHT; ++y)
	{
		for (int x = 0; x < BOARD_WIDTH; ++x)
		{
			if (m_Board[y][x]->GetState() == MINE_STATE::OPEN)
				Opened++;
		}
	}

	return Opened == Target;
}

void MineSweeperScene::HandleLeftClick(const Vector2 _vec2)
{
	if (m_Board[_vec2.m_iy][_vec2.m_ix]->IsMine())
	{
		RevealMines();
		m_GameState = GAMESTATE::LOSE;
	}
	else
	{
		RevealAdj(_vec2);
		if (WinCheck())
			m_GameState = GAMESTATE::WIN;
	}
}

void MineSweeperScene::HandleRightClick(const Vector2 _vec2)
{
	if (m_Board[_vec2.m_iy][_vec2.m_ix]->GetState() == MINE_STATE::FLAGGED)
	{
		m_Board[_vec2.m_iy][_vec2.m_ix]->SetState(MINE_STATE::CLOSE);
		m_iNumOfFlags++;
	}
	else if (m_Board[_vec2.m_iy][_vec2.m_ix]->GetState() == MINE_STATE::CLOSE)
	{
		if (m_iNumOfFlags <= 0) return;
		m_Board[_vec2.m_iy][_vec2.m_ix]->SetState(MINE_STATE::FLAGGED);
		m_iNumOfFlags--;
	}
}


