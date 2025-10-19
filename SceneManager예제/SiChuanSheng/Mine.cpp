#include "pch.h"
#include "Mine.h"

Mine::Mine(bool _IsBomb)
{
	m_iAdjBombs = 0;
	m_bIsBomb = _IsBomb;
	m_State = MINE_STATE::CLOSE;
	m_ClickArea = {};
	m_pTexture = nullptr;
}

void Mine::Init(Vector2 _vec2Position, TEXTURE_TYPE _eTexture_Type)
{
	m_pTexture = ResourceManager::GetInstance()->LoadTexture(_eTexture_Type);
}

void Mine::Update()
{

}

void Mine::Render(HDC _memDC)
{

}