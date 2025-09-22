#include "pch.h"
#include "Texture.h"
#include "Core.h"

Texture::Texture()
{
	m_BitMapInfo = {};
	m_hBitMap = nullptr;
	m_hDC = nullptr;
}

Texture::~Texture()
{

}

void Texture::Load(const std::wstring _strFileName)
{
	m_hBitMap = (HBITMAP)LoadImage(nullptr, _strFileName.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	m_hDC = CreateCompatibleDC(Core::GetInstance()->GetMainDC());

	HBITMAP hPrevBitMap = (HBITMAP)SelectObject(m_hDC, m_hBitMap);
	DeleteObject(hPrevBitMap);

	GetObject(m_hBitMap, sizeof(BITMAP), &m_BitMapInfo);
}