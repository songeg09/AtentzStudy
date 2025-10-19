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
	case TEXTURE_TYPE::CARD_000:						return "card_00.bmp";
	case TEXTURE_TYPE::CARD_001:						return "card_01.bmp";
	case TEXTURE_TYPE::CARD_002:						return "card_02.bmp";
	case TEXTURE_TYPE::CARD_003:						return "card_03.bmp";
	case TEXTURE_TYPE::CARD_004:						return "card_04.bmp";
	case TEXTURE_TYPE::CARD_005:						return "card_05.bmp";
	case TEXTURE_TYPE::CARD_006:						return "card_06.bmp";
	case TEXTURE_TYPE::CARD_007:						return "card_07.bmp";
	case TEXTURE_TYPE::CARD_008:						return "card_08.bmp";
	case TEXTURE_TYPE::CARD_009:						return "card_09.bmp";
	case TEXTURE_TYPE::CARD_010:						return "card_10.bmp";
	case TEXTURE_TYPE::CARD_011:						return "card_11.bmp";
	case TEXTURE_TYPE::CARD_012:						return "card_12.bmp";
	case TEXTURE_TYPE::CARD_013:						return "card_13.bmp";
	case TEXTURE_TYPE::CARD_014:						return "card_14.bmp";
	case TEXTURE_TYPE::CARD_015:						return "card_15.bmp";
	case TEXTURE_TYPE::CARD_016:						return "card_16.bmp";
	case TEXTURE_TYPE::CARD_017:						return "card_17.bmp";
	case TEXTURE_TYPE::CARD_018:						return "card_18.bmp";
	case TEXTURE_TYPE::CARD_019:						return "card_19.bmp";
	case TEXTURE_TYPE::CARD_020:						return "card_20.bmp";
	case TEXTURE_TYPE::CARD_021:						return "card_21.bmp";
	case TEXTURE_TYPE::CARD_022:						return "card_22.bmp";
	case TEXTURE_TYPE::CARD_023:						return "card_23.bmp";
	case TEXTURE_TYPE::CARD_024:						return "card_24.bmp";
	case TEXTURE_TYPE::CARD_025:						return "card_25.bmp";
	case TEXTURE_TYPE::CARD_026:						return "card_26.bmp";
	case TEXTURE_TYPE::CARD_027:						return "card_27.bmp";
	case TEXTURE_TYPE::CARD_028:						return "card_28.bmp";
	case TEXTURE_TYPE::CARD_029:						return "card_29.bmp";
	case TEXTURE_TYPE::CARD_030:						return "card_30.bmp";
	case TEXTURE_TYPE::CARD_031:						return "card_31.bmp";
	case TEXTURE_TYPE::CARD_032:						return "card_32.bmp";
	case TEXTURE_TYPE::CARD_033:						return "card_33.bmp";
	case TEXTURE_TYPE::CARD_034:						return "card_34.bmp";
	case TEXTURE_TYPE::CARD_035:						return "card_35.bmp";
	case TEXTURE_TYPE::CARD_036:						return "card_36.bmp";
	case TEXTURE_TYPE::CARD_037:						return "card_37.bmp";
	case TEXTURE_TYPE::CARD_038:						return "card_38.bmp";
	case TEXTURE_TYPE::CARD_039:						return "card_39.bmp";
	case TEXTURE_TYPE::CARD_040:						return "card_40.bmp";
	case TEXTURE_TYPE::CARD_041:						return "card_41.bmp";
	case TEXTURE_TYPE::CARD_042:						return "card_42.bmp";
	case TEXTURE_TYPE::CARD_043:						return "card_43.bmp";
	case TEXTURE_TYPE::CARD_000_SELECTED:			return "card_00_selected.bmp";
	case TEXTURE_TYPE::CARD_001_SELECTED:			return "card_01_selected.bmp";
	case TEXTURE_TYPE::CARD_002_SELECTED:			return "card_02_selected.bmp";
	case TEXTURE_TYPE::CARD_003_SELECTED:			return "card_03_selected.bmp";
	case TEXTURE_TYPE::CARD_004_SELECTED:			return "card_04_selected.bmp";
	case TEXTURE_TYPE::CARD_005_SELECTED:			return "card_05_selected.bmp";
	case TEXTURE_TYPE::CARD_006_SELECTED:			return "card_06_selected.bmp";
	case TEXTURE_TYPE::CARD_007_SELECTED:			return "card_07_selected.bmp";
	case TEXTURE_TYPE::CARD_008_SELECTED:			return "card_08_selected.bmp";
	case TEXTURE_TYPE::CARD_009_SELECTED:			return "card_09_selected.bmp";
	case TEXTURE_TYPE::CARD_010_SELECTED:			return "card_10_selected.bmp";
	case TEXTURE_TYPE::CARD_011_SELECTED:			return "card_11_selected.bmp";
	case TEXTURE_TYPE::CARD_012_SELECTED:			return "card_12_selected.bmp";
	case TEXTURE_TYPE::CARD_013_SELECTED:			return "card_13_selected.bmp";
	case TEXTURE_TYPE::CARD_014_SELECTED:			return "card_14_selected.bmp";
	case TEXTURE_TYPE::CARD_015_SELECTED:			return "card_15_selected.bmp";
	case TEXTURE_TYPE::CARD_016_SELECTED:			return "card_16_selected.bmp";
	case TEXTURE_TYPE::CARD_017_SELECTED:			return "card_17_selected.bmp";
	case TEXTURE_TYPE::CARD_018_SELECTED:			return "card_18_selected.bmp";
	case TEXTURE_TYPE::CARD_019_SELECTED:			return "card_19_selected.bmp";
	case TEXTURE_TYPE::CARD_020_SELECTED:			return "card_20_selected.bmp";
	case TEXTURE_TYPE::CARD_021_SELECTED:			return "card_21_selected.bmp";
	case TEXTURE_TYPE::CARD_022_SELECTED:			return "card_22_selected.bmp";
	case TEXTURE_TYPE::CARD_023_SELECTED:			return "card_23_selected.bmp";
	case TEXTURE_TYPE::CARD_024_SELECTED:			return "card_24_selected.bmp";
	case TEXTURE_TYPE::CARD_025_SELECTED:			return "card_25_selected.bmp";
	case TEXTURE_TYPE::CARD_026_SELECTED:			return "card_26_selected.bmp";
	case TEXTURE_TYPE::CARD_027_SELECTED:			return "card_27_selected.bmp";
	case TEXTURE_TYPE::CARD_028_SELECTED:			return "card_28_selected.bmp";
	case TEXTURE_TYPE::CARD_029_SELECTED:			return "card_29_selected.bmp";
	case TEXTURE_TYPE::CARD_030_SELECTED:			return "card_30_selected.bmp";
	case TEXTURE_TYPE::CARD_031_SELECTED:			return "card_31_selected.bmp";
	case TEXTURE_TYPE::CARD_032_SELECTED:			return "card_32_selected.bmp";
	case TEXTURE_TYPE::CARD_033_SELECTED:			return "card_33_selected.bmp";
	case TEXTURE_TYPE::CARD_034_SELECTED:			return "card_34_selected.bmp";
	case TEXTURE_TYPE::CARD_035_SELECTED:			return "card_35_selected.bmp";
	case TEXTURE_TYPE::CARD_036_SELECTED:			return "card_36_selected.bmp";
	case TEXTURE_TYPE::CARD_037_SELECTED:			return "card_37_selected.bmp";
	case TEXTURE_TYPE::CARD_038_SELECTED:			return "card_38_selected.bmp";
	case TEXTURE_TYPE::CARD_039_SELECTED:			return "card_39_selected.bmp";
	case TEXTURE_TYPE::CARD_040_SELECTED:			return "card_40_selected.bmp";
	case TEXTURE_TYPE::CARD_041_SELECTED:			return "card_41_selected.bmp";
	case TEXTURE_TYPE::CARD_042_SELECTED:			return "card_42_selected.bmp";
	case TEXTURE_TYPE::CARD_043_SELECTED:			return "card_43_selected.bmp";
	case TEXTURE_TYPE::LINE_1:								return "Line1.bmp";
	case TEXTURE_TYPE::LINE_2:								return "Line2.bmp";
	case TEXTURE_TYPE::LINE_3:								return "Line3.bmp";
	case TEXTURE_TYPE::LINE_4:								return "Line4.bmp";
	case TEXTURE_TYPE::LINE_5:								return "Line5.bmp";
	case TEXTURE_TYPE::LINE_6:								return "Line6.bmp";
	case TEXTURE_TYPE::BACK_BOARD:					return "back_board.bmp";
	case TEXTURE_TYPE::TIMER_BLOCK:					return "timer_block.bmp";
	case TEXTURE_TYPE::SICHUANSHENG_BUTTON:		return "sichuansheng_button.bmp";
	case TEXTURE_TYPE::MINESWEEPER_BUTTON:		return "Minesweeper_button.bmp";
	case TEXTURE_TYPE::BACK:					return "back.bmp";
	case TEXTURE_TYPE::BLOCK:					return "block.bmp";
	case TEXTURE_TYPE::BLOCK_0:					return "block_0.bmp";
	case TEXTURE_TYPE::BLOCK_1:					return "block_1.bmp";
	case TEXTURE_TYPE::BLOCK_2:					return "block_2.bmp";
	case TEXTURE_TYPE::BLOCK_3:					return "block_3.bmp";
	case TEXTURE_TYPE::BLOCK_4:					return "block_4.bmp";
	case TEXTURE_TYPE::BLOCK_5:					return "block_5.bmp";
	case TEXTURE_TYPE::BLOCK_6:					return "block_6.bmp";
	case TEXTURE_TYPE::BLOCK_7:					return "block_7.bmp";
	case TEXTURE_TYPE::BLOCK_8:					return "block_8.bmp";
	case TEXTURE_TYPE::FLAG:					return "flag.bmp";
	case TEXTURE_TYPE::MINE:					return "mine.bmp";
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
