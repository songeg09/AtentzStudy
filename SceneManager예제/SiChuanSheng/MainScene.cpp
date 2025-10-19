#include "pch.h"
#include "MainScene.h"
#include "SceneManager.h"
#include "Button.h"

MainScene::MainScene(std::string _strName) : Scene(_strName)
{
}

MainScene::~MainScene()
{
}

void MainScene::Init()
{
	m_arrObjects.resize(OBJECT_GROUP::END);
	Scene::SetWindowSize(WINDOW_SIZE::WIDTH, WINDOW_SIZE::HEIGHT);
	Button* button = new Button;
	button->Init(Vector2{ 100,100 }, TEXTURE_TYPE::SICHUANSHENG_BUTTON,std::bind(&MainScene::StartSiChuanSheng,this));
	Scene::AddObject(button,OBJECT_GROUP::BUTTON);
	Button* button2 = new Button;
	button2->Init(Vector2{ 500,100 }, TEXTURE_TYPE::MINESWEEPER_BUTTON);
	Scene::AddObject(button2, OBJECT_GROUP::BUTTON);
}

void MainScene::StartSiChuanSheng()
{
	SceneManager::GetInstance()->SceneChange(SCENE_TYPE::SI_CHUAN_SHENG);
}

void MainScene::StartMineSweeper()
{
	SceneManager::GetInstance()->SceneChange(SCENE_TYPE::MINE_SWEEPER);
}
