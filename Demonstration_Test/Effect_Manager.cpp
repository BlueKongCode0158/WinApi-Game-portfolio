#include "stdafx.h"
#include "Effect_Manager.h"
#include "Effect.h"



CEffect_Manager* CEffect_Manager::pInstance = nullptr;
void CEffect_Manager::Ready_Effect_Manager()
{
}

void CEffect_Manager::Update_Effect_Manager()
{
	for (int i = 0; i < EffectID::EFFECT_END; i++)
	{
		for (auto& iter = m_listEffect[i].begin(); iter != m_listEffect[i].end();)
		{
			int iEvent = (*iter)->Update_Effect();
			if (OBJ_DEAD == iEvent)
			{
				Safe_Delete(*iter);
				iter = m_listEffect[i].erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}

	for (int i = 0; i < EffectID::EFFECT_END; i++)
	{
		for (auto& iter = m_listEffect[i].begin(); iter != m_listEffect[i].end(); iter++)
		{
			(*iter)->Late_Update_Effect();
		}
	}
}

void CEffect_Manager::Render_Effect_Manager(HDC hDC)
{
	for (int i = 0; i < EffectID::EFFECT_END; i++)
	{
		for (auto& iter = m_listEffect[i].begin(); iter != m_listEffect[i].end(); iter++)
		{
			(*iter)->Render_Effect(hDC);
		}
	}
}

void CEffect_Manager::Release_Effect_Manager()
{
	for (int i = 0; i < EffectID::EFFECT_END; i++)
	{
		for (auto& iter = m_listEffect[i].begin(); iter != m_listEffect[i].end(); iter++)
		{
			Safe_Delete(*iter);
		}
		m_listEffect[i].clear();
	}
}
