#pragma once
#include "Skil.h"

class CSlash final
	:public CSkil
{
public:
	enum SlashAnimation
	{
		
	};
private:
	CSlash();
public:
	virtual ~CSlash();
public:
	static CSkil* Create();
	static CSkil* Create(LPVOID pVoid);
	static CSkil* Create(int iNum);
public:
	// CSkil을(를) 통해 상속됨
	virtual int Ready_Skil() override;
	virtual int Update_Skil() override;
	virtual void Render_Skil(HDC hDC) override;
	virtual void Release_Skil() override;
};