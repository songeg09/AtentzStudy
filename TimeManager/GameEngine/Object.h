#pragma once
#include"ResourceManager.h"

class Collider;
class Object
{
private:
	Vector2 m_vec2Position;
	Vector2 m_vec2Scale;
	Texture* m_pTexture;
	Collider* m_pCollider;

public:
	Object();
	virtual ~Object();

	virtual void Update() = 0;
	virtual void LateUpdate() final; // 자식 Class에서 Override하지 못하게 막는 용도
	virtual void Render(HDC _memDC);
	virtual void Init(Vector2 _vec2Position, TEXTURE_TYPE _eTexture_Type);

	void CreateCollider();

	inline Collider* GetCollider() { return m_pCollider; }
	void AddPosition(Vector2 _vec2Add) { m_vec2Position += _vec2Add; }
	void SetPosition(Vector2 _vec2Position) { m_vec2Position = _vec2Position; }
	void SetScale(Vector2 _vec2Scale) { m_vec2Scale = _vec2Scale; }
	Vector2 GetPosition() { return m_vec2Position; }
	Vector2 GetScale() { return m_vec2Scale; }
};

