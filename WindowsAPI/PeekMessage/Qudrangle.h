#pragma once
#include "Shape.h"

class Qudrangle : public Shape
{
public:
	Qudrangle(HDC _hdc, POINT _pt, COLOR _color);

	virtual void Draw() override;

};

