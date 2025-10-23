#include "pch.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Object.h"
#include "Collider.h"

CollisionManager::CollisionManager()
{

}

CollisionManager::~CollisionManager()
{

}

void CollisionManager::Init()
{
	for (int i = 0; i != static_cast<int>(OBJECT_GROUP::END); ++i)
	{
		m_CollisionGroupList[i] = std::vector<bool>(i + 1, false);
	}
}

void CollisionManager::Update()
{
	for (int i = 0; i != static_cast<int>(OBJECT_GROUP::END); ++i)
	{
		for (int j = 0; j < m_CollisionGroupList[i].size(); j++)
		{
			if (m_CollisionGroupList[i][j] == true)
				CollisionCheckGroup(static_cast<OBJECT_GROUP>(i), static_cast<OBJECT_GROUP>(j));
		}
	}
}

void CollisionManager::RegistCollisionGroup(OBJECT_GROUP _eFirst, OBJECT_GROUP _eSecond)
{
	if (_eFirst < _eSecond)
	{
		OBJECT_GROUP tmp = _eFirst;
		_eFirst = _eSecond;
		_eSecond = tmp;
	}
	m_CollisionGroupList[static_cast<int>(_eFirst)][static_cast<int>(_eSecond)] = true;
}

bool CollisionManager::IsCollision(Collider* _pFirst, Collider* _pSecond)
{
	Vector2 FirstPosition = _pFirst->GetPosition();
	Vector2 FirstSize = _pFirst->GetSize();
	Vector2 SecondPosition = _pSecond->GetPosition();
	Vector2 SecondSize = _pSecond->GetSize();

	Vector2 CollisionPosition = FirstPosition - SecondPosition;

	if (abs(CollisionPosition.m_fx) < (FirstSize.m_fx + SecondSize.m_fx) / 2.0f &&
		abs(CollisionPosition.m_fy) < (FirstSize.m_fy + SecondSize.m_fy) / 2.0f)
	{
		return true;
	}


	return false;
}

void CollisionManager::ReleaseCollisionGroup()
{
	for (int i = 0; i != static_cast<int>(OBJECT_GROUP::END); ++i)
	{
		for (int j = 0; j < m_CollisionGroupList[i].size(); ++j)
			m_CollisionGroupList[i][j] = false;
	}
}

void CollisionManager::CollisionCheckGroup(OBJECT_GROUP _eFirst, OBJECT_GROUP _eSecond)
{
	Scene* CurScene = SceneManager::GetInstance()->GetCurScene();
	const std::vector<Object*>& FirstGroup = CurScene->GetObjectGroup(_eFirst);
	const std::vector<Object*>& SecondGroup = CurScene->GetObjectGroup(_eSecond);

	for (int i = 0; i < FirstGroup.size(); ++i)
	{
		if (FirstGroup[i]->GetCollider() == nullptr)
			continue;
		for (int j = 0; j < SecondGroup.size(); ++j)
		{
			if (FirstGroup[i] == SecondGroup[j])
				continue;
			if (SecondGroup[j]->GetCollider() == nullptr)
				continue;

			CollisionCheck(FirstGroup[i]->GetCollider(), SecondGroup[j]->GetCollider());
		}
	}
}

void CollisionManager::CollisionCheck(Collider* _pFirst, Collider* _pSecond)
{
	int iFirstID = _pFirst->GetID();
	int iSecondID = _pSecond->GetID();
	if (iFirstID > iSecondID)
	{
		int tmp = iFirstID;
		iFirstID = iSecondID;
		iSecondID = tmp;
	}
	Collider_ID ID;
	ID.iFirst_ID = iFirstID;
	ID.iSecond_ID = iSecondID;

	std::map<unsigned long long, bool>::iterator iter = m_PrevCollision.find(ID.ID);

	if (iter == m_PrevCollision.end())
	{
		m_PrevCollision.insert(std::make_pair(ID.ID, false));
		iter = m_PrevCollision.find(ID.ID);
	}

	if (IsCollision(_pFirst, _pSecond) == true)
	{
		if (iter->second == true)
		{
			_pFirst->OnCollision(_pSecond);
			_pSecond->OnCollision(_pFirst);
		}
		else
		{
			_pFirst->BeginCollision(_pSecond);
			_pSecond->BeginCollision(_pFirst);
			iter->second = true;
		}
	}
	else
	{
		if (iter->second == true)
		{
			_pFirst->EndCollision(_pSecond);
			_pSecond->EndCollision(_pFirst);
			iter->second = false;
		}
	}

}