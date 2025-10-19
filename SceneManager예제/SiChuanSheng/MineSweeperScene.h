#pragma once
#include"Scene.h"



class Texture;
class Mine;

class MineSweeperScene : public Scene
{
	static constexpr int BOARD_HEIGHT = 30;
	static constexpr int BOARD_WIDTH = 16;
	static constexpr int NUM_OF_BOMBS = 48;

	enum class GAMESTATE
	{
		PREGAME,
		PLAY,
		WIN,
		LOSE
	};

	enum OBJECT_GROUP
	{
		BLOCK,
		END,
	};

private:
	Texture*				m_pBackBoard;
	GAMESTATE				m_GameState;
	int						m_iNumOfFlags;
	Mine*					m_Board[BOARD_HEIGHT][BOARD_WIDTH];

public:
	MineSweeperScene(std::string _strName);
	~MineSweeperScene();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC _memDC) override;

	// 보드 관련 함수
	void InitBoard();
	void ReleaseBoard();
	void ShuffleBoard();

	// 게임 관련 함수
	int GetAdjMines(const Vector2 _pos);
	bool PositionOutOfBounds(const Vector2& _pos);
	void RevealMines();
	void RevealAdjBlocks(const Vector2 _vec2);

	bool WinCheck();
	void HandleBlockClicked(const Vector2 _vec2);
	void HandleBombClicked();
};

