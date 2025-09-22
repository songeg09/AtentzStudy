#pragma once
#include"GameResource.h"
class Texture : public GameResource
{
private:
	HDC m_hDC;
	HBITMAP m_hBitMap;
	BITMAP m_BitMapInfo;
public:
	Texture();
	~Texture();
	void Load(const std::wstring _strFileName);
	HDC GetDC() { return m_hDC; }
	int GetWidth() { return m_BitMapInfo.bmWidth; }
	int GetHeight() { return m_BitMapInfo.bmHeight; }

};

