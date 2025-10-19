#pragma once
#include"Scene.h"
#include"ResourceManager.h"
#include"Block.h"
#include"TimerUI.h"



struct Node
{

	enum DIRECTION
	{
		LEFT,
		UP,
		RIGHT,
		DOWN,
		END
	};
	int m_iF;
	int m_iG;
	Vector2 m_CurPosition;
	DIRECTION m_ePrevDirection;
	DIRECTION m_eNextDirection;
	int m_iRotateCount;

	bool operator<(const Node& node) const
	{
		if (m_CurPosition.m_iy != node.m_CurPosition.m_iy)
			return m_CurPosition.m_iy < node.m_CurPosition.m_iy;
		return m_CurPosition.m_ix < node.m_CurPosition.m_ix;
	}
	bool operator>(const Node& node) const
	{
		if (m_CurPosition.m_iy != node.m_CurPosition.m_iy)
			return m_CurPosition.m_iy > node.m_CurPosition.m_iy;
		return m_CurPosition.m_ix > node.m_CurPosition.m_ix;
	}
	bool operator==(const Node& node) const
	{
		return m_CurPosition.m_ix == node.m_CurPosition.m_ix && m_CurPosition.m_iy == node.m_CurPosition.m_iy;
	}
};

enum BOARD_START
{
	X = 20,
	Y = 80
};
class SiChuanShengScene : public Scene
{
	enum OBJECT_GROUP
	{
		DEFAULT,
		BLOCK,
		LOAD,
		END
	};
	enum
	{
		SHUFFLE_MAX = 10,
	};
	enum BOARD_SIZE
	{
		WIDTH = 20,
		HEIGHT = 10
	};
private:
	Block* m_Board[BOARD_SIZE::HEIGHT][BOARD_SIZE::WIDTH];
	std::vector<TEXTURE_TYPE> m_vecBlockList;
	Block* m_pFirstBlock;
	Block* m_pSecondBlock;
	std::list<Node> m_listPositionList;
	int		m_iOldClock;
	bool m_bLoadPrintStatus;

	Texture* m_pBackBoard;

	int		m_iScore;
	int		m_iShuffleCount;
	TimerUI m_TimerUI;
public:
	// Scene을(를) 통해 상속됨
	SiChuanShengScene(std::string _strName);
	~SiChuanShengScene();
	void Reset();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC _memDC) override;
	void BoardShuffle();
	void CreateLoad();
	void ReleaseLoad();
	void CompareBlock(Block* _pBlock);
	bool FindLoad(Vector2 _vec2Start, Vector2 _vec2End);
	bool CheckLoad(Vector2 _vec2Position);
	Vector2 GetFrontPosition(Node::DIRECTION _eDirection);
	void BoardRelease();
	void BoardSet();
	bool WinCheck();
};

