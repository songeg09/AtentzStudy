#include "pch.h"
#include "SiChuanShengScene.h"
#include "Core.h"
#include"InputManager.h"
#include "Load.h"
#include"Texture.h"
#include"SceneManager.h"

SiChuanShengScene::SiChuanShengScene(std::string _strName) : Scene(_strName), m_Board{}
{
	m_iOldClock = -1;
	m_bLoadPrintStatus = false;
	m_pFirstBlock = nullptr;
}

SiChuanShengScene::~SiChuanShengScene()
{
	BoardRelease();
}

void SiChuanShengScene::Reset()
{
	BoardSet();

	m_TimerUI.Init();
	m_iScore = 0;
	m_iShuffleCount = SHUFFLE_MAX;
}

void SiChuanShengScene::Init()
{
	m_arrObjects.resize(OBJECT_GROUP::END);
	m_pBackBoard = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::BACK_BOARD);
	Scene::SetWindowSize(m_pBackBoard->GetWidth() + 16, m_pBackBoard->GetHeight() + 60);
	BoardSet();
	m_iScore = 0;
	m_iShuffleCount = SHUFFLE_MAX;
	m_TimerUI.Init();
}

void SiChuanShengScene::Release()
{
	BoardRelease();
	Scene::Release();
}

void SiChuanShengScene::Update()
{
	if(InputManager::GetInstance()->GetKeyState(VK_ESCAPE) == KEY_STATE::DOWN)
		SceneManager::GetInstance()->SceneChange(SCENE_TYPE::MAIN);
	if (m_bLoadPrintStatus == true)
	{
		if (clock() - m_iOldClock >= 1000)
		{
			m_Board[m_pFirstBlock->GetBoardPosition().m_iy][m_pFirstBlock->GetBoardPosition().m_ix] = nullptr;
			delete m_pFirstBlock;
			m_pFirstBlock = nullptr;
			m_Board[m_pSecondBlock->GetBoardPosition().m_iy][m_pSecondBlock->GetBoardPosition().m_ix] = nullptr;
			delete m_pSecondBlock;
			m_pSecondBlock = nullptr;
			ReleaseLoad();
			m_bLoadPrintStatus = false;
			m_TimerUI.TimeUp();
			m_iScore += 10;
			if (WinCheck() == true)
			{
				if (MessageBox(Core::GetInstance()->GethWnd(), "다시 하시겠습니까?", "GameWin!!", MB_OKCANCEL) == IDOK)
				{
					Reset();
				}
				else
					SceneManager::GetInstance()->SceneChange(SCENE_TYPE::MAIN);
			}
		}
	}
	else
	{

		for (int y = 0; y < HEIGHT; y++)
		{
			for (int x = 0; x < WIDTH; x++)
			{
				if (m_Board[y][x] != nullptr)
					m_Board[y][x]->Update();
			}
		}
		if (m_iShuffleCount > 0 && InputManager::GetInstance()->GetKeyState(VK_RBUTTON) == KEY_STATE::DOWN)
		{
			m_iShuffleCount -= 1;
			BoardShuffle();
		}
		m_TimerUI.Update();
		if (m_TimerUI.TimeCheck() == false)
		{
			if (MessageBox(Core::GetInstance()->GethWnd(), "다시 하시겠습니까?", "GameOver", MB_OKCANCEL) == IDOK)
			{
				Reset();
			}
			else
				SceneManager::GetInstance()->SceneChange(SCENE_TYPE::MAIN);
		}
	}
	Scene::Update();
}

void SiChuanShengScene::Render(HDC _memDC)
{
	BitBlt(_memDC, 0, 0, m_pBackBoard->GetWidth(), m_pBackBoard->GetHeight(), m_pBackBoard->GetDC(), 0, 0, SRCCOPY);
	for (int y = 0; y < BOARD_SIZE::HEIGHT; y++)
	{
		for (int x = BOARD_SIZE::WIDTH - 1; x >= 0; x--)
		{
			if (m_Board[y][x] != nullptr)
				m_Board[y][x]->Render(_memDC);
		}
	}
	m_TimerUI.Render(_memDC);
	std::string message = std::to_string(m_iScore);
	SetTextAlign(_memDC, TA_CENTER);
	TextOut(_memDC, 573, 23, message.c_str(), message.length());
	message = std::to_string(m_iShuffleCount);
	TextOut(_memDC, 612, 530, message.c_str(), message.length());
	Scene::Render(_memDC);
}

void SiChuanShengScene::CreateLoad()
{
	for (auto iter = m_listPositionList.begin(); iter != m_listPositionList.end(); iter++)
	{
		Node node = *iter;

		TEXTURE_TYPE eDirectionTextureType = TEXTURE_TYPE::LINE_1;
		if (node.m_eNextDirection == Node::DIRECTION::END || node.m_ePrevDirection == Node::DIRECTION::END)
			continue;

		switch (node.m_eNextDirection)
		{
		case Node::DIRECTION::LEFT:
			if (node.m_ePrevDirection == node.m_eNextDirection)
				eDirectionTextureType = TEXTURE_TYPE::LINE_1;
			else if (node.m_ePrevDirection == Node::DIRECTION::UP)
				eDirectionTextureType = TEXTURE_TYPE::LINE_5;
			else if (node.m_ePrevDirection == Node::DIRECTION::DOWN)
				eDirectionTextureType = TEXTURE_TYPE::LINE_6;
			break;
		case Node::DIRECTION::DOWN:
			if (node.m_ePrevDirection == node.m_eNextDirection)
				eDirectionTextureType = TEXTURE_TYPE::LINE_2;
			else if (node.m_ePrevDirection == Node::DIRECTION::LEFT)
				eDirectionTextureType = TEXTURE_TYPE::LINE_4;
			else if (node.m_ePrevDirection == Node::DIRECTION::RIGHT)
				eDirectionTextureType = TEXTURE_TYPE::LINE_5;
			break;
		case Node::DIRECTION::RIGHT:
			if (node.m_ePrevDirection == node.m_eNextDirection)
				eDirectionTextureType = TEXTURE_TYPE::LINE_1;
			else if (node.m_ePrevDirection == Node::DIRECTION::UP)
				eDirectionTextureType = TEXTURE_TYPE::LINE_4;
			else if (node.m_ePrevDirection == Node::DIRECTION::DOWN)
				eDirectionTextureType = TEXTURE_TYPE::LINE_3;
			break;
		case Node::DIRECTION::UP:
			if (node.m_ePrevDirection == node.m_eNextDirection)
				eDirectionTextureType = TEXTURE_TYPE::LINE_2;
			else if (node.m_ePrevDirection == Node::DIRECTION::LEFT)
				eDirectionTextureType = TEXTURE_TYPE::LINE_3;
			else if (node.m_ePrevDirection == Node::DIRECTION::RIGHT)
				eDirectionTextureType = TEXTURE_TYPE::LINE_6;
			break;
		}
		Load* load = new Load;
		load->Init(Vector2{ node.m_CurPosition.m_ix, node.m_CurPosition.m_iy }, eDirectionTextureType);
		AddObject(load, OBJECT_GROUP::LOAD);
	}
}

void SiChuanShengScene::ReleaseLoad()
{
	for (int i = 0; i < m_arrObjects[OBJECT_GROUP::LOAD].size(); i++)
	{
		delete m_arrObjects[OBJECT_GROUP::LOAD][i];
	}
	m_arrObjects[OBJECT_GROUP::LOAD].clear();
}

void SiChuanShengScene::CompareBlock(Block* _pBlock)
{
	if (m_pFirstBlock == nullptr)
	{
		_pBlock->Select();
		m_pFirstBlock = _pBlock;
	}
	else
	{
		if (m_pFirstBlock == _pBlock)
		{
			m_pFirstBlock->Cancle();
			m_pFirstBlock = nullptr;
			return;
		}
		m_pSecondBlock = _pBlock;
		m_pFirstBlock->Cancle();
		if (*m_pSecondBlock == *m_pFirstBlock)
		{
			Vector2 vec2FirstPosition = m_pFirstBlock->GetBoardPosition();
			Vector2 vec2SecondPosition = m_pSecondBlock->GetBoardPosition();
			if (FindLoad(vec2FirstPosition, vec2SecondPosition) == true)
			{
				m_pFirstBlock->Select();
				m_pSecondBlock->Select();
				m_iOldClock = clock();
				CreateLoad();
				m_bLoadPrintStatus = true;
				return;
			}
		}
		m_pFirstBlock->Cancle();
		_pBlock->Select();
		m_pFirstBlock = _pBlock;
	}
}

bool SiChuanShengScene::FindLoad(Vector2 _vec2Start, Vector2 _vec2End)
{
	std::vector<std::vector<int>> vecMapBestCost(BOARD_SIZE::HEIGHT, std::vector<int>(BOARD_SIZE::WIDTH, INT32_MAX));

	std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pQueue;

	std::map<Node, Node> mapBestParent;

	Node CurNode = Node{ _vec2Start.GetDistance(_vec2End),0,_vec2Start,Node::DIRECTION::END,Node::DIRECTION::END,0 };
	pQueue.push(CurNode);
	vecMapBestCost[CurNode.m_CurPosition.m_iy][CurNode.m_CurPosition.m_ix] = CurNode.m_iF;
	mapBestParent[CurNode] = CurNode;

	Node::DIRECTION eDirectionArray[Node::DIRECTION::END] = {
		Node::DIRECTION::LEFT,
		Node::DIRECTION::UP,
		Node::DIRECTION::RIGHT,
		Node::DIRECTION::DOWN,
	};

	while (pQueue.empty() == false)
	{
		CurNode = pQueue.top();
		pQueue.pop();

		if (vecMapBestCost[CurNode.m_CurPosition.m_iy][CurNode.m_CurPosition.m_ix] < CurNode.m_iF)
			continue;

		if (CurNode.m_CurPosition == _vec2End)
			break;

		for (Node::DIRECTION eDirection : eDirectionArray)
		{
			Node NextNode;
			NextNode.m_eNextDirection = Node::DIRECTION::END;
			NextNode.m_ePrevDirection = CurNode.m_eNextDirection = eDirection;
			if (CurNode.m_ePrevDirection != Node::DIRECTION::END && NextNode.m_ePrevDirection != CurNode.m_ePrevDirection)
			{
				if (CurNode.m_iRotateCount >= 2)
					continue;
				NextNode.m_iRotateCount = CurNode.m_iRotateCount + 1;
			}
			else
				NextNode.m_iRotateCount = CurNode.m_iRotateCount;

			NextNode.m_CurPosition = CurNode.m_CurPosition + GetFrontPosition(CurNode.m_eNextDirection);

			if (NextNode.m_CurPosition != _vec2End && CheckLoad(NextNode.m_CurPosition) == false)
				continue;
			NextNode.m_iG = CurNode.m_iG + 1;
			NextNode.m_iF = NextNode.m_iG + NextNode.m_CurPosition.GetDistance(_vec2End);
			if (vecMapBestCost[NextNode.m_CurPosition.m_iy][NextNode.m_CurPosition.m_ix] <= NextNode.m_iF)
				continue;

			pQueue.push(NextNode);
			vecMapBestCost[NextNode.m_CurPosition.m_iy][NextNode.m_CurPosition.m_ix] = NextNode.m_iF;
			mapBestParent[NextNode] = CurNode;
		}
	}

	m_listPositionList.clear();

	Node Cur;
	Cur.m_CurPosition = _vec2End;
	if (mapBestParent.find(Cur) == mapBestParent.end())
		return false;

	CurNode = mapBestParent.find(Cur)->first;
	while (true)
	{
		m_listPositionList.push_back(CurNode);
		if (CurNode.m_CurPosition == _vec2Start)
			break;
		CurNode = mapBestParent[CurNode];
	}
	return true;
}

bool SiChuanShengScene::CheckLoad(Vector2 _vec2Position)
{
	if (_vec2Position.m_ix < 0 || _vec2Position.m_ix >= BOARD_SIZE::WIDTH)
		return false;
	if (_vec2Position.m_iy < 0 || _vec2Position.m_iy >= BOARD_SIZE::HEIGHT)
		return false;
	if (m_Board[_vec2Position.m_iy][_vec2Position.m_ix] != nullptr)
		return false;
	return true;
}

Vector2 SiChuanShengScene::GetFrontPosition(Node::DIRECTION _eDirection)
{
	switch (_eDirection)
	{
	case Node::DIRECTION::LEFT:		return Vector2{ -1,0 };
	case Node::DIRECTION::DOWN:	return Vector2{ 0,1 };
	case Node::DIRECTION::RIGHT:		return Vector2{ 1,0 };
	case Node::DIRECTION::UP:			return Vector2{ 0,-1 };
	default:							return Vector2{ 0,0 };
	}
}

void SiChuanShengScene::BoardRelease()
{
	for (int y = 0; y < BOARD_SIZE::HEIGHT; y++)
	{
		for (int x = 0; x < BOARD_SIZE::WIDTH; x++)
		{
			if (m_Board[y][x] != nullptr)
			{
				delete m_Board[y][x];
				m_Board[y][x] = nullptr;
			}
		}
	}
}
void SiChuanShengScene::BoardSet()
{
	BoardRelease();
	int iTextureIndex = (int)TEXTURE_TYPE::CARD_START;
	bool bLoop = false;
	for (int y = 0; y < BOARD_SIZE::HEIGHT; y++)
	{
		for (int x = 0; x < BOARD_SIZE::WIDTH; x++)
		{
			if (x == 0 || x == BOARD_SIZE::WIDTH - 1 || y == 0 || y == BOARD_SIZE::HEIGHT - 1)
				m_Board[y][x] = nullptr;
			else if (iTextureIndex == (int)TEXTURE_TYPE::CARD_END)
				m_Board[y][x] = nullptr;
			else
			{
				m_Board[y][x] = new Block();
				m_Board[y][x]->Init(Vector2{ x,y }, (TEXTURE_TYPE)iTextureIndex);
				++iTextureIndex;
				if (bLoop == false && iTextureIndex == (int)TEXTURE_TYPE::CARD_END)
				{
					bLoop = true;
					iTextureIndex = (int)TEXTURE_TYPE::CARD_START;
				}
			}
		}
	}
	BoardShuffle();
	m_pFirstBlock = nullptr;
}


bool SiChuanShengScene::WinCheck()
{
	for (int y = 0; y < BOARD_SIZE::HEIGHT; y++)
	{
		for (int x = 0; x < BOARD_SIZE::WIDTH; x++)
		{
			if (m_Board[y][x] != nullptr)
				return false;
		}
	}
	return true;
}
void SiChuanShengScene::BoardShuffle()
{
	for (int i = 0; i < 3000; i++)
	{
		int index1_x = (rand() % (BOARD_SIZE::WIDTH - 2)) + 1;
		int index1_y = (rand() % (BOARD_SIZE::HEIGHT - 2)) + 1;
		int index2_x = (rand() % (BOARD_SIZE::WIDTH - 2)) + 1;
		int index2_y = (rand() % (BOARD_SIZE::HEIGHT - 2)) + 1;
		Block* block = m_Board[index1_y][index1_x];
		m_Board[index1_y][index1_x] = m_Board[index2_y][index2_x];
		m_Board[index2_y][index2_x] = block;
	}
	for (int y = 1; y < BOARD_SIZE::HEIGHT - 1; y++)
	{
		for (int x = 1; x < BOARD_SIZE::WIDTH - 1; x++)
		{
			if (m_Board[y][x] != nullptr)
				m_Board[y][x]->SetPosition(Vector2{ x, y });
		}
	}
}