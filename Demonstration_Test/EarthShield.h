#pragma once
#include "Skil.h"

class CEarthShield final
	:public CSkil
{
private:
	CEarthShield();
public:
	~CEarthShield();
public: // 생성관련
	static CSkil* Create();
	static CSkil* Create(LPVOID pVoid);
	static CSkil* Create(TFPOINT& rPoint);
	static CSkil* Create(float fAngle);
private:
	void Set_Point(TFPOINT& rPoint)
	{
		m_tPoint.fX = rPoint.fX;
		m_tPoint.fY = rPoint.fY;
	}
public:
	// CSkil을(를) 통해 상속됨
	virtual int Ready_Skil() override;
	virtual int Update_Skil() override;
	virtual void Render_Skil(HDC hDC) override;
	virtual void Release_Skil() override;
private:
	DWORD m_dwShildTime;
};