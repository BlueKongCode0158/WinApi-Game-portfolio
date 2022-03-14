#pragma once
#include "Skil.h"

class CDash final
	:public CSkil
{
private:
	CDash();
public:
	virtual ~CDash();
public:
	static CSkil* Create();
	static CSkil* Create(LPVOID pVoid);
public:
	// CSkil��(��) ���� ��ӵ�
	virtual int Ready_Skil() override;
	virtual int Update_Skil() override;
	virtual void Render_Skil(HDC hDC) override;
	virtual void Release_Skil() override;
};