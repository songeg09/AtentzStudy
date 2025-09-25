#pragma once

struct Vector2
{
	float x;
	float y;
	Vector2()
	{
		x = 0.0f;
		y = 0.0f;
	}
	Vector2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}
	void operator+=(Vector2 _vec2)
	{
		x += _vec2.x;
		y += _vec2.y;
	}

	Vector2 operator+(const Vector2 _vec2)
	{
		return Vector2(x + _vec2.x, y + _vec2.y);
	}
};