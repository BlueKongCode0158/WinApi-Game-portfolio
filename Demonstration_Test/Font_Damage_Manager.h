#pragma once

class CFont_Damage;
class CFont_Damage_Manager
{
private:
	static CFont_Damage_Manager* m_pInstance;
private:
	CFont_Damage_Manager();
	~CFont_Damage_Manager();
public:
	static CFont_Damage_Manager* Get_Instance()
	{
		if (nullptr == m_pInstance)
		{
			m_pInstance = new CFont_Damage_Manager;
		}
		return m_pInstance;
	}
	void Release_Damage_Manager()
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
			//staitc이니까 이런 식으로 해주는건가?
		}
	}
public:
	void Add_Font_Damage(CFont_Damage* pFont)
	{
		m_listFontDamage.emplace_back(pFont);
	}
public:
	void Ready_Font_Damage_Manager();
	void Update_Font_Damage_Manager();
	void Render_Font_Damage_Manager(HDC hDC);
	void Release_Font_Damage_Manage();
private:
	list<CFont_Damage*> m_listFontDamage;
};