#pragma once
#include "pch.h"

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

	void Update(const POINT& pt);
	void Render(HDC _hDC);
	
	void SetupBlock(int _AdjBombs);
	void SetClickArea();

	void Close() { m_bIsOpen = false; }
	void Open() { m_bIsOpen = true; }

	// Getters & Setters
	bool IsBomb() { return m_bIsBomb; }
	Vector2 GetPosition() { return m_vec2Position; }
	void SetPosition(const Vector2 _vec2) { m_vec2Position = _vec2; }

};

