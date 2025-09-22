#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "PathManager.h"

ResourceManager::ResourceManager()
{
	LoadTexture(L"루피", L"luffy.bmp");
	LoadTexture(L"조로", L"zoro.bmp");
	LoadTexture(L"나미", L"nami.bmp");
	LoadTexture(L"우솝", L"usopp.bmp");
	LoadTexture(L"상디", L"sanji.bmp");
	LoadTexture(L"니코로빈", L"nico_robin.bmp");
	LoadTexture(L"비비", L"vivi.bmp");
	LoadTexture(L"샹크스", L"shanks.bmp");
	LoadTexture(L"에이스", L"ace.bmp");
	LoadTexture(L"버기", L"buggy.bmp");
	LoadTexture(L"골드로저", L"gold_roger.bmp");
	LoadTexture(L"쵸파", L"chopper.bmp");
}

ResourceManager::~ResourceManager()
{
	for (std::map<std::wstring, Texture*>::iterator iter = m_MapTexture.begin(); iter != m_MapTexture.end(); iter++)
	{
		delete iter->second;
	}
}

Texture* ResourceManager::LoadTexture(const std::wstring& _strKey, const std::wstring& _strRelativePath)
{
	std::wstring path = PathManager::GetInstance()->GetContentPath() + L"texture\\" + _strRelativePath;
	Texture* pTexture = FindTexture(_strKey, path);
	if (pTexture == nullptr)
	{
		pTexture = new Texture;
		pTexture->Load(path);
		pTexture->SetKey(_strKey);
		m_MapTexture.insert(make_pair(_strKey, pTexture));
	}

	return pTexture;
}

Texture* ResourceManager::FindTexture(const std::wstring& _strKey, const std::wstring& _strRelativePath)
{
	std::map<std::wstring, Texture*>::iterator iter = m_MapTexture.find(_strKey);
	if (iter == m_MapTexture.end())
		return nullptr;
	else
		return iter->second;
}
