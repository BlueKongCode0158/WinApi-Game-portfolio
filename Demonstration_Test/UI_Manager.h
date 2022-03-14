#pragma once

class CMyUI;
class CUI_Manager final
{
public:
	static CUI_Manager* Get_Instance()
	{
		if (nullptr == m_pInstance)
		{
			m_pInstance = new CUI_Manager;
		}
		return m_pInstance;
	}
	static void CUI_Release_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
public:
	void Add_UI_Object(CMyUI* pUI, UI_OBJECT::START_ID eID)
	{
		m_listUI_LOAD[eID].emplace_back(pUI);
	}
	void Add_UI_Object(CMyUI* pUI, UI_OBJECT::GAME_ID eID)
	{
		m_listUI[eID].emplace_back(pUI);
	}
	void Delete_UI(UI_OBJECT::START_ID eID)
	{
		for (auto& iter = m_listUI_LOAD[eID].begin(); iter != m_listUI_LOAD[eID].end(); iter++)
			Safe_Delete(*iter);
		m_listUI[eID].clear();
	}
public:
	//void Ready_UI_Manager();
	void Update_UI_Manager();
	void Render_UI_Manager(HDC hDC);
	void Release_UI_Manager();
	void Update_UI_LOAD_Manager();
	void Render_UI_LOAD_Manager(HDC hDC);
private:
	CUI_Manager();
	~CUI_Manager();
private:
	static CUI_Manager* m_pInstance;
public:
	list<CMyUI*> m_listUI[UI_OBJECT::GAME_ID::GAME_UI_END];
	list<CMyUI*> m_listUI_LOAD[UI_OBJECT::START_ID::END];
};