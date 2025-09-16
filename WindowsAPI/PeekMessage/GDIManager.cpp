#include "GDIManager.h"


GDIManager& GDIManager::GetInstance()
{
	static GDIManager gdiManager;
	return gdiManager;
}

GDIManager::GDIManager()
{
	hBlackPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	hRedPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	hGreenPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	hBluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	hWhitePen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
}

GDIManager::~GDIManager()
{
}

void GDIManager::SetColor(HDC _hdc, COLOR _color)
{
	switch (_color)
	{
	case COLOR::BLACK:
		SelectObject(_hdc, hBlackPen);
		break;
	case COLOR::RED:
		SelectObject(_hdc, hRedPen);
		break;
	case COLOR::GREEN:
		SelectObject(_hdc, hGreenPen);
		break;
	case COLOR::BLUE:
		SelectObject(_hdc, hBluePen);
		break;
	case COLOR::WHITE:
		SelectObject(_hdc, hWhitePen);
		break;
	}
}