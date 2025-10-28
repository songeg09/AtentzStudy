#include "pch.h"
#include "Monster.h"
#include "Collider.h"
#include "SceneManager.h"
#include "TimerManager.h"
#include "Player.h"

Monster::Monster()
	: Object(ConstValue::MONSTER_SPEED)
{
	m_eCurAnimation = ANIMATION::IDLE;
	m_eDirection = DIRECTION::DOWN;
}

Monster::~Monster()
{
}

void Monster::Init(Vector2 _vec2Position)
{
	Object::Init(_vec2Position);

	Collider* collider = new Collider;
	collider->SetTarget(this);
	collider->SetSize(Vector2{ 20.0f, 20.0f });
	collider->SetOffsetPosition(Vector2{ 0.0f,-10.0f });
	collider->SetActive(true);
	SceneManager::GetInstance()->GetCurScene()->AddCollider(collider, COLLIDER_GROUP::MONSTER);
	m_pColliders.push_back(collider);

	std::vector<AnimNode> vecAnimationList;
	for (int i = DIRECTION::START; i != DIRECTION::END; ++i)
	{
		//���⺰ ���ڸ� �ִϸ��̼�
		vecAnimationList.clear();
		for (int j = TEXTURE_TYPE::MONSTER_IDLE_START; j <= TEXTURE_TYPE::MONSTER_IDLE_END; ++j)
		{
			vecAnimationList.push_back(AnimNode{ ResourceManager::GetInstance()->LoadTexture(static_cast<TEXTURE_TYPE>(j),static_cast<DIRECTION>(i)),nullptr });
		}
		m_AnimationList[i][ANIMATION::IDLE].Init(vecAnimationList, ANIMATION_TYPE::LOOP, 0.2f, ANCHOR::CENTER_BOTTOM);
		m_AnimationList[i][ANIMATION::RUN].Init(vecAnimationList, ANIMATION_TYPE::LOOP, 0.2f, ANCHOR::CENTER_BOTTOM);
		vecAnimationList[vecAnimationList.size() - 1].m_callBack = std::bind(&Monster::EndAttack, this);
		m_AnimationList[i][ANIMATION::ATTACK].Init(vecAnimationList, ANIMATION_TYPE::ONCE, ConstValue::fAnimationPlayerSpeed, ANCHOR::CENTER_BOTTOM);
	}
	m_eCurAnimation = ANIMATION::IDLE;
}


void Monster::Action()
{
	// �÷��̾� ���󰡱�
	if (Object* Player = SceneManager::GetInstance()->GetCurScene()->GetPlayer())
	{
		Vector2 PlayerPos = Player->GetPosition();
		Vector2 vec2MoveForce = PlayerPos - GetPosition();

		vec2MoveForce.Normalize();
		vec2MoveForce = vec2MoveForce * m_fMoveSpeed * TimerManager::GetInstance()->GetfDeltaTime();

		SetPosition(GetPosition() + vec2MoveForce);
	}
}

void Monster::EndAttack()
{
	SetAnimation(ANIMATION::IDLE);
}

void Monster::HitBy(Vector2 _vec2MoveForce, Collider* _other)
{
	// �������̰ų�
	if (Object::m_eCurAnimation == ANIMATION::ATTACK)
		return;

	// �̹� �˹� ���ΰ�� 
	if (m_vec2ExternalForce.Length() > 0.2f)
		return;

	if (Player* player = dynamic_cast<Player*>(SceneManager::GetInstance()->GetCurScene()->GetPlayer()))
	{
		// Į�� ����� ���
		if (_other == player->GetSword())
		{
			Object::m_vec2ExternalForce = _vec2MoveForce;
		}
		// �÷��̾�� ���� ��������
		else
		{
			m_eCurAnimation = ANIMATION::ATTACK;
			m_AnimationList[m_eDirection][m_eCurAnimation].Reset();
		}
	}

}
