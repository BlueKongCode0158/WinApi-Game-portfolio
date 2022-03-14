#pragma once

class CSkil;
class CSkil_Manager
{
public:
	static CSkil_Manager* Get_Instacne()
	{
		if (nullptr == pInstacne)
		{
			pInstacne = new CSkil_Manager;
		}
		return pInstacne;
	}
	void Release_Instance()
	{
		delete pInstacne;
		pInstacne = nullptr;
	}
private:
	CSkil_Manager();
	~CSkil_Manager();
public:
	void Add_Skil(CSkil* pSkil, GAMEOBJECT::UPDATE_SKIL eSkil)
	{
		m_listSkil[eSkil].emplace_back(pSkil);
	}
public:
	void Update_Skil();
	void Render_Skil(HDC hDC);
public:
	list<CSkil*>* Get_list(GAMEOBJECT::UPDATE_SKIL eID)
	{
		return &m_listSkil[eID];
	}
private:
	void Release_Skil();
private:
	static CSkil_Manager* pInstacne;
private:
	list<CSkil*> m_listSkil[GAMEOBJECT::UPDATE_SKIL::SKIL_END];
};