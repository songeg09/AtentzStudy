#pragma once
#include "Object.h"

class Texture;

class Block
{
private:
	int			m_iAdjBombs;
	bool		m_bIsBomb;
	bool		m_bIsOpen;
	bool		m_bIsFlagged;

	Texture*	m_pTexture;
	RECT        m_ClickArea;
	Vector2     m_vec2Position;

public:
	Block(bool _IsBomb, Vector2 _pos);
	~Block();

	void Update();
	void Render(HDC _hDC);

	bool IsBomb() { return m_bIsBomb; }
	void SetBlock(int _AdjBombs);

	void Close() { m_bIsOpen = false; }
	void Open() { m_bIsOpen = true; }

};

