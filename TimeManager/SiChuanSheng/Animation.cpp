#include "pch.h"
#include "Animation.h"
#include "Texture.h"
#include "TimerManager.h"

Animation::Animation()
{
	m_vecList = {};
	m_eType = ANIMATION_TYPE::END;
	m_iCurIndex = 0;
	m_fAccTime = 0.0f;
	m_fSpeed = 0.0f;
}

Animation::~Animation()
{
}

void Animation::Reset()
{
	m_iCurIndex = 0;
	m_fAccTime = 0.0f;
}

void Animation::Init(std::vector<AnimNode> _vecList, ANIMATION_TYPE _eType, float _fSpeed, ANCHOR _eAnchor)
{
	m_vecList = _vecList;
	m_eType = _eType;
	m_fSpeed = _fSpeed;
	m_eAnchor = _eAnchor;
	m_iCurIndex = 0;
	m_fAccTime = 0.0f;
}

void Animation::Update()
{
	if (m_eType == ANIMATION_TYPE::ONCE && m_iCurIndex >= m_vecList.size() - 1)
		return;
	m_fAccTime += TimerManager::GetInstance()->GetfDeltaTime();
	if (m_fAccTime >= m_fSpeed)
	{
		++m_iCurIndex;
		if (m_eType == ANIMATION_TYPE::LOOP && m_iCurIndex >= m_vecList.size())
			m_iCurIndex = 0;
		m_fAccTime = 0;
		if (m_vecList[m_iCurIndex].m_callBack != nullptr)
			m_vecList[m_iCurIndex].m_callBack();
	}
}

void Animation::Render(HDC _memDC, Vector2 _vec2Position)
{
	int iWidth = m_vecList[m_iCurIndex].m_pTexture->GetWidth();
	int iHeight = m_vecList[m_iCurIndex].m_pTexture->GetHeight();
	switch (m_eAnchor)
	{
	case ANCHOR::CENTER:
		_vec2Position.m_fx -= iWidth / 2;
		_vec2Position.m_fy -= iHeight / 2;
		break;
	case ANCHOR::CENTER_BOTTOM:
		_vec2Position.m_fx -= iWidth / 2;
		_vec2Position.m_fy -= iHeight;
		break;
	case ANCHOR::CENTER_TOP:
		_vec2Position.m_fx -= iWidth / 2;
		break;
	}
	if (m_vecList.size() == 0)
		return;
	TransparentBlt(_memDC, _vec2Position.m_fx, _vec2Position.m_fy, iWidth, iHeight,
		m_vecList[m_iCurIndex].m_pTexture->GetDC(), 0, 0, iWidth, iHeight, RGB(255, 255, 255));
}
