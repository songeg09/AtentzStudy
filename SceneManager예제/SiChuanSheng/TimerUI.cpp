#include "pch.h"
#include "TimerUI.h"
#include "Texture.h"

TimerUI::TimerUI()
{
	m_iCurTime = -1;
	m_pTimerBar = nullptr;
	m_vec2Position = {};
}

TimerUI::~TimerUI()
{
}

void TimerUI::Init()
{
	m_iCheckTime = clock();
	m_iCurTime = MAX_TIME;
	m_vec2Position = Vector2{ 80,515 };
	m_pTimerBar = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::TIMER_BLOCK);
}

void TimerUI::Render(HDC _hDC)
{
	int BlockMax = m_iCurTime / (SECOND * 5);
	for (int i = 0; i <= BlockMax; i++)
	{
		TransparentBlt(_hDC, m_vec2Position.m_ix + i * m_pTimerBar->GetWidth(), m_vec2Position.m_iy, m_pTimerBar->GetWidth(), m_pTimerBar->GetHeight(), m_pTimerBar->GetDC(),
			0, 0, m_pTimerBar->GetWidth(), m_pTimerBar->GetHeight(), RGB(255, 0, 255));
	}
}

void TimerUI::Update()
{
	m_iCurTime -= (clock() - m_iCheckTime);
	m_iCheckTime = clock();
}

bool TimerUI::TimeCheck()
{
	if (m_iCurTime <= 0)
		return false;
	return true;
}
