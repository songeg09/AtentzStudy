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

std::string ResourceManager::GetTextureFileName(TEXTURE_TYPE _eTextureType)
{
	switch (_eTextureType)
	{
	case TEXTURE_TYPE::BACKGROUND:			return "background.bmp";
	case TEXTURE_TYPE::PLAYER_ATTACK:		return "atk_2_8.bmp";
	case TEXTURE_TYPE::PLAYER_IDLE_1:		return "idle_1.bmp";
	case TEXTURE_TYPE::PLAYER_IDLE_2:		return "idle_2.bmp";
	case TEXTURE_TYPE::PLAYER_IDLE_3:		return "idle_3.bmp";
	case TEXTURE_TYPE::PLAYER_IDLE_4:		return "idle_4.bmp";
	case TEXTURE_TYPE::PLAYER_IDLE_5:		return "idle_5.bmp";
	case TEXTURE_TYPE::PLAYER_IDLE_6:		return "idle_6.bmp";
	case TEXTURE_TYPE::PLAYER_IDLE_7:		return "idle_7.bmp";
	case TEXTURE_TYPE::PLAYER_IDLE_8:		return "idle_8.bmp";
	case TEXTURE_TYPE::PLAYER_IDLE_9:		return "idle_9.bmp";
	case TEXTURE_TYPE::PLAYER_IDLE_10:		return "idle_10.bmp";
	case TEXTURE_TYPE::PLAYER_IDLE_11:		return "idle_11.bmp";
	case TEXTURE_TYPE::PLAYER_IDLE_12:		return "idle_12.bmp";
	case TEXTURE_TYPE::PLAYER_ATTACK_1_1:	return "attack_1_1.bmp";
	case TEXTURE_TYPE::PLAYER_ATTACK_1_2:	return "attack_1_2.bmp";
	case TEXTURE_TYPE::PLAYER_ATTACK_1_3:	return "attack_1_3.bmp";
	case TEXTURE_TYPE::PLAYER_ATTACK_1_4:	return "attack_1_4.bmp";
	case TEXTURE_TYPE::PLAYER_ATTACK_1_5:	return "attack_1_5.bmp";
	case TEXTURE_TYPE::PLAYER_ATTACK_1_6:	return "attack_1_6.bmp";
	case TEXTURE_TYPE::PLAYER_ATTACK_1_7:	return "attack_1_7.bmp";
	case TEXTURE_TYPE::PLAYER_ATTACK_1_8:	return "attack_1_8.bmp";
	case TEXTURE_TYPE::PLAYER_ATTACK_1_9:	return "attack_1_9.bmp";
	case TEXTURE_TYPE::PLAYER_ATTACK_1_10:	return "attack_1_10.bmp";
	case TEXTURE_TYPE::PLAYER_ATTACK_1_11:	return "attack_1_11.bmp";
	case TEXTURE_TYPE::PLAYER_ATTACK_1_12:	return "attack_1_12.bmp";
	case TEXTURE_TYPE::PLAYER_ATTACK_1_13:	return "attack_1_13.bmp";
	case TEXTURE_TYPE::PLAYER_ATTACK_1_14:	return "attack_1_14.bmp";
	case TEXTURE_TYPE::PLAYER_ATTACK_1_15:	return "attack_1_15.bmp";
	case TEXTURE_TYPE::ARROW:				return "arrow.bmp";
	default: return "";
	}
}

Texture* ResourceManager::LoadTexture(TEXTURE_TYPE _eTextureType)
{
	std::string strFileName = GetTextureFileName(_eTextureType);
	assert(strFileName.length() != 0);

	std::string strKey = strFileName.substr(0, strFileName.length() - 4);

	Texture* pTexture = FindTexture(strKey);
	if (pTexture == nullptr)
	{
		pTexture = new Texture;
		std::string strPath = PathManager::GetInstance()->GetContentpath();
		strPath += "texture\\" + strFileName;
		pTexture->Load(strPath);
		pTexture->SetKey(strKey);
		pTexture->SetRelativePath(strFileName);
		m_MapTexture.insert(std::make_pair(strKey, pTexture));
	}
	return pTexture;
}

Texture* ResourceManager::FindTexture(const std::string& _strKey)
{
	std::map<std::string, Texture*>::iterator iter = m_MapTexture.find(_strKey);
	if (iter == m_MapTexture.end())
		return nullptr;
	else
		return iter->second;
}
