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
	Vector2 operator - (Vector2 _vec2)
	{
		return Vector2(m_fx - _vec2.m_fx, m_fy - _vec2.m_fy);
	}
	Vector2 operator + (Vector2 _vec2)
	{
		Vector2 value;
		value.m_fx = m_fx + _vec2.m_fx;
		value.m_fy = m_fy + _vec2.m_fy;
		return value;
	}

	Vector2 operator * (float f)
	{
		Vector2 value;
		value.m_fx = m_fx * f;
		value.m_fy = m_fy * f;
		return Vector2(m_fx * f, m_fy * f);
	}

	float Length()
	{
		return sqrt(m_fx * m_fx + m_fy * m_fy);
	}
	void Normalize()
	{
		float length = Length();

		if (length == 0.0f) return;

		assert(length != 0.0f);
		m_fx /= length;
		m_fy /= length;
	}
};