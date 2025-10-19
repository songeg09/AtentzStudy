#include "pch.h"
#include "MineSweeperScene.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Mine.h"

MineSweeperScene::MineSweeperScene(std::string _strName)
	: Scene(_strName), m_Board{}
{
	m_pBackBoard = nullptr;
	m_GameState = GAMESTATE::PREGAME;
	m_iNumOfFlags = NUM_OF_BOMBS;
}

void MineSweeperScene::Init()
{
	m_arrObjects.resize(OBJECT_GROUP::END);
	m_pBackBoard = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::BACK);
	Scene::SetWindowSize(m_pBackBoard->GetWidth() + 16, m_pBackBoard->GetHeight() + 60);
	InitBoard();
}

void MineSweeperScene::InitBoard()
{
	ReleaseBoard();
	int numOfBombs = 0;
	for (int y = 0; y < BOARD_HEIGHT; ++y)
	{
		for (int x = 0; x < BOARD_WIDTH; ++x)
		{
			if (numOfBombs < NUM_OF_BOMBS)
			{
				m_Board[y][x] = new Mine(true);
				m_Board[y][x]->Init(Vector2(x,y), TEXTURE_TYPE::MINE);
				numOfBombs++;
			}
			else
			{
				m_Board[y][x] = new Mine(false);
				m_Board[y][x]->Init(Vector2(x, y), TEXTURE_TYPE::BLOCK_0);
			}
		}
	}
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


		Mine* temp = m_Board[y1][x1];
		m_Board[y1][x1] = m_Board[y2][x2];
		m_Board[y2][x2] = temp;

		Vector2 tempVec2 = m_Board[y1][x1]->GetPosition();
		m_Board[y1][x1]->SetPosition(m_Board[y2][x2]->GetPosition());
		m_Board[y2][x2]->SetPosition(tempVec2);
	}
}

void MineSweeperScene::ReleaseBoard()
{
	for (int y = 0; y < BOARD_HEIGHT; y++)
	{
		for (int x = 0; x < BOARD_WIDTH; x++)
		{
			if (m_Board[y][x] != nullptr)
			{
				delete m_Board[y][x];
				m_Board[y][x] = nullptr;
			}
		}
	}
}