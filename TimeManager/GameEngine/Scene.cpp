#include "pch.h"
#include "Scene.h"
#include "Object.h"
#include "Core.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "Collider.h"

Scene::Scene(std::wstring _strName)
{
	m_strName = _strName;
}

Scene::~Scene()
{
	Release();
}

void Scene::Release()
{
	for (int i = 0; i < static_cast<int>(OBJECT_GROUP::END); i++)
	{
		for (Object* object : m_arrObjects[i])
		{
			delete object;
		}
		m_arrObjects[i].clear();
	}
	CollisionManager::GetInstance()->ReleaseColliderGroup();
}

void Scene::SetWindowSize(int _iWidth, int _iHeight)
{
	Vector2 vec2ScreenStartPosition = { GetSystemMetrics(SM_CXSCREEN) / 2.0f,GetSystemMetrics(SM_CYSCREEN) / 2.0f };
	m_vec2WindowCenterPosition = { _iWidth / 2.0f ,_iHeight / 2.0f };
	m_vec2WindowStartPosition = { vec2ScreenStartPosition.m_fx - (_iWidth / 2.0f),
											  vec2ScreenStartPosition.m_fy - (_iHeight / 2.0f) };
	m_vec2WindowSize = { static_cast<float>(_iWidth),static_cast<float>(_iHeight) };

	SetWindowPos(Core::GetInstance()->GethWnd(), nullptr, m_vec2WindowStartPosition.m_fx, m_vec2WindowStartPosition.m_fy,
		_iWidth + 16, _iHeight + 39, SWP_SHOWWINDOW);
}

void Scene::AddObject(Object* _object, OBJECT_GROUP _eGroup)
{
	m_arrObjects[static_cast<int>(_eGroup)].push_back(_object);
}

void Scene::AddCollider(Collider* _collider, COLLIDER_GROUP _eGroup)
{
	m_arrColliders[static_cast<int>(_eGroup)].push_back(_collider);
}

Object* Scene::GetPlayer()
{
	if(m_arrObjects[static_cast<int>(OBJECT_GROUP::PLAYABLE)].size() == 0)
		return nullptr;
	return m_arrObjects[static_cast<int>(OBJECT_GROUP::PLAYABLE)][0];
}

void Scene::Update()
{
	for (int i = 0; i < static_cast<int>(OBJECT_GROUP::END); i++)
	{
		for (int j = 0; j < m_arrObjects[i].size(); j++)
			m_arrObjects[i][j]->Update();
	}
}

void Scene::LateUpdate()
{
	for (int i = 0; i < static_cast<int>(OBJECT_GROUP::END); i++)
	{
		for (int j = 0; j < m_arrObjects[i].size(); j++)
			m_arrObjects[i][j]->LateUpdate();
	}
}

void Scene::Render(HDC _memDC)
{
	for (int i = 0; i < static_cast<int>(OBJECT_GROUP::END); i++)
	{
		for (Object* object : m_arrObjects[i])
			object->Render(_memDC);
	}
}
