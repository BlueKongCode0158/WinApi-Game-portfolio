#pragma once
#include "Effect.h"

class CSlashEffect final
	:public CEffect
{
private:
	CSlashEffect();
public:
	virtual ~CSlashEffect();
public:
	// CSkil��(��) ���� ��ӵ�
	virtual int Ready_Effect() override;
	virtual int Update_Effect() override;
	virtual void Late_Update_Effect() override;
	virtual void Render_Effect(HDC hDC) override;
	virtual void Release_Effect() override;
private:
public:
	static CEffect * Create(TPOINT * tPoint);
	HDC m_hMemDC;
};