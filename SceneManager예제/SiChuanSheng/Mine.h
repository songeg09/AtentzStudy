#pragma once
#include"ResourceManager.h"
#include "Object.h"

enum MINE_STATE
{
	OPEN,
	CLOSE,
	FLAGGED
};

enum ACTION_RESULT
{
	ACTION_OPEN,
	ACTION_FLAG,
	ACTION_UNFLAG,
	ACTION_NOTHING,
};

class Texture;
class Mine : public Object
{
private:
	int			m_iAdjBombs;
	bool		m_bIsBomb;
	MINE_STATE m_State;

	Texture*	m_pTexture;
	RECT        m_ClickArea;
	Vector2     m_vec2Position;

public:
	Mine(bool _IsBomb);
	~Mine();

	virtual void Update();
	virtual void Render(HDC _memDC);
	virtual void Init(Vector2 _vec2Position, TEXTURE_TYPE _eTexture_Type);
	virtual void SetPosition(Vector2 _vec2Position);
};

