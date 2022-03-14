#pragma once
#include "GameObject.h"

class CEarth_Pillar final
	:public CGameObject
{
private:
	CEarth_Pillar();
public:
	virtual ~CEarth_Pillar();
public:
	// CGameObject을(를) 통해 상속됨
	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_GamceObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;
private:
	void Set_Angle(float fAngle)
	{
		m_fAngle = fAngle;
	}
	void Set_fDist(float fDist)
	{
		m_fDist = fDist;
	}
public:
	static CGameObject* Create(float fAngle, float fDist);
private:
	float m_fAngle;
	float m_fDist;
private:
	RECT m_tCollisionRect;
};