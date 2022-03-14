#pragma once
#include "MyUI.h"

class CBossHp_Bar final
	:public CMyUI
{
private:
	CBossHp_Bar();
public:
	virtual ~CBossHp_Bar();
public:
	// CMyUI을(를) 통해 상속됨
	virtual int Ready_UI() override;
	virtual void Update_UI() override;
	virtual void Late_Update_UI() override;
	virtual void Render_UI(HDC hDC) override;
public:
	static CMyUI* Create();
private:
	LOGFONT m_logFont;
	HFONT m_hFont;
	HFONT HOldFont;
};