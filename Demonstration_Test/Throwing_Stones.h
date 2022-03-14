#pragma once
#include "GameObject.h"

class CThrowing_Stones final
	:public CGameObject
{
private:
	CThrowing_Stones();
public:
	virtual ~CThrowing_Stones();
public:
	static CGameObject* Create();
public:
	// CGameObject을(를) 통해 상속됨
	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_GamceObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;
public:
	void Set_ShotTime(DWORD dwTime)
	{
		m_dwShotTime = dwTime;
	}
private:
	void Set_tShotPoint(float fX,float fY)
	{
		m_tShotPoint.fX = fX;
		m_tShotPoint.fY = fY;
	} //프레임이 변하는 순간 저장하면 되는거고
private:
	DWORD m_dwShotTime;
	DWORD m_dwGetick;
private:
	TFPOINT m_tShotPoint;
	float m_fAngle; //발사하는 각도 앵글
	bool m_bShotTarget;
};