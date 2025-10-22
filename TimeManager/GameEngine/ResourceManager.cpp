#include "pch.h"
#include "ResourceManager.h"
#include "PathManager.h"
#include "Texture.h"

ResourceManager::ResourceManager()
{

}
ResourceManager::~ResourceManager()
{
	for (auto iter = m_MapTexture.begin(); iter != m_MapTexture.end(); iter++)
		delete iter->second;
}

std::wstring ResourceManager::GetTextureFileName(TEXTURE_TYPE _eTextureType)
{
	switch (_eTextureType)
	{
	case TEXTURE_TYPE::BACKGROUND:			return L"background.bmp";
	case TEXTURE_TYPE::PLAYER_ATTACK:		return L"atk_2_8.bmp";
	case TEXTURE_TYPE::PLAYER_IDLE_1:		return L"idle_1.bmp";
	case TEXTURE_TYPE::PLAYER_IDLE_2:		return L"idle_2.bmp";
	case TEXTURE_TYPE::PLAYER_IDLE_3:		return L"idle_3.bmp";
	case TEXTURE_TYPE::PLAYER_IDLE_4:		return L"idle_4.bmp";
	case TEXTURE_TYPE::PLAYER_IDLE_5:		return L"idle_5.bmp";
	case TEXTURE_TYPE::PLAYER_IDLE_6:		return L"idle_6.bmp";
	case TEXTURE_TYPE::PLAYER_IDLE_7:		return L"idle_7.bmp";
	case TEXTURE_TYPE::PLAYER_IDLE_8:		return L"idle_8.bmp";
	case TEXTURE_TYPE::PLAYER_IDLE_9:		return L"idle_9.bmp";
	case TEXTURE_TYPE::PLAYER_IDLE_10:		return L"idle_10.bmp";
	case TEXTURE_TYPE::PLAYER_IDLE_11:		return L"idle_11.bmp";
	case TEXTURE_TYPE::PLAYER_IDLE_12:		return L"idle_12.bmp";
	case TEXTURE_TYPE::PLAYER_ATTACK_1_1:	return L"attack_1_1.bmp";
	case TEXTURE_TYPE::PLAYER_ATTACK_1_2:	return L"attack_1_2.bmp";
	case TEXTURE_TYPE::PLAYER_ATTACK_1_3:	return L"attack_1_3.bmp";
	case TEXTURE_TYPE::PLAYER_ATTACK_1_4:	return L"attack_1_4.bmp";
	case TEXTURE_TYPE::PLAYER_ATTACK_1_5:	return L"attack_1_5.bmp";
	case TEXTURE_TYPE::PLAYER_ATTACK_1_6:	return L"attack_1_6.bmp";
	case TEXTURE_TYPE::PLAYER_ATTACK_1_7:	return L"attack_1_7.bmp";
	case TEXTURE_TYPE::PLAYER_ATTACK_1_8:	return L"attack_1_8.bmp";
	case TEXTURE_TYPE::PLAYER_ATTACK_1_9:	return L"attack_1_9.bmp";
	case TEXTURE_TYPE::PLAYER_ATTACK_1_10:	return L"attack_1_10.bmp";
	case TEXTURE_TYPE::PLAYER_ATTACK_1_11:	return L"attack_1_11.bmp";
	case TEXTURE_TYPE::PLAYER_ATTACK_1_12:	return L"attack_1_12.bmp";
	case TEXTURE_TYPE::PLAYER_ATTACK_1_13:	return L"attack_1_13.bmp";
	case TEXTURE_TYPE::PLAYER_ATTACK_1_14:	return L"attack_1_14.bmp";
	case TEXTURE_TYPE::PLAYER_ATTACK_1_15:	return L"attack_1_15.bmp";
	case TEXTURE_TYPE::ARROW:				return L"arrow.bmp";
	default: return L"";
	}
}

Texture* ResourceManager::LoadTexture(TEXTURE_TYPE _eTextureType)
{
	std::wstring strFileName = GetTextureFileName(_eTextureType);
	assert(strFileName.length() != 0);

	std::wstring strKey = strFileName.substr(0, strFileName.length() - 4);

	Texture* pTexture = FindTexture(strKey);
	if (pTexture == nullptr)
	{
		pTexture = new Texture;
		std::wstring strPath = PathManager::GetInstance()->GetContentpath();
		strPath += L"texture\\" + strFileName;
		pTexture->Load(strPath);
		pTexture->SetKey(strKey);
		pTexture->SetRelativePath(strFileName);
		m_MapTexture.insert(std::make_pair(strKey, pTexture));
	}
	return pTexture;
}

Texture* ResourceManager::FindTexture(const std::wstring& _strKey)
{
	std::map<std::wstring, Texture*>::iterator iter = m_MapTexture.find(_strKey);
	if (iter == m_MapTexture.end())
		return nullptr;
	else
		return iter->second;
}
