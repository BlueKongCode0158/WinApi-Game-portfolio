#pragma once

class CBitmap;
class CBitmap_Manager
{
public:
	static CBitmap_Manager* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CBitmap_Manager;
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
	CBitmap_Manager();
	~CBitmap_Manager();
public:
	static CBitmap_Manager* m_pInstance;
public:
	HDC FindImage(const TCHAR* pImageKey);
	void Insert_Bitmap(const TCHAR* pPath, const TCHAR* pImageKey);
	void Release_Bitmap();

private:
	map<const TCHAR*, CBitmap*>m_mapBmp;
};