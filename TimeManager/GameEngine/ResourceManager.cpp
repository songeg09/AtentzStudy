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

std::wstring ResourceManager::GetTextureFileName(TEXTURE_TYPE _eTextureType, DIRECTION _eDirection)
{
	switch (_eTextureType)
	{
	case TEXTURE_TYPE::BACKGROUND:			return L"background.bmp";

	case TEXTURE_TYPE::PLAYER_IDLE_1:			return std::format(L"character_idle_{}_00.bmp", GetDirectionString(_eDirection));
	case TEXTURE_TYPE::PLAYER_IDLE_2:			return std::format(L"character_idle_{}_01.bmp", GetDirectionString(_eDirection));
	case TEXTURE_TYPE::PLAYER_IDLE_3:			return std::format(L"character_idle_{}_02.bmp", GetDirectionString(_eDirection));
	case TEXTURE_TYPE::PLAYER_IDLE_4:			return std::format(L"character_idle_{}_03.bmp", GetDirectionString(_eDirection));
	case TEXTURE_TYPE::PLAYER_IDLE_5:			return std::format(L"character_idle_{}_04.bmp", GetDirectionString(_eDirection));
	case TEXTURE_TYPE::PLAYER_IDLE_6:			return std::format(L"character_idle_{}_05.bmp", GetDirectionString(_eDirection));
	case TEXTURE_TYPE::PLAYER_IDLE_7:			return std::format(L"character_idle_{}_06.bmp", GetDirectionString(_eDirection));
	case TEXTURE_TYPE::PLAYER_IDLE_8:			return std::format(L"character_idle_{}_07.bmp", GetDirectionString(_eDirection));
																   
	case TEXTURE_TYPE::PLAYER_RUN_1:			return std::format(L"character_run_{}_00.bmp", GetDirectionString(_eDirection));
	case TEXTURE_TYPE::PLAYER_RUN_2:			return std::format(L"character_run_{}_01.bmp", GetDirectionString(_eDirection));
	case TEXTURE_TYPE::PLAYER_RUN_3:			return std::format(L"character_run_{}_02.bmp", GetDirectionString(_eDirection));
	case TEXTURE_TYPE::PLAYER_RUN_4:			return std::format(L"character_run_{}_03.bmp", GetDirectionString(_eDirection));
	case TEXTURE_TYPE::PLAYER_RUN_5:			return std::format(L"character_run_{}_04.bmp", GetDirectionString(_eDirection));
	case TEXTURE_TYPE::PLAYER_RUN_6:			return std::format(L"character_run_{}_05.bmp", GetDirectionString(_eDirection));
	case TEXTURE_TYPE::PLAYER_RUN_7:			return std::format(L"character_run_{}_06.bmp", GetDirectionString(_eDirection));
	case TEXTURE_TYPE::PLAYER_RUN_8:			return std::format(L"character_run_{}_07.bmp", GetDirectionString(_eDirection));
																   
	case TEXTURE_TYPE::PLAYER_ATTACK_1:			return std::format(L"character_attack_{}_00.bmp", GetDirectionString(_eDirection));
	case TEXTURE_TYPE::PLAYER_ATTACK_2:			return std::format(L"character_attack_{}_01.bmp", GetDirectionString(_eDirection));
	case TEXTURE_TYPE::PLAYER_ATTACK_3:			return std::format(L"character_attack_{}_02.bmp", GetDirectionString(_eDirection));
	case TEXTURE_TYPE::PLAYER_ATTACK_4:			return std::format(L"character_attack_{}_03.bmp", GetDirectionString(_eDirection));
	case TEXTURE_TYPE::PLAYER_ATTACK_5:			return std::format(L"character_attack_{}_04.bmp", GetDirectionString(_eDirection));

	case TEXTURE_TYPE::MONSTER_IDLE_1:			return std::format(L"monster2_{}_00.bmp", GetDirectionString(_eDirection));
	case TEXTURE_TYPE::MONSTER_IDLE_2:			return std::format(L"monster2_{}_01.bmp", GetDirectionString(_eDirection));
	case TEXTURE_TYPE::MONSTER_IDLE_3:			return std::format(L"monster2_{}_02.bmp", GetDirectionString(_eDirection));
	default: return L"";
	}
}

std::wstring ResourceManager::GetDirectionString(DIRECTION _eDirection)
{
	switch (_eDirection)
	{
	case DIRECTION::LEFT:
		return L"left";
	case DIRECTION::RIGHT:
		return L"right";
	case DIRECTION::UP:
		return L"up";
	case DIRECTION::DOWN:
		return L"down";
	default:
		break;
	}
	return std::wstring();
}

Texture* ResourceManager::LoadTexture(TEXTURE_TYPE _eTextureType, DIRECTION _eDirection)
{
	std::wstring strFileName = GetTextureFileName(_eTextureType, _eDirection);
	assert(strFileName.length() != 0);

	std::wstring strKey = strFileName.substr(0, strFileName.length() - 4);

	Texture* pTexture = FindTexture(strKey);
	if (pTexture == nullptr)
	{
		pTexture = new Texture;
		std::wstring strPath = PathManager::GetInstance()->GetContentpath();
		strPath += ConstValue::strTexturePath + strFileName;
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
