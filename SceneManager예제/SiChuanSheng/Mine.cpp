#include "pch.h"
#include "Mine.h"
#include "Texture.h"
#include "InputManager.h" 
#include "Core.h"

Mine::Mine(bool _IsMine, std::function<void(Vector2)> _LeftClickCallBackFunction, std::function<void(Vector2)> _RighttClickCallBackFunction)
	:m_iAdjMines(0),
	m_bIsMine(_IsMine),
	m_State(MINE_STATE::CLOSE),
	m_ClickArea({}),
	m_pTexture(nullptr),
	m_LeftClickCallBackFunction(_LeftClickCallBackFunction),
	m_RightClickCallBackFunction(_RighttClickCallBackFunction)
{
}

Mine::~Mine()
{
}

void Mine::Init(Vector2 _vec2Position, TEXTURE_TYPE _eTexture_Type)
{
	m_pTexture = ResourceManager::GetInstance()->LoadTexture(_eTexture_Type);
	SetPosition(_vec2Position);
}

void Mine::Update()
{
	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(Core::GetInstance()->GethWnd(), &ptMouse);

	if (PtInRect(&m_ClickArea, ptMouse))
	{
		if (InputManager::GetInstance()->GetKeyState(VK_LBUTTON) == KEY_STATE::DOWN)
		{
			if (m_State == MINE_STATE::OPEN || m_State == MINE_STATE::FLAGGED) return;

			m_LeftClickCallBackFunction(m_vec2Position);
		}
		else if (InputManager::GetInstance()->GetKeyState(VK_RBUTTON) == KEY_STATE::DOWN)
		{
			if (m_State == MINE_STATE::OPEN) return;

			m_RightClickCallBackFunction(m_vec2Position);
		}
	}

}

void Mine::Render(HDC _memDC)
{
	static Texture* m_pBackTextue = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::BLOCK);
	static Texture* m_pFlagTextue = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::FLAG);

	Texture* CurTexture;
	if (m_State == MINE_STATE::OPEN)
		CurTexture = m_pTexture;
	else if (m_State == MINE_STATE::FLAGGED)
		CurTexture = m_pFlagTextue;
	else
		CurTexture = m_pBackTextue;

	BitBlt(_memDC, m_ClickArea.left, m_ClickArea.top, m_ClickArea.right, m_ClickArea.bottom, CurTexture->GetDC(), 0, 0, SRCCOPY);
}

void Mine::SetTexture(int _AdjBombs)
{
	m_iAdjMines = _AdjBombs;

	if (m_bIsMine == true)
	{
		m_pTexture = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::MINE);
		return;
	}

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
		
}

void Mine::SetPosition(const Vector2 _vec2)
{
	static Texture* m_pBackTextue = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::BLOCK);
	m_vec2Position = _vec2;
	int x = BOARD_START_X + (m_vec2Position.m_ix * m_pBackTextue->GetWidth());
	int y = BOARD_START_Y + (m_vec2Position.m_iy * m_pBackTextue->GetHeight());

	m_ClickArea = {
		x,
		y,
		x + m_pTexture->GetWidth(),
		y + m_pTexture->GetHeight()
	};
}
