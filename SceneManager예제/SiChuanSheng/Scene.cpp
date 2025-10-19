#include "pch.h"
#include "Scene.h"
#include"Object.h"
#include"Core.h"

Scene::Scene(std::string _strName)
{
	m_strName = _strName;
}

Scene::~Scene()
{
	Release();
}

void Scene::Release()
{
	for (int i = 0; i < m_arrObjects.size(); i++)
	{
		for (Object* object : m_arrObjects[i])
		{
			delete object;
		}
		m_arrObjects[i].clear();
	}
}

void Scene::SetWindowSize(int _iWidth, int _iHeight)
{
	Vector2 vec2ScreenStartPosition = { GetSystemMetrics(SM_CXSCREEN) / 2,GetSystemMetrics(SM_CYSCREEN) / 2 };
	m_vec2WindowCenterPosition = { _iWidth / 2 ,_iHeight / 2 };
	m_vec2WindowStartPosition = { vec2ScreenStartPosition.m_ix - (_iWidth / 2),
											  vec2ScreenStartPosition.m_iy - (_iHeight / 2) };
	m_vec2WindowSize = { _iWidth ,_iHeight };

	SetWindowPos(Core::GetInstance()->GethWnd(), nullptr, m_vec2WindowStartPosition.m_ix, m_vec2WindowStartPosition.m_iy,
		_iWidth, _iHeight, SWP_SHOWWINDOW);
}

void Scene::AddObject(Object* _object, unsigned int _eGroup)
{
	m_arrObjects[_eGroup].push_back(_object);
}

void Scene::Update()
{
	for (int i = 0; i < m_arrObjects.size(); i++)
	{
		for(int j =0 ; j < m_arrObjects[i].size() ; j++)
			m_arrObjects[i][j]->Update();
	}
}

void Scene::Render(HDC _memDC)
{
	for (int i = 0; i < m_arrObjects.size(); i++)
	{
		for (Object* object : m_arrObjects[i])
			object->Render(_memDC);
	}
}
