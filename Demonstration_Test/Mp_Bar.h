#pragma once
#include "MyUI.h"

class CMp_Bar final
	:public CMyUI
{
private:
	CMp_Bar();
public:
	virtual ~CMp_Bar();
public:
	// CMyUI��(��) ���� ��ӵ�
	virtual int Ready_UI() override;
	virtual void Update_UI() override;
	virtual void Late_Update_UI() override;
	virtual void Render_UI(HDC hDC) override;
public:
	static CMyUI* Create();
};