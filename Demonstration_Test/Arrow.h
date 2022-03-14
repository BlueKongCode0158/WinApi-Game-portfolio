#pragma once
#include "GameObject.h"

class CArrow final :
	public CGameObject
{
private:
	CArrow();
public:
	virtual ~CArrow();
public:
	// CGameObject��(��) ���� ��ӵ�
	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_GamceObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;
public:
	static CGameObject* Create(TFPOINT& rPoint);
	static CGameObject* Create();
protected:
	DWORD m_dwCreateTime;

	float m_fAngle;
};