#pragma once

union Collider_ID
{
	struct
	{
		unsigned int iFirst_ID;
		unsigned int iSecond_ID;
	};
	unsigned long long ID;
};

class Collider;
class CollisionManager
{
	SINGLETON(CollisionManager)
private:
	std::map<unsigned long long, bool> m_PrevCollision;
	std::vector<bool> m_ColliderGroupList[static_cast<int>(COLLIDER_GROUP::END)];
public:
	void Init();
	void Update();
	void RegistColliderGroup(COLLIDER_GROUP _eFirst, COLLIDER_GROUP _eSecond);
	bool IsCollision(Collider* _pFirst, Collider* _pSecond);
	void ReleaseColliderGroup();
	void CollisionCheckGroup(COLLIDER_GROUP _eFirst, COLLIDER_GROUP _eSecond);
	void CollisionCheck(Collider* _pFirst, Collider* _pSecond);
};

