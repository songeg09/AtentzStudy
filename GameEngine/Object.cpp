#include "Object.h"

Object::Object()
{
	m_vec2Position = {};
	m_vec2Scale = {};
}

Object::~Object()
{
}

void Object::Init(Vector2 _vec2Position, Vector2 _vec2Scale)
{
	m_vec2Position = _vec2Position;
	m_vec2Scale = _vec2Scale;
}
