#pragma once
class GameResource
{
private:
	std::wstring m_strKey;
public:
	void SetKey(const std::wstring _strKey) { m_strKey = _strKey; }
	const std::wstring GetKey() { return m_strKey; }
	GameResource();
	~GameResource();
};

