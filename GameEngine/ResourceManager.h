#pragma once
class Texture;
class ResourceManager
{
	SINGLETON(ResourceManager)
private:
	std::map<std::wstring, Texture*> m_MapTexture;
public:
	Texture* LoadTexture(const std::wstring& _strKey, const std::wstring& _strRelativePath);
	Texture* FindTexture(const std::wstring& _strKey, const std::wstring& _strRelativePath);

};

