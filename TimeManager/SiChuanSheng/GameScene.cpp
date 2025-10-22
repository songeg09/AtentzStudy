#include "pch.h"
#include "GameScene.h"
#include "Texture.h"
#include "Player.h"
#include "InputManager.h"

GameScene::GameScene(std::string _strName) : Scene(_strName)
{
	m_pBackGround = nullptr;
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	InputManager::GetInstance()->RegistKey(VK_SPACE);

	m_pBackGround = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::BACKGROUND);
	Scene::SetWindowSize(m_pBackGround->GetWidth(), m_pBackGround->GetHeight());

	Player* pPlayer = new Player;
	Vector2 vec2WindowSize = Scene::GetWindowSize();
	pPlayer->Init(ConstValue::vec2PlayerStartPosition);
	Scene::AddObject(pPlayer, OBJECT_GROUP::PLAYABLE);
}

void GameScene::Update()
{
	Scene::Update();
}

void GameScene::Render(HDC _memDC)
{
	BitBlt(_memDC, 0, 0, m_pBackGround->GetWidth(), m_pBackGround->GetHeight(),
		m_pBackGround->GetDC(), 0, 0, SRCCOPY);
	Scene::Render(_memDC);
}