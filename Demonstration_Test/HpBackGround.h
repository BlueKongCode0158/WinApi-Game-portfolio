#pragma once
#include "MyUI.h"

class CHpBackGround final
	:public CMyUI
{
private:
	CHpBackGround();
public:
	virtual ~CHpBackGround();
public:
	// CMyUI을(를) 통해 상속됨
	virtual int Ready_UI() override;
	virtual void Update_UI() override;
	virtual void Late_Update_UI() override;
	virtual void Render_UI(HDC hDC) override;
public:
	static CMyUI* Create();
};