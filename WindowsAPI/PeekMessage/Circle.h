#pragma once
#include "Shape.h"

class Circle : public Shape
{
public:
	Circle(HDC _hdc, POINT _pt, COLOR _color);

	virtual void Draw() override;
};

