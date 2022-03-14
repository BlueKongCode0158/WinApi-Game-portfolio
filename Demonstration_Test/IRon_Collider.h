#pragma once
#include "Collider.h"

class CIRon_Collider final
	:public CCollider
{
private:
	CIRon_Collider();
public:
	virtual ~CIRon_Collider();
public:
	static CCollider* Create();
public:
	// CCollider을(를) 통해 상속됨
	virtual int Ready_Collider() override;
	virtual int Update_Collider() override;
	virtual void Render_Collider(HDC hDC) override;
	virtual void Release_Collider() override;
private:
	DWORD m_dwCount;
};