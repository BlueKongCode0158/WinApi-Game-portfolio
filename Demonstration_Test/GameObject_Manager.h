#pragma once

class CGameObject;
class CGameObject_Manager
{
public:
	static CGameObject_Manager* Get_Instacne()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CGameObject_Manager;
		}
		return m_pInstance;
	}
	static void Release_Instance()
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
public:
	CGameObject* Get_Player() 
	{ 
		if (!m_listGameObject[GAMEOBJECT::UPDATE_ID::PLAYER].empty())
		{
			return m_listGameObject[GAMEOBJECT::UPDATE_ID::PLAYER].front();
		}
		return nullptr;
	}
	list<CGameObject*>* Get_List(GAMEOBJECT::UPDATE_ID eID)
	{
		if (!m_listGameObject[eID].empty())
		{
			return &m_listGameObject[eID];
		}
		return nullptr;
	}
	CGameObject* Get_Boss()
	{
		if (!m_listGameObject[GAMEOBJECT::UPDATE_ID::BOSS].empty())
		{
			return m_listGameObject[GAMEOBJECT::UPDATE_ID::BOSS].front();
		}
		return nullptr;
	}
public:
	void Add_Game_Object_Manager(CGameObject* pAdd, GAMEOBJECT::UPDATE_ID eNum)
	{
		m_listGameObject[eNum].emplace_back(pAdd);
	}
	void Save_Data_Monster();
	void Load_Data_Monster();
	void Save_Data_Prob();
	void Load_Data_Prob();
public:		//충돌 되는 부분 나눠준 곳
	void Collision_Shield();
	void Collision_ShieldHit();
	void Collision_TileArrow();
	void Collision_Monster();
	
	void Collision_Monster_Slash();
	void Collision_Boss_Slash();

	void Collision_IceSpin();
	void Collision_IceSpin_Attack();

public:
	void Collision_ShieldHit_Monster();
	void Collision_ShieldHit_Boss();
	void Collision_IceSpin_Monster();
	void Collision_IceSpin_Boss();
public:
	void Update_GameObject_Manager();
	void Render_GameObject_Manager(HDC hDC);
	void Release_GameObject_Manager();
public:
	void Collision_Rect_Delete(RECT& rRect);
	void Collision_Rect_Delete_PRob(RECT& rRECT);
private:
	CGameObject_Manager();
	~CGameObject_Manager();
public:
	static CGameObject_Manager* m_pInstance;
private:
	list<CGameObject*> m_listGameObject[GAMEOBJECT::UPDATE_ID::UPDATE_END];
	list<CGameObject*> m_listGameObjectSortRender;
};