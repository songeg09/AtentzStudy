#pragma once
#include "pch.h"

enum BLOCK_STATE
{
	OPEN,
	CLOSE,
	FLAGGED
};

class Texture;
class Block
{
private:
	int			m_iAdjBombs;
	bool		m_bIsBomb;
	BLOCK_STATE m_State;

	Texture*	m_pTexture;
	RECT        m_ClickArea;
	Vector2     m_vec2Position;

public:
	Block(bool _IsBomb, Vector2 _pos);
	~Block();

	bool CursorOnBlock(const POINT& pt);
	void Render(HDC _hDC);
	
	void SetupBlock(int _AdjBombs);
	void SetClickArea();

	void Close() { m_State = BLOCK_STATE::CLOSE; }
	void Open() { m_State = BLOCK_STATE::OPEN; }

	// Getters & Setters
	bool IsBomb() { return m_bIsBomb; }
	int GetAdjBombs() { return m_iAdjBombs; }
	Vector2 GetPosition() { return m_vec2Position; }
	void SetPosition(const Vector2 _vec2) { m_vec2Position = _vec2; }
	BLOCK_STATE GetState() { return m_State; }
	void SetState(BLOCK_STATE _state) { m_State = _state; }

};

