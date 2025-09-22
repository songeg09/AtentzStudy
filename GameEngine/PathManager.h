#pragma once
class PathManager
{
	SINGLETON(PathManager)

private:
	WCHAR m_szContentsPath[512];
public:
	void Init();
	const std::wstring GetContentPath() { return m_szContentsPath; }
};

