#pragma once
#include "MyUI.h"

class CPlayerImage final
	:public CMyUI
{
private:
	CPlayerImage();
public:
	virtual ~CPlayerImage();
public:
	// CMyUI을(를) 통해 상속됨
	virtual int Ready_UI() override;
	virtual void Update_UI() override;
	virtual void Late_Update_UI() override;
	virtual void Render_UI(HDC hDC) override;
public:
	static CMyUI* Create();
	TFrame m_tFrame;
	TCHAR* PlayerKey;
};