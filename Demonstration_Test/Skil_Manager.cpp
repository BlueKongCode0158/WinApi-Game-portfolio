#include "stdafx.h"
#include "Skil_Manager.h"
#include "Skil.h"

CSkil_Manager* CSkil_Manager::pInstacne = nullptr;

CSkil_Manager::CSkil_Manager()
{
}

CSkil_Manager::~CSkil_Manager()
{
	Release_Skil();
}

void CSkil_Manager::Update_Skil()
{
	for (int i = 0; i < GAMEOBJECT::UPDATE_SKIL::SKIL_END; i++)
	{
		for (auto& iter = m_listSkil[i].begin(); iter != m_listSkil[i].end();)
		{
			int iEvent = (*iter)->Update_Skil();
			if (iEvent == OBJ_DEAD)
			{
				Safe_Delete(*iter);
				iter = m_listSkil[i].erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}
}

void CSkil_Manager::Render_Skil(HDC hDC)
{
	for (int i = 0; i < GAMEOBJECT::UPDATE_SKIL::SKIL_END; i++)
	{
		for (auto& iter = m_listSkil[i].begin(); iter != m_listSkil[i].end(); iter++)
		{
			(*iter)->Render_Skil(hDC);
		}
	}
}

void CSkil_Manager::Release_Skil()
{
	for (int i = 0; i < GAMEOBJECT::UPDATE_SKIL::SKIL_END; i++)
	{
		for (auto& pObject : m_listSkil[i])
		{
			Safe_Delete(pObject);
		}
		m_listSkil[i].clear();
	}
}
