#pragma once


struct Vector2
{
	int m_ix;
	int m_iy;

	Vector2()
	{
		m_ix = 0;
		m_iy = 0;
	}
	Vector2(int _ix, int _iy)
	{
		m_ix = _ix;
		m_iy = _iy;
	}	
	bool operator==(Vector2 vec)
	{
		return m_ix == vec.m_ix && m_iy == vec.m_iy;
	}
	bool operator!=(Vector2 vec)
	{
		return m_ix != vec.m_ix || m_iy != vec.m_iy;
	}
	bool operator<(const Vector2& vec) const
	{
		if (m_iy != vec.m_iy)
			return m_iy < vec.m_iy;
		return m_ix < vec.m_ix;
	}
	Vector2 operator+(Vector2 vec)
	{
		return Vector2{ m_ix + vec.m_ix ,m_iy + vec.m_iy };
	}
	void operator+=(Vector2 vec)
	{
		m_ix += vec.m_ix;
		m_iy += vec.m_iy;
	}
	int GetDistance(Vector2 other)
	{
		return abs(m_ix - other.m_ix) + abs(m_iy - other.m_iy);
	}
};