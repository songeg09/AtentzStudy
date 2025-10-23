#include "pch.h"
#include "Object.h"
#include "Texture.h"
#include "Collider.h"

Object::Object()
{
	m_vec2Position = {};
	m_vec2Scale = {};
	m_pTexture = nullptr;
	m_pCollider = nullptr;
}

Object::~Object()
{
	if (m_pCollider != nullptr)
		delete m_pCollider;
}

void Object::LateUpdate()
{
	if (m_pCollider != nullptr)
		m_pCollider->FinalUpdate();
}

void Object::Render(HDC _memDC)
{
	Vector2 vec2Position = Object::GetPosition();
	int iWidth = m_pTexture->GetWidth();
	int iHeight = m_pTexture->GetHeight();
	vec2Position.m_fx -= iWidth / 2;
	vec2Position.m_fy -= iHeight / 2;

	TransparentBlt(_memDC, vec2Position.m_fx, vec2Position.m_fy, iWidth, iHeight,
		m_pTexture->GetDC(), 0, 0, iWidth, iHeight, RGB(255, 255, 255));

	if (m_pCollider != nullptr)
		m_pCollider->Render(_memDC);
}

void Object::Init(Vector2 _vec2Position, TEXTURE_TYPE _eTexture_Type)
{
	m_pTexture = ResourceManager::GetInstance()->LoadTexture(_eTexture_Type);
	SetPosition(_vec2Position);
}

void Object:: CreateCollider()
{
	if (m_pCollider != nullptr)
		return;
	m_pCollider = new Collider;
	m_pCollider->SetTarget(this);
}