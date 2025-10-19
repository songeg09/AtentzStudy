#pragma once
#include"ResourceManager.h"
#include"Object.h"

class Texture;
class SiChuanShengScene;
class Block : public Object
{
private:
	TEXTURE_TYPE		m_eBlockType;
	bool					m_bSelect;
	Texture*				m_pBlockTexture;
	Texture*				m_pSelectBlockTexture;
	RECT					m_rect;
	SiChuanShengScene* m_pSiChuanShengScene;
	Vector2				m_BoardPosition;
public:
	Block();
	~Block();
	virtual void Update();
	virtual void Render(HDC _memDC);
	virtual void Init(Vector2 _vec2Position, TEXTURE_TYPE _eTexture_Type);
	virtual void SetPosition(Vector2 _vec2Position);
	void Select() { m_bSelect = true; };
	void Cancle() { m_bSelect = false; };
	Vector2 GetBoardPosition() { return m_BoardPosition; }
	bool operator == (Block block)
	{
		return block.m_eBlockType == this->m_eBlockType;
	}
	bool operator != (Block block)
	{
		return block.m_eBlockType != this->m_eBlockType;
	}
};

