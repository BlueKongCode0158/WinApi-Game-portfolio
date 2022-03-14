#pragma once

class CMyMouse;
class CMyMouse_Manager final
{
public:
	static CMyMouse_Manager* Get_Instance()
	{
		if (nullptr == m_pInstance)
		{
			m_pInstance = new CMyMouse_Manager;
		}
		return m_pInstance;
	}
	static void Release_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	CMyMouse_Manager();
	~CMyMouse_Manager();
private:
	static CMyMouse_Manager* m_pInstance;
public:
	void Ready_MyMouse_Manager();
	void Update_MyMouse_Manager();
	void Render_MyMouse_Manager(HDC hDC);
private:
	CMyMouse* m_pMouse;
};