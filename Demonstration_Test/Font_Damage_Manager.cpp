#include "stdafx.h"
#include "Font_Damage_Manager.h"
#include "Font_Damage.h"

CFont_Damage_Manager* CFont_Damage_Manager::m_pInstance = nullptr;
CFont_Damage_Manager::CFont_Damage_Manager()
{
}

CFont_Damage_Manager::~CFont_Damage_Manager()
{
	Release_Font_Damage_Manage();
}

void CFont_Damage_Manager::Ready_Font_Damage_Manager()
{

}

void CFont_Damage_Manager::Update_Font_Damage_Manager()
{
	for (auto& iter = m_listFontDamage.begin(); iter != m_listFontDamage.end();)
	{
		int iEvent = (*iter)->Update_Font_Damage();
		if (OBJ_DEAD == iEvent)
		{
			Safe_Delete(*iter);
			iter = m_listFontDamage.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

void CFont_Damage_Manager::Render_Font_Damage_Manager(HDC hDC)
{
	for (auto& iter = m_listFontDamage.begin(); iter != m_listFontDamage.end(); iter++)
	{
		(*iter)->Render_Font_Damage(hDC);
	}
}

void CFont_Damage_Manager::Release_Font_Damage_Manage()
{
	for (auto& pFont : m_listFontDamage)
	{
		Safe_Delete(pFont);
	}
	m_listFontDamage.clear();
}
