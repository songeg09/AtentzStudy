#include "pch.h"
#include "SceneManager.h"
#include "SiChuanShengScene.h"
#include "MineSweeperScene.h"
#include "MainScene.h"
#include "Core.h"

SceneManager::SceneManager() : m_arrScene{}
{
	m_eSceneType = SCENE_TYPE::END;
}
SceneManager::~SceneManager()
{
	for (int i = 0; i < SCENE_TYPE::END; i++)
	{
		if (m_arrScene[i] != nullptr)
		{
			m_arrScene[i]->Release();
			delete m_arrScene[i];
		}
	}
}
void SceneManager::Init()
{
	m_arrScene[SCENE_TYPE::SI_CHUAN_SHENG] = new SiChuanShengScene("사천성");
	m_arrScene[SCENE_TYPE::MINE_SWEEPER] = new MineSweeperScene("지뢰찾기");
	m_arrScene[SCENE_TYPE::MAIN] = new MainScene("메인");
	

	SceneChange(SCENE_TYPE::MAIN);
}

void SceneManager::Update()
{
	m_arrScene[m_eSceneType]->Update();
}

void SceneManager::Render(HDC _memDC)
{
	m_arrScene[m_eSceneType]->Render(_memDC);
}

void SceneManager::SceneChange(SCENE_TYPE _eSceneType)
{
	if (m_eSceneType != SCENE_TYPE::END && m_arrScene[m_eSceneType] != nullptr)
		m_arrScene[m_eSceneType]->Release();
	m_eSceneType = _eSceneType;
	m_arrScene[m_eSceneType]->Init();
	Core::GetInstance()->CreateBackDC();
}
