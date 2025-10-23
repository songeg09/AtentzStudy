#include "pch.h"
#include "Monster.h"
#include "Collider.h"

Monster::Monster()
	: m_fMoveSpeed(100.f)
{
	m_eCurAnimation = ANIMATION::IDLE;
	m_eDirection = DIRECTION::DOWN;

	CreateCollider();
	GetCollider()->SetSize(Vector2{ 20.0f, 20.0f });
	GetCollider()->SetOffsetPosition(Vector2{ 0.0f,-10.0f });
}

Monster::~Monster()
{
}

void Monster::Init(Vector2 _vec2Position)
{
	Object::SetPosition(_vec2Position);

	std::vector<AnimNode> vecAnimationList;
	for (int i = DIRECTION::START; i != DIRECTION::END; ++i)
	{
		//방향별 제자리 애니메이션
		vecAnimationList.clear();
		for (int j = TEXTURE_TYPE::MONSTER_IDLE_START; j <= TEXTURE_TYPE::MONSTER_IDLE_END; ++j)
		{
			vecAnimationList.push_back(AnimNode{ ResourceManager::GetInstance()->LoadTexture(static_cast<TEXTURE_TYPE>(j),static_cast<DIRECTION>(i)),nullptr });
		}
		m_AnimationList[i][ANIMATION::IDLE].Init(vecAnimationList, ANIMATION_TYPE::LOOP, 0.2f, ANCHOR::CENTER_BOTTOM);
	}
	m_eCurAnimation = ANIMATION::IDLE;
}

void Monster::Update()
{
	m_AnimationList[m_eDirection][m_eCurAnimation].Update();
}

void Monster::Render(HDC _memDC)
{
	m_AnimationList[m_eDirection][m_eCurAnimation].Render(_memDC, Object::GetPosition());
	if (GetCollider() != nullptr)
		GetCollider()->Render(_memDC);
}