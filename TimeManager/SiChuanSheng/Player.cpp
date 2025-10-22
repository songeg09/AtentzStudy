#include "pch.h"
#include "Player.h"
#include "Texture.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Arrow.h"

Player::Player()
{
	m_eCurAnimation = ANIMATION::IDLE;
}

Player::~Player()
{
}

void Player::FireArrow()
{
	Arrow* arrow = new Arrow;
	Vector2 vec2Position = Object::GetPosition();
	vec2Position.m_fx += 18;
	vec2Position.m_fy -= 35;
	arrow->Init(vec2Position, TEXTURE_TYPE::ARROW);
	arrow->SetSpeed(ConstValue::fArrow_Speed);
	SceneManager::GetInstance()->GetCurScene()->AddObject(arrow, OBJECT_GROUP::BULLET);
}

void Player::Init(Vector2 _vec2Position)
{
	Object::SetPosition(_vec2Position);
	std::vector<AnimNode> vecAnimationList;
	for (int i = static_cast<int>(TEXTURE_TYPE::PLAYER_IDLE_START); i <= static_cast<int>(TEXTURE_TYPE::PLAYER_IDLE_END); i++)
	{
		vecAnimationList.push_back(AnimNode{ ResourceManager::GetInstance()->LoadTexture(static_cast<TEXTURE_TYPE>(i)),nullptr });
	}
	m_AnimationList[ANIMATION::IDLE].Init(vecAnimationList, ANIMATION_TYPE::LOOP, 0.1f, ANCHOR::CENTER_BOTTOM);

	vecAnimationList.clear();
	for (int i = static_cast<int>(TEXTURE_TYPE::PLAYER_ATTACK_1_START); i <= static_cast<int>(TEXTURE_TYPE::PLAYER_ATTACK_1_END); i++)
	{
		vecAnimationList.push_back(AnimNode{ ResourceManager::GetInstance()->LoadTexture(static_cast<TEXTURE_TYPE>(i)),nullptr });
	}
	vecAnimationList[8].m_callBack = std::bind(&Player::FireArrow, this);
	m_AnimationList[ANIMATION::ATTACK_1].Init(vecAnimationList, ANIMATION_TYPE::ONCE, 0.1f, ANCHOR::CENTER_BOTTOM);


	m_eCurAnimation = ANIMATION::IDLE;
}

void Player::Update()
{
	if (m_eCurAnimation == ANIMATION::IDLE && InputManager::GetInstance()->GetKeyState(VK_SPACE) == KEY_STATE::DOWN)
	{
		m_eCurAnimation = ANIMATION::ATTACK_1;
		m_AnimationList[m_eCurAnimation].Reset();
	}

	m_AnimationList[m_eCurAnimation].Update();

	if (m_eCurAnimation == ANIMATION::ATTACK_1 && m_AnimationList[m_eCurAnimation].GetLive() == false)
	{
		m_eCurAnimation = ANIMATION::IDLE;
		m_AnimationList[m_eCurAnimation].Reset();
	}
}

void Player::Render(HDC _memDC)
{
	m_AnimationList[m_eCurAnimation].Render(_memDC, Object::GetPosition());
}
