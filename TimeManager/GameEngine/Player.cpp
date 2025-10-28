#include "pch.h"
#include "Player.h"
#include "Texture.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "TimerManager.h"
#include "Core.h"
#include "Collider.h"

Player::Player()
	: Object(ConstValue::PLAYER_SPEED)
{
	Object::m_eCurAnimation = ANIMATION::IDLE;
	Object::m_eDirection = DIRECTION::DOWN;
}

Player::~Player()
{
}

void Player::Init(Vector2 _vec2Position)
{
	Object::Init(_vec2Position);

	// 캐릭터 콜라이더
	Collider* collider = new Collider;
	collider->SetTarget(this);
	collider->SetSize(Vector2{ 30.0f, 40.0f });
	collider->SetOffsetPosition(Vector2{ 0.0f,-6.0f });
	collider->SetActive(true);
	m_pColliders.push_back(collider);
	SceneManager::GetInstance()->GetCurScene()->AddCollider(collider, COLLIDER_GROUP::PLAYABLE);

	// 칼 콜라이더
	collider = new Collider;
	collider->SetTarget(this);
	collider->SetSize(Vector2{ 20.0f, 20.0f });
	collider->SetOffsetPosition(Vector2{ 0.0f,0.0f });
	collider->SetActive(false);
	m_pColliders.push_back(collider);
	SceneManager::GetInstance()->GetCurScene()->AddCollider(collider, COLLIDER_GROUP::BULLET);
	m_Sword = collider;

	InputManager::GetInstance()->RegistKey(VK_LEFT);
	InputManager::GetInstance()->RegistKey(VK_RIGHT);
	InputManager::GetInstance()->RegistKey(VK_UP);
	InputManager::GetInstance()->RegistKey(VK_DOWN);
	InputManager::GetInstance()->RegistKey(VK_SPACE);

	std::vector<AnimNode> vecAnimationList;

	for (int i = DIRECTION::START; i != DIRECTION::END; ++i)
	{
		//방향별 IDLE 애니메이션
		vecAnimationList.clear();
		for (int j = TEXTURE_TYPE::PLAYER_IDLE_START; j <= TEXTURE_TYPE::PLAYER_IDLE_END; j++)
		{
			vecAnimationList.push_back(AnimNode{ ResourceManager::GetInstance()->LoadTexture(static_cast<TEXTURE_TYPE>(j),static_cast<DIRECTION>(i)),nullptr });
		}
		m_AnimationList[i][ANIMATION::IDLE].Init(vecAnimationList, ANIMATION_TYPE::LOOP, ConstValue::fAnimationPlayerSpeed, ANCHOR::CENTER);

		//방향별 이동 애니메이션
		vecAnimationList.clear();
		for (int j = TEXTURE_TYPE::PLAYER_RUN_START; j <= TEXTURE_TYPE::PLAYER_RUN_END; ++j)
		{
			vecAnimationList.push_back(AnimNode{ ResourceManager::GetInstance()->LoadTexture(static_cast<TEXTURE_TYPE>(j),static_cast<DIRECTION>(i)),nullptr });
		}
		m_AnimationList[i][ANIMATION::RUN].Init(vecAnimationList, ANIMATION_TYPE::LOOP, ConstValue::fAnimationPlayerSpeed, ANCHOR::CENTER);
	
		//방향별 공격 애니메이션
		vecAnimationList.clear();
		for (int j = TEXTURE_TYPE::PLAYER_ATTACK_START; j <= TEXTURE_TYPE::PLAYER_ATTACK_END; ++j)
		{
			vecAnimationList.push_back(AnimNode{ ResourceManager::GetInstance()->LoadTexture(static_cast<TEXTURE_TYPE>(j),static_cast<DIRECTION>(i)),nullptr });
		}
 		vecAnimationList[0].m_callBack = std::bind(&Player::BeginAttack, this);
		vecAnimationList[vecAnimationList.size() - 1].m_callBack = std::bind(&Player::EndAttack, this);
		m_AnimationList[i][ANIMATION::ATTACK].Init(vecAnimationList, ANIMATION_TYPE::ONCE, ConstValue::fAnimationPlayerSpeed, ANCHOR::CENTER);
		
	}
	
	m_eCurAnimation = ANIMATION::IDLE;
}

void Player::Action()
{
	if (InputManager::GetInstance()->GetKeyState(VK_SPACE) == KEY_STATE::DOWN)
	{
		m_eCurAnimation = ANIMATION::ATTACK;
		m_AnimationList[m_eDirection][m_eCurAnimation].Reset();
	}
	else if (m_eCurAnimation != ANIMATION::ATTACK)
	{
		Vector2 vec2MoveForce;
		if (InputManager::GetInstance()->GetKeyState(VK_LEFT) == KEY_STATE::PRESS)
		{
			vec2MoveForce.m_fx = m_fMoveSpeed * TimerManager::GetInstance()->GetdDeltaTime() * -1.0f;
			m_eDirection = DIRECTION::LEFT;
			m_Sword->SetOffsetPosition({ -20.f,-6.0f });
		}
		else if (InputManager::GetInstance()->GetKeyState(VK_RIGHT) == KEY_STATE::PRESS)
		{
			vec2MoveForce.m_fx = m_fMoveSpeed * TimerManager::GetInstance()->GetdDeltaTime() * 1.0f;
			m_eDirection = DIRECTION::RIGHT;
			m_Sword->SetOffsetPosition({ 20.f,-6.0f });
		}
		else if (InputManager::GetInstance()->GetKeyState(VK_UP) == KEY_STATE::PRESS)
		{
			vec2MoveForce.m_fy = m_fMoveSpeed * TimerManager::GetInstance()->GetdDeltaTime() * -1.0f;
			m_eDirection = DIRECTION::UP;
			m_Sword->SetOffsetPosition({ 0.f,-26.f });
		}
		else if (InputManager::GetInstance()->GetKeyState(VK_DOWN) == KEY_STATE::PRESS)
		{
			vec2MoveForce.m_fy = m_fMoveSpeed * TimerManager::GetInstance()->GetdDeltaTime() * 1.0f;
			m_eDirection = DIRECTION::DOWN;
			m_Sword->SetOffsetPosition({ 0.f,14.f });
		}
		if (vec2MoveForce.m_fx != 0.0f || vec2MoveForce.m_fy != 0.0f)
		{
			Vector2 vec2CurPosition = GetPosition();
			vec2CurPosition += vec2MoveForce;
			SetPosition(vec2CurPosition);
			m_eCurAnimation = ANIMATION::RUN;
		}
		else
		{
			m_eCurAnimation = ANIMATION::IDLE;
		}
	}
}


void Player::BeginAttack()
{
	m_Sword->SetActive(true);
}

void Player::EndAttack()
{
	m_Sword->SetActive(false);
	SetAnimation(ANIMATION::IDLE);
}
