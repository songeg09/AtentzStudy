#include "pch.h"
#include "Player.h"
#include "Texture.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "TimerManager.h"
#include "Core.h"
#include "Collider.h"
#include "Sword.h"

Player::Player()
	: m_fMoveSpeed(150.0f)
{
	m_Sword = nullptr;
	m_eCurAnimation = ANIMATION::IDLE;
	m_eDirection = DIRECTION::DOWN;
	CreateCollider();
	GetCollider()->SetSize(Vector2{ 30.0f, 40.0f });
	GetCollider()->SetOffsetPosition(Vector2{ 0.0f,-40.0f });
}

Player::~Player()
{
}

void Player::Init(Vector2 _vec2Position)
{
	m_Sword = new Sword;
	m_Sword->Init({ 0.0f,0.0f }, this);
	SceneManager::GetInstance()->GetCurScene()->AddObject(m_Sword, OBJECT_GROUP::BULLET);

	InputManager::GetInstance()->RegistKey(VK_LEFT);
	InputManager::GetInstance()->RegistKey(VK_RIGHT);
	InputManager::GetInstance()->RegistKey(VK_UP);
	InputManager::GetInstance()->RegistKey(VK_DOWN);
	InputManager::GetInstance()->RegistKey(VK_SPACE);

	Object::SetPosition(_vec2Position);
	std::vector<AnimNode> vecAnimationList;

	for (int i = DIRECTION::START; i != DIRECTION::END; ++i)
	{
		//방향별 IDLE 애니메이션
		vecAnimationList.clear();
		for (int j = TEXTURE_TYPE::PLAYER_IDLE_START; j <= TEXTURE_TYPE::PLAYER_IDLE_END; j++)
		{
			vecAnimationList.push_back(AnimNode{ ResourceManager::GetInstance()->LoadTexture(static_cast<TEXTURE_TYPE>(j),static_cast<DIRECTION>(i)),nullptr });
		}
		m_AnimationList[i][ANIMATION::IDLE].Init(vecAnimationList, ANIMATION_TYPE::LOOP, ConstValue::fAnimationPlayerSpeed, ANCHOR::CENTER_BOTTOM);

		//방향별 이동 애니메이션
		vecAnimationList.clear();
		for (int j = TEXTURE_TYPE::PLAYER_RUN_START; j <= TEXTURE_TYPE::PLAYER_RUN_END; ++j)
		{
			vecAnimationList.push_back(AnimNode{ ResourceManager::GetInstance()->LoadTexture(static_cast<TEXTURE_TYPE>(j),static_cast<DIRECTION>(i)),nullptr });
		}
		m_AnimationList[i][ANIMATION::RUN].Init(vecAnimationList, ANIMATION_TYPE::LOOP, ConstValue::fAnimationPlayerSpeed, ANCHOR::CENTER_BOTTOM);
	
		//방향별 공격 애니메이션
		vecAnimationList.clear();
		for (int j = TEXTURE_TYPE::PLAYER_ATTACK_START; j <= TEXTURE_TYPE::PLAYER_ATTACK_END; ++j)
		{
			vecAnimationList.push_back(AnimNode{ ResourceManager::GetInstance()->LoadTexture(static_cast<TEXTURE_TYPE>(j),static_cast<DIRECTION>(i)),nullptr });
		}
 		vecAnimationList[0].m_callBack = std::bind(&Player::BeginAttack, this);
		vecAnimationList[vecAnimationList.size() - 1].m_callBack = std::bind(&Player::EndAttack, this);
		m_AnimationList[i][ANIMATION::ATTACK].Init(vecAnimationList, ANIMATION_TYPE::ONCE, ConstValue::fAnimationPlayerSpeed, ANCHOR::CENTER_BOTTOM);
		
	}
	
	m_eCurAnimation = ANIMATION::IDLE;
}

void Player::Update()
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
		}
		else if (InputManager::GetInstance()->GetKeyState(VK_RIGHT) == KEY_STATE::PRESS)
		{
			vec2MoveForce.m_fx = m_fMoveSpeed * TimerManager::GetInstance()->GetdDeltaTime() * 1.0f;
			m_eDirection = DIRECTION::RIGHT;
		}
		else if (InputManager::GetInstance()->GetKeyState(VK_UP) == KEY_STATE::PRESS)
		{
			vec2MoveForce.m_fy = m_fMoveSpeed * TimerManager::GetInstance()->GetdDeltaTime() * -1.0f;
			m_eDirection = DIRECTION::UP;
		}
		else if (InputManager::GetInstance()->GetKeyState(VK_DOWN) == KEY_STATE::PRESS)
		{
			vec2MoveForce.m_fy = m_fMoveSpeed * TimerManager::GetInstance()->GetdDeltaTime() * 1.0f;
			m_eDirection = DIRECTION::DOWN;
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

	m_AnimationList[m_eDirection][m_eCurAnimation].Update();
}

void Player::Render(HDC _memDC)
{
	m_AnimationList[m_eDirection][m_eCurAnimation].Render(_memDC, Object::GetPosition());
	if (GetCollider() != nullptr)
		GetCollider()->Render(_memDC);
}

void Player::BeginAttack()
{
	m_Sword->SetPosition(m_eDirection);
}

void Player::EndAttack()
{
	m_Sword->Object::SetPosition({ 0.0f,0.0f });
	SetAnimation(ANIMATION::IDLE);
}
