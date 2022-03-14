#pragma once

class CEffect abstract
{
public:
	CEffect();
	virtual ~CEffect();
public:
	virtual	int Ready_Effect() = 0;
	virtual int Update_Effect() = 0;
	virtual void Late_Update_Effect() = 0;
	virtual void Render_Effect(HDC hDC) = 0;
	virtual void Release_Effect() = 0;
public:
	void Update_RECT();
	void Set_tPoint(TFPOINT& tPoint)
	{
		m_tPoint.fX = tPoint.fX;
		m_tPoint.fY = tPoint.fY;
	}
	void Set_tPoint(TPOINT& tPoint)
	{
		m_tPoint.fX = tPoint.fX;
		m_tPoint.fY = tPoint.fY;
	}
protected:
	TPOINT m_tPoint;
	RECT m_tRect;
	FRAME m_tFrame;
protected:
	MYSIZE m_tRecognizeSize;
	RECT m_tRect_Recognize;
};