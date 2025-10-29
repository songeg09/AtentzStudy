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
	bool m_bEnabled;

	std::function<void(Collider* _pOther)> m_OnCollisioncallBack;
	std::function<void(Collider* _pOther)> m_BeginCollisioncallBack;
	std::function<void(Collider* _pOther)> m_EndCollisioncallBack;
public:
	void Init(bool _bEnabled, Vector2 _vecSize, Vector2 _vecOffset = Vector2{ 0.0f,0.0f });
	inline void SetOnCollisionCallBack(std::function<void(Collider* _pOther)> _pCallBack) { m_OnCollisioncallBack = _pCallBack; }
	inline void SetBeginCollisionCallBack(std::function<void(Collider* _pOther)> _pCallBack) { m_BeginCollisioncallBack = _pCallBack; }
	inline void SetEndCollisionCallBack(std::function<void(Collider* _pOther)> _pCallBack) { m_EndCollisioncallBack = _pCallBack; }
	inline void SetOffsetPosition(Vector2 _vecPosition) { m_vecOffset = _vecPosition; }
	inline void SetSize(Vector2 _vecSize) { m_vecSize = _vecSize; }
	inline void SetTarget(Object* _pTarget) { m_pTarget = _pTarget; }

	void OnCollision(Collider* _pOther);
	void BeginCollision(Collider* _pOther);
	void EndCollision(Collider* _pOther);

	inline unsigned int GetID() { return m_uID; }
	inline Vector2 GetOffsetPosition() { return m_vecOffset; }
	inline Vector2 GetPosition() { return m_vecPosition; }
	inline Vector2 GetSize() { return m_vecSize; }
	inline Object* GetTarget() { return m_pTarget; }
	inline bool isEnable() { return m_bEnabled; }
	inline void SetEnable(bool _bEnabled) { m_bEnabled = _bEnabled; }

	void FinalUpdate();
	void Render(HDC _memDC);

	Collider();
	~Collider();
};

