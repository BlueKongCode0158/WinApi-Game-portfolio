#pragma once
#include "Skil.h"

class CIceSpin final
	:public CSkil
{
private:
	CIceSpin();
public:
	virtual ~CIceSpin();
public:
	// CSkil을(를) 통해 상속됨
	virtual int Ready_Skil() override;
	virtual int Update_Skil() override;
	virtual void Render_Skil(HDC hDC) override;
	virtual void Release_Skil() override;
public:
	static CSkil* Create(float fAngle);
private:
	DWORD m_dwCreateTime;
	float m_fDistance;
};