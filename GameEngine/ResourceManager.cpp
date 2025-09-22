#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "PathManager.h"

ResourceManager::ResourceManager()
{
	LoadTexture(L"����", L"luffy.bmp");
	LoadTexture(L"����", L"zoro.bmp");
	LoadTexture(L"����", L"nami.bmp");
	LoadTexture(L"���", L"usopp.bmp");
	LoadTexture(L"���", L"sanji.bmp");
	LoadTexture(L"���ڷκ�", L"nico_robin.bmp");
	LoadTexture(L"���", L"vivi.bmp");
	LoadTexture(L"��ũ��", L"shanks.bmp");
	LoadTexture(L"���̽�", L"ace.bmp");
	LoadTexture(L"����", L"buggy.bmp");
	LoadTexture(L"������", L"gold_roger.bmp");
	LoadTexture(L"����", L"chopper.bmp");
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
