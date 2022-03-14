#pragma once

class CScene;
class CScene_Manager final
{
public:
	enum ID {SCENE_START, SCENE_HOME, SCENE_PLAZA, SCENE_DUNGEON, SCENE_EDIT, SCENE_END};
public:
	static CScene_Manager* Get_Instance()
	{
		if (nullptr == m_pInstance)
		{
			m_pInstance = new CScene_Manager;
		}
		return m_pInstance;
	}
	static void Release_Instance()
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
private:
	CScene_Manager();
	~CScene_Manager();
public:
	void Scene_Change(ID eNextID);
	void Update_Scene_Manager();
	void Render_Scene_Manager(HDC hDC);
	void Release_Scene_Manager();
private:
	static CScene_Manager* m_pInstance;
private:
	CScene* m_pScene;
	ID m_eCurScene;
	ID m_eNextScene;
};