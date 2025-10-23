#pragma once
class Object;
class Collider
{
private:
	static unsigned int s_uID;
	Object* m_pTarget;
	Vector2 m_vecOffset;
	Vector2 m_vecPosition;
	Vector2 m_vecSize;
	const unsigned int m_uID;
	int m_iCollisionCount;

public:
	void SetOffsetPosition(Vector2 _vecPosition) { m_vecOffset = _vecPosition; }
	void SetSize(Vector2 _vecSize) { m_vecSize = _vecSize; }
	void SetTarget(Object* _pTarget) { m_pTarget = _pTarget; }

	void OnCollision(Collider* _pOther);
	void BeginCollision(Collider* _pOther);
	void EndCollision(Collider* _pOther);

	unsigned int GetID() { return m_uID; }
	Vector2 GetOffsetPosition() { return m_vecOffset; }
	Vector2 GetPosition() { return m_vecPosition; }
	Vector2 GetSize() { return m_vecSize; }

	void FinalUpdate();
	void Render(HDC _memDC);
	Collider();
	~Collider();
};

