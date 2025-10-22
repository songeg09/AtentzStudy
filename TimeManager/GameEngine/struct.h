#pragma once


struct Vector2
{
	float m_fx;
	float m_fy;

	Vector2()
	{
		m_fx = 0.0f;
		m_fy = 0.0f;
	}
	Vector2(float _fx, float _fy)
	{
		m_fx = _fx;
		m_fy = _fy;
	}

	void operator += (Vector2 _vec2)
	{
		m_fx += _vec2.m_fx;
		m_fy += _vec2.m_fy;
	}
};