#pragma once
#include "framework.h"
#include "Mecro.h"

class GDIManager
{
public:
	static GDIManager& GetInstance();
	void SetColor(HDC _hdc, COLOR _color);

private:
	GDIManager();
	~GDIManager();

	HPEN hBlackPen;
	HPEN hRedPen;
	HPEN hGreenPen;
	HPEN hBluePen;
	HPEN hWhitePen;

};

