#pragma once

class CMyUI abstract
{
public:
	CMyUI();
	virtual ~CMyUI();
public:
	virtual int Ready_UI() = 0;
	virtual void Update_UI() = 0;
	virtual void Late_Update_UI() = 0;
	virtual void Render_UI(HDC hDC) = 0;
public:
	void SetPos(float fX, float fY)
	{ 
		m_tPoint.fX = fX;
		m_tPoint.fY = fY;
	}
protected:
	void Update_RECT();
protected:
	RECT m_tRECT;
	TPOINT m_tPoint;
};