#include "stdafx.h"
#include "Bitmap_Manager.h"
#include "Bitmap.h"

CBitmap_Manager* CBitmap_Manager::m_pInstance = nullptr;
CBitmap_Manager::CBitmap_Manager()
{
}

CBitmap_Manager::~CBitmap_Manager()
{
}

HDC CBitmap_Manager::FindImage(const TCHAR * pImageKey)
{
	auto& iter_find = m_mapBmp.find(pImageKey);
	// == map<const TCHAR*, CBitmap*>::iterator iter_find = m_mapBmp.find(pImageKey);

	if (iter_find == m_mapBmp.end())
	{
		return nullptr;
	}

	return iter_find->second->Get_MemDC();
}

void CBitmap_Manager::Insert_Bitmap(const TCHAR * pPath, const TCHAR * pImageKey)
{
	auto& iter_find = m_mapBmp.find(pImageKey);
	// == map<const TCHAR*, CBitmap*>::iterator iter_find = m_mapBmp.find(pImageKey);

	if (iter_find != m_mapBmp.end())
	{
		return;
	}

	CBitmap* pBitMap = new CBitmap;
	pBitMap->Insert_Bitmap(pPath);

	m_mapBmp.emplace(pImageKey, pBitMap);
}

void CBitmap_Manager::Release_Bitmap()
{
	for (auto& rPair : m_mapBmp)
	{
		Safe_Delete(rPair.second);
	}
	m_mapBmp.clear();
}
