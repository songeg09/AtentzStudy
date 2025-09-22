#include "pch.h"
#include "Card.h"
#include "Texture.h"
#include "ResourceManager.h"

Card::Card()
{
	m_vec2Position = {};
	m_pTexture = nullptr;
}

Card::~Card()
{

}

void Card::Update()
{

}

void Card::Init(Vector2 _vec2Position, Texture* _pTexture)
{
	m_vec2Position = _vec2Position;
	m_pTexture = _pTexture;
}

void Card::Render(HDC _hDC)
{
	Vector2 Position = GetPosition();
	Position.x -= m_pTexture->GetWidth() / 2;
	Position.y -= m_pTexture->GetHeight() / 2;
	BitBlt(_hDC, Position.x, Position.y, m_pTexture->GetWidth(), m_pTexture->GetHeight(), m_pTexture->GetDC(), 0, 0, SRCCOPY);
}
