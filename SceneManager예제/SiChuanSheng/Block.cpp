#include "pch.h"
#include "Block.h"
#include "Texture.h"
#include "InputManager.h"
#include "Core.h"
#include "SceneManager.h"
#include "SiChuanShengScene.h"

Block::Block()
{
	m_rect = {};
	m_bSelect = false;
	m_eBlockType = TEXTURE_TYPE::CARD_001;
	m_pBlockTexture = nullptr;
	m_pSelectBlockTexture = nullptr;
}

Block::~Block()
{
}

void Block::Update()
{
	if (InputManager::GetInstance()->GetKeyState(VK_LBUTTON) == KEY_STATE::DOWN)
	{
		POINT ptMouse;
		GetCursorPos(&ptMouse);
		ScreenToClient(Core::GetInstance()->GethWnd(), &ptMouse);
		if (m_bSelect == false)
		{
			if (PtInRect(&m_rect, ptMouse) == true)
			{
				m_pSiChuanShengScene->CompareBlock(this);
			}
		}
	}
}

void Block::Init(Vector2 _vec2Position, TEXTURE_TYPE _eTexture_Type)
{
	m_pSiChuanShengScene = SceneManager::GetInstance()->GetSiChuanShengScene();
	assert(m_pSiChuanShengScene != nullptr);

	m_eBlockType = _eTexture_Type;
	m_pBlockTexture = ResourceManager::GetInstance()->LoadTexture(m_eBlockType);
	if ((int)m_eBlockType < (int)TEXTURE_TYPE::CARD_END)
	{
		TEXTURE_TYPE eSelectedType = (TEXTURE_TYPE)((int)m_eBlockType + (int)TEXTURE_TYPE::CARD_SELECTED_START);
		m_pSelectBlockTexture = ResourceManager::GetInstance()->LoadTexture(eSelectedType);
	}
	else
		m_pSelectBlockTexture = nullptr;

	m_bSelect = false;
}

void Block::SetPosition(Vector2 _vec2Position)
{
	m_BoardPosition = _vec2Position;	
	Vector2 vec2Scale;
	vec2Scale.m_ix = m_pBlockTexture->GetWidth();
	vec2Scale.m_iy = m_pBlockTexture->GetHeight();
	Object::SetScale(vec2Scale);
	m_rect.left = BOARD_START::X + _vec2Position.m_ix * m_pBlockTexture->GetWidth() - (5 + _vec2Position.m_ix * 5);
	m_rect.top = BOARD_START::Y + _vec2Position.m_iy * m_pBlockTexture->GetHeight();
	m_rect.right = m_rect.left + m_pBlockTexture->GetWidth();
	m_rect.bottom = m_rect.top + m_pBlockTexture->GetHeight();
	Object::SetPosition(Vector2{ m_rect.left,m_rect.top });
}

void Block::Render(HDC _hDC)
{
	if (m_pSelectBlockTexture != nullptr && m_bSelect == true)
	{
		TransparentBlt(_hDC, m_rect.left, m_rect.top, m_pSelectBlockTexture->GetWidth(), m_pSelectBlockTexture->GetHeight(), m_pSelectBlockTexture->GetDC(),
			0, 0, m_pSelectBlockTexture->GetWidth(), m_pSelectBlockTexture->GetHeight(), RGB(255, 0, 255));
	}
	else
	{
		TransparentBlt(_hDC, m_rect.left, m_rect.top, m_pBlockTexture->GetWidth(), m_pBlockTexture->GetHeight(), m_pBlockTexture->GetDC(),
			0, 0, m_pBlockTexture->GetWidth(), m_pBlockTexture->GetHeight(), RGB(255, 0, 255));
	}
}
