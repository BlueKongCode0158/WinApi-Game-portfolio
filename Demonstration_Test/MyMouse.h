#pragma once

class CMyMouse final
{
private:
	CMyMouse();
public:
	~CMyMouse();
public:
	int Ready_MyMouse();
	void Update_MyMouse();
	void Late_MyMouse();
	void Render_MyMouse(HDC hDC);
	void Release_MyMouse();
public:
	static CMyMouse* Create();
	static CMyMouse* Create(LPVOID pVoid);
private:
	TPOINT m_tPoint;
	RECT   m_tRect;
};