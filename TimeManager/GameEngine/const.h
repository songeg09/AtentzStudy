#pragma once
#include<string>
namespace ConstValue
{
	static const float fArrow_Speed = 100.0f;
	static const std::wstring strResourcePath = L"\\bin\\content\\";
	static const std::wstring strTexturePath = L"texture\\";
	static const Vector2 vec2PlayerFirePosition = { 18.0f,35.0f };
	static const float fAnimationPlayerSpeed = 0.1f;
	static const Vector2 vec2GameSceneWindowSize = { 1000.0f,562.0f };
	static const Vector2 vec2PlayerStartPosition = { vec2GameSceneWindowSize.m_fx * 0.5f,vec2GameSceneWindowSize.m_fy * 0.5f };
}