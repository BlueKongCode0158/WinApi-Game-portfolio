#pragma once
#include "MyUI.h"

class CKey_Manager;
class CMyButton final
	:public CMyUI
{
private:
	CMyButton();
public:
	virtual ~CMyButton();
public:
	virtual int Ready_UI() override;
	virtual void Update_UI() override;
	virtual void Late_Update_UI() override;
	virtual void Render_UI(HDC hDC) override;
private:
	void Set_pKey(const TCHAR* pKey)
	{
		m_pKey = pKey;
	}
public:
	static CMyUI* Create(const TCHAR* pVoid);
private:
	const TCHAR* m_pKey;
	LOGFONT m_logFont;
	HFONT m_hFont;
	HFONT HOldFont;
	DWORD m_dwFontSize;
};