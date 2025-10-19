#pragma once
#include"SiChuanShengScene.h"
#include"MineSweeperScene.h"

enum SCENE_TYPE
{
	MAIN,
	SI_CHUAN_SHENG,
	MINE_SWEEPER,
	END,
};
class Scene;
class SceneManager
{
	SINGLETON(SceneManager)
private:
	Scene* m_arrScene[SCENE_TYPE::END];
	SCENE_TYPE m_eSceneType;
public:
	void Init();
	void Update();
	void Render(HDC _memDC);
	void SceneChange(SCENE_TYPE _eSceneType);
	SiChuanShengScene* GetSiChuanShengScene()
	{
		if (m_arrScene[SCENE_TYPE::SI_CHUAN_SHENG] == nullptr)
			return nullptr;
		SiChuanShengScene* scene = dynamic_cast<SiChuanShengScene*>(m_arrScene[SCENE_TYPE::SI_CHUAN_SHENG]);
		assert(scene != nullptr);
		return scene;
	}
	MineSweeperScene* GetMineSweeperScene()
	{
		if (m_arrScene[SCENE_TYPE::MINE_SWEEPER] == nullptr)
			return nullptr;
		MineSweeperScene* scene = dynamic_cast<MineSweeperScene*>(m_arrScene[SCENE_TYPE::MINE_SWEEPER]);
		assert(scene != nullptr);
		return scene;
	}
	Scene* GetCurScene() { return m_arrScene[m_eSceneType]; }
};

