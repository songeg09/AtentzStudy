#include "Block.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Core.h"


Block::Block(bool _IsBomb, Vector2 _pos)
	:m_bIsBomb(_IsBomb), m_iAdjBombs(0), m_bIsOpen(false), m_bIsFlagged(false),m_vec2Position(_pos)
{
	m_ClickArea = {};
	m_pTexture = nullptr;
	if (m_bIsBomb)
	{
		m_pTexture = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::BLOCK_MINE);
		SetClickArea();
	}
}

Block::~Block()
{
}

void Block::Update(const POINT& pt)
{
	if(PtInRect(&m_ClickArea, pt))
		m_bIsOpen = true;
}

void Block::Render(HDC _hDC)
{
	static Texture* m_pBackTextue = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::BLOCK_CLOSE);
	static Texture* m_pFlagTextue = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::BLOCK_FLAG);
	
	if(m_bIsOpen)
		BitBlt(_hDC, m_vec2Position.x, m_vec2Position.y, m_pTexture->GetWidth(), m_pTexture->GetHeight(), m_pTexture->GetDC(), 0, 0, SRCCOPY);
	else if(m_bIsFlagged)
		BitBlt(_hDC, m_vec2Position.x, m_vec2Position.y, m_pFlagTextue->GetWidth(), m_pFlagTextue->GetHeight(), m_pFlagTextue->GetDC(), 0, 0, SRCCOPY);
	else
		BitBlt(_hDC, m_vec2Position.x, m_vec2Position.y, m_pBackTextue-> GetWidth(), m_pBackTextue->GetHeight(), m_pBackTextue->GetDC(), 0, 0, SRCCOPY);

}

void Block::SetupBlock(int _AdjBombs)
{
	m_iAdjBombs = _AdjBombs;
	
	switch (_AdjBombs)
	{
	case 0:
		m_pTexture = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::BLOCK_0);
		break;
	case 1:
		m_pTexture = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::BLOCK_1);
		break;
	case 2:
		m_pTexture = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::BLOCK_2);
		break;
	case 3:
		m_pTexture = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::BLOCK_3);
		break;
	case 4:
		m_pTexture = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::BLOCK_4);
		break;
	case 5:
		m_pTexture = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::BLOCK_5);
		break;
	case 6:
		m_pTexture = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::BLOCK_6);
		break;
	case 7:
		m_pTexture = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::BLOCK_7);
		break;
	case 8:
		m_pTexture = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::BLOCK_8);
		break;
	}

	SetClickArea();
}

void Block::SetClickArea()
{
	m_ClickArea = {
		m_vec2Position.x - m_pTexture->GetWidth() / 2,
		m_vec2Position.y - m_pTexture->GetHeight() / 2,
		m_vec2Position.x + m_pTexture->GetWidth() / 2,
		m_vec2Position.y + m_pTexture->GetHeight() / 2,
	};
}
