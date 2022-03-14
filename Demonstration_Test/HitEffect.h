#pragma once
#include "Effect.h"

class CHitEffect final
	:public CEffect
{
private:
	CHitEffect();
public:
	virtual ~CHitEffect();
public:
	static CEffect* Create();
public:
	// CEffect을(를) 통해 상속됨
	virtual int Ready_Effect() override;
	virtual int Update_Effect() override;
	virtual void Late_Update_Effect() override;
	virtual void Render_Effect(HDC hDC) override;
	virtual void Release_Effect() override;

};