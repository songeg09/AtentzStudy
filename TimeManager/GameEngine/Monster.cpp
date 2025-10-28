#include "pch.h"
#include "Monster.h"
#include "Collider.h"
#include "SceneManager.h"
#include "TimerManager.h"

Monster::Monster()
	: m_fMoveSpeed(ConstValue::MONSTER_SPEED)
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

	Vector2 vec2MoveForce;
	if (GetCanMove() == true)
	{
		// 플레이어 따라가기
		if (Object* Player = SceneManager::GetInstance()->GetCurScene()->GetPlayer())
		{
			Vector2 PlayerPos = Player->GetCollider()->GetPosition();
			vec2MoveForce = PlayerPos - GetCollider()->GetPosition();

			vec2MoveForce.Normalize();
			vec2MoveForce = vec2MoveForce * m_fMoveSpeed * TimerManager::GetInstance()->GetfDeltaTime();

			SetPosition(GetPosition() + vec2MoveForce);
		}
	}
	else
	{
		vec2MoveForce = GetExternalForce() * TimerManager::GetInstance()->GetfDeltaTime();

		SetPosition(GetPosition() + vec2MoveForce);

		Vector2 vec2Friction = GetExternalForce();
		vec2Friction.Normalize();
		vec2Friction = vec2Friction * ConstValue::FRICTION * TimerManager::GetInstance()->GetfDeltaTime() * (- 1.f);
		
		SetExternalForce(GetExternalForce() + vec2Friction);
		if (GetExternalForce().Length() <= 0.2f)
		{
			SetCanMove(true);
		}
	}

	m_AnimationList[m_eDirection][m_eCurAnimation].Update();
}

void Monster::Render(HDC _memDC)
{
	m_AnimationList[m_eDirection][m_eCurAnimation].Render(_memDC, Object::GetPosition());
	if (GetCollider() != nullptr)
		GetCollider()->Render(_memDC);
}