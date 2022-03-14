#pragma once
#include "MyUI.h"

class CTitle final
	:public CMyUI
{
private:
	CTitle();
public:
	virtual ~CTitle();
public:
	virtual int Ready_UI() override;
	virtual void Update_UI() override;
	virtual void Late_Update_UI() override;
	virtual void Render_UI(HDC hDC) override;
public:
	static CMyUI* Create();
	static CMyUI* Create(LPVOID pVoid);
};