#include "stdafx.h"
#include "MyUI.h"
#include "UI_Manager.h"
#include "GameObject.h"
#include "GameObject_Manager.h"


CUI_Manager* CUI_Manager::m_pInstance = nullptr;
CUI_Manager::CUI_Manager()
{
}

CUI_Manager::~CUI_Manager()
{
	Release_UI_Manager();
}

//void CUI_Manager::Ready_UI_Manager()
//{
//	for (int i = 0; i < UI_OBJECT::START_ID::END; i++)
//	{
//		for (auto& iter = m_listUI[i].begin(); iter != m_listUI[i].end(); iter++)
//		{
//			(*iter)->Ready_UI();
//		}
//	}
//} 우선 필요없으니까 주석

void CUI_Manager::Update_UI_Manager()
{
	CGameObject* pObj = CGameObject_Manager::Get_Instacne()->Get_Boss();
	if (nullptr == pObj)
	{
		for (auto& pBossHp : m_listUI[UI_OBJECT::GAME_ID::BOSSBACKGROUND])
		{
			Safe_Delete(pBossHp);
		}
		m_listUI[UI_OBJECT::GAME_ID::BOSSBACKGROUND].clear();
		
		for (auto& pBossHpBar : m_listUI[UI_OBJECT::GAME_ID::BOSSHP])
		{
			Safe_Delete(pBossHpBar);
		}
		m_listUI[UI_OBJECT::GAME_ID::BOSSHP].clear();
	}


	for (int i = 0; i < UI_OBJECT::GAME_ID::GAME_UI_END; i++)
	{
		if (!m_listUI[i].empty())
		{
			for (auto& iter = m_listUI[i].begin(); iter != m_listUI[i].end(); iter++)
			{
				if (iter == m_listUI[i].end())
					break;
				if (NULL == (*iter))
				{
					break;
				}
				(*iter)->Update_UI();
			}
		}
	}
	for (int i = 0; i < UI_OBJECT::GAME_ID::GAME_UI_END; i++)
	{
		if (!m_listUI[i].empty())
		{
			for (list<CMyUI*>::iterator iterBegin = m_listUI[i].begin();
				iterBegin != m_listUI[i].end();
				iterBegin++)
			{
				if (NULL != (*iterBegin))
				{
					(*iterBegin)->Late_Update_UI();
				}
				if (m_listUI[i].empty())
					break;
				else if ((m_listUI[i].size() == 0))
					break;
				else if (m_listUI[i].begin() == m_listUI[i].end())
					break;
			}
		}
	}

}
// 참조하는 거 잊지 않기. 매번 실수한다.

void CUI_Manager::Render_UI_Manager(HDC hDC)
{
	for (int i = 0; i < UI_OBJECT::GAME_ID::GAME_UI_END; i++)
	{
		if (!m_listUI[i].empty())
		{
			//auto& == list<CMyUI*>::iterator
			for (auto& iter = m_listUI[i].begin(); iter != m_listUI[i].end(); iter++)
			{
				if (*iter == NULL)
					break;
				(*iter)->Render_UI(hDC);
			}
		}
	}
}

void CUI_Manager::Release_UI_Manager()
{
	for (int i = 0; i < UI_OBJECT::GAME_ID::GAME_UI_END; i++)
	{
		if (!m_listUI[i].empty())
		{
			for (list<CMyUI*>::iterator iter = m_listUI[i].begin(); iter != m_listUI[i].end(); iter++)
			{
				delete (*iter);
				*iter = nullptr;
			}
		}
		m_listUI[i].clear();
	}

	for (int i = 0; i < UI_OBJECT::START_ID::END; i++)
	{
		if (!m_listUI_LOAD[i].empty())
		{
			for (list<CMyUI*>::iterator iter = m_listUI_LOAD[i].begin(); iter != m_listUI_LOAD[i].end(); iter++)
			{
				delete (*iter);
				*iter = nullptr;
			}
		}
		m_listUI_LOAD[i].clear();
	}
}

void CUI_Manager::Update_UI_LOAD_Manager()
{
	for (int i = 0; i < UI_OBJECT::START_ID::END; i++)
	{
		if (!m_listUI_LOAD[i].empty())
		{
			for (auto& iter = m_listUI_LOAD[i].begin(); iter != m_listUI_LOAD[i].end(); iter++)
			{
				if (iter == m_listUI_LOAD[i].end())
					break;
				(*iter)->Update_UI();
			}
		}
	}
	for (int i = 0; i < UI_OBJECT::START_ID::END; i++)
	{
		if (!m_listUI_LOAD[i].empty())
		{
			for (list<CMyUI*>::iterator iterBegin = m_listUI_LOAD[i].begin();
				iterBegin != m_listUI_LOAD[i].end();
				iterBegin++)
			{
				(*iterBegin)->Late_Update_UI();
				if (m_listUI_LOAD[i].empty())
					break;
				else if ((m_listUI_LOAD[i].size() == 0))
					break;
				else if (m_listUI_LOAD[i].begin() == m_listUI_LOAD[i].end())
					break;
			}
		}
	}
}

void CUI_Manager::Render_UI_LOAD_Manager(HDC hDC)
{
	for (int i = 0; i < UI_OBJECT::START_ID::END; i++)
	{
		if (!m_listUI_LOAD[i].empty())
		{
			//auto& == list<CMyUI*>::iterator
			for (auto& iter = m_listUI_LOAD[i].begin(); iter != m_listUI_LOAD[i].end(); iter++)
			{
				(*iter)->Render_UI(hDC);
			}
		}
	}
}
