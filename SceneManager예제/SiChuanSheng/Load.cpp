#include "pch.h"
#include "Load.h"
#include "Texture.h"
#include "SiChuanShengScene.h"

void Load::Update()
{
}

void Load::Render(HDC _memDC)
{
	TransparentBlt(_memDC, Object::GetPosition().m_ix, Object::GetPosition().m_iy, m_pBlockTexture->GetWidth(), m_pBlockTexture->GetHeight(), m_pBlockTexture->GetDC(),
		0, 0, m_pBlockTexture->GetWidth(), m_pBlockTexture->GetHeight(), RGB(255, 0, 255));
}

void Load::Init(Vector2 _vec2Position, TEXTURE_TYPE _eTexture_Type)
{
	m_eBlockType = _eTexture_Type;
	m_pBlockTexture = ResourceManager::GetInstance()->LoadTexture(m_eBlockType);


	Vector2 vec2Scale;
	vec2Scale.m_ix = m_pBlockTexture->GetWidth();
	vec2Scale.m_iy = m_pBlockTexture->GetHeight();
	Object::SetScale(vec2Scale);
	Vector2 vec2Position;
	vec2Position.m_ix = BOARD_START::X + _vec2Position.m_ix * m_pBlockTexture->GetWidth() - (5 + _vec2Position.m_ix * 5);
	vec2Position.m_iy = BOARD_START::Y + _vec2Position.m_iy * m_pBlockTexture->GetHeight();
	Object::SetPosition(vec2Position);
}
