#pragma once
#include "Shape.h"

class Triangle : public Shape
{
private:
	void DrawLine(HDC hdc, POINT p1, POINT p2);

public:
	Triangle(HDC _hdc, POINT _pt, COLOR _color);

	virtual void Draw() override;
};

