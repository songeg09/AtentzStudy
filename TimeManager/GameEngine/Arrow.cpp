#include "pch.h"
#include "Arrow.h"
#include "Texture.h"
#include "TimerManager.h"
#include "SceneManager.h"

Arrow::Arrow()
{
	m_iMaxPosition_x = 0;
	m_fSpeed = 0.0f;
}

Arrow::~Arrow()
{
}

void Arrow::Update()
{
	Vector2 position = Object::GetPosition();
	if (position.m_fx >= m_iMaxPosition_x)
		return;

	position.m_fx += m_fSpeed * TimerManager::GetInstance()->GetfDeltaTime();
	Object::SetPosition(position);

}

void Arrow::Init(Vector2 _vec2Position, TEXTURE_TYPE _eTexture_Type)
{
	Object::Init(_vec2Position, _eTexture_Type);
	m_iMaxPosition_x = SceneManager::GetInstance()->GetCurScene()->GetWindowSize().m_fx;
}