#pragma once
#include "Effect.h"

class CCardEffect final
	: public CEffect
{
private:
	CCardEffect();
public:
	virtual ~CCardEffect();
public:
	// CEffect을(를) 통해 상속됨
	virtual int Ready_Effect() override;
	virtual int Update_Effect() override;
	virtual void Late_Update_Effect() override;
	virtual void Render_Effect(HDC hDC) override;
	virtual void Release_Effect() override;
public:
	void Set_Collision()
	{
		m_bCollision = true;
	}
private:
	void Collision_Player();

public:
	static CEffect* Create(TFPOINT& rPoint);
private:
	bool m_bCollision;
};