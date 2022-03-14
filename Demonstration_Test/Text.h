#pragma once
#include "MyUI.h"

class CText final
	:public CMyUI
{
private:
	CText();
public:
	virtual ~CText();
public:
	// CMyUI을(를) 통해 상속됨
	virtual int Ready_UI() override;
	virtual void Update_UI() override;
	virtual void Late_Update_UI() override;
	virtual void Render_UI(HDC hDC) override;
public:
	static CMyUI* Create();
	static CMyUI* Create(LPVOID pVoid);
private:
	LOGFONT m_logFont;
	HFONT m_hFont;
	HFONT HOldFont;
	DWORD m_Font_Color;
	bool m_bColorWhite;
	bool m_bColorBlack;
};