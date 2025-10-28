#include "pch.h"
#include "Sword.h"
#include "Collider.h"

Sword::Sword()
{
	m_Owner = nullptr;
	CreateCollider();
	GetCollider()->SetSize(Vector2{ 20.0f, 20.0f });
	GetCollider()->SetOffsetPosition(Vector2{ 0.0f,0.0f });
}

Sword::~Sword()
{
}

void Sword::SetPosition(DIRECTION _eDriection)
{
	Vector2 CurPos = m_Owner->GetCollider()->GetPosition();

	switch(_eDriection)
	{
	case DIRECTION::LEFT:
		CurPos += {-20.f, 0.0f};
		break;
	case DIRECTION::RIGHT:
		CurPos += {20.f, 0.0f};
		break;
	case DIRECTION::DOWN:
		CurPos += {0.0f, 20.0f};
		break;
	case DIRECTION::UP:
		CurPos += {0.0f, -20.0f};
		break;
	}

	Object::SetPosition(CurPos);
}

void Sword::Init(Vector2 _vec2Position, Object* _Owner)
{
	Object::SetPosition(_vec2Position);
	m_Owner = _Owner;
}

void Sword::Render(HDC _memDC)
{
	if (GetCollider() != nullptr)
		GetCollider()->Render(_memDC);
}

void Sword::Update()
{
}
