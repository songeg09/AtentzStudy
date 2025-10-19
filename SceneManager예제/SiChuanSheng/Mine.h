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
	static constexpr int BOARD_START_X = 43;
	static constexpr int BOARD_START_Y = 46;

	int			m_iAdjMines;
	bool		m_bIsMine;
	MINE_STATE	m_State;

	Texture*	m_pTexture;
	RECT        m_ClickArea;
	Vector2     m_vec2Position;

	std::function<void(Vector2)> m_LeftClickCallBackFunction;
	std::function<void(Vector2)> m_RightClickCallBackFunction;

public:
	Mine
	(
		bool _IsMine, 
		std::function<void(Vector2)> _LeftClickCallBackFunction, 
		std::function<void(Vector2)> _RighttClickCallBackFunction
	);
	~Mine();

	virtual void Update() override;
	virtual void Render(HDC _memDC) override;
	virtual void Init(Vector2 _vec2Position, TEXTURE_TYPE _eTexture_Type) override;
	

	// Getters & Setters
	bool IsMine() { return m_bIsMine; }
	int GetAdjMines() { return m_iAdjMines; }
	Vector2 GetPosition() { return m_vec2Position; }
	MINE_STATE GetState() { return m_State; }

	void SetTexture(int _AdjBombs);
	void SetPosition(const Vector2 _vec2);
	void SetState(MINE_STATE _state) { m_State = _state; }
};

