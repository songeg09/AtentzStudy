#include "pch.h"
#include "Player.h"
#include "Texture.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "TimerManager.h"
#include "Core.h"
#include "Collider.h"
#include "Monster.h"

Player::Player()
{
	m_bInput = true;
	m_pAttackCollider = nullptr;
}

Player::~Player()
{
}

void Player::Init(Vector2 _vec2Position)
{
	// Ű ���
	InputManager::GetInstance()->RegistKey(VK_LEFT);
	InputManager::GetInstance()->RegistKey(VK_RIGHT);
	InputManager::GetInstance()->RegistKey(VK_UP);
	InputManager::GetInstance()->RegistKey(VK_DOWN);
	InputManager::GetInstance()->RegistKey(VK_SPACE);

	CreateCollider(true, Vector2{ 40.f,40.f }, Vector2{ 0.0f,0.0f });
	m_pAttackCollider = CreateCollider(false, Vector2{ 40.f, 40.f }, Vector2(0.0f, 20.f));
	m_pAttackCollider->SetBeginCollisionCallBack(
		std::bind([this](Collider* _pOther)
			{
				Monster* TargetMonster = dynamic_cast<Monster*>(_pOther->GetTarget());
				if (TargetMonster == nullptr)
					return;
				Vector2 ForceDirection = _pOther->GetPosition() - GetPosition();
				ForceDirection.Normalize();
				TargetMonster->AddForce(ForceDirection * 300.0f);
			}, std::placeholders::_1));

	// �ִϸ��̼� ����
	Actor::SetPosition(_vec2Position);
	Actor::ResizeAnimation(ANIMATION::END);
	Actor::InitAnimation(ANIMATION::IDLE, TEXTURE_TYPE::PLAYER_IDLE_START, TEXTURE_TYPE::PLAYER_IDLE_END);
	Actor::InitAnimation(ANIMATION::RUN, TEXTURE_TYPE::PLAYER_RUN_START, TEXTURE_TYPE::PLAYER_RUN_END);
	Actor::InitAnimation(ANIMATION::ATTACK, TEXTURE_TYPE::PLAYER_ATTACK_START, TEXTURE_TYPE::PLAYER_ATTACK_END, 0.5f, ANIMATION_TYPE::ONCE);
	Actor::SetAnimationEvent(ANIMATION::ATTACK, 1,
		[this]() {
			m_pAttackCollider->SetEnable(true);
		}
	);
	Actor::SetAnimationEvent(ANIMATION::ATTACK, 2,
		[this]() {
			m_pAttackCollider->SetEnable(false);
		}
	);
	Actor::SetAnimationEvent(ANIMATION::ATTACK, 3,
		[this]() {
			m_bInput = true;
			Actor::SetAnimation(ANIMATION::IDLE);
		}
	);
	Actor::SetAnimation(ANIMATION::IDLE);
	
	// �ӵ� ����
	Actor::SetMoveSpeed(200.0f);
}

void Player::Update()
{
  	Actor::Update();
	Input();
}

void Player::Render(HDC _memDC)
{
	Actor::Render(_memDC);
}

void Player::Attack(Collider* _pOther)
{
}

void Player::Input()
{
	if (m_bInput == false)
		return;

	if (InputManager::GetInstance()->GetKeyState(VK_SPACE) == KEY_STATE::DOWN)
	{
		m_bInput = false;
		Actor::SetAnimation(ANIMATION::ATTACK);
	}
	else
	{
		Vector2 vec2MoveForce;
		if (InputManager::GetInstance()->GetKeyState(VK_LEFT) == KEY_STATE::PRESS)
			vec2MoveForce.m_fx += -1.0f;
		if (InputManager::GetInstance()->GetKeyState(VK_RIGHT) == KEY_STATE::PRESS)
			vec2MoveForce.m_fx += 1.0f;
		if (InputManager::GetInstance()->GetKeyState(VK_UP) == KEY_STATE::PRESS)
			vec2MoveForce.m_fy += -1.0f;
		if (InputManager::GetInstance()->GetKeyState(VK_DOWN) == KEY_STATE::PRESS)
			vec2MoveForce.m_fy += 1.0f;

		if (vec2MoveForce.isValid() == true)
		{
			Actor::Move(vec2MoveForce);
			Actor::SetAnimation(ANIMATION::RUN);
		}
		else
			Actor::SetAnimation(ANIMATION::IDLE);
	}
}
