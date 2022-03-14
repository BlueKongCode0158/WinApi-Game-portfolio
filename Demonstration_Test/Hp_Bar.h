#pragma once
#include "MyUI.h"

class CHp_Bar
	:public CMyUI
{
private:
	CHp_Bar();
public:
	virtual ~CHp_Bar();
public:
	// CMyUI을(를) 통해 상속됨
	virtual int Ready_UI() override;
	virtual void Update_UI() override;
	virtual void Late_Update_UI() override;
	virtual void Render_UI(HDC hDC) override;
public:
	static CMyUI* Create();
	static CMyUI* Create(int iHp);
private:
	int m_iHp;
	int m_iMaxHp;
	TCHAR m_szHp[32];
	LOGFONT m_logFont;
	HFONT m_hFont;
	HFONT HOldFont;

};