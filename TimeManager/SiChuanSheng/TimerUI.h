#pragma once
#include"ResourceManager.h"
#include"Object.h"

class TimerUI : public Object
{
	enum
	{
		SECOND = 1000,
		MAX_TIME = SECOND * 60,
	};
private:
	Texture* m_pTimerBar;
	Vector2 m_vec2Position;
	int m_iCurTime;
	int m_iCheckTime;
public:
	TimerUI();
	~TimerUI();

	virtual void Init(Vector2 _vec2Position, TEXTURE_TYPE _eTexture_Type) {};
	void Init();
	void Render(HDC _hDC);
	void Update();
	bool TimeCheck();
	void TimeUp()
	{
		m_iCurTime += SECOND * 5;
		if (m_iCurTime > MAX_TIME)
			m_iCurTime = MAX_TIME;
	}

};

