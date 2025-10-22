#include "pch.h"
#include "Object.h"
#include "Texture.h"

Object::Object()
{
	m_vec2Position = {};
	m_vec2Scale = {};
}

Object::~Object()
{
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
}

void Object::Init(Vector2 _vec2Position, TEXTURE_TYPE _eTexture_Type)
{
	m_pTexture = ResourceManager::GetInstance()->LoadTexture(_eTexture_Type);
	SetPosition(_vec2Position);
}